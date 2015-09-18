//
//  ofxJFCanvas.h
//  ofxJFCanvas
//
//  Created by João Fonseca on 31/07/15.
//
//

#pragma once

class ofxJFCanvas {
    
public:
    
    ofVec2f canvasSize;
    ofVec2f windowSize;
    ofVec2f anchorPoint;
    ofVec2f navWindowSize;
    
    ofFbo * canvas;
    ofFbo * canvas2;
    
    float scale;
    float minScale;
    float maxScale;
    
    bool pdfRendering;
    
    
    ofxJFCanvas(){}
    
    ofxJFCanvas(int _w, int _h, ofFbo * _canvas, ofFbo * _canvas2){
        
        canvas = _canvas;
        canvas2 = _canvas2;
        windowSize.set(_w, _h);
        
        scale = windowSize.x / canvas->getWidth();
        minScale = scale;
        maxScale = 10;
        anchorPoint.set(0,0);
        canvasSize.set(canvas->getWidth()*scale,canvas->getHeight()*scale);
        
        pdfRendering=false;
    }
    
    void update(){
        
    }
    
    void draw(){
        
        float anchorPosX=ofMap(anchorPoint.x,0,navWindowSize.x,0,canvasSize.x);
        float anchorPosY=ofMap(anchorPoint.y,0,navWindowSize.y,0,canvasSize.y);
        
        ofPushMatrix();
        ofPushStyle();
        
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofPushStyle();
        ofSetColor(220);
        ofDrawRectangle(0-(canvasSize.x/2)-anchorPosX,0-(canvasSize.y/2)-anchorPosY,canvasSize.x,canvasSize.y);
        ofPopStyle();
        
        ofSetColor(255);
        canvas->draw(0-(canvasSize.x/2)-anchorPosX,0-(canvasSize.y/2)-anchorPosY,canvasSize.x,canvasSize.y);
        ofSetColor(255);
        canvas2->draw(0-(canvasSize.x/2)-anchorPosX,0-(canvasSize.y/2)-anchorPosY,canvasSize.x,canvasSize.y);
        
        ofPopStyle();
        ofPopMatrix();
        
   
        //exportToPdf();
        
        navigationWindow();
        
//        ofPixels temp;
//        canvas->readToPixels(temp);
//        ofSaveImage(temp, "exports/png/frame_"+ofToString(ofGetFrameNum())+".png", OF_IMAGE_QUALITY_BEST);
    }
    
    void navigationWindow(){
        
        float navWindowScale=0.1;
        
        
        navWindowSize.set(canvas->getWidth()*navWindowScale,canvas->getHeight()*navWindowScale);
        ofVec2f navWindowPosition(windowSize.x-20-navWindowSize.x,20);
        navWindowPosition+=navWindowSize/2;
        
        ofPushMatrix();
        ofPushStyle();
        
        ofTranslate(navWindowPosition.x, navWindowPosition.y);
        
        ofSetColor(255);
        canvas->draw(-navWindowSize.x/2,-navWindowSize.y/2,navWindowSize.x,navWindowSize.y);
        canvas2->draw(-navWindowSize.x/2,-navWindowSize.y/2,navWindowSize.x,navWindowSize.y);
        
        ofNoFill();
        ofSetColor(255);
        ofDrawRectangle(-navWindowSize.x/2,-navWindowSize.y/2,navWindowSize.x,navWindowSize.y);
        
        
        if(scale!=minScale){
            ofFill();
            ofSetColor(255);
            int lineSize=20;
            ofDrawLine(anchorPoint.x-lineSize, anchorPoint.y, anchorPoint.x+lineSize, anchorPoint.y);
            ofDrawLine(anchorPoint.x, anchorPoint.y-lineSize, anchorPoint.x, anchorPoint.y+lineSize);
            
            
            
            
            if(ofGetMousePressed() && ((ofGetMouseX()>navWindowPosition.x-navWindowSize.x/2) && (ofGetMouseX()<navWindowPosition.x -navWindowSize.x/2 + navWindowSize.x) && (ofGetMouseY()>navWindowPosition.y -navWindowSize.y/2) && (ofGetMouseY()<navWindowPosition.y -navWindowSize.y/2 + navWindowSize.y))){
                
                anchorPoint.set(ofGetMouseX()-(navWindowPosition.x-navWindowSize.x/2)-navWindowSize.x/2, ofGetMouseY()-(navWindowPosition.y-navWindowSize.y/2)-navWindowSize.y/2);
            }
            
        }else {
            
            anchorPoint.set(0,0);
        }
        
        ofPopStyle();
        ofPopMatrix();
        
        
        
        
    }
    
    
    void zoom(){
        
        scale = ofClamp(scale, minScale, maxScale);
        canvasSize.set(canvas->getWidth()*scale,canvas->getHeight()*scale);
    }
    
    
    void keyPressed(int _key){
        
        if (_key == '+') {
            scale += 0.1;
            zoom();
            
        }else if(_key == '-'){
            scale -= 0.1;
            zoom();
            
        }else if(_key == '1'){
            scale = minScale;
            zoom();
            
        }else if(_key == '2'){
            scale = 1;
            zoom();
            
        }else if(_key == '3'){
            scale = 1*5;
            zoom();
            
        }else if(_key == 'e'){
            
            //            pdfRendering=!pdfRendering;
            //            exportToPdf();
        }
    }
    
    
    void exportToPdf(){
        
        //ofPushMatrix();
        
        if( pdfRendering ){
            //ofSetFrameRate(12);  // so it doesn't generate tons of pages
            ofRectangle viewport(0, 0, canvas->getWidth(), canvas->getHeight());
            ofViewport(viewport);
            ofBeginSaveScreenAsPDF("exports/frame_"+ofToString(ofGetFrameNum())+".pdf", false);
        }else{
            // ofSetFrameRate(60);
            ofEndSaveScreenAsPDF();
            
        }
        
    }
    
    
};