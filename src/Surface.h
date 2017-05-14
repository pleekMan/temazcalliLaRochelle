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
    
    void beginDraw();
    void endDraw();
    
    ofxBezierWarp warpSurface;
    int ID;
    string name;
    
private:
};