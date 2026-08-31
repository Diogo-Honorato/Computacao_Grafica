#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class ImGuiOverlay
{
public:
    static void Init(GLFWwindow *window);
    static void Begin();
    static void End();
    static void Shutdown();
};