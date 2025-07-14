#include "GUI.hh"
#include "../imgui/imgui.h"

namespace gui {

    static int themeIndex = 0;
    static ImVec4 windowBgColor = ImVec4(0.1f, 0.105f, 0.11f, 1.0f);
    static float frameRounding = 8.0f;
    static float scrollbarSize = 12.0f;
    static ImVec2 windowPadding = ImVec2(15, 15);
    static float fontScale = 1.0f;

    static void applyTheme(int idx) {
        ImGuiStyle& style = ImGui::GetStyle();

        switch (idx) {
        case 0:
            ImGui::StyleColorsDark();
            style.WindowPadding = windowPadding;
            style.FramePadding = ImVec2(10, 6);
            style.ItemSpacing = ImVec2(12, 8);
            style.ScrollbarSize = scrollbarSize;
            style.WindowRounding = 12.0f;
            style.ChildRounding = 10.0f;
            style.FrameRounding = frameRounding;
            style.PopupRounding = 10.0f;
            style.GrabRounding = 6.0f;
            style.TabRounding = 8.0f;
            style.WindowBorderSize = 1.0f;
            style.FrameBorderSize = 1.0f;

            style.Colors[ImGuiCol_WindowBg] = windowBgColor;
            style.Colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.30f, 0.60f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.25f, 1.00f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.34f, 0.38f, 1.00f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.28f, 0.32f, 1.00f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
            style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.28f, 0.35f, 1.00f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.23f, 0.29f, 1.00f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.25f, 0.28f, 0.35f, 1.00f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.23f, 0.29f, 1.00f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.35f, 0.42f, 1.00f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.23f, 0.27f, 0.34f, 1.00f);
            break;

        case 1:
            ImGui::StyleColorsDark();
            {
                ImVec4* colors = style.Colors;
                colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.15f, 0.3f, 1.0f);
                colors[ImGuiCol_Header] = ImVec4(0.2f, 0.35f, 0.6f, 1.0f);
                colors[ImGuiCol_HeaderHovered] = ImVec4(0.3f, 0.45f, 0.7f, 1.0f);
                colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.25f, 0.4f, 1.0f);
            }
            break;

        case 2: ImGui::StyleColorsLight(); break;
        case 3: ImGui::StyleColorsClassic(); break;

        default: ImGui::StyleColorsDark(); break;
        }

        style.WindowPadding = windowPadding;
        style.FrameRounding = frameRounding;
        style.ScrollbarSize = scrollbarSize;
        ImGui::GetIO().FontGlobalScale = fontScale;
        style.Colors[ImGuiCol_WindowBg] = windowBgColor;
    }

    void init() {
        applyTheme(themeIndex);
    }

    void renderSettings() {
        const char* themes[] = { "Normal", "Blue", "Light", "Classic" };

        if (ImGui::Combo("Theme", &themeIndex, themes, IM_ARRAYSIZE(themes))) {
            applyTheme(themeIndex);
        }

        if (ImGui::ColorEdit4("Window Background", (float*)&windowBgColor)) {
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = windowBgColor;
        }

        if (ImGui::SliderFloat("Font Scale", &fontScale, 0.5f, 2.0f, "%.2f")) {
            ImGui::GetIO().FontGlobalScale = fontScale;
        }
        if (ImGui::SliderFloat("Frame Rounding", &frameRounding, 0.0f, 12.0f, "%.1f")) {
            ImGui::GetStyle().FrameRounding = frameRounding;
        }
        if (ImGui::SliderFloat("Scrollbar Size", &scrollbarSize, 6.0f, 24.0f, "%.1f")) {
            ImGui::GetStyle().ScrollbarSize = scrollbarSize;
        }
        if (ImGui::DragFloat2("Window Padding", (float*)&windowPadding, 1.0f, 0.0f, 50.0f, "%.0f")) {
            ImGui::GetStyle().WindowPadding = windowPadding;
        }

        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Padding inside the window borders");
    }
}
