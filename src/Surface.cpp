//
//  Surface.cpp
//  temazcalliLaRochelle
//
//  Created by PleekMan on 12/5/2017.
//
//

#include "Surface.h"

void Surface::init(int _id, int width, int height, int resX, int resY){
    
    ID = _id;
    warpSurface.allocate(324,234,3,2,100); // (w,h,resX,resY,pixelsPerGridDivision)
    
}

void Surface::update(){
    
}

void Surface::render(){
    warpSurface.draw();
}

void Surface::setControlPoints(vector<GLfloat> controlPoints){
    
}

void Surface::beginDraw(){
    warpSurface.begin();
    
}

void Surface::endDraw(){
    warpSurface.end();
}

