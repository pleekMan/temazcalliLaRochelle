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
    bool loadSettings(ofxXmlSettings* settings);
    void saveSettings(ofxXmlSettings* settings);
    void update();
    void render();
    void setFont(ofTrueTypeFont *_font);
    
    void createSurface(string name, int id, int width, int height, int resX, int resY, vector<GLfloat> controlPoints);
    Surface* getSurfaceById(int ID);
    Surface getSurfaceByName(string _name);
    int getSurfaceCount();
    void selectSurface(int x, int y);
    void activateSurface(int selectedSurface);
    
    void drawBeginOnSurface(int ID);
    void drawEndOnSurface(int ID);
    void toggleSurfaceGrid(int ID);
    void previewSelection();
    
    void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    
    
    int selectedSurface;
    ofTrueTypeFont* font;
    
private:
    
    vector<Surface> surfaces;
    
    
};