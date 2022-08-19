#include <window.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
pixel* main_screen;
GLFWwindow* window;
void create_window(uint32_t width, uint32_t height)
{
    //We DO NOT use OpenGL.
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(width, height, "Emulated Window", NULL, NULL);
}
void destroy_window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
