#include "WinMain.h"
#include "EffectImg.h"
// ------------------------------------------------------------
//	エフェクトクラス
//	 横方向に連続で描画された画像を分割描画し、
//	 指定された速度でアニメーションを再生するクラス
//	 ※ 縦方向の画像には配慮していないため
//		その画像を使用したい場合は、各自で拡張すること
// ------------------------------------------------------------
// 画像ファイルの読み込み
//	戻り値: なし
//	引数1:	ファイル名（フルパス）
//	引数2:	分割数（X方向のみ）
void EffectImg::load(std::string fname, int div_num)
{
	// 画像がすでに読み込まれていたら削除する
	if (img_ != -1)
	{
		DeleteGraph(img_);
	}

	img_ = LoadGraph(fname.c_str());
	GetGraphSize(img_, &img_size_.x, &img_size_.y);
	img_size2_ = { img_size_.x / div_num, img_size_.y };
	div_num_   = div_num;
}

// 再生速度の設定
//	戻り値:	なし
//	引数:	再生速度
void EffectImg::setSpeed(int speed)
{
	speed_ = speed;
}

// アニメーションの再生
//	戻り値:	なし
//	引数:	なし
void EffectImg::play()
{
	if (is_stop_ == false)
		return;

	frame_ = 0;
	src_x_ = 0;
	is_stop_ = false;
}

// 描画座標の設定
//	戻り値:	なし
//	引数:	座標
void EffectImg::setPos(int2 pos)
{
	pos_ = pos;
}

// 更新処理
void EffectImg::update()
{
	if (is_stop_ == true)
		return;

	++frame_;
	frame_ %= speed_;
	if (frame_ == 0)
	{
		frame_ = 0;
		src_x_ += img_size2_.x;
		if (src_x_ > img_size_.x)
		{
			src_x_	 = 0;
			is_stop_ = true;
		}

	}
}

// 更新処理
void EffectImg::render()
{
	if (is_stop_ == true)
		return;

	DrawRectRotaGraph(pos_.x, pos_.y, src_x_, 0,
		img_size2_.x, img_size2_.y, 1, 0,
		img_, TRUE);
}

// 終了処理
void EffectImg::exit()
{
	DeleteGraph(img_);
}

