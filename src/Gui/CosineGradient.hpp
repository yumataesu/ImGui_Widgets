//
//  thCosineGradient.hpp
//  Interstellar
//
//  Created by Yuma Taesu on 2017/09/05.
//
//

#pragma once
#include "ofMain.h"
#include "ofxImGui.h"


class CosineGradient {
public:
    CosineGradient();
    ~CosineGradient();
    void setup();
    void writeToFbo();
    void drawGui();
    
    ofTexture getCosineGradientTex() const { return fbo_->getTexture(); }
    ofTexture& getCosineGradientTex() { return fbo_->getTexture(); }
    
protected:
    string genVertShader();
    string genFragShader();
    ofShader cosine_shader_;
    ofMesh quad_;
    std::shared_ptr<ofFbo> fbo_;
    
    ofVec3f m_freq;
    ofVec3f m_phase;
    
};
