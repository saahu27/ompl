#ifndef OMPLAPP_G_MANIPULATOR_PLANNING_
#define OMPLAPP_G_MANIPULATOR_PLANNING_

#include "ManipulatorPlanning.h"
#include "omplapp/graphics/RenderGeometry.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <iostream>

namespace ompl {
namespace app {

class GManipulatorPlanning : public ManipulatorPlanning, public RenderGeometry {
public:
  GManipulatorPlanning()
    : ManipulatorPlanning(),
      RenderGeometry(*dynamic_cast<const RigidBodyGeometry*>(this), getGeometricStateExtractor())
  {
  }
  
  virtual ~GManipulatorPlanning() {}

  virtual int renderRobot() const override {
    ompl::base::ScopedState<> state = getDefaultStartState();
    GLuint listID = glGenLists(1);
    glNewList(listID, GL_COMPILE);
    for (unsigned int i = 0; i < getRobotCount(); ++i) {
      ompl::base::ScopedState<> linkPose = computeLinkPose(state.get(), i);
      Eigen::Matrix4d transform = se3StateToMatrix(linkPose.get());
      glPushMatrix();
      glMultMatrixd(transform.data());
      const aiScene* scene = getGeometrySpecification().robot[i];
      if (scene && scene->HasMeshes()) {
         scene::renderSceneWithTransform(scene);
         std::cout << "Rendered link " << i << std::endl;
      }
      else {
         std::cerr << "Warning: collision mesh for link " << i << " is invalid." << std::endl;
      }
      glPopMatrix();
    }
    glEndList();
    return listID;
  }

private:
  Eigen::Matrix4d se3StateToMatrix(const ompl::base::State* state) const {
    const auto* se3 = state->as<ompl::base::SE3StateSpace::StateType>();
    Eigen::Matrix4d mat = Eigen::Matrix4d::Identity();
    mat(0, 3) = se3->getX();
    mat(1, 3) = se3->getY();
    mat(2, 3) = se3->getZ();
    Eigen::Quaterniond q(se3->rotation().w,
                         se3->rotation().x,
                         se3->rotation().y,
                         se3->rotation().z);
    mat.block<3,3>(0,0) = q.toRotationMatrix();
    return mat;
  }
};

} // namespace app
} // namespace ompl

#endif
