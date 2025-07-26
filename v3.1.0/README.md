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

## Créditos

- Parte do código de geração de esfera e cilindro foi baseada no trabalho de **Song Ho Ahn**:
- [OpenGL Sphere Tessellation](https://www.songho.ca/opengl/gl_sphere.html)
- [OpenGL Cylinder, Prism & Pipe](https://www.songho.ca/opengl/gl_cylinder.html#cylinder)
