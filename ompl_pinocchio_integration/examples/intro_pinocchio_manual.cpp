/**
 * @file intro_pinocchio_manual.cpp
 * @brief A minimal example showing how to build a robot model with Pinocchio,
 *        compute forward kinematics, and print the end-effector placement.
 *
 * This code builds a robot model with several joints and runs forward kinematics.
 */

 #include <pinocchio/multibody/model.hpp>
 #include <pinocchio/multibody/data.hpp>
 #include <pinocchio/algorithm/kinematics.hpp>
 #include <pinocchio/algorithm/frames.hpp>
 #include <pinocchio/algorithm/joint-configuration.hpp>
 #include <iostream>
 #include <cmath>
 
 using namespace pinocchio;
 using namespace Eigen;
 
 /**
  * @brief Creates a simple robot model.
  *
  * The model is built by adding several joints to form a kinematic chain.
  * An end-effector frame is added at the last joint.
  *
  * @return Model The robot model.
  */
 Model create_model() {
   Model model;
 
   // ----- Create Link 0 -----
   // Add joint0 (revolute about Z) attached to the universe (parent = 0)
   JointIndex jid0 = model.addJoint(
       0,                             // Parent joint (universe)
       JointModelRZ(),                // Revolute joint about Z
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.0)),
       "joint0"
   );
   // Append a body to joint0.
   model.appendBodyToJoint(
       jid0,
       Inertia(1.0, Vector3d(0.0, 0.0, 0.5), Matrix3d::Identity() * 0.1),
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.1))
   );
   // Add a frame to joint0.
   Frame frame0("joint0", jid0, model.getFrameId("universe"), SE3::Identity(), OP_FRAME);
   model.addFrame(frame0, true);  // Update frame mapping
 
   // ----- Create Link 1 -----
   JointIndex jid1 = model.addJoint(
       jid0,                          // Parent: joint0
       JointModelRY(),                // Revolute about Y
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.2)),
       "joint1"
   );
   model.appendBodyToJoint(
       jid1,
       Inertia(1.0, Vector3d(0.0, 0.0, 0.5), Matrix3d::Identity() * 0.1),
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.25))
   );
   Frame frame1("joint1", jid1, model.getFrameId("joint0"), SE3::Identity(), OP_FRAME);
   model.addFrame(frame1, true);
 
   // ----- Create Link 2 -----
   JointIndex jid2 = model.addJoint(
       jid1,
       JointModelRY(),                // Revolute about Y
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.5)),
       "joint2"
   );
   model.appendBodyToJoint(
       jid2,
       Inertia(1.0, Vector3d(0.0, 0.0, 0.5), Matrix3d::Identity() * 0.1),
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.25))
   );
   Frame frame2("joint2", jid2, model.getFrameId("joint1"), SE3::Identity(), OP_FRAME);
   model.addFrame(frame2, true);
 
   // ----- Create Link 3 -----
   JointIndex jid3 = model.addJoint(
       jid2,
       JointModelRZ(),                // Revolute about Z
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.5)),
       "joint3"
   );
   model.appendBodyToJoint(
       jid3,
       Inertia(1.0, Vector3d(0.0, 0.0, 0.5), Matrix3d::Identity() * 0.1),
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.1))
   );
   Frame frame3("joint3", jid3, model.getFrameId("joint2"), SE3::Identity(), OP_FRAME);
   model.addFrame(frame3, true);
 
   // ----- Create Link 4 -----
   JointIndex jid4 = model.addJoint(
       jid3,
       JointModelRX(),                // Revolute about X
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.1)),
       "joint4"
   );
   model.appendBodyToJoint(
       jid4,
       Inertia(1.0, Vector3d(0.0, 0.0, 0.5), Matrix3d::Identity() * 0.1),
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.1))
   );
   Frame frame4("joint4", jid4, model.getFrameId("joint3"), SE3::Identity(), OP_FRAME);
   model.addFrame(frame4, true);
 
   // ----- Create Link 5 -----
   JointIndex jid5 = model.addJoint(
       jid4,
       JointModelRZ(),                // Revolute about Z
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.1)),
       "joint5"
   );
   model.appendBodyToJoint(
       jid5,
       Inertia(1.0, Vector3d(0.0, 0.0, 0.5), Matrix3d::Identity() * 0.1),
       SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.1))
   );
   Frame frame5("joint5", jid5, model.getFrameId("joint4"), SE3::Identity(), OP_FRAME);
   model.addFrame(frame5, true);
 
   // ----- Add End-Effector Frame -----
   Frame ee("ee", jid5, model.getFrameId("joint5"),
            SE3(Matrix3d::Identity(), Vector3d(0.0, 0.0, 0.2)), OP_FRAME);
   model.addFrame(ee, true);
 
   return model;
 }
 
 int main() {

    // Seed the standard random number generator with the current time.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create the robot model and associated data.
    Model model = create_model();
    Data data(model);
    
    // Define lower and upper bounds for the random configuration.
    // Here we assume all joints are rotational so we use [-pi, pi].
    VectorXd qmin(model.nq), qmax(model.nq);
    qmin.setConstant(-M_PI);
    qmax.setConstant(M_PI);
    
    // Generate a random configuration within the specified bounds.
    VectorXd q = randomConfiguration(model, qmin, qmax);
    
    // (Optional) Print the random configuration to verify its values.
    std::cout << "Random configuration (q): " << q.transpose() << std::endl;
    
    // Compute forward kinematics and update the frame placements.
    forwardKinematics(model, data, q);
    updateFramePlacements(model, data);
    
    // Retrieve and print the end-effector ("ee") placement.
    // The placement of the "ee" frame is stored in data.oMf[] at the index given by model.getFrameId("ee")
    SE3 ee_placement = data.oMf[model.getFrameId("ee")];
    std::cout << "End-effector placement (translation): " << std::endl;
    std::cout << ee_placement.translation().transpose() << std::endl;
    
    return 0;
 }
 