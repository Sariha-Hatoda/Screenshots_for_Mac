#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //色空間の定義(デバイス依存)
    colorSpace = CGColorSpaceCreateDeviceRGB();

    //オンラインディスプレイのリストを取得
    dErr = CGGetOnlineDisplayList(maxDisplays, onlineDisplays, &displayCount);

    //ofAppウィンドウサイズを初期化
    drawwidth =0;
    drawheight=0;
    all_disp_size = 0;
    //ディスプレイIDおよび幅と高さの初期化
    for (int i = 0; i < displayCount; i++) {

        //ディスプレイIDの取得
        dID = onlineDisplays[i];

        width[i] =CGDisplayPixelsWide(dID);
        height[i] =CGDisplayPixelsHigh(dID);
        total_disp_size[i] = width[i]*height[i];
        all_disp_size+=total_disp_size[i];
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
    diff= 0.0;
    for (int i = 0; i < displayCount; i++) {
        dID = onlineDisplays[i];
        imageRef[i] = CGDisplayCreateImage(dID);
        CGContextDrawImage(contextRef[i], CGRectMake(0, 0, width[i], height[i]), imageRef[i]);

        //最初の実行の場合，何もしないでフラグを下ろす
        if(isFirst){
            isFirst = false;
        }
        //2回目以降の実行の場合，実際に差分の計算
        else{
            //差分画像の生成
            imgsdiff[i] = graydiff(imgs[i], imgsold[i]);
            //差分値(平均値)の計算
            diff+=reduceMat(imgsdiff[i])*total_disp_size[i];
        }
        //どちらの場合でも，古い画像は更新する
        imgsold[i] = imgs[i].clone();
    }
    cout<<diff/(float)all_disp_size<<endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ディスプレイの数だけ繰り返す
    for (int i = 0; i < displayCount; i++) {
        //差分画像の描画
        ofxCv::drawMat(imgsdiff[i], 0+i*width[i-1]*RESIZE, 0, width[i]*RESIZE, height[i]*RESIZE);
        //画像の解放
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
