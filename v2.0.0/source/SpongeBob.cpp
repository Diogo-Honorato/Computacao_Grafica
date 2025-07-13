#include "../include/SpongeBob.hpp"
/*
    Teclas de controle:
    -press key 2 to make the animation
    -press key 1 to return to the original position
*/

SpongeBob::SpongeBob()
{
    buildBody();
    buildShoulders();
    buildRightArm();
    buildLeftArm();
    buildRightLeg();
    buildLeftLeg();
    buildFace();
    buildEyes();
    buildEyelashes();
}

void SpongeBob::buildBody()
{
    // Body cuboid
    Shapes.push_back(std::make_unique<Cube>("../texture/bob_back.png"));
    
    glm::mat4 model_body = glm::mat4(1.0);
    model_body = glm::translate(model_body, glm::vec3(0.0, 0.0, -4.0));
    model_body = glm::scale(model_body, glm::vec3(3.0, 4.0, 1.0));
    
    matrices.push_back(model_body);
}

void SpongeBob::buildShoulders()
{
    // Shoulders (cones)
    Shapes.push_back(std::make_unique<AxialExtruder>(0.0f, 0.25f, 0.5f, 36, 8, "../texture/white.jpg"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.0f, 0.25f, 0.5f, 36, 8, "../texture/white.jpg"));

    glm::mat4 model_R_shoulder = glm::mat4(1.0);
    model_R_shoulder = glm::translate(model_R_shoulder, glm::vec3(1.75, 0.0, -4.0));
    model_R_shoulder = glm::rotate(model_R_shoulder, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
    
    glm::mat4 model_L_shoulder = glm::mat4(1.0);
    model_L_shoulder = glm::translate(model_L_shoulder, glm::vec3(-1.75, 0.0, -4.0));
    model_L_shoulder = glm::rotate(model_L_shoulder, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));

    matrices.push_back(model_R_shoulder);
    matrices.push_back(model_L_shoulder);
}

void SpongeBob::buildRightArm()
{
    // Right arm parts
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.5f, 36, 8, "../texture/yellow.png"));
    Shapes.push_back(std::make_unique<Sphere>(0.15f, 16, 8, "../texture/cinza.jpg"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.5f, 36, 8, "../texture/yellow.png"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.3f, 0.3f, 0.1f, 4, 1, "../texture/yellow.png"));

    glm::mat4 model_R_arm = glm::mat4(1.0);
    model_R_arm = glm::translate(model_R_arm, glm::vec3(2.25, 0.0, -4.0));
    model_R_arm = glm::rotate(model_R_arm, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 model_R_elbow = glm::mat4(1.0);
    model_R_elbow = glm::translate(model_R_elbow, glm::vec3(2.58, 0.0, -4.0));

    glm::mat4 model_R_forearm = glm::mat4(1.0);
    model_R_forearm = glm::translate(model_R_forearm, glm::vec3(2.91, 0.0, -4.0));
    model_R_forearm = glm::rotate(model_R_forearm, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 model_R_hand = glm::mat4(1.0);
    model_R_hand = glm::translate(model_R_hand, glm::vec3(3.37, 0.0, -4.0));
    model_R_hand = glm::rotate(model_R_hand, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    matrices.push_back(model_R_arm);
    matrices.push_back(model_R_elbow);
    index_R_forearm = matrices.size();
    matrices.push_back(model_R_forearm);
    index_R_hand = matrices.size();
    matrices.push_back(model_R_hand);
}

void SpongeBob::buildLeftArm()
{
    // Left arm parts (similar to right arm)
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.5f, 36, 8, "../texture/yellow.png"));
    Shapes.push_back(std::make_unique<Sphere>(0.15f, 16, 8, "../texture/cinza.jpg"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.5f, 36, 8, "../texture/yellow.png"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.3f, 0.3f, 0.1f, 4, 1, "../texture/yellow.png"));

    glm::mat4 model_L_arm = glm::mat4(1.0);
    model_L_arm = glm::translate(model_L_arm, glm::vec3(-2.25, 0.0, -4.0));
    model_L_arm = glm::rotate(model_L_arm, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 model_L_elbow = glm::mat4(1.0);
    model_L_elbow = glm::translate(model_L_elbow, glm::vec3(-2.58, 0.0, -4.0));

    glm::mat4 model_L_forearm = glm::mat4(1.0);
    model_L_forearm = glm::translate(model_L_forearm, glm::vec3(-2.91, 0.0, -4.0));
    model_L_forearm = glm::rotate(model_L_forearm, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 model_L_hand = glm::mat4(1.0);
    model_L_hand = glm::translate(model_L_hand, glm::vec3(-3.37, 0.0, -4.0));
    model_L_hand = glm::rotate(model_L_hand, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    matrices.push_back(model_L_arm);
    matrices.push_back(model_L_elbow);
    index_L_forearm = matrices.size();
    matrices.push_back(model_L_forearm);
    index_L_hand = matrices.size();
    matrices.push_back(model_L_hand);
}

void SpongeBob::buildRightLeg()
{
    // Right leg parts
    Shapes.push_back(std::make_unique<Sphere>(0.25f, 16, 8, "../texture/cinza.jpg"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.5f, 36, 8, "../texture/yellow.png"));
    Shapes.push_back(std::make_unique<Sphere>(0.2f, 16, 8, "../texture/cinza.jpg"));        
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.42f, 36, 8, "../texture/bob_leg.png"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.2f, 0.2f, 0.1f, 4, 1, "../texture/preto.png"));

    glm::mat4 model_R_leg_ligament = glm::mat4(1.0);
    model_R_leg_ligament = glm::translate(model_R_leg_ligament, glm::vec3(0.75, -2.3, -4.0));
    
    glm::mat4 model_R_thigh = glm::mat4(1.0);
    model_R_thigh = glm::translate(model_R_thigh, glm::vec3(0.75, -2.79, -4.0));
    model_R_thigh = glm::rotate(model_R_thigh, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    
    glm::mat4 model_R_knee = glm::mat4(1.0);
    model_R_knee = glm::translate(model_R_knee, glm::vec3(0.75, -3.24, -4.0));

    glm::mat4 model_R_calf = glm::mat4(1.0);
    model_R_calf = glm::translate(model_R_calf, glm::vec3(0.75, -3.65, -4.0));
    model_R_calf = glm::rotate(model_R_calf, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

    glm::mat4 model_R_foot = glm::mat4(1.0);
    model_R_foot = glm::translate(model_R_foot, glm::vec3(0.75, -3.96, -3.8));
    model_R_foot = glm::scale(model_R_foot, glm::vec3(-2.0f, -2.0f, 3.5f));
    model_R_foot = glm::rotate(model_R_foot, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model_R_foot = glm::rotate(model_R_foot, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    matrices.push_back(model_R_leg_ligament);
    matrices.push_back(model_R_thigh);
    matrices.push_back(model_R_knee);
    matrices.push_back(model_R_calf);
    matrices.push_back(model_R_foot);
}

void SpongeBob::buildLeftLeg()
{
    // Left leg parts (similar to right leg)
    Shapes.push_back(std::make_unique<Sphere>(0.25f, 16, 8, "../texture/cinza.jpg"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.5f, 36, 8, "../texture/yellow.png"));
    Shapes.push_back(std::make_unique<Sphere>(0.2f, 16, 8, "../texture/cinza.jpg"));        
    Shapes.push_back(std::make_unique<AxialExtruder>(0.1f, 0.1f, 0.42f, 36, 8, "../texture/bob_leg.png"));
    Shapes.push_back(std::make_unique<AxialExtruder>(0.2f, 0.2f, 0.1f, 4, 1, "../texture/preto.png"));

    glm::mat4 model_L_leg_ligament = glm::mat4(1.0);
    model_L_leg_ligament = glm::translate(model_L_leg_ligament, glm::vec3(-0.75, -2.3, -4.0));
    
    glm::mat4 model_L_thigh = glm::mat4(1.0);
    model_L_thigh = glm::translate(model_L_thigh, glm::vec3(-0.75, -2.79, -4.0));
    model_L_thigh = glm::rotate(model_L_thigh, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    
    glm::mat4 model_L_knee = glm::mat4(1.0);
    model_L_knee = glm::translate(model_L_knee, glm::vec3(-0.75, -3.24, -4.0));

    glm::mat4 model_L_calf = glm::mat4(1.0);
    model_L_calf = glm::translate(model_L_calf, glm::vec3(-0.75, -3.65, -4.0));
    model_L_calf = glm::rotate(model_L_calf, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

    glm::mat4 model_L_foot = glm::mat4(1.0);
    model_L_foot = glm::translate(model_L_foot, glm::vec3(-0.75, -3.96, -3.8));
    model_L_foot = glm::scale(model_L_foot, glm::vec3(-2.0f, -2.0f, 3.5f));
    model_L_foot = glm::rotate(model_L_foot, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model_L_foot = glm::rotate(model_L_foot, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    matrices.push_back(model_L_leg_ligament);
    matrices.push_back(model_L_thigh);
    matrices.push_back(model_L_knee);
    matrices.push_back(model_L_calf);
    matrices.push_back(model_L_foot);
}

void SpongeBob::buildFace()
{
    // Face parts
    Shapes.push_back(std::make_unique<Sphere>(0.7f, 36, 18, "../texture/white.jpg"));
    Shapes.push_back(std::make_unique<Sphere>(0.7f, 36, 18, "../texture/white.jpg"));
    Shapes.push_back(std::make_unique<Paraboloid>(false, false, -0.6f, 0.75, 36, 18, "../texture/palpe.png"));
    Shapes.push_back(std::make_unique<Paraboloid>(false, false, -0.6f, 0.75, 36, 18, "../texture/palpe.png"));
    Shapes.push_back(std::make_unique<Sphere>(0.25, 36, 18, "../texture/noise.png"));

    std::vector<float> p = Line::generateParabolaPoints(0.5f, 0.0f, -0.9f, -1.3f, 1.3f, 30);
    std::vector<glm::vec3> parabolaPoints;
    parabolaPoints.reserve(p.size() / 3);
    for (size_t i = 0; i < p.size(); i += 3) {
        parabolaPoints.emplace_back(p[i], p[i+1], p[i+2]);
    }
    Shapes.push_back(std::make_unique<Pipe>(parabolaPoints, 0.1f, 0.1f, 2, "../texture/preto.png"));
    Shapes.push_back(std::make_unique<Cube>("../texture/white.jpg"));
    Shapes.push_back(std::make_unique<Cube>("../texture/white.jpg"));

    glm::mat4 model_R_eye = glm::mat4(1.0f);
    model_R_eye = glm::translate(model_R_eye, glm::vec3(0.75, 0.7, -3.8));
    model_R_eye = glm::scale(model_R_eye, glm::vec3(1.0, 1.1, 1.0));

    glm::mat4 model_L_eye = glm::mat4(1.0f);
    model_L_eye = glm::translate(model_L_eye, glm::vec3(-0.75, 0.7, -3.8));
    model_L_eye = glm::scale(model_L_eye, glm::vec3(1.0, 1.1, 1.0));

    glm::mat4 model_R_eyelid = glm::mat4(1.0f);
    model_R_eyelid = glm::translate(model_R_eyelid, glm::vec3(0.75, 1.55, -3.75));

    glm::mat4 model_L_eyelid = glm::mat4(1.0f);
    model_L_eyelid = glm::translate(model_L_eyelid, glm::vec3(-0.75, 1.55, -3.75));
    
    glm::mat4 model_noise = glm::mat4(1.0f);
    model_noise = glm::translate(model_noise, glm::vec3(0.0, 0.2, -3.5));
    model_noise = glm::rotate(model_noise, glm::radians(-5.0f), glm::vec3(1.0, 0.0, 0.0));
    model_noise = glm::scale(model_noise, glm::vec3(1.0, 1.0, 4.0));

    glm::mat4 model_mouth = glm::mat4(1.0f);
    model_mouth = glm::translate(model_mouth, glm::vec3(0.0, 0.0, -3.49));
    
    glm::mat4 model_R_teeth = glm::mat4(1.0f);
    model_R_teeth = glm::translate(model_R_teeth, glm::vec3(0.3, -1.05, -3.48));
    model_R_teeth = glm::scale(model_R_teeth, glm::vec3(0.5, 0.5, 0.1));

    glm::mat4 model_L_teeth = glm::mat4(1.0f);
    model_L_teeth = glm::translate(model_L_teeth, glm::vec3(-0.3, -1.05, -3.48));
    model_L_teeth = glm::scale(model_L_teeth, glm::vec3(0.5, 0.5, 0.1));

    matrices.push_back(model_R_eye);
    matrices.push_back(model_L_eye);
    matrices.push_back(model_R_eyelid);
    matrices.push_back(model_L_eyelid);
    matrices.push_back(model_noise);
    matrices.push_back(model_mouth);
    matrices.push_back(model_R_teeth);
    matrices.push_back(model_L_teeth);
}

void SpongeBob::buildEyes()
{
    // Eye details
    Shapes.push_back(std::make_unique<Paraboloid>(false, false, 0.05, 0.75, 36, 18, "../texture/iris.png"));
    Shapes.push_back(std::make_unique<Paraboloid>(false, false, 0.05, 0.75, 36, 18, "../texture/iris.png"));
    Shapes.push_back(std::make_unique<Paraboloid>(false, false, 0.05, 0.75, 36, 18, "../texture/preto.png"));
    Shapes.push_back(std::make_unique<Paraboloid>(false, false, 0.05, 0.75, 36, 18, "../texture/preto.png"));

    glm::mat4 model_R_iris = glm::mat4(1.0f);
    model_R_iris = glm::translate(model_R_iris, glm::vec3(0.75, 0.7, -3.08));
    model_R_iris = glm::rotate(model_R_iris, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model_R_iris = glm::scale(model_R_iris, glm::vec3(0.3, 1.0, 0.3));

    glm::mat4 model_L_iris = glm::mat4(1.0f);
    model_L_iris = glm::translate(model_L_iris, glm::vec3(-0.75, 0.7, -3.08));
    model_L_iris = glm::rotate(model_L_iris, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model_L_iris = glm::scale(model_L_iris, glm::vec3(0.3, 1.0, 0.3));

    glm::mat4 model_R_pupil = glm::mat4(1.0f);
    model_R_pupil = glm::translate(model_R_pupil, glm::vec3(0.75, 0.7, -3.05));
    model_R_pupil = glm::rotate(model_R_pupil, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model_R_pupil = glm::scale(model_R_pupil, glm::vec3(0.2, 1.0, 0.2));

    glm::mat4 model_L_pupil = glm::mat4(1.0f);
    model_L_pupil = glm::translate(model_L_pupil, glm::vec3(-0.75, 0.7, -3.05));
    model_L_pupil = glm::rotate(model_L_pupil, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model_L_pupil = glm::scale(model_L_pupil, glm::vec3(0.2, 1.0, 0.2));

    matrices.push_back(model_R_iris); 
    matrices.push_back(model_L_iris);
    matrices.push_back(model_R_pupil); 
    matrices.push_back(model_L_pupil);
}

void SpongeBob::buildEyelashes()
{
    // Eyelashes
    Shapes.push_back(std::make_unique<Cube>("../texture/preto.png"));
    Shapes.push_back(std::make_unique<Cube>("../texture/preto.png"));
    Shapes.push_back(std::make_unique<Cube>("../texture/preto.png"));
    Shapes.push_back(std::make_unique<Cube>("../texture/preto.png"));
    Shapes.push_back(std::make_unique<Cube>("../texture/preto.png"));
    Shapes.push_back(std::make_unique<Cube>("../texture/preto.png"));

    glm::mat4 model_RR_eyelash = glm::mat4(1.0f);
    model_RR_eyelash = glm::translate(model_RR_eyelash, glm::vec3(1.2, 1.47, -3.48));
    model_RR_eyelash = glm::rotate(model_RR_eyelash, glm::radians(-35.0f), glm::vec3(0.0, 0.0, 1.0));
    model_RR_eyelash = glm::scale(model_RR_eyelash, glm::vec3(0.2, 0.3, 0.1));

    glm::mat4 model_MR_eyelash = glm::mat4(1.0f);
    model_MR_eyelash = glm::translate(model_MR_eyelash, glm::vec3(0.75, 1.59, -3.48));
    model_MR_eyelash = glm::scale(model_MR_eyelash, glm::vec3(0.2, 0.3, 0.1));

    glm::mat4 model_LR_eyelash = glm::mat4(1.0f);
    model_LR_eyelash = glm::translate(model_LR_eyelash, glm::vec3(0.3, 1.47, -3.48));
    model_LR_eyelash = glm::rotate(model_LR_eyelash, glm::radians(35.0f), glm::vec3(0.0, 0.0, 1.0));
    model_LR_eyelash = glm::scale(model_LR_eyelash, glm::vec3(0.2, 0.3, 0.1));

    glm::mat4 model_RL_eyelash = glm::mat4(1.0f);
    model_RL_eyelash = glm::translate(model_RL_eyelash, glm::vec3(-1.2, 1.47, -3.48));
    model_RL_eyelash = glm::rotate(model_RL_eyelash, glm::radians(35.0f), glm::vec3(0.0, 0.0, 1.0));
    model_RL_eyelash = glm::scale(model_RL_eyelash, glm::vec3(0.2, 0.3, 0.1));

    glm::mat4 model_ML_eyelash = glm::mat4(1.0f);
    model_ML_eyelash = glm::translate(model_ML_eyelash, glm::vec3(-0.75, 1.59, -3.48));
    model_ML_eyelash = glm::scale(model_ML_eyelash, glm::vec3(0.2, 0.3, 0.1));

    glm::mat4 model_LL_eyelash = glm::mat4(1.0f);
    model_LL_eyelash = glm::translate(model_LL_eyelash, glm::vec3(-0.3, 1.47, -3.48));
    model_LL_eyelash = glm::rotate(model_LL_eyelash, glm::radians(-35.0f), glm::vec3(0.0, 0.0, 1.0));
    model_LL_eyelash = glm::scale(model_LL_eyelash, glm::vec3(0.2, 0.3, 0.1));

    matrices.push_back(model_RR_eyelash);
    matrices.push_back(model_MR_eyelash);
    matrices.push_back(model_LR_eyelash);
    matrices.push_back(model_RL_eyelash);
    matrices.push_back(model_ML_eyelash);
    matrices.push_back(model_LL_eyelash);
}

void SpongeBob::processArmInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        // Default arm position
        glm::mat4 model_R_forearm = glm::mat4(1.0);
        model_R_forearm = glm::translate(model_R_forearm, glm::vec3(2.91, 0.0, -4.0));
        model_R_forearm = glm::rotate(model_R_forearm, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 model_R_hand = glm::mat4(1.0);
        model_R_hand = glm::translate(model_R_hand, glm::vec3(3.37, 0.0, -4.0));
        model_R_hand = glm::rotate(model_R_hand, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 model_L_forearm = glm::mat4(1.0);
        model_L_forearm = glm::translate(model_L_forearm, glm::vec3(-2.91, 0.0, -4.0));
        model_L_forearm = glm::rotate(model_L_forearm, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 model_L_hand = glm::mat4(1.0);
        model_L_hand = glm::translate(model_L_hand, glm::vec3(-3.37, 0.0, -4.0));
        model_L_hand = glm::rotate(model_L_hand, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        matrices[index_R_forearm] = model_R_forearm;
        matrices[index_R_hand] = model_R_hand;
        matrices[index_L_forearm] = model_L_forearm;
        matrices[index_L_hand] = model_L_hand;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        // Raised arm position
        glm::mat4 model_R_forearm = glm::mat4(1.0);
        model_R_forearm = glm::translate(model_R_forearm, glm::vec3(2.58, 0.4, -4.0));
        model_R_forearm = glm::rotate(model_R_forearm, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        
        glm::mat4 model_R_hand = glm::mat4(1.0);
        model_R_hand = glm::translate(model_R_hand, glm::vec3(2.58, 0.87, -4.0));
        model_R_hand = glm::rotate(model_R_hand, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 model_L_forearm = glm::mat4(1.0);
        model_L_forearm = glm::translate(model_L_forearm, glm::vec3(-2.58, 0.4, -4.0));
        model_L_forearm = glm::rotate(model_L_forearm, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        
        glm::mat4 model_L_hand = glm::mat4(1.0);
        model_L_hand = glm::translate(model_L_hand, glm::vec3(-2.58, 0.87, -4.0));
        model_L_hand = glm::rotate(model_L_hand, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        
        matrices[index_R_forearm] = model_R_forearm;
        matrices[index_R_hand] = model_R_hand;
        matrices[index_L_forearm] = model_L_forearm;
        matrices[index_L_hand] = model_L_hand;
    }
}

void SpongeBob::drawSpongeBob(const glm::mat4& projection, const glm::mat4& view)
{
    for (size_t i = 0; i < Shapes.size(); i++)
    {
        Shapes[i]->getShader().useShaders();
        Shapes[i]->getShader().setMat4("model", matrices[i]);
        Shapes[i]->getShader().setMat4("projection", projection);
        Shapes[i]->getShader().setMat4("view", view);

        Shapes[i]->getTexture()->Bind();
        Shapes[i]->desenhar();
        Shapes[i]->getTexture()->Unbind();
    }
}