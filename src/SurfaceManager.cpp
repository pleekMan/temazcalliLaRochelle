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
    selectedSurface = -1;
}

void SurfaceManager::setFont(ofTrueTypeFont *_font){
    font = _font;
}

void SurfaceManager::update(){
    
}

void SurfaceManager::render(){
    
    for (int i=0; i<getSurfaceCount(); i++) {
        surfaces[i].render();
        
        if (surfaces[i].isActive()) {
            surfaces[i].drawGizmos();
        }
    }
    
    previewSelection();
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
                int resX = settings->getAttribute("surface","gridResX",2,i);
                int resY = settings->getAttribute("surface","gridResY",2,i);
                int id = settings->getAttribute("surface", "id", 0, i);
                
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
                createSurface(surfaceName, id, 640, 480, resX, resY, controlPoints);
                
                
                
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

void SurfaceManager::createSurface(string name, int id, int width, int height, int resX, int resY, vector<GLfloat> controlPoints){
    
    Surface newSurface;
    newSurface.init(width, height, resX, resY);
    newSurface.setName(name);
    newSurface.setId(id);
    newSurface.setControlPoints(controlPoints);
    
    surfaces.push_back(newSurface);
    
    
}

Surface* SurfaceManager::getSurfaceById(int ID){
    
    if(getSurfaceCount() > 0){ // --> PASAR ESTA AL LUGAR DONDE SE ESTE LLAMANDO A ESTA FUNCION
        for (int i=0; i<getSurfaceCount(); i++) {
            
            if (surfaces[i].ID == ID) {
                return &surfaces[i];
            } else {
                cout << "|| DID NOT FIND A SURFACE WITH ID: " << ID << ". RETURNING SURFACE[0]" << endl;
                return &surfaces[0];
            }
        }
    } else {
        cout << "|| NO SURFACE EXIST: RETURNING NULL POINTER" << endl;
        return nullptr;
    }
}

Surface SurfaceManager::getSurfaceByName(string _name){
    
}

void SurfaceManager::toggleSurfaceGrid(int ID){
    surfaces[ID].warpSurface.toggleShowWarpGrid();
}

int SurfaceManager::getSurfaceCount(){
    return surfaces.size();
}

void SurfaceManager::selectSurface(int x, int y){
    
    //selectedSurface = -1;
    
    for (int i=0; i<getSurfaceCount(); i++) {
        
        ofPolyline surfaceShape;
        // THE ORDER OF vector<GLFloat> IS NOT GOOD FOR CONSTRUCTING THE SQUARED POLYLINE
        surfaceShape.addVertex(surfaces[i].getCorners()[0]);
        surfaceShape.addVertex(surfaces[i].getCorners()[1]);
        surfaceShape.addVertex(surfaces[i].getCorners()[3]);
        surfaceShape.addVertex(surfaces[i].getCorners()[2]);
        
        if(surfaceShape.inside(x, y)){
            selectedSurface = i;
            
            ofBeginShape();
            ofVertices(surfaceShape.getVertices());
            ofEndShape();
            
            
            break;
        }
    }
    activateSurface(selectedSurface);
    
}


void SurfaceManager::activateSurface(int selectedSurface){
    
    if (selectedSurface != -1) {
        for (int i=0; i<getSurfaceCount(); i++) {
            surfaces[i].warpSurface.setShowWarpGrid(false);
            surfaces[i].setActive(false);
        }
        surfaces[selectedSurface].warpSurface.setShowWarpGrid(true);
        surfaces[selectedSurface].setActive(true);
        
    }
}

void SurfaceManager::previewSelection(){
    
    for (int i=0; i<getSurfaceCount(); i++) {
        
        ofPolyline surfaceShape;
        // THE ORDER OF vector<GLFloat> IS NOT GOOD FOR CONSTRUCTING THE SQUARED POLYLINE
        surfaceShape.addVertex(surfaces[i].getCorners()[0]);
        surfaceShape.addVertex(surfaces[i].getCorners()[1]);
        surfaceShape.addVertex(surfaces[i].getCorners()[3]);
        surfaceShape.addVertex(surfaces[i].getCorners()[2]);
        
        if(surfaceShape.inside(ofGetMouseX(), ofGetMouseY()) && i != selectedSurface){
            
            ofPushStyle();
            ofRectangle textBoundingBox = font->getStringBoundingBox(surfaces[i].name, 0, 0);
            font->drawString(surfaces[i].name, ofGetMouseX() - (textBoundingBox.getWidth() * 0.5),ofGetMouseY() - 20);
            
            
            // DRAW BOUNDING SHAPE + CROSS
            ofNoFill();
            ofSetColor(0, 255, 255);
            
            ofBeginShape();
            ofVertices(surfaceShape.getVertices());
            ofEndShape(true);
            
            ofDrawLine(surfaceShape.getVertices()[0], surfaceShape.getVertices()[2]);
            ofDrawLine(surfaceShape.getVertices()[1], surfaceShape.getVertices()[3]);

            
            ofPopStyle();
            
            break;
        }
    }
    
}
void SurfaceManager::keyPressed(int key){
    
    // TEST TO GET THE CORNERS OF A WARPSURFACE
    if (key == 'c' || key == 'C') {
        vector<ofPoint> corners = surfaces[0].getCorners();
        
        for (int i=0; i<corners.size(); i++) {
            cout << "Corner " << i << " -> " << ofToString(corners[i].x) << ":" << ofToString(corners[i].y) << endl;
        }
    }
}

void SurfaceManager::mouseReleased(int x, int y, int button){
    
    selectSurface(x,y);
 
}



