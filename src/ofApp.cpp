#include "ofApp.h"

/*
目的:マルチディスプレイであっても輝度差分を抽出し，指定時間でサンプリングする

目標:
輝度差分をとる．
とれた．

*/

//--------------------------------------------------------------
void ofApp::setup(){
    //色空間の定義(デバイス依存)
    colorSpace = CGColorSpaceCreateDeviceRGB();

    //オンラインディスプレイのリストを取得
    dErr = CGGetOnlineDisplayList(maxDisplays, onlineDisplays, &displayCount);

    //ofAppウィンドウサイズを初期化
    drawwidth =0;
    drawheight=0;

    //ディスプレイIDおよび幅と高さの初期化
    for (int i = 0; i < displayCount; i++) {

        //ディスプレイIDの取得
        dID = onlineDisplays[i];

        width[i] =CGDisplayPixelsWide(dID);
        height[i] =CGDisplayPixelsHigh(dID);
        //ofAppウィンドウの横幅は単純に合計
        drawwidth+=width[i];
        //高さはどちらか高い方
        if(height[i]>drawheight)
            drawheight = height[i];

        //画像配列の定義
        cv::Mat im(cv::Size(width[i], height[i]), CV_8UC4);
        //配列要素を同様に定義
        imgs[i] = im;
        //imgsoldはimgsで初期化
        imgsold[i] = imgs[i].clone();
        //CGコンテクストを作成
        contextRef[i] = CGBitmapContextCreate(imgs[i].data, imgs[i].cols, imgs[i].rows, 8, imgs[i].step[0], colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault);
    }
    //ウィンドウの形状をリサイズ後のサイズで指定
    ofSetWindowShape(drawwidth*RESIZE, drawheight*RESIZE);

    isFirst = true;

    //開始時刻の記録
    oldtime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    //検出されたディスプレイの数だけ，スクショを取得
    for (int i = 0; i < displayCount; i++) {
        dID = onlineDisplays[i];
        imageRef[i] = CGDisplayCreateImage(dID);
        CGContextDrawImage(contextRef[i], CGRectMake(0, 0, width[i], height[i]), imageRef[i]);
        if(isFirst){
            isFirst = false;
        }
        else{
            diff[i]= 0.0;//差分を初期化
            imgsdiff[i] = graydiff(imgs[i], imgsold[i]);
            cout <<ofToString(i)+":"<< reduceMat(imgsdiff[i]) << endl;
        }
        imgs[i].copyTo(imgsold[i]);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ディスプレイの数だけ繰り返す
    for (int i = 0; i < displayCount; i++) {
        //最初の実行でない時のみ，輝度差分を抽出
            ofxCv::drawMat(imgsdiff[i], 0+i*width[i-1]*RESIZE, 0, width[i]*RESIZE, height[i]*RESIZE);
            CGImageRelease(imageRef[i]);
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
