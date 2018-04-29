//
//  DragDrop.hpp
//  drag_and_drop
//
//  Created by Yuma Taesu on 2018/04/29.
//
//

#ifndef DragDrop_hpp
#define DragDrop_hpp

#include "ofMain.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"

namespace ttt {
class DragDrop {
public:
    void loadThumbnails();
    void drawGui();

private:
    
    ofDirectory dir;
    std::vector<ofTexture> dests;
    std::vector<ofTexture> thumbnails;
};
}


#endif /* DragDrop_hpp */
