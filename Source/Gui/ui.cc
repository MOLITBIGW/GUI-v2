#include "ui.hh"
#include "globals.hh"
#include "../imgui/imgui.h"
#include "../Modules/GUI.hh"
#include <Windows.h>

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;

    if (window_pos.x == 0 && window_pos.y == 0) {
        RECT desktop_rect{};
        GetWindowRect(GetDesktopWindow(), &desktop_rect);
        screen_res = ImVec2(float(desktop_rect.right), float(desktop_rect.bottom));
        window_pos = ImVec2(
            (screen_res.x - window_size.x) * 0.5f,
            (screen_res.y - window_size.y) * 0.5f
        );
    }

    gui::init(); 
}

void ui::render() {
    if (!globals::active) return;

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(0.95f);
    ImGui::Begin(window_title, &globals::active, window_flags);
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font_bold = io.Fonts->Fonts[0];
    float scale = 1.8f;
    ImGui::PushFont(io.Fonts->Fonts[0]);
    float window_width = ImGui::GetWindowSize().x;
    ImVec2 text_size = ImGui::CalcTextSize(window_title);
    ImGui::SetCursorPosX((window_width - text_size.x * scale) * 0.5f);
    ImGui::SetWindowFontScale(scale);
    ImGui::Text("%s", window_title);
    ImGui::SetWindowFontScale(1.8f);

    ImGui::PopFont();

    ImGui::Separator();

    static int current_tab = 0;
    static float content_alpha = 1.0f;
    static bool animating = false;

    const char* tab_names[] = { "Combat", "Visual", "Misc" };

    ImGui::BeginChild("Sidebar", ImVec2(160, 0), true);
    for (int i = 0; i < IM_ARRAYSIZE(tab_names); i++) {
        if (ImGui::Selectable(tab_names[i], current_tab == i)) {
            if (current_tab != i) {
                current_tab = i;
                animating = true;
                content_alpha = 0.0f;
            }
        }
    }
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("MainContent", ImVec2(0, 0), true);

    if (animating) {
        content_alpha += ImGui::GetIO().DeltaTime * 4.0f;
        if (content_alpha >= 1.0f) {
            content_alpha = 1.0f;
            animating = false;
        }
    }

    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, content_alpha);

    switch (current_tab) {
    case 0:
      // COMBAT
        break;
    case 1:
      // VISUAL
        gui::renderSettings();
        break;
    case 2:
      // MISC
        break;
    }

    ImGui::PopStyleVar();

    ImGui::EndChild();

    ImGui::End();

    if (!globals::active) {
        PostQuitMessage(0);
    }
}
