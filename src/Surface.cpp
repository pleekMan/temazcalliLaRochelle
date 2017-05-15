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

vector<ofPoint> Surface::getCorners(){

    vector<ofPoint> cornerPoints;
    
    ofPoint topLeft = ofPoint(float(warpSurface.getControlPoints()[0]),float(warpSurface.getControlPoints()[1]));
    
    ofPoint topRight = ofPoint(float(warpSurface.getControlPoints()[((gridResX-1)*3)+0]),float(warpSurface.getControlPoints()[((gridResX-1)*3)+1]));
    
    int blX = (warpSurface.getControlPoints().size() - (gridResX*3))+0;
    int blY = (warpSurface.getControlPoints().size() - (gridResX*3))+1;
    ofPoint bottomLeft = ofPoint(float(warpSurface.getControlPoints()[blX]),float(warpSurface.getControlPoints()[blY]));
    
    ofPoint bottomRight = ofPoint(float(warpSurface.getControlPoints()[warpSurface.getControlPoints().size() - 3]), float(warpSurface.getControlPoints()[warpSurface.getControlPoints().size() - 2]));
    
    cornerPoints.push_back(topLeft);
    cornerPoints.push_back(topRight);
    cornerPoints.push_back(bottomLeft);
    cornerPoints.push_back(bottomRight);
    
    return cornerPoints;
}

