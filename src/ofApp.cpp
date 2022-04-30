#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    sc.init();
    //ウィンドウの形状をリサイズ後のサイズで指定
    ofSetWindowShape(sc.drawwidth/RESIZE, sc.drawheight/RESIZE);

    //開始時刻の記録
    old = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    sc.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    sc.show(RESIZE);
    if(isPassed(&old)){
        sc.clear();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
