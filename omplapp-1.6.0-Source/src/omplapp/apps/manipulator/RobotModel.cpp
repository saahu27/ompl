#include "RobotModel.h"
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <cassert>

std::shared_ptr<fcl::CollisionObjectd> RobotModel::buildCollisionObjectFromMesh(const std::string &meshFile)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshFile, 
      aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if(!scene || !scene->HasMeshes()){
        std::cerr << "Error loading mesh: " << meshFile << std::endl;
        return nullptr;
    }
    // For simplicity, use the first mesh.
    const aiMesh* mesh = scene->mMeshes[0];

    std::vector<fcl::Vector3d> points;
    std::vector<fcl::Triangle> triangles;

    // Extract vertices.
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        aiVector3D v = mesh->mVertices[i];
        points.emplace_back(v.x, v.y, v.z);
    }
    // Extract triangles.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        const aiFace& face = mesh->mFaces[i];
        if(face.mNumIndices == 3){
            triangles.emplace_back(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
        }
    }
    // Build FCL BVH model.
    auto bvhModel = std::make_shared<fcl::BVHModel<fcl::OBBRSSd>>();
    bvhModel->beginModel();
    bvhModel->addSubModel(points, triangles);
    bvhModel->endModel();

    // Create a collision object with identity transform.
    return std::make_shared<fcl::CollisionObjectd>(bvhModel);
}

RobotModel::RobotModel(const std::string &urdf_path)
{
    try {
        pinocchio::urdf::buildModel(urdf_path, model_);
        data_ = pinocchio::Data(model_);
        std::cout << "Loaded robot model from: " << urdf_path << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error loading robot model: " << e.what() << std::endl;
        throw;
    }
}

void RobotModel::computeForwardKinematics(const Eigen::VectorXd &q)
{
    if(q.size() != model_.nq){
        std::cerr << "Dimension mismatch in computeForwardKinematics" << std::endl;
        return;
    }
    pinocchio::forwardKinematics(model_, data_, q);
    pinocchio::updateGlobalPlacements(model_, data_);
}

bool RobotModel::isStateValid(const Eigen::VectorXd &q) const
{
    if(q.size() != model_.nq) {
        std::cerr << "Invalid state dimension" << std::endl;
        return false;
    }
    if(model_.lowerPositionLimit.size() == static_cast<size_t>(model_.nq) &&
       model_.upperPositionLimit.size() == static_cast<size_t>(model_.nq))
    {
        for(int i = 0; i < q.size(); i++){
            if(q[i] < model_.lowerPositionLimit[i] || q[i] > model_.upperPositionLimit[i])
                return false;
        }
    }
    return true;
}

bool RobotModel::addLinkCollisionMesh(const std::string &linkName, const std::string &meshFile)
{
    auto colObj = buildCollisionObjectFromMesh(meshFile);
    if(!colObj) {
        return false;
    }
    LinkCollision lc;
    lc.linkName = linkName;
    lc.collisionObject = colObj;
    linkCollisions_.push_back(lc);
    std::cout << "Loaded collision mesh for link: " << linkName << " from " << meshFile << std::endl;
    return true;
}
