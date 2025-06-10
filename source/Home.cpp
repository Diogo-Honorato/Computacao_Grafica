#include "../include/Home.hpp"

Home::Home()
{
    Shapes.resize(8);
    matrices.resize(8);
    
    buildWalls(matrices[0],matrices[1],Shapes[0],Shapes[1]);
    buildDoor(matrices[2],Shapes[2]);
    buildWindows(matrices[3],matrices[4],Shapes[3],Shapes[4]);
    buildTriangle(matrices[5],Shapes[5]);
    buildCircle(matrices[6],Shapes[6]);
    buildRoof(matrices[7],Shapes[7]);
}

void Home::buildWalls(glm::mat4 &mr,glm::mat4 &ml,std::unique_ptr<Shape> &ShapeR,std::unique_ptr<Shape> &ShapeL)
{

    // square wall left
    ShapeL = std::make_unique<Square>("../shader/shaders_casa/vertex/vertex_square.vs",
                    "../shader/basic_shaders/fragment/basic_square.fs");
    glm::mat4 trans_wall_left = glm::mat4(1.0f);
    trans_wall_left = glm::translate(trans_wall_left, glm::vec3(-0.3f, -0.5f, 0.0f));
    trans_wall_left = glm::scale(trans_wall_left, glm::vec3(0.65f, 0.65f, 0.0));

    ml = trans_wall_left;

    // square wall right
    ShapeR = std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/basic_shaders/fragment/basic_square.fs");

    glm::mat4 trans_wall_right = glm::mat4(1.0f);
    trans_wall_right = glm::translate(trans_wall_right, glm::vec3(0.337f, -0.4f, 0.0f));
    trans_wall_right = glm::scale(trans_wall_right, glm::vec3(0.705f, 0.755f, 0.0));
    trans_wall_right = glm::rotate(trans_wall_right, glm::radians(31.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    trans_wall_right = glm::rotate(trans_wall_right, glm::radians(31.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    mr = trans_wall_right;
}

void Home::buildDoor(glm::mat4 &m,std::unique_ptr<Shape> &Shape){

    // square door
    Shape = std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/shaders_casa/fragment/fragment_door.fs");

    glm::mat4 trans_door = glm::mat4(1.0f);
    trans_door = glm::translate(trans_door, glm::vec3(-0.3f, -0.6f, 0.0f));
    trans_door = glm::scale(trans_door, glm::vec3(0.25f, 0.45f, 0.0));

    m = trans_door;
}

void Home::buildWindows(glm::mat4 &mr,glm::mat4 &ml,std::unique_ptr<Shape> &ShapeR,std::unique_ptr<Shape> &ShapeL)
{
    // square window left
    ShapeL = std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/shaders_casa/fragment/fragment_window.fs");

    glm::mat4 trans_window_left = glm::mat4(1.0f);
    trans_window_left = glm::translate(trans_window_left, glm::vec3(0.2f, -0.4f, 0.0f));
    trans_window_left = glm::scale(trans_window_left, glm::vec3(0.205f, 0.255f, 0.0));
    trans_window_left = glm::rotate(trans_window_left, glm::radians(31.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    trans_window_left = glm::rotate(trans_window_left, glm::radians(31.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ml = trans_window_left;

    // square window right
    ShapeR = std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/shaders_casa/fragment/fragment_window.fs");

    glm::mat4 trans_window_right = glm::mat4(1.0f);
    trans_window_right = glm::translate(trans_window_right, glm::vec3(0.5f, -0.3f, 0.0f));
    trans_window_right = glm::scale(trans_window_right, glm::vec3(0.203f, 0.253f, 0.0));
    trans_window_right = glm::rotate(trans_window_right, glm::radians(31.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    trans_window_right = glm::rotate(trans_window_right, glm::radians(31.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    mr = trans_window_right;
}

void Home::buildRoof(glm::mat4 &m,std::unique_ptr<Shape> &Shape)
{

    // square roof
    Shape = std::make_unique<Square>(
        "../shader/shaders_casa/vertex/vertex_square.vs",
        "../shader/shaders_casa/fragment/fragment_roof.fs");

    glm::mat4 trans_roof = glm::mat4(1.0f);
    trans_roof = glm::translate(trans_roof, glm::vec3(0.172f, 0.269f, 0.0f));
    trans_roof = glm::scale(trans_roof, glm::vec3(0.69f, 0.96f, 0.0));

    trans_roof = glm::rotate(trans_roof, glm::radians(220.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    trans_roof = glm::rotate(trans_roof, glm::radians(227.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    trans_roof = glm::rotate(trans_roof, glm::radians(16.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    m = trans_roof;
}

void Home::buildTriangle(glm::mat4 &m,std::unique_ptr<Shape> &Shape)
{

    // triangle
    Shape = std::make_unique<Triangle>(
        "../shader/shaders_casa/vertex/vertex_triangle.vs",
        "../shader/basic_shaders/fragment/basic_triangle.fs");

    glm::mat4 trans_triangle = glm::mat4(1.0f);
    trans_triangle = glm::translate(trans_triangle, glm::vec3(-0.3f, 0.167f, 0.0f));
    trans_triangle = glm::scale(trans_triangle, glm::vec3(0.65f, 0.65f, 0.0));

    m = trans_triangle;
}

void Home::buildCircle(glm::mat4 &m,std::unique_ptr<Shape> &Shape)
{

    // circle
    Shape = std::make_unique<Circle>(
        "../shader/shaders_casa/vertex/vertex_circle.vs",
        "../shader/basic_shaders/fragment/basic_circle.fs");

    glm::mat4 trans_circle = glm::mat4(1.0f);
    trans_circle = glm::translate(trans_circle, glm::vec3(-0.3f, 0.045f, 0.0));
    trans_circle = glm::scale(trans_circle, glm::vec3(0.282f, 0.282f, 0.0));

    m = trans_circle;
}

void Home::drawHome()
{

    // Desenha Shapes
    for (size_t i = 0; i < Shapes.size(); i++)
    {
        Shapes[i]->getShader().useShaders();

        Shapes[i]->getShader().setMat4("transform", matrices[i]);

        Shapes[i]->desenhar();
    }
}