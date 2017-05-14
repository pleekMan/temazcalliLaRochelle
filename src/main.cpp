#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    //ofAppGLFWWindow displaySettings;
    //displaySettings.setMultiDisplayFullscreen(true);
    ////displaySettings.windowMode = OF_FULLSCREEN;
    ////displaySettings.multiMonitorFullScreen = true;
    ////ofCreateWindow(displaySettings);
    //ofSetupOpenGL(&displaySettings, 1920, 2160, OF_FULLSCREEN);
    
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	//ofSetupOpenGL(1920,2160,OF_FULLSCREEN);			// <-------- setup the GL context

    
    // this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
