//
//  thCosineGradient.cpp
//  Interstellar
//
//  Created by Yuma Taesu on 2017/09/05.
//
//

#include "CosineGradient.hpp"


CosineGradient::CosineGradient()
:m_freq(ofVec3f(1.0, 1.0, 0.5))
,m_phase(ofVec3f(0.8, 0.9, 0.3))
{}

CosineGradient::~CosineGradient()
{}

//Generate pass-through vertex shader
string CosineGradient::genVertShader(){
    stringstream src;
    
    src <<"#version 410\n";
    src <<"in vec3 position;\n";
    src <<"in vec2 texcoord;\n";
    src <<"out vec2 v_texcoord;\n";
    src <<"void main() {;\n";
    src <<"\tv_texcoord = texcoord;\n";
    src <<"\tgl_Position = vec4(position, 1.0);\n";
    src <<"}\n";
    
    return src.str();
}


string CosineGradient::genFragShader(){
    stringstream src;
    
    src <<"#version 410\n";
    src <<"#define PI 3.14159\n";
    src <<"uniform vec3 freq;\n";
    src <<"uniform vec3 phase;\n";
    src <<"in vec2 v_texcoord;\n";
    src <<"out vec4 fragColor;\n";
    src <<"void main() {;\n";
    src <<"\tfloat red   = 0.5 + 0.5 * cos(2 * PI * (freq.r * v_texcoord.x + phase.r));\n";
    src <<"\tfloat green = 0.5 + 0.5 * cos(2 * PI * (freq.g * v_texcoord.x + phase.g));\n";
    src <<"\tfloat blue  = 0.5 + 0.5 * cos(2 * PI * (freq.b * v_texcoord.x + phase.b));\n";
    src <<"\tfragColor = vec4(red, green, blue, 1.0);\n";
    src <<"}\n";
    
    return src.str();
}

void CosineGradient::setup()
{
    quad_.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    quad_.addVertex(ofVec3f(1.0, 1.0, 0.0));
    quad_.addTexCoord(ofVec2f(1.0f, 1.0f));
    quad_.addVertex(ofVec3f(1.0, -1.0, 0.0));
    quad_.addTexCoord(ofVec2f(1.0f, 0.0f));
    quad_.addVertex(ofVec3f(-1.0, -1.0, 0.0));
    quad_.addTexCoord(ofVec2f(0.0f, 0.0f));
    quad_.addVertex(ofVec3f(-1.0, 1.0, 0.0));
    quad_.addTexCoord(ofVec2f(0.0f, 1.0f));
    
    
    ofDisableArbTex();
    fbo_ = std::make_shared<ofFbo>();
    fbo_->allocate(256, 1);
    fbo_->begin(); ofClear(0); fbo_->end();
    ofEnableArbTex();
    
    cosine_shader_.setupShaderFromSource(GL_VERTEX_SHADER, this->genVertShader());
    cosine_shader_.setupShaderFromSource(GL_FRAGMENT_SHADER, this->genFragShader());
    cosine_shader_.bindDefaults();
    cosine_shader_.linkProgram();
}


void CosineGradient::writeToFbo()
{
    fbo_->begin();
    ofClear(0);
    cosine_shader_.begin();
    cosine_shader_.setUniform3f("freq", m_freq.x, m_freq.y, m_freq.z);
    cosine_shader_.setUniform3f("phase", m_phase.x, m_phase.y, m_phase.z);
    quad_.draw();
    cosine_shader_.end();
    fbo_->end();
}

void CosineGradient::drawGui()
{
    bool guishow = true;
    ImGui::Begin("Color Plette");
    ImGui::PushItemWidth(-1);
    ImGui::ImageButton((ImTextureID)(uintptr_t) fbo_->getTexture(0).getTextureData().textureID, ImVec2(320, 54));
    ImGui::Text("Freqences");
    ImGui::SliderFloat("##RedFreq", &m_freq.x, 0.0f, 1.0f);
    ImGui::SliderFloat("##GreenFreq", &m_freq.y, 0.0f, 1.0f);
    ImGui::SliderFloat("##BlueFreq", &m_freq.z, 0.0f, 1.0f);
    ImGui::Text("phase");
    ImGui::SliderFloat("##RedPhase", &m_phase.x, 0.0f, 1.0f);
    ImGui::SliderFloat("##GreenPhase", &m_phase.y, 0.0f, 1.0f);
    ImGui::SliderFloat("##BluePhase", &m_phase.z, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    ImGui::End();
}
