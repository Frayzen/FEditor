#include "simulation/physics/pysc_sim.hh"
#include "pysc_gui.hh"
#include "gui/imgui_impl_glfw.h"
#include "gui/imgui_impl_opengl3.h"

static bool created = false;
void PyscGUI::update()
{
    PyscSimulation &sim = (PyscSimulation &)sim_;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("FEngine_t");
    if (!created) {
        created = true;
        ImGui::SetWindowFontScale(1.8f);
        ImGui::SetWindowPos(ImVec2(50, 50));
        ImGui::SetWindowSize(ImVec2(600, 500));
    }
    ImGui::SliderFloat("MovementSpeed", (float *)&sim.cam.speed, 0.1f, 100.0f);

    if (ImGui::Button(sim.isRunning ? "Pause" : "Play"))
        sim.isRunning = !sim.isRunning;

    ImGuiIO &io = ImGui::GetIO();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}
