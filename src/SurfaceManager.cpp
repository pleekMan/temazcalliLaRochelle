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
    activeSurface = -1;
    dragInsideMode = false;
    warpMode = false;
    
    gizmosColorA = ofColor(0, 255, 255);
}

void SurfaceManager::setFont(ofTrueTypeFont *_font){
    font = _font;
}

void SurfaceManager::update(){
    
}

void SurfaceManager::render(){
    
    for (int i=0; i<getSurfaceCount(); i++) {
        surfaces[i].render();
        
        // ALWAYS DRAW GIZMOS AFTER RENDERING SHIT
        if (surfaces[i].isActive()) {
            drawGizmos();
        }
    }
    
    previewSelection();
    
}

#pragma mark DRAWING
void SurfaceManager::drawBeginOnSurface(int ID){
    surfaces[ID].beginDraw();
}

void SurfaceManager::drawEndOnSurface(int ID){
    surfaces[ID].endDraw();

}

void SurfaceManager::drawGizmos(){
    if (warpMode) {
        
    } else if(dragInsideMode){
        surfaces[activeSurface].drawWarpSurfaceOutline();
    } else {
        // SELECT-MODE AND GLOBAL SURFACE FUNCTIONS
        
        // DRAW CORNERS
        
        ofSetColor(gizmosColorA);
        ofNoFill();
        
        ofPolyline cornersShape =  surfaces[activeSurface].getCornersOutline();
        for (int i=0; i<cornersShape.getVertices().size(); i++) {
            float x = cornersShape.getVertices()[i].x;
            float y = cornersShape.getVertices()[i].y;
            
            ofDrawEllipse(x, y, 10, 10);
            ofDrawEllipse(x, y, 20, 20);
        }
        
        // DRAW WARP MESH AS LITTLE DOTS
        ofFill();
        vector<float> warpPoints = surfaces[activeSurface].warpSurface.getControlPointsReference();
        for (int i=0; i<warpPoints.size(); i++) {
            float x = warpPoints[(3*i) + 0];
            float y = warpPoints[(3*i) + 1];
            
            ofDrawEllipse(x, y, 3, 3);
        }
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
        
        if(surfaceShape.inside(ofGetMouseX(), ofGetMouseY()) && i != activeSurface){
            
            ofPushStyle();
            ofRectangle textBoundingBox = font->getStringBoundingBox(surfaces[i].name, 0, 0);
            font->drawString(surfaces[i].name, ofGetMouseX() - (textBoundingBox.getWidth() * 0.5),ofGetMouseY() - 20);
            
            
            // DRAW BOUNDING SHAPE + CROSS
            ofNoFill();
            ofSetColor(gizmosColorA);
            
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

#pragma mark SETTINGS LOAD/SAVE
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

#pragma mark SURFACE OPERATIONS
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
    
    int tempSelectedSurface = -1;

    
    for (int i=0; i<getSurfaceCount(); i++) {
        
        ofPolyline surfaceShape = surfaces[i].getCornersOutline();
        
        if(surfaceShape.inside(x, y)){
            
            if (i != tempSelectedSurface) {
                tempSelectedSurface = i;
            }
            break;
        }
    }
    
    // NEED TO DO SOMETHING HERE TO GET OUT OF DRAG-MODE WITHOUT DESELECTING THE ACTUAL SURFACE
    
    activeSurface = tempSelectedSurface;
    activateSurface(activeSurface);
    
}


void SurfaceManager::activateSurface(int selSurf){
    
    for (int i=0; i<getSurfaceCount(); i++) {
        surfaces[i].warpSurface.setShowWarpGrid(false);
        surfaces[i].setActive(false);
    }
    
    if (selSurf != -1) {
        //surfaces[activeSurface].warpSurface.setShowWarpGrid(true);
        surfaces[activeSurface].setActive(true);
        
    }
}


void SurfaceManager::dragContentInside(){
    
    float deltaX = ofGetMouseX() - ofGetPreviousMouseX();
    float deltaY = ofGetMouseY() - ofGetPreviousMouseY();
    
    surfaces[activeSurface].offsetContent(ofPoint(deltaX,deltaY));
    
}

#pragma mark -
#pragma mark EVENTS
void SurfaceManager::keyPressed(int key){
    
    if (key == 'd' || key == 'D') {
        dragInsideMode = !dragInsideMode;
        surfaces[activeSurface].showWarpOutline = dragInsideMode;
    }
    if (key == 'w' || key == 'W') {
        warpMode = !warpMode;
        
        if (activeSurface != -1) {
            surfaces[activeSurface].warpSurface.setShowWarpGrid(warpMode);
        }
    }
}

void SurfaceManager::mouseReleased(int x, int y, int button){
    
 
}

void SurfaceManager::mousePressed(int x, int y, int button){
    if(!warpMode){
        selectSurface(x,y);
    }
}

void SurfaceManager::mouseDragged(int x, int y, int button){
    if (dragInsideMode && !warpMode) {
        dragContentInside();
    }
}



