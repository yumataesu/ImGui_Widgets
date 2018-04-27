//
//  ColorPicker.h
//  drag_and_drop
//
//  Created by Yuma Taesu on 2018/04/26.
//
//

#include "imgui.h"

#ifndef ColorPicker_h
#define ColorPicker_h

static void ShowHelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(450.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


namespace ttt {
    class ColorPicker {
        
    private:
        bool alpha = true;
        bool alpha_bar = true;
        bool side_preview = false;
        bool ref_color = false;
        ImVec4 ref_color_v = ImVec4(1.0f, 0.0f, 1.0f, 0.5f);
        int inputs_mode = 2;
        int picker_mode = 0;
        ImVec4 color = ImColor(114, 144, 154, 255);
        
    public:
        void drawGui(const std::string& title) {
            //ImGui::Begin(title.c_str());
            int misc_flags = (ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaPreview);
            
            // Generate a dummy palette
            static bool saved_palette_inited = false;
            static ImVec4 saved_palette[32];
            if (!saved_palette_inited)
                for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++) {
                    ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f, saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
                    saved_palette[n].w = 1.0f; // Alpha
                }
            saved_palette_inited = true;
            
            
            static ImVec4 backup_color;
            bool open_popup = ImGui::ColorButton(title.c_str(), color, misc_flags);
            ImGui::SameLine();
            if (open_popup) {
                ImGui::OpenPopup(title.c_str());
                backup_color = color;
            }
            if (ImGui::BeginPopup(title.c_str())) {
                // FIXME: Adding a drag and drop example here would be perfect!
                //ImGui::Text("MY CUSTOM COLOR PICKER WITH AN AMAZING PALETTE!");
                ImGui::Separator();
                
                //ImGui::ColorPicker4("##picker", (float*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
                ImGui::Combo("##v", &inputs_mode, "All Inputs\0No Inputs\0RGB Input\0HSV Input\0HEX Input\0");
                ImGui::Combo("###v", &picker_mode, "Auto/Current\0Hue bar + SV rect\0Hue wheel + SV triangle\0");
                ImGui::SameLine(); ShowHelpMarker("User can right-click the picker to change mode.");
                ImGuiColorEditFlags flags = misc_flags;
                if (!alpha) flags |= ImGuiColorEditFlags_NoAlpha; // This is by default if you call ColorPicker3() instead of ColorPicker4()
                if (alpha_bar) flags |= ImGuiColorEditFlags_AlphaBar;
                if (!side_preview) flags |= ImGuiColorEditFlags_NoSidePreview;
                if (picker_mode == 1) flags |= ImGuiColorEditFlags_PickerHueBar;
                if (picker_mode == 2) flags |= ImGuiColorEditFlags_PickerHueWheel;
                if (inputs_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;
                if (inputs_mode == 2) flags |= ImGuiColorEditFlags_RGB;
                if (inputs_mode == 3) flags |= ImGuiColorEditFlags_HSV;
                if (inputs_mode == 4) flags |= ImGuiColorEditFlags_HEX;
                ImGui::ColorPicker4("##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);
                
                ImGui::SameLine();
                ImGui::BeginGroup();
                
                ImGui::Text("Current");
                ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60,40));
                
                ImGui::Text("Previous");
                if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60,40))) {
                    color = backup_color;
                }
                ImGui::Separator();
                ImGui::Text("Palette");
                for (int n = 0; n < IM_ARRAYSIZE(saved_palette); ++n) {
                    ImGui::PushID(n);
                    if ((n % 8) != 0)
                        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);
                    if (ImGui::ColorButton("##palette", saved_palette[n], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, ImVec2(20,20)))
                        color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!
                    
                    if (ImGui::BeginDragDropTarget()) {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F)) {
                            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
                        }
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F)) {
                            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
                        }
                        ImGui::EndDragDropTarget();
                    }
                    
                    ImGui::PopID();
                }
                ImGui::EndGroup();
                ImGui::EndPopup();
            }
            
            //ImGui::End();
        }
    };
}



#endif /* ColorPicker_h */
