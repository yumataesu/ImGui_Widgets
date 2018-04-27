#ifndef Histogram_h
#define Histogram_h

#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"

namespace ttt {
class Histgram {
    
private:
    std::vector<float> plots = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f,
                                      0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f,
                                      0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
public:
    
    void drawGui() {
        ImGui::PushItemWidth(-1);
        ImGui::PlotHistogram("##v", plots.data(), plots.size(), 0, NULL, 0.0f, 1.0f, ImVec2(0,80));
        ImGui::PopItemWidth();
    }
};
}



#endif /* Histogram_h */
