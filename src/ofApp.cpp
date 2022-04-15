#include "ofApp.h"

/*
ver.4.0
目的:マルチディスプレイであっても輝度差分を抽出し，指定時間でサンプリングする

目標:
マルチディスプレイでスクショをとる

成果:



*/

//--------------------------------------------------------------
void ofApp::setup(){
    //色空間の定義(デバイス依存)
    colorSpace = CGColorSpaceCreateDeviceRGB();

    //オンラインディスプレイのリストを取得
    dErr = CGGetOnlineDisplayList(maxDisplays, onlineDisplays, &displayCount);

    drawwidth =0;
    drawheight=0;
    for (int i = 0; i < displayCount; i++) {

        dID = onlineDisplays[i];

        width[i] =CGDisplayPixelsWide(dID);
        height[i] =CGDisplayPixelsHigh(dID);
        drawwidth+=width[i];
        if(height[i]>drawheight)
            drawheight = height[i];

        cv::Mat im(cv::Size(width[i], height[i]), CV_8UC4);
        imgs[i] = im;
        contextRef[i] = CGBitmapContextCreate(imgs[i].data, imgs[i].cols, imgs[i].rows, 8, imgs[i].step[0], colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault);

    }
    ofSetWindowShape(drawwidth*RESIZE, drawheight*RESIZE);

    //画像配列の定義(BGRA，BGR，リサイズBGR)
    
    oldtime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < displayCount; i++) {
        dID = onlineDisplays[i];
        imageRef[i] = CGDisplayCreateImage(dID);
        CGContextDrawImage(contextRef[i], CGRectMake(0, 0, width[i], height[i]), imageRef[i]);

    }

    //CGContextDrawImage:グラフィックコンテクストに画像を描画
    //(1)描画される画像コンテクスト
    //(2)画像を描画する矩形の位地と寸法
    //(3)描画する画像
}

//--------------------------------------------------------------
void ofApp::draw(){
    //リサイズ後のスクショを描画
    for (int i = 0; i < displayCount; i++) {
    ofxCv::drawMat(imgs[i], 0+i*width[i-1]*RESIZE, 0, width[i]*RESIZE, height[i]*RESIZE);
    }
    //画面収録用
    ofImage savefig;
    savefig.grabScreen(0, 0,drawwidth, drawheight);


    if (int(ofGetElapsedTimef())-oldtime == INTERVAL) {
        savefig.resize(savefig.getWidth()*RESIZE, savefig.getHeight()*RESIZE);
        savefig.save(ofGetTimestampString("%y%m%d%H%M%S") + ".jpg");
        oldtime = ofGetElapsedTimef();
    }
    for (int i = 0; i < displayCount; i++)
        CGImageRelease(imageRef[i]);
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
