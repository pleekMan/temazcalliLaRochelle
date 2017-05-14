//
//  Surface.cpp
//  temazcalliLaRochelle
//
//  Created by PleekMan on 12/5/2017.
//
//

#include "Surface.h"

void Surface::init(int width, int height, int resX, int resY){
    
    gridResX = resX;
    gridResY = resY;
    
    warpSurface.allocate(width,height,resX,resY,100); // (w,h,resX,resY,pixelsPerGridDivision)
    
    warpSurface.begin();
    ofClear(0);
    warpSurface.end();
}

void Surface::update(){
    
}

void Surface::render(){
    warpSurface.draw();
}

void Surface::setControlPoints(vector<GLfloat> controlPoints){
    warpSurface.setControlPoints(controlPoints);
}

void Surface::setName(string _name){
    name = _name;
}
void Surface::setId(int _id){
    ID = _id;
}

void Surface::beginDraw(){
    warpSurface.begin();
    
    ofPushStyle();
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofSetLineWidth(5);
    ofDrawRectangle(0, 0, warpSurface.getWidth(), warpSurface.getHeight());
    
    ofPopStyle();
    
    ofDrawBitmapString(name, 20, 20);
    
}

void Surface::endDraw(){
    warpSurface.end();
}

