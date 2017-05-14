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

void SurfaceManager::render(){
    
    for (int i=0; i<getSurfaceCount(); i++) {
        surfaces[i].render();
    }
    
}

void SurfaceManager::drawBeginOnSurface(int ID){
    surfaces[ID].beginDraw();
}

void SurfaceManager::drawEndOnSurface(int ID){
    surfaces[ID].endDraw();

}

bool SurfaceManager::loadSettings(ofxXmlSettings* settings){
    
    //if( settings.loadFile("settingsAttributes_bkup.xml") ){
    
    // LOAD SURFACES - BEGIN
    
    if (settings->tagExists("settings:surfaces")){
        
        settings->pushTag("settings"); // SI HAGO ASI "settings:surfaces", NO FUNCIONA
        settings->pushTag("surfaces");
        
        int surfacesCount = settings->getNumTags("surface");
        if(surfacesCount > 0){
            for (int i=0; i<surfacesCount; i++) {
                
                string surfaceName = settings->getAttribute("surface", "name","SurfaceX", i);
                int resX = settings->getAttribute("surface","gridResX",1,i);
                int resY = settings->getAttribute("surface","gridResY",1,i);
                
                cout << "|| " << surfaceName << endl;
                
                settings->pushTag("surface",i);
                int pointsCount = settings->getNumTags("controlPoint");
                
                vector<GLfloat> controlPoints;
                
                
                for (int j=0; j<pointsCount; j++) {
                    int x = ofToFloat(settings->getAttribute("controlPoint", "x", "99", j));
                    int y = ofToFloat(settings->getAttribute("controlPoint", "y", "99", j));
                    int z = 0;
                    
                    controlPoints.push_back(x);
                    controlPoints.push_back(y);
                    controlPoints.push_back(z);
                    
                    cout << "|| " << x << " : " << y << endl;
                }
                
                // CREATE SURFACE
                createSurface(surfaceName, 640, 480, resX, resY, controlPoints);
                
                
                
                //cout << "|| " << settings2.getValue("a:valor", 99, i) << endl;
                settings->popTag();
            }
        }
        settings->popTag();
        settings->popTag(); // BACK TO: BEFORE settings (ROOT)
        
        // LOAD SURFACES - END
        return true;
    }
    else{
        // LOAD DEFAULT SURFACES SETTINGS
        cout << "|| WARNING: NO SURFACES FOUND ON SETTINGS" << endl;
        return false;
    }
}

void SurfaceManager::saveSettings(ofxXmlSettings* settings){
    
    settings->pushTag("settings");
    settings->pushTag("surfaces");
    settings->clear();
    //settings->addTag("surface");
    
    for (int i=0; i<getSurfaceCount(); i++) {
        settings->addTag("surface");
        settings->addAttribute("surface", "name", surfaces[i].name, i);
        settings->addAttribute("surface", "gridResX", surfaces[i].gridResX, i);
        settings->addAttribute("surface", "gridResY", surfaces[i].gridResY, i);
        
        settings->pushTag("surface", i);
        vector<float> controlPoints = surfaces[i].warpSurface.getControlPointsReference();
        
        int pointCount =surfaces[i].warpSurface.getNumXPoints() * surfaces[i].warpSurface.getNumYPoints();
        for (int j=0; j< pointCount ; j++) {
            
            settings->addTag("controlPoint");
            settings->addAttribute("controlPoint", "x", int(controlPoints[(j*3)+0]),j);
            settings->addAttribute("controlPoint", "y", int(controlPoints[(j*3)+1]),j);

        }
        settings->popTag();

    }
    
    settings->saveFile();
    
    cout << "|| Settings File Saved" << endl;
    
    
}

void SurfaceManager::createSurface(string name, int width, int height, int resX, int resY, vector<GLfloat> controlPoints){
    
    int newId = surfaces.size();
    
    Surface newSurface;
    newSurface.init(width, height, resX, resY);
    newSurface.setName(name);
    newSurface.setId(newId);
    newSurface.setControlPoints(controlPoints);
    
    surfaces.push_back(newSurface);
    
    
}

Surface SurfaceManager::getSurfaceById(int ID){
    return surfaces[ID];
}

Surface SurfaceManager::getSurfaceByName(string _name){
    
}

void SurfaceManager::toggleSurfaceGrid(int ID){
    surfaces[ID].warpSurface.toggleShowWarpGrid();
}

int SurfaceManager::getSurfaceCount(){
    return surfaces.size();
}