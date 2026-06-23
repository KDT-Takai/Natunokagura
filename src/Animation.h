#pragma once
#include <string>
// ------------------------------------------------------------
//	アニメーション再生クラス
//	 「0000.png」のファイル形式の画像を指定された枚数読み込み、
//	 指定された速度でアニメーションを再生するクラス
// ------------------------------------------------------------
const int MAX_IMG_NUM = 25;
class Animation
{
public:
	Animation();

	// 画像読み込み
	//	戻り値:	なし
	//	引数1:	ファイルのパス
	//	引数2:	画像の枚数
	void load(std::string path, int img_num);
	// 再生速度の設定
	//	戻り値:	なし
	//	引数:	再生速度
	void setSpeed(int speed);
	// アニメーションの再生
	//	戻り値:	なし
	//	引数:	なし
	void play();
	// 現在の画像の取得
	//	戻り値:	画像の中で現在の画像を取得
	//	引数:	なし
	int  getImg() const;
	// アニメーションが再生中かどうか
	//	戻り値:	アニメーションが再生中であればtrue/そうじゃなければfalse
	//	引数:	なし
	bool isPlay() const
	{
		return (is_stop_ == false);
	}

	void update();	// 更新処理
	void exit();	// 終了処理

private:
	int  img_[MAX_IMG_NUM] = { 0 };	// 画像
	int  index_			   = 0;		// 現在のアニメーション番号
	int  size_			   = 0;		// サイズ
	int  frame_			   = 0;		// アニメーション再生フレーム
	int  speed_			   = 5;		// 再生速度
	bool is_stop_		   = true;	// 再生停止中かどうか

};
