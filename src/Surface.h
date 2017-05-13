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
    void init(int _id, int width, int height, int resX, int resY);
    void update();
    void render();
    
    void setControlPoints(vector<GLfloat> controlPoints);
    void beginDraw();
    void endDraw();
    
    ofxBezierWarp warpSurface;
    int ID;
    
private:
};