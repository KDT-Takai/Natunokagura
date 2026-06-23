#pragma once

#include "DxLib.h"
#include "typedef.h"
#include "InputKey.h"
#include "InputMouse.h"
#include "GameMain.h"
#include "Player.h"
#include "WinMain.h"
#include "Hitshot.h"
#include "EXP.h"
#include <cmath>

void EnemyInit();
void EnemyUpdate();
void EnemyDraw();
void EnemyExit();

//#define STAGE_NULL_COUNT	2	* 60
//#define STAGE_FIRST_COUNT	120	* 60
//#define STAGE_SECOND_COUNT	120	* 60
//#define STAGE_THIRD_COUNT	180	* 60
//#define STAGE_FOURTH_COUNT	120	* 60
//#define STAGE_FIFTH_COUNT	180	* 60
//#define STAGE_SIXTH_COUNT	240	* 60
//
////　赤色と青色の数（ステージ）
//#define STAGE_FIRST_NUM		1
//#define STAGE_SECOND_NUM	2
//#define STAGE_THIRD_NUM		3
//
////　赤色の雑魚敵
//#define ENEMY_RED_SHOT_MAX			5		//　一回に出す弾の数
//#define ENEMY_RED_NUM_MAX			100		//　弾の最大（これ以上行くと０に戻すので無限に撃つ）
//#define ENEMY_RED_COUNT_TIMING		45		//　弾を出すタイミング
//#define ENEMY_RED_SPEED_SWAY		2.0f	//　赤色の弾の速度
//#define ENEMY_RED_R					6		//　赤色の雑魚敵の大きさ
//#define ENEMY_RED_SHOT_R			4		//　弾の半径
//#define ENEMY_ROT_DIRECTLY_BELOW	85		//　真下に向けるための角度　９０度
//#define ENEMY_RED_SPEED				0.5f	//　赤色の敵の移動スピード
//#define ENEMY_RED_ROT_SIZE			6		//　赤色の敵の弾の一つ一つの隙間の角度
//#define ENEMY_RED_NUM				3		//　赤色の雑魚敵の合計数
//
////　青色の雑魚敵
//#define ENEMY_BLUE_SHOT_MAX			30		//　１周する間に出す数
//#define ENEMY_BLUE_COUNT_TIMING		15		//　１発撃つタイミング
//#define ENEMY_BLUE_SPEED_SWAY		3.0f	//　青色の弾の速度
//#define ENEMY_BLUE_R				6		//　青色の雑魚敵の大きさ
//#define ENEMY_BLUE_SHOT_R			4		//　青色の弾の半径
//#define ENEMY_BLUE_SPEED			0.5f	//　青色の敵の移動スピード
//#define ENEMY_BLUE_NUM				3		//　青色の雑魚敵の合計数
//
//#define ENEMY_RED_BLUE_X			40		//　敵座標の位置調整
//#define ENMEY_RED_BLUE_START		30		//　スタート一の座標調整
//
//
//#define SAKUYA_SIZE_R						10		//　赤色の雑魚敵の大きさ
//#define SAKUYA_ROT_DIRECTLY_BELOW			90		//　真下に向けるための角度　９０度
//#define SAKUYA_SPEED_X						1.1f	//　移動スピード
//#define SAKUYA_SPEED_Y						0.8f	//　移動スピード
//#define SAKUYA_MAX_HP						500	//　咲夜の最大HP
//
////　１
//#define SAKUYA_ATTACK_1_SHOT_MAX			7		//　一回に出す弾の数
//#define SAKUYA_ATTACK_1_NUM_MAX				25		//　弾の最大（これ以上行くと０に戻すので無限に撃つ）
//#define SAKUYA_ATTACK_1_COUNT_TIMING		70		//　弾を出すタイミング
//#define SAKUYA_ATTACK_1_SPEED_SWAY			1.5f	//　赤色の弾の速度
//#define SAKUYA_ATTACK_1_SHOT_R				3		//　弾の半径
//#define SAKUYA_ATTACK_1_SPEED				1.5f	//　赤色の敵の移動スピード
//#define SAKUYA_ATTACK_1_ROT_SIZE			4		//　赤色の敵の弾の一つ一つの隙間の角度
//
////　２
//#define SAKUYA_ATTACK_2_SHOT_MAX			36		//　一回に出す弾の数
//#define SAKUYA_ATTACK_2_NUM_MAX				25		//　弾の最大（これ以上行くと０に戻すので無限に撃つ）
//#define SAKUYA_ATTACK_2_COUNT_TIMING		70		//　弾を出すタイミング
//#define SAKUYA_ATTACK_2_SPEED_SWAY			1.0f	//　赤色の弾の速度
//#define SAKUYA_ATTACK_2_SHOT_R				3		//　弾の半径
//#define SAKUYA_ATTACK_2_SPEED				1.5f	//　赤色の敵の移動スピード
//#define SAKUYA_ATTACK_2_ROT_SIZE			10		//　赤色の敵の弾の一つ一つの隙間の角度
//
////　３
//#define SAKUYA_ATTACK_3_ARRAY_MAX			25		//　数
//#define SAKUYA_ATTACK_3_ARRAY_CC			10		//　タイミング
//#define SAKUYA_ATTACK_3_CIRCLE_SIZE			4		//　サイズ
//#define SAKUYA_ATTACK_3_INTERVAL			30		//　一つ一つの間隔
//#define SAKUYA_ATTACK_3_MAX					4		//　何列あるか
//
////　４
//#define SAKUYA_ATTACK_4_ARRAY_MAX			25		//　数
//#define SAKUYA_ATTACK_4_ARRAY_CC			10		//　タイミング
//#define SAKUYA_ATTACK_4_SIZE				4		//　サイズ
//#define SAKUYA_ATTACK_4_INTERVAL			30		//　間隔
//#define SAKUYA_ATTACK_4_MAX					4		//　何列あるか
//
////　咲夜の移動位置
//#define SAKUYA_START						-20				//　スタート位置	
//#define SAKUYA_POSITION_1_Y					100				//　最初のポジ
//#define SAKUYA_POSITION_2_X					BG_X_LW + 40	//　次のポジ
//#define SAKUYA_POSITION_3_X					BG_X_HW - 40	//　同上
//#define SAKUYA_POSITION_3_Y					WINDOW_H / 2	//　同上
//#define SAKUYA_POSITION_4_Y					140				//　同上
//
////　次の攻撃に行くタイミング
//#define SAKUYA_ATTACK_1_COUNT_1				200		//　中央から左
//#define SAKUYA_ATTACK_1_COUNT_2				100		//　左から右
//#define SAKUYA_ATTACK_1_COUNT_3				200		//　右から中央
//#define SAKUYA_ATTACK_1_COUNT_4				240		//　中央から中心　（SecondAttack）
//#define SAKUYA_ATTACK_2_COUNT_1				1000	//　中心のばらまき
//#define SAKUYA_ATTACK_3_COUNT_1				540		//　だんだん出すやつ
//#define SAKUYA_ATTACK_4_COUNT_1				540		//　だんだん出して止まる
//#define SAKUYA_ATTACK_5_COUNT_1				1600	//　１と２の攻撃
//#define SAKUYA_ATTACK_6_COUNT_1				540		//　よくわからん
//
//#define ENEMY_RB_IMG_TIMING					8
//#define ENEMY_RB_IMG_WIDTH					32
//#define ENEMY_RB_IMG_HEIGHT					33
//#define ENEMY_RB_IMG_WIDTH_MAX				192
//#define ENEMY_RB_IMG_SAME_SIZE				1.1

#define ATTACK_NO 16

// =====================================================
// 敵の出現タイミング（数字は敵の種類には関係しない）

#define ATTACK_1_TIMING		10
#define ATTACK_2_TIMING		350
#define ATTACK_3_TIMING		750	
#define ATTACK_4_TIMING		950
#define ATTACK_5_TIMING		1150
#define ATTACK_6_TIMING		1350
#define ATTACK_7_TIMING		1450
#define ATTACK_8_TIMING		1750
#define ATTACK_9_TIMING		2000
#define ATTACK_10_TIMING	2300
#define ATTACK_11_TIMING	2600
#define ATTACK_12_TIMING	2800
#define ATTACK_13_TIMING	3000
#define ATTACK_14_TIMING	3300
#define ATTACK_15_TIMING	3600
#define ATTACK_16_TIMING	4000
#define ATTACK_BOSS_TIMING	4500			//　ボス戦

// =====================================================
// 敵の半径
#define ATTACK_1_2_ROT_SIZE			5	//　ATTACK_1_2_MAX,	ATTACK_1_2__NUM,	zako_attack_1_coordinate[i][j].x,	zako_attack_1_coordinate[i][j].y		zako_attack_2_coordinate[i][j].x,			zako_attack_2_coordinate[i][j].y
#define ATTACK_3_4_ROT_SIZE			7	//　ATTACK_3_4_MAX,						zako_attack_3_coordinate[i].x,		zako_attack_3_coordinate[i].y			zako_attack_4_coordinate[i].x,				zako_attack_4_coordinate[i].y
#define ATTACK_5_ROT_SIZE			7	//　									attack_5_coordinate.x,				attack_5_coordinate.y
#define ATTACK_5_ZAKO_ROT_SIZE		7	//　ATTACK_5_MAX,						attack_5_zako_coordinate[i].x,		attack_5_zako_coordinate[i].y
#define ATTACK_6_ROT_SIZE			7	//　									attack_6_teki_coordinate.x,			attack_6_teki_coordinate.y
#define ATTACK_6_ZAKO_ROT_SIZE		7	//　ATTACK_6_MAX,						attack_6_zako_coordinate[i].x,		attack_6_zako_coordinate[i].y
#define ATTACK_7_ROT_SIZE			7	//　ATTACK_7_MAX,						attack_7_zako_coordinate[i].x,		attack_7_zako_coordinate[i].y
#define ATTACK_8_ROT_SIZE			7	//　ATTACK_8_MAX,						attack_8_zako_coordinate[i].x,		attack_8_zako_coordinate[i].y
#define ATTACK_9_ROT_SIZE			8	//　ATTACK_9_NUM,						attack_9_zako_coordinate[i].x,		attack_9_zako_coordinate[i].y			attack_9_nekomimi_attack_coordinate.x,		attack_9_nekomimi_attack_coordinate.y,
#define ATTACK_10_ROT_SIZE			8	//　ATTACK_10_NUM,						attack_10_zako_coordinate[i].x,		attack_10_zako_coordinate[i].y			attack_10_nekomimi_attack_coordinate.x,		attack_10_nekomimi_attack_coordinate.y
#define ATTACK_11_ROT_SIZE			8	//　ATTACK_11_NUM,						attack_11_zako_coordinate[i].x,		attack_11_zako_coordinate[i].y			attack_11_nekomimi_attack_coordinate.x,		attack_11_nekomimi_attack_coordinate.y
#define ATTACK_12_ROT_SIZE			8	//　attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y

// =====================================================
// 敵の弾の半径
#define ATTACK_1_2_SHOT_ROT_SIZE			4	//　ATTACK_1_2_MAX,		ATTACK_1_2__NUM,	zako_attack_1_shot_coordinate[i][j].x,				zako_attack_1_shot_coordinate[i][j].y				zako_attack_2_shot_coordinate[i][j].x,		zako_attack_2_shot_coordinate[i][j].y
#define ATTACK_3_4_SHOT_ROT_SIZE			5	//　ATTACK_3_4_MAX,		ATTACK_3_4_NUM,		zako_attack_3_shot_coordinate[i][j].x,				zako_attack_3_shot_coordinate[i][j].y				zako_attack_4_shot_coordinate[i][j].x,		zako_attack_4_shot_coordinate[i][j].y
#define ATTACK_5_SHOT_ROT_SIZE				5	//　ATTACK_5_SHOT_NUM,						attack_5_shot_coordinate[p].x,						attack_5_shot_coordinate[p].y
#define ATTACK_5_NEKOMIMI_SHOT_ROT_SIZE		4	//　NEKOMIMI_MAX,		NEKOMIMI_NUM,		attack_5_nekomimi_attack_shot_coordinate[i][j].x,	attack_5_nekomimi_attack_shot_coordinate[i][j].y
#define ATTACK_5_ZAKO_SHOT_ROT_SIZE			5	//　ATTACK_5_MAX,		ATTACK_5_NUM,		attack_5_zako_shot_coordinate[i][j].x,				attack_5_zako_shot_coordinate[i][j].y
#define ATTACK_6_SHOT_ROT_SIZE				5	//　ATTACK_6_SHOT_NUM,						attack_6_teki_shot_coordinate[p].x,					attack_6_teki_shot_coordinate[p].y
#define ATTACK_6_NEKOMIMI_SHOT_ROT_SIZE		4	//　NEKOMIMI_MAX,		NEKOMIMI_NUM,		attack_6_nekomimi_attack_shot_coordinate[i][j].x,	attack_6_nekomimi_attack_shot_coordinate[i][j].y
#define ATTACK_6_ZAKO_SHOT_ROT_SIZE			5	//　ATTACK_6_MAX,		ATTACK_6_NUM,		attack_6_zako_shot_coordinate[i][j].x,				attack_6_zako_shot_coordinate[i][j].y
#define ATTACK_7_SHOT_ROT_SIZE				5	//　ATTACK_7_MAX,		ATTACK_7_NUM,		attack_7_zako_shot_coordinate[i][j].x,				attack_7_zako_shot_coordinate[i][j].y
#define ATTACK_8_SHOT_ROT_SIZE				5	//　ATTACK_8_MAX,		ATTACK_8_NUM,		attack_8_zako_shot_coordinate[i][j].x,				attack_8_zako_shot_coordinate[i][j].y
#define ATTACK_9_SHOT_ROT_SIZE				4	//　ATTACK_9_NUM,		ATTACK_9_MAX,		attack_9_zako_shot_coordinate[i][j].x,				attack_9_zako_shot_coordinate[i][j].y				ATTACK_9_NEKOMIMI_MAX,		ATTACK_9_NEKOMIMI_NUM,		attack_9_nekomimi_attack_shot_coordinate[i][j].x,		attack_9_nekomimi_attack_shot_coordinate[i][j].y
#define ATTACK_10_SHOT_ROT_SIZE				4	//　ATTACK_10_NUM,		ATTACK_10_MAX,		attack_10_zako_shot_coordinate[i][j].x,				attack_10_zako_shot_coordinate[i][j].y				ATTACK_10_NEKOMIMI_MAX,		ATTACK_10_NEKOMIMI_NUM,		attack_10_nekomimi_attack_shot_coordinate[i][j].x,		attack_10_nekomimi_attack_shot_coordinate[i][j].y
#define ATTACK_11_SHOT_ROT_SIZE				4	//　ATTACK_11_NUM,		ATTACK_11_MAX,		attack_11_zako_shot_coordinate[i][j].x,				attack_11_zako_shot_coordinate[i][j].y				ATTACK_11_NEKOMIMI_MAX,		ATTACK_11_NEKOMIMI_NUM,		attack_11_nekomimi_attack_shot_coordinate[i][j].x,		attack_11_nekomimi_attack_shot_coordinate[i][j].y
#define ATTACK_12_SHOT_ROT					3	//　ATTACK_12_SHOT_MAX, attack_12_circle_shot[i].x, attack_12_circle_shot[i].y, ATTACK_12_NEKOMIMI_MAX, ATTACK_12_NEKOMIMI_NUM, attack_12_nekomimi_attack_shot_coordinate[i][j].x, attack_12_nekomimi_attack_shot_coordinate[i][j].y

// =====================================================
// 攻撃１＆２

#define ATTACK_1_2_MAX			5
#define ATTACK_1_2__NUM			2

#define ATTACK_SHOT_SPEED		1.5f	
#define ATTACK_SPEED_X			1.1f
#define ATTACK_SPEED_Y			1.0f
#define ATTACK_SHOT_TIMING		60
#define ATTACK_STOP_TIMING		60

// =====================================================
// 攻撃３＆４

#define ATTACK_3_4_MAX	6
#define ATTACK_3_4_NUM 2

// =====================================================
// 攻撃５

#define ATTACK_5_SHOT_NUM 15

#define ATTACK_5_MAX	3
#define ATTACK_5_NUM 2

//　猫耳
#define NEKOMIMI_MAX	10
#define NEKOMIMI_NUM	3

// =====================================================
// 攻撃６

#define ATTACK_6_SHOT_NUM 15

#define ATTACK_6_MAX	3
#define ATTACK_6_NUM 2

// =====================================================
// 攻撃７

#define ATTACK_7_MAX	8
#define ATTACK_7_NUM 3

// =====================================================
// 攻撃８

#define ATTACK_8_MAX	8
#define ATTACK_8_NUM 3

// =====================================================
// 攻撃９

#define ATTACK_9_NEKOMIMI_MAX	10
#define ATTACK_9_NEKOMIMI_NUM	6

#define ATTACK_9_NUM	6
#define ATTACK_9_MAX	2

// =====================================================
// 攻撃１０

#define ATTACK_10_NEKOMIMI_MAX	10
#define ATTACK_10_NEKOMIMI_NUM	6

#define ATTACK_10_NUM	 6
#define ATTACK_10_MAX	2

// =====================================================
// 攻撃１１

#define ATTACK_11_NEKOMIMI_MAX	10
#define ATTACK_11_NEKOMIMI_NUM	6

#define ATTACK_11_NUM	 6
#define ATTACK_11_MAX	2

// =====================================================
// 攻撃１２

#define ATTACK_12_NEKOMIMI_MAX	10
#define ATTACK_12_NEKOMIMI_NUM	12

#define ATTACK_12_SHOT_MAX				36		//　一回に出す弾の数
#define ATTACK_12_COUNT_TIMING			70		//　弾を出すタイミング
#define ATTACK_12_SPEED_SWAY			1.0f	//　赤色の弾の速度
#define ATTACK_12_ROT_DIRECTLY_BELOW	90	//　真下に向けるための角度　９０度
#define ATTACK_12_SPEED					1.5f	//　赤色の敵の移動スピード
#define ATTACK_12_SPACE_SIZE			10		//　赤色の敵の弾の一つ一つの隙間の角度

// =====================================================
//	ボス
// =====================================================

#define BOSS_ROT_SIZE			10	//　ボスの半径

#define BOSS_ATTACK_NONE		120
#define BOSS_ATTACK_TIMING_1	1800
#define BOSS_ATTACK_TIMING_2	1800
#define BOSS_ATTACK_TIMING_3	1800
#define BOSS_ATTACK_TIMING_4	1800

// ==========================================================================================================
//　ステージ１攻撃１

// =====================================================
//　出すタイミング
#define BOSS_C1 0
#define BOSS_C2 300
#define BOSS_C3 600
#define BOSS_C4 900
#define BOSS_C5 1200
#define BOSS_C6 1500
// =====================================================

// =====================================================
//　時計回り１
#define BOSS_BIG_LEFT_1_SHOT_MAX 9
#define BOSS_BIG_LEFT_1_SHOT_NUM 4
#define BOSS_BIG_LEFT_1_SHOT_SPEED 0.6f
#define BOSS_BIG_LEFT_1_SHOT_SIZE 10
#define BOSS_BIG_LEFT_1_SHOT_TIMING 40

#define BOSS_SMALL_LEFT_1_SHOT_MAX 9
#define BOSS_SMALL_LEFT_1_SHOT_NUM 3
#define BOSS_SMALL_LEFT_1_SHOT_SPEED 0.7f
#define BOSS_SMALL_LEFT_1_SHOT_SIZE 5
#define BOSS_SMALL_LEFT_1_SHOT_TIMING 30
// =====================================================

// =====================================================
//　反時計回り１
#define BOSS_BIG_RIGHT_1_SHOT_MAX 9
#define BOSS_BIG_RIGHT_1_SHOT_NUM 4
#define BOSS_BIG_RIGHT_1_SHOT_SPEED 0.6f
#define BOSS_BIG_RIGHT_1_SHOT_SIZE 10
#define BOSS_BIG_RIGHT_1_SHOT_TIMING 40

#define BOSS_SMALL_RIGHT_1_SHOT_MAX 9
#define BOSS_SMALL_RIGHT_1_SHOT_NUM 3
#define BOSS_SMALL_RIGHT_1_SHOT_SPEED 0.7f
#define BOSS_SMALL_RIGHT_1_SHOT_SIZE 5
#define BOSS_SMALL_RIGHT_1_SHOT_TIMING 30
// =====================================================

// =====================================================
//　時計回り２
#define BOSS_BIG_LEFT_2_SHOT_MAX 9
#define BOSS_BIG_LEFT_2_SHOT_NUM 4
#define BOSS_BIG_LEFT_2_SHOT_SPEED 0.6f
#define BOSS_BIG_LEFT_2_SHOT_SIZE 10
#define BOSS_BIG_LEFT_2_SHOT_TIMING 40

#define BOSS_SMALL_LEFT_2_SHOT_MAX 9
#define BOSS_SMALL_LEFT_2_SHOT_NUM 3
#define BOSS_SMALL_LEFT_2_SHOT_SPEED 0.7f
#define BOSS_SMALL_LEFT_2_SHOT_SIZE 5
#define BOSS_SMALL_LEFT_2_SHOT_TIMING 30
// =====================================================

// =====================================================
//　反時計回り２
#define BOSS_BIG_RIGHT_2_SHOT_MAX 9
#define BOSS_BIG_RIGHT_2_SHOT_NUM 4
#define BOSS_BIG_RIGHT_2_SHOT_SPEED 0.6f
#define BOSS_BIG_RIGHT_2_SHOT_SIZE 10
#define BOSS_BIG_RIGHT_2_SHOT_TIMING 40

#define BOSS_SMALL_RIGHT_2_SHOT_MAX 9
#define BOSS_SMALL_RIGHT_2_SHOT_NUM 3
#define BOSS_SMALL_RIGHT_2_SHOT_SPEED 0.7f
#define BOSS_SMALL_RIGHT_2_SHOT_SIZE 5
#define BOSS_SMALL_RIGHT_2_SHOT_TIMING 30
// =====================================================

// =====================================================
//　時計回り３
#define BOSS_BIG_LEFT_3_SHOT_MAX 9
#define BOSS_BIG_LEFT_3_SHOT_NUM 4
#define BOSS_BIG_LEFT_3_SHOT_SPEED 0.6f
#define BOSS_BIG_LEFT_3_SHOT_SIZE 10
#define BOSS_BIG_LEFT_3_SHOT_TIMING 40

#define BOSS_SMALL_LEFT_3_SHOT_MAX 9
#define BOSS_SMALL_LEFT_3_SHOT_NUM 3
#define BOSS_SMALL_LEFT_3_SHOT_SPEED 0.7f
#define BOSS_SMALL_LEFT_3_SHOT_SIZE 5
#define BOSS_SMALL_LEFT_3_SHOT_TIMING 30
// =====================================================

// =====================================================
//　反時計回り３
#define BOSS_BIG_RIGHT_3_SHOT_MAX 9
#define BOSS_BIG_RIGHT_3_SHOT_NUM 4
#define BOSS_BIG_RIGHT_3_SHOT_SPEED 0.6f
#define BOSS_BIG_RIGHT_3_SHOT_SIZE 10
#define BOSS_BIG_RIGHT_3_SHOT_TIMING 40

#define BOSS_SMALL_RIGHT_3_SHOT_MAX 9
#define BOSS_SMALL_RIGHT_3_SHOT_NUM 3
#define BOSS_SMALL_RIGHT_3_SHOT_SPEED 0.7f
#define BOSS_SMALL_RIGHT_3_SHOT_SIZE 5
#define BOSS_SMALL_RIGHT_3_SHOT_TIMING 30
// =====================================================
// ==========================================================================================================

// ==========================================================================================================
//　ステージ１攻撃２
#define BOSS_RAND_SIZE1	3
#define BOSS_RAND_SIZE2	5
#define BOSS_RAND_SIZE3	10

#define BOSS_RAND_NUM1	60
#define BOSS_RAND_NUM2	40
#define BOSS_RAND_NUM3	20
// ==========================================================================================================

// ==========================================================================================================
//　ステージ２
#define BOSS_ROTATE_MAX		50
#define BOSS_ROTATE_COUNT	180
#define BOSS_ROTATE_NUM		2
#define BOSS_ROTATE_NUMBER	2

#define BOSS_ROTATE_COUNT_TIMING	60
#define BOSS_ROTATE_SHOT_MAX		30
#define BOSS_ROTATE_SHOT_SPEED	0.8f
#define BOSS_ROTATE_SHOT_SIZE	4

#define BOSS_NEKOMIMI_MAX	10
#define BOSS_NEKOMIMI_NUM	12

#define BOSS_SMALL_SHOT_MAX 12
#define BOSS_SMALL_SHOT_SPEED 0.4f
#define BOSS_SMALL_SHOT_SIZE 4
#define BOSS_SMALL_SHOT_TIMING 40

#define BOSS_SMALL_AMAX 12
#define BOSS_SMALL_SPEED 0.4f
#define BOSS_SMALL_SIZE 4
#define BOSS_SMALL_TIMING 40
// ==========================================================================================================

// ==========================================================================================================
//　ステージ３
#define BOSS_FURAN_RED_SHOT_MAX				24							//　一回に出す弾の数
#define BOSS_FURAN_RED_NUM_MAX				250							//　弾の最大（これ以上行くと０に戻すので無限に撃つ）
#define BOSS_FURAN_RED_COUNT_TIMING			80							//　弾を出すタイミング
#define BOSS_FURAN_RED_SPEED_SWAY			0.5f						//　赤色の弾の速度
#define BOSS_FURAN_RED_R					4							//　赤色の雑魚敵の大きさ
#define BOSS_FURAN_RED_SHOT_R				5							//　弾の半径
#define BOSS_FURAN_RED_ROT_DIRECTLY_BELOW	90							//　真下に向けるための角度　９０度
#define BOSS_FURAN_RED_ROT_SIZE				360 / BOSS_FURAN_RED_SHOT_MAX	//　赤色の敵の弾の一つ一つの隙間の角度

#define BOSS_FURAN_BLUE_SHOT_MAX				36							//　一回に出す弾の数
#define BOSS_FURAN_BLUE_NUM_MAX				80							//　弾の最大（これ以上行くと０に戻すので無限に撃つ）
#define BOSS_FURAN_BLUE_COUNT_TIMING			180							//　弾を出すタイミング
#define BOSS_FURAN_BLUE_SPEED_SWAY			0.6f						//　赤色の弾の速度
#define BOSS_FURAN_BLUE_SHOT_R				5							//　弾の半径
#define BOSS_FURAN_BLUE_ROT_DIRECTLY_BELOW	90							//　真下に向けるための角度　９０度
#define BOSS_FURAN_BLUE_ROT_SIZE				360 / BOSS_FURAN_BLUE_SHOT_MAX	//　赤色の敵の弾の一つ一つの隙間の角度
#define BOSS_FURAN_BLUE_LB					2							//　左右

#define BOSS_FURAN_PURPLE_SHOT_MAX				24							//　一回に出す弾の数
#define BOSS_FURAN_PURPLE_NUM_MAX				100							//　弾の最大（これ以上行くと０に戻すので無限に撃つ）
#define BOSS_FURAN_PURPLE_COUNT_TIMING			50							//　弾を出すタイミング
#define BOSS_FURAN_PURPLE_SPEED_SWAY				0.8f						//　赤色の弾の速度
#define BOSS_FURAN_PURPLE_SHOT_R					5							//　弾の半径
#define BOSS_FURAN_PURPLE_ROT_DIRECTLY_BELOW		90							//　真下に向けるための角度　９０度
#define BOSS_FURAN_PURPLE_ROT_SIZE				360 / BOSS_FURAN_PURPLE_SHOT_MAX	//　赤色の敵の弾の一つ一つの隙間の角度
// ==========================================================================================================

// =====================================================
// 雑魚敵のＨＰ管理（初期値）
// =====================================================
#define HP_MAX_LEVEL1	2
#define HP_MAX_LEVEL2	7
#define HP_MAX_LEVEL3	20

// =====================================================
// ボスのＨＰ管理（初期値）
// =====================================================
#define BOSS_MAX_HP1	500
#define BOSS_MAX_HP2	500
#define BOSS_MAX_HP3	500

// =====================================================
// 雑魚敵のＥＸＰ管理（初期値）
// =====================================================
#define EXP_LEVEL1	5
#define EXP_LEVEL2	8
#define EXP_LEVEL3	10

// =====================================================
// 雑魚敵のスコア管理（初期値）
// =====================================================
#define SCORE_LEVEL1	30
#define SCORE_LEVEL2	50
#define SCORE_LEVEL3	100

// =====================================================
// ボスのスコア管理（初期値）
// =====================================================

//　倒したとき
#define BOSS_SCORE_LEVEL1	1000
#define BOSS_SCORE_LEVEL2	1500
#define BOSS_SCORE_LEVEL3	2000

//　与えたダメージ
#define BOSS_HIT_DAMAG	250

//　画像
#define ENEMY_RB_IMG_TIMING					8
#define ENEMY_RB_IMG_WIDTH					32
#define ENEMY_RB_IMG_HEIGHT					32
#define ENEMY_RB_IMG_WIDTH_MAX				192
#define ENEMY_RB_IMG_SAME_SIZE				1.1
