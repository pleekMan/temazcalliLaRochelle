//
//  SurfaceManager.h
//  temazcalliLaRochelle
//
//  Created by PleekMan on 13/5/2017.
//
//

#ifndef __temazcalliLaRochelle__SurfaceManager__
#define __temazcalliLaRochelle__SurfaceManager__

#include <iostream>
#include "ofMain.h"
#include "Surface.h"
#include "ofxXmlSettings.h"

#endif /* defined(__temazcalliLaRochelle__SurfaceManager__) */

class SurfaceManager{

public:
    SurfaceManager();
    ~SurfaceManager();
    
    void init();
    bool loadSettings(ofxXmlSettings settings);
    void update();
    void draw();
    
    void createSurface(string name, int width, int height, int resX, int resY, vector<GLfloat> controlPoints);
    Surface getSurface(int ID);
    
    
private:
    
    vector<Surface> surfaces;
    
    
};