#include "ofApp.h"

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
    //ratio = video.getHeight() / ofGetWindowHeight();
    
    /*
    videoTop.allocate(videoSize, videoSize / 2);
    videoTop.begin();
    ofClear(0);
    videoTop.end();
    
    videoBottom.allocate(videoSize, videoSize / 2);
    videoBottom.begin();
    ofClear(0);
    videoBottom.end();
     */
    
    selectedSurface = 0;
    moveStep = 1;
    
    calibrationMode = true;
    
    
    //-----------
    
    videoSurface[0].allocate(videoSize, videoSize / 2, 3, 2, 100);
    videoSurface[1].allocate(videoSize, videoSize / 2, 3, 2, 100);
    
    
    cout << ofToString(videoSurface[0].getControlPoints()) << endl;
    
    //vector<GLfloat> bezierPoints1;
    vector<GLfloat> bezierPoints2;
    
    loadMappingData();
    
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
    //videoSurface[0].setShowWarpGrid(true);

    
    videoSurface[1].begin();
        video.draw(0, -(videoSize / 2), videoSize, videoSize);
    videoSurface[1].end();

    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // IMPORTANT!!
    // USING 2 FULLHD PROJECTORS + COMPUTER DISPLAY (900px HEIGHT)
    // VIDEOSIZE IS FULLHD WIDTH.
    // PLACING THE VIDEO VERTICALLY IS = computerDisplayHeight + ((2projectorsHeight - videoSize) * halfOfThat)
    
    
    for (int i=0; i<2; i++) {
        videoSurface[i].draw();
    }
 
    /*
    if (calibrationMode) {
        
        if(positionMode){
            ofDrawBitmapString("POSITION MODE", 200, 20);
        }
        ofNoFill();
        ofDrawCircle(keystoneLayers[selectedKeystone].getPoint(currentPoint), 10);
        ofDrawCircle(keystoneLayers[selectedKeystone].getPoint(currentPoint), 5);
        
        ofDrawBitmapString(currentPoint, keystoneLayers[selectedKeystone].getPoint(currentPoint) + ofPoint(10,10));

        
        ofDrawBitmapString("x:" + ofToString(ofGetMouseX()) + " | y: " + ofToString(ofGetMouseY()), ofGetMouseX(), ofGetMouseY());
        ofDrawBitmapString("FR:" + ofToString(ofGetFrameRate()) + "\nSELECTED KEYSTONE: " + ofToString(selectedKeystone), 20,20);
        
        ofDrawBitmapString("SURFACE 1:\n" + ofToString(keystoneLayers[0].getPoint(0)) + "\n" + ofToString(keystoneLayers[0].getPoint(1)) + "\n" + ofToString(keystoneLayers[0].getPoint(2)) + "\n" + ofToString(keystoneLayers[0].getPoint(3)), 10, 100);
        
        ofDrawBitmapString("SURFACE 2:\n" + ofToString(keystoneLayers[1].getPoint(0)) + "\n" + ofToString(keystoneLayers[1].getPoint(1)) + "\n" + ofToString(keystoneLayers[1].getPoint(2)) + "\n" + ofToString(keystoneLayers[1].getPoint(3)), 10, 100);

    }
     */

    
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
    std::vector<GLfloat> split_lo(bezierPoints.begin(), bezierPoints.begin() + half_size);
    std::vector<GLfloat> split_hi(bezierPoints.begin() + half_size, bezierPoints.end());
    
    videoSurface[0].setControlPoints(split_lo);
    videoSurface[1].setControlPoints(split_hi);
    
}
void ofApp::saveMappingData(){
    
    /*
    vector<float> bezierPoints;
    
    bezierPoints.insert( bezierPoints.end(), videoSurface[0].getControlPoints().begin(), videoSurface[0].getControlPoints().end() );
    bezierPoints.insert( bezierPoints.end(), videoSurface[1].getControlPoints().begin(), videoSurface[1].getControlPoints().end() );
    
    cout << "--- SAVE DATA STRUCTURE\n" << ofToString(bezierPoints) << endl;
    */
    
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

    
    /*
    for (int i=0; i<8; i++) {
        ofxCsvRow currentRow;
        
            currentRow.addInt(keystoneLayers[0].getPoint(i%4).x);
            currentRow.addInt(keystoneLayers[0].getPoint(i%4).y);

        
        settings.setRow(i, currentRow);
    }
    
    */
    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'c'){
        calibrationMode = !calibrationMode;
        selectedSurface = 0;
    }
    
    if(key == ' '){
        if (video.isPaused()) {
            //video.setPaused(false);
            video.play();
        } else{
            video.setPaused(true);
            //video.play();
        }
    }
    
    if(key == 'q'){
        //video.setFrame(video.getCurrentFrame() - 500);
    }
    if(key == 'w'){
        video.setFrame(video.getCurrentFrame() + 500);
    }
    
    if(key == 'p'){
        positionMode = !positionMode;
        //selectedKeystone = 0;
        //currentPoint = 0;
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
    /*
    if(positionMode){
       ofPoint selectedPoint = keystoneLayers[selectedKeystone].getPoint(currentPoint);
       keystoneLayers[selectedKeystone].setPoint(currentPoint, ofGetMouseX(), ofGetMouseY());
    }
     */
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
