//
//  ofxHT16K33.h
//  ------------------------
//
//  Created by hisahayashi on 2015/12/27.
//  Copyright (c) 2015 hisahayashi.
//

#ifndef __emptyExample__ofxHT16K33__
#define __emptyExample__ofxHT16K33__

#include "ofMain.h"

#define DEBUG 1
#define X_SIZE 8
#define Y_SIZE 16
#define LED_SIZE X_SIZE * Y_SIZE

class ofxHT16K33 {
    
public:
    void setup();
    void update();
    void draw();
    void clear(int id);
    void drawPixels(int x, int y, int id);
    void drawAll(int id);
    
    bool bWrite;
    int updateSplit = 3;
    
private:
    void setupArduino();
    void updateSerial();
    
    // serial
    ofSerial serial;
    bool bSetupArduino;
    
    string writer;
    
    char bytesRead[3];
    char bytesReadString[4];
    int nBytesRead;
    int nTimesRead;
    float readTime;
    int updateCount = 0;
};

#endif /* defined(__emptyExample__ofxHT16K33__) */
