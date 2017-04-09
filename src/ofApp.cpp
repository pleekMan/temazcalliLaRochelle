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
    
    videoTop.allocate(videoSize, videoSize / 2);
    videoTop.begin();
    ofClear(0);
    videoTop.end();
    
    videoBottom.allocate(videoSize, videoSize / 2);
    videoBottom.begin();
    ofClear(0);
    videoBottom.end();
    
    selectedKeystone = 0;
    currentPoint = 0;
    moveStep = 1;
    
    calibrationMode = true;
    positionY = 0;
    
    keystoneLayers[0].setTexture(videoTop.getTexture());
    keystoneLayers[1].setTexture(videoBottom.getTexture());

    loadKeystoneData();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //if(positionMode){
        //ofPoint selectedPoint = keystoneLayers[selectedKeystone].getPoint(currentPoint);
      //  keystoneLayers[selectedKeystone].setPoint(currentPoint, ofGetMouseX(), ofGetMouseY());
    //}
    
    video.update();
    
    videoTop.begin();
    ofClear(0);
    video.draw(0, 0, videoSize, videoSize);
    
    if (calibrationMode) {
        ofSetColor(255);
        for (int i=0; i < 10; i++) {
            ofDrawLine(i * (videoTop.getWidth() / 10.0), 0, i * (videoTop.getWidth() / 10.0), videoTop.getHeight());
            ofDrawLine(0,i * (videoTop.getHeight() / 10.0), videoTop.getWidth(), i * (videoTop.getHeight() / 10.0));

        }
        
        ofFill();
        ofDrawRectangle(videoTop.getWidth() * 0.5, videoTop.getHeight() * 0.5, 50, 200);
    }
    videoTop.end();
    
    videoBottom.begin();
    ofClear(0);
    video.draw(0, -(videoSize / 2), videoSize, videoSize);
    
    if (calibrationMode) {
        ofSetColor(255);
        for (int i=0; i < 10; i++) {
            ofDrawLine(i * (videoTop.getWidth() / 10.0), 0, i * (videoTop.getWidth() / 10.0), videoTop.getHeight());
            ofDrawLine(0,i * (videoTop.getHeight() / 10.0), videoTop.getWidth(), i * (videoTop.getHeight() / 10.0));
            
        }
        
        ofFill();
        ofDrawRectangle(videoTop.getWidth() * 0.5, videoTop.getHeight() * 0.5, 50, 200);
        ofDrawRectangle(videoTop.getWidth() * 0.5 + 60, videoTop.getHeight() * 0.5, 50, 200);

    }
    
    videoBottom.end();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // IMPORTANT!!
    // USING 2 FULLHD PROJECTORS + COMPUTER DISPLAY (900px HEIGHT)
    // VIDEOSIZE IS FULLHD WIDTH.
    // PLACING THE VIDEO VERTICALLY IS = computerDisplayHeight + ((2projectorsHeight - videoSize) * halfOfThat)
    
    ofSetColor(255);
    
    //ofTranslate(200, 200);
    //ofScale(0.5, 0.5);
    keystoneLayers[0].draw();
    
    //ofTranslate(200, 200);
    keystoneLayers[1].draw();
    
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
    
}

void ofApp::loadKeystoneData(){
    
    settings.load("settings.csv", ",");
    for (int i=0; i<settings.getNumRows(); i++) {
        ofxCsvRow currentRow = settings.getRow(i);
        cout << ofToString(currentRow.getData()) << endl;
        
        if(i < 4){
            keystoneLayers[0].setPoint(i % 4, currentRow.getInt(0), currentRow.getInt(1));
        } else {
            keystoneLayers[1].setPoint(i % 4, currentRow.getInt(0), currentRow.getInt(1));
            
        }
    }

    
}
void ofApp::saveKeystoneData(){
    
    for (int i=0; i<8; i++) {
        ofxCsvRow currentRow;
        if (i<4) {
            currentRow.addInt(keystoneLayers[0].getPoint(i%4).x);
            currentRow.addInt(keystoneLayers[0].getPoint(i%4).y);
        } else {
            currentRow.addInt(keystoneLayers[1].getPoint(i%4).x);
            currentRow.addInt(keystoneLayers[1].getPoint(i%4).y);
        }
        
        settings.setRow(i, currentRow);
    }
    
    settings.save();
    
    
}

void ofApp::moveLeft(){
    ofPoint c = keystoneLayers[selectedKeystone].getPoint(currentPoint);
    keystoneLayers[selectedKeystone].setPoint(currentPoint, c.x-moveStep, c.y);
}
void ofApp::moveRight(){
    ofPoint c = keystoneLayers[selectedKeystone].getPoint(currentPoint);
    keystoneLayers[selectedKeystone].setPoint(currentPoint, c.x+moveStep, c.y);
}
void ofApp::moveUp(){
    ofPoint c = keystoneLayers[selectedKeystone].getPoint(currentPoint);
    keystoneLayers[selectedKeystone].setPoint(currentPoint, c.x, c.y-moveStep);
}
void ofApp::moveDown(){
    ofPoint c = keystoneLayers[selectedKeystone].getPoint(currentPoint);
    keystoneLayers[selectedKeystone].setPoint(currentPoint, c.x, c.y+moveStep);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'c'){
        calibrationMode = !calibrationMode;
        selectedKeystone = 0;
    }
    
    if(key == ' '){
        if (video.isPaused()) {
            video.setPaused(false);
            video.play();
        } else{
            video.setPaused(true);
            video.play();
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
        selectedKeystone = 0;
    }
    if(key == '2'){
        selectedKeystone = 1;
    }
    
    if (key == 's') {
        saveKeystoneData();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    switch(key){
        case OF_KEY_RETURN:
            currentPoint = (currentPoint+1) % 4;
            break;
        case OF_KEY_LEFT:
            moveLeft();
            break;
        case OF_KEY_RIGHT:
            moveRight();
            break;
        case OF_KEY_UP:
            moveUp();
            break;
        case OF_KEY_DOWN:
            moveDown();
            // cout << ofToString(keystoneLayers[selectedKeystone].getPoint(currentPoint)) << endl;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(positionMode){
       ofPoint selectedPoint = keystoneLayers[selectedKeystone].getPoint(currentPoint);
       keystoneLayers[selectedKeystone].setPoint(currentPoint, ofGetMouseX(), ofGetMouseY());
    }
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
