# Computacao_Grafica
Repositório destinado para códigos de computação gráfica. 

## <h2 id="Requisitos">Requisitos</h2>

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
Para executar modificações feitas no código será preciso [compila-lo]("Requisitos") novamente.

## Dependências
Dependências já inclusas. Código testado em Linux.

## Projetos Prontos

### casa_v2

Projeto que renderiza uma casa no centro da tela. Basta adicionar a biblioteca **"../include/Home.hpp"** instânciar um objeto **Home** na main(), no  Loop principal de renderização chamar a função **drawHome()** do objeto Home.

Exemplo.:

```bash
#include "../include/Home.hpp"

int main()
{
    ...código anterior criando janela

    {
        Home home;

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
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
