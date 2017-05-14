//
//  SurfaceManager.cpp
//  temazcalliLaRochelle
//
//  Created by PleekMan on 13/5/2017.
//
//

#include "SurfaceManager.h"

SurfaceManager::SurfaceManager(){
    
}
SurfaceManager::~SurfaceManager(){
    
}

void SurfaceManager::init(){
    
}

void SurfaceManager::update(){
    
}

void SurfaceManager::draw(){
    
    
}

bool SurfaceManager::loadSettings(ofxXmlSettings settings){
    
    //if( settings.loadFile("settingsAttributes_bkup.xml") ){
    
    // LOAD SURFACES - BEGIN
    
    if (settings.tagExists("settings:surfaces")){
        
        settings.pushTag("settings"); // SI HAGO ASI "settings:surfaces", NO FUNCIONA
        settings.pushTag("surfaces");
        
        int surfacesCount = settings.getNumTags("surface");
        if(surfacesCount > 0){
            for (int i=0; i<surfacesCount; i++) {
                
                string surfaceName = settings.getAttribute("surface", "name","SurfaceX", i);
                int resX = settings.getAttribute("surface","gridResX",1,i);
                int resY = settings.getAttribute("surface","gridResY",1,i);
                
                cout << "|| " << surfaceName << endl;
                
                settings.pushTag("surface",i);
                int pointsCount = settings.getNumTags("controlPoint");
                
                vector<GLfloat> controlPoints;
                
                
                for (int j=0; j<pointsCount; j++) {
                    int x = ofToFloat(settings.getAttribute("controlPoint", "x", "99", j));
                    int y = ofToFloat(settings.getAttribute("controlPoint", "y", "99", j));
                    
                    controlPoints.push_back(x);
                    controlPoints.push_back(y);
                    
                    cout << "|| " << x << endl;
                }
                
                // CREATE SURFACE
                createSurface(surfaceName, 640, 480, resX, resY, controlPoints);
                
                
                
                //cout << "|| " << settings2.getValue("a:valor", 99, i) << endl;
                settings.popTag();
            }
        }
        settings.popTag();
        settings.popTag(); // BACK TO: BEFORE settings (ROOT)
        
        // LOAD SURFACES - END
        return true;
    }
    else{
        // LOAD DEFAULT SURFACES SETTINGS
        cout << "|| WARNING: NO SURFACES FOUND ON SETTINGS" << endl;
        return false;
    }
}

void SurfaceManager::createSurface(string name, int width, int height, int resX, int resY, vector<GLfloat> controlPoints){
    
    int newId = surfaces.size();
    
    Surface newSurface;
    newSurface.init(width, height, resX, resY);
    newSurface.setName(name);
    newSurface.setId(newId);
    
    surfaces.push_back(newSurface);
    
    
}

Surface SurfaceManager::getSurface(int ID){
    
}