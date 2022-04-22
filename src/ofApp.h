#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

#define MAX_DISPLAYS 2
#define INTERVAL 3
#define RESIZE 0.5

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    private:
    
    //マルチディスプレイ操作用
    CGDisplayErr dErr;
    CGDisplayCount displayCount;
    CGDirectDisplayID dID;
    CGDisplayCount maxDisplays = MAX_DISPLAYS;
    CGDirectDisplayID onlineDisplays[MAX_DISPLAYS];

    //メインディスプレイの幅と高さ
    size_t width[MAX_DISPLAYS];
    size_t height[MAX_DISPLAYS];

    //描画する際の画面サイズ
    size_t drawwidth, drawheight;

    //画像を格納するグローバル変数
    //ARGB
    cv::Mat imgs[MAX_DISPLAYS], imgsold[MAX_DISPLAYS],imgsdiff[MAX_DISPLAYS];

    //ディスプレイの色の解釈方式，つまり色空間
    CGColorSpaceRef colorSpace;

    //2D描画先(描画パラメタ，デバイス固有情報など)．
    CGContextRef contextRef[MAX_DISPLAYS];

    //ビットマップ画像，もしくはマスク画像
    CGImageRef imageRef[MAX_DISPLAYS];

    //時刻取得用
    unsigned int oldtime;
    
    //最初の実行かどうかを管理するフラグ
    bool isFirst;

    //輝度差分を格納しておく変数
    float diff[MAX_DISPLAYS];

    //グレースケール化したのち差分画像を生成する関数
    cv::Mat graydiff(cv::Mat now, cv::Mat old){
        //グレースケール化
        cv::Mat nowg,oldg,diffg;
        cv::cvtColor(now, nowg, CV_RGBA2GRAY);
        cv::cvtColor(old, oldg, CV_RGBA2GRAY);
        cv::absdiff(nowg,oldg,diffg);
        return diffg;
    }
    //cv::Mat各要素の平均をとる関数
    float reduceMat(cv::Mat inputMat){
        float scalafloat;
        scalafloat = (float)cv::mean(inputMat)[0];
        return scalafloat;
    }
};
