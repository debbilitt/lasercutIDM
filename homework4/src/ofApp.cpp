#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mGui.setup("Control Booth");
    mJitterSlider.setup("Control Jitter",0.0f, 0.0f, 5.0f);
    iSlider.setup("I",0.0f, 0.0f, 5.0f);
    heartSlider.setup("<3",0.0f, 0.0f, 5.0f);
    dSlider.setup("D",0.0f, 0.0f, 5.0f);
    mSlider.setup("M",0.0f, 0.0f, 5.0f);
    
    mJitterSlider.addListener(this, &ofApp::onChangeJitter);
    
    mGui.add(&mJitterSlider);
    mGui.add(&iSlider);
    mGui.add(&heartSlider);
    mGui.add(&dSlider);
    mGui.add(&mSlider);
    
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
    
    mGui.draw();
    //    font.drawString("I <3 DM", 150, 150);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    jitter.draw();
    ofPopMatrix();
    
    if( savePDF ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }
    
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
