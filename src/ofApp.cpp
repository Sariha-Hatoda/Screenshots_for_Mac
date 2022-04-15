#include "ofApp.h"

/*
目的:マルチディスプレイであっても輝度差分を抽出し，指定時間でサンプリングする

目標:
輝度差分をとる．

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

        //CGコンテクストを作成
        contextRef[i] = CGBitmapContextCreate(imgs[i].data, imgs[i].cols, imgs[i].rows, 8, imgs[i].step[0], colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault);
    }
    //ウィンドウの形状をリサイズ後のサイズで指定
    ofSetWindowShape(drawwidth*RESIZE, drawheight*RESIZE);

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
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //リサイズ後のスクショを描画
    for (int i = 0; i < displayCount; i++) {
        ofxCv::drawMat(imgs[i], 0+i*width[i-1]*RESIZE, 0, width[i]*RESIZE, height[i]*RESIZE);
    }

    //画面収録用
    ofImage savefig;
    savefig.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    //指定したサンプリング時間を迎えた場合，画像を保存
    if (int(ofGetElapsedTimef()-oldtime) == INTERVAL) {
        //さらに半分にリサイズ
        savefig.resize(savefig.getWidth()*RESIZE, savefig.getHeight()*RESIZE);
        //タイムスタンプをファイル名として保存
        savefig.save(ofGetTimestampString("%y%m%d%H%M%S") + ".jpg");
        
        //現在時刻に更新
        oldtime = ofGetElapsedTimef();
    }
    //イメージを解放
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
