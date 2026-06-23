#include "WinMain.h"
// 「Timingゲーム」の作成
// extern

//　背景画像
int BG_frame_img;						//　フレーム背景の画像
int BG_stage_img;						//　ステージ背景の画像
//　背景画像のスクロール
float BG_stage_y;						//　ステージ背景の画像を縦スクロールさせる


float a;

struct Floatxy {
	float x;	//　ｘ座標
	float y;	//　ｙ座標
};

void GameInit()
{
	// DrawStringやDrawFormatStrinで描画する文字を
	// アンチエイリアスを使用してきれいに描画する
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	BG_frame_img = LoadGraph("data/bg/STG_Frame3.png");			//　フレーム
	BG_stage_img = LoadGraph("data/bg/st01.png");				//　ステージ

	//　ステージ背景のスクロール
	//BG_stage_y += BG_STAGE_SPEED;
	////　もし画像が画像一個分まで進んだら元
	//if (BG_stage_y >= 488.0f) {
	//	//　元の位置に戻す
	//	BG_stage_y = 0.0f;
	//}
}

void GameUpdate()
{

	//　ステージ背景のスクロール
//	BG_stage_y += BG_STAGE_SPEED;
	BG_stage_y += 1;
	//　もし画像が画像一個分まで進んだら元
	if (BG_stage_y >= 488.0f) {
		//　元の位置に戻す
		BG_stage_y = 0.0f;
	}
	a += 0.5;
}

void GameDraw()
{
	float x = BG_STAGE_X_SIZE / 2.0f + BG_X_LW;
	float y = BG_STAGE_Y_SIZE / 2.0f + BG_Y_LH + BG_stage_y;
	float x1 = BG_STAGE_X_SIZE / 2.0f + BG_X_LW;
	float y1 = BG_STAGE_Y_SIZE / 2.0f + BG_Y_LH - BG_STAGE_Y_SIZE + BG_stage_y;
	//　ステージの背景
	DrawRotaGraphF(x,	y,	PLAYER_IMG_SAME_SIZE,	0, BG_stage_img, TRUE);		//　先
//	DrawGraphF(BG_X_LW, a, BG_stage_img, TRUE);		//　先
	DrawRotaGraphF(x1, y1,	PLAYER_IMG_SAME_SIZE,	0, BG_stage_img, TRUE);		//　後


}

void GameExit()
{
	DeleteGraph(BG_stage_img);
	DeleteGraph(BG_frame_img);
}