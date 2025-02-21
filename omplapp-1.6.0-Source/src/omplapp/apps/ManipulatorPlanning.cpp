#include "ManipulatorPlanning.h"
#include "omplapp/geometry/detail/assimpUtil.h"  // For computeGeometrySpecification()
#include <pinocchio/parsers/urdf.hpp>              // For building the model from URDF
#include <pinocchio/algorithm/kinematics.hpp>
#include <pinocchio/algorithm/frames.hpp>
#include <iostream>
#include <cassert>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <tinyxml2.h>
#include <sstream>
#include <cmath>

// Include the SE3 state space header from OMPL.
#include <ompl/base/spaces/SE3StateSpace.h>

using namespace ompl::app;

ManipulatorPlanning::ManipulatorPlanning()
  : AppBase<AppType::GEOMETRIC>(std::make_shared<ompl::base::RealVectorStateSpace>(7), Motion_3D),
    nJoints_(0)
{
  name_ = "Manipulator Planning (URDF via Pinocchio)";
  jointSpace_ = getStateSpace();
  geomSpace_ = std::make_shared<ompl::base::SE3StateSpace>();
}

bool ManipulatorPlanning::setRobotMesh(const std::string &robot)
{
  std::string ext = robot.substr(robot.find_last_of(".") + 1);
  if(ext == "urdf" || ext == "URDF")
  {
    try {
      std::cout << "Loading URDF: " << robot << std::endl;
      // Build the robot model using Pinocchio.
      pinocchio::urdf::buildModel(robot, pinModel_);
      pinData_ = pinocchio::Data(pinModel_);
      nJoints_ = pinModel_.nq;
      std::cout << "Loaded URDF with " << nJoints_ << " joints." << std::endl;
      std::cout << "pinModel_.nframes = " << pinModel_.nframes << std::endl;
      
      // Clear existing geometry specification and collision indices.
      geom_.robot.clear();
      geom_.robotShift.clear();
      collisionLinkIndices_.clear();

      tinyxml2::XMLDocument doc;
      if(doc.LoadFile(robot.c_str()) != tinyxml2::XML_SUCCESS) {
         std::cerr << "Error parsing URDF XML" << std::endl;
         return false;
      }
      tinyxml2::XMLElement* robotElem = doc.FirstChildElement("robot");
      if(!robotElem) {
         std::cerr << "No <robot> element found in URDF." << std::endl;
         return false;
      }
      
      // Iterate over each link in the URDF.
      for (tinyxml2::XMLElement* linkElem = robotElem->FirstChildElement("link");
           linkElem;
           linkElem = linkElem->NextSiblingElement("link"))
      {
        const char* linkName = linkElem->Attribute("name");
        tinyxml2::XMLElement* collisionElem = linkElem->FirstChildElement("collision");
        if (collisionElem)
        {
          Eigen::Vector3d originTranslation = Eigen::Vector3d::Zero();
          tinyxml2::XMLElement* originElem = collisionElem->FirstChildElement("origin");
          if (originElem)
          {
            const char* xyz = originElem->Attribute("xyz");
            if (xyz)
            {
              std::istringstream iss(xyz);
              double x, y, z;
              if (iss >> x >> y >> z)
                originTranslation = Eigen::Vector3d(x, y, z);
            }
          }
          tinyxml2::XMLElement* geometryElem = collisionElem->FirstChildElement("geometry");
          if (geometryElem)
          {
            tinyxml2::XMLElement* meshElem = geometryElem->FirstChildElement("mesh");
            if (meshElem)
            {
              const char* filename = meshElem->Attribute("filename");
              if (filename)
              {
                std::string meshFile = filename;
                const aiScene* scenePtr = nullptr;
                // Always load a new importer instance for each collision geometry.
                if (RigidBodyGeometry::addRobotMesh(meshFile))
                {
                    scenePtr = importerRobot_[importerRobot_.size()-1]->GetScene();
                }
                else
                {
                    std::cerr << "Failed to load mesh: " << meshFile << std::endl;
                    continue;
                }
                if (!scenePtr)
                {
                  std::cerr << "Error: scene pointer is null for mesh: " << meshFile << std::endl;
                  continue;
                }
                // Get the frame id from the Pinocchio model.
                unsigned int frameId = pinModel_.getFrameId(linkName);
                if (frameId >= pinModel_.nframes)
                {
                  std::cerr << "Warning: Frame id " << frameId << " for link " << linkName
                            << " is out of range (nframes=" << pinModel_.nframes << "). Skipping." << std::endl;
                  continue;
                }
                std::cout << "Link " << linkName << " frame id = " << frameId << std::endl;
                // Store collision geometry and shift.
                aiVector3D shift(originTranslation.x(), originTranslation.y(), originTranslation.z());
                geom_.robotShift.push_back(shift);
                geom_.robot.push_back(scenePtr);
                collisionLinkIndices_.push_back(frameId);
                std::cout << "Loaded collision mesh for link " << linkName << std::endl;
              }
            }
          }
        }
      }
      
      std::cout << "Loaded " << geom_.robot.size() << " collision meshes (one per link)" << std::endl;
      std::cout << collisionLinkIndices_.size() << " collision link indices." << std::endl;
      if (geom_.robot.empty())
      {
         std::cerr << "No collision geometry found in URDF via XML parsing." << std::endl;
         return RigidBodyGeometry::setRobotMesh(robot);
      }
      
      // Filter out any invalid importer entries.
      {
        std::vector< std::shared_ptr<Assimp::Importer> > validImporters;
        std::vector<unsigned int> validFrameIDs;
        for (unsigned int i = 0; i < importerRobot_.size(); i++) {
          const aiScene* scene = importerRobot_[i]->GetScene();
          if (scene != nullptr && scene->HasMeshes()) {
            validImporters.push_back(importerRobot_[i]);
            if(i < collisionLinkIndices_.size())
              validFrameIDs.push_back(collisionLinkIndices_[i]);
          }
          else {
            std::cerr << "Warning: importerRobot_[" << i << "] returned an invalid scene." << std::endl;
          }
        }
        importerRobot_ = validImporters;
        collisionLinkIndices_ = validFrameIDs;
        computeGeometrySpecification();
      }
      
      // Update the joint space dimension if needed.
      if(nJoints_ > 0 && getStateSpace()->getDimension() != nJoints_)
      {
         ompl::base::StateSpacePtr newJointSpace = std::make_shared<ompl::base::RealVectorStateSpace>(nJoints_);
         ompl::base::RealVectorBounds bounds(nJoints_);
         for(unsigned int i = 0; i < nJoints_; ++i)
         {
            bounds.low[i] = -3.14;
            bounds.high[i] =  3.14;
         }
         newJointSpace->as<ompl::base::RealVectorStateSpace>()->setBounds(bounds);
         jointSpace_ = newJointSpace;
         std::cout << "Updated joint space dimension to " << nJoints_ << std::endl;
      }
      
      std::cout << "Loading done" << std::endl;
      return true;
    }
    catch (const std::exception &ex)
    {
       std::cerr << "Error loading URDF: " << ex.what() << std::endl;
       return false;
    }
  }
  else
  {
      return RigidBodyGeometry::setRobotMesh(robot);
  }
}

ompl::base::RealVectorBounds ManipulatorPlanning::inferEnvironmentBounds() const
{
  ompl::base::RealVectorBounds bounds(3);
  bounds.setLow(-5);
  bounds.setHigh(5);
  return bounds;
}

// NOTE: Instead of delegating to the base class method, we now return the locally stored shift.
aiVector3D ManipulatorPlanning::getRobotCenter(unsigned int robotIndex) const
{
  if (robotIndex < geom_.robotShift.size())
    return geom_.robotShift[robotIndex];
  else
    return aiVector3D(0,0,0);
}

ompl::base::ScopedState<> ManipulatorPlanning::getDefaultStartState() const
{
  ompl::base::ScopedState<ompl::base::RealVectorStateSpace> state(jointSpace_);
  std::vector<double> home = {0.0, -0.785, 0.0, -2.356, 0.0, 1.571, 0.785, 0.0, 0.0};
  assert(home.size() == jointSpace_->getDimension());
  for (unsigned int i = 0; i < home.size(); ++i)
    state->values[i] = home[i];
  return state;
}

GeometricStateExtractor ManipulatorPlanning::getGeometricStateExtractor() const
{
  return [this](const ompl::base::State* state, unsigned int index) -> const ompl::base::State*
  {
    ompl::base::ScopedState<> linkPose = this->computeLinkPose(state, index);
    ompl::base::State* s = getGeometricComponentStateSpace()->allocState();
    getGeometricComponentStateSpace()->copyState(s, linkPose.get());
    return s;
  };
}

const GeometrySpecification& ManipulatorPlanning::getGeometrySpecification() const
{
   return geom_;
}

const ompl::base::StateSpacePtr& ManipulatorPlanning::getGeometricComponentStateSpace() const
{
  return geomSpace_;
}

unsigned int ManipulatorPlanning::getRobotCount() const
{
  return static_cast<unsigned int>( getGeometrySpecification().robot.size() );
}

const ompl::base::State* ManipulatorPlanning::getGeometricComponentStateInternal(
    const ompl::base::State* state, unsigned int index) const
{
  ompl::base::ScopedState<> linkPose = computeLinkPose(state, index);
  ompl::base::State* s = getGeometricComponentStateSpace()->allocState();
  getGeometricComponentStateSpace()->copyState(s, linkPose.get());
  return s;
}

ompl::base::ScopedState<> ManipulatorPlanning::computeLinkPose(
    const ompl::base::State* state, unsigned int linkIndex) const
{
  const auto* rstate = state->as<ompl::base::RealVectorStateSpace::StateType>();
  Eigen::VectorXd q(nJoints_);
  for (unsigned int i = 0; i < nJoints_; ++i)
    q[i] = rstate->values[i];

  // Compute forward kinematics.
  pinocchio::forwardKinematics(pinModel_, pinData_, q);
  pinocchio::updateFramePlacements(pinModel_, pinData_);

  if (collisionLinkIndices_.empty())
  {
    ompl::base::ScopedState<ompl::base::SE3StateSpace> identity(geomSpace_);
    identity->setXYZ(0,0,0);
    identity->rotation().setIdentity();
    return identity;
  }

  if (linkIndex >= collisionLinkIndices_.size())
    linkIndex = 0;
  unsigned int frame_id = collisionLinkIndices_[linkIndex];
  std::cout << "Link " << linkIndex << " frame id = " << frame_id << std::endl;
  std::cout << "pinData_.oMf.size() = " << pinData_.oMf.size()
            << ", pinModel_.nframes = " << pinModel_.nframes << std::endl;
  
  if (frame_id >= pinData_.oMf.size() || frame_id >= pinModel_.nframes)
  {
      std::cerr << "Warning: frame_id " << frame_id << " is out of range. Returning identity transform." << std::endl;
      ompl::base::ScopedState<ompl::base::SE3StateSpace> identity(geomSpace_);
      identity->setXYZ(0,0,0);
      identity->rotation().setIdentity();
      return identity;
  }
  
  pinocchio::SE3 se3 = pinData_.oMf[frame_id];
  std::cout << "Link " << linkIndex << " translation: " 
            << se3.translation().transpose() << std::endl;

  const GeometrySpecification &gs = getGeometrySpecification();
  Eigen::Vector3d offset = Eigen::Vector3d::Zero();
  if (linkIndex < gs.robotShift.size())
    offset = Eigen::Vector3d(gs.robotShift[linkIndex].x,
                             gs.robotShift[linkIndex].y,
                             gs.robotShift[linkIndex].z);
  
  Eigen::Vector3d finalTranslation = se3.translation() + se3.rotation() * offset;
  se3.translation() = finalTranslation;
  std::cout << "Link " << linkIndex << " final translation: " 
            << finalTranslation.transpose() << std::endl;

  ompl::base::ScopedState<ompl::base::SE3StateSpace> se3state(geomSpace_);
  se3state->setXYZ(se3.translation().x(), se3.translation().y(), se3.translation().z());
  Eigen::Quaterniond quat(se3.rotation());
  se3state->rotation().x = quat.x();
  se3state->rotation().y = quat.y();
  se3state->rotation().z = quat.z();
  se3state->rotation().w = quat.w();
  return se3state;
}

bool ManipulatorPlanning::isSelfCollisionEnabled() const
{
  return true;
}

ompl::base::ScopedState<> ManipulatorPlanning::getFullStateFromGeometricComponent(
    const ompl::base::ScopedState<> &state) const
{
  return state;
}
