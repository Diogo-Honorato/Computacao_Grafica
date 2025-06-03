#include"../include/main.hpp"

/*

*Press key:
    'esc' activates: Close window.
    'w'   activates: glPolygonMode FILL.
    'e'   activates: glPolygonMode LINE.
    'r'   activates: glPolygonMode POINT.

*/

int main()
{
    // Cria janela
    GLFWwindow *window = startWindow(WIN_WIDTH, WIN_HEIGHT, "Casa_V2");
    if (initializeOpenGL(window) == -1){
        return -1;
    }

    std::vector<std::unique_ptr<Shape>> Shapes;
    std::vector<glm::mat4> matrices;

    //triangle
    Shapes.push_back(std::make_unique<Triangle>(
        "../shader/shaders_casa/vertex/vertex_triangle.vs",
        "../shader/basic_shaders/fragment/basic_triangle.fs"
    ));

    glm::mat4 trans_triangle = glm::mat4(1.0f);
    trans_triangle = glm::translate(trans_triangle,glm::vec3(-0.3f,0.167f,0.0f));
    trans_triangle = glm::scale(trans_triangle,glm::vec3(0.65f,0.65f,0.0));
    
    matrices.push_back(trans_triangle);
    //////////////////////////////////////////////////////////////////

    //square wall left
    Shapes.push_back(std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/basic_shaders/fragment/basic_square.fs"
    ));

    glm::mat4 trans_wall_left = glm::mat4(1.0f);
    trans_wall_left = glm::translate(trans_wall_left,glm::vec3(-0.3f,-0.5f,0.0f));
    trans_wall_left = glm::scale(trans_wall_left,glm::vec3(0.65f,0.65f,0.0));

    matrices.push_back(trans_wall_left);

    //////////////////////////////////////////////////////////////////

    //square wall right
    Shapes.push_back(std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/basic_shaders/fragment/basic_square.fs"
    ));

    glm::mat4 trans_wall_right = glm::mat4(1.0f);
    trans_wall_right = glm::translate(trans_wall_right,glm::vec3(0.337f,-0.4f,0.0f));
    trans_wall_right = glm::scale(trans_wall_right,glm::vec3(0.705f,0.755f,0.0));
    trans_wall_right = glm::rotate(trans_wall_right,glm::radians(31.0f),glm::vec3(1.0f,0.0f,0.0f));
    trans_wall_right = glm::rotate(trans_wall_right,glm::radians(31.0f),glm::vec3(0.0f,1.0f,0.0f));

    matrices.push_back(trans_wall_right);
    //////////////////////////////////////////////////////////////////

    //square roof
    Shapes.push_back(std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/shaders_casa/fragment/fragment_roof.fs"
    ));

    glm::mat4 trans_roof = glm::mat4(1.0f);
    trans_roof = glm::translate(trans_roof,glm::vec3(0.337f,0.0f,0.0f));
    trans_roof = glm::scale(trans_roof,glm::vec3(0.705f,0.755f,0.0));
    trans_roof = glm::rotate(trans_roof,glm::radians(131.0f),glm::vec3(0.0f,1.0f,0.0f));
    trans_roof = glm::rotate(trans_roof,glm::radians(131.0f),glm::vec3(1.0f,0.0f,0.0f));

    matrices.push_back(trans_roof);
    //////////////////////////////////////////////////////////////////
    
    //circle
    Shapes.push_back(std::make_unique<Circle>(
        "../shader/shaders_casa/vertex/vertex_circle.vs",
        "../shader/basic_shaders/fragment/basic_circle.fs"
    ));
    
    glm::mat4 trans_circle = glm::mat4(1.0f);
    trans_circle = glm::translate(trans_circle,glm::vec3(-0.3f,0.045f,0.0));
    trans_circle = glm::scale(trans_circle,glm::vec3(0.382f,0.382f,0.0));

    matrices.push_back(trans_circle);
    //////////////////////////////////////////////////////////////////


    // Loop principal de renderização
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Limpa tela
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenha Shapes
        for (size_t i = 0; i < Shapes.size(); i++)
        {
            Shapes[i]->getShader().useShaders();

            Shapes[i]->getShader().setMat4("transform",matrices[i]);
            
            Shapes[i]->desenhar();
        }

        // Troca buffers e trata eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Shapes.clear();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}