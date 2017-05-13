#include "ofApp.h"

/*
---------
---------
 
NOT USING selectedSurface stuff now, but will later

*/

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
	ofSetVerticalSync(true);
    //ofSetFullscreen(true);
    //ofSetWindowShape(1920, 2160);
    //ofSetWindowPosition(x,y);
    
 	video.load("Temazcalli_FullDome_Final_1024x.mov");
	video.setLoopState(OF_LOOP_NORMAL);
	video.play();
    
    playing = true;
    videoSize = 1920;

    
    selectedSurface = 0;
    moveStep = 1;
    stopWhenFinished = true;
    
    calibrationMode = true;
    
    
    //-----------
    
    videoSurface[0].allocate(videoSize, videoSize / 2, 3, 2, 100);
    videoSurface[1].allocate(videoSize, videoSize / 2, 3, 2, 100);
    
    
    cout << ofToString(videoSurface[0].getControlPoints()) << endl;
    
    //vector<GLfloat> bezierPoints1;
    vector<GLfloat> bezierPoints2;
    
    //loadMappingData();
    loadSettings();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    /*
    if (calibrationMode) {
        ofSetColor(255);
        for (int i=0; i < 10; i++) {
            ofDrawLine(i * (videoTop.getWidth() / 10.0), 0, i * (videoTop.getWidth() / 10.0), videoTop.getHeight());
            ofDrawLine(0,i * (videoTop.getHeight() / 10.0), videoTop.getWidth(), i * (videoTop.getHeight() / 10.0));
            
        }
        
        ofFill();
        ofDrawRectangle(videoTop.getWidth() * 0.5, videoTop.getHeight() * 0.5, 50, 200);
    }
    */
    
    video.update();

    videoSurface[0].begin();
        video.draw(0, 0, videoSize, videoSize);
    videoSurface[0].end();

    
    videoSurface[1].begin();
        video.draw(0, -(videoSize / 2), videoSize, videoSize);
    videoSurface[1].end();
    
    if (stopWhenFinished) {
        if (video.getIsMovieDone()) {
            video.setFrame(0);
            video.setPaused(true);
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // IMPORTANT!!
    // USING 2 FULLHD PROJECTORS + COMPUTER DISPLAY (900px HEIGHT APROX)
    // VIDEOSIZE IS FULLHD WIDTH.
    // PLACING THE VIDEO VERTICALLY IS = computerDisplayHeight + ((2projectorsHeight - videoSize) * halfOfThat)
    
    
    for (int i=0; i<2; i++) {
        videoSurface[i].draw();
    }
    
    ofPushStyle();
    
    
    
    ofPopStyle();
    
}

bool ofApp::loadSettings(){
    
    if( settings2.loadFile("settingsAttributes_bkup.xml") ){
		
        // LOAD SURFACES - BEGIN
        
        if (settings2.tagExists("settings:surfaces")){
            
            settings2.pushTag("settings"); // SI HAGO ASI "settings:surfaces", NO FUNCIONA
            settings2.pushTag("surfaces");

            int surfacesCount = settings2.getNumTags("surface");
            if(surfacesCount > 0){
                for (int i=0; i<surfacesCount; i++) {
                    
                    string surfaceName = settings2.getAttribute("surface", "name","SurfaceX", i);
                    cout << "|| " << surfaceName << endl;
                    
                    settings2.pushTag("surface",i);
                    int pointsCount = settings2.getNumTags("controlPoint");
                    
                    for (int j=0; j<pointsCount; j++) {
                        int x = ofToInt(settings2.getAttribute("controlPoint", "x", "99", j));
                        int y = ofToInt(settings2.getAttribute("controlPoint", "y", "99", j));
                        
                        cout << "|| " << x << endl;
                    }
                    
                    //cout << "|| " << settings2.getValue("a:valor", 99, i) << endl;
                    settings2.popTag();
                }
            }
            settings2.popTag();
            settings2.popTag(); // BACK TO: BEFORE settings (ROOT)

            
        }
        
        
        // LOAD SURFACES - END
        
        
        
        return true;
	}else{
        return false;
    }
}

void ofApp::loadMappingData(){
    
    settings.load("settings.csv", ",");
    vector<GLfloat> bezierPoints;
    
    for (int i=0; i<settings.getNumRows(); i++) {
        ofxCsvRow currentRow = settings.getRow(i);
        
        cout << ofToString(currentRow.getData()) << endl;
        
        bezierPoints.push_back(currentRow.getFloat(0));
        bezierPoints.push_back(currentRow.getFloat(1));
        bezierPoints.push_back(currentRow.getFloat(2));
    }
    
    std::size_t const half_size = bezierPoints.size() / 2;
    std::vector<GLfloat> split_low(bezierPoints.begin(), bezierPoints.begin() + half_size);
    std::vector<GLfloat> split_hi(bezierPoints.begin() + half_size, bezierPoints.end());
    
    videoSurface[0].setControlPoints(split_low);
    videoSurface[1].setControlPoints(split_hi);
    
}
void ofApp::saveMappingData(){
    
    for(int i=0; i < videoSurface[0].getControlPoints().size(); i+=3){
        
        ofxCsvRow currentRow;
        currentRow.addInt(videoSurface[0].getControlPoints()[i+0]);
        currentRow.addInt(videoSurface[0].getControlPoints()[i+1]);
        currentRow.addInt(videoSurface[0].getControlPoints()[i+2]);
        settings.setRow(i / 3, currentRow);
    }
    
    for(int i=0; i < videoSurface[1].getControlPoints().size(); i+=3){
        
        ofxCsvRow currentRow;
        currentRow.addInt(videoSurface[1].getControlPoints()[i+0]);
        currentRow.addInt(videoSurface[1].getControlPoints()[i+1]);
        currentRow.addInt(videoSurface[1].getControlPoints()[i+2]);
        settings.setRow((i / 3) + 6, currentRow);
    }
    
    settings.save();

    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'c' || key == 'C'){
        calibrationMode = !calibrationMode;
        selectedSurface = 0;
    }
    
    if(key == ' '){
        if (video.isPaused()) {
            video.play();
        } else{
            video.setPaused(true);
        }
    }
    
    if(key == 'q'){
        video.setFrame(video.getCurrentFrame() - 500);
    }
    if(key == 'w'){
        video.setFrame(video.getCurrentFrame() + 500);
    }
    
    if(key == '1'){
        selectedSurface = 0;
    }
    if(key == '2'){
        selectedSurface = 1;
    }
    
    if (key == 's') {
        saveMappingData();
    }
    
    switch (key) {
        case 'w':
            //bUseWarp = !bUseWarp;
            break;
        case 'r':
            //warp.resetWarpGrid();
            break;
        case 'k':
            videoSurface[0].toggleShowWarpGrid();
            break;
        case 'l':
            videoSurface[1].toggleShowWarpGrid();
            //warp.setWarpGridPosition(100, 100, (ofGetWidth() - 200), (ofGetHeight() - 200));
            break;
        case OF_KEY_UP:
            //warp.setWarpGrid(warp.getNumXPoints(), warp.getNumYPoints() + 1);
            break;
        case OF_KEY_RIGHT:
            //warp.setWarpGrid(warp.getNumXPoints() + 1, warp.getNumYPoints());
            break;
        case OF_KEY_DOWN:
            //warp.setWarpGrid(warp.getNumXPoints(), warp.getNumYPoints() - 1);
            break;
        case OF_KEY_LEFT:
            //warp.setWarpGrid(warp.getNumXPoints() - 1, warp.getNumYPoints());
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
