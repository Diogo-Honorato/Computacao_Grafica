#ifndef HOME_HPP
#define HOME_HPP

#include "Shapes.hpp"
#include "Shape.hpp"
#include "../dep/glm/glm.hpp"
#include "../dep/glm/gtc/matrix_transform.hpp"
#include "../dep/glm/gtc/type_ptr.hpp"
#include <memory>
#include <vector>


class Home
{
private:

    std::vector<std::unique_ptr<Shape>> Shapes;
    std::vector<glm::mat4> matrices;

private:

    void buildWalls(glm::mat4 &mr,glm::mat4 &ml,std::unique_ptr<Shape> &ShapeR,std::unique_ptr<Shape> &ShapeL);
    void buildWindows(glm::mat4 &mr,glm::mat4 &ml,std::unique_ptr<Shape> &ShapeR,std::unique_ptr<Shape> &ShapeL);
    void buildRoof(glm::mat4 &m,std::unique_ptr<Shape> &Shape);
    void buildDoor(glm::mat4 &m,std::unique_ptr<Shape> &Shape);
    void buildTriangle(glm::mat4 &m, std::unique_ptr<Shape> &Shape);
    void buildCircle(glm::mat4 &m, std::unique_ptr<Shape> &Shape);

public:
    Home();
    void drawHome();
};







#endif