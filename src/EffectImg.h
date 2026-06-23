#pragma once
#include <string>
// ------------------------------------------------------------
//	エフェクトクラス
//	 横方向に連続で描画された画像を分割描画し、
//	 指定された速度でアニメーションを再生するクラス
//	 ※ 縦方向の画像には配慮していないため
//		その画像を使用したい場合は、各自で拡張すること
// ------------------------------------------------------------
class EffectImg
{
public:
		
	// 画像ファイルの読み込み
	//	戻り値: なし
	//	引数1:	ファイル名（フルパス）
	//	引数2:	分割数
	void load(std::string fname, int div_num);

	// 再生速度の設定
	//	戻り値:	なし
	//	引数:	再生速度
	void setSpeed(int speed);

	// アニメーションの再生
	//	戻り値:	なし
	//	引数:	なし
	void play();

	// 描画座標の設定
	//	戻り値:	なし
	//	引数:	座標
	void setPos(int2 pos);

	// アニメーションが再生中かどうか
	//	戻り値:	アニメーションが再生中であればtrue/そうじゃなければfalse
	//	引数:	なし
	bool isPlay() const
	{
		return (is_stop_ == false);
	}

	void update();	// 更新処理
	void render();	// 描画処理
	void exit();	// 終了処理

private:
	int2 pos_;				// 描画座標
	int2 img_size_;			// 画像サイズ（全体）
	int2 img_size2_;		// 画像サイズ（分割後）

	int img_	 = -1;		// 画像
	int div_num_ = 0;		// 分割数
	int src_x_	 = 0;		// 切り取り位置
	int speed_	 = 5;		// 再生速度
	int frame_	 = 0;		// 現在のフレーム数

	bool is_stop_ = true;	// 再生停止中かどうか
};

