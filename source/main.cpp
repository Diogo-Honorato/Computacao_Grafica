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

    {        
        Home home;

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // Limpa tela
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            home.drawHome();

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
    }


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}