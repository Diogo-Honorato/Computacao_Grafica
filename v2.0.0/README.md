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

Definir ```false``` no segundo argumento da função ```initializeOpenGL()```, instânciar um objeto **Home** na main(), no  Loop principal de renderização chamar a função **drawHome()** do objeto Home.

deve se parecer com isso:

```bash
#include "../include/main.hpp"

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
### Bob esponja
Projeto que renderiza um modelo 3D do Bob Esponja no centro da tela.
instânciar um objeto **SpongeBob** na main(), no  Loop principal de renderização chamar a função **processArmInput(window);** para fazer a animação do modelo e **drawSpongeBob(projection,view);** para desenhar o modelo.

deve se parecer com isso:
```bash
int main()
{
    // Cria janela
    GLFWwindow *window = startWindowCamera(WIN_WIDTH, WIN_HEIGHT, "Engine");
    if (initializeOpenGL(window, true) == -1)
    {
        return -1;
    }

    {

        SpongeBob SB;

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {   
            float currentFrame = static_cast<float>(glfwGetTime());
            processInputCamera(window,currentFrame - Globals::lastFrame);
            Globals::lastFrame = currentFrame;
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            float aspectRatio = static_cast<float>(Globals::windowWidth) / static_cast<float>(Globals::windowHeight);
            glm::mat4 projection = glm::perspective(glm::radians(Globals::camera.Zoom), aspectRatio, 0.1f, 100.0f);
            glm::mat4 view = Globals::camera.GetViewMatrix();


            SB.processArmInput(window);
            SB.drawSpongeBob(projection,view);

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

-Para fazer a animação pressione a tecla '2'.

-Para voltar a posição original pressione a tecla '1'.

## Créditos

- Parte do código de geração de esfera e cilindro foi baseada no trabalho de **Song Ho Ahn**:
- [OpenGL Sphere Tessellation](https://www.songho.ca/opengl/gl_sphere.html)
- [OpenGL Cylinder, Prism & Pipe](https://www.songho.ca/opengl/gl_cylinder.html#cylinder)
