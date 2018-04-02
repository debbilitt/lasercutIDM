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
   
    void onChangeJitter(float & newJitterValue);
     void linesPressed();
     void gridPressed();
     void sqGridPressed();
     void diamondPressed();
    
    
        ofTrueTypeFont font;
        ofxPanel mGui;
        ofxFloatSlider mJitterSlider;
    
    
   //four sliders controlling each letter
        ofxButton randLines;
        ofxButton grid;
        ofxButton sqGrid;
        ofxButton diamond;
    
        ofPolyline jitter;
    
    bool savePDF;
    
    bool drawGrid;
    

		
};
