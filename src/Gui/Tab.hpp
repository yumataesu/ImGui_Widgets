#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"

namespace ImGui {
    IMGUI_API bool TabLabels(char **tabLabels, int tabSize, int &tabIndex, int *tabOrder=NULL);
}
