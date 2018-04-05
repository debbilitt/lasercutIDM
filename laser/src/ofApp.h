#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
    void numLinesChanged(int & newNumLines);
    void randGridSizeChanged(int & newRandGridSize);
    
    void drawRandomLines();
    void drawGridLines();
    void drawSquareGrid();
    void drawRandomGrid();
    void drawDiamondGrid();
    
    ofTrueTypeFont font;
    ofxPanel mGui;
    ofxFloatSlider mJitterSlider;
    
    int toggledKey;
    
    ofxToggle mask;
    
    
    //four sliders controlling each letter
    ofxToggle randLines;
    ofxIntSlider numLines;
    ofxToggle grid;
    ofxFloatSlider gridSize;
    ofxToggle sqGrid;
    ofxFloatSlider sqGridSize;
    ofxFloatSlider sqCellSize;
    ofxToggle diamond;
    ofxFloatSlider diamondSize;
    ofxToggle randGrid;
    ofxIntSlider randGridSize;
    
    ofPolyline lines;
    
    vector<ofPoint> points;
    
    bool savePDF;
    
    bool drawGrid;
    
    
    
};
