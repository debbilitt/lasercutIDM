#include "ofApp.h"

ofFbo letterFillFbo;
ofFbo backgroundFbo;

//--------------------------------------------------------------
void ofApp::setup(){
    
    numLines.addListener(this, &ofApp::numLinesChanged);
    randGridSize.addListener(this, &ofApp::randGridSizeChanged);
    
    mGui.setup("Control Booth");
    mask.setup("Mask", false);
    randLines.setup("Random Lines", false);
    numLines.setup("Number of Lines", 500, 0, 5000);
    grid.setup("Grid", false);
    gridSize.setup("GridSize", 15.0, 5.0, 30.0);
    sqGrid.setup("Square Grid", false);
    sqGridSize.setup("Square Grid Size", 15.0, 5.0, 30.0);
    sqCellSize.setup("Square Cell Size", 0.5, 0.0, 1.0);
    diamond.setup("Diamonds", false);
    diamondSize.setup("Diamond Size", 20.0, 10.0, 30.0);
    randGrid.setup("Random Grid", false);
    randGridSize.setup("Random Grid Size", 10, 5, 20);
    
    mGui.add(&mask);
    mGui.add(&randLines);
    mGui.add(&numLines);
    mGui.add(&grid);
    mGui.add(&gridSize);
    mGui.add(&sqGrid);
    mGui.add(&sqGridSize);
    mGui.add(&sqCellSize);
    mGui.add(&diamond);
    mGui.add(&diamondSize);
    mGui.add(&randGrid);
    mGui.add(&randGridSize);
    
    //load a custom font
    //the ttf file must be inside your bin/data directory
    font.load("BreeSerif-Regular.ttf", 500, true, false, true);
    
    savePDF = false;
    
    lines.clear();
    
    ofSetLineWidth(1.0);
    ofSetColor(0);
    ofFill();
    
    for (int i = 0; i < 500; i++) {
        ofPoint x = ofPoint(ofRandom(-ofGetWidth() * 5, ofGetWidth() * 5), ofRandom(-ofGetHeight() * 5, ofGetHeight() * 5));
        ofPoint y = ofPoint(ofRandom(-ofGetWidth() * 5, ofGetWidth() * 5), ofRandom(-ofGetHeight() * 5, ofGetHeight() * 5));
        lines.lineTo(x);
    }
    
    int space = 10;
    for (int x = 0; x < ofGetWidth(); x += space) {
        for (int y = 0; y < ofGetHeight(); y += space) {
            int r = int(ofRandom(0, 3));
            if (r == 2) {
                ofPoint p1 = ofPoint(x, y);
                ofPoint p2 = ofPoint(x + space, y + space);
                points.push_back(p1);
                points.push_back(p2);
            }
            else if (r == 1) {
                ofPoint p1 = ofPoint(x, y + space);
                ofPoint p2 = ofPoint(x + space, y);
                points.push_back(p1);
                points.push_back(p2);
            }
            else continue;
        }
    }
    
    letterFillFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    letterFillFbo.begin();
    ofClear(255, 255, 255, 0);
    letterFillFbo.end();
    
    backgroundFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    backgroundFbo.begin();
    ofClear(255, 255, 255, 0);
    backgroundFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /* Start PDF Save */
    if( savePDF ) ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    
    /* Clear background FBO */
    backgroundFbo.begin();
    ofClear(255, 255, 255, 0);
    backgroundFbo.end();
    
    /* Draw pattern onto background FBO */
    backgroundFbo.begin();
    
    if(randLines) drawRandomLines();
    if(grid) drawGridLines();
    if(sqGrid) drawSquareGrid();
    if (diamond) drawDiamondGrid();
    if (randGrid) drawRandomGrid();
    
    backgroundFbo.end();
    
    /* Set mask. */
    
    if (mask) {
        letterFillFbo.getTexture().setAlphaMask(backgroundFbo.getTexture());
        letterFillFbo.draw(0, 0);
    }
    else {
        backgroundFbo.draw(0, 0);
    }
    
    /* Draw Polyline of Letters */
    
    string s = ofToString((char)toggledKey);
    vector < ofTTFCharacter > fontPaths = font.getStringAsPoints(s);
    ofRectangle s_bbox = font.getStringBoundingBox(s, 0, 0);
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2 - s_bbox.width / 2, ofGetHeight() / 2 + s_bbox.height / 2);
    ofFill();
    ofSetColor(ofColor::black);
    ofSetLineWidth(3.0);
    for (int i = 0; i < fontPaths.size(); i++) {
        vector <ofPolyline> polylines = fontPaths[i].getOutline();
        for (int j = 0; j < polylines.size(); j++) {
            polylines[j].draw();
        }
    }
    ofPopMatrix();
    
    /* End PDF Save*/
    if( savePDF ){
        ofEndSaveScreenAsPDF();
        savePDF = false;
    }
    
    /* Draw GUI */
    mGui.draw();
}

/* BACKGROUND PATTERNS */

void ofApp::drawRandomLines() {
    ofPushMatrix();
    ofSetLineWidth(1.0);
    ofSetColor(0);
    lines.draw();
    ofPopMatrix();
}

void ofApp::drawGridLines() {
    ofPushMatrix();
    ofSetLineWidth(1.0);
    ofSetColor(0);
    ofNoFill();
    
    for (int i = 0; i < ofGetWidth(); i += gridSize) {
        for (int j = 0; j < ofGetHeight(); j += gridSize) {
            ofDrawRectangle(i, j, gridSize, gridSize);
        }
    }
    ofPopMatrix();
}

void ofApp::drawSquareGrid() {
    ofPushMatrix();
    ofSetLineWidth(1.0);
    ofSetColor(0);
    ofNoFill();
    for (int i = 0; i < ofGetWidth(); i += sqGridSize) {
        for (int j = 0; j < ofGetHeight(); j += sqGridSize) {
            ofDrawRectangle(i, j, sqGridSize * sqCellSize, sqGridSize * sqCellSize);
        }
    }
    ofPopMatrix();
}

void ofApp::drawRandomGrid() {
    ofPushMatrix();
    for (int i = 0; i < points.size(); i += 2) {
        ofPoint pt1 = points.at(i);
        ofPoint pt2 = points.at(i + 1);
        ofSetLineWidth(1.0);
        ofLine(pt1, pt2);
    }
    ofPopMatrix();
}

void ofApp::drawDiamondGrid() {
    ofPushMatrix();
    ofSetLineWidth(1.0);
    ofSetColor(0);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotate(45);
    ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
    for (int i = 0; i < ofGetHeight(); i += diamondSize) {
        ofDrawLine(0, i, ofGetWidth(), i);
    }
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotate(-45);
    ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
    for (int i = 0; i < ofGetHeight(); i += diamondSize) {
        ofDrawLine(0, i, ofGetWidth(), i);
    }
    ofPopMatrix();
    ofPopMatrix();
}

/* Callback Functions for Pattern Changes    */
void ofApp::randGridSizeChanged(int & newRandGridSize) {
    points.clear();
    
    int space = newRandGridSize;
    for (int x = 0; x < ofGetWidth(); x += space) {
        for (int y = 0; y < ofGetHeight(); y += space) {
            int r = int(ofRandom(0, 3));
            if (r == 2) {
                ofPoint p1 = ofPoint(x, y);
                ofPoint p2 = ofPoint(x + space, y + space);
                points.push_back(p1);
                points.push_back(p2);
            }
            else if (r == 1) {
                ofPoint p1 = ofPoint(x, y + space);
                ofPoint p2 = ofPoint(x + space, y);
                points.push_back(p1);
                points.push_back(p2);
            }
            else continue;
        }
    }
}

void ofApp::numLinesChanged(int & newNumLines) {
    
    lines.clear();
    
    ofSetLineWidth(1.0);
    ofSetColor(0);
    ofFill();
    
    for (int i = 0; i < newNumLines; i++) {
        ofPoint x = ofPoint(ofRandom(-ofGetWidth() * 5, ofGetWidth() * 5), ofRandom(-ofGetHeight() * 5, ofGetHeight() * 5));
        ofPoint y = ofPoint(ofRandom(-ofGetWidth() * 5, ofGetWidth() * 5), ofRandom(-ofGetHeight() * 5, ofGetHeight() * 5));
        lines.lineTo(x);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == '1') {
        savePDF = true;
        ofEndSaveScreenAsPDF();
    }
    
    if (key != '1') {
        toggledKey = key;
        string s = ofToString((char)key);
        vector < ofTTFCharacter > fontPaths = font.getStringAsPoints(s);
        ofRectangle s_bbox = font.getStringBoundingBox(s, 0, 0);
        letterFillFbo.begin();
        ofClear(255, 255, 255, 0);
        letterFillFbo.end();
        
        letterFillFbo.begin();
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2 - s_bbox.width / 2, ofGetHeight() / 2 + s_bbox.height / 2);
        
        ofPath path;
        for (int i = 0; i < fontPaths.size(); i++) {
            vector <ofPolyline> polylines = fontPaths[i].getOutline();
            for (int j = 0; j < polylines.size(); j++) {
                polylines[j].draw();
                for (int i = 0; i <  polylines[j].getVertices().size(); i++) {
                    if (i == 0) {
                        path.newSubPath();
                        path.moveTo(polylines[j].getVertices()[i]);
                    }
                    else {
                        path.lineTo(polylines[j].getVertices()[i]);
                    }
                }
                path.close();
                path.simplify();
            }
        }
        path.setStrokeWidth(5.0);
        path.setStrokeColor(ofColor::black);
        path.draw();
        
        ofFill();
        ofSetColor(ofColor::black);
        ofSetLineWidth(3.0);
        for (int i = 0; i < fontPaths.size(); i++) {
            vector <ofPolyline> polylines = fontPaths[i].getOutline();
            for (int j = 0; j < polylines.size(); j++) {
                polylines[j].draw();
            }
        }
        ofPopMatrix();
        letterFillFbo.end();
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
