//
//  Combo.cpp
//  drag_and_drop
//
//  Created by Yuma Taesu on 2018/04/27.
//
//

#include "Combo.hpp"

namespace ImGui {
    IMGUI_API bool Combo(const char* label, int* currIndex, std::vector<std::string>& values) {
        if (values.empty()) { return false; }
        return Combo(label, currIndex, vector_getter,
                     static_cast<void*>(&values), values.size());
    }
    
    //    bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values) {
    //        if (values.empty()) { return false; }
    //        return ListBox(label, currIndex, vector_getter,
    //                       static_cast<void*>(&values), values.size());
    //    }
    
}
