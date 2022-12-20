# Screenshots_for_Mac
openFrameworks0.11.2とCoreGraphicsフレームワークを用いて，一定時間ごとに自動でスクリーンショットを記録するアプリを作成しました．
同時にopenCVのメソッドを使って前後フレームの輝度差分も抽出するようにしてあります．

# Usage
openFrameworks0.11.2でビルドしてください．projectGeneratorでupdateすれば問題ないはずです．
必要なアドオンは，addons.makeにある
ofxOpenCv
ofxCv
ofxGraph
ofxGui
ofxXmlSettings
です．ofxGraphは
https://github.com/TetsuakiBaba/ofxGraph　
から拝借しました．

#参考:
-CoreFoundation ドキュメント
https://developer.apple.com/documentation/corefoundation/
-openFrameworks ドキュメント
https://openframeworks.cc/ja/documentation/
