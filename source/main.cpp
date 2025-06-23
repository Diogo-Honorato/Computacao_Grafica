#include "../include/main.hpp"

/*
    Teclas de controle:
        - ESC: Fecha a janela.
        - W, A, S, D: Movimento da câmera (frente, trás, esquerda, direita).
        - Mouse: Controla rotação da câmera.
        - Scroll: Controla zoom (campo de visão).
        - Q: Define modo de renderização como preenchido (GL_FILL).
        - E: Define modo de renderização como wireframe (GL_LINE).
        - R: Define modo de renderização como pontos (GL_POINT).
*/

void processArmInput(GLFWwindow *window, std::vector<glm::mat4> &matrices, size_t index_R_forearm, size_t index_R_hand, size_t index_L_forearm, size_t index_L_hand) {
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {

        glm::mat4 model_R_forearm = glm::mat4(1.0);
        model_R_forearm = glm::translate(model_R_forearm,glm::vec3(2.91,0.0,-4.0));
        model_R_forearm = glm::rotate(model_R_forearm,glm::radians(-90.0f),glm::vec3(0.0,1.0,0.0));

        glm::mat4 model_R_hand = glm::mat4(1.0);
        model_R_hand = glm::translate(model_R_hand,glm::vec3(3.37,0.0,-4.0));
        model_R_hand = glm::rotate(model_R_hand,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));

        glm::mat4 model_L_forearm = glm::mat4(1.0);
        model_L_forearm = glm::translate(model_L_forearm,glm::vec3(-2.91,0.0,-4.0));
        model_L_forearm = glm::rotate(model_L_forearm,glm::radians(-90.0f),glm::vec3(0.0,1.0,0.0));

        glm::mat4 model_L_hand = glm::mat4(1.0);
        model_L_hand = glm::translate(model_L_hand,glm::vec3(-3.37,0.0,-4.0));
        model_L_hand = glm::rotate(model_L_hand,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));

        matrices[index_R_forearm] = model_R_forearm;
        matrices[index_R_hand] = model_R_hand;
        matrices[index_L_forearm] = model_L_forearm;
        matrices[index_L_hand] = model_L_hand;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {

        //animation R_forearm
        glm::mat4 model_R_forearm = glm::mat4(1.0);
        model_R_forearm = glm::translate(model_R_forearm,glm::vec3(2.58,0.4,-4.0));
        model_R_forearm = glm::rotate(model_R_forearm,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));
        
        //animation R_hand
        glm::mat4 model_R_hand = glm::mat4(1.0);
        model_R_hand = glm::translate(model_R_hand,glm::vec3(2.58,0.87,-4.0));
        model_R_hand = glm::rotate(model_R_hand,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));

        //animation L_forearm
        glm::mat4 model_L_forearm = glm::mat4(1.0);
        model_L_forearm = glm::translate(model_L_forearm,glm::vec3(-2.58,0.4,-4.0));
        model_L_forearm = glm::rotate(model_L_forearm,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));
        
        //animation L_hand
        glm::mat4 model_L_hand = glm::mat4(1.0);
        model_L_hand = glm::translate(model_L_hand,glm::vec3(-2.58,0.87,-4.0));
        model_L_hand = glm::rotate(model_L_hand,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));
        
        matrices[index_R_forearm] = model_R_forearm;
        matrices[index_R_hand] = model_R_hand;
        matrices[index_L_forearm] = model_L_forearm;
        matrices[index_L_hand] = model_L_hand;
    }
}

int main()
{
    // Cria janela
    GLFWwindow *window = startWindowCamera(WIN_WIDTH, WIN_HEIGHT, "Engine");
    if (initializeOpenGL(window, true) == -1)
    {
        return -1;
    }


    {
        std::vector<std::unique_ptr<Shape>> Shapes;
        std::vector<glm::mat4> matrices;

        //cuboid
        Shapes.push_back(std::make_unique<Cube>("../texture/bob_back.png"));
        
        glm::mat4 model_body = glm::mat4(1.0);
        model_body = glm::translate(model_body,glm::vec3(0.0,0.0,-4.0));
        model_body = glm::scale(model_body,glm::vec3(3.0,4.0,1.0));
        
        matrices.push_back(model_body);


        //cone for the sholders
        Shapes.push_back(std::make_unique<AxialExtruder>(0.0f,0.25f,0.5f,36,8,"../texture/white.jpg"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.0f,0.25f,0.5f,36,8,"../texture/white.jpg"));

        glm::mat4 model_R_sholder = glm::mat4(1.0);
        model_R_sholder = glm::translate(model_R_sholder,glm::vec3(1.75,0.0,-4.0));
        model_R_sholder = glm::rotate(model_R_sholder,glm::radians(-90.0f),glm::vec3(0.0,1.0,0.0));
        
        glm::mat4 model_L_sholder = glm::mat4(1.0);
        model_L_sholder = glm::translate(model_L_sholder,glm::vec3(-1.75,0.0,-4.0));
        model_L_sholder = glm::rotate(model_L_sholder,glm::radians(90.0f),glm::vec3(0.0,1.0,0.0));

        matrices.push_back(model_R_sholder);
        matrices.push_back(model_L_sholder);


        //sphere,cylinder and cuboid for the right arm
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.5f,36,8,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<Sphere>(0.15f,16,8,"../texture/cinza.jpg"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.5f,36,8,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.3f,0.3f,0.1f,4,1,"../texture/amarelo.png"));

        glm::mat4 model_R_arm = glm::mat4(1.0);
        model_R_arm = glm::translate(model_R_arm,glm::vec3(2.25,0.0,-4.0));
        model_R_arm = glm::rotate(model_R_arm,glm::radians(-90.0f),glm::vec3(0.0,1.0,0.0));

        glm::mat4 model_R_elbow = glm::mat4(1.0);
        model_R_elbow = glm::translate(model_R_elbow,glm::vec3(2.58,0.0,-4.0));

        glm::mat4 model_R_forearm = glm::mat4(1.0);
        model_R_forearm = glm::translate(model_R_forearm,glm::vec3(2.91,0.0,-4.0));
        model_R_forearm = glm::rotate(model_R_forearm,glm::radians(-90.0f),glm::vec3(0.0,1.0,0.0));

        glm::mat4 model_R_hand = glm::mat4(1.0);
        model_R_hand = glm::translate(model_R_hand,glm::vec3(3.37,0.0,-4.0));
        model_R_hand = glm::rotate(model_R_hand,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));

        matrices.push_back(model_R_arm);
        matrices.push_back(model_R_elbow);
        size_t index_R_forearm = matrices.size();
        matrices.push_back(model_R_forearm);
        size_t index_R_hand = matrices.size();
        matrices.push_back(model_R_hand);

        //sphere,cylinder and cuboid for the left arm 
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.5f,36,8,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<Sphere>(0.15f,16,8,"../texture/cinza.jpg"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.5f,36,8,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.3f,0.3f,0.1f,4,1,"../texture/amarelo.png"));

        glm::mat4 model_L_arm = glm::mat4(1.0);
        model_L_arm = glm::translate(model_L_arm,glm::vec3(-2.25,0.0,-4.0));
        model_L_arm = glm::rotate(model_L_arm,glm::radians(-90.0f),glm::vec3(0.0,1.0,0.0));

        glm::mat4 model_L_elbow = glm::mat4(1.0);
        model_L_elbow = glm::translate(model_L_elbow,glm::vec3(-2.58,0.0,-4.0));

        glm::mat4 model_L_forearm = glm::mat4(1.0);
        model_L_forearm = glm::translate(model_L_forearm,glm::vec3(-2.91,0.0,-4.0));
        model_L_forearm = glm::rotate(model_L_forearm,glm::radians(-90.0f),glm::vec3(0.0,1.0,0.0));

        glm::mat4 model_L_hand = glm::mat4(1.0);
        model_L_hand = glm::translate(model_L_hand,glm::vec3(-3.37,0.0,-4.0));
        model_L_hand = glm::rotate(model_L_hand,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));

        matrices.push_back(model_L_arm);
        matrices.push_back(model_L_elbow);
        size_t index_L_forearm = matrices.size();
        matrices.push_back(model_L_forearm);
        size_t index_L_hand = matrices.size();
        matrices.push_back(model_L_hand);


        //sphere,cylinder and cuboid for the right leg
        Shapes.push_back(std::make_unique<Sphere>(0.25f,16,8,"../texture/cinza.jpg"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.5f,36,8,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<Sphere>(0.2f,16,8,"../texture/cinza.jpg"));        
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.42f,36,8,"../texture/sponge_bob/bob_leg.png"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.2f,0.2f,0.1f,4,1,"../texture/preto.png"));

        glm::mat4 model_R_leg_ligament = glm::mat4(1.0);
        model_R_leg_ligament = glm::translate(model_R_leg_ligament,glm::vec3(0.75,-2.3,-4.0));
        
        glm::mat4 model_R_thigh = glm::mat4(1.0);
        model_R_thigh = glm::translate(model_R_thigh,glm::vec3(0.75,-2.79,-4.0));
        model_R_thigh = glm::rotate(model_R_thigh,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));
        
        glm::mat4 model_R_knee = glm::mat4(1.0);
        model_R_knee = glm::translate(model_R_knee,glm::vec3(0.75,-3.24,-4.0));

        glm::mat4 model_R_calf = glm::mat4(1.0);
        model_R_calf = glm::translate(model_R_calf,glm::vec3(0.75,-3.65,-4.0));
        model_R_calf = glm::rotate(model_R_calf,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));

        glm::mat4 model_R_foot = glm::mat4(1.0);
        model_R_foot = glm::translate(model_R_foot,glm::vec3(0.75,-3.96,-3.8));
        model_R_foot = glm::scale(model_R_foot,glm::vec3(-2.0f,-2.0f,3.5f));
        model_R_foot = glm::rotate(model_R_foot,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));
        model_R_foot = glm::rotate(model_R_foot,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));


        matrices.push_back(model_R_leg_ligament);
        matrices.push_back(model_R_thigh);
        matrices.push_back(model_R_knee);
        matrices.push_back(model_R_calf);
        matrices.push_back(model_R_foot);


        //sphere,cylinder and cuboid for the left leg
        Shapes.push_back(std::make_unique<Sphere>(0.25f,16,8,"../texture/cinza.jpg"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.5f,36,8,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<Sphere>(0.2f,16,8,"../texture/cinza.jpg"));        
        Shapes.push_back(std::make_unique<AxialExtruder>(0.1f,0.1f,0.42f,36,8,"../texture/sponge_bob/bob_leg.png"));
        Shapes.push_back(std::make_unique<AxialExtruder>(0.2f,0.2f,0.1f,4,1,"../texture/preto.png"));

        glm::mat4 model_L_leg_ligament = glm::mat4(1.0);
        model_L_leg_ligament = glm::translate(model_L_leg_ligament,glm::vec3(-0.75,-2.3,-4.0));
        
        glm::mat4 model_L_thigh = glm::mat4(1.0);
        model_L_thigh = glm::translate(model_L_thigh,glm::vec3(-0.75,-2.79,-4.0));
        model_L_thigh = glm::rotate(model_L_thigh,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));
        
        glm::mat4 model_L_knee = glm::mat4(1.0);
        model_L_knee = glm::translate(model_L_knee,glm::vec3(-0.75,-3.24,-4.0));

        glm::mat4 model_L_calf = glm::mat4(1.0);
        model_L_calf = glm::translate(model_L_calf,glm::vec3(-0.75,-3.65,-4.0));
        model_L_calf = glm::rotate(model_L_calf,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));

        glm::mat4 model_L_foot = glm::mat4(1.0);
        model_L_foot = glm::translate(model_L_foot,glm::vec3(-0.75,-3.96,-3.8));
        model_L_foot = glm::scale(model_L_foot,glm::vec3(-2.0f,-2.0f,3.5f));
        model_L_foot = glm::rotate(model_L_foot,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));
        model_L_foot = glm::rotate(model_L_foot,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));


        matrices.push_back(model_L_leg_ligament);
        matrices.push_back(model_L_thigh);
        matrices.push_back(model_L_knee);
        matrices.push_back(model_L_calf);
        matrices.push_back(model_L_foot);


        //sphere,paraboloid for the face
        Shapes.push_back(std::make_unique<Sphere>(0.7f,36,18,"../texture/white.jpg"));
        Shapes.push_back(std::make_unique<Sphere>(0.7f,36,18,"../texture/white.jpg"));
        Shapes.push_back(std::make_unique<Paraboloid>(false,false,-0.6f,0.75,36,18,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<Paraboloid>(false,false,-0.6f,0.75,36,18,"../texture/amarelo.png"));
        Shapes.push_back(std::make_unique<Sphere>(0.25,36,18,"../texture/amarelo.png"));

        std::vector<float> p = Line::generateParabolaPoints(0.5f, 0.0f, -0.9f, -1.3f, 1.3f, 30);

        std::vector<glm::vec3> parabolaPoints;
        parabolaPoints.reserve(p.size() / 3);

        for (size_t i = 0; i < p.size(); i += 3) {
            parabolaPoints.emplace_back(p[i], p[i+1], p[i+2]);
        }
        Shapes.push_back(std::make_unique<Pipe>(parabolaPoints,0.2f,0.2f,2,"../texture/preto.png"));
      
        glm::mat4 model_R_eye = glm::mat4(1.0f);
        model_R_eye = glm::translate(model_R_eye,glm::vec3(0.75,0.7,-3.8));
        model_R_eye = glm::scale(model_R_eye,glm::vec3(1.0,1.1,1.0));

        glm::mat4 model_L_eye = glm::mat4(1.0f);
        model_L_eye = glm::translate(model_L_eye,glm::vec3(-0.75,0.7,-3.8));
        model_L_eye = glm::scale(model_L_eye,glm::vec3(1.0,1.1,1.0));

        glm::mat4 model_R_eyelid = glm::mat4(1.0f);
        model_R_eyelid = glm::translate(model_R_eyelid,glm::vec3(0.75,1.55,-3.75));

        glm::mat4 model_L_eyelid = glm::mat4(1.0f);
        model_L_eyelid = glm::translate(model_L_eyelid,glm::vec3(-0.75,1.55,-3.75));

        glm::mat4 model_noise = glm::mat4(1.0f);
        model_noise = glm::translate(model_noise,glm::vec3(0.0,0.2,-3.5));
        model_noise = glm::rotate(model_noise,glm::radians(-5.0f),glm::vec3(1.0,0.0,0.0));
        model_noise = glm::scale(model_noise,glm::vec3(1.0,1.0,4.0));

        glm::mat4 model_mouth = glm::mat4(1.0f);
        model_mouth = glm::translate(model_mouth,glm::vec3(0.0,0.0,-3.49));

        matrices.push_back(model_R_eye);
        matrices.push_back(model_L_eye);
        matrices.push_back(model_R_eyelid);
        matrices.push_back(model_L_eyelid);
        matrices.push_back(model_noise);
        matrices.push_back(model_mouth);       

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {   
            float currentFrame = static_cast<float>(glfwGetTime());
            processInputCamera(window,currentFrame - Globals::lastFrame);
            Globals::lastFrame = currentFrame;
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            float aspectRatio = static_cast<float>(Globals::windowWidth) / static_cast<float>(Globals::windowHeight);
            glm::mat4 projection = glm::perspective(glm::radians(Globals::camera.Zoom), aspectRatio, 0.1f, 100.0f);
            glm::mat4 view = Globals::camera.GetViewMatrix();

            processArmInput(window,matrices,index_R_forearm,index_R_hand,index_L_forearm,index_L_hand);
            
            for (size_t i = 0; i < Shapes.size(); i++)
            {
                Shapes[i]->getShader().useShaders();
                Shapes[i]->getShader().setMat4("model", matrices[i]);
                Shapes[i]->getShader().setMat4("projection",projection);
                Shapes[i]->getShader().setMat4("view", view);

                Shapes[i]->getTexture().Bind();

                Shapes[i]->desenhar();

                Shapes[i]->getTexture().Unbind();
            }

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}