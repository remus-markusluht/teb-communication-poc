#include "draw.h"

void MainThread(ImDrawList* drawList) {

}

void DrawOverlay() {
    ImGui::Begin(xorstr_("renderer"), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN))); // W , H
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    /* Overlay */
    MainThread(drawList);

    ImGui::End();
}

void MenuThread() {
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        client->MenuOpen = !client->MenuOpen;
    }

    if (client->MenuOpen) {
        if (ImGui::Begin(xorstr_("XIMAMenu"), nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImDrawList* drawList = ImGui::GetWindowDrawList();
            ImGui::SetWindowPos(ImVec2(15.0f, 45.0f), ImGuiCond_Always);

            /* ASSETS */
        }
    }
}

void drawLoop() {
	ImGuiIO& io = ImGui::GetIO();

    DrawOverlay();

	MenuThread();
}