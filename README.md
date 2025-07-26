# Engine Gráfica em OpenGL(3.3)

Esta é uma engine gráfica desenvolvida em C++ utilizando OpenGL, voltada para projetos educacionais, testes gráficos e criação de cenas 3D simples com controle de câmera e luz.

Ela possui **duas versões principais**, cada uma com seu foco específico:

## Versões Disponíveis

### Versão 2.0.0 — **Foco em Simplicidade**

A versão 2.0.0 foi projetada para ser mais acessível e fácil de usar. Nela, o foco está na clareza do código, mesmo que isso signifique utilizar mais abstrações e consumir mais recursos.

#### Características:

- Criação de objetos com classes derivadas (`Sphere`, `Cube`, etc).

- Cada objeto pode acabar instanciando seu próprio shader ou malha, mesmo quando são idênticos a outros objetos isso facilita o isolamento de lógica, mas gera redundância.

- Ideal para iniciantes ou quem deseja explorar a engine com menos complexidade interna.

#### Desvantagens:

- **Maior consumo de memória** e recursos, devido ao uso mais intensivo de objetos e cópias.
- Menor controle direto sobre otimizações manuais.

- Malhas idênticas (como esferas ou cubos) podem ser instanciadas repetidamente para cada objeto.

- Shaders também podem ser carregados múltiplas vezes mesmo sendo os mesmos.

Isso aumenta o uso de memória e o número de uploads para GPU, causando maior custo computacional

### Versão 3.0.0 — **Foco em Otimização**

A versão 3.0.0 é mais enxuta e eficiente. Ela foi desenhada para melhor desempenho, com menos abstrações automáticas e maior controle sobre alocação de memória.

#### Características:

- Uso direto de ponteiros crus (`Shader*`, `Mesh*`).

- Reaproveitamento de malhas (`Mesh`) entre diferentes objetos.

- Liberação explícita de dados da CPU com `mesh->clearCPUData()` após envio à GPU.

- Maior eficiência no uso de memória e processamento.

#### Desvantagens:

- Código levemente mais complexo.

- Requer mais atenção do usuário em relação ao gerenciamento de memória.

## Controles Padrão

Em ambas as versões, os controles de navegação e renderização são os mesmos:

| Tecla | Função |
|------|--------|
| `W`, `A`, `S`, `D` | Movimentação da câmera |
| Mouse | Rotação da câmera |
| Scroll | Zoom (campo de visão) |
| `ESC` | Fecha a janela |
| `Q` | Modo de renderização: **Preenchido** (`GL_FILL`) |
| `E` | Modo de renderização: **Wireframe** (`GL_LINE`) |
| `R` | Modo de renderização: **Pontos** (`GL_POINT`) |
