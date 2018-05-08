//
//  thCosineGradient.hpp
//  Interstellar
//
//  Created by Yuma Taesu on 2017/09/05.
//
//

#pragma once
#include "ofShader.h"
#include "ofFbo.h"
#include "ofTexture.h"
#include "ofxImGui.h"

namespace th {
    
    class CosineGradient {
    public:
        CosineGradient();
        ~CosineGradient();
        void setup();
        void writeToFbo();
        void drawGui();
        
        ofTexture getCosineGradientTex() const { return m_fbo->getTexture(); }
        ofTexture& getCosineGradientTex() { return m_fbo->getTexture(); }
        
    protected:
        string genVertShader();
        string genFragShader();
        ofShader m_cosineShader;
        ofMesh m_quad;
        ofFbo* m_fbo;
        
        ofVec3f m_freq;
        ofVec3f m_phase;
        ofxImGui m_gui;
    };
    
}
