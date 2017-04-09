#pragma once

#include "ofMain.h"
#include "ofxKeystoneTexture.h"
#include "ofxCsv.h"

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
    
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    void loadKeystoneData();
    void saveKeystoneData();

    
    ofVideoPlayer video;
    bool playing;
    float ratio;
    int videoSize;
    
    bool calibrationMode;
    ofxCsv settings;
    //String settingsMessage;
    
    int positionY;
    bool positionMode;
    
    ofFbo videoTop;
    ofFbo videoBottom;
    
    ofxKeystoneTexture keystoneLayers[2];
    
    int selectedKeystone;
    int currentPoint;
    int moveStep;
		
};
