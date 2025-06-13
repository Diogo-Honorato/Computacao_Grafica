# Computacao_Grafica
Repositório destinado para códigos de computação gráfica. 

## Requisitos

- Linux
- C++23 compatível
- CMake ≥ 3.0.0
- Make
- OpenGL 3.3 Core Profile

## Como compilar

```bash
mkdir build
cd build
cmake ..
make
```

## Como executar

```bash
./engine
```

## Edição
Para executar modificações feitas no código será preciso [compila-lo](https://github.com/Diogo-Honorato/Computacao_Grafica?tab=readme-ov-file#como-compilar) novamente para assim poder apenas usar os comandos ```make && ./engine```.

## Dependências
Dependências já inclusas. Código testado em Linux.

## Projetos Prontos

### casa_v2

Projeto que renderiza uma casa no centro da tela. 

Definir ```false``` no segundo argumento da função ```initializeOpenGL()```, adicionar a biblioteca **"../include/Home.hpp"** instânciar um objeto **Home** na main(), no  Loop principal de renderização chamar a função **drawHome()** do objeto Home.

deve se parecer com isso:

```bash
#include "../include/Home.hpp"

int main()
{
    GLFWwindow *window = startWindow(WIN_WIDTH, WIN_HEIGHT, "Engine");
    if (initializeOpenGL(window, false) == -1)
    {
        return -1;
    }

    {
        Home home;

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            home.drawHome();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

```
## Créditos

- Parte do código de geração de esfera foi baseada no trabalho de **Song Ho Ahn**:
  - [OpenGL Sphere Tessellation](https://www.songho.ca/opengl/gl_sphere.html)
