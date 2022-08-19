#include <event.h>
#include <GLFW/glfw3.h>
extern GLFWwindow* window;
void main_loop(void)
{
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}
