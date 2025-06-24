#ifndef ESPONGEBOB_HPP
#define ESPONGEBOB_HPP

#include "Shapes.hpp"
#include "Shape.hpp"
#include "Paths.hpp"
#include "../dep/glm/glm.hpp"
#include "../dep/glm/gtc/matrix_transform.hpp"
#include "../dep/glm/gtc/type_ptr.hpp"
#include "../dep/glfw/include/GLFW/glfw3.h"
#include <memory>
#include <vector>

class SpongeBob
{
private:
    std::vector<std::unique_ptr<Shape>> Shapes;
    std::vector<glm::mat4> matrices;
    
    size_t index_R_forearm;
    size_t index_R_hand;
    size_t index_L_forearm;
    size_t index_L_hand;

private:
    void buildBody();
    void buildShoulders();
    void buildRightArm();
    void buildLeftArm();
    void buildRightLeg();
    void buildLeftLeg();
    void buildFace();
    void buildEyes();
    void buildEyelashes();

public:
    SpongeBob();
    void processArmInput(GLFWwindow* window);
    void drawSpongeBob(const glm::mat4& projection, const glm::mat4& view);
};
#endif