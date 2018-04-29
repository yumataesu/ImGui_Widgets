//
//  DragDrop.cpp
//  drag_and_drop
//
//  Created by Yuma Taesu on 2018/04/29.
//
//

#include "DragDrop.hpp"

namespace ttt {
    
    void DragDrop::loadThumbnails() {
        ofDisableArbTex();
        
        std::size_t size = dir.listDir("thumbnails");
        dir.sort();
        
        thumbnails.resize(size);
        for(std::size_t i = 0; i < size; ++i) {
            ofLoadImage(thumbnails[i], dir.getPath(i));
        }
        
        dests.resize(3);
        for(auto& d : dests) {
            d.allocate(1280, 720, GL_RGBA);
        }
        ofEnableArbTex();
    }

    
    
    void DragDrop::drawGui() {
        auto& style = ImGui::GetStyle();
        
        ImGui::Begin("PREVIEW");
        style.FramePadding = ImVec2(2.f, 2.f);
        style.ItemSpacing  = ImVec2(2.f, 2.f);
        
        int preview_index = 0;
        for(const auto& t : thumbnails) {
            std::string window_title = "PREVIEW" + std::to_string(preview_index);
            ImGui::BeginChild(window_title.data(), ImVec2(90, 55));
            ImGui::ImageButton((ImTextureID)(uintptr_t) t.getTextureData().textureID, ImVec2(80, 45));
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload("_oFScn", &t, sizeof(t), ImGuiCond_Once);
                ImGui::ImageButton((ImTextureID)(uintptr_t) t.getTextureData().textureID, ImVec2(80, 45), ImVec2(0.f, 0.f), ImVec2(1.f, 1.f), 0);
                ImGui::EndDragDropSource();
            }
            ImGui::EndChild(); ImGui::SameLine();
            preview_index++;
        }
        style.FramePadding = ImVec2(2.f, 0.f);
        style.ItemSpacing  = ImVec2(8.f, 4.f);
        ImGui::End();
        
        
        
        int dest_index = 0;
        for(const auto& d : dests) {
            std::string window_title = "DST" + std::to_string(dest_index);
            ImGui::Begin(window_title.data());
            ImGui::ImageButton((ImTextureID)(uintptr_t) d.getTextureData().textureID, ImVec2(160, 90), ImVec2(0, 0), ImVec2(1, 1), 0);
            if(ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_oFScn")) {
                    IM_ASSERT(payload->DataSize == sizeof(thumbnails[0]));
                    memcpy((void*)&d, payload->Data, sizeof(thumbnails[0]));
                }
            }
            dest_index++;
            ImGui::End();
        }
    }
}
