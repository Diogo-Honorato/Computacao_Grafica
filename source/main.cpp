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
    trans_triangle = glm::translate(trans_triangle,glm::vec3(-0.5f,0.0f,0.0));
    
    matrices.push_back(trans_triangle);
    //////////////////////////////////////////////////////////////////

    //square
    Shapes.push_back(std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/basic_shaders/fragment/basic_square.fs"
    ));

    glm::mat4 trans_square = glm::mat4(1.0f);
    trans_square = glm::translate(trans_square,glm::vec3(-0.5f,-0.5f,0.0));

    matrices.push_back(trans_square);
    //////////////////////////////////////////////////////////////////


    // Loop principal de renderização
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Limpa tela
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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