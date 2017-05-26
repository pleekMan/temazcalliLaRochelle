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
    
 	//video.load("Temazcalli_FullDome_Final_1024x.mov");
	//video.setLoopState(OF_LOOP_NORMAL);
	//video.play();
    
    playing = true;
    videoSize = 1920;

    
    //selectedSurface = 0;
    moveStep = 1;
    stopWhenFinished = true;
    
    calibrationMode = true;
    
    
    font.load("FiraCode-Regular.ttf", 40);
    
    
    //-----------
    
    
    //videoSurface[0].allocate(videoSize, videoSize / 2, 3, 2, 100);
    //videoSurface[1].allocate(videoSize, videoSize / 2, 3, 2, 100);
    
    
    //cout << ofToString(videoSurface[0].getControlPoints()) << endl;
    
    //vector<GLfloat> bezierPoints1;
    //vector<GLfloat> bezierPoints2;
    
    //loadMappingData();
    //loadSettings();
    
    
    //----- LO NUEVO CON SURFACES
    settings.load("settings.xml");
    surfaceManager.init();
    surfaceManager.setFont(&font);
    surfaceManager.loadSettings(&settings);
    
    
    
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
    
    // NEW SURFACE SHIT
    surfaceManager.update();
    
    surfaceManager.drawBeginOnSurface(0);
    ofSetColor(0,ofRandom(255),0);
    
    ofDrawEllipse(320, 240, 50, 50);
    
    /*
    for (int i=0; i<20; i++) {
        float pos = (640 / 20.0) * i;
        ofDrawLine(pos, 0, 0, pos);
        ofDrawLine(0, 480 - pos, pos, 480);
    }
     */
    
    
    
    surfaceManager.drawEndOnSurface(0);
    
    //----------
    
    surfaceManager.drawBeginOnSurface(1);
    ofSetColor(0,0,ofRandom(255));
    ofDrawEllipse(320, 240, 50, 50);
    surfaceManager.drawEndOnSurface(1);
    
    
    
    // NEW SURFACE SHIT - END
    
    /*
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
    */
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // IMPORTANT!!
    // USING 2 FULLHD PROJECTORS + COMPUTER DISPLAY (900px HEIGHT APROX)
    // VIDEOSIZE IS FULLHD WIDTH.
    // PLACING THE VIDEO VERTICALLY IS = computerDisplayHeight + ((2projectorsHeight - videoSize) * halfOfThat)
    
    /*
    for (int i=0; i<2; i++) {
        videoSurface[i].draw();
    }
     */
    
    for (int i=0; i<surfaceManager.getSurfaceCount(); i++) {
        surfaceManager.render();
    }
    
    //ofPushStyle();
    //ofPopStyle();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(20,20));
    ofDrawBitmapString(ofToString(ofGetMouseX()) + " : " + ofToString(ofGetMouseY()), ofGetMouseX(), ofGetMouseY());
}


/*
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
 */


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    surfaceManager.keyPressed(key);
    
    if(key == 'c' || key == 'C'){
        calibrationMode = !calibrationMode;
        //selectedSurface = 0;
    }
    
    if(key == ' '){
        /*
        if (video.isPaused()) {
            video.play();
        } else{
            video.setPaused(true);
        }
         */
    }
    
    if(key == 'q'){
        //video.setFrame(video.getCurrentFrame() - 500);
    }
    if(key == 'w'){
        //video.setFrame(video.getCurrentFrame() + 500);
    }
    
    if(key == '1'){
        //selectedSurface = 0;
    }
    if(key == '2'){
        //selectedSurface = 1;
    }
    
    if (key == 's') {
        surfaceManager.saveSettings(&settings);
    }
    
    switch (key) {
        case 'w':
            //bUseWarp = !bUseWarp;
            break;
        case 'r':
            //warp.resetWarpGrid();
            break;
        case 'k':
            surfaceManager.toggleSurfaceGrid(0); // ESTO FREAKEA MAALL..!!
            break;
        case 'l':
            //videoSurface[1].toggleShowWarpGrid();
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
    surfaceManager.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    surfaceManager.mousePressed(x,y,button);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    surfaceManager.mouseReleased(x,y,button);
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
