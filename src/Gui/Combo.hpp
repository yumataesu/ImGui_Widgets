//
//  Combo.hpp
//  drag_and_drop
//
//  Created by Yuma Taesu on 2018/04/27.
//
//

#ifndef Combo_h
#define Combo_h

#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"

namespace ImGui {
    auto vector_getter = [](void* vec, int idx, const char** out_text) {
        auto& vector = *static_cast<std::vector<std::string>*>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
        *out_text = vector.at(idx).c_str();
        return true;
    };
    
    IMGUI_API bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
}




#endif /* Combo_h */
