//
//  Knob.hpp
//  drag_and_drop
//
//  Created by Yuma Taesu on 2018/04/29.
//
//

#ifndef Knob_hpp
#define Knob_hpp

#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"


namespace ImGui {
    IMGUI_API bool Knob(const char* label, float* value_p, float minv, float maxv);
}

#endif /* Knob_hpp */
