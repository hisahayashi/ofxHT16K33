//
//  ofxHT16K33.cpp
//  ------------------------
//
//  Created by hisahayashi on 2015/12/27.
//  Copyright (c) 2015 hisahayashi.
//

#include "ofxHT16K33.h"

//--------------------------------------------------------------
void ofxHT16K33::setup(){
    
    // Get serial port
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    string deviceLine, serialID;
    
    // Get port name
    for( int i = 0; i < deviceList.size(); i++ ){
        deviceLine = deviceList[i].getDeviceName().c_str();
        
        if( deviceLine.substr(0,12) == "tty.usbmodem" ){
            serialID = "/dev/" + deviceLine;
            ofLog() << "Arduino serial = " << serialID << endl;
        }
    }
    
    // Connect to Arduino
    serial.setup(serialID, 115200);
    
    bWrite = false;
    updateSplit = 6;
    updateCount = 1;
    
    // Initialize the parameter
    bSetupArduino = false;
}

//--------------------------------------------------------------
void ofxHT16K33::setupArduino(){
     ofLog() << "ofSerial Setup";
    
    // Connected flag
    bSetupArduino = true;
}

//--------------------------------------------------------------
void ofxHT16K33::update(){
    
    if( serial.isInitialized() && !bSetupArduino ){
        setupArduino();
    }
    
    // Connected process
    if( bSetupArduino ){
//        if(updateCount % updateSplit == 0){
//            ofLog() << updateCount;
            updateSerial();
//        }
        updateCount++;
    }
}

//--------------------------------------------------------------
void ofxHT16K33::updateSerial(){
    
    string writerSerial = "";
    int splitSize = 125;
    
    if(writer.length() > splitSize){
        int length = 0;
        vector <string> lengthCheck = ofSplitString(writer, "H");
        
        for(int i = 0; i < lengthCheck.size(); i++){
            length += lengthCheck[i].length() + 1;
            if(length >= 125){
                splitSize = length - 1;
                break;
            }
        }
        
//        ofLog() << "splitSize: " << splitSize;
        writerSerial = writer.substr(0, splitSize);
        writer = writer.substr(splitSize);
        
        bWrite = false;
    }
    else{
        writerSerial = writer;
        writer = "";
        
        writerSerial += "/0";
        bWrite = true;
    }
    
//    ofLog() << "writerSerial: " << writerSerial << ", length: " << writer.length();
    
    unsigned char* writeByte = (unsigned char*) writerSerial.c_str();
    int result = serial.writeBytes(writeByte, writerSerial.length() + 1);
    

    nTimesRead = 0;
    nBytesRead = 0;
    int nRead  = 0;
    
    unsigned char bytesReturned[3];
    
    memset(bytesReadString, 0, 4);
    memset(bytesReturned, 0, 3);
    
    while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
        nTimesRead++;
        nBytesRead = nRead;
    };
    
    memcpy(bytesReadString, bytesReturned, 3);
    
    readTime = ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofxHT16K33::draw(){
    
    if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
        ofSetColor(0);
    } else {
        ofSetColor(160);
    }
    string msg;
    msg += "nBytes read " + ofToString(nBytesRead) + "\n";
    msg += "nTimes read " + ofToString(nTimesRead) + "\n";
    msg += "read: " + ofToString(bytesReadString) + "\n";
    msg += "(at time " + ofToString(readTime, 3) + ")";
    ofDrawBitmapString(msg, 20, 30);
    
}

//--------------------------------------------------------------
void ofxHT16K33::clear(int id){
    writer = "";
}

//--------------------------------------------------------------
void ofxHT16K33::drawAll(int id){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 8; j++){
            drawPixels(j, i, id);
        }
    }
}

//--------------------------------------------------------------
void ofxHT16K33::drawPixels(int x, int y, int id){
    int idNumber = id * LED_SIZE;
    int number = (y * X_SIZE + x) + idNumber;
    writer += "H" + ofToString(number);
    //    ofLog() << number;
}