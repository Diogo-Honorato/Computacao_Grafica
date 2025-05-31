#include <iostream>
#include <vector>
#include <memory>
#include "../include/Window.hpp"
#include "../include/Shader.hpp"
#include "../include/Shape.hpp"
#include "../include/Triangle.hpp"
#include "../include/Square.hpp"
#include "../include/Circle.hpp"

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