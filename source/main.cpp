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



    Shapes.push_back(std::make_unique<Circle>());
    Shapes.push_back(std::make_unique<Triangle>());



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