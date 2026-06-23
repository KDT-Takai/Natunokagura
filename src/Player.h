#pragma once

#include "DxLib.h"
#include "typedef.h"
#include "InputKey.h"
#include "InputMouse.h"
#include "GameMain.h"
#include "Enemy.h"
#include "WinMain.h"
#include "Hitshot.h"
#include "EXP.h"
#include "GameDead.h"
#include "GameClear.h"
#include "ui.h"
#include <cmath>

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerExit();

#define PI		 3.141592653589793
#define RadToDeg 57.29577951f
#define R2D(rad) rad * RadToDeg

#define DegToRad 0.017453293f
#define D2R(deg) deg * DegToRad

#define BLACK	GetColor(0, 0, 0)
#define WHITE	GetColor(255, 255, 255)
#define RED		GetColor(255, 0, 0)
#define GREEN	GetColor(60, 179, 113)
#define BLUE	GetColor(0, 0, 255)
#define YELLOW	GetColor(255, 255, 0)
#define PINK	GetColor(255, 0, 255)
#define SKYBLUE	GetColor(0, 255, 255)

#define WINDOW_W	640
#define WINDOW_H	480

#define IMG_SIZE	32


//　初期値の０に戻す際の定数
#define START_ZERO 0

//　DrawCircleAAの角形
#define CIRCLEAA_SQUARE	64		//　何角形か

//　画面の範囲
#define BG_X_LW 31		//　左
#define BG_X_HW 416		//　右
#define BG_Y_LH 14		//　上
#define BG_Y_HH 463		//　下

//　自機移動設定
#define PLAYER_R				3	//　プレイヤーの半径
#define PLAYER_SPEED_NORMAL		4	//　プレイヤーの移動スピード（通常時）
#define PLAYER_SPEED_GLAZE		2	//　プレイヤーの移動スピード（グレイズモード）
#define	PLAYER_IMG_WIDTH		32	//　プレイヤーの画像の横幅
#define	PLAYER_IMG_HEIGHT		48	//　プレイヤーの画像の縦幅
#define PLAYER_IMG_WIDTH_MAX	128	//　プレイヤーの画像の横幅最大値
#define PLAYER_IMG_TIMING		8	//　画像が切り替わる
#define PLAYER_IMG_SAME_SIZE	1	//　画像等倍
#define PLAYER_HP_MAX			3	//　ヒットポイントの最大値
#define PLAYER_HIT_INVINCIBLE	180	//　プレイヤーに弾が当たったら何秒間無敵か

//　霊夢の隣にある丸（霊札？）
#define PLAYER_REIFU_SPEED		0.5f//　回転速度
#define PLAYER_REIFU_WIDTH		25	//　プレイヤーの中心からどれくらい離すか（横の場合　レベル３，４，５）
#define PLAYER_REIFU_HEIGHT		35	//　プレイヤーの中心からどれくらい離すか（縦の場合　レベル１，２）
#define PLAYER_REIFU_SIZE		16	//　霊札のサイズ

//　自機の弾（ Sway 用）
#define SWAY_MAX_NUM	100		//　弾の最大値（最大値まで行くと０に戻すため一応あふれることはない）
#define SWAY_TIMING		10		//　攻撃のタイミング調整
#define SWAY_ROT		270		//　弾を出す角度（真上に出す場合の定数）
#define SWAY_SPEED		7.0f	//	弾の速度
#define SWAY_R			5		//　弾の大きさ
#define SWAY_NUM		10		//　弾の個数

#define	SWAY_ROT_L2		3		//　レベル２の弾の角度
#define	SWAY_L2			3		//　レベル２の弾の数
#define SWAY_L4			5		//　レベル４の弾の数

//　自機の弾（ 霊夢のサブショット ）
#define HR_SHOT_MAX_NUM		100		//　弾の最大値
#define HR_SHOT_R			3		//　弾の半径
#define HR_SHOT_NUM			6		//　弾の個数
#define HR_SHOT_TIMING		15		//　攻撃のタイミング調整
#define HR_SHOT_SPEED		8.5f	//　弾のスピード

//　霊夢のスペルカード
#define HR_SPELLCARD_R_SPEED		5	//　スペルカードの半径がどれぐらいのスピードで大きくなるか
#define HR_CIRCLE_SIZE				500	//　最大サイズ５００になったらスペルカード終了

//　自機の弾（魔理沙のサブショット）
#define KM_SHOT_MAX				2	//　何本あるか（ずっと２本だよ）
#define KM_SHOT_L3_WIDTH		6	//　レベル３のときの幅
#define KM_SHOT_L4_WIDTH		10	//　レベル４のときの幅
#define KM_SHOT_L5_WIDTH		14	//　レベル５のときの幅
#define KM_SHOT_SPEED			13	//　ビームの速度
#define KM_SHOT_COUNT			30	//　何フレームにダメージか
#define KM_SHOT_DAMAGE			5	//　ダメージ数

//　魔理沙のスペルカード
#define KM_SPELLCARD_SPEED_X			15	//　スピード
#define KM_SPELLCARD_SPEED_Y			30	//　スピード
#define KM_SPELLCARD_SIZE			200	//　横幅
#define KM_SPELLCARD_Y_ADJUSTMENT	40	//　魔理沙の少し上から発射したいからその座標の調整用
#define KM_SPELLCARD_LONG			120	//　何フレーム間撃つのか
#define KM_COUNT					15
#define KM_SPELLCARD_COUNT			5

#define SPELLCARD_TIMING			400	//　４００フレームで次のスペルカードを撃てる
//　スペルカード回数
#define SPELLCARD_NUM				3

//　サウンド
#define SE_PLAYER_VOLUME			100

// 円と円との当たり判定
bool isHit(int x1, int y1, int r1, int x2, int y2, int r2);

//　ボックスと点の当たり判定
bool isBoxHit(int x1, int y1, int x2, int y2, int mouse_x, int mouse_y);

//	文字の真ん中を指定の位置に描画　（洞ちゃん作成）
void DrawCenterString(float x, float y, const char* string, unsigned int Color);

//　円のｘ、円のｙ、円の半径、ボックスのｘ（左上）、ボックスのｙ（左上）、ボックスのサイズｘ、ボックスのサイズｙ
bool CheckHitBoxCircle(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_x_size, float box_y_size);

//　メモ 	int LoadDivGraph( char *FileName , int AllNum ,int XNum, int YNum,int XSize, int YSize, int* HandleBuf );
//　画像を分割して使える
