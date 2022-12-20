#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ScreenGrab.hpp"
#include "ofxGraph.h"//ProjectGeneratorで，xmlsettingsとguiを追加しておくのを忘れずに

#define INTERVAL 3
#define RESIZE 4

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
    
    //スクショ管理用の変数
    ScreenGrab sc;
    //時刻取得用
    int old;
    //グラフ描画用
    ofxGraph graph;
    //指定時間が経過したかどうかを判断する論理関数
    bool isPassed(int* time){
        if((int)ofGetElapsedTimef()-(*time)==INTERVAL){
            *time = ofGetElapsedTimef();
            return true;
        }
        else
            return false;
    };
};
