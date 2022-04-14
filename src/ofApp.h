#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>

#define MAX_DISPLAYS 2

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
    cv::Mat imgs[MAX_DISPLAYS];

    //ディスプレイの色の解釈方式，つまり色空間
    CGColorSpaceRef colorSpace;

    //2D描画先(描画パラメタ，デバイス固有情報など)．
    CGContextRef contextRef[MAX_DISPLAYS];

    //ビットマップ画像，もしくはマスク画像
    CGImageRef imageRef[MAX_DISPLAYS];

    //時刻取得用
    unsigned int interval, oldtime;
};
