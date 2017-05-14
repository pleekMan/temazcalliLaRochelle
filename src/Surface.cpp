//
//  Surface.cpp
//  temazcalliLaRochelle
//
//  Created by PleekMan on 12/5/2017.
//
//

#include "Surface.h"

void Surface::init(int width, int height, int resX, int resY){
    warpSurface.allocate(width,height,resX,resY,100); // (w,h,resX,resY,pixelsPerGridDivision)
}

void Surface::update(){
    
}

void Surface::render(){
    warpSurface.draw();
}

void Surface::setControlPoints(vector<GLfloat> controlPoints){
    
}

void Surface::setName(string _name){
    name = _name;
}
void Surface::setId(int _id){
    ID = _id;
}

void Surface::beginDraw(){
    warpSurface.begin();
    
}

void Surface::endDraw(){
    warpSurface.end();
}

