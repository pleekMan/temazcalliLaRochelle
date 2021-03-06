#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxBezierWarp.h"
#include "ofxXmlSettings.h"
#include "Surface.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void loadMappingData();
    void saveMappingData();

    
    ofVideoPlayer video;
    bool playing;
    int videoSize;
    bool stopWhenFinished;
    
    bool calibrationMode;
    ofxCsv settings;
    
   
    bool positionMode;
    
    int selectedSurface;
    //int currentPoint;
    int moveStep;
    
    //----------
    
    ofxBezierWarp videoSurface[2];
    
    //----------
    
    ofxXmlSettings settings2;
    bool loadSettings();
    
    // ------- LO NUEVO CON SURFACES
    // ACORDARSE DE CREAR UN SurfaceManager PARA GESTIONARLOS Y RENDERIZAR LOS OVERLAYED CONTROLS
    
    Surface surface1;
    
};
