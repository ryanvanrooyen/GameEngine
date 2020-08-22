
#include "Renderer.hpp"
#include "../logging.h"
#include "opengl.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


Renderer::Renderer(GLFWwindow* window) : window(window) {}


void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}


void Renderer::SwapBuffers()
{
    glfwSwapBuffers(window);
}


void Renderer::BeginGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


void Renderer::EndGUI()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
