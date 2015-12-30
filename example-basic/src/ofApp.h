#pragma once

#include "ofMain.h"
#include "ofxHT16K33.h"

class ofApp : public ofBaseApp{
	
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxHT16K33 driver;
    int updateSplit;
    int updateCount;
    
    ofImage image;
    int capW = 640;
    int capH = 640;
    
    int circleX = 0;
    int circleY = 0;
    float circleDX = 0;
    float circleDY = 0;
    float circleTX = 0;
    float circleTY = 0;
    int circleRad = 120;
    
    bool bMousePress;
    
    unsigned char * pixels;
    bool bGetPixels = false;
};

