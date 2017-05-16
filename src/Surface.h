//
//  Surface.h
//  temazcalliLaRochelle
//
//  Created by PleekMan on 12/5/2017.
//
//

#ifndef __temazcalliLaRochelle__Surface__
#define __temazcalliLaRochelle__Surface__

#include <iostream>
#include "ofMain.h"
#include "ofxBezierWarp.h"

#endif /* defined(__temazcalliLaRochelle__Surface__) */

class Surface {
    
    
public:
    void init(int width, int height, int resX, int resY);
    void update();
    void render();
    
    void setControlPoints(vector<GLfloat> controlPoints);
    void setName(string _name);
    void setId(int _id);
    void setActive(bool state);
    bool isActive();
    
#pragma mark CONTINUE THIS METHOD
    void offsetContent(ofPoint deltaOffset);
    
    void beginDraw();
    void endDraw();
    void drawGizmos();
    
    vector<ofPoint> getCorners();
    
    ofxBezierWarp warpSurface;
    int ID;
    string name;
    int gridResX, gridResY;
    
    bool active;
    ofPoint contentPosOffset;
    
private:
};