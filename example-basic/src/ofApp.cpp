#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
    ofBackground(230);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    driver.setup();
    
    updateCount = 1;
    updateSplit = 1;
    image.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    circleDX = ofRandom(20) + 3;
    circleDY = ofRandom(20) + 3;
    circleX = 100;
    circleY = 100;
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    ofLog() << "bWrite: " << driver.bWrite;
    
    if(updateCount % updateSplit == 0){
        
        driver.update();
        
        if(driver.bWrite){
            
            if(bGetPixels){
                
                int w = image.width;
                int h = image.height;
                int stepW = w / (X_SIZE * 2);
                int stepH = h / Y_SIZE;
                int xi = 0;
                int yi = 0;
                int colorSize = 3;
                
                for (int j = stepH * 0.5; j < h; j += stepH){
                    xi = 0;
                    for (int i = stepW * 0.5; i < w; i += stepW){
                        int head = j * colorSize * w + i * colorSize;
                        int r = pixels[head];
                        int g = pixels[head + 1];
                        int b = pixels[head + 2];
                        
                        if(r < 100 && g < 100 && b < 100){
                            
                            if(xi < X_SIZE){
                                driver.drawPixels(xi, yi, 0);
                            }
                            else{
                                driver.drawPixels(xi - 8, yi, 1);
                            }
                        }
                        xi++;
                    }
                    yi++;
                }
                
            }
            
//            driver.drawAll(0);
//            driver.drawAll(1);
            
//            for(int i = 0; i < 20; i++){
//                int id = ofRandom(0, 2);
//                int x = ofRandom(0, X_SIZE);
//                int y = ofRandom(0, Y_SIZE);
//                driver.drawPixels(x, y, id);
//            }
            
        }
    }
    updateCount++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    float ww = ofGetWidth();
    float wh = ofGetHeight();
    
    int capX = (ww - capW) * 0.5;
    int capY = (wh - capH) * 0.5;
    ofSetColor(255);
    ofRect(capX, capY, capW, capH);
    
    float borderL = capX + circleRad;
    float borderR = capX + capW - circleRad;
    float borderT = capY + circleRad;
    float borderB = capY + capW - circleRad;
    
    if(circleX < borderL){
        circleDX *= -1;
        circleX = borderL;
    }
    else if(circleX > borderR){
        circleDX *= -1;
        circleX = borderR;
    }
    
    if(circleY < borderT){
        circleDY *= -1;
        circleY = borderT;
    }
    else if(circleY > borderB){
        circleDY *= -1;
        circleY = borderB;
    }
    
    if(!bMousePress){
        
        circleX += circleDX;
        circleY += circleDY;
    }
        
    circleTX += (circleX - circleTX) * 0.2;
    circleTY += (circleY - circleTY) * 0.2;
    
    ofSetColor(0, 0, 0, 255);
    ofCircle(circleTX, circleTY, circleRad);
    
    image.grabScreen(capX, capY, capW, capH);
    image.setImageType(OF_IMAGE_COLOR);
    pixels = image.getPixels();
    
    int w = image.width;
    int h = image.height;
    int stepW = w / (X_SIZE * 2);
    int stepH = h / Y_SIZE;
    int xi = 0;
    int yi = 0;
    int colorSize = 3;
    int margin = 12;
    
    for (int j = stepH * 0.5; j < h; j += stepH){
        xi = 0;
        for (int i = stepW * 0.5; i < w; i += stepW){
            int head = j * colorSize * w + i * colorSize;
            int r = pixels[head];
            int g = pixels[head + 1];
            int b = pixels[head + 2];
            
            if(r < 100 && g < 100 && b < 100){
                ofSetColor(255, 0, 0, 255);
            }
            else{
                ofSetColor(230, 230, 230, 255);
            }
            ofRect(capX + i - 5, capY + j - 5, 10, 10);
            
            xi++;
        }
        yi++;
    }
    
    bGetPixels = true;
    
    driver.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    circleX = x;
    circleY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bMousePress = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bMousePress = false;
	
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

