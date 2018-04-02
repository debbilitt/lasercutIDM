#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mGui.setup("Control Booth");
//    mJitterSlider.setup("Control Jitter",0.0f, 0.0f, 5.0f);

    randLines.setup("Random Lines");
    grid.setup("Grid");
    sqGrid.setup("Square Grid");
    diamond.setup("Diamonds");
    
    randLines.addListener(this, &ofApp::linesPressed);
    grid.addListener(this, &ofApp::gridPressed);
    sqGrid.addListener(this, &ofApp::sqGridPressed);
    diamond.addListener(this, &ofApp::diamondPressed);

    
    mGui.add(&randLines);
    mGui.add(&grid);
    mGui.add(&sqGrid);
    mGui.add(&diamond);


    //load a custom font
    //the ttf file must be inside your bin/data directory
    font.load("BreeSerif-Regular.ttf", 100, true, false, true);
    
    savePDF = false;


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
 
    if( savePDF ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }
    
    mGui.draw();
//    font.drawString("I <3 DM", 150, 150);

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    ofFill();
    ofSetColor(ofColor::white);
//    jitter.draw();
    
    
    /* Draw grid lines*/
    
    if(drawGrid){
        ofSetLineWidth(1.0);
        ofSetColor(0);
        ofNoFill();
        
        for (int i = 0; i < ofGetWidth(); i += 13) {
            for (int j = 0; j < ofGetHeight(); j += 13) {
                ofDrawRectangle(i, j, 13, 13);
            }
        }
    }
    
    
    /*Draw Polyline of Letters*/
    
    vector < ofTTFCharacter > iPaths = font.getStringAsPoints("I");
    vector < ofTTFCharacter > heartPaths = font.getStringAsPoints("<3");
    vector < ofTTFCharacter > dPaths = font.getStringAsPoints("D");
    vector < ofTTFCharacter > mPaths = font.getStringAsPoints("M");
   
    ofPushMatrix();
    ofTranslate(50, 0);
    for (int i = 0; i < iPaths.size(); i++) {
    
    	// for every character break it out to polylines
    
    	vector <ofPolyline> polylines = iPaths[i].getOutline();
    
    	for (int j = 0; j < polylines.size(); j++) {
    		polylines[j].draw();
    	}
    }
    ofPopMatrix();
    
    ofPushMatrix();
      ofTranslate(125, 0);
    for (int i = 0; i < heartPaths.size(); i++) {
        
        // for every character break it out to polylines
        
        vector <ofPolyline> polylines = heartPaths[i].getOutline();
        
        for (int j = 0; j < polylines.size(); j++) {
            polylines[j].draw();
        }
    }
    
     ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(50, 125);
    for (int i = 0; i < dPaths.size(); i++) {
        
        // for every character break it out to polylines
        
        vector <ofPolyline> polylines = dPaths[i].getOutline();
        
        for (int j = 0; j < polylines.size(); j++) {
            polylines[j].draw();
        }
    }
    
     ofPopMatrix();
    ofPushMatrix();
     ofTranslate(150, 125);
    for (int i = 0; i < mPaths.size(); i++) {
        
        // for every character break it out to polylines
        
        vector <ofPolyline> polylines = mPaths[i].getOutline();
        
        for (int j = 0; j < polylines.size(); j++) {
            polylines[j].draw();
        }
    }
    ofPopMatrix();

    ofPopMatrix();
    
    
    
    /* Draw rectangle grid */
 
//    if() {
//        ofSetLineWidth(1.0);
//        ofSetColor(0);
//        ofNoFill();
//        for (int i = 0; i < ofGetWidth(); i += 10) {
//            for (int j = 0; j < ofGetHeight(); j += 10) {
//                ofDrawRectangle(i, j, 5, 5);
//            }
//        }
//        
//    }
    
  
    
    /* Draw triangular lines*/
    //ofSetLineWidth(1.0);
    //ofSetColor(0);
    //ofNoFill();
    //
    //ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    /*for (int i = 0; i < ofGetHeight(); i += 20) {
     ofDrawLine(0, i - 4, ofGetWidth(), i - 4);
     }*/
    
    /*ofPushMatrix();
     ofTranslate(300,0);
     ofRotate(45);
     
     for (int i = -500; i < ofGetHeight() + 500; i += 20) {
     ofDrawLine(-500, i, ofGetWidth() + 500, i);
     }
     ofPopMatrix();
     
     ofPushMatrix();
     ofTranslate(0, -300);
     ofRotate(-45);
     
     for (int i = -500; i < ofGetHeight() + 500; i += 20) {
     ofDrawLine(-500, i, ofGetWidth() + 500, i);
     }
     ofPopMatrix();
     */

    

    if( savePDF ){
        ofEndSaveScreenAsPDF();
        savePDF = false;
    }
    
    
}




//--------------------------------------------------------------
void ofApp::onChangeJitter(float & newJitterValue){
    jitter.clear();
    // get the string as paths
    vector < ofTTFCharacter > paths = font.getStringAsPoints("I <3 DM");
    
    for (int i = 0; i < paths.size(); i++){
        
        // for every character break it out to polylines
        
        vector <ofPolyline> polylines = paths[i].getOutline();
        
        //looping through polylines
        
        for (int j = 0; j < polylines.size(); j++){
            // for (int k = 0; k < polylines[j].size(); k++){
            //  ofDrawCircle( polylines[j][k], 1);
            
   //resampling polylines to space out along shape of letter
            ofPolyline p = polylines[j].getResampledBySpacing(5);
            
            vector <ofPoint> points = p.getVertices();
            
            ofLog(OF_LOG_NOTICE, ofToString(points.size()));
            
            for (auto &v : points) {
                v.x+=ofRandom(-newJitterValue,newJitterValue);
                v.y+=ofRandom(-newJitterValue,newJitterValue);
                
                jitter.lineTo(v);
                
            }
            
            jitter.close();
        }
    }

    
}

//--------------------------------------------------------------
void ofApp::linesPressed(){
    
    /* Draw random lines */
    
    ofPolyline p;
    p.clear();
    for (int i = 0; i < 100; i++) {
        ofPoint x = ofPoint(ofRandom(50, ofGetWidth()), ofRandom(50, ofGetHeight()));
        ofPoint y = ofPoint(ofRandom(50, ofGetWidth()), ofRandom(50, ofGetHeight()));
        p.lineTo(x);
    }
    
    
    
    
}
//--------------------------------------------------------------
void ofApp::gridPressed(){
    
     drawGrid == true;

    
    
    
}
//--------------------------------------------------------------
void ofApp::sqGridPressed(){
    
    
    
}
//--------------------------------------------------------------
void ofApp::diamondPressed(){
    
    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
        if(key == 's') {
    
            savePDF = true;
            ofEndSaveScreenAsPDF();
           
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
