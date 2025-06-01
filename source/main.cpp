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
    Shapes.push_back(std::make_unique<Triangle>(
        "../shader/shaders_casa/vertex/vertex_casa.vs",
        "../shader/basic_shaders/fragment/basic_triangle.fs"
    ));

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans,glm::vec3(0.5f,-0.5f,0.0));



    // Loop principal de renderização
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Limpa tela
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenha Shapes
        for (auto &Shape : Shapes)
        {
            Shape->getShader().useShaders();
            Shape->getShader().setMat4("transform",trans);
            Shape->desenhar();
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