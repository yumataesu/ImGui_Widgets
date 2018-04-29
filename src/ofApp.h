#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "Gui/ColorPicker.h"
#include "Gui/Tab.hpp"
#include "Gui/Histgram.h"
#include "Gui/Combo.hpp"
#include "Gui/DragDrop.hpp"
#include "Gui/Knob.hpp"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void lateDrawUpdate();
    void drawGui();
    void keyPressed(int key);
    void keyReleased(int key);
    
    void DndBegin(const char* label);
    void DndEnd();
    
    const int WIDTH = ofGetWidth();
    const int HEIGHT = ofGetHeight();
    
    ofxImGui::Gui imgui;
    std::array<ttt::ColorPicker, 12> color_pickers;
    ttt::Histgram histgram;
    ttt::DragDrop drag_drop;
    ImFont* large_font;
    ImFont* midium_font;
    
    std::array<ofTexture, 6> textures;
    
    std::vector<char*> charVec;
    std::vector<int> tabOrder;
    std::vector<std::string> metatag;
    int tabSelected;
    int tag_num;
    
    
    std::array<float, 256> array_data;
};
