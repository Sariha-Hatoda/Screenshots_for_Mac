#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // ofxGraph Init
    graph.setup("Diff");
    graph.setDx(0.1); // which means delta of time
    
    graph.setColor(ofColor::white);  // ofColor(255,255,255)

    ofSetFrameRate(60);
    ofSetVerticalSync(true);//垂直同期を有効化
    sc.init();
    //ウィンドウの形状をリサイズ後のサイズで指定
    ofSetWindowShape(sc.drawwidth/RESIZE, sc.drawheight*2);

    //開始時刻の記録
    old = ofGetElapsedTimef();


}

//--------------------------------------------------------------
void ofApp::update(){
    sc.update();
    graph.add(sc.diff);
}

//--------------------------------------------------------------
void ofApp::draw(){
    sc.show(RESIZE);
    graph.draw();
    ofSaveFrame(true);
/*
    if(isPassed(&old)){
        sc.clear();
    }
*/
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
