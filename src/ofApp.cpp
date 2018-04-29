#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    
    imgui.setup();
    
    auto& style = ImGui::GetStyle();
    style.FrameRounding = 0.f;
    style.WindowPadding = ImVec2(8.f, 8.f);
    style.PopupRounding = 0.f;
    style.FramePadding = ImVec2(2.f, 0.f);
    style.ItemSpacing = ImVec2(8.f, 4.f);
    style.GrabMinSize = 20.f;
    
    
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.08f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.44f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.01f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.00f, 0.10f, 0.38f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.10f, 0.38f, 0.71f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.00f, 0.59f, 0.81f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_CloseButton]            = ImVec4(0.41f, 0.41f, 0.41f, 0.51f);
    colors[ImGuiCol_CloseButtonHovered]     = ImVec4(0.00f, 0.59f, 0.81f, 1.00f);
    colors[ImGuiCol_CloseButtonActive]      = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.00f, 0.78f, 0.89f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.44f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.00f, 0.78f, 0.89f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.44f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.00f, 0.78f, 0.89f, 1.00f);
    colors[ImGuiCol_ModalWindowDarkening]   = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 0.00f, 0.38f, 1.00f);
    
    
    ofDisableArbTex();
    ofLoadImage(textures[0], "VRSP03.gvintermediate.png");
    ofLoadImage(textures[1], "VRSP04.gvintermediate.png");
    ofLoadImage(textures[2], "VRSP05.gvintermediate.png");
    ofLoadImage(textures[3], "VRSP06.gvintermediate.png");
    ofLoadImage(textures[4], "VRSP07.gvintermediate.png");
    ofLoadImage(textures[5], "VRSP08.gvintermediate.png");
    
    //rendering_scene_thumbnail = std::make_shared<ofTexture>();
    rendering_scene_thumbnail.allocate(1280, 720, GL_RGBA);
    rendering_scene_thumbnail2.allocate(1280, 720, GL_RGBA);
    rendering_scene_thumbnail3.allocate(1280, 720, GL_RGBA);
    ofEnableArbTex();
    
    
    drag_drop.loadThumbnails();
    
    metatag = { "All", "Primitive", "Realistic", "Potemkin", "Glitch", "Doped" };
    tag_num = metatag.size();
    
    int index = 0;
    for (const auto &str : metatag) {
        char *charStr = new char[str.size() + 1];
        std::strcpy(charStr, str.c_str());
        charVec.push_back(charStr);
        tabOrder.push_back(index);
        index++;
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    //deltaTime_ += (deltaTime * delta);
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(45);
    auto& style = ImGui::GetStyle();
    
    imgui.begin();
    
    {
        static float v = 0.f;
        static float v1 = 0.f;
        static float v2 = 0.f;
        static float v3 = 0.f;
        static float v4 = 0.f;
        ImGui::Begin("##");
        ImGui::PushItemWidth(-1);
        ImGui::SliderFloat("##v", &v, 0.f, 30.f, "");
        ImGui::SliderFloat("##vv", &v1, 0.f, 30.f, "");
        ImGui::SliderFloat("##vvv", &v2, 0.f, 30.f, "");
        ImGui::SliderFloat("###vvv", &v3, 0.f, 30.f, "");
        ImGui::SliderFloat("###vvvv", &v4, 0.f, 30.f, "");
        ImGui::SliderFloat("###q", &v4, 0.f, 30.f, "");
        ImGui::PopItemWidth();
        ImGui::End();
    }
    
    {
        static float v = 0.f;
        static float v1 = 0.f;
        static float v2 = 0.f;
        static float v3 = 0.f;
        static float v4 = 0.f;
        static float v5 = 0.f;
        ImGui::Begin("VSlider");
        ImGui::VSliderFloat("##v", ImVec2(30, 150), &v, 0.f, 10.f, ""); ImGui::SameLine();
        ImGui::VSliderFloat("##vv", ImVec2(30, 150), &v1, 0.f, 10.f, ""); ImGui::SameLine();
        ImGui::VSliderFloat("##vvw", ImVec2(30, 150), &v2, 0.f, 10.f, ""); ImGui::SameLine();
        ImGui::VSliderFloat("##ve", ImVec2(30, 150), &v3, 0.f, 10.f, ""); ImGui::SameLine();
        ImGui::VSliderFloat("##1", ImVec2(30, 150), &v4, 0.f, 10.f, ""); ImGui::SameLine();
        ImGui::VSliderFloat("##2", ImVec2(30, 150), &v5, 0.f, 10.f, "");
        ImGui::End();
    }
    
    
    {
        //Preview--------------------------------------------------------
        ImGui::Begin("Images");
        auto& style = ImGui::GetStyle();
        style.FramePadding = ImVec2(2.f, 2.f);
        style.ItemSpacing = ImVec2(2.f, 2.f);
        ImGui::Columns(4, "mycolumns3", false);  // 4-ways, no border
        ImGui::Separator();
        for(auto& t : textures) {
            ImGui::ImageButton((ImTextureID)(uintptr_t) t.getTextureData().textureID, ImVec2(80, 45));
            ImGui::NextColumn();
        }
        style.FramePadding = ImVec2(2.f, 0.f);
        style.ItemSpacing = ImVec2(8.f, 4.f);
        ImGui::End();
    }
    
    //HISTGRAM-------------------------------------------------------
    ImGui::Begin("HISTOGRAM");
    histgram.drawGui();
    ImGui::End();
    
    
    //KNOB----------------------------------------------------------
    static float angle = 0;
    static float angle2 = 0;
    static float angle3 = 0;
    static float angle4 = 0;
    static float angle5 = 0;
    static float angle6 = 0;
    static float angle7 = 0;
    static float angle8 = 0;
    
    ImGui::Begin("KNOB");
    ImGui::Knob("Freq", &angle, 0.f, 10.f); ImGui::SameLine();
    ImGui::Knob("Prd", &angle2, 0.f, 10.f); ImGui::SameLine();
    ImGui::Knob("Spd", &angle3, 0.f, 10.f);
    ImGui::End();
    
    
    
    //LINE HISTOGRAM-------------------------------------------------
    float time = ofGetElapsedTimef();
    for(std::size_t i = 0; i < array_data.size(); ++i) {
        array_data[i] = ofSignedNoise(i * DEG_TO_RAD + time);
    }
    ImGui::Begin("LINE HISTOGRAM");
    ImGui::PushItemWidth(-1);
    ImGui::PlotLines("##line_hist", array_data.data(), array_data.size(), 0.f, "", -1.0f, 1.0f, ImVec2(0, 80));
    ImGui::PopItemWidth();
    ImGui::End();
    
    
    //LINE HISTOGRAM-------------------------------------------------
    ImGui::Begin("GRID");
    static bool selected[16] = { true, false, false, false, false, true, false, false, false, false, true, false, false, false, false, true };
    for (int i = 0; i < 16; i++) {
        ImGui::PushID(i);
        if (ImGui::Selectable("##grid", &selected[i], 0, ImVec2(30, 30))) {
            int x = i % 4, y = i / 4;
            if (x > 0) selected[i - 1] ^= 1;
            if (x < 3) selected[i + 1] ^= 1;
            if (y > 0) selected[i - 4] ^= 1;
            if (y < 3) selected[i + 4] ^= 1;
        }
        if ((i % 4) < 3) ImGui::SameLine();
        ImGui::PopID();
    }
    ImGui::End();
    
    //RADIOBUTTON-------------------------------------------------------
    ImGui::Begin("RADIO BUTTON");
    static int e = 0;
    ImGui::RadioButton("1", &e, 0); ImGui::SameLine();
    ImGui::RadioButton("2", &e, 2); ImGui::SameLine();
    ImGui::RadioButton("3", &e, 3); ImGui::SameLine();
    ImGui::RadioButton("4", &e, 4); ImGui::SameLine();
    ImGui::RadioButton("5", &e, 5); ImGui::SameLine();
    ImGui::RadioButton("6", &e, 6);
    ImGui::End();
    
    
    //CHECKBOX---------------------------------------------------------
    static bool read_only = false;
    ImGui::Begin("CHECK BOX");
    ImGui::Checkbox("Read-only", &read_only); ImGui::SameLine();
    ImGui::Checkbox("Read-only", &read_only); ImGui::SameLine();
    ImGui::Checkbox("Read-only", &read_only); ImGui::SameLine();
    ImGui::Checkbox("Read-only", &read_only); ImGui::SameLine();
    ImGui::Checkbox("Read-only", &read_only); ImGui::SameLine();
    ImGui::Checkbox("Read-only", &read_only);
    ImGui::End();
    
    
    
    //COMBO------------------------------------------------------------
    ImGui::Begin("Combo");
    const ImVec2 framepadding = style.FramePadding;
    style.FramePadding = ImVec2(8.f, 2.f);
    std::vector<std::string> items = { "Additive", "Substitute", "Multiple", "Divide" };
    static int item = -1;
    ImGui::Combo("Combo", &item, items);
    style.FramePadding = framepadding;
    ImGui::End();
    
    
    
    //PROGRESS--------------------------------------------------------
    static float progress = 0;
    progress = 0.5 + 0.5 * sin(ofGetElapsedTimef());
    ImGui::Begin("Progressbar");
    ImGui::PushItemWidth(-1);
    ImGui::ProgressBar(progress, ImVec2(0.0f, 1.0f), "");
    ImGui::ProgressBar(progress, ImVec2(0.0f, 4.0f), "");
    ImGui::ProgressBar(progress, ImVec2(0.0f, 8.0f), "");
    ImGui::PopItemWidth();
    ImGui::End();
    
    
    
    //TAB------------------------------------------------------------
    ImGui::Begin("Tab");
    ImGui::TabLabels(&charVec[0], tag_num, tabSelected, &tabOrder[0]);
    ImGui::Text("%s", metatag[tabSelected].data());
    ImGui::End();
    
    
    
    //COLOR PALLETE--------------------------------------------------
    ImGui::Begin("Color");
    int index = 0;
    for(auto& c : color_pickers) {
        c.drawGui(std::to_string(index));
        index++;
    }
    ImGui::End();
    
    
    //DRAG DROP TEST----------------------------------------------------
    drag_drop.drawGui();

    
    
    
    this->drawGui();
    imgui.end();
}


void ofApp::drawGui()
{
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}



void ofApp::exit() {
    rendering_scene_thumbnail.clear();
    rendering_scene_thumbnail2.clear();
    rendering_scene_thumbnail3.clear();
}
