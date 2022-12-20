//
//  ScreenGrab.cpp
//  CGScreenshot4
//
//  Created by Tadashi Ohara on 2022/04/30.
//

#include "ScreenGrab.hpp"

void ScreenGrab::init(){
    //色空間を定義
    //colorSpace = CGColorSpaceCreateDeviceRGB();
    colorSpace = CGColorSpaceCreateDeviceGray();//グレースケール

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

        width[i]  = CGDisplayPixelsWide(dID);
        height[i] = CGDisplayPixelsHigh(dID);
        total_disp_size[i] = width[i]*height[i];
        all_disp_size+=total_disp_size[i];
        //ofAppウィンドウの横幅は単純に合計
        drawwidth+=width[i];
        //高さはどちらか高い方
        if(height[i]>drawheight)
            drawheight = height[i];

        //画像配列の定義
        cv::Mat im(cv::Size(width[i], height[i]), CV_8UC1);//グレースケールなので，チャネル数は1，階調は　8ビット
        //配列要素を同様に定義
        imgs[i] = im;
        //imgsoldはimgsで初期化
        imgsold[i] = imgs[i].clone();
        //CGコンテクストを作成
        contextRef[i] = CGBitmapContextCreate(imgs[i].data, imgs[i].cols, imgs[i].rows, 8, imgs[i].step[0], colorSpace,kCGBitmapByteOrderDefault);
    }

    diff= 0.0;      //累積の輝度差分價の平均値
    difftemp = 0.0; //輝度差分の瞬間價を格納する変数

    //フラグをtrueで初期化
    isFirst = true;

    //スクショ取得の有無を決定するカウンタを初期化
    grabcount = 0;

    //平均化用のカウンタを初期化
    ave_count = 0;
}

void ScreenGrab::update(){
    grabcount++;
    //if(grabcount>=1){
        //カウントアップ
        //ave_count++;
        //一度輝度差分を平均し直す
        //diff*=(float)ave_count-1;
        //差分値のバッファ
        float diffbuf = 0.0;
        for (int i = 0; i < displayCount; i++) {
            dID = onlineDisplays[i];
            //この2行が異常なまでにcpuを食い潰す．
            imageRef[i] = CGDisplayCreateImage(dID);
            CGContextDrawImage(contextRef[i], CGRectMake(0, 0, width[i], height[i]), imageRef[i]);
            //画像の解放
            CGImageRelease(imageRef[i]);
            //最初の実行の場合，何もしないでフラグを下ろす
            if(isFirst){
                isFirst = false;
            }
            //2回目以降の実行の場合，実際に差分の計算
            else{
                //差分画像の生成
                //imgsdiff[i] = graydiff(
                cv::absdiff(imgs[i], imgsold[i], imgsdiff[i]);
                //差分値(平均値)の計算
                //平均値を求めた後，ディスプレイの解像度をかけ直して平均し直す
                //この時点ではバッファに格納する
                difftemp = reduceMat(imgsdiff[i])*total_disp_size[i];
                diffbuf+=difftemp;
            }
            //どちらの場合でも，古い画像は更新する
            imgsold[i] = imgs[i].clone();
        //}
        //全体の解像度で割って，マルチディスプレイの結果を平均化する(opencvによる行列圧縮のプロトコル自体が全ての画素の平均値導出なので，この操作は不要である)
        //diffbuf/=all_disp_size;
        //diff+=diffbuf;
        diff = diffbuf;
        //差分抽出実行回数で平均化
        //diff/=(float)ave_count;
        //cout<<diff<<endl;
        //検出用カウンタをリセット
        grabcount = 0;
    }
}

void ScreenGrab::clear(){
    diff = 0.0;
    ave_count = 0;
}

void ScreenGrab::show(int resize){
    //ディスプレイの数だけ繰り返す
    for (int i = 0; i < displayCount; i++) {
        //差分画像の描画
        ofxCv::drawMat(imgs[i], 0+i*width[i-1]/resize, 0, width[i]/resize, height[i]/resize);
        //差分画像の描画
        ofxCv::drawMat(imgsdiff[i], 0+i*width[i-1]/resize, height[i]/resize, width[i]/resize, height[i]/resize);
    }
}
