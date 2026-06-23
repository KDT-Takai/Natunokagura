#include "WinMain.h"
// 「Timingゲーム」の作成

// =====================================================
// 定数
// 変数に「const」を付けると、代入禁止の変数（＝定数）となる
// =====================================================

////　画面の範囲
//#define BG_X_LW 31		//　左
//#define BG_X_HW 416		//　右
//#define BG_Y_LH 14		//　上
//#define BG_Y_HH 463		//　下
////　初期値の０に戻す際の定数
//#define START_ZERO 0
////　DrawCircleAAの角形
//#define CIRCLEAA_SQUARE	64		//　何角形か

//int stage_map_mode;	//　０：なしの状態　１：雑魚敵２体　２：雑魚敵４体　３：咲夜　４：雑魚敵６体　５：フラン　６：フラン＆レミリア
//
//enum StageMap {
//	StageNull,
//	StageFirst,
//	StageSecond,
//	StageThird,
//	StageFourth,
//	StageFifth,
//	StageSixth,
//};

//　ゲーム画面操作
extern int game_start_mode;
extern enum
{
	Menu,
	Character,
	Game,
	Options,
	Game_Clear,
	Game_Dead,
};

// =====================================================
//	グローバル変数
//	複数の関数で共通して使いたい変数はここに書く
// =====================================================

struct Floatxy {
	float x;	//　ｘ座標
	float y;	//　ｙ座標
};

enum {
	MODE_WAIT,
	MODE_MOVE,
};

enum {
	HIDDEN,		//　隠れてる
	DISPLAY,	//　出てる
};

bool	game_shot[ATTACK_NO];	//　ゲームのモード
int		frame_count;		//　フレームのカウント


// =====================================================
// 攻撃１


Floatxy zako_attack_1_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];				//　敵		座標								
Floatxy zako_attack_1_shot_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　敵の弾　座標					
int		zako_attack_1_count[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
int		zako_attack_1_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
float	zako_attack_1_angle[ATTACK_1_2_MAX][ATTACK_1_2__NUM];

int		display_handle_1_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];					//　敵を表示するかしないか
int		display_handle_1_shot_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　弾の表示するかしないか

int		attack_1_hp[ATTACK_1_2_MAX][ATTACK_1_2__NUM];

// =====================================================
// 攻撃２

Floatxy zako_attack_2_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];				//　敵		座標							
Floatxy zako_attack_2_shot_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　敵の弾　座標								
int		zako_attack_2_count[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
int		zako_attack_2_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
float	zako_attack_2_angle[ATTACK_1_2_MAX][ATTACK_1_2__NUM];

int		display_handle_2_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];					//　敵を表示するかしないか
int		display_handle_2_shot_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　弾の表示するかしないか

int		attack_2_hp[ATTACK_1_2_MAX][ATTACK_1_2__NUM];

// =====================================================
// 攻撃３


Floatxy zako_attack_3_coordinate[ATTACK_3_4_MAX];								//　敵		座標			
Floatxy zako_attack_3_shot_coordinate[ATTACK_3_4_MAX][ATTACK_3_4_NUM];			//　敵の弾　座標								
int		zako_attack_3_count[ATTACK_3_4_MAX];
int		zako_attack_3_mode[ATTACK_3_4_MAX];
int		zako_attack_3_shot_mode[ATTACK_3_4_MAX];
float	zako_attack_3_angle[ATTACK_3_4_MAX][ATTACK_3_4_NUM];
float	zako_attack_3_y;

int		display_handle_3_mode[ATTACK_3_4_MAX];									//　敵を表示するかしないか
int		display_handle_3_shot_mode[ATTACK_3_4_MAX][ATTACK_3_4_NUM];				//　弾の表示するかしないか

int		attack_3_hp[ATTACK_3_4_MAX];

// =====================================================
// 攻撃４

Floatxy zako_attack_4_coordinate[ATTACK_3_4_MAX];								//　敵		座標			
Floatxy zako_attack_4_shot_coordinate[ATTACK_3_4_MAX][ATTACK_3_4_NUM];			//　敵の弾　座標								
int		zako_attack_4_count[ATTACK_3_4_MAX];
int		zako_attack_4_mode[ATTACK_3_4_MAX];
int		zako_attack_4_shot_mode[ATTACK_3_4_MAX];
float	zako_attack_4_angle[ATTACK_3_4_MAX][ATTACK_3_4_NUM];
float	zako_attack_4_y;

int		display_handle_4_mode[ATTACK_3_4_MAX];									//　敵を表示するかしないか
int		display_handle_4_shot_mode[ATTACK_3_4_MAX][ATTACK_3_4_NUM];				//　弾の表示するかしないか

int		attack_4_hp[ATTACK_3_4_MAX];

// =====================================================
// 攻撃５


Floatxy attack_5_coordinate;													//　敵		座標
Floatxy attack_5_shot_coordinate[ATTACK_5_SHOT_NUM];							//　敵の弾　座標
float	attack_5_shot_r[ATTACK_5_SHOT_NUM];

int		display_handle_5_c_mode;												//　敵を表示するかしないか
int		display_handle_5_c_shot_mode[ATTACK_5_SHOT_NUM];						//　弾の表示するかしないか

int		attack_5_hp;

Floatxy attack_5_zako_coordinate[ATTACK_5_MAX];									//　敵		座標	
Floatxy attack_5_zako_shot_coordinate[ATTACK_5_MAX][ATTACK_5_NUM];				//　敵の弾　座標						
int		attack_5_zako_count[ATTACK_5_MAX];
int		attack_5_zako_mode[ATTACK_5_MAX];
int		attack_5_zako_shot_mode[ATTACK_5_MAX];
float	attack_5_angle[ATTACK_5_MAX][ATTACK_5_NUM];
float	attack_5_y;

int		display_handle_5_mode[ATTACK_5_MAX];									//　敵を表示するかしないか
int		display_handle_5_shot_mode[ATTACK_5_MAX][ATTACK_5_NUM];					//　弾の表示するかしないか

int		attack_zako_5_hp[ATTACK_5_MAX];

//　猫耳

Floatxy attack_5_nekomimi_attack_shot_coordinate[NEKOMIMI_MAX][NEKOMIMI_NUM];	//　敵の弾　座標
int		attack_5_nekomimi_attack_count[NEKOMIMI_MAX][NEKOMIMI_NUM];
float	attack_5_nekomimi_attack_missile_rot[NEKOMIMI_MAX][NEKOMIMI_NUM];
float	attack_5_nekomimi_attack_speed[NEKOMIMI_MAX][NEKOMIMI_NUM];
float	attack_5_nekomimi_attack_angle;
int		attack_5_nekomimi_attack_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];
int		display_handle_5_nekomimi_shot_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];		//　弾の表示するかしないか

// =====================================================
// 攻撃６


Floatxy attack_6_teki_coordinate;												//　敵	　座標
Floatxy attack_6_teki_shot_coordinate[ATTACK_6_SHOT_NUM];						//　敵の弾　座標
float	attack_6_teki_shot_r[ATTACK_6_SHOT_NUM];

int		display_handle_6_c_mode;												//　敵を表示するかしないか
int		display_handle_6_c_shot_mode[ATTACK_6_SHOT_NUM];						//　弾の表示するかしないか

int		attack_6_hp;

Floatxy attack_6_zako_coordinate[ATTACK_6_MAX];									//　敵	　座標	
Floatxy attack_6_zako_shot_coordinate[ATTACK_6_MAX][ATTACK_6_NUM];				//　敵の弾　座標						
int		attack_6_zako_count[ATTACK_6_MAX];
int		attack_6_zako_mode[ATTACK_6_MAX];
int		attack_6_zako_shot_mode[ATTACK_6_MAX];
float	attack_6_angle[ATTACK_6_MAX][ATTACK_6_NUM];
float	attack_6_y;

int		display_handle_6_mode[ATTACK_6_MAX];									//　敵を表示するかしないか
int		display_handle_6_shot_mode[ATTACK_6_MAX][ATTACK_6_NUM];					//　弾の表示するかしないか

int		attack_zako_6_hp[ATTACK_6_MAX];

Floatxy attack_6_nekomimi_attack_shot_coordinate[NEKOMIMI_MAX][NEKOMIMI_NUM];	//　敵	　座標
int		attack_6_nekomimi_attack_count[NEKOMIMI_MAX][NEKOMIMI_NUM];				//　敵の弾　座標
float	attack_6_nekomimi_attack_missile_rot[NEKOMIMI_MAX][NEKOMIMI_NUM];
float	attack_6_nekomimi_attack_speed[NEKOMIMI_MAX][NEKOMIMI_NUM];
float	attack_6_nekomimi_attack_angle;
int		attack_6_nekomimi_attack_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];
int		display_handle_6_nekomimi_shot_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];		//　弾の表示するかしないか

// =====================================================
// 攻撃７

Floatxy attack_7_zako_coordinate[ATTACK_7_MAX];
Floatxy attack_7_zako_shot_coordinate[ATTACK_7_MAX][ATTACK_7_NUM];
int		attack_7_zako_count[ATTACK_7_MAX];
int		attack_7_zako_mode[ATTACK_7_MAX];
int		attack_7_zako_shot_mode[ATTACK_7_MAX];
float	attack_7_angle[ATTACK_7_MAX][ATTACK_7_NUM];
int		attack_7_num;
int		attack_7_count;
float	attack_7_y[ATTACK_7_MAX];

int		display_handle_7_mode[ATTACK_7_MAX];									//　敵を表示するかしないか
int		display_handle_7_shot_mode[ATTACK_7_MAX][ATTACK_7_NUM];					//　弾の表示するかしないか

int		attack_7_hp[ATTACK_7_MAX];

// =====================================================
// 攻撃８

Floatxy attack_8_zako_coordinate[ATTACK_8_MAX];
Floatxy attack_8_zako_shot_coordinate[ATTACK_8_MAX][ATTACK_8_NUM];
int		attack_8_zako_count[ATTACK_8_MAX];
int		attack_8_zako_mode[ATTACK_8_MAX];
int		attack_8_zako_shot_mode[ATTACK_8_MAX];
float	attack_8_angle[ATTACK_8_MAX][ATTACK_8_NUM];
int		attack_8_num;
int		attack_8_count;
float	attack_8_y[ATTACK_8_MAX];

int		display_handle_8_mode[ATTACK_8_MAX];									//　敵を表示するかしないか
int		display_handle_8_shot_mode[ATTACK_8_MAX][ATTACK_8_NUM];					//　弾の表示するかしないか

int		attack_8_hp[ATTACK_8_MAX];

// =====================================================
// 攻撃９

Floatxy attack_9_nekomimi_attack_coordinate;
Floatxy attack_9_nekomimi_attack_shot_coordinate[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];
int		attack_9_nekomimi_attack_count[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];
float	attack_9_nekomimi_attack_missile_rot[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];
float	attack_9_nekomimi_attack_speed[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];
float	attack_9_nekomimi_attack_angle;
int		attack_9_nekomimi_attack_mode[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];

int		display_handle_9_nekomimi_mode;																//　敵を表示するかしないか
int		display_handle_9_nekomimi_shot_mode[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];			//　弾の表示するかしないか

int		attack_9_hp;

Floatxy attack_9_zako_coordinate[ATTACK_9_NUM];
Floatxy attack_9_zako_shot_coordinate[ATTACK_9_NUM][ATTACK_9_MAX];
int		attack_9_zako_mode[ATTACK_9_NUM];
float	attack_9_angle[ATTACK_9_NUM][ATTACK_9_MAX];

int		display_handle_9_mode[ATTACK_9_NUM];									//　敵を表示するかしないか
int		display_handle_9_shot_mode[ATTACK_9_NUM][ATTACK_9_MAX];					//　弾の表示するかしないか

int		attack_zako_9_hp[ATTACK_9_NUM];

// =====================================================
// 攻撃１０

Floatxy attack_10_nekomimi_attack_coordinate;
Floatxy attack_10_nekomimi_attack_shot_coordinate[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];
int		attack_10_nekomimi_attack_count[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];
float	attack_10_nekomimi_attack_missile_rot[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];
float	attack_10_nekomimi_attack_speed[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];
float	attack_10_nekomimi_attack_angle;
int		attack_10_nekomimi_attack_mode[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];

int		display_handle_10_nekomimi_mode;															//　敵を表示するかしないか
int		display_handle_10_nekomimi_shot_mode[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];		//　弾の表示するかしないか

int		attack_10_hp;

Floatxy attack_10_zako_coordinate[ATTACK_10_NUM];
Floatxy attack_10_zako_shot_coordinate[ATTACK_10_NUM][ATTACK_10_MAX];
int		attack_10_zako_mode[ATTACK_10_NUM];
float	attack_10_angle[ATTACK_10_NUM][ATTACK_10_MAX];

int		display_handle_10_mode[ATTACK_10_NUM];									//　敵を表示するかしないか
int		display_handle_10_shot_mode[ATTACK_10_NUM][ATTACK_10_MAX];				//　弾の表示するかしないか

int		attack_zako_10_hp[ATTACK_10_NUM];

// =====================================================
// 攻撃１１

Floatxy attack_11_nekomimi_attack_coordinate;
Floatxy attack_11_nekomimi_attack_shot_coordinate[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];
int		attack_11_nekomimi_attack_count[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];
float	attack_11_nekomimi_attack_missile_rot[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];
float	attack_11_nekomimi_attack_speed[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];
float	attack_11_nekomimi_attack_angle;
int		attack_11_nekomimi_attack_mode[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];

int		display_handle_11_nekomimi_mode;																//　敵を表示するかしないか
int		display_handle_11_nekomimi_shot_mode[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];			//　弾の表示するかしないか

int		attack_11_hp;

Floatxy attack_11_zako_coordinate[ATTACK_11_NUM];
Floatxy attack_11_zako_shot_coordinate[ATTACK_11_NUM][ATTACK_11_MAX];
int		attack_11_zako_mode[ATTACK_11_NUM];
float	attack_11_angle[ATTACK_11_NUM][ATTACK_11_MAX];

int		display_handle_11_mode[ATTACK_11_NUM];									//　敵を表示するかしないか
int		display_handle_11_shot_mode[ATTACK_11_NUM][ATTACK_11_MAX];				//　弾の表示するかしないか

int		attack_zako_11_hp[ATTACK_11_NUM];

// =====================================================
// 攻撃１２

Floatxy attack_12_nekomimi_coordinate;
float	attack_12_coordinate_y;

Floatxy attack_12_nekomimi_attack_shot_coordinate[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];
int		attack_12_nekomimi_attack_count[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];
float	attack_12_nekomimi_attack_missile_rot[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];
float	attack_12_nekomimi_attack_speed[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];
float	attack_12_nekomimi_attack_angle;
int		attack_12_nekomimi_attack_mode[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];

int		display_handle_12_nekomimi_shot_mode[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];			//　弾の表示するかしないか

Floatxy attack_12_circle_shot[ATTACK_12_SHOT_MAX];			//　赤色の雑魚敵の弾
float	attack_12_circle_target_angle[ATTACK_12_SHOT_MAX];	//　赤色の目的角度
int		attack_12_circle_mode[ATTACK_12_SHOT_MAX];			//　赤色のモード
enum
{
	MODE_12_WAIT,
	MODE_12_PREPARATION,
	MODE_12_SPREAD,
	MODE_12_FACE,
	MODE_12_STOP,
};
int		attack_12_circle_rot;								//　角度計算
float	attack_12_circle_r;
int		attack_12_circle_count[ATTACK_12_SHOT_MAX];
float	attack_12_circle_s;
int		attack_12_count;

int		display_handle_12_mode;									//　敵を表示するかしないか
int		display_handle_12_shot_mode[ATTACK_12_SHOT_MAX];			//　弾の表示するかしないか

int		attack_12_hp;

// =====================================================
//	ボス
// =====================================================

bool boss_mode;
Floatxy boss;
int boss_hp;

int boss_stage_now;
enum {
	none,
	first,
	second,
	third,
};

int boss_attack_count;
int boss_img;
int boss_magic_img;

//int boss_attack_mode;	//　０：何もない　１：４つの弾＆ランダムで落とす　３：４つの所から出す　４：スペルカード
//enum {
//	Attack_Off,				//　雑魚敵
//	Attack_Count,			//　カウントスタート
//	Attack_Mode_1,			//　１つ目の攻撃
//	Attack_Mode_2,			//　２つ目の攻撃
//	Attack_Mode_3,			//　３つ目の攻撃を消す
//};

//int attack_mode_1;
//int attack_mode_2;
//int attack_mode_3;
//int attack_mode_4;

// ==========================================================================================================
//　ステージ１攻撃１

// =====================================================
int boss_attack_1_count;
// =====================================================

// =====================================================
//　時計回り１

Floatxy boss_big_left_1_shot_shot[BOSS_BIG_LEFT_1_SHOT_MAX][BOSS_BIG_LEFT_1_SHOT_NUM];
bool	boss_big_left_1_shot_mode[BOSS_BIG_LEFT_1_SHOT_MAX][BOSS_BIG_LEFT_1_SHOT_NUM];
float	boss_big_left_1_shot_r = 360 / BOSS_BIG_LEFT_1_SHOT_MAX;
int		boss_big_left_1_shot_count;
int		boss_big_left_1_shot_num;

Floatxy boss_small_left_1_shot_shot[BOSS_SMALL_LEFT_1_SHOT_MAX][BOSS_SMALL_LEFT_1_SHOT_NUM];
bool	boss_small_left_1_shot_mode[BOSS_SMALL_LEFT_1_SHOT_MAX][BOSS_SMALL_LEFT_1_SHOT_NUM];
float	boss_small_left_1_shot_r = 360 / BOSS_SMALL_LEFT_1_SHOT_MAX;
int		boss_small_left_1_shot_count;
int		boss_small_left_1_shot_num;

// =====================================================

// =====================================================
//　反時計回り１

Floatxy boss_big_right_1_shot_shot[BOSS_BIG_LEFT_1_SHOT_MAX][BOSS_BIG_LEFT_1_SHOT_NUM];
bool	boss_big_right_1_shot_mode[BOSS_BIG_LEFT_1_SHOT_MAX][BOSS_BIG_LEFT_1_SHOT_NUM];
float	boss_big_right_1_shot_r = 360 / BOSS_BIG_LEFT_1_SHOT_MAX;
int		boss_big_right_1_shot_count;
int		boss_big_right_1_shot_num;

Floatxy boss_small_right_1_shot_shot[BOSS_SMALL_LEFT_1_SHOT_MAX][BOSS_SMALL_LEFT_1_SHOT_NUM];
bool	boss_small_right_1_shot_mode[BOSS_SMALL_LEFT_1_SHOT_MAX][BOSS_SMALL_LEFT_1_SHOT_NUM];
float	boss_small_right_1_shot_r = 360 / BOSS_SMALL_LEFT_1_SHOT_MAX;
int		boss_small_right_1_shot_count;
int		boss_small_right_1_shot_num;

// =====================================================

// =====================================================
//　時計回り２

Floatxy boss_big_left_2_shot_shot[BOSS_BIG_LEFT_2_SHOT_MAX][BOSS_BIG_LEFT_2_SHOT_NUM];
bool	boss_big_left_2_shot_mode[BOSS_BIG_LEFT_2_SHOT_MAX][BOSS_BIG_LEFT_2_SHOT_NUM];
float	boss_big_left_2_shot_r = 360 / BOSS_BIG_LEFT_2_SHOT_MAX;
int		boss_big_left_2_shot_count;
int		boss_big_left_2_shot_num;

Floatxy boss_small_left_2_shot_shot[BOSS_SMALL_LEFT_2_SHOT_MAX][BOSS_SMALL_LEFT_2_SHOT_NUM];
bool	boss_small_left_2_shot_mode[BOSS_SMALL_LEFT_2_SHOT_MAX][BOSS_SMALL_LEFT_2_SHOT_NUM];
float	boss_small_left_2_shot_r = 360 / BOSS_SMALL_LEFT_2_SHOT_MAX;
int		boss_small_left_2_shot_count;
int		boss_small_left_2_shot_num;

// =====================================================


// =====================================================
//　反時計回り２

Floatxy boss_big_right_2_shot_shot[BOSS_BIG_LEFT_2_SHOT_MAX][BOSS_BIG_LEFT_2_SHOT_NUM];
bool	boss_big_right_2_shot_mode[BOSS_BIG_LEFT_2_SHOT_MAX][BOSS_BIG_LEFT_2_SHOT_NUM];
float	boss_big_right_2_shot_r = 360 / BOSS_BIG_LEFT_2_SHOT_MAX;
int		boss_big_right_2_shot_count;
int		boss_big_right_2_shot_num;

Floatxy boss_small_right_2_shot_shot[BOSS_SMALL_LEFT_2_SHOT_MAX][BOSS_SMALL_LEFT_2_SHOT_NUM];
bool	boss_small_right_2_shot_mode[BOSS_SMALL_LEFT_2_SHOT_MAX][BOSS_SMALL_LEFT_2_SHOT_NUM];
float	boss_small_right_2_shot_r = 360 / BOSS_SMALL_LEFT_2_SHOT_MAX;
int		boss_small_right_2_shot_count;
int		boss_small_right_2_shot_num;

// =====================================================

// =====================================================
//　時計回り３

Floatxy boss_big_left_3_shot_shot[BOSS_BIG_LEFT_3_SHOT_MAX][BOSS_BIG_LEFT_3_SHOT_NUM];
bool	boss_big_left_3_shot_mode[BOSS_BIG_LEFT_3_SHOT_MAX][BOSS_BIG_LEFT_3_SHOT_NUM];
float	boss_big_left_3_shot_r = 360 / BOSS_BIG_LEFT_3_SHOT_MAX;
int		boss_big_left_3_shot_count;
int		boss_big_left_3_shot_num;

Floatxy boss_small_left_3_shot_shot[BOSS_SMALL_LEFT_3_SHOT_MAX][BOSS_SMALL_LEFT_3_SHOT_NUM];
bool	boss_small_left_3_shot_mode[BOSS_SMALL_LEFT_3_SHOT_MAX][BOSS_SMALL_LEFT_3_SHOT_NUM];
float	boss_small_left_3_shot_r = 360 / BOSS_SMALL_LEFT_3_SHOT_MAX;
int		boss_small_left_3_shot_count;
int		boss_small_left_3_shot_num;

// =====================================================

// =====================================================
//　反時計回り３

Floatxy boss_big_right_3_shot_shot[BOSS_BIG_LEFT_3_SHOT_MAX][BOSS_BIG_LEFT_3_SHOT_NUM];
bool	boss_big_right_3_shot_mode[BOSS_BIG_LEFT_3_SHOT_MAX][BOSS_BIG_LEFT_3_SHOT_NUM];
float	boss_big_right_3_shot_r = 360 / BOSS_BIG_LEFT_3_SHOT_MAX;
int		boss_big_right_3_shot_count;
int		boss_big_right_3_shot_num;

Floatxy boss_small_right_3_shot_shot[BOSS_SMALL_LEFT_3_SHOT_MAX][BOSS_SMALL_LEFT_3_SHOT_NUM];
bool	boss_small_right_3_shot_mode[BOSS_SMALL_LEFT_3_SHOT_MAX][BOSS_SMALL_LEFT_3_SHOT_NUM];
float	boss_small_right_3_shot_r = 360 / BOSS_SMALL_LEFT_3_SHOT_MAX;
int		boss_small_right_3_shot_count;
int		boss_small_right_3_shot_num;

int		display_handle_boss_shot_mode_big[9][4][6];				//　大きいほうの弾の表示するかしないか
int		display_handle_boss_shot_mode_small[9][3][6];			//　大きいほうの弾の表示するかしないか

// ==========================================================================================================

// ==========================================================================================================
//　ステージ１攻撃２


Floatxy boss_rand_shot_1[BOSS_RAND_NUM1];
float	boss_rand_speed_1[BOSS_RAND_NUM1];

Floatxy boss_rand_shot_2[BOSS_RAND_NUM2];
float	boss_rand_speed_2[BOSS_RAND_NUM2];

Floatxy boss_rand_shot_3[BOSS_RAND_NUM3];
float	boss_rand_speed_3[BOSS_RAND_NUM3];

int		display_handle_snow_1_shot_mode[BOSS_RAND_NUM1];			//　雪弾１の表示するかしないか
int		display_handle_snow_2_shot_mode[BOSS_RAND_NUM2];			//　雪弾２の表示するかしないか
int		display_handle_snow_3_shot_mode[BOSS_RAND_NUM3];			//　雪弾３の表示するかしないか

// ==========================================================================================================

// ==========================================================================================================
//　ステージ２


Floatxy boss_rotate_coordinate[BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
int		boss_rotate_count[BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
int		boss_rotate_num[BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
int		boss_rotate_mode[BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
enum
{
	TOP,
	RIGHT,
	BOT,
	LEFT,
};

int		boss_rotate_count_num;
Floatxy boss_rotate_shot_coordinate[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];										//　赤色の雑魚敵の座標
int		boss_rotate_shot_mode[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
float	boss_rotate_shot_angle[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
int		boss_rotate_shot_num[BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];

int		display_handle_rotate_shot_mode[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];			//　弾の表示するかしないか

Floatxy boss_nekomimi_attack_shot_coordinate[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
int		boss_nekomimi_attack_count[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
float	boss_nekomimi_attack_missile_rot[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
float	boss_nekomimi_attack_speed[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
int		boss_nekomimi_attack_mode[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];

float	boss_nekomimi_s = 360.0f / BOSS_NEKOMIMI_NUM;
float	boss_nekomimi_rr;

Floatxy boss_small_shot_shot[BOSS_SMALL_SHOT_MAX];
bool	boss_small_shot_mode[BOSS_SMALL_SHOT_MAX];
int		boss_small_shot_count;
int		boss_small_shot_num;

float	boss_small_ssss;
float	boss_small_r;

Floatxy boss_small_shot[BOSS_SMALL_AMAX];
bool	boss_small_mode[BOSS_SMALL_AMAX];
int		boss_small_count;
int		boss_small_num;

float	boss_small_s1;
float	boss_small_r1;

// ==========================================================================================================

// ==========================================================================================================
//　ステージ３


Floatxy boss_furan_red_circle_shot[BOSS_FURAN_RED_SHOT_MAX][BOSS_FURAN_RED_NUM_MAX];				//　赤色の雑魚敵の弾
float	boss_furan_red_circle_target_angle[BOSS_FURAN_RED_SHOT_MAX][BOSS_FURAN_RED_NUM_MAX];		//　赤色の目的角度
int		boss_furan_red_circle_mode[BOSS_FURAN_RED_SHOT_MAX][BOSS_FURAN_RED_NUM_MAX];				//　赤色のモード
int		boss_furan_red_circle_shot_num;													//　赤色の回数
int		boss_furan_red_circle_count;														//　カウント
int		boss_furan_red_circle_rot;														//　角度計算
float	boss_furan_red_circle_r;

Floatxy boss_furan_blue_circle_shot[BOSS_FURAN_BLUE_SHOT_MAX][BOSS_FURAN_BLUE_NUM_MAX][BOSS_FURAN_BLUE_LB];				//　赤色の雑魚敵の弾
float	boss_furan_blue_circle_target_angle[BOSS_FURAN_BLUE_SHOT_MAX][BOSS_FURAN_BLUE_NUM_MAX][BOSS_FURAN_BLUE_LB];		//　赤色の目的角度
int		boss_furan_blue_circle_mode[BOSS_FURAN_BLUE_SHOT_MAX][BOSS_FURAN_BLUE_NUM_MAX][BOSS_FURAN_BLUE_LB];				//　赤色のモード
int		boss_furan_blue_circle_shot_num;																	//　赤色の回数
int		boss_furan_blue_circle_count;																	//　カウント
int		boss_furan_blue_circle_rot;																		//　角度計算
float	boss_furan_blue_circle_r;

Floatxy boss_furan_purple_circle_shot[BOSS_FURAN_PURPLE_SHOT_MAX][BOSS_FURAN_PURPLE_NUM_MAX];				//　赤色の雑魚敵の弾
float	boss_furan_purple_circle_target_angle[BOSS_FURAN_PURPLE_SHOT_MAX][BOSS_FURAN_PURPLE_NUM_MAX];		//　赤色の目的角度
int		boss_furan_purple_circle_mode[BOSS_FURAN_PURPLE_SHOT_MAX][BOSS_FURAN_PURPLE_NUM_MAX];				//　赤色のモード
int		boss_furan_purple_circle_shot_num;													//　赤色の回数
int		boss_furan_purple_circle_count;														//　カウント
int		boss_furan_purple_circle_rot;														//　角度計算
float	boss_furan_purple_circle_r;

int		display_handle_furan_red_shot_mode[BOSS_FURAN_RED_SHOT_MAX][BOSS_FURAN_RED_NUM_MAX];							//　雪弾３の表示するかしないか
int		display_handle_furan_blue_shot_mode[BOSS_FURAN_BLUE_SHOT_MAX][BOSS_FURAN_BLUE_NUM_MAX][BOSS_FURAN_BLUE_LB];		//　雪弾３の表示するかしないか
int		display_handle_furan_purple_shot_mode[BOSS_FURAN_PURPLE_SHOT_MAX][BOSS_FURAN_PURPLE_NUM_MAX];						//　雪弾３の表示するかしないか


// =====================================================
//	exrturn用（プレイヤー）
// =====================================================
//　自機移動設定
extern Floatxy	player_coordinate;				//　プレイヤーの座標

//　雑魚敵用の画像
int enemy_rb_image;
Floatxy enemy_rb_img_coordinate;
int enemy_rb_img_count;

//　BGM
//int bgm;
//bool sound;

int se_enemy_attack[4];

extern int score;

int w_count;
int boss_ensyutu_mode;
int w_alpha;
int boss_worning;

//　敵の弾画像
int gr_enemy_shot[4];	//　紫、青、赤、黄
int gr_enemy_shot_a[2];
int gr_enemy_shot_b;

// =====================================================
//		初期化
//	ゲーム開始直後に最初に1回だけ実行される関数
//	最初の値を変数に入れたいときに使う
// =====================================================
void EnemyInit()
{
	// DrawStringやDrawFormatStrinで描画する文字を
	// アンチエイリアスを使用してきれいに描画する
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	enemy_rb_image = LoadGraph("data/enemy/Enemy.png");
	boss_img = LoadGraph("data/enemy/remiria.png");
	boss_magic_img = LoadGraph("data/enemy/Magic.png");
	boss_worning = LoadGraph("data/BG/w.png");
	frame_count = 0;
	for (int i = 0; i < 16; i++) {
		game_shot[i] = MODE_WAIT;
	}


//	frame_count = 3500;


	//bgm = LoadSoundMem("data/bgm/bgm1.mp3");
	//sound = 0;
	se_enemy_attack[0] = LoadSoundMem("data/se/Shot00.wav");
	se_enemy_attack[1] = LoadSoundMem("data/se/Shot01.wav");
	se_enemy_attack[2] = LoadSoundMem("data/se/shot1.wav");
	se_enemy_attack[3] = LoadSoundMem("data/se/shot2.wav");

	gr_enemy_shot[0] = LoadGraph("data/enemy/attack1.png");
	gr_enemy_shot[1] = LoadGraph("data/enemy/attack2.png");
	gr_enemy_shot[2] = LoadGraph("data/enemy/attack3.png");
	gr_enemy_shot[3] = LoadGraph("data/enemy/attack4.png");

	gr_enemy_shot_a[0] = LoadGraph("data/enemy/NuclearSpark2.png");
	gr_enemy_shot_a[1] = LoadGraph("data/enemy/NuclearSpark.png");
	
	gr_enemy_shot_b = LoadGraph("data/enemy/UtuhoShot.png");

	for (int i = 0; i < ATTACK_1_2_MAX; i++) {
		for (int j = 0; j < ATTACK_1_2__NUM; j++) {
			display_handle_1_mode[i][j] = HIDDEN;
			display_handle_1_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_1_2_MAX; i++) {
		for (int j = 0; j < ATTACK_1_2__NUM; j++) {
			display_handle_2_mode[i][j] = HIDDEN;
			display_handle_2_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_3_4_MAX; i++) {
		display_handle_3_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_3_4_NUM; j++) {
			display_handle_3_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_3_4_MAX; i++) {
		display_handle_4_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_3_4_NUM; j++) {
			display_handle_4_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_5_MAX; i++) {
		display_handle_5_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_5_NUM; j++) {
			display_handle_5_shot_mode[i][j] = HIDDEN;
		}
	}
	display_handle_5_c_mode = HIDDEN;
	for (int p = 0; p < ATTACK_5_SHOT_NUM; p++) {
		attack_5_shot_r[p] = 0;
		display_handle_5_c_shot_mode[p] = HIDDEN;
	}
	for (int i = 0; i < NEKOMIMI_MAX; i++) {
		for (int j = 0; j < NEKOMIMI_NUM; j++) {
			display_handle_5_nekomimi_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_6_MAX; i++) {
		display_handle_6_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_6_NUM; j++) {
			display_handle_6_shot_mode[i][j] = HIDDEN;
		}
	}
	display_handle_6_c_mode = HIDDEN;
	for (int p = 0; p < ATTACK_6_SHOT_NUM; p++) {
		attack_6_teki_shot_r[p] = 0;
		display_handle_6_c_shot_mode[p] = HIDDEN;
	}
	for (int i = 0; i < NEKOMIMI_MAX; i++) {
		for (int j = 0; j < NEKOMIMI_NUM; j++) {
			display_handle_6_nekomimi_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_7_MAX; i++) {
		display_handle_7_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_7_NUM; j++) {
			display_handle_7_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_8_MAX; i++) {
		display_handle_8_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_8_NUM; j++) {
			display_handle_8_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_9_NUM; i++) {
		attack_9_zako_mode[i] = MODE_WAIT;
		display_handle_9_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_9_MAX; j++) {
			display_handle_9_shot_mode[i][j] = HIDDEN;
		}
	}
	display_handle_9_nekomimi_mode = HIDDEN;
	for (int i = 0; i < ATTACK_9_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_9_NEKOMIMI_NUM; j++) {
			display_handle_9_nekomimi_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_10_NUM; i++) {
		display_handle_10_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_10_MAX; j++) {
			display_handle_10_shot_mode[i][j] = HIDDEN;
		}
	}
	display_handle_10_nekomimi_mode = HIDDEN;
	for (int i = 0; i < ATTACK_10_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_10_NEKOMIMI_NUM; j++) {
			display_handle_10_nekomimi_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_11_NUM; i++) {
		display_handle_11_mode[i] = HIDDEN;
		for (int j = 0; j < ATTACK_11_MAX; j++) {
			display_handle_11_shot_mode[i][j] = HIDDEN;
		}
	}
	display_handle_11_nekomimi_mode = HIDDEN;
	for (int i = 0; i < ATTACK_11_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_11_NEKOMIMI_NUM; j++) {
			display_handle_11_nekomimi_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < ATTACK_12_SHOT_MAX; i++) {
		display_handle_12_shot_mode[i] = HIDDEN;
	}
	display_handle_12_mode = HIDDEN;
	for (int i = 0; i < ATTACK_12_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_12_NEKOMIMI_NUM; j++) {
			display_handle_12_nekomimi_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_BIG_LEFT_1_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_BIG_LEFT_1_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_big[j][i][0] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_SMALL_LEFT_1_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_SMALL_LEFT_1_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_small[j][i][0] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_BIG_RIGHT_1_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_BIG_RIGHT_1_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_big[j][i][1] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_SMALL_RIGHT_1_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_SMALL_RIGHT_1_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_small[j][i][1] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_BIG_LEFT_2_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_BIG_LEFT_2_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_big[j][i][2] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_SMALL_LEFT_2_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_SMALL_LEFT_2_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_small[j][i][2] == HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_BIG_RIGHT_2_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_BIG_RIGHT_2_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_big[j][i][3] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_SMALL_RIGHT_2_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_SMALL_RIGHT_2_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_small[j][i][3] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_BIG_LEFT_3_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_BIG_LEFT_3_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_big[j][i][4] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_SMALL_LEFT_3_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_SMALL_LEFT_3_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_small[j][i][4] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_BIG_RIGHT_3_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_BIG_RIGHT_3_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_big[j][i][5] = HIDDEN;
		}
	}
	for (int j = 0; j < BOSS_SMALL_RIGHT_3_SHOT_MAX; j++) {
		for (int i = 0; i < BOSS_SMALL_RIGHT_3_SHOT_NUM; i++) {
			display_handle_boss_shot_mode_small[j][i][5] = HIDDEN;
		}
	}
	for (int i = 0; i < BOSS_RAND_NUM1; i++) {
		display_handle_snow_1_shot_mode[i] = HIDDEN;
	}
	for (int i = 0; i < BOSS_RAND_NUM2; i++) {
		display_handle_snow_2_shot_mode[i] = HIDDEN;
	}
	for (int i = 0; i < BOSS_RAND_NUM3; i++) {
		display_handle_snow_3_shot_mode[i] = HIDDEN;
	}
	for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
		for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
			for (int i = 0; i < BOSS_ROTATE_SHOT_MAX; i++) {
				display_handle_rotate_shot_mode[i][p][t] = HIDDEN;
			}
		}
	}
	for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
		for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
			for (int i = 0; i < BOSS_ROTATE_SHOT_MAX; i++) {
				boss_rotate_shot_mode[i][p][t] = MODE_WAIT;
			}
		}
	}
	for (int i = 0; i < BOSS_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < BOSS_NEKOMIMI_NUM; j++) {
			boss_nekomimi_attack_mode[i][j] = MODE_WAIT;
		}
	}
	for (int j = 0; j < BOSS_SMALL_SHOT_MAX; j++) {
		boss_small_shot_mode[j] = MODE_WAIT;
	}
	for (int j = 0; j < BOSS_SMALL_AMAX; j++) {
		boss_small_mode[j] = MODE_WAIT;
	}
	for (int i = 0; i < BOSS_FURAN_RED_SHOT_MAX; i++) {
		for (int j = 0; j < BOSS_FURAN_RED_NUM_MAX; j++) {
			display_handle_furan_red_shot_mode[i][j] = HIDDEN;
		}
	}
	for (int i = 0; i < BOSS_FURAN_BLUE_SHOT_MAX; i++) {
		for (int j = 0; j < BOSS_FURAN_BLUE_NUM_MAX; j++) {
			for (int k = 0; k < BOSS_FURAN_BLUE_LB; k++) {
				display_handle_furan_blue_shot_mode[i][j][k] = HIDDEN;
			}
		}
	}
	for (int i = 0; i < BOSS_FURAN_PURPLE_SHOT_MAX; i++) {
		for (int j = 0; j < BOSS_FURAN_PURPLE_NUM_MAX; j++) {
			display_handle_furan_purple_shot_mode[i][j] = HIDDEN;
		}
	}
	boss_nekomimi_rr = 0;
	boss_small_s1 = 0;
	boss_small_r1 = 0;
	boss_stage_now = none;
	attack_7_count = 0;
	attack_7_num = 0;
	for (int i = 0; i < ATTACK_7_MAX; i++) {
		attack_7_zako_mode[i] = MODE_WAIT;
	}
	attack_8_count = 0;
	attack_8_num = -0;
	for (int i = 0; i < ATTACK_8_MAX; i++) {
		attack_8_zako_mode[i] = MODE_WAIT;
	}
	//　８，９，１２，１３，１４，１５，
	
}

// =====================================================
//		更新
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	1フレームで行う処理をここに書く
// =====================================================
void EnemyUpdate()
{
//	ChangeVolumeSoundMem(SE_PLAYER_VOLUME, bgm);
	for (int i = 0; i < 4; i++) {
		ChangeVolumeSoundMem(SE_PLAYER_VOLUME, se_enemy_attack[i]);
	}
	
	//if (sound == 0 && game_start_mode == Game){
	//	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
	//	sound = 1;
	//}
	//if (CheckSoundFile() == 0) {
	//	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
	//}

	//　画像
	enemy_rb_img_count++;	//カウント
	//　カウントがタイミングよりも大きくなったら
	if (enemy_rb_img_count >= ENEMY_RB_IMG_TIMING) {
		//　カウントを０にする
		enemy_rb_img_count = 0;
		//　プレイヤーの画像の横幅分を足す
		enemy_rb_img_coordinate.x += ENEMY_RB_IMG_WIDTH;
		//　もし一番右の画像まで行ったら　
		if (enemy_rb_img_coordinate.x >= ENEMY_RB_IMG_WIDTH_MAX) {
			//　０に戻す
			enemy_rb_img_coordinate.x = 0;
		}
	}

	//if (CheckHitKey(KEY_INPUT_SPACE)) {
	//	frame_count = 0;
	//	for (int i = 0; i < 16; i++) {
	//	game_shot[i] = MODE_WAIT;
	//	}
	//}
	//　フレームカウント
	frame_count++;

	if (frame_count == ATTACK_1_TIMING) {

		game_shot[0] = MODE_MOVE;
		for (int i = 0; i < ATTACK_1_2_MAX; i++) {
			for (int j = 0; j < ATTACK_1_2__NUM; j++) {
				zako_attack_1_coordinate[i][j].x = 127 - 20 * j;
				zako_attack_1_coordinate[i][j].y = 0 - 40 * i;
				zako_attack_1_mode[i][j] = MODE_WAIT;
				zako_attack_1_angle[i][j] = 0;
				zako_attack_1_count[i][j] = 0;
				attack_1_hp[i][j] = HP_MAX_LEVEL1;
			}
		}
	}
	if (frame_count == ATTACK_2_TIMING) {
		game_shot[1] = MODE_MOVE;
		for (int i = 0; i < ATTACK_1_2_MAX; i++) {
			for (int j = 0; j < ATTACK_1_2__NUM; j++) {
				//　敵の位置（仮）
			//	display_handle_2_mode[i][j] = DISPLAY;
				zako_attack_2_coordinate[i][j].x = WINDOW_W / 2 + 20 * j;
				zako_attack_2_coordinate[i][j].y = 0 - 40 * i;
				zako_attack_2_mode[i][j] = MODE_WAIT;
				zako_attack_2_angle[i][j] = 0;
				zako_attack_2_count[i][j] = 0;
				attack_2_hp[i][j] = HP_MAX_LEVEL1;
			}
		}
	}
	if (frame_count == ATTACK_3_TIMING) {
		game_shot[2] = MODE_MOVE;
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			zako_attack_3_mode[i] = MODE_WAIT;
			zako_attack_3_count[i] = 0;
			zako_attack_3_shot_mode[i] = MODE_WAIT;
			attack_3_hp[i] = HP_MAX_LEVEL1;
		}
	}
	if (frame_count == ATTACK_4_TIMING) {
		game_shot[3] = MODE_MOVE;
		game_shot[0] = MODE_WAIT;
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			zako_attack_4_mode[i] = MODE_WAIT;
			zako_attack_4_count[i] = 0;
			zako_attack_4_shot_mode[i] = MODE_WAIT;
			attack_4_hp[i] = HP_MAX_LEVEL1;
		}
	}
	if (frame_count == ATTACK_5_TIMING) {
		game_shot[4] = MODE_MOVE;
		game_shot[1] = MODE_WAIT;
		game_shot[2] = MODE_WAIT;
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			zako_attack_3_mode[i] = MODE_WAIT;
			zako_attack_3_count[i] = 0;
			zako_attack_3_shot_mode[i] = MODE_WAIT;
			attack_3_hp[i] = HP_MAX_LEVEL1;
		}
	}
	if (frame_count == ATTACK_6_TIMING) {
		game_shot[5] = MODE_MOVE;
		game_shot[3] = MODE_WAIT;
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			zako_attack_4_mode[i] = MODE_WAIT;
			zako_attack_4_count[i] = 0;
			zako_attack_4_shot_mode[i] = MODE_WAIT;
			attack_4_hp[i] = HP_MAX_LEVEL1;
		}
	}
	if (frame_count == ATTACK_7_TIMING) {
		game_shot[6] = MODE_MOVE;
		for (int i = 0; i < ATTACK_5_MAX; i++) {
			attack_5_zako_coordinate[i].x = 127;
			attack_5_zako_coordinate[i].y = 0 - 40 * i;
			attack_5_zako_count[i] = 0;
			attack_5_zako_mode[i] = MODE_WAIT;
			attack_5_hp = HP_MAX_LEVEL2;
			attack_zako_5_hp[i] = HP_MAX_LEVEL1;
			attack_5_zako_shot_mode[i] = MODE_WAIT;
			for (int j = 0; j < ATTACK_5_NUM; j++) {
				attack_5_angle[i][j] = 0;
			}
		}
	}
	if (frame_count == ATTACK_8_TIMING) {
		game_shot[7] = MODE_MOVE;
		game_shot[4] = MODE_WAIT;
		//		game_shot[5] = MODE_WAIT;
		for (int i = 0; i < ATTACK_6_MAX; i++) {
			attack_6_zako_coordinate[i].x = 127;
			attack_6_zako_coordinate[i].y = 0 - 40 * i;
			attack_6_zako_count[i] = 0;
			attack_6_zako_mode[i] = MODE_WAIT;
			attack_6_hp = HP_MAX_LEVEL2;
			attack_zako_6_hp[i] = HP_MAX_LEVEL1;
		}
		//for (int i = 0; i < ATTACK_7_MAX; i++) {
		//	display_handle_7_mode[i] = MODE_WAIT;
		//}
	}
	if (frame_count == ATTACK_9_TIMING) {
		game_shot[8] = MODE_MOVE;
		game_shot[5] = MODE_WAIT;
		for (int i = 0; i < ATTACK_7_MAX; i++) {
			attack_7_zako_coordinate[i].x = 127;
			attack_7_zako_coordinate[i].y = 0 - 40 * i;
			attack_7_hp[i] = HP_MAX_LEVEL1;
			attack_7_zako_mode[i] = MODE_WAIT;
			display_handle_7_mode[i] = MODE_WAIT;
			attack_7_zako_count[i] = 0;
		}
		attack_7_count = 0;
		attack_7_num = 0;
	}
	if (frame_count == ATTACK_10_TIMING) {
		game_shot[9] = MODE_MOVE;
		for (int i = 0; i < ATTACK_8_MAX; i++) {
			attack_8_zako_coordinate[i].x = 127;
			attack_8_zako_coordinate[i].y = 0 - 40 * i;
			attack_8_hp[i] = HP_MAX_LEVEL1;
			attack_8_zako_mode[i] = MODE_WAIT;
			display_handle_8_mode[i] = MODE_WAIT;
			attack_8_zako_count[i] = 0;
		}
		attack_8_count = 0;
		attack_8_num = 0;
	}
	if (frame_count == ATTACK_11_TIMING) {
		game_shot[10] = MODE_MOVE;
		game_shot[6] = MODE_WAIT;
		for (int i = 0; i < ATTACK_5_MAX; i++) {
			attack_5_zako_coordinate[i].x = 127;
			attack_5_zako_coordinate[i].y = 0 - 40 * i;
			attack_5_zako_count[i] = 0;
			attack_5_zako_mode[i] = MODE_WAIT;
			attack_5_hp = HP_MAX_LEVEL2;
			attack_zako_5_hp[i] = HP_MAX_LEVEL1;
		}
	}
	if (frame_count == ATTACK_12_TIMING) {
		game_shot[11] = MODE_MOVE;
		game_shot[7] = MODE_WAIT;
		//game_shot[6] = MODE_WAIT;
		//game_shot[7] = MODE_WAIT;
		//game_shot[8] = MODE_WAIT;
		//game_shot[9] = MODE_WAIT;
		for (int i = 0; i < ATTACK_6_MAX; i++) {
			attack_6_zako_coordinate[i].x = 127;
			attack_6_zako_coordinate[i].y = 0 - 40 * i;
			attack_6_zako_count[i] = 0;
			attack_6_zako_mode[i] = MODE_WAIT;
			attack_6_hp = HP_MAX_LEVEL2;
			attack_zako_6_hp[i] = HP_MAX_LEVEL1;
			attack_6_zako_shot_mode[i] = MODE_WAIT;
			display_handle_6_mode[i] = HIDDEN;
		}
		display_handle_6_c_mode = HIDDEN;
		for (int p = 0; p < ATTACK_6_SHOT_NUM; p++) {
			display_handle_6_c_shot_mode[p] = HIDDEN;
			attack_6_teki_shot_r[p] = 0;
		}
		for (int j = 0; j < NEKOMIMI_NUM; j++) {
			for (int i = 0; i < NEKOMIMI_MAX; i++) {
				display_handle_6_nekomimi_shot_mode[i][j] = HIDDEN;
			}
		}
		for (int i = 0; i < NEKOMIMI_MAX; i++) {
			for (int j = 0; j < NEKOMIMI_NUM; j++) {
				attack_6_nekomimi_attack_mode[i][j] = MODE_WAIT;
				attack_6_nekomimi_attack_missile_rot[i][j] = 0;
			}
		}
	}
	if (frame_count == ATTACK_13_TIMING) {
		game_shot[12] = MODE_MOVE;
		attack_9_hp = HP_MAX_LEVEL3;
		for (int i = 0; i < ATTACK_9_NUM; i++) {
			attack_zako_9_hp[i] = HP_MAX_LEVEL1;
			attack_9_zako_mode[i] = MODE_WAIT;
			display_handle_9_mode[i] = HIDDEN;
		}
		for (int j = 0; j < ATTACK_9_NEKOMIMI_NUM; j++) {
			for (int i = 0; i < ATTACK_9_NEKOMIMI_MAX; i++) {
				attack_9_nekomimi_attack_mode[i][j] = MODE_WAIT;
			}
		}
		display_handle_9_nekomimi_mode = HIDDEN;
	}
	if (frame_count == ATTACK_14_TIMING) {
		game_shot[13] = MODE_MOVE;
		attack_10_hp = HP_MAX_LEVEL3;
		for (int i = 0; i < ATTACK_10_NUM; i++) {
			attack_zako_10_hp[i] = HP_MAX_LEVEL1;
			attack_10_zako_mode[i] = MODE_WAIT;
			display_handle_10_mode[i] = HIDDEN;
		}
		for (int j = 0; j < ATTACK_10_NEKOMIMI_NUM; j++) {
			for (int i = 0; i < ATTACK_10_NEKOMIMI_MAX; i++) {
				attack_10_nekomimi_attack_mode[i][j] = MODE_WAIT;
			}
		}
		display_handle_10_nekomimi_mode = HIDDEN;
	}
	if (frame_count == ATTACK_15_TIMING) {
		game_shot[14] = MODE_MOVE;
		attack_11_hp = HP_MAX_LEVEL3;
		for (int i = 0; i < ATTACK_11_NUM; i++) {
			attack_zako_11_hp[i] = HP_MAX_LEVEL1;
			attack_11_zako_mode[i] = MODE_WAIT;
			display_handle_11_mode[i] = HIDDEN;
		}
		for (int j = 0; j < ATTACK_11_NEKOMIMI_NUM; j++) {
			for (int i = 0; i < ATTACK_11_NEKOMIMI_MAX; i++) {
				attack_11_nekomimi_attack_mode[i][j] = MODE_WAIT;
			}
		}
		display_handle_11_nekomimi_mode = HIDDEN;
	}
	if (frame_count == ATTACK_16_TIMING) {
		game_shot[15] = MODE_MOVE;
		game_shot[8] = MODE_WAIT;
		game_shot[9] = MODE_WAIT;
		game_shot[10] = MODE_WAIT;
		attack_12_nekomimi_coordinate.x = (BG_X_HW - BG_X_LW) / 2 + BG_X_LW;
		attack_12_nekomimi_coordinate.y = 120;
		display_handle_12_mode = DISPLAY;
		attack_12_hp = HP_MAX_LEVEL3;
		attack_12_count = 0;
		for (int j = 0; j < ATTACK_12_NEKOMIMI_NUM; j++) {
			for (int i = 0; i < ATTACK_12_NEKOMIMI_MAX; i++) {
				display_handle_12_nekomimi_shot_mode[i][j] = HIDDEN;
			}
		}
	}
	
	//　左上からの攻撃
	if (game_shot[0] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_1_2_MAX; i++) {
			for (int j = 0; j < ATTACK_1_2__NUM; j++) {
				if (zako_attack_1_coordinate[i][j].y <= 60) {
					zako_attack_1_coordinate[i][j].y += ATTACK_SPEED_Y;
					if (attack_1_hp[i][j] == HP_MAX_LEVEL1) {
						display_handle_1_mode[i][j] = DISPLAY;
					}
				}
				else {
					zako_attack_1_count[i][j]++;
					if (zako_attack_1_mode[i][j] == MODE_WAIT) {
						if (zako_attack_1_count[i][j] >= ATTACK_SHOT_TIMING) {
							zako_attack_1_shot_coordinate[i][j].x = zako_attack_1_coordinate[i][j].x;
							zako_attack_1_shot_coordinate[i][j].y = zako_attack_1_coordinate[i][j].y;
							zako_attack_1_angle[i][j] = atan2f(player_coordinate.y - zako_attack_1_coordinate[i][j].y, player_coordinate.x - zako_attack_1_coordinate[i][j].x - 20 + j * 40);

							if (display_handle_1_mode[i][j] == DISPLAY) {
								display_handle_1_shot_mode[i][j] = DISPLAY;
								PlaySoundMem(se_enemy_attack[0], DX_PLAYTYPE_BACK);
								zako_attack_1_mode[i][j] = MODE_MOVE;
							}
						}
					}
					if (zako_attack_1_count[i][j] >= ATTACK_STOP_TIMING) {
						zako_attack_1_coordinate[i][j].x += ATTACK_SPEED_X;
						zako_attack_1_coordinate[i][j].y += ATTACK_SPEED_Y;
					}
				}
				if (zako_attack_1_mode[i][j] == MODE_MOVE) {
					zako_attack_1_shot_coordinate[i][j].x += cosf(zako_attack_1_angle[i][j]) * ATTACK_SHOT_SPEED;
					zako_attack_1_shot_coordinate[i][j].y += sinf(zako_attack_1_angle[i][j]) * ATTACK_SHOT_SPEED;
				}
				if (zako_attack_1_shot_coordinate[i][j].x < 0 || zako_attack_1_shot_coordinate[i][j].x > WINDOW_W || zako_attack_1_shot_coordinate[i][j].y < 0 || zako_attack_1_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_1_shot_mode[i][j] = HIDDEN;
				}
				if (zako_attack_1_coordinate[i][j].x < 0 || zako_attack_1_coordinate[i][j].x > WINDOW_W || zako_attack_1_coordinate[i][j].y < 0 || zako_attack_1_coordinate[i][j].y > WINDOW_H) {
					display_handle_1_mode[i][j] = HIDDEN;
				}
			}
		}
	}
	//　右上からの攻撃
	if (game_shot[1] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_1_2_MAX; i++) {
			for (int j = 0; j < ATTACK_1_2__NUM; j++) {
				if (zako_attack_2_coordinate[i][j].y <= 60) {
					zako_attack_2_coordinate[i][j].y += ATTACK_SPEED_Y;
					if (attack_2_hp[i][j] == HP_MAX_LEVEL1) {
						display_handle_2_mode[i][j] = DISPLAY;
					}
				}
				else {
					zako_attack_2_count[i][j]++;
					if (zako_attack_2_mode[i][j] == MODE_WAIT) {
						if (zako_attack_2_count[i][j] >= ATTACK_SHOT_TIMING) {
							zako_attack_2_shot_coordinate[i][j].x = zako_attack_2_coordinate[i][j].x;
							zako_attack_2_shot_coordinate[i][j].y = zako_attack_2_coordinate[i][j].y;
							zako_attack_2_angle[i][j] = atan2f(player_coordinate.y - zako_attack_2_coordinate[i][j].y, player_coordinate.x - zako_attack_2_coordinate[i][j].x + 20 - j * 40);
							if (display_handle_2_mode[i][j] == DISPLAY) {
								display_handle_2_shot_mode[i][j] = DISPLAY;
								zako_attack_2_mode[i][j] = MODE_MOVE;
								PlaySoundMem(se_enemy_attack[0], DX_PLAYTYPE_BACK);
							}
						}
					}
					if (zako_attack_2_count[i][j] >= ATTACK_STOP_TIMING) {
						zako_attack_2_coordinate[i][j].x -= ATTACK_SPEED_X;
						zako_attack_2_coordinate[i][j].y += ATTACK_SPEED_Y;
					}
				}
				if (zako_attack_2_mode[i][j] == MODE_MOVE) {
					zako_attack_2_shot_coordinate[i][j].x += cosf(zako_attack_2_angle[i][j]) * ATTACK_SHOT_SPEED;
					zako_attack_2_shot_coordinate[i][j].y += sinf(zako_attack_2_angle[i][j]) * ATTACK_SHOT_SPEED;
				}
				if (zako_attack_2_shot_coordinate[i][j].x < 0 || zako_attack_2_shot_coordinate[i][j].x > WINDOW_W || zako_attack_2_shot_coordinate[i][j].y < 0 || zako_attack_2_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_2_shot_mode[i][j] = HIDDEN;
				}
				if (zako_attack_2_coordinate[i][j].x < 0 || zako_attack_2_coordinate[i][j].x > WINDOW_W || zako_attack_2_coordinate[i][j].y < 0 || zako_attack_2_coordinate[i][j].y > WINDOW_H) {
					display_handle_2_mode[i][j] = HIDDEN;
				}
			}
		}
	}
	//　丸みを帯びた並びの２つの弾を出す左側
	if (game_shot[2] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_3_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_3_4_NUM; j++) {
					zako_attack_3_angle[i][j] = 30 + i * 15;
					zako_attack_3_coordinate[i].x = 130 + cosf(D2R(zako_attack_3_angle[i][j])) * 200;	// + i * 10;
					zako_attack_3_coordinate[i].y = 0 + sinf(D2R(zako_attack_3_angle[i][j])) * 200;		//70;
				}
				zako_attack_3_mode[i] = MODE_MOVE;
				display_handle_3_mode[i] = DISPLAY;
				zako_attack_3_y = -2.5f;
			}
		}
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_3_mode[i] == MODE_MOVE) {
				zako_attack_3_coordinate[i].y += zako_attack_3_y;
				if (zako_attack_3_y <= 1.5f) {
					zako_attack_3_y += 0.01f;
				}
				zako_attack_3_count[i]++;
				//	if (zako_attack_3_count[i] <= 60) {		//　後で >= 60に直す
				if (zako_attack_3_count[i] >= 60) {		//　後で >= 60に直す
					if (display_handle_3_mode[i] == DISPLAY) {
						if (zako_attack_3_shot_mode[i] == MODE_WAIT) {
							zako_attack_3_shot_mode[i] = MODE_MOVE;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								display_handle_3_shot_mode[i][j] = DISPLAY;
							}
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								zako_attack_3_shot_coordinate[i][j].x = zako_attack_3_coordinate[i].x;
								zako_attack_3_shot_coordinate[i][j].y = zako_attack_3_coordinate[i].y;
								zako_attack_3_angle[i][j] = atan2f(player_coordinate.y - zako_attack_3_shot_coordinate[i][j].y, player_coordinate.x - zako_attack_3_shot_coordinate[i][j].x);
							}
						}
					}
				}
			}
			for (int j = 0; j < ATTACK_3_4_NUM; j++) {
				if (zako_attack_3_shot_mode[i] == MODE_MOVE) {
					zako_attack_3_shot_coordinate[i][j].x += cosf(zako_attack_3_angle[i][j]) * 2.5f * (j * 0.1 + 1);
					zako_attack_3_shot_coordinate[i][j].y += sinf(zako_attack_3_angle[i][j]) * 2.5f * (j * 0.1 + 1);
				}
				if (zako_attack_3_shot_coordinate[i][j].x < 0 || zako_attack_3_shot_coordinate[i][j].x > WINDOW_W || zako_attack_3_shot_coordinate[i][j].y < 0 || zako_attack_3_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_3_shot_mode[i][j] = HIDDEN;
				}
			}
			if (zako_attack_3_coordinate[i].x < 0 || zako_attack_3_coordinate[i].x > WINDOW_W || zako_attack_3_coordinate[i].y < 0 || zako_attack_3_coordinate[i].y > WINDOW_H) {
				display_handle_3_mode[i] = HIDDEN;
			}
		}
	}
	//　丸みを帯びた並びの２つの弾を出す右側
	if (game_shot[3] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_4_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_3_4_NUM; j++) {
					zako_attack_4_angle[i][j] = 70 + i * 15;
					zako_attack_4_coordinate[i].x = 317 + cosf(D2R(zako_attack_4_angle[i][j])) * 200;	// + i * 10;
					zako_attack_4_coordinate[i].y = 0 + sinf(D2R(zako_attack_4_angle[i][j])) * 200;		//70;
				}
				zako_attack_4_mode[i] = MODE_MOVE;
				display_handle_4_mode[i] = DISPLAY;
				zako_attack_4_y = -2.5f;
			}
		}
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_4_mode[i] == MODE_MOVE) {
				zako_attack_4_coordinate[i].y += zako_attack_4_y;
				if (zako_attack_4_y <= 1.5f) {
					zako_attack_4_y += 0.01f;
				}
				zako_attack_4_count[i]++;
				if (zako_attack_4_count[i] >= 60) {
					if (display_handle_4_mode[i] == DISPLAY) {
						if (zako_attack_4_shot_mode[i] == MODE_WAIT) {
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							zako_attack_4_shot_mode[i] = MODE_MOVE;
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								display_handle_4_shot_mode[i][j] = DISPLAY;
							}
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								zako_attack_4_shot_coordinate[i][j].x = zako_attack_4_coordinate[i].x;
								zako_attack_4_shot_coordinate[i][j].y = zako_attack_4_coordinate[i].y;
								zako_attack_4_angle[i][j] = atan2f(player_coordinate.y - zako_attack_4_shot_coordinate[i][j].y, player_coordinate.x - zako_attack_4_shot_coordinate[i][j].x);
							}
						}
					}
				}
			}
			for (int j = 0; j < ATTACK_3_4_NUM; j++) {
				if (zako_attack_4_shot_mode[i] == MODE_MOVE) {
					zako_attack_4_shot_coordinate[i][j].x += cosf(zako_attack_4_angle[i][j]) * 2.5f * (j * 0.1 + 1);
					zako_attack_4_shot_coordinate[i][j].y += sinf(zako_attack_4_angle[i][j]) * 2.5f * (j * 0.1 + 1);
				}
				if (zako_attack_4_shot_coordinate[i][j].x < 0 || zako_attack_4_shot_coordinate[i][j].x > WINDOW_W || zako_attack_4_shot_coordinate[i][j].y < 0 || zako_attack_4_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_4_shot_mode[i][j] = HIDDEN;
				}
			}
			if (zako_attack_4_coordinate[i].x < 0 || zako_attack_4_coordinate[i].x > WINDOW_W || zako_attack_4_coordinate[i].y < 0 || zako_attack_4_coordinate[i].y > WINDOW_H) {
				display_handle_4_mode[i] = HIDDEN;
			}
		}
	}
	//　丸みを帯びた並びの２つの弾を出す左側
	if (game_shot[4] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_3_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_3_4_NUM; j++) {
					zako_attack_3_angle[i][j] = 30 + i * 15;
					zako_attack_3_coordinate[i].x = 130 + cosf(D2R(zako_attack_3_angle[i][j])) * 200;	// + i * 10;
					zako_attack_3_coordinate[i].y = 0 + sinf(D2R(zako_attack_3_angle[i][j])) * 200;		//70;
				}
				zako_attack_3_mode[i] = MODE_MOVE;
				display_handle_3_mode[i] = DISPLAY;
				zako_attack_3_y = -2.5f;
			}
		}
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_3_mode[i] == MODE_MOVE) {
				zako_attack_3_coordinate[i].y += zako_attack_3_y;
				if (zako_attack_3_y <= 1.5f) {
					zako_attack_3_y += 0.01f;
				}
				zako_attack_3_count[i]++;
				if (zako_attack_3_count[i] >= 60) {		//　後で >= 60に直す
					if (display_handle_3_mode[i] == DISPLAY) {
						if (zako_attack_3_shot_mode[i] == MODE_WAIT) {
							zako_attack_3_shot_mode[i] = MODE_MOVE;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								display_handle_3_shot_mode[i][j] = DISPLAY;
							}
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								zako_attack_3_shot_coordinate[i][j].x = zako_attack_3_coordinate[i].x;
								zako_attack_3_shot_coordinate[i][j].y = zako_attack_3_coordinate[i].y;
								zako_attack_3_angle[i][j] = atan2f(player_coordinate.y - zako_attack_3_shot_coordinate[i][j].y, player_coordinate.x - zako_attack_3_shot_coordinate[i][j].x);
							}
						}
					}
				}
			}
			for (int j = 0; j < ATTACK_3_4_NUM; j++) {
				if (zako_attack_3_shot_mode[i] == MODE_MOVE) {
					zako_attack_3_shot_coordinate[i][j].x += cosf(zako_attack_3_angle[i][j]) * 2.5f * (j * 0.1 + 1);
					zako_attack_3_shot_coordinate[i][j].y += sinf(zako_attack_3_angle[i][j]) * 2.5f * (j * 0.1 + 1);
				}
				if (zako_attack_3_shot_coordinate[i][j].x < 0 || zako_attack_3_shot_coordinate[i][j].x > WINDOW_W || zako_attack_3_shot_coordinate[i][j].y < 0 || zako_attack_3_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_3_shot_mode[i][j] = HIDDEN;
				}
			}
			if (zako_attack_3_coordinate[i].x < 0 || zako_attack_3_coordinate[i].x > WINDOW_W || zako_attack_3_coordinate[i].y < 0 || zako_attack_3_coordinate[i].y > WINDOW_H) {
				display_handle_3_mode[i] = HIDDEN;
			}
		}
	}
	//　丸みを帯びた並びの２つの弾を出す右側.
	if (game_shot[5] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_4_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_3_4_NUM; j++) {
					zako_attack_4_angle[i][j] = 70 + i * 15;
					zako_attack_4_coordinate[i].x = 317 + cosf(D2R(zako_attack_4_angle[i][j])) * 200;	// + i * 10;
					zako_attack_4_coordinate[i].y = 0 + sinf(D2R(zako_attack_4_angle[i][j])) * 200;		//70;
				}
				zako_attack_4_mode[i] = MODE_MOVE;
				display_handle_4_mode[i] = DISPLAY;
				zako_attack_4_y = -2.5f;
			}
		}
		for (int i = 0; i < ATTACK_3_4_MAX; i++) {
			if (zako_attack_4_mode[i] == MODE_MOVE) {
				zako_attack_4_coordinate[i].y += zako_attack_4_y;
				if (zako_attack_4_y <= 1.5f) {
					zako_attack_4_y += 0.01f;
				}
				zako_attack_4_count[i]++;
				if (zako_attack_4_count[i] >= 60) {
					if (display_handle_4_mode[i] == DISPLAY) {
						if (zako_attack_4_shot_mode[i] == MODE_WAIT) {
							zako_attack_4_shot_mode[i] = MODE_MOVE;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								display_handle_4_shot_mode[i][j] = DISPLAY;
							}
							for (int j = 0; j < ATTACK_3_4_NUM; j++) {
								zako_attack_4_shot_coordinate[i][j].x = zako_attack_4_coordinate[i].x;
								zako_attack_4_shot_coordinate[i][j].y = zako_attack_4_coordinate[i].y;
								zako_attack_4_angle[i][j] = atan2f(player_coordinate.y - zako_attack_4_shot_coordinate[i][j].y, player_coordinate.x - zako_attack_4_shot_coordinate[i][j].x);
							}
						}
					}
				}
			}
			for (int j = 0; j < ATTACK_3_4_NUM; j++) {
				if (zako_attack_4_shot_mode[i] == MODE_MOVE) {
					zako_attack_4_shot_coordinate[i][j].x += cosf(zako_attack_4_angle[i][j]) * 2.5f * (j * 0.1 + 1);
					zako_attack_4_shot_coordinate[i][j].y += sinf(zako_attack_4_angle[i][j]) * 2.5f * (j * 0.1 + 1);
				}
				if (zako_attack_4_shot_coordinate[i][j].x < 0 || zako_attack_4_shot_coordinate[i][j].x > WINDOW_W || zako_attack_4_shot_coordinate[i][j].y < 0 || zako_attack_4_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_4_shot_mode[i][j] = HIDDEN;
				}
			}
			if (zako_attack_4_coordinate[i].x < 0 || zako_attack_4_coordinate[i].x > WINDOW_W || zako_attack_4_coordinate[i].y < 0 || zako_attack_4_coordinate[i].y > WINDOW_H) {
				display_handle_4_mode[i] = HIDDEN;
			}
		}
	}
	//　左に猫耳と円、右に３体の２つの弾
	if (game_shot[6] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_5_MAX; i++) {
			if (attack_5_zako_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_5_NUM; j++) {
					attack_5_zako_coordinate[i].x = BG_X_HW - 80 - 50 * i;			// + i * 10;
					attack_5_zako_coordinate[i].y = 120 + 30 * i;					//70;
					attack_5_coordinate.x = 127;
					attack_5_coordinate.y = attack_5_zako_coordinate[1].y;
				}
				attack_5_zako_mode[i] = MODE_MOVE;
				display_handle_5_c_mode = DISPLAY;
				display_handle_5_mode[i] = DISPLAY;
				attack_5_y = -1.0f;
			}
		}
		for (int i = 0; i < ATTACK_5_MAX; i++) {
			if (attack_5_zako_mode[i] == MODE_MOVE) {
				attack_5_zako_coordinate[i].y += attack_5_y;
				attack_5_coordinate.y += attack_5_y / 3;
				if (attack_5_y <= 0.5f) {
					attack_5_y += 0.01f;
				}
				attack_5_zako_count[i]++;
				if (attack_5_zako_count[i] == 100) {
					if (display_handle_5_mode[i] == DISPLAY) {
						attack_5_zako_shot_mode[i] = MODE_MOVE;
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						for (int j = 0; j < ATTACK_5_NUM; j++) {
							display_handle_5_shot_mode[i][j] = DISPLAY;
						}
						for (int j = 0; j < ATTACK_5_NUM; j++) {
							attack_5_zako_shot_coordinate[i][j].x = attack_5_zako_coordinate[i].x;
							attack_5_zako_shot_coordinate[i][j].y = attack_5_zako_coordinate[i].y;
							attack_5_angle[i][j] = atan2f(player_coordinate.y - attack_5_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_5_zako_shot_coordinate[i][j].x);
						}
					}
					for (int p = 0; p < ATTACK_5_SHOT_NUM; p++) {
						if (display_handle_5_c_mode == DISPLAY) {
							attack_5_shot_coordinate[p].x = attack_5_coordinate.x;
							attack_5_shot_coordinate[p].y = attack_5_coordinate.y;
							attack_5_shot_r[p] = 360 / ATTACK_5_SHOT_NUM * p;
							display_handle_5_c_shot_mode[p] = DISPLAY;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						}
					}
					attack_5_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_5_coordinate.y, player_coordinate.x - attack_5_coordinate.x);

					for (int j = 0; j < NEKOMIMI_NUM; j++) {
						for (int i = 0; i < NEKOMIMI_MAX; i++) {
							if (display_handle_5_c_mode == DISPLAY) {
								attack_5_nekomimi_attack_shot_coordinate[i][j].x = attack_5_coordinate.x;
								attack_5_nekomimi_attack_shot_coordinate[i][j].y = attack_5_coordinate.y;
								attack_5_nekomimi_attack_mode[i][j] = MODE_MOVE;
								PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							}
							display_handle_5_nekomimi_shot_mode[i][j] = DISPLAY;
						}
						for (int i = 0; i < 4; i++) {	//　０～３
							attack_5_nekomimi_attack_missile_rot[i][j] = 0.0f - 22.5f + 15.0f * i;
							attack_5_nekomimi_attack_speed[i][j] = 0.25f;
						}
						for (int i = 0; i < 3; i++) {	//　４～６
							attack_5_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 15.0f + 15.0f * i;
							attack_5_nekomimi_attack_speed[i + 4][j] = 0.3f;
						}
						for (int i = 0; i < 2; i++) {
							attack_5_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 7.0f + 15.0f * i;
							attack_5_nekomimi_attack_speed[i + 7][j] = 0.35f;
						}
						attack_5_nekomimi_attack_missile_rot[9][j] = 0.0f;
						attack_5_nekomimi_attack_speed[9][j] = 0.4f;
					}
				}
			}
		}


		for (int i = 0; i < ATTACK_5_MAX; i++) {
			for (int j = 0; j < ATTACK_5_NUM; j++) {
				if (attack_5_zako_shot_mode[i] == MODE_MOVE) {
					//　マウスに向かって　2個飛ばす
					attack_5_zako_shot_coordinate[i][j].x += cosf(attack_5_angle[i][j]) * 1.0f * (j * 0.1 + 1);
					attack_5_zako_shot_coordinate[i][j].y += sinf(attack_5_angle[i][j]) * 1.0f * (j * 0.1 + 1);
					//for (int p = 0; p < ATTACK_5_SHOT_NUM; p++) {
					//	//　弾　広がる
					//	attack_5_shot_coordinate[p].x += cosf(D2R(attack_5_shot_r[p])) * 0.08f;
					//	attack_5_shot_coordinate[p].y += sinf(D2R(attack_5_shot_r[p])) * 0.08f;
					//	if (attack_5_shot_coordinate[p].x < 0 || attack_5_shot_coordinate[p].x > WINDOW_W || attack_5_shot_coordinate[p].y < 0 || attack_5_shot_coordinate[p].y > WINDOW_H) {
					//		display_handle_5_c_shot_mode[p] = HIDDEN;
					//	}
					//}
				}
				if (attack_5_zako_shot_coordinate[i][j].x < 0 || attack_5_zako_shot_coordinate[i][j].x > WINDOW_W || attack_5_zako_shot_coordinate[i][j].y < 0 || attack_5_zako_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_5_shot_mode[i][j] = HIDDEN;
				}
			}
			if (attack_5_zako_coordinate[i].x < 0 || attack_5_zako_coordinate[i].x > WINDOW_W || attack_5_zako_coordinate[i].y < 0 || attack_5_zako_coordinate[i].y > WINDOW_H) {
				display_handle_5_mode[i] = HIDDEN;
			}
		}

		//　猫
		for (int i = 0; i < NEKOMIMI_MAX; i++) {
			for (int j = 0; j < NEKOMIMI_NUM; j++) {
				if (attack_5_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					for (int p = 0; p < ATTACK_5_SHOT_NUM; p++) {
						//　弾　広がる
						attack_5_shot_coordinate[p].x += cosf(D2R(attack_5_shot_r[p])) * 0.02f;
						attack_5_shot_coordinate[p].y += sinf(D2R(attack_5_shot_r[p])) * 0.02f;
						if (attack_5_shot_coordinate[p].x < 0 || attack_5_shot_coordinate[p].x > WINDOW_W || attack_5_shot_coordinate[p].y < 0 || attack_5_shot_coordinate[p].y > WINDOW_H) {
							display_handle_5_c_shot_mode[p] = HIDDEN;
						}
					}

					attack_5_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_5_nekomimi_attack_missile_rot[i][j]) + attack_5_nekomimi_attack_angle + 90 * j) * attack_5_nekomimi_attack_speed[i][j] * 3;
					attack_5_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_5_nekomimi_attack_missile_rot[i][j]) + attack_5_nekomimi_attack_angle + 90 * j) * attack_5_nekomimi_attack_speed[i][j] * 3;
				}
				if (attack_5_nekomimi_attack_shot_coordinate[i][j].x < 0 || attack_5_nekomimi_attack_shot_coordinate[i][j].x > WINDOW_W || attack_5_nekomimi_attack_shot_coordinate[i][j].y < 0 || attack_5_nekomimi_attack_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_5_nekomimi_shot_mode[i][j] = HIDDEN;
				}
			}
		}
		if (attack_5_coordinate.x < 0 || attack_5_coordinate.x > WINDOW_W || attack_5_coordinate.y < 0 || attack_5_coordinate.y > WINDOW_H) {
			display_handle_5_c_mode = HIDDEN;
		}
	}
	//　右に猫耳と円、左に３体の２つの弾
	if (game_shot[7] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_6_MAX; i++) {
			if (attack_6_zako_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_6_NUM; j++) {
					attack_6_angle[i][j] = 100 + i * 15;
					attack_6_zako_coordinate[i].x = BG_X_LW + 80 + 50 * i;			// + i * 10;
					attack_6_zako_coordinate[i].y = 120 + 30 * i;					//70;
					attack_6_teki_coordinate.x = 320;
					attack_6_teki_coordinate.y = attack_6_zako_coordinate[1].y;
				}
				attack_6_zako_mode[i] = MODE_MOVE;
				display_handle_6_c_mode = DISPLAY;
				display_handle_6_mode[i] = DISPLAY;
				attack_6_y = -1.0f;
			}
		}
		for (int i = 0; i < ATTACK_6_MAX; i++) {
			if (attack_6_zako_mode[i] == MODE_MOVE) {
				attack_6_zako_coordinate[i].y += attack_6_y;
				attack_6_teki_coordinate.y += attack_6_y / 3;
				if (attack_6_y <= 0.5f) {
					attack_6_y += 0.01f;
				}
				attack_6_zako_count[i]++;
				if (attack_6_zako_count[i] == 100) {
					if (display_handle_6_mode[i] == DISPLAY) {
						attack_6_zako_shot_mode[i] = MODE_MOVE;
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						for (int j = 0; j < ATTACK_5_NUM; j++) {
							display_handle_6_shot_mode[i][j] = DISPLAY;
						}
						for (int j = 0; j < ATTACK_6_NUM; j++) {
							attack_6_zako_shot_coordinate[i][j].x = attack_6_zako_coordinate[i].x;
							attack_6_zako_shot_coordinate[i][j].y = attack_6_zako_coordinate[i].y;
							attack_6_angle[i][j] = atan2f(player_coordinate.y - attack_6_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_6_zako_shot_coordinate[i][j].x);
						}
					}
					for (int p = 0; p < ATTACK_6_SHOT_NUM; p++) {
						if (display_handle_6_c_mode == DISPLAY) {
							attack_6_teki_shot_coordinate[p].x = attack_6_teki_coordinate.x;
							attack_6_teki_shot_coordinate[p].y = attack_6_teki_coordinate.y;
							attack_6_teki_shot_r[p] = 360 / ATTACK_6_SHOT_NUM * p;
							display_handle_6_c_shot_mode[p] = DISPLAY;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						}
					}
					attack_6_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_6_teki_coordinate.y, player_coordinate.x - attack_6_teki_coordinate.x);

					for (int j = 0; j < NEKOMIMI_NUM; j++) {
						for (int i = 0; i < NEKOMIMI_MAX; i++) {
							if (display_handle_6_c_mode == DISPLAY) {
								attack_6_nekomimi_attack_shot_coordinate[i][j].x = attack_6_teki_coordinate.x;
								attack_6_nekomimi_attack_shot_coordinate[i][j].y = attack_6_teki_coordinate.y;
								attack_6_nekomimi_attack_mode[i][j] = MODE_MOVE;
								PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
								display_handle_6_nekomimi_shot_mode[i][j] = DISPLAY;
							}
						}
						for (int i = 0; i < 4; i++) {	//　０～３
							attack_6_nekomimi_attack_missile_rot[i][j] = 0.0f - 22.5f + 15.0f * i;
							attack_6_nekomimi_attack_speed[i][j] = 0.25f;
						}
						for (int i = 0; i < 3; i++) {	//　４～６
							attack_6_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 15.0f + 15.0f * i;
							attack_6_nekomimi_attack_speed[i + 4][j] = 0.3f;
						}
						for (int i = 0; i < 2; i++) {
							attack_6_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 7.0f + 15.0f * i;
							attack_6_nekomimi_attack_speed[i + 7][j] = 0.35f;
						}
						attack_6_nekomimi_attack_missile_rot[9][j] = 0.0f;
						attack_6_nekomimi_attack_speed[9][j] = 0.4f;
					}
				}
			}
		}


		for (int i = 0; i < ATTACK_6_MAX; i++) {
			for (int j = 0; j < ATTACK_6_NUM; j++) {
				if (attack_6_zako_shot_mode[i] == MODE_MOVE) {
					//　マウスに向かって　2個飛ばす
					attack_6_zako_shot_coordinate[i][j].x += cosf(attack_6_angle[i][j]) * 1.0f * (j * 0.1 + 1);
					attack_6_zako_shot_coordinate[i][j].y += sinf(attack_6_angle[i][j]) * 1.0f * (j * 0.1 + 1);
					if (attack_6_zako_shot_coordinate[i][j].x < 0 || attack_6_zako_shot_coordinate[i][j].x > WINDOW_W || attack_6_zako_shot_coordinate[i][j].y < 0 || attack_6_zako_shot_coordinate[i][j].y > WINDOW_H) {
						display_handle_6_shot_mode[i][j] = HIDDEN;
					}
				}
			}
			if (attack_6_zako_coordinate[i].x < 0 || attack_6_zako_coordinate[i].x > WINDOW_W || attack_6_zako_coordinate[i].y < 0 || attack_6_zako_coordinate[i].y > WINDOW_H) {
				display_handle_6_mode[i] = HIDDEN;
			}
		}

		//　猫
		for (int i = 0; i < NEKOMIMI_MAX; i++) {
			for (int j = 0; j < NEKOMIMI_NUM; j++) {
				if (attack_6_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					for (int p = 0; p < ATTACK_6_SHOT_NUM; p++) {
						//　弾　広がる
						attack_6_teki_shot_coordinate[p].x += cosf(D2R(attack_6_teki_shot_r[p])) * 0.02f;
						attack_6_teki_shot_coordinate[p].y += sinf(D2R(attack_6_teki_shot_r[p])) * 0.02f;
						if (attack_6_teki_shot_coordinate[p].x < 0 || attack_6_teki_shot_coordinate[p].x > WINDOW_W || attack_6_teki_shot_coordinate[p].y < 0 || attack_6_teki_shot_coordinate[p].y > WINDOW_H) {
							display_handle_6_c_shot_mode[p] = HIDDEN;
						}
					}

					attack_6_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_6_nekomimi_attack_missile_rot[i][j]) + attack_6_nekomimi_attack_angle + 90 * j) * attack_6_nekomimi_attack_speed[i][j] * 3;
					attack_6_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_6_nekomimi_attack_missile_rot[i][j]) + attack_6_nekomimi_attack_angle + 90 * j) * attack_6_nekomimi_attack_speed[i][j] * 3;
				}
				if (attack_6_nekomimi_attack_shot_coordinate[i][j].x < 0 || attack_6_nekomimi_attack_shot_coordinate[i][j].x > WINDOW_W || attack_6_nekomimi_attack_shot_coordinate[i][j].y < 0 || attack_6_nekomimi_attack_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_6_nekomimi_shot_mode[i][j] = HIDDEN;
				}
			}
		}
		if (attack_6_teki_coordinate.x < 0 || attack_6_teki_coordinate.x > WINDOW_W || attack_6_teki_coordinate.y < 0 || attack_6_teki_coordinate.y > WINDOW_H) {
			display_handle_6_c_mode = HIDDEN;
		}
	}
	//　右から順番に並べる３つの弾
	if (game_shot[8] == MODE_MOVE) {
		attack_7_count++;
		if (attack_7_count >= 30) {
			attack_7_count = 0;
			if (attack_7_zako_mode[attack_7_num] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_7_NUM; j++) {
					attack_7_angle[attack_7_num][j] = 30 + attack_7_num * 15;
					attack_7_zako_coordinate[attack_7_num].x = 382 - 45 * attack_7_num;	// + i * 10;
					attack_7_zako_coordinate[attack_7_num].y = 130;		//70;
					//for (int i = 0; i < ATTACK_7_MAX; i++) {
					//	attack_7_zako_shot_coordinate[]
					//}
				}
				display_handle_7_mode[attack_7_num] = DISPLAY;
				attack_7_y[attack_7_num] = -2.5f;
				attack_7_zako_shot_mode[attack_7_num] = MODE_WAIT;
				attack_7_zako_mode[attack_7_num] = MODE_MOVE;
				//display_handle_7_mode[attack_7_num] = MODE_WAIT;
				
			}
			attack_7_num++;
			if (attack_7_num >= ATTACK_7_MAX) {
				attack_7_num = 0;
			}
		}
		for (int i = 0; i < ATTACK_7_MAX; i++) {
			if (attack_7_zako_mode[i] == MODE_MOVE) {
				attack_7_zako_coordinate[i].y += attack_7_y[i];
				if (attack_7_y[i] <= 1.0f) {
					attack_7_y[i] += 0.05f;
				}
				attack_7_zako_count[i]++;
				if (attack_7_zako_count[i] == 60) {
					if (display_handle_7_mode[i] == DISPLAY) {
						attack_7_zako_shot_mode[i] = MODE_MOVE;
						for (int j = 0; j < ATTACK_7_NUM; j++) {
							PlaySoundMem(se_enemy_attack[2], DX_PLAYTYPE_BACK);
							display_handle_7_shot_mode[i][j] = DISPLAY;
							attack_7_zako_shot_coordinate[i][j].x = attack_7_zako_coordinate[i].x;
							attack_7_zako_shot_coordinate[i][j].y = attack_7_zako_coordinate[i].y;
							attack_7_angle[i][j] = atan2f(player_coordinate.y - attack_7_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_7_zako_shot_coordinate[i][j].x);
						}

					}
				}
			}
			for (int j = 0; j < ATTACK_7_NUM; j++) {
				if (attack_7_zako_shot_mode[i] == MODE_MOVE) {
					attack_7_zako_shot_coordinate[i][j].x += cosf(attack_7_angle[i][j]) * 1.5f * (j * 0.1 + 1);
					attack_7_zako_shot_coordinate[i][j].y += sinf(attack_7_angle[i][j]) * 1.5f * (j * 0.1 + 1);
				}
				if (attack_7_zako_shot_coordinate[i][j].x < 0 || attack_7_zako_shot_coordinate[i][j].x > WINDOW_W || attack_7_zako_shot_coordinate[i][j].y < 0 || attack_7_zako_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_7_shot_mode[i][j] = HIDDEN;
				}
			}
			if (attack_7_zako_coordinate[i].x < 0 || attack_7_zako_coordinate[i].x > WINDOW_W || attack_7_zako_coordinate[i].y < 0 || attack_7_zako_coordinate[i].y > WINDOW_H) {
				display_handle_7_mode[i] = HIDDEN;
			}
		}
	}
	//　左から順番に並べる３つの弾
	if (game_shot[9] == MODE_MOVE) {
		attack_8_count++;
		if (attack_8_count >= 30) {
			attack_8_count = 0;
			if (attack_8_zako_mode[attack_8_num] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_8_NUM; j++) {
					attack_8_angle[attack_8_num][j] = 30 + attack_8_num * 15;
					attack_8_zako_coordinate[attack_8_num].x = 65 + 45 * attack_8_num;	// + i * 10;
					attack_8_zako_coordinate[attack_8_num].y = 130;		//70;
				}
				attack_8_zako_mode[attack_8_num] = MODE_MOVE;
				display_handle_8_mode[attack_8_num] = DISPLAY;
				attack_8_y[attack_8_num] = -2.5f;
				attack_8_zako_shot_mode[attack_8_num] = MODE_WAIT;
			}
			attack_8_num++;
			if (attack_8_num >= ATTACK_8_MAX) {
				attack_8_num = 0;
			}
				
		}
		for (int i = 0; i < ATTACK_8_MAX; i++) {
			if (attack_8_zako_mode[i] == MODE_MOVE) {
				attack_8_zako_coordinate[i].y += attack_8_y[i];
				if (attack_8_y[i] <= 1.0f) {
					attack_8_y[i] += 0.05f;
				}
				attack_8_zako_count[i]++;
				if (attack_8_zako_count[i] == 60) {
					if (display_handle_8_mode[i] == DISPLAY) {
						attack_8_zako_shot_mode[i] = MODE_MOVE;
						for (int j = 0; j < ATTACK_8_NUM; j++) {
							PlaySoundMem(se_enemy_attack[2], DX_PLAYTYPE_BACK);
							display_handle_8_shot_mode[i][j] = DISPLAY;
							attack_8_zako_shot_coordinate[i][j].x = attack_8_zako_coordinate[i].x;
							attack_8_zako_shot_coordinate[i][j].y = attack_8_zako_coordinate[i].y;
							attack_8_angle[i][j] = atan2f(player_coordinate.y - attack_8_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_8_zako_shot_coordinate[i][j].x);
						}
					}
				}
			}
			for (int j = 0; j < ATTACK_8_NUM; j++) {
				if (attack_8_zako_shot_mode[i] == MODE_MOVE) {
					attack_8_zako_shot_coordinate[i][j].x += cosf(attack_8_angle[i][j]) * 1.5f * (j * 0.1 + 1);
					attack_8_zako_shot_coordinate[i][j].y += sinf(attack_8_angle[i][j]) * 1.5f * (j * 0.1 + 1);
				}
				if (attack_8_zako_shot_coordinate[i][j].x < 0 || attack_8_zako_shot_coordinate[i][j].x > WINDOW_W || attack_8_zako_shot_coordinate[i][j].y < 0 || attack_8_zako_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_8_shot_mode[i][j] = HIDDEN;
				}
			}
			if (attack_8_zako_coordinate[i].x < 0 || attack_8_zako_coordinate[i].x > WINDOW_W || attack_8_zako_coordinate[i].y < 0 || attack_8_zako_coordinate[i].y > WINDOW_H) {
				display_handle_8_mode[i] = HIDDEN;
			}
		}
	}
	//　左に猫耳と円、右に３体の２つの弾
	if (game_shot[10] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_5_MAX; i++) {
			if (attack_5_zako_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_5_NUM; j++) {
					attack_5_zako_coordinate[i].x = BG_X_HW - 80 - 50 * i;			// + i * 10;
					attack_5_zako_coordinate[i].y = 120 + 30 * i;					//70;
					attack_5_coordinate.x = 127;
					attack_5_coordinate.y = attack_5_zako_coordinate[1].y;
				}
				attack_5_zako_mode[i] = MODE_MOVE;
				display_handle_5_c_mode = DISPLAY;
				display_handle_5_mode[i] = DISPLAY;
				attack_5_zako_shot_mode[i] = MODE_WAIT;
				attack_5_y = -1.0f;
				for (int i = 0; i < ATTACK_5_SHOT_NUM; i++) {
					attack_5_shot_r[i] = 0;
				}
			}
		}
		for (int i = 0; i < ATTACK_5_MAX; i++) {
			if (attack_5_zako_mode[i] == MODE_MOVE) {
				attack_5_zako_coordinate[i].y += attack_5_y;
				attack_5_coordinate.y += attack_5_y / 3;
				if (attack_5_y <= 0.5f) {
					attack_5_y += 0.01f;
				}
				attack_5_zako_count[i]++;
				if (attack_5_zako_count[i] == 100) {
					if (display_handle_5_mode[i] == DISPLAY) {
						attack_5_zako_shot_mode[i] = MODE_MOVE;
						for (int j = 0; j < ATTACK_5_NUM; j++) {
							display_handle_5_shot_mode[i][j] = DISPLAY;
							PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
						}
						for (int j = 0; j < ATTACK_5_NUM; j++) {
							attack_5_zako_shot_coordinate[i][j].x = attack_5_zako_coordinate[i].x;
							attack_5_zako_shot_coordinate[i][j].y = attack_5_zako_coordinate[i].y;
							attack_5_angle[i][j] = atan2f(player_coordinate.y - attack_5_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_5_zako_shot_coordinate[i][j].x);
							//attack_5_angle[i][j] = atan2f(player_coordinate.y - attack_5_zako_coordinate[i].y, player_coordinate.y - attack_5_zako_coordinate[i].x);
						}
					}
					for (int p = 0; p < ATTACK_5_SHOT_NUM; p++) {
						if (display_handle_5_c_mode == DISPLAY) {
							attack_5_shot_coordinate[p].x = attack_5_coordinate.x;
							attack_5_shot_coordinate[p].y = attack_5_coordinate.y;
							attack_5_shot_r[p] = 360 / ATTACK_5_SHOT_NUM * p;
							PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
							display_handle_5_c_shot_mode[p] = DISPLAY;
						}
					}
					attack_5_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_5_coordinate.y, player_coordinate.x - attack_5_coordinate.x);

					for (int j = 0; j < NEKOMIMI_NUM; j++) {
						for (int i = 0; i < NEKOMIMI_MAX; i++) {
							if (display_handle_5_c_mode == DISPLAY) {
								attack_5_nekomimi_attack_shot_coordinate[i][j].x = attack_5_coordinate.x;
								attack_5_nekomimi_attack_shot_coordinate[i][j].y = attack_5_coordinate.y;
								attack_5_nekomimi_attack_mode[i][j] = MODE_MOVE;
								PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
							}
							display_handle_5_nekomimi_shot_mode[i][j] = DISPLAY;
						}
						for (int i = 0; i < 4; i++) {	//　０～３
							attack_5_nekomimi_attack_missile_rot[i][j] = 0.0f - 22.5f + 15.0f * i;
							attack_5_nekomimi_attack_speed[i][j] = 0.25f;
						}
						for (int i = 0; i < 3; i++) {	//　４～６
							attack_5_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 15.0f + 15.0f * i;
							attack_5_nekomimi_attack_speed[i + 4][j] = 0.3f;
						}
						for (int i = 0; i < 2; i++) {
							attack_5_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 7.0f + 15.0f * i;
							attack_5_nekomimi_attack_speed[i + 7][j] = 0.35f;
						}
						attack_5_nekomimi_attack_missile_rot[9][j] = 0.0f;
						attack_5_nekomimi_attack_speed[9][j] = 0.4f;
					}
				}
			}
		}


		for (int i = 0; i < ATTACK_5_MAX; i++) {
			for (int j = 0; j < ATTACK_5_NUM; j++) {
				if (attack_5_zako_shot_mode[i] == MODE_MOVE) {
					//　マウスに向かって　2個飛ばす
					attack_5_zako_shot_coordinate[i][j].x += cosf(attack_5_angle[i][j]) * 1.0f * (j * 0.1 + 1);
					attack_5_zako_shot_coordinate[i][j].y += sinf(attack_5_angle[i][j]) * 1.0f * (j * 0.1 + 1);
				}
				if (attack_5_zako_shot_coordinate[i][j].x < 0 || attack_5_zako_shot_coordinate[i][j].x > WINDOW_W || attack_5_zako_shot_coordinate[i][j].y < 0 || attack_5_zako_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_5_shot_mode[i][j] = HIDDEN;
				}
			}
			if (attack_5_zako_coordinate[i].x < 0 || attack_5_zako_coordinate[i].x > WINDOW_W || attack_5_zako_coordinate[i].y < 0 || attack_5_zako_coordinate[i].y > WINDOW_H) {
				display_handle_5_mode[i] = HIDDEN;
			}
		}

		//　猫
		for (int i = 0; i < NEKOMIMI_MAX; i++) {
			for (int j = 0; j < NEKOMIMI_NUM; j++) {
				if (attack_5_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					for (int p = 0; p < ATTACK_5_SHOT_NUM; p++) {
						//　弾　広がる
						attack_5_shot_coordinate[p].x += cosf(D2R(attack_5_shot_r[p])) * 0.02f;
						attack_5_shot_coordinate[p].y += sinf(D2R(attack_5_shot_r[p])) * 0.02f;
						if (attack_5_shot_coordinate[p].x < 0 || attack_5_shot_coordinate[p].x > WINDOW_W || attack_5_shot_coordinate[p].y < 0 || attack_5_shot_coordinate[p].y > WINDOW_H) {
							display_handle_5_c_shot_mode[p] = HIDDEN;
						}
					}

					attack_5_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_5_nekomimi_attack_missile_rot[i][j]) + attack_5_nekomimi_attack_angle + 90 * j) * attack_5_nekomimi_attack_speed[i][j] * 3;
					attack_5_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_5_nekomimi_attack_missile_rot[i][j]) + attack_5_nekomimi_attack_angle + 90 * j) * attack_5_nekomimi_attack_speed[i][j] * 3;
				}
				if (attack_5_nekomimi_attack_shot_coordinate[i][j].x < 0 || attack_5_nekomimi_attack_shot_coordinate[i][j].x > WINDOW_W || attack_5_nekomimi_attack_shot_coordinate[i][j].y < 0 || attack_5_nekomimi_attack_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_5_nekomimi_shot_mode[i][j] = HIDDEN;
				}
			}
		}
		if (attack_5_coordinate.x < 0 || attack_5_coordinate.x > WINDOW_W || attack_5_coordinate.y < 0 || attack_5_coordinate.y > WINDOW_H) {
			display_handle_5_c_mode = HIDDEN;
		}
	}
	//　右に猫耳と円、左に３体の２つの弾
	if (game_shot[11] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_6_MAX; i++) {
			if (attack_6_zako_mode[i] == MODE_WAIT) {
				for (int j = 0; j < ATTACK_6_NUM; j++) {
					attack_6_angle[i][j] = 100 + i * 15;
					attack_6_zako_coordinate[i].x = BG_X_LW + 80 + 50 * i;			// + i * 10;
					attack_6_zako_coordinate[i].y = 120 + 30 * i;					//70;
					attack_6_teki_coordinate.x = 320;
					attack_6_teki_coordinate.y = attack_6_zako_coordinate[1].y;
				}
				attack_6_zako_mode[i] = MODE_MOVE;
				display_handle_6_c_mode = DISPLAY;
				display_handle_6_mode[i] = DISPLAY;
				attack_6_y = -1.0f;
				for (int i = 0; i < ATTACK_6_SHOT_NUM; i++) {
					attack_6_teki_shot_r[i] = 0;
				}
			}
		}
		for (int i = 0; i < ATTACK_6_MAX; i++) {
			if (attack_6_zako_mode[i] == MODE_MOVE) {
				attack_6_zako_coordinate[i].y += attack_6_y;
				attack_6_teki_coordinate.y += attack_6_y / 3;
				if (attack_6_y <= 0.5f) {
					attack_6_y += 0.01f;
				}
				attack_6_zako_count[i]++;
				if (attack_6_zako_count[i] == 100) {
					if (display_handle_6_mode[i] == DISPLAY) {
						attack_6_zako_shot_mode[i] = MODE_MOVE;
						for (int j = 0; j < ATTACK_6_NUM; j++) {
							PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
							display_handle_6_shot_mode[i][j] = DISPLAY;
						}
						for (int j = 0; j < ATTACK_6_NUM; j++) {
							attack_6_zako_shot_coordinate[i][j].x = attack_6_zako_coordinate[i].x;
							attack_6_zako_shot_coordinate[i][j].y = attack_6_zako_coordinate[i].y;
							attack_6_angle[i][j] = atan2f(player_coordinate.y - attack_6_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_6_zako_shot_coordinate[i][j].x);
						}
					}
					for (int p = 0; p < ATTACK_6_SHOT_NUM; p++) {
						if (display_handle_6_c_mode == DISPLAY) {
							attack_6_teki_shot_coordinate[p].x = attack_6_teki_coordinate.x;
							attack_6_teki_shot_coordinate[p].y = attack_6_teki_coordinate.y;
							attack_6_teki_shot_r[p] = 360 / ATTACK_6_SHOT_NUM * p;
							PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
							display_handle_6_c_shot_mode[p] = DISPLAY;
						}
					}
					attack_6_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_6_teki_coordinate.y, player_coordinate.x - attack_6_teki_coordinate.x);

					for (int j = 0; j < NEKOMIMI_NUM; j++) {
						for (int i = 0; i < NEKOMIMI_MAX; i++) {
							if (display_handle_6_c_mode == DISPLAY) {
								attack_6_nekomimi_attack_shot_coordinate[i][j].x = attack_6_teki_coordinate.x;
								attack_6_nekomimi_attack_shot_coordinate[i][j].y = attack_6_teki_coordinate.y;
								attack_6_nekomimi_attack_mode[i][j] = MODE_MOVE;
								PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
								display_handle_6_nekomimi_shot_mode[i][j] = DISPLAY;
							}
						}
						for (int i = 0; i < 4; i++) {	//　０～３
							attack_6_nekomimi_attack_missile_rot[i][j] = 0.0f - 22.5f + 15.0f * i;
							attack_6_nekomimi_attack_speed[i][j] = 0.25f;
						}
						for (int i = 0; i < 3; i++) {	//　４～６
							attack_6_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 15.0f + 15.0f * i;
							attack_6_nekomimi_attack_speed[i + 4][j] = 0.3f;
						}
						for (int i = 0; i < 2; i++) {
							attack_6_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 7.0f + 15.0f * i;
							attack_6_nekomimi_attack_speed[i + 7][j] = 0.35f;
						}
						attack_6_nekomimi_attack_missile_rot[9][j] = 0.0f;
						attack_6_nekomimi_attack_speed[9][j] = 0.4f;
					}
				}
			}
		}


		for (int i = 0; i < ATTACK_6_MAX; i++) {
			for (int j = 0; j < ATTACK_6_NUM; j++) {
				if (attack_6_zako_shot_mode[i] == MODE_MOVE) {
					//　マウスに向かって　2個飛ばす
					attack_6_zako_shot_coordinate[i][j].x += cosf(attack_6_angle[i][j]) * 1.0f * (j * 0.1 + 1);
					attack_6_zako_shot_coordinate[i][j].y += sinf(attack_6_angle[i][j]) * 1.0f * (j * 0.1 + 1);
					if (attack_6_zako_shot_coordinate[i][j].x < 0 || attack_6_zako_shot_coordinate[i][j].x > WINDOW_W || attack_6_zako_shot_coordinate[i][j].y < 0 || attack_6_zako_shot_coordinate[i][j].y > WINDOW_H) {
						display_handle_6_shot_mode[i][j] = HIDDEN;
					}
				}
			}
			if (attack_6_zako_coordinate[i].x < 0 || attack_6_zako_coordinate[i].x > WINDOW_W || attack_6_zako_coordinate[i].y < 0 || attack_6_zako_coordinate[i].y > WINDOW_H) {
				display_handle_6_mode[i] = HIDDEN;
			}
		}

		//　猫
		for (int i = 0; i < NEKOMIMI_MAX; i++) {
			for (int j = 0; j < NEKOMIMI_NUM; j++) {
				if (attack_6_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					for (int p = 0; p < ATTACK_6_SHOT_NUM; p++) {
						//　弾　広がる
						attack_6_teki_shot_coordinate[p].x += cosf(D2R(attack_6_teki_shot_r[p])) * 0.02f;
						attack_6_teki_shot_coordinate[p].y += sinf(D2R(attack_6_teki_shot_r[p])) * 0.02f;
						if (attack_6_teki_shot_coordinate[p].x < 0 || attack_6_teki_shot_coordinate[p].x > WINDOW_W || attack_6_teki_shot_coordinate[p].y < 0 || attack_6_teki_shot_coordinate[p].y > WINDOW_H) {
							display_handle_6_c_shot_mode[p] = HIDDEN;
						}
					}

					attack_6_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_6_nekomimi_attack_missile_rot[i][j]) + attack_6_nekomimi_attack_angle + 90 * j) * attack_6_nekomimi_attack_speed[i][j] * 3;
					attack_6_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_6_nekomimi_attack_missile_rot[i][j]) + attack_6_nekomimi_attack_angle + 90 * j) * attack_6_nekomimi_attack_speed[i][j] * 3;
				}
				if (attack_6_nekomimi_attack_shot_coordinate[i][j].x < 0 || attack_6_nekomimi_attack_shot_coordinate[i][j].x > WINDOW_W || attack_6_nekomimi_attack_shot_coordinate[i][j].y < 0 || attack_6_nekomimi_attack_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_6_nekomimi_shot_mode[i][j] = HIDDEN;
				}
			}
		}
		if (attack_6_teki_coordinate.x < 0 || attack_6_teki_coordinate.x > WINDOW_W || attack_6_teki_coordinate.y < 0 || attack_6_teki_coordinate.y > WINDOW_H) {
			display_handle_6_c_mode = HIDDEN;
		}
	}
	//　中央に猫耳、左右に3体ずつ２つの弾
	if (game_shot[12] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_9_NUM; i++) {
			if (attack_9_zako_mode[i] == MODE_WAIT) {
				display_handle_9_nekomimi_mode = DISPLAY;
				display_handle_9_mode[i] = DISPLAY;
				attack_9_zako_mode[i] = MODE_MOVE;
				attack_9_nekomimi_attack_coordinate.x = (BG_X_HW - BG_X_LW) / 2 + BG_X_LW;
				attack_9_nekomimi_attack_coordinate.y = 120;
				attack_9_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_9_nekomimi_attack_coordinate.y, player_coordinate.x - attack_9_nekomimi_attack_coordinate.x);
				for (int i = 0; i < 3; i++) {
					attack_9_zako_coordinate[i].x = attack_9_nekomimi_attack_coordinate.x - 70 - 40 * i;
					attack_9_zako_coordinate[i].y = 100 - 20 * i;
				}
				for (int i = 3; i < ATTACK_9_NUM; i++) {
					attack_9_zako_coordinate[i].x = attack_9_nekomimi_attack_coordinate.x + 70 + 40 * (i - 3);
					attack_9_zako_coordinate[i].y = 100 - 20 * (i - 3);
				}
				for (int j = 0; j < ATTACK_9_MAX; j++) {
					if (display_handle_9_mode[i] == DISPLAY) {
						attack_9_zako_shot_coordinate[i][j].x = attack_9_zako_coordinate[i].x;
						attack_9_zako_shot_coordinate[i][j].y = attack_9_zako_coordinate[i].y;
						attack_9_angle[i][j] = atan2f(player_coordinate.y - attack_9_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_9_zako_shot_coordinate[i][j].x);
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						display_handle_9_shot_mode[i][j] = DISPLAY;
					}
				}
			}
		}
		for (int j = 0; j < ATTACK_9_NEKOMIMI_NUM; j++) {
			for (int i = 0; i < ATTACK_9_NEKOMIMI_MAX; i++) {
				if (attack_9_nekomimi_attack_mode[i][j] == MODE_WAIT) {
					if (display_handle_9_nekomimi_mode == DISPLAY) {
						attack_9_nekomimi_attack_shot_coordinate[i][j].x = attack_9_nekomimi_attack_coordinate.x;
						attack_9_nekomimi_attack_shot_coordinate[i][j].y = attack_9_nekomimi_attack_coordinate.y;
						attack_9_nekomimi_attack_mode[i][j] = MODE_MOVE;
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						display_handle_9_nekomimi_shot_mode[i][j] = DISPLAY;
					}
					for (int i = 0; i < 4; i++) {	//　０～３
						attack_9_nekomimi_attack_missile_rot[i][j] = 0.0f - 30.0f + 20.0f * i;
						attack_9_nekomimi_attack_speed[i][j] = 0.3f;
					}
					for (int i = 0; i < 3; i++) {	//　４～６
						attack_9_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 15.0f + 15.0f * i;
						attack_9_nekomimi_attack_speed[i + 4][j] = 0.45f;
					}
					for (int i = 0; i < 2; i++) {
						attack_9_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 7.5f + 15.0f * i;	// /2
						attack_9_nekomimi_attack_speed[i + 7][j] = 0.6f;
					}
					attack_9_nekomimi_attack_missile_rot[9][j] = 0.0f;
					attack_9_nekomimi_attack_speed[9][j] = 0.75f;
				}
			}
		}
		attack_9_nekomimi_attack_coordinate.y += 0.5f;
		for (int i = 0; i < ATTACK_9_NUM; i++) {
			attack_9_zako_coordinate[i].y += 0.5f;
		}

		float s = 360.0f / ATTACK_9_NEKOMIMI_NUM;
		for (int i = 0; i < ATTACK_9_NEKOMIMI_MAX; i++) {
			for (int j = 0; j < ATTACK_9_NEKOMIMI_NUM; j++) {
				if (attack_9_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					attack_9_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_9_nekomimi_attack_missile_rot[i][j]) + attack_9_nekomimi_attack_angle + D2R(s * j)) * attack_9_nekomimi_attack_speed[i][j];
					attack_9_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_9_nekomimi_attack_missile_rot[i][j]) + attack_9_nekomimi_attack_angle + D2R(s * j)) * attack_9_nekomimi_attack_speed[i][j];
				}
				if (attack_9_nekomimi_attack_shot_coordinate[i][j].x < 0 || attack_9_nekomimi_attack_shot_coordinate[i][j].x > WINDOW_W || attack_9_nekomimi_attack_shot_coordinate[i][j].y < 0 || attack_9_nekomimi_attack_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_9_nekomimi_shot_mode[i][j] = HIDDEN;
				}
			}
		}
		for (int i = 0; i < ATTACK_9_NUM; i++) {
			for (int j = 0; j < ATTACK_9_MAX; j++) {
				if (attack_9_zako_mode[i] == MODE_MOVE) {
					attack_9_zako_shot_coordinate[i][j].x += cosf(attack_9_angle[i][j]) * 0.8f * (j * 0.1 + 1);
					attack_9_zako_shot_coordinate[i][j].y += sinf(attack_9_angle[i][j]) * 0.8f * (j * 0.1 + 1);
				}
				if (attack_9_zako_shot_coordinate[i][j].x < 0 || attack_9_zako_shot_coordinate[i][j].x > WINDOW_W || attack_9_zako_shot_coordinate[i][j].y < 0 || attack_9_zako_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_9_shot_mode[i][j] = HIDDEN;
				}
			}
			if (attack_9_zako_coordinate[i].x < 0 || attack_9_zako_coordinate[i].x > WINDOW_W || attack_9_zako_coordinate[i].y < 0 || attack_9_zako_coordinate[i].y > WINDOW_H) {
				display_handle_9_mode[i] = HIDDEN;
			}
		}
		if (attack_9_nekomimi_attack_coordinate.x < 0 || attack_9_nekomimi_attack_coordinate.x > WINDOW_W || attack_9_nekomimi_attack_coordinate.y < 0 || attack_9_nekomimi_attack_coordinate.y > WINDOW_H) {
			display_handle_9_nekomimi_mode = HIDDEN;
		}
	}
	//　中央に猫耳、左右に3体ずつ２つの弾	
	if (game_shot[13] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_10_NUM; i++) {
			if (attack_10_zako_mode[i] == MODE_WAIT) {
				display_handle_10_nekomimi_mode = DISPLAY;
				display_handle_10_mode[i] = DISPLAY;
				attack_10_zako_mode[i] = MODE_MOVE;
				attack_10_nekomimi_attack_coordinate.x = (BG_X_HW - BG_X_LW) / 2 + BG_X_LW;
				attack_10_nekomimi_attack_coordinate.y = 120;
				attack_10_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_10_nekomimi_attack_coordinate.y, player_coordinate.x - attack_10_nekomimi_attack_coordinate.x);
				for (int i = 0; i < 3; i++) {
					attack_10_zako_coordinate[i].x = attack_10_nekomimi_attack_coordinate.x - 70 - 40 * i;
					attack_10_zako_coordinate[i].y = 100 - 20 * i;
				}
				for (int i = 3; i < ATTACK_10_NUM; i++) {
					attack_10_zako_coordinate[i].x = attack_10_nekomimi_attack_coordinate.x + 70 + 40 * (i - 3);
					attack_10_zako_coordinate[i].y = 100 - 20 * (i - 3);
				}
				for (int j = 0; j < ATTACK_10_MAX; j++) {
					if (display_handle_10_mode[i] == DISPLAY) {
						attack_10_zako_shot_coordinate[i][j].x = attack_10_zako_coordinate[i].x;
						attack_10_zako_shot_coordinate[i][j].y = attack_10_zako_coordinate[i].y;
						attack_10_angle[i][j] = atan2f(player_coordinate.y - attack_10_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_10_zako_shot_coordinate[i][j].x);
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						display_handle_10_shot_mode[i][j] = DISPLAY;
					}
				}
			}
		}
		for (int j = 0; j < ATTACK_10_NEKOMIMI_NUM; j++) {
			for (int i = 0; i < ATTACK_10_NEKOMIMI_MAX; i++) {
				if (attack_10_nekomimi_attack_mode[i][j] == MODE_WAIT) {
					if (display_handle_10_nekomimi_mode == DISPLAY) {
						attack_10_nekomimi_attack_shot_coordinate[i][j].x = attack_10_nekomimi_attack_coordinate.x;
						attack_10_nekomimi_attack_shot_coordinate[i][j].y = attack_10_nekomimi_attack_coordinate.y;
						attack_10_nekomimi_attack_mode[i][j] = MODE_MOVE;
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						display_handle_10_nekomimi_shot_mode[i][j] = DISPLAY;
					}
					for (int i = 0; i < 4; i++) {	//　０～３
						attack_10_nekomimi_attack_missile_rot[i][j] = 0.0f - 30.0f + 20.0f * i;
						attack_10_nekomimi_attack_speed[i][j] = 0.3f;
					}
					for (int i = 0; i < 3; i++) {	//　４～６
						attack_10_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 15.0f + 15.0f * i;
						attack_10_nekomimi_attack_speed[i + 4][j] = 0.45f;
					}
					for (int i = 0; i < 2; i++) {
						attack_10_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 7.5f + 15.0f * i;	// /2
						attack_10_nekomimi_attack_speed[i + 7][j] = 0.6f;
					}
					attack_10_nekomimi_attack_missile_rot[9][j] = 0.0f;
					attack_10_nekomimi_attack_speed[9][j] = 0.75f;
				}
			}
		}
		attack_10_nekomimi_attack_coordinate.y += 0.5f;
		for (int i = 0; i < ATTACK_10_NUM; i++) {
			attack_10_zako_coordinate[i].y += 0.5f;
		}

		float s = 360.0f / ATTACK_10_NEKOMIMI_NUM;
		for (int i = 0; i < ATTACK_10_NEKOMIMI_MAX; i++) {
			for (int j = 0; j < ATTACK_10_NEKOMIMI_NUM; j++) {
				if (attack_10_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					attack_10_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_10_nekomimi_attack_missile_rot[i][j]) + attack_10_nekomimi_attack_angle + D2R(s * j)) * attack_10_nekomimi_attack_speed[i][j];
					attack_10_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_10_nekomimi_attack_missile_rot[i][j]) + attack_10_nekomimi_attack_angle + D2R(s * j)) * attack_10_nekomimi_attack_speed[i][j];
				}
				if (attack_10_nekomimi_attack_shot_coordinate[i][j].x < 0 || attack_10_nekomimi_attack_shot_coordinate[i][j].x > WINDOW_W || attack_10_nekomimi_attack_shot_coordinate[i][j].y < 0 || attack_10_nekomimi_attack_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_10_nekomimi_shot_mode[i][j] = HIDDEN;
				}
			}
		}
		for (int i = 0; i < ATTACK_10_NUM; i++) {
			for (int j = 0; j < ATTACK_10_MAX; j++) {
				if (attack_10_zako_mode[i] == MODE_MOVE) {
					attack_10_zako_shot_coordinate[i][j].x += cosf(attack_10_angle[i][j]) * 0.8f * (j * 0.1 + 1);
					attack_10_zako_shot_coordinate[i][j].y += sinf(attack_10_angle[i][j]) * 0.8f * (j * 0.1 + 1);
				}
				if (attack_10_zako_shot_coordinate[i][j].x < 0 || attack_10_zako_shot_coordinate[i][j].x > WINDOW_W || attack_10_zako_shot_coordinate[i][j].y < 0 || attack_10_zako_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_10_shot_mode[i][j] = HIDDEN;
				}
			}
			if (attack_10_zako_coordinate[i].x < 0 || attack_10_zako_coordinate[i].x > WINDOW_W || attack_10_zako_coordinate[i].y < 0 || attack_10_zako_coordinate[i].y > WINDOW_H) {
				display_handle_10_mode[i] = HIDDEN;
			}
		}
		if (attack_10_nekomimi_attack_coordinate.x < 0 || attack_10_nekomimi_attack_coordinate.x > WINDOW_W || attack_10_nekomimi_attack_coordinate.y < 0 || attack_10_nekomimi_attack_coordinate.y > WINDOW_H) {
			display_handle_10_nekomimi_mode = HIDDEN;
		}
	}
	//　中央に猫耳、左右に3体ずつ２つの弾	
	if (game_shot[14] == MODE_MOVE) {
		for (int i = 0; i < ATTACK_11_NUM; i++) {
			if (attack_11_zako_mode[i] == MODE_WAIT) {
				display_handle_11_nekomimi_mode = DISPLAY;
				display_handle_11_mode[i] = DISPLAY;
				attack_11_zako_mode[i] = MODE_MOVE;
				attack_11_nekomimi_attack_coordinate.x = (BG_X_HW - BG_X_LW) / 2 + BG_X_LW;
				attack_11_nekomimi_attack_coordinate.y = 120;
				attack_11_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_11_nekomimi_attack_coordinate.y, player_coordinate.x - attack_11_nekomimi_attack_coordinate.x);
				for (int i = 0; i < 3; i++) {
					attack_11_zako_coordinate[i].x = attack_11_nekomimi_attack_coordinate.x - 70 - 40 * i;
					attack_11_zako_coordinate[i].y = 110 - 20 * i;
				}
				for (int i = 3; i < ATTACK_11_NUM; i++) {
					attack_11_zako_coordinate[i].x = attack_11_nekomimi_attack_coordinate.x + 70 + 40 * (i - 3);
					attack_11_zako_coordinate[i].y = 110 - 20 * (i - 3);
				}
				for (int j = 0; j < ATTACK_11_MAX; j++) {
					if (display_handle_11_mode[i] == DISPLAY) {
						attack_11_zako_shot_coordinate[i][j].x = attack_11_zako_coordinate[i].x;
						attack_11_zako_shot_coordinate[i][j].y = attack_11_zako_coordinate[i].y;
						attack_11_angle[i][j] = atan2f(player_coordinate.y - attack_11_zako_shot_coordinate[i][j].y, player_coordinate.x - attack_11_zako_shot_coordinate[i][j].x);
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						display_handle_11_shot_mode[i][j] = DISPLAY;
					}
				}
			}
		}
		for (int j = 0; j < ATTACK_11_NEKOMIMI_NUM; j++) {
			for (int i = 0; i < ATTACK_11_NEKOMIMI_MAX; i++) {
				if (attack_11_nekomimi_attack_mode[i][j] == MODE_WAIT) {
					if (display_handle_10_nekomimi_mode == DISPLAY) {
						attack_11_nekomimi_attack_shot_coordinate[i][j].x = attack_11_nekomimi_attack_coordinate.x;
						attack_11_nekomimi_attack_shot_coordinate[i][j].y = attack_11_nekomimi_attack_coordinate.y;
						attack_11_nekomimi_attack_mode[i][j] = MODE_MOVE;
						PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
						display_handle_11_nekomimi_shot_mode[i][j] = DISPLAY;
					}
					for (int i = 0; i < 4; i++) {	//　０～３
						attack_11_nekomimi_attack_missile_rot[i][j] = 0.0f - 30.0f + 20.0f * i;
						attack_11_nekomimi_attack_speed[i][j] = 0.3f;
					}
					for (int i = 0; i < 3; i++) {	//　４～６
						attack_11_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 15.0f + 15.0f * i;
						attack_11_nekomimi_attack_speed[i + 4][j] = 0.45f;
					}
					for (int i = 0; i < 2; i++) {
						attack_11_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 7.5f + 15.0f * i;	// /2
						attack_11_nekomimi_attack_speed[i + 7][j] = 0.6f;
					}
					attack_11_nekomimi_attack_missile_rot[9][j] = 0.0f;
					attack_11_nekomimi_attack_speed[9][j] = 0.75f;
				}
			}
		}
		attack_11_nekomimi_attack_coordinate.y += 0.5f;
		for (int i = 0; i < ATTACK_11_NUM; i++) {
			attack_11_zako_coordinate[i].y += 0.5f;
		}

		float s = 360.0f / ATTACK_11_NEKOMIMI_NUM;
		for (int i = 0; i < ATTACK_11_NEKOMIMI_MAX; i++) {
			for (int j = 0; j < ATTACK_11_NEKOMIMI_NUM; j++) {
				if (attack_11_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					attack_11_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_11_nekomimi_attack_missile_rot[i][j]) + attack_11_nekomimi_attack_angle + D2R(s * j)) * attack_11_nekomimi_attack_speed[i][j];
					attack_11_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_11_nekomimi_attack_missile_rot[i][j]) + attack_11_nekomimi_attack_angle + D2R(s * j)) * attack_11_nekomimi_attack_speed[i][j];
				}
				if (attack_11_nekomimi_attack_shot_coordinate[i][j].x < 0 || attack_11_nekomimi_attack_shot_coordinate[i][j].x > WINDOW_W || attack_11_nekomimi_attack_shot_coordinate[i][j].y < 0 || attack_11_nekomimi_attack_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_11_nekomimi_shot_mode[i][j] = HIDDEN;
				}
			}
		}
		for (int i = 0; i < ATTACK_11_NUM; i++) {
			for (int j = 0; j < ATTACK_11_MAX; j++) {
				if (attack_11_zako_mode[i] == MODE_MOVE) {
					attack_11_zako_shot_coordinate[i][j].x += cosf(attack_11_angle[i][j]) * 0.8f * (j * 0.1 + 1);
					attack_11_zako_shot_coordinate[i][j].y += sinf(attack_11_angle[i][j]) * 0.8f * (j * 0.1 + 1);
				}
				if (attack_11_zako_shot_coordinate[i][j].x < 0 || attack_11_zako_shot_coordinate[i][j].x > WINDOW_W || attack_11_zako_shot_coordinate[i][j].y < 0 || attack_11_zako_shot_coordinate[i][j].y > WINDOW_H) {
					display_handle_11_shot_mode[i][j] = HIDDEN;
				}
			}
			if (attack_11_zako_coordinate[i].x < 0 || attack_11_zako_coordinate[i].x > WINDOW_W || attack_11_zako_coordinate[i].y < 0 || attack_11_zako_coordinate[i].y > WINDOW_H) {
				display_handle_11_mode[i] = HIDDEN;
			}
		}
		if (attack_11_nekomimi_attack_coordinate.x < 0 || attack_11_nekomimi_attack_coordinate.x > WINDOW_W || attack_11_nekomimi_attack_coordinate.y < 0 || attack_11_nekomimi_attack_coordinate.y > WINDOW_H) {
			display_handle_11_nekomimi_mode = HIDDEN;
		}
	}
	//　雑魚的ラストの攻撃
	if (game_shot[15] == MODE_MOVE) {
		attack_12_coordinate_y = 0.4f;
		attack_12_nekomimi_coordinate.y += attack_12_coordinate_y;

		attack_12_count++;
		if (attack_12_count == 20) {
			attack_12_circle_s = 360.0f / ATTACK_12_NEKOMIMI_NUM;
			attack_12_nekomimi_attack_angle = atan2f(player_coordinate.y - attack_12_nekomimi_coordinate.y, player_coordinate.x - attack_12_nekomimi_coordinate.x);

			for (int j = 0; j < ATTACK_12_NEKOMIMI_NUM; j++) {
				for (int i = 0; i < ATTACK_12_NEKOMIMI_MAX; i++) {
					if (display_handle_12_mode == DISPLAY) {
						if (display_handle_12_nekomimi_shot_mode[i][j] == HIDDEN) {
							attack_12_nekomimi_attack_shot_coordinate[i][j].x = attack_12_nekomimi_coordinate.x;
							attack_12_nekomimi_attack_shot_coordinate[i][j].y = attack_12_nekomimi_coordinate.y;
							attack_12_nekomimi_attack_mode[i][j] = MODE_MOVE;
							PlaySoundMem(se_enemy_attack[2], DX_PLAYTYPE_BACK);
							display_handle_12_nekomimi_shot_mode[i][j] = DISPLAY;
						}
					}
				}
				for (int i = 0; i < 4; i++) {	//　０～３
					attack_12_nekomimi_attack_missile_rot[i][j] = 0.0f - 30.0f + 20.0f * i;
					attack_12_nekomimi_attack_speed[i][j] = 0.3f;
				}
				for (int i = 0; i < 3; i++) {	//　４～６
					attack_12_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 20.0f + 20.0f * i;
					attack_12_nekomimi_attack_speed[i + 4][j] = 0.45f;
				}
				for (int i = 0; i < 2; i++) {
					attack_12_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 10.0f + 20.0f * i;
					attack_12_nekomimi_attack_speed[i + 7][j] = 0.6f;
				}
				attack_12_nekomimi_attack_missile_rot[9][j] = 0.0f;
				attack_12_nekomimi_attack_speed[9][j] = 0.75f;
			}

			for (int i = 0; i < ATTACK_12_SHOT_MAX; i++) {
				if (display_handle_12_mode == DISPLAY) {
					attack_12_circle_mode[i] = MODE_12_PREPARATION;
					PlaySoundMem(se_enemy_attack[2], DX_PLAYTYPE_BACK);
					display_handle_12_shot_mode[i] = DISPLAY;
				}
			}
		}

		for (int i = 0; i < ATTACK_12_NEKOMIMI_MAX; i++) {
			for (int j = 0; j < ATTACK_12_NEKOMIMI_NUM; j++) {
				if (attack_12_nekomimi_attack_mode[i][j] == MODE_MOVE) {
					attack_12_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(attack_12_nekomimi_attack_missile_rot[i][j]) + D2R(attack_12_circle_s * j)) * attack_12_nekomimi_attack_speed[i][j];
					attack_12_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(attack_12_nekomimi_attack_missile_rot[i][j]) + D2R(attack_12_circle_s * j)) * attack_12_nekomimi_attack_speed[i][j];
				}
				if (attack_12_nekomimi_attack_shot_coordinate[i][j].y >= WINDOW_H || attack_12_nekomimi_attack_shot_coordinate[i][j].y <= 0 || attack_12_nekomimi_attack_shot_coordinate[i][j].x >= WINDOW_W || attack_12_nekomimi_attack_shot_coordinate[i][j].x <= 0) {												//　画面より下に行ったら
					display_handle_12_nekomimi_shot_mode[i][j] = HIDDEN;														//　動かないもーどにする
				}
			}
		}

		for (int i = 0; i < ATTACK_12_SHOT_MAX; i++) {														//　i を３回繰り返す												//　j を１００回繰り返す
			if (attack_12_circle_mode[i] == MODE_12_PREPARATION) {									//　モードが false の時
				attack_12_circle_shot[i].x = attack_12_nekomimi_coordinate.x;				//　ｘ座標を敵に合わせる
				attack_12_circle_shot[i].y = attack_12_nekomimi_coordinate.y;				//　ｙ座標を敵に合わせる
				attack_12_circle_rot = ATTACK_12_ROT_DIRECTLY_BELOW - ATTACK_12_SPACE_SIZE + ATTACK_12_SPACE_SIZE * i;														//　角度を決める
				attack_12_circle_target_angle[i] = D2R(attack_12_circle_rot);			//　角度を合わせる
				attack_12_circle_count[i] = 0;
				attack_12_circle_mode[i] = MODE_12_SPREAD;										//　モードを true にする
			}
			else if (attack_12_circle_mode[i] == MODE_12_SPREAD) {														//　動く状態なら
				attack_12_circle_shot[i].x += cosf(attack_12_circle_target_angle[i]) * ATTACK_12_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｘ軸移動
				attack_12_circle_shot[i].y += sinf(attack_12_circle_target_angle[i]) * ATTACK_12_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｙ軸移動
				attack_12_circle_count[i]++;
				if (attack_12_circle_count[i] >= 120) {
					attack_12_circle_mode[i] = MODE_12_FACE;
					attack_12_circle_target_angle[i] = atan2(attack_12_nekomimi_coordinate.y + 200 - attack_12_circle_shot[i].y, attack_12_nekomimi_coordinate.x - attack_12_circle_shot[i].x);
				}
			}
			else if (attack_12_circle_mode[i] == MODE_12_FACE) {														//　動く状態なら
				attack_12_circle_shot[i].x += cosf(attack_12_circle_target_angle[i]) * 1.8f;	//　ENEMY_RED_SPEED の速さでｘ軸移動
				attack_12_circle_shot[i].y += sinf(attack_12_circle_target_angle[i]) * 1.8f;	//　ENEMY_RED_SPEED の速さでｙ軸移動
			}
			if (attack_12_circle_shot[i].y >= WINDOW_H || attack_12_circle_shot[i].y <= 0 || attack_12_circle_shot[i].x >= WINDOW_W || attack_12_circle_shot[i].x <= 0) {												//　画面より下に行ったら
				display_handle_12_shot_mode[i] = HIDDEN;														//　動かないもーどにする
			}
		}
	}


	// =====================================================
	//	ボスタイマー
	// =====================================================
	if (frame_count <= ATTACK_BOSS_TIMING - 100) {
		boss_mode = MODE_WAIT;
	}
	else if (frame_count == ATTACK_BOSS_TIMING) {
		boss_mode = MODE_MOVE;
		boss.y = -20;
		w_count = 0;
		for (int i = 0; i < ATTACK_11_NUM; i++) {
			display_handle_11_mode[i] = HIDDEN;
			for (int j = 0; j < ATTACK_11_MAX; j++) {
				display_handle_11_shot_mode[i][j] = HIDDEN;
			}
		}
		display_handle_11_nekomimi_mode = HIDDEN;
		for (int i = 0; i < ATTACK_11_NEKOMIMI_MAX; i++) {
			for (int j = 0; j < ATTACK_11_NEKOMIMI_NUM; j++) {
				display_handle_11_nekomimi_shot_mode[i][j] = HIDDEN;
			}
		}
		for (int i = 0; i < ATTACK_12_SHOT_MAX; i++) {
			display_handle_12_shot_mode[i] = HIDDEN;
		}
		display_handle_12_mode = HIDDEN;
		for (int i = 0; i < ATTACK_12_NEKOMIMI_MAX; i++) {
			for (int j = 0; j < ATTACK_12_NEKOMIMI_NUM; j++) {
				display_handle_12_nekomimi_shot_mode[i][j] = HIDDEN;
			}
		}
		//boss.x = (BG_X_HW - BG_X_LW) / 2 + BG_X_LW;
		//boss.y = 120;
		//game_shot[11] = MODE_WAIT;
		//game_shot[12] = MODE_WAIT;
		//game_shot[12] = MODE_WAIT;
	}

	if (w_count >= 20) {
		w_count = 0;
		if (w_alpha == DISPLAY) {
			w_alpha = HIDDEN;
		}
		else {
			w_alpha = DISPLAY;
		}
	}

	// =====================================================
	//	ボス
	// =====================================================
	if (boss_mode == MODE_MOVE) {
		// =====================================================
//　カウント（攻撃に入るモード用）
//	if (boss_attack_mode != Attack_Off) {
//		boss_attack_count++;
//	}
	//　カウントして攻撃のモード
//	if (boss_attack_count == BOSS_ATTACK_TIMING_1) boss_attack_mode = Attack_Mode_1;
//	if (boss_attack_count == BOSS_ATTACK_TIMING_2) boss_attack_mode = Attack_Mode_2;
//	if (boss_attack_count == BOSS_ATTACK_TIMING_3) boss_attack_mode = Attack_Mode_3;

		if (boss_stage_now == none) {
			boss.x = (BG_X_HW - BG_X_LW) / 2 + BG_X_LW;
			if (boss.y <= 120) {
				boss.y += 0.8f;
			}
			w_count++;
			game_shot[7] = MODE_WAIT;
			game_shot[8] = MODE_WAIT;
			game_shot[9] = MODE_WAIT;
			game_shot[10] = MODE_WAIT;
			game_shot[11] = MODE_WAIT;
			game_shot[12] = MODE_WAIT;
			game_shot[12] = MODE_WAIT;

			boss_attack_count++;
			if (boss.y >= 120) {
			//if (boss_attack_count >= BOSS_ATTACK_NONE) {
				boss_hp = BOSS_MAX_HP1;
				boss_stage_now = first;
				boss_attack_count = 0;
				for (int i = 0; i < BOSS_RAND_NUM1; i++) {
					boss_rand_shot_1[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
					boss_rand_shot_1[i].y = GetRand(2400) * -1;
					boss_rand_speed_1[i] = 2.0f;
					display_handle_snow_1_shot_mode[i] = DISPLAY;
				}
				for (int i = 0; i < BOSS_RAND_NUM2; i++) {
					boss_rand_shot_2[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
					boss_rand_shot_2[i].y = GetRand(2400) * -2;
					boss_rand_speed_2[i] = 2.0f;
					display_handle_snow_2_shot_mode[i] = DISPLAY;
				}
				for (int i = 0; i < BOSS_RAND_NUM3; i++) {
					boss_rand_shot_3[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
					boss_rand_shot_3[i].y = GetRand(3400) * -3;
					boss_rand_speed_3[i] = 3.0f;
					display_handle_snow_3_shot_mode[i] = DISPLAY;
				}
			}

			boss_attack_1_count = 0;
			boss_big_left_1_shot_count = 0;
			boss_big_left_1_shot_num = 0;
			for (int j = 0; j < BOSS_BIG_LEFT_1_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_BIG_LEFT_1_SHOT_NUM; i++) {
					boss_big_left_1_shot_mode[j][i] = MODE_WAIT;
				}
			}
			boss_small_left_1_shot_count = 0;
			boss_small_left_1_shot_num = 0;
			for (int j = 0; j < BOSS_SMALL_LEFT_1_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_SMALL_LEFT_1_SHOT_NUM; i++) {
					boss_small_left_1_shot_mode[j][i] = MODE_WAIT;
					display_handle_boss_shot_mode_small[j][i][0] = HIDDEN;
				}
			}
			boss_big_right_1_shot_count = 0;
			boss_big_right_1_shot_num = 0;
			for (int j = 0; j < BOSS_BIG_RIGHT_1_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_BIG_RIGHT_1_SHOT_NUM; i++) {
					boss_big_right_1_shot_mode[j][i] = MODE_WAIT;
				}
			}
			boss_small_right_1_shot_count = 0;
			boss_small_right_1_shot_num = 0;
			for (int j = 0; j < BOSS_SMALL_RIGHT_1_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_SMALL_RIGHT_1_SHOT_NUM; i++) {
					boss_small_right_1_shot_mode[j][i] = MODE_WAIT;
					display_handle_boss_shot_mode_small[j][i][1] = HIDDEN;
				}
			}
			boss_big_left_2_shot_count = 0;
			boss_big_left_2_shot_num = 0;
			for (int j = 0; j < BOSS_BIG_LEFT_2_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_BIG_LEFT_2_SHOT_NUM; i++) {
					boss_big_left_2_shot_mode[j][i] = MODE_WAIT;
				}
			}
			boss_small_left_2_shot_count = 0;
			boss_small_left_2_shot_num = 0;
			for (int j = 0; j < BOSS_SMALL_LEFT_2_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_SMALL_LEFT_2_SHOT_NUM; i++) {
					boss_small_left_2_shot_mode[j][i] = MODE_WAIT;
					display_handle_boss_shot_mode_small[j][i][2] = HIDDEN;
				}
			}
			boss_big_right_2_shot_count = 0;
			boss_big_right_2_shot_num = 0;
			for (int j = 0; j < BOSS_BIG_RIGHT_2_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_BIG_RIGHT_2_SHOT_NUM; i++) {
					boss_big_right_2_shot_mode[j][i] = MODE_WAIT;
				}
			}
			boss_small_right_2_shot_count = 0;
			boss_small_right_2_shot_num = 0;
			for (int j = 0; j < BOSS_SMALL_RIGHT_2_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_SMALL_RIGHT_2_SHOT_NUM; i++) {
					boss_small_right_2_shot_mode[j][i] = MODE_WAIT;
					display_handle_boss_shot_mode_small[j][i][3] = HIDDEN;
				}
			}
			boss_big_left_3_shot_count = 0;
			boss_big_left_3_shot_num = 0;
			for (int j = 0; j < BOSS_BIG_LEFT_3_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_BIG_LEFT_3_SHOT_NUM; i++) {
					boss_big_left_3_shot_mode[j][i] = MODE_WAIT;
				}
			}
			boss_small_left_3_shot_count = 0;
			boss_small_left_3_shot_num = 0;
			for (int j = 0; j < BOSS_SMALL_LEFT_3_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_SMALL_LEFT_3_SHOT_NUM; i++) {
					boss_small_left_3_shot_mode[j][i] = MODE_WAIT;
					display_handle_boss_shot_mode_small[j][i][4] = HIDDEN;
				}
			}
			boss_big_right_3_shot_count = 0;
			boss_big_right_3_shot_num = 0;
			for (int j = 0; j < BOSS_BIG_RIGHT_3_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_BIG_RIGHT_3_SHOT_NUM; i++) {
					boss_big_right_3_shot_mode[j][i] = MODE_WAIT;
				}
			}
			boss_small_right_3_shot_count = 0;
			boss_small_right_3_shot_num = 0;
			for (int j = 0; j < BOSS_SMALL_RIGHT_3_SHOT_MAX; j++) {
				for (int i = 0; i < BOSS_SMALL_RIGHT_3_SHOT_NUM; i++) {
					boss_small_right_3_shot_mode[j][i] = MODE_WAIT;
					display_handle_boss_shot_mode_small[j][i][5] = HIDDEN;
				}
			}
			boss_furan_red_circle_count = 0;
			boss_furan_blue_circle_count = 0;
			boss_furan_purple_circle_count = 0;
		}
		if (boss_stage_now == first) {
			boss_attack_count++;
			if (boss_attack_count >= BOSS_ATTACK_TIMING_1) {
				boss_hp = BOSS_MAX_HP2;
				boss_stage_now = second;
				boss_attack_count = 0;
				boss_rotate_coordinate[0][0].x = BG_X_HW - 10;
				boss_rotate_coordinate[0][0].y = BG_Y_HH; //120;;
				boss_rotate_mode[0][0] = RIGHT;

				boss_rotate_coordinate[0][1].x = BG_X_LW + 10;
				boss_rotate_coordinate[0][1].y = BG_Y_HH; //120;;
				boss_rotate_mode[0][1] = LEFT;

				boss_rotate_coordinate[1][0].x = BG_X_LW + 10;
				boss_rotate_coordinate[1][0].y = BG_Y_LH; //120;;
				boss_rotate_mode[1][0] = LEFT;

				boss_rotate_coordinate[1][1].x = BG_X_HW - 10;
				boss_rotate_coordinate[1][1].y = BG_Y_LH; //120;;
				boss_rotate_mode[1][1] = RIGHT;

				for (int x = 0; x < BOSS_RAND_NUM1; x++) {
					display_handle_snow_1_shot_mode[x] = HIDDEN;
				}
				for (int x = 0; x < BOSS_RAND_NUM2; x++) {
					display_handle_snow_2_shot_mode[x] = HIDDEN;
				}
				for (int x = 0; x < BOSS_RAND_NUM3; x++) {
					display_handle_snow_3_shot_mode[x] = HIDDEN;
				}

				for (int i = 0; i < BOSS_ROTATE_SHOT_MAX; i++) {
					for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
						for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
							boss_rotate_shot_mode[i][p][t] = MODE_WAIT;
						}
					}
				}
				for (int j = 0; j < BOSS_NEKOMIMI_NUM; j++) {
					for (int i = 0; i < BOSS_NEKOMIMI_MAX; i++) {
						boss_nekomimi_attack_shot_coordinate[i][j].x = boss.x;
						boss_nekomimi_attack_shot_coordinate[i][j].y = boss.y;
						boss_nekomimi_attack_mode[i][j] = MODE_MOVE;
					}
					for (int i = 0; i < 4; i++) {	//　０～３
						boss_nekomimi_attack_missile_rot[i][j] = 0.0f - 30.0f + 20.0f * i;
						boss_nekomimi_attack_speed[i][j] = 0.3f;
					}
					for (int i = 0; i < 3; i++) {	//　４～６
						boss_nekomimi_attack_missile_rot[i + 4][j] = 0.0f - 20.0f + 20.0f * i;
						boss_nekomimi_attack_speed[i + 4][j] = 0.45f;
					}
					for (int i = 0; i < 2; i++) {
						boss_nekomimi_attack_missile_rot[i + 7][j] = 0.0f - 10.0f + 20.0f * i;
						boss_nekomimi_attack_speed[i + 7][j] = 0.6f;
					}
					boss_nekomimi_attack_missile_rot[9][j] = 0.0f;
					boss_nekomimi_attack_speed[9][j] = 0.75f;
				}
				for (int j = 0; j < BOSS_SMALL_SHOT_MAX; j++) {
					boss_small_shot_mode[j] = MODE_MOVE;
				}
				for (int j = 0; j < BOSS_SMALL_AMAX; j++) {
					boss_small_mode[j] = MODE_MOVE;
				}
			}
		}
		if (boss_stage_now == second) {
			game_shot[13] = MODE_WAIT;
			game_shot[14] = MODE_WAIT;
			game_shot[15] = MODE_WAIT;
			boss_attack_count++;
			if (boss_attack_count >= BOSS_ATTACK_TIMING_2) {
				boss_hp = BOSS_MAX_HP3;
				boss_stage_now = third;
				boss_attack_count = 0;
			}
		}
		if (boss_stage_now == third) {
			boss_attack_count++;
			if (boss_attack_count >= BOSS_ATTACK_TIMING_4) {
				boss_attack_count = 0;
			//	boss_stage_now = 10;
				game_start_mode = Game_Clear;
			}
		}

		//　攻撃モード
		/*if (boss_attack_mode == Attack_Mode_1) {
			if (attack_mode_1 == MODE_WAIT) {
				for (int i = 0; i < RAND_NUM1; i++) {
					rand_shot_1[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
					rand_shot_1[i].y = GetRand(2400) * -1;
					rand_speed_1[i] = 2.0f;
				}
				for (int i = 0; i < RAND_NUM2; i++) {
					rand_shot_2[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
					rand_shot_2[i].y = GetRand(2400) * -2;
					rand_speed_2[i] = 2.0f;
				}
				for (int i = 0; i < RAND_NUM3; i++) {
					rand_shot_3[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
					rand_shot_3[i].y = GetRand(3400) * -3;
					rand_speed_3[i] = 3.0f;
				}
			}
			attack_mode_1 = MODE_MOVE;
		}
		if (boss_attack_mode == Attack_Mode_2) {
			attack_mode_2 = MODE_MOVE;
			attack_mode_1 = MODE_WAIT;
		}
		if (boss_attack_mode == Attack_Mode_3) {
			attack_mode_3 = MODE_MOVE;
		}*/

		//　デバック用
		//if (CheckHitKey(KEY_INPUT_SPACE)) {
		//	boss_attack_mode = Attack_Count;
		//}

		// =====================================================


		// =====================================================
		//　ステージ１
		if (boss_stage_now == first) {
			//　左右のやつ　
			boss_attack_1_count++;
			if (boss_attack_1_count >= BOSS_C1) {
				boss_big_left_1_shot_count++;
				if (boss_big_left_1_shot_count >= BOSS_BIG_LEFT_1_SHOT_TIMING) {
					boss_big_left_1_shot_count = 0;
					for (int j = 0; j < BOSS_BIG_LEFT_1_SHOT_MAX; j++) {
						if (boss_big_left_1_shot_mode[j][boss_big_left_1_shot_num] == MODE_WAIT) {
							boss_big_left_1_shot_shot[j][boss_big_left_1_shot_num].x = boss.x;
							boss_big_left_1_shot_shot[j][boss_big_left_1_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_big[j][boss_big_left_1_shot_num][0] = DISPLAY;
							boss_big_left_1_shot_mode[j][boss_big_left_1_shot_num] = MODE_MOVE;
						}
					}
					boss_big_left_1_shot_num++;
					if (boss_big_left_1_shot_num >= BOSS_BIG_LEFT_1_SHOT_NUM) {
						boss_big_left_1_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_BIG_LEFT_1_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_BIG_LEFT_1_SHOT_NUM; i++) {
						if (boss_big_left_1_shot_mode[j][i] == MODE_MOVE) {
							boss_big_left_1_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_big_left_1_shot_r) + D2R(i * 15)) * BOSS_BIG_LEFT_1_SHOT_SPEED;
							boss_big_left_1_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_big_left_1_shot_r) + D2R(i * 15)) * BOSS_BIG_LEFT_1_SHOT_SPEED;
						}
					}
				}
				boss_small_left_1_shot_count++;
				if (boss_small_left_1_shot_count >= BOSS_SMALL_LEFT_1_SHOT_TIMING) {
					boss_small_left_1_shot_count = 0;
					for (int j = 0; j < BOSS_SMALL_LEFT_1_SHOT_MAX; j++) {
						if (boss_small_left_1_shot_mode[j][boss_small_left_1_shot_num] == MODE_WAIT) {
							boss_small_left_1_shot_shot[j][boss_small_left_1_shot_num].x = boss.x;
							boss_small_left_1_shot_shot[j][boss_small_left_1_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_small[j][boss_small_left_1_shot_num][0] = DISPLAY;
							boss_small_left_1_shot_mode[j][boss_small_left_1_shot_num] = MODE_MOVE;
						}
					}
					boss_small_left_1_shot_num++;
					if (boss_small_left_1_shot_num >= BOSS_SMALL_LEFT_1_SHOT_NUM) {
						boss_small_left_1_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_SMALL_LEFT_1_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_SMALL_LEFT_1_SHOT_NUM; i++) {
						if (boss_small_left_1_shot_mode[j][i] == MODE_MOVE) {
							boss_small_left_1_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_small_left_1_shot_r) + D2R(i * 17)) * BOSS_SMALL_LEFT_1_SHOT_SPEED;
							boss_small_left_1_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_small_left_1_shot_r) + D2R(i * 17)) * BOSS_SMALL_LEFT_1_SHOT_SPEED;
						}
					}
				}
			}
			if (boss_attack_1_count >= BOSS_C2) {
				boss_big_right_1_shot_count++;
				if (boss_big_right_1_shot_count >= BOSS_BIG_RIGHT_1_SHOT_TIMING) {
					boss_big_right_1_shot_count = 0;
					for (int j = 0; j < BOSS_BIG_RIGHT_1_SHOT_MAX; j++) {
						if (boss_big_right_1_shot_mode[j][boss_big_right_1_shot_num] == MODE_WAIT) {
							boss_big_right_1_shot_shot[j][boss_big_right_1_shot_num].x = boss.x;
							boss_big_right_1_shot_shot[j][boss_big_right_1_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_big[j][boss_big_right_1_shot_num][1] = DISPLAY;
							boss_big_right_1_shot_mode[j][boss_big_right_1_shot_num] = MODE_MOVE;
						}
					}
					boss_big_right_1_shot_num++;
					if (boss_big_right_1_shot_num >= BOSS_BIG_RIGHT_1_SHOT_NUM) {
						boss_big_right_1_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_BIG_RIGHT_1_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_BIG_RIGHT_1_SHOT_NUM; i++) {
						if (boss_big_right_1_shot_mode[j][i] == MODE_MOVE) {
							boss_big_right_1_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_big_right_1_shot_r) + D2R(-i * 15)) * BOSS_BIG_RIGHT_1_SHOT_SPEED;
							boss_big_right_1_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_big_right_1_shot_r) + D2R(-i * 15)) * BOSS_BIG_RIGHT_1_SHOT_SPEED;
						}
					}
				}
				boss_small_right_1_shot_count++;
				if (boss_small_right_1_shot_count >= BOSS_SMALL_RIGHT_1_SHOT_TIMING) {
					boss_small_right_1_shot_count = 0;
					for (int j = 0; j < BOSS_SMALL_RIGHT_1_SHOT_MAX; j++) {
						if (boss_small_right_1_shot_mode[j][boss_small_right_1_shot_num] == MODE_WAIT) {
							boss_small_right_1_shot_shot[j][boss_small_right_1_shot_num].x = boss.x;
							boss_small_right_1_shot_shot[j][boss_small_right_1_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_small[j][boss_small_right_1_shot_num][1] = DISPLAY;
							boss_small_right_1_shot_mode[j][boss_small_right_1_shot_num] = MODE_MOVE;
						}
					}
					boss_small_right_1_shot_num++;
					if (boss_small_right_1_shot_num >= BOSS_SMALL_RIGHT_1_SHOT_NUM) {
						boss_small_right_1_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_SMALL_RIGHT_1_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_SMALL_RIGHT_1_SHOT_NUM; i++) {
						if (boss_small_right_1_shot_mode[j][i] == MODE_MOVE) {
							boss_small_right_1_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_small_right_1_shot_r) + D2R(-i * 17)) * BOSS_SMALL_RIGHT_1_SHOT_SPEED;
							boss_small_right_1_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_small_right_1_shot_r) + D2R(-i * 17)) * BOSS_SMALL_RIGHT_1_SHOT_SPEED;
						}
					}
				}
			}
			if (boss_attack_1_count >= BOSS_C3) {
				boss_big_left_2_shot_count++;
				if (boss_big_left_2_shot_count >= BOSS_BIG_LEFT_2_SHOT_TIMING) {
					boss_big_left_2_shot_count = 0;
					for (int j = 0; j < BOSS_BIG_LEFT_2_SHOT_MAX; j++) {
						if (boss_big_left_2_shot_mode[j][boss_big_left_2_shot_num] == MODE_WAIT) {
							boss_big_left_2_shot_shot[j][boss_big_left_2_shot_num].x = boss.x;
							boss_big_left_2_shot_shot[j][boss_big_left_2_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_big[j][boss_big_left_2_shot_num][2] = DISPLAY;
							boss_big_left_2_shot_mode[j][boss_big_left_2_shot_num] = MODE_MOVE;
						}
					}
					boss_big_left_2_shot_num++;
					if (boss_big_left_2_shot_num >= BOSS_BIG_LEFT_2_SHOT_NUM) {
						boss_big_left_2_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_BIG_LEFT_2_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_BIG_LEFT_2_SHOT_NUM; i++) {
						if (boss_big_left_2_shot_mode[j][i] == MODE_MOVE) {
							boss_big_left_2_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_big_left_2_shot_r) + D2R(i * 15)) * BOSS_BIG_LEFT_2_SHOT_SPEED;
							boss_big_left_2_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_big_left_2_shot_r) + D2R(i * 15)) * BOSS_BIG_LEFT_2_SHOT_SPEED;
						}
					}
				}
				boss_small_left_2_shot_count++;
				if (boss_small_left_2_shot_count >= BOSS_SMALL_LEFT_2_SHOT_TIMING) {
					boss_small_left_2_shot_count = 0;
					for (int j = 0; j < BOSS_SMALL_LEFT_2_SHOT_MAX; j++) {
						if (boss_small_left_2_shot_mode[j][boss_small_left_2_shot_num] == MODE_WAIT) {
							boss_small_left_2_shot_shot[j][boss_small_left_2_shot_num].x = boss.x;
							boss_small_left_2_shot_shot[j][boss_small_left_2_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_small[j][boss_small_left_2_shot_num][2] = DISPLAY;
							boss_small_left_2_shot_mode[j][boss_small_left_2_shot_num] = MODE_MOVE;
						}
					}
					boss_small_left_2_shot_num++;
					if (boss_small_left_2_shot_num >= BOSS_SMALL_LEFT_2_SHOT_NUM) {
						boss_small_left_2_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_SMALL_LEFT_2_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_SMALL_LEFT_2_SHOT_NUM; i++) {
						if (boss_small_left_2_shot_mode[j][i] == MODE_MOVE) {
							boss_small_left_2_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_small_left_2_shot_r) + D2R(i * 17)) * BOSS_SMALL_LEFT_2_SHOT_SPEED;
							boss_small_left_2_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_small_left_2_shot_r) + D2R(i * 17)) * BOSS_SMALL_LEFT_2_SHOT_SPEED;
						}
					}
				}
			}
			if (boss_attack_1_count >= BOSS_C4) {
				boss_big_right_2_shot_count++;
				if (boss_big_right_2_shot_count >= BOSS_BIG_RIGHT_2_SHOT_TIMING) {
					boss_big_right_2_shot_count = 0;
					for (int j = 0; j < BOSS_BIG_RIGHT_2_SHOT_MAX; j++) {
						if (boss_big_right_2_shot_mode[j][boss_big_right_2_shot_num] == MODE_WAIT) {
							boss_big_right_2_shot_shot[j][boss_big_right_2_shot_num].x = boss.x;
							boss_big_right_2_shot_shot[j][boss_big_right_2_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_big[j][boss_big_right_2_shot_num][3] = DISPLAY;
							boss_big_right_2_shot_mode[j][boss_big_right_2_shot_num] = MODE_MOVE;
						}
					}
					boss_big_right_2_shot_num++;
					if (boss_big_right_2_shot_num >= BOSS_BIG_RIGHT_2_SHOT_NUM) {
						boss_big_right_2_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_BIG_RIGHT_2_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_BIG_RIGHT_2_SHOT_NUM; i++) {
						if (boss_big_right_2_shot_mode[j][i] == MODE_MOVE) {
							boss_big_right_2_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_big_right_2_shot_r) + D2R(-i * 15)) * BOSS_BIG_RIGHT_2_SHOT_SPEED;
							boss_big_right_2_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_big_right_2_shot_r) + D2R(-i * 15)) * BOSS_BIG_RIGHT_2_SHOT_SPEED;
						}
					}
				}
				boss_small_right_2_shot_count++;
				if (boss_small_right_2_shot_count >= BOSS_SMALL_RIGHT_2_SHOT_TIMING) {
					boss_small_right_2_shot_count = 0;
					for (int j = 0; j < BOSS_SMALL_RIGHT_2_SHOT_MAX; j++) {
						if (boss_small_right_2_shot_mode[j][boss_small_right_2_shot_num] == MODE_WAIT) {
							boss_small_right_2_shot_shot[j][boss_small_right_2_shot_num].x = boss.x;
							boss_small_right_2_shot_shot[j][boss_small_right_2_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_small[j][boss_small_right_2_shot_num][3] = DISPLAY;
							boss_small_right_2_shot_mode[j][boss_small_right_2_shot_num] = MODE_MOVE;
						}
					}
					boss_small_right_2_shot_num++;
					if (boss_small_right_2_shot_num >= BOSS_SMALL_RIGHT_2_SHOT_NUM) {
						boss_small_right_2_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_SMALL_RIGHT_2_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_SMALL_RIGHT_2_SHOT_NUM; i++) {
						if (boss_small_right_2_shot_mode[j][i] == MODE_MOVE) {
							boss_small_right_2_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_small_right_2_shot_r) + D2R(-i * 17)) * BOSS_SMALL_RIGHT_2_SHOT_SPEED;
							boss_small_right_2_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_small_right_2_shot_r) + D2R(-i * 17)) * BOSS_SMALL_RIGHT_2_SHOT_SPEED;
						}
					}
				}
			}
			if (boss_attack_1_count >= BOSS_C5) {
				boss_big_left_3_shot_count++;
				if (boss_big_left_3_shot_count >= BOSS_BIG_LEFT_3_SHOT_TIMING) {
					boss_big_left_3_shot_count = 0;
					for (int j = 0; j < BOSS_BIG_LEFT_3_SHOT_MAX; j++) {
						if (boss_big_left_3_shot_mode[j][boss_big_left_3_shot_num] == MODE_WAIT) {
							boss_big_left_3_shot_shot[j][boss_big_left_3_shot_num].x = boss.x;
							boss_big_left_3_shot_shot[j][boss_big_left_3_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_big[j][boss_big_left_3_shot_num][4] = DISPLAY;
							boss_big_left_3_shot_mode[j][boss_big_left_3_shot_num] = MODE_MOVE;
						}
					}
					boss_big_left_3_shot_num++;
					if (boss_big_left_3_shot_num >= BOSS_BIG_LEFT_3_SHOT_NUM) {
						boss_big_left_3_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_BIG_LEFT_3_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_BIG_LEFT_3_SHOT_NUM; i++) {
						if (boss_big_left_3_shot_mode[j][i] == MODE_MOVE) {
							boss_big_left_3_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_big_left_3_shot_r) + D2R(i * 15)) * BOSS_BIG_LEFT_3_SHOT_SPEED;
							boss_big_left_3_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_big_left_3_shot_r) + D2R(i * 15)) * BOSS_BIG_LEFT_3_SHOT_SPEED;
						}
					}
				}
				boss_small_left_3_shot_count++;
				if (boss_small_left_3_shot_count >= BOSS_SMALL_LEFT_3_SHOT_TIMING) {
					boss_small_left_3_shot_count = 0;
					for (int j = 0; j < BOSS_SMALL_LEFT_3_SHOT_MAX; j++) {
						if (boss_small_left_3_shot_mode[j][boss_small_left_3_shot_num] == MODE_WAIT) {
							boss_small_left_3_shot_shot[j][boss_small_left_3_shot_num].x = boss.x;
							boss_small_left_3_shot_shot[j][boss_small_left_3_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_small[j][boss_small_left_3_shot_num][4] = DISPLAY;
							boss_small_left_3_shot_mode[j][boss_small_left_3_shot_num] = MODE_MOVE;
						}
					}
					boss_small_left_3_shot_num++;
					if (boss_small_left_3_shot_num >= BOSS_SMALL_LEFT_3_SHOT_NUM) {
						boss_small_left_3_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_SMALL_LEFT_3_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_SMALL_LEFT_3_SHOT_NUM; i++) {
						if (boss_small_left_3_shot_mode[j][i] == MODE_MOVE) {
							boss_small_left_3_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_small_left_3_shot_r) + D2R(i * 17)) * BOSS_SMALL_LEFT_3_SHOT_SPEED;
							boss_small_left_3_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_small_left_3_shot_r) + D2R(i * 17)) * BOSS_SMALL_LEFT_3_SHOT_SPEED;
						}
					}
				}
			}
			if (boss_attack_1_count >= BOSS_C6) {
				boss_big_right_3_shot_count++;
				if (boss_big_right_3_shot_count >= BOSS_BIG_RIGHT_3_SHOT_TIMING) {
					boss_big_right_3_shot_count = 0;
					for (int j = 0; j < BOSS_BIG_RIGHT_3_SHOT_MAX; j++) {
						if (boss_big_right_3_shot_mode[j][boss_big_right_3_shot_num] == MODE_WAIT) {
							boss_big_right_3_shot_shot[j][boss_big_right_3_shot_num].x = boss.x;
							boss_big_right_3_shot_shot[j][boss_big_right_3_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_big[j][boss_big_right_3_shot_num][5] = DISPLAY;
							boss_big_right_3_shot_mode[j][boss_big_right_3_shot_num] = MODE_MOVE;
						}
					}
					boss_big_right_3_shot_num++;
					if (boss_big_right_3_shot_num >= BOSS_BIG_RIGHT_3_SHOT_NUM) {
						boss_big_right_3_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_BIG_RIGHT_3_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_BIG_RIGHT_3_SHOT_NUM; i++) {
						if (boss_big_right_3_shot_mode[j][i] == MODE_MOVE) {
							boss_big_right_3_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_big_right_3_shot_r) + D2R(-i * 15)) * BOSS_BIG_RIGHT_3_SHOT_SPEED;
							boss_big_right_3_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_big_right_3_shot_r) + D2R(-i * 15)) * BOSS_BIG_RIGHT_3_SHOT_SPEED;
						}
					}
				}
				boss_small_right_3_shot_count++;
				if (boss_small_right_3_shot_count >= BOSS_SMALL_RIGHT_3_SHOT_TIMING) {
					boss_small_right_3_shot_count = 0;
					for (int j = 0; j < BOSS_SMALL_RIGHT_3_SHOT_MAX; j++) {
						if (boss_small_right_3_shot_mode[j][boss_small_right_3_shot_num] == MODE_WAIT) {
							boss_small_right_3_shot_shot[j][boss_small_right_3_shot_num].x = boss.x;
							boss_small_right_3_shot_shot[j][boss_small_right_3_shot_num].y = boss.y;
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_boss_shot_mode_small[j][boss_small_right_3_shot_num][5] = DISPLAY;
							boss_small_right_3_shot_mode[j][boss_small_right_3_shot_num] = MODE_MOVE;
						}
					}
					boss_small_right_3_shot_num++;
					if (boss_small_right_3_shot_num >= BOSS_SMALL_RIGHT_3_SHOT_NUM) {
						boss_small_right_3_shot_num = 0;
					}
				}
				for (int j = 0; j < BOSS_SMALL_RIGHT_3_SHOT_MAX; j++) {
					for (int i = 0; i < BOSS_SMALL_RIGHT_3_SHOT_NUM; i++) {
						if (boss_small_right_3_shot_mode[j][i] == MODE_MOVE) {
							boss_small_right_3_shot_shot[j][i].x += cosf(D2R(90) + D2R(j * boss_small_right_3_shot_r) + D2R(-i * 17)) * BOSS_SMALL_RIGHT_3_SHOT_SPEED;
							boss_small_right_3_shot_shot[j][i].y += sinf(D2R(90) + D2R(j * boss_small_right_3_shot_r) + D2R(-i * 17)) * BOSS_SMALL_RIGHT_3_SHOT_SPEED;
						}
					}
				}
			}
			//　雪
			for (int i = 0; i < BOSS_RAND_NUM1; i++) {
				if (boss_rand_speed_1[i] >= 0.8 && boss_rand_shot_1[i].y > 0) {
					boss_rand_speed_1[i] -= 0.01;
				}
				boss_rand_shot_1[i].y += boss_rand_speed_1[i];

				if (boss_rand_shot_1[i].y >= WINDOW_H) {
					if (boss_attack_count <= BOSS_ATTACK_TIMING_2) {
						boss_rand_shot_1[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
						boss_rand_shot_1[i].y = GetRand(1200) * -1;
						boss_rand_speed_1[i] = 2.0f;
						display_handle_snow_1_shot_mode[i] = DISPLAY;
					}
				}
				if (boss_attack_count >= BOSS_ATTACK_TIMING_2) {
					if (boss_rand_shot_1[i].y >= 0) {
						boss_rand_shot_1[i].y = WINDOW_H;
					}
				}
			}
			for (int i = 0; i < BOSS_RAND_NUM2; i++) {
				if (boss_rand_speed_2[i] >= 0.6 && boss_rand_shot_2[i].y > 0) {
					boss_rand_speed_2[i] -= 0.03;
				}
				boss_rand_shot_2[i].y += boss_rand_speed_2[i];

				if (boss_rand_shot_2[i].y >= WINDOW_H) {
					if (boss_attack_count <= BOSS_ATTACK_TIMING_2) {
						boss_rand_shot_2[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
						boss_rand_shot_2[i].y = GetRand(2200) * -2;
						boss_rand_speed_2[i] = 2.0f;
						display_handle_snow_2_shot_mode[i] = DISPLAY;
					}
				}
				if (boss_attack_count >= BOSS_ATTACK_TIMING_2) {
					if (boss_rand_shot_2[i].y >= 0) {
						boss_rand_shot_2[i].y = WINDOW_H;
					}
				}
			}
			for (int i = 0; i < BOSS_RAND_NUM3; i++) {
				if (boss_rand_speed_3[i] >= 0.5 && boss_rand_shot_3[i].y > 0) {
					boss_rand_speed_3[i] -= 0.03;
				}
				boss_rand_shot_3[i].y += boss_rand_speed_3[i];

				if (boss_rand_shot_3[i].y >= WINDOW_H) {
					if (boss_attack_count <= BOSS_ATTACK_TIMING_2) {
						boss_rand_shot_3[i].x = GetRand(BG_X_HW - BG_X_LW) + BG_X_LW;
						boss_rand_shot_3[i].y = GetRand(3300) * -3;
						boss_rand_speed_3[i] = 3.0f;
						display_handle_snow_3_shot_mode[i] = DISPLAY;
					}
				}
				if (boss_attack_count >= BOSS_ATTACK_TIMING_2) {
					if (boss_rand_shot_3[i].y >= 0) {
						boss_rand_shot_3[i].y = WINDOW_H;
					}
				}

			}
		}
		// =====================================================

		// =====================================================
		//　ステージ２
		if (boss_stage_now == second) {
			//　回転の調整
			for (int i = 0; i < BOSS_ROTATE_NUM; i++) {
				if (boss_rotate_mode[i][0] == TOP) {
					if (boss_rotate_coordinate[i][0].x >= BG_X_LW + 10) {
						boss_rotate_coordinate[i][0].x--;
					}
					else {
						boss_rotate_count[i][0]++;
						if (boss_rotate_count[i][0] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][0] = 0;
							boss_rotate_mode[i][0] = LEFT;
						}
					}
				}
				else if (boss_rotate_mode[i][0] == LEFT) {
					if (boss_rotate_coordinate[i][0].y <= BG_Y_HH - 10) {
						boss_rotate_coordinate[i][0].y++;
					}
					else {
						boss_rotate_count[i][0]++;
						if (boss_rotate_count[i][0] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][0] = 0;
							boss_rotate_mode[i][0] = BOT;
						}
					}
				}
				else if (boss_rotate_mode[i][0] == BOT) {
					if (boss_rotate_coordinate[i][0].x <= BG_X_HW - 10) {
						boss_rotate_coordinate[i][0].x++;
					}
					else {
						boss_rotate_count[i][0]++;
						if (boss_rotate_count[i][0] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][0] = 0;
							boss_rotate_mode[i][0] = RIGHT;
						}
					}
				}
				else if (boss_rotate_mode[i][0] == RIGHT) {
					if (boss_rotate_coordinate[i][0].y >= BG_Y_LH + 10) {
						boss_rotate_coordinate[i][0].y--;
					}
					else {
						boss_rotate_count[i][0]++;
						if (boss_rotate_count[i][0] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][0] = 0;
							boss_rotate_mode[i][0] = TOP;
						}
					}
				}


				if (boss_rotate_mode[i][1] == TOP) {
					if (boss_rotate_coordinate[i][1].x <= BG_X_HW - 10) {
						boss_rotate_coordinate[i][1].x++;
					}
					else {
						boss_rotate_count[i][1]++;
						if (boss_rotate_count[i][1] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][1] = 0;
							boss_rotate_mode[i][1] = RIGHT;
						}
					}
				}
				else if (boss_rotate_mode[i][1] == LEFT) {
					if (boss_rotate_coordinate[i][1].y >= BG_Y_LH + 10) {
						boss_rotate_coordinate[i][1].y--;
					}
					else {
						boss_rotate_count[i][1]++;
						if (boss_rotate_count[i][1] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][1] = 0;
							boss_rotate_mode[i][1] = TOP;
						}
					}
				}
				else if (boss_rotate_mode[i][1] == BOT) {
					if (boss_rotate_coordinate[i][1].x >= BG_X_LW + 10) {
						boss_rotate_coordinate[i][1].x--;
					}
					else {
						boss_rotate_count[i][1]++;
						if (boss_rotate_count[i][1] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][1] = 0;
							boss_rotate_mode[i][1] = LEFT;
						}
					}
				}
				else if (boss_rotate_mode[i][1] == RIGHT) {
					if (boss_rotate_coordinate[i][1].y <= BG_Y_HH - 10) {
						boss_rotate_coordinate[i][1].y++;
					}
					else {
						boss_rotate_count[i][1]++;
						if (boss_rotate_count[i][1] >= BOSS_ROTATE_COUNT) {
							boss_rotate_count[i][1] = 0;
							boss_rotate_mode[i][1] = BOT;
						}
					}
				}


			}

			boss_rotate_count_num++;
			if (boss_rotate_count_num >= BOSS_ROTATE_COUNT_TIMING) {
				boss_rotate_count_num = 0;
				for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
					for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
						if (boss_rotate_shot_mode[boss_rotate_shot_num[p][t]][p][t] == MODE_WAIT) {
							boss_rotate_shot_angle[boss_rotate_shot_num[p][t]][p][t] = atan2f(player_coordinate.y - boss_rotate_coordinate[p][t].y, player_coordinate.x - boss_rotate_coordinate[p][t].x);
							boss_rotate_shot_coordinate[boss_rotate_shot_num[p][t]][p][t].x = boss_rotate_coordinate[p][t].x;
							boss_rotate_shot_coordinate[boss_rotate_shot_num[p][t]][p][t].y = boss_rotate_coordinate[p][t].y;
							boss_rotate_shot_mode[boss_rotate_shot_num[p][t]][p][t] = MODE_MOVE;
							PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
							display_handle_rotate_shot_mode[boss_rotate_shot_num[p][t]][p][t] = DISPLAY;
							boss_rotate_shot_num[p][t]++;
						}
					}
				}
			}

			for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
				for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
					if (boss_rotate_shot_num[p][t] >= BOSS_ROTATE_SHOT_MAX) {
						boss_rotate_shot_num[p][t] = 0;
					}
				}
			}

			for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
				for (int i = 0; i < BOSS_ROTATE_SHOT_MAX; i++) {
					for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
						if (boss_rotate_shot_mode[i][p][t] == MODE_MOVE) {
							boss_rotate_shot_coordinate[i][p][t].x += cosf(boss_rotate_shot_angle[i][p][t]) * BOSS_ROTATE_SHOT_SPEED;
							boss_rotate_shot_coordinate[i][p][t].y += sinf(boss_rotate_shot_angle[i][p][t]) * BOSS_ROTATE_SHOT_SPEED;
							if (boss_rotate_shot_coordinate[i][p][t].x <= BG_X_LW || boss_rotate_shot_coordinate[i][p][t].x >= BG_X_HW || boss_rotate_shot_coordinate[i][p][t].y <= BG_Y_LH || boss_rotate_shot_coordinate[i][p][t].y >= BG_Y_HH) {
								boss_rotate_shot_mode[i][p][t] = MODE_WAIT;
							}
						}
					}
				}
			}

			boss_nekomimi_rr -= 0.7;
			for (int i = 0; i < BOSS_NEKOMIMI_MAX; i++) {
				for (int j = 0; j < BOSS_NEKOMIMI_NUM; j++) {
					if (boss_nekomimi_attack_mode[i][j] == MODE_MOVE) {
						boss_nekomimi_attack_shot_coordinate[i][j].x += cosf(D2R(boss_nekomimi_attack_missile_rot[i][j]) + D2R(boss_nekomimi_s * j) + D2R(boss_nekomimi_rr)) * boss_nekomimi_attack_speed[i][j];
						boss_nekomimi_attack_shot_coordinate[i][j].y += sinf(D2R(boss_nekomimi_attack_missile_rot[i][j]) + D2R(boss_nekomimi_s * j) + D2R(boss_nekomimi_rr)) * boss_nekomimi_attack_speed[i][j];
					}
				}
			}

			//////////////

			for (int j = 0; j < BOSS_SMALL_SHOT_MAX; j++) {
				if (boss_small_shot_mode[j] == MODE_MOVE) {
					boss_small_ssss += 0.05;
					if (boss_small_r <= 60) boss_small_r += 0.04;
					boss_small_shot_shot[j].x = boss.x + boss_small_r * cosf(D2R(30 * j) + D2R(boss_small_ssss));
					boss_small_shot_shot[j].y = boss.y + boss_small_r * sinf(D2R(30 * j) + D2R(boss_small_ssss));
				}
			}
			/////////////

			for (int j = 0; j < BOSS_SMALL_AMAX; j++) {
				if (boss_small_mode[j] == MODE_MOVE) {
					boss_small_s1 -= 0.1;
					if (boss_small_r1 <= 85) boss_small_r1 += 0.05;
					boss_small_shot[j].x = boss.x + boss_small_r1 * cosf(D2R(30 * j) + D2R(boss_small_s1));
					boss_small_shot[j].y = boss.y + boss_small_r1 * sinf(D2R(30 * j) + D2R(boss_small_s1));
				}
			}
		}

		// =====================================================

		// =====================================================
		//　ステージ３
		if (boss_stage_now == third) {
			//　敵の弾
			boss_furan_red_circle_count++;																				//　カウント
			if (boss_furan_red_circle_count >= BOSS_FURAN_RED_COUNT_TIMING) {													//　カウントがそのタイミングになった時
				boss_furan_red_circle_count = START_ZERO;																//　カウントを０に戻す
				int x = GetRand(50) + 198;
				int y = GetRand(50) + 125;
				for (int i = 0; i < BOSS_FURAN_RED_SHOT_MAX; i++) {													//　i を３回繰り返す
					if (boss_furan_red_circle_mode[i][boss_furan_red_circle_shot_num] == false) {									//　モードが false の時
						boss_furan_red_circle_shot[i][boss_furan_red_circle_shot_num].x = x;				//　ｘ座標を敵に合わせる
						boss_furan_red_circle_shot[i][boss_furan_red_circle_shot_num].y = y;				//　ｙ座標を敵に合わせる
						boss_furan_red_circle_rot = BOSS_FURAN_RED_ROT_DIRECTLY_BELOW - BOSS_FURAN_RED_ROT_SIZE + BOSS_FURAN_RED_ROT_SIZE * i;		//　角度を決める
						boss_furan_red_circle_target_angle[i][boss_furan_red_circle_shot_num] = D2R(boss_furan_red_circle_rot);			//　角度を合わせる
						boss_furan_red_circle_mode[i][boss_furan_red_circle_shot_num] = true;										//　モードを true にする
						PlaySoundMem(se_enemy_attack[3], DX_PLAYTYPE_BACK);
						display_handle_furan_red_shot_mode[i][boss_furan_red_circle_shot_num] = DISPLAY;
						boss_furan_red_circle_shot_num++;																//　現在の番号から１増やす
					}
					if (boss_furan_red_circle_shot_num >= BOSS_FURAN_RED_NUM_MAX) {											//　もし現在の番号が最大値を超えると
						boss_furan_red_circle_shot_num = START_ZERO;														//　番号を０に戻す
					}
				}
			}
			for (int i = 0; i < BOSS_FURAN_RED_SHOT_MAX; i++) {														//　i を３回繰り返す
				for (int j = 0; j < BOSS_FURAN_RED_NUM_MAX; j++) {													//　j を１００回繰り返す
					if (boss_furan_red_circle_mode[i][j] == true) {														//　動く状態なら
						boss_furan_red_circle_shot[i][j].x += cosf(boss_furan_red_circle_target_angle[i][j]) * BOSS_FURAN_RED_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｘ軸移動
						boss_furan_red_circle_shot[i][j].y += sinf(boss_furan_red_circle_target_angle[i][j]) * BOSS_FURAN_RED_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｙ軸移動
					}
					if (boss_furan_red_circle_shot[i][j].y >= WINDOW_H || boss_furan_red_circle_shot[i][j].y <= 0 || boss_furan_red_circle_shot[i][j].x >= WINDOW_W || boss_furan_red_circle_shot[i][j].x <= 0) {												//　画面より下に行ったら
						boss_furan_red_circle_mode[i][j] = false;														//　動かないもーどにする
					}
				}
			}

			//　敵の弾
			boss_furan_blue_circle_count++;																				//　カウント
			if (boss_furan_blue_circle_count >= BOSS_FURAN_BLUE_COUNT_TIMING) {													//　カウントがそのタイミングになった時
				boss_furan_blue_circle_count = START_ZERO;																//　カウントを０に戻す
				int i = GetRand(1);
				int x = GetRand(25) + BG_X_LW;
				int y1 = GetRand((BG_Y_HH - BG_Y_LH) / 2) + BG_Y_LH;
				int y2 = GetRand((BG_Y_HH - BG_Y_LH) / 2) + BG_Y_LH;
				for (int i = 0; i < BOSS_FURAN_BLUE_SHOT_MAX; i++) {													//　i を３回繰り返す
					for (int k = 0; k < BOSS_FURAN_BLUE_LB; k++) {
						if (boss_furan_blue_circle_mode[i][boss_furan_blue_circle_shot_num][k] == false) {									//　モードが false の時
							boss_furan_blue_circle_shot[i][boss_furan_blue_circle_shot_num][k].x = x + 360 * k;				//　ｘ座標を敵に合わせる
							boss_furan_blue_circle_shot[i][boss_furan_blue_circle_shot_num][0].y = y1;				//　ｙ座標を敵に合わせる
							boss_furan_blue_circle_shot[i][boss_furan_blue_circle_shot_num][1].y = y2;				//　ｙ座標を敵に合わせる
							boss_furan_blue_circle_rot = BOSS_FURAN_BLUE_ROT_DIRECTLY_BELOW - BOSS_FURAN_BLUE_ROT_SIZE + BOSS_FURAN_BLUE_ROT_SIZE * i;		//　角度を決める
							boss_furan_blue_circle_target_angle[i][boss_furan_blue_circle_shot_num][k] = D2R(boss_furan_blue_circle_rot);			//　角度を合わせる
							boss_furan_blue_circle_mode[i][boss_furan_blue_circle_shot_num][k] = true;										//　モードを true にする
							PlaySoundMem(se_enemy_attack[1], DX_PLAYTYPE_BACK);
							display_handle_furan_blue_shot_mode[i][boss_furan_blue_circle_shot_num][k] = DISPLAY;
							boss_furan_blue_circle_shot_num++;																//　現在の番号から１増やす
						}
					}
					if (boss_furan_blue_circle_shot_num >= BOSS_FURAN_BLUE_NUM_MAX) {											//　もし現在の番号が最大値を超えると
						boss_furan_blue_circle_shot_num = START_ZERO;														//　番号を０に戻す
					}
				}
			}
			for (int i = 0; i < BOSS_FURAN_BLUE_SHOT_MAX; i++) {														//　i を３回繰り返す
				for (int j = 0; j < BOSS_FURAN_BLUE_NUM_MAX; j++) {													//　j を１００回繰り返す
					for (int k = 0; k < BOSS_FURAN_BLUE_LB; k++) {
						if (boss_furan_blue_circle_mode[i][j][k] == true) {														//　動く状態なら
							boss_furan_blue_circle_shot[i][j][k].x += cosf(boss_furan_blue_circle_target_angle[i][j][k]) * BOSS_FURAN_BLUE_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｘ軸移動
							boss_furan_blue_circle_shot[i][j][k].y += sinf(boss_furan_blue_circle_target_angle[i][j][k]) * BOSS_FURAN_BLUE_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｙ軸移動
						}
						if (boss_furan_blue_circle_shot[i][j][k].y >= WINDOW_H || boss_furan_blue_circle_shot[i][j][k].y <= 0 || boss_furan_blue_circle_shot[i][j][k].x >= WINDOW_W || boss_furan_blue_circle_shot[i][j][k].x <= 0) {												//　画面より下に行ったら
							boss_furan_blue_circle_mode[i][j][k] = false;														//　動かないもーどにする
						}
					}
				}
			}
			//　敵の弾
			boss_furan_purple_circle_count++;																				//　カウント
			if (boss_furan_purple_circle_count >= BOSS_FURAN_PURPLE_COUNT_TIMING) {													//　カウントがそのタイミングになった時
				boss_furan_purple_circle_count = START_ZERO;																//　カウントを０に戻す
				for (int i = 0; i < BOSS_FURAN_PURPLE_SHOT_MAX; i++) {													//　i を３回繰り返す
					if (boss_furan_purple_circle_mode[i][boss_furan_purple_circle_shot_num] == false) {									//　モードが false の時
						boss_furan_purple_circle_shot[i][boss_furan_purple_circle_shot_num].x = boss.x;				//　ｘ座標を敵に合わせる
						boss_furan_purple_circle_shot[i][boss_furan_purple_circle_shot_num].y = boss.y;				//　ｙ座標を敵に合わせる
						boss_furan_purple_circle_rot = BOSS_FURAN_PURPLE_ROT_DIRECTLY_BELOW - BOSS_FURAN_PURPLE_ROT_SIZE + BOSS_FURAN_PURPLE_ROT_SIZE * i;		//　角度を決める
						boss_furan_purple_circle_target_angle[i][boss_furan_purple_circle_shot_num] = D2R(boss_furan_purple_circle_rot);			//　角度を合わせる
						boss_furan_purple_circle_mode[i][boss_furan_purple_circle_shot_num] = true;										//　モードを true にする
						PlaySoundMem(se_enemy_attack[0], DX_PLAYTYPE_BACK);
						display_handle_furan_purple_shot_mode[i][boss_furan_purple_circle_shot_num] = DISPLAY;
						boss_furan_purple_circle_shot_num++;																//　現在の番号から１増やす
					}
					if (boss_furan_purple_circle_shot_num >= BOSS_FURAN_PURPLE_NUM_MAX) {											//　もし現在の番号が最大値を超えると
						boss_furan_purple_circle_shot_num = START_ZERO;														//　番号を０に戻す
					}
				}
			}
			for (int i = 0; i < BOSS_FURAN_PURPLE_SHOT_MAX; i++) {														//　i を３回繰り返す
				for (int j = 0; j < BOSS_FURAN_PURPLE_NUM_MAX; j++) {													//　j を１００回繰り返す
					if (boss_furan_purple_circle_mode[i][j] == true) {														//　動く状態なら
						boss_furan_purple_circle_shot[i][j].x += cosf(boss_furan_purple_circle_target_angle[i][j]) * BOSS_FURAN_PURPLE_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｘ軸移動
						boss_furan_purple_circle_shot[i][j].y += sinf(boss_furan_purple_circle_target_angle[i][j]) * BOSS_FURAN_PURPLE_SPEED_SWAY;	//　ENEMY_RED_SPEED の速さでｙ軸移動
					}
					if (boss_furan_purple_circle_shot[i][j].y >= WINDOW_H || boss_furan_purple_circle_shot[i][j].y <= 0 || boss_furan_purple_circle_shot[i][j].x >= WINDOW_W || boss_furan_purple_circle_shot[i][j].x <= 0) {												//　画面より下に行ったら
						boss_furan_purple_circle_mode[i][j] = false;														//　動かないもーどにする
					}
				}
			}
		}

		// =====================================================
	}


}
// =====================================================
//		描画
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	GameUpdate関数が実行された後に実行される関数
// =====================================================
void EnemyDraw()
{
//	DrawRectRotaGraphF(50, 50, 120 * 4, 120 * 3, 120, 120, 0.12, 0, gr_enemy_shot[0], 1);
//	DrawRectRotaGraphF(50, 100, 120 * 4, 120 * 3, 120, 120, 0.12, 0, gr_enemy_shot[1], 1);
//	DrawRectRotaGraphF(50, 150, 120 * 4, 120 * 3, 120, 120, 0.12, 0, gr_enemy_shot[2], 1);
//	DrawRectRotaGraphF(50, 200, 240 * 4, 240 * 3, 240, 240, 0.06, 0, gr_enemy_shot[3], 1);

//	DrawRotaGraphF(50, 250, 0.06, 0, gr_enemy_shot_a[0], 1);
//	DrawRotaGraphF(50, 300, 0.04, 0, gr_enemy_shot_a[1], 1);				//　黄色

//	DrawRectRotaGraphF(50, 350, 0, 0, 20, 20,  0.9, 0, gr_enemy_shot_b, 1);	//　青
//	DrawRectRotaGraphF(50, 370, 20, 0, 20, 20, 0.9, 0, gr_enemy_shot_b, 1);	//　白
//	DrawRectRotaGraphF(50, 390, 0, 20, 20, 20, 0.9, 0, gr_enemy_shot_b, 1);	//　赤
//	DrawRectRotaGraphF(50, 410, 20, 20, 20, 20, 0.9, 0, gr_enemy_shot_b, 1);	//　ピンク

	


	//			DrawRectRotaGraph(enemy_red_coordinate[p].x, enemy_red_coordinate[p].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);	//　赤
	//			DrawRectRotaGraph(enemy_blue_coordinate[p].x, enemy_blue_coordinate[p].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);						//　青

	// =====================================================
	// 攻撃１
	for (int i = 0; i < ATTACK_1_2_MAX; i++) {
		for (int j = 0; j < ATTACK_1_2__NUM; j++) {
			if (display_handle_1_mode[i][j] == DISPLAY)			DrawRectRotaGraphF(zako_attack_1_coordinate[i][j].x, zako_attack_1_coordinate[i][j].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(zako_attack_1_coordinate[i][j].x, zako_attack_1_coordinate[i][j].y, ATTACK_1_2_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
			if (display_handle_1_shot_mode[i][j] == DISPLAY)	DrawRectRotaGraphF(zako_attack_1_shot_coordinate[i][j].x, zako_attack_1_shot_coordinate[i][j].y,0, 0,256, 256, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(zako_attack_1_shot_coordinate[i][j].x, zako_attack_1_shot_coordinate[i][j].y, ATTACK_1_2_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃２
	for (int i = 0; i < ATTACK_1_2_MAX; i++) {
		for (int j = 0; j < ATTACK_1_2__NUM; j++) {
			if (display_handle_2_mode[i][j] == DISPLAY)			DrawRectRotaGraphF(zako_attack_2_coordinate[i][j].x, zako_attack_2_coordinate[i][j].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE); //DrawCircleAA(zako_attack_2_coordinate[i][j].x, zako_attack_2_coordinate[i][j].y, ATTACK_1_2_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
			if (display_handle_2_shot_mode[i][j] == DISPLAY)	DrawRotaGraphF(zako_attack_2_shot_coordinate[i][j].x, zako_attack_2_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(zako_attack_2_shot_coordinate[i][j].x, zako_attack_2_shot_coordinate[i][j].y, ATTACK_1_2_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃３
	for (int i = 0; i < ATTACK_3_4_MAX; i++) {
		if (display_handle_3_mode[i] == DISPLAY) DrawRectRotaGraphF(zako_attack_3_coordinate[i].x, zako_attack_3_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(zako_attack_3_coordinate[i].x, zako_attack_3_coordinate[i].y, ATTACK_3_4_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
		for (int j = 0; j < ATTACK_3_4_NUM; j++) {
			if (display_handle_3_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(zako_attack_3_shot_coordinate[i][j].x, zako_attack_3_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(zako_attack_3_shot_coordinate[i][j].x, zako_attack_3_shot_coordinate[i][j].y, ATTACK_3_4_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃４
	for (int i = 0; i < ATTACK_3_4_MAX; i++) {
		if (display_handle_4_mode[i] == DISPLAY) DrawRectRotaGraphF(zako_attack_4_coordinate[i].x, zako_attack_4_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(zako_attack_4_coordinate[i].x, zako_attack_4_coordinate[i].y, ATTACK_3_4_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
		for (int j = 0; j < ATTACK_3_4_NUM; j++) {
			if (display_handle_4_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(zako_attack_4_shot_coordinate[i][j].x, zako_attack_4_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(zako_attack_4_shot_coordinate[i][j].x, zako_attack_4_shot_coordinate[i][j].y, ATTACK_3_4_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃５
	for (int i = 0; i < ATTACK_5_MAX; i++) {
		if (display_handle_5_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_5_zako_coordinate[i].x, attack_5_zako_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_5_zako_coordinate[i].x, attack_5_zako_coordinate[i].y, ATTACK_5_ZAKO_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
		for (int j = 0; j < ATTACK_5_NUM; j++) {
			if (display_handle_5_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_5_zako_shot_coordinate[i][j].x, attack_5_zako_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_5_zako_shot_coordinate[i][j].x, attack_5_zako_shot_coordinate[i][j].y, ATTACK_5_ZAKO_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}
	if (display_handle_5_c_mode == DISPLAY) DrawRectRotaGraphF(attack_5_coordinate.x, attack_5_coordinate.y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_5_coordinate.x, attack_5_coordinate.y, ATTACK_5_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
	for (int p = 0; p < ATTACK_5_SHOT_NUM; p++) {
		if (display_handle_5_c_shot_mode[p] == DISPLAY) DrawRotaGraphF(attack_5_shot_coordinate[p].x, attack_5_shot_coordinate[p].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_5_shot_coordinate[p].x, attack_5_shot_coordinate[p].y, ATTACK_5_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
	}
	for (int i = 0; i < NEKOMIMI_MAX; i++) {
		for (int j = 0; j < NEKOMIMI_NUM; j++) {
			if (display_handle_5_nekomimi_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_5_nekomimi_attack_shot_coordinate[i][j].x, attack_5_nekomimi_attack_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_5_nekomimi_attack_shot_coordinate[i][j].x, attack_5_nekomimi_attack_shot_coordinate[i][j].y, ATTACK_5_NEKOMIMI_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃６
	for (int i = 0; i < ATTACK_6_MAX; i++) {
		if (display_handle_6_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_6_zako_coordinate[i].x, attack_6_zako_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_6_zako_coordinate[i].x, attack_6_zako_coordinate[i].y, ATTACK_6_ZAKO_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
		for (int j = 0; j < ATTACK_6_NUM; j++) {
			if (display_handle_6_shot_mode[i][j] == DISPLAY)DrawRotaGraphF(attack_6_zako_shot_coordinate[i][j].x, attack_6_zako_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_6_zako_shot_coordinate[i][j].x, attack_6_zako_shot_coordinate[i][j].y, ATTACK_6_ZAKO_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}
	if (display_handle_6_c_mode == DISPLAY) DrawRectRotaGraphF(attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, ATTACK_6_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
	for (int p = 0; p < ATTACK_6_SHOT_NUM; p++) {
		if (display_handle_6_c_shot_mode[p] == DISPLAY) DrawRotaGraphF(attack_6_teki_shot_coordinate[p].x, attack_6_teki_shot_coordinate[p].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_6_teki_shot_coordinate[p].x, attack_6_teki_shot_coordinate[p].y, ATTACK_6_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
	}
	for (int i = 0; i < NEKOMIMI_MAX; i++) {
		for (int j = 0; j < NEKOMIMI_NUM; j++) {
			if (display_handle_6_nekomimi_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_6_nekomimi_attack_shot_coordinate[i][j].x, attack_6_nekomimi_attack_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_6_nekomimi_attack_shot_coordinate[i][j].x, attack_6_nekomimi_attack_shot_coordinate[i][j].y, ATTACK_6_NEKOMIMI_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃７
	for (int i = 0; i < ATTACK_7_MAX; i++) {
		if (display_handle_7_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_7_zako_coordinate[i].x, attack_7_zako_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_7_zako_coordinate[i].x, attack_7_zako_coordinate[i].y, ATTACK_7_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
		for (int j = 0; j < ATTACK_7_NUM; j++) {
			if (display_handle_7_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_7_zako_shot_coordinate[i][j].x, attack_7_zako_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_7_zako_shot_coordinate[i][j].x, attack_7_zako_shot_coordinate[i][j].y, ATTACK_7_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃８
	for (int i = 0; i < ATTACK_8_MAX; i++) {
		if (display_handle_8_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_8_zako_coordinate[i].x, attack_8_zako_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_8_zako_coordinate[i].x, attack_8_zako_coordinate[i].y, ATTACK_8_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
		for (int j = 0; j < ATTACK_8_NUM; j++) {
			if (display_handle_8_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_8_zako_shot_coordinate[i][j].x, attack_8_zako_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_8_zako_shot_coordinate[i][j].x, attack_8_zako_shot_coordinate[i][j].y, ATTACK_8_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃９
	for (int i = 0; i < ATTACK_9_NUM; i++) {
		if (display_handle_9_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_9_zako_coordinate[i].x, attack_9_zako_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_9_zako_coordinate[i].x, attack_9_zako_coordinate[i].y, ATTACK_9_ROT_SIZE, CIRCLEAA_SQUARE, BLUE, TRUE);
		for (int j = 0; j < ATTACK_9_MAX; j++) {
			if (display_handle_9_shot_mode[i][j] == DISPLAY)DrawRotaGraphF(attack_9_zako_shot_coordinate[i][j].x, attack_9_zako_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);// DrawCircleAA(attack_9_zako_shot_coordinate[i][j].x, attack_9_zako_shot_coordinate[i][j].y, ATTACK_9_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}
	if (display_handle_9_nekomimi_mode == DISPLAY) DrawRectRotaGraphF(attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, ATTACK_9_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
	for (int i = 0; i < ATTACK_9_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_9_NEKOMIMI_NUM; j++) {
			if (display_handle_9_nekomimi_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_9_nekomimi_attack_shot_coordinate[i][j].x, attack_9_nekomimi_attack_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_9_nekomimi_attack_shot_coordinate[i][j].x, attack_9_nekomimi_attack_shot_coordinate[i][j].y, ATTACK_9_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃１０
	for (int i = 0; i < ATTACK_10_NUM; i++) {
		if (display_handle_10_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_10_zako_coordinate[i].x, attack_10_zako_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_10_zako_coordinate[i].x, attack_10_zako_coordinate[i].y, ATTACK_10_ROT_SIZE, CIRCLEAA_SQUARE, BLUE, TRUE);
		for (int j = 0; j < ATTACK_10_MAX; j++) {
			if (display_handle_10_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_10_zako_shot_coordinate[i][j].x, attack_10_zako_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_10_zako_shot_coordinate[i][j].x, attack_10_zako_shot_coordinate[i][j].y, ATTACK_10_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}
	if (display_handle_10_nekomimi_mode == DISPLAY) DrawRectRotaGraphF(attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, ATTACK_10_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
	for (int i = 0; i < ATTACK_10_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_10_NEKOMIMI_NUM; j++) {
			if (display_handle_10_nekomimi_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_10_nekomimi_attack_shot_coordinate[i][j].x, attack_10_nekomimi_attack_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_10_nekomimi_attack_shot_coordinate[i][j].x, attack_10_nekomimi_attack_shot_coordinate[i][j].y, ATTACK_10_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃１１
	for (int i = 0; i < ATTACK_11_NUM; i++) {
		if (display_handle_11_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_11_zako_coordinate[i].x, attack_11_zako_coordinate[i].y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_11_zako_coordinate[i].x, attack_11_zako_coordinate[i].y, ATTACK_11_ROT_SIZE, CIRCLEAA_SQUARE, BLUE, TRUE);
		for (int j = 0; j < ATTACK_11_MAX; j++) {
			if (display_handle_11_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_11_zako_shot_coordinate[i][j].x, attack_11_zako_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_11_zako_shot_coordinate[i][j].x, attack_11_zako_shot_coordinate[i][j].y, ATTACK_11_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}
	if (display_handle_11_nekomimi_mode == DISPLAY) DrawRectRotaGraphF(attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);//DrawCircleAA(attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, ATTACK_11_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
	for (int i = 0; i < ATTACK_11_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_11_NEKOMIMI_NUM; j++) {
			if (display_handle_11_nekomimi_shot_mode[i][j] == DISPLAY) DrawRotaGraphF(attack_11_nekomimi_attack_shot_coordinate[i][j].x, attack_11_nekomimi_attack_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_11_nekomimi_attack_shot_coordinate[i][j].x, attack_11_nekomimi_attack_shot_coordinate[i][j].y, ATTACK_11_SHOT_ROT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	// 攻撃１２
	for (int i = 0; i < ATTACK_12_SHOT_MAX; i++) {
		if (display_handle_12_shot_mode[i] == DISPLAY) DrawRectRotaGraphF(attack_12_circle_shot[i].x, attack_12_circle_shot[i].y, 0, 20, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(attack_12_circle_shot[i].x, attack_12_circle_shot[i].y, ATTACK_12_SHOT_ROT, CIRCLEAA_SQUARE, YELLOW, TRUE);
	}
	if (display_handle_12_mode == DISPLAY)DrawRectRotaGraphF(attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, enemy_rb_img_coordinate.x, enemy_rb_img_coordinate.y + ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_WIDTH, ENEMY_RB_IMG_HEIGHT, ENEMY_RB_IMG_SAME_SIZE, 0, enemy_rb_image, TRUE);// DrawCircleAA(attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, ATTACK_12_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
	for (int i = 0; i < ATTACK_12_NEKOMIMI_MAX; i++) {
		for (int j = 0; j < ATTACK_12_NEKOMIMI_NUM; j++) {
			if (display_handle_12_nekomimi_shot_mode[i][j] == DISPLAY)DrawRotaGraphF(attack_12_nekomimi_attack_shot_coordinate[i][j].x, attack_12_nekomimi_attack_shot_coordinate[i][j].y, 0.06, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(attack_12_nekomimi_attack_shot_coordinate[i][j].x, attack_12_nekomimi_attack_shot_coordinate[i][j].y, ATTACK_12_SHOT_ROT, CIRCLEAA_SQUARE, YELLOW, TRUE);
		}
	}

	// =====================================================
	//	ボス
	// =====================================================

	// =====================================================
	//　ステージ１
	if (boss_mode == MODE_MOVE) {
		if (boss_stage_now == none) {
			if (w_alpha == DISPLAY) {
				SetFontSize(30);
				//	DrawString((BG_X_HW - BG_X_LW) / 2 + BG_X_LW - 40, WINDOW_H / 2 - 20, "BOSS", GetColor(255, 0, 0));
				DrawRotaGraph((BG_X_HW - BG_X_LW) / 2 + BG_X_LW, WINDOW_H / 2, 1, 0, boss_worning, TRUE);
			}
		}
	}

	if (boss_stage_now == first) {
		//　ＨＰ
		DrawFillBox(BG_X_LW + 90, BG_Y_LH + 20, BG_X_LW + 90 + boss_hp / 2, BG_Y_LH + 25, RED);
		//　タイマー
		DrawCircleAA(BG_X_LW + 50, BG_Y_LH + 20, 20, CIRCLEAA_SQUARE, BLUE, TRUE);
		SetFontSize(20);
		DrawFormatString(BG_X_LW + 40, BG_Y_LH + 10, WHITE, "%d", 30 - boss_attack_count / 60);
		SetFontSize(10);
		// =====================================================
		//　Ｃ１
		for (int j = 0; j < BOSS_BIG_LEFT_1_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_BIG_LEFT_1_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_big[j][i][0] == DISPLAY) DrawRotaGraphF(boss_big_left_1_shot_shot[j][i].x, boss_big_left_1_shot_shot[j][i].y, 0.12, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_big_left_1_shot_shot[j][i].x, boss_big_left_1_shot_shot[j][i].y, BOSS_BIG_LEFT_1_SHOT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
			}
		}

		for (int j = 0; j < BOSS_SMALL_LEFT_1_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_SMALL_LEFT_1_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_small[j][i][0] == DISPLAY) DrawRectRotaGraphF(boss_small_left_1_shot_shot[j][i].x, boss_small_left_1_shot_shot[j][i].y, 0, 0, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_left_1_shot_shot[j][i].x, boss_small_left_1_shot_shot[j][i].y, BOSS_SMALL_LEFT_1_SHOT_SIZE, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
			}
		}
		// =====================================================


		// =====================================================
		//　Ｃ２
		for (int j = 0; j < BOSS_BIG_RIGHT_1_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_BIG_RIGHT_1_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_big[j][i][1] == DISPLAY)	DrawRotaGraphF(boss_big_right_1_shot_shot[j][i].x, boss_big_right_1_shot_shot[j][i].y, 0.12, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_big_right_1_shot_shot[j][i].x, boss_big_right_1_shot_shot[j][i].y, BOSS_BIG_RIGHT_1_SHOT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
			}
		}

		for (int j = 0; j < BOSS_SMALL_RIGHT_1_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_SMALL_RIGHT_1_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_small[j][i][1] == DISPLAY) DrawRectRotaGraphF(boss_small_right_1_shot_shot[j][i].x, boss_small_right_1_shot_shot[j][i].y, 0, 0, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_right_1_shot_shot[j][i].x, boss_small_right_1_shot_shot[j][i].y, BOSS_SMALL_RIGHT_1_SHOT_SIZE, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
			}
		}
		// =====================================================


		// =====================================================
		//　Ｃ３
		for (int j = 0; j < BOSS_BIG_LEFT_2_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_BIG_LEFT_2_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_big[j][i][2] == DISPLAY) DrawRotaGraphF(boss_big_left_2_shot_shot[j][i].x, boss_big_left_2_shot_shot[j][i].y, 0.12, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_big_left_2_shot_shot[j][i].x, boss_big_left_2_shot_shot[j][i].y, BOSS_BIG_LEFT_2_SHOT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
			}
		}

		for (int j = 0; j < BOSS_SMALL_LEFT_2_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_SMALL_LEFT_2_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_small[j][i][2] == DISPLAY) DrawRectRotaGraphF(boss_small_left_2_shot_shot[j][i].x, boss_small_left_2_shot_shot[j][i].y, 0, 0, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_left_2_shot_shot[j][i].x, boss_small_left_2_shot_shot[j][i].y, BOSS_SMALL_LEFT_2_SHOT_SIZE, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
			}
		}
		// =====================================================


		// =====================================================
		//　Ｃ４
		for (int j = 0; j < BOSS_BIG_RIGHT_2_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_BIG_RIGHT_2_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_big[j][i][3] == DISPLAY) DrawRotaGraphF(boss_big_right_2_shot_shot[j][i].x, boss_big_right_2_shot_shot[j][i].y, 0.12, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_big_right_2_shot_shot[j][i].x, boss_big_right_2_shot_shot[j][i].y, BOSS_BIG_RIGHT_2_SHOT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
			}
		}

		for (int j = 0; j < BOSS_SMALL_RIGHT_2_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_SMALL_RIGHT_2_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_small[j][i][3] == DISPLAY) DrawRectRotaGraphF(boss_small_right_2_shot_shot[j][i].x, boss_small_right_2_shot_shot[j][i].y, 0, 0, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_right_2_shot_shot[j][i].x, boss_small_right_2_shot_shot[j][i].y, BOSS_SMALL_RIGHT_2_SHOT_SIZE, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
			}
		}

		// =====================================================
		//　Ｃ５
		for (int j = 0; j < BOSS_BIG_LEFT_3_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_BIG_LEFT_3_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_big[j][i][4] == DISPLAY) DrawRotaGraphF(boss_big_left_3_shot_shot[j][i].x, boss_big_left_3_shot_shot[j][i].y, 0.12, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_big_left_3_shot_shot[j][i].x, boss_big_left_3_shot_shot[j][i].y, BOSS_BIG_LEFT_3_SHOT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
			}
		}

		for (int j = 0; j < BOSS_SMALL_LEFT_3_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_SMALL_LEFT_3_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_small[j][i][4] == DISPLAY) DrawRectRotaGraphF(boss_small_left_3_shot_shot[j][i].x, boss_small_left_3_shot_shot[j][i].y, 0, 0, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_left_3_shot_shot[j][i].x, boss_small_left_3_shot_shot[j][i].y, BOSS_SMALL_LEFT_3_SHOT_SIZE, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
			}
		}
		// =====================================================


		// =====================================================
		//　Ｃ６
		for (int j = 0; j < BOSS_BIG_RIGHT_3_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_BIG_RIGHT_3_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_big[j][i][5] == DISPLAY) DrawRotaGraphF(boss_big_right_3_shot_shot[j][i].x, boss_big_right_3_shot_shot[j][i].y, 0.12, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_big_right_3_shot_shot[j][i].x, boss_big_right_3_shot_shot[j][i].y, BOSS_BIG_RIGHT_3_SHOT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
			}
		}

		for (int j = 0; j < BOSS_SMALL_RIGHT_3_SHOT_MAX; j++) {
			for (int i = 0; i < BOSS_SMALL_RIGHT_3_SHOT_NUM; i++) {
				if (display_handle_boss_shot_mode_small[j][i][5] == DISPLAY) DrawRectRotaGraphF(boss_small_right_3_shot_shot[j][i].x, boss_small_right_3_shot_shot[j][i].y, 0, 0, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_right_3_shot_shot[j][i].x, boss_small_right_3_shot_shot[j][i].y, BOSS_SMALL_RIGHT_3_SHOT_SIZE, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
			}
		}
		// =====================================================

		// =====================================================


		// =====================================================
		//　攻撃２雪
		for (int i = 0; i < BOSS_RAND_NUM1; i++) {
			if (display_handle_snow_1_shot_mode[i] == DISPLAY) DrawRectRotaGraphF(boss_rand_shot_1[i].x, boss_rand_shot_1[i].y, 20, 0, 20, 20, 0.6, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_rand_shot_1[i].x, boss_rand_shot_1[i].y, BOSS_RAND_SIZE1, CIRCLEAA_SQUARE, WHITE, TRUE);
		}

		for (int i = 0; i < BOSS_RAND_NUM2; i++) {
			if (display_handle_snow_2_shot_mode[i] == DISPLAY) DrawRectRotaGraphF(boss_rand_shot_2[i].x, boss_rand_shot_2[i].y, 20, 0, 20, 20, 1, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_rand_shot_2[i].x, boss_rand_shot_2[i].y, BOSS_RAND_SIZE2, CIRCLEAA_SQUARE, WHITE, TRUE);
		}

		for (int i = 0; i < BOSS_RAND_NUM3; i++) {
			if (display_handle_snow_3_shot_mode[i] == DISPLAY) DrawRectRotaGraphF(boss_rand_shot_3[i].x, boss_rand_shot_3[i].y, 20, 0, 20, 20, 1.6, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_rand_shot_3[i].x, boss_rand_shot_3[i].y, BOSS_RAND_SIZE3, CIRCLEAA_SQUARE, WHITE, TRUE);
		}
	}
	// =====================================================
	// =====================================================

	// =====================================================
	//　ステージ２
	if (boss_stage_now == second) {
		//　ＨＰ
		DrawFillBox(BG_X_LW + 90, BG_Y_LH + 20, BG_X_LW + 90 + boss_hp / 2, BG_Y_LH + 25, RED);
		//　タイマー
		DrawCircleAA(BG_X_LW + 50, BG_Y_LH + 20, 20, CIRCLEAA_SQUARE, BLUE, TRUE);
		SetFontSize(20);
		DrawFormatString(BG_X_LW + 40, BG_Y_LH + 10, WHITE, "%d", 30 - boss_attack_count / 60);
		SetFontSize(10);
		for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
			DrawRectRotaGraphF(boss_rotate_coordinate[p][0].x, boss_rotate_coordinate[p][0].y, 0, 20, 20, 20, 1.6, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_rotate_coordinate[p][0].x, boss_rotate_coordinate[p][0].y, 10, CIRCLEAA_SQUARE, RED, TRUE);
			DrawRectRotaGraphF(boss_rotate_coordinate[p][1].x, boss_rotate_coordinate[p][1].y, 0, 0, 20, 20, 1.6, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_rotate_coordinate[p][1].x, boss_rotate_coordinate[p][1].y, 10, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
			for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
				for (int i = 0; i < BOSS_ROTATE_SHOT_MAX; i++) {
					if (boss_rotate_shot_mode[i][p][t] == MODE_MOVE) {
						if (display_handle_rotate_shot_mode[i][p][t] == DISPLAY) DrawRotaGraphF(boss_rotate_shot_coordinate[i][p][t].x, boss_rotate_shot_coordinate[i][p][t].y, 0.04, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_rotate_shot_coordinate[i][p][t].x, boss_rotate_shot_coordinate[i][p][t].y, BOSS_ROTATE_SHOT_SIZE, CIRCLEAA_SQUARE, YELLOW, TRUE);
					}
				}
			}
		}
		for (int i = 0; i < BOSS_NEKOMIMI_MAX; i++) {
			for (int j = 0; j < BOSS_NEKOMIMI_NUM; j++) {
				DrawRotaGraphF(boss_nekomimi_attack_shot_coordinate[i][j].x, boss_nekomimi_attack_shot_coordinate[i][j].y, 0.04, 0, gr_enemy_shot_a[1], 1);//DrawCircleAA(boss_nekomimi_attack_shot_coordinate[i][j].x, boss_nekomimi_attack_shot_coordinate[i][j].y, 4, CIRCLEAA_SQUARE, YELLOW, TRUE);
			}
		}
		for (int j = 0; j < BOSS_SMALL_SHOT_MAX; j++) {
			DrawRectRotaGraphF(boss_small_shot_shot[j].x, boss_small_shot_shot[j].y, 0, 0, 20, 20, 0.6, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_shot_shot[j].x, boss_small_shot_shot[j].y, BOSS_SMALL_SHOT_SIZE, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
		}
		for (int j = 0; j < BOSS_SMALL_AMAX; j++) {
			DrawRectRotaGraphF(boss_small_shot[j].x, boss_small_shot[j].y, 0, 20, 20, 20, 0.6, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_small_shot[j].x, boss_small_shot[j].y, BOSS_SMALL_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
		}
	}
	// =====================================================

	// =====================================================
	//　ステージ３
	if (boss_stage_now == third) {
		//　ＨＰ
		DrawFillBox(BG_X_LW + 90, BG_Y_LH + 20, BG_X_LW + 90 + boss_hp / 2, BG_Y_LH + 25, RED);
		//　タイマー
		DrawCircleAA(BG_X_LW + 50, BG_Y_LH + 20, 20, CIRCLEAA_SQUARE, BLUE, TRUE);
		SetFontSize(20);
		DrawFormatString(BG_X_LW + 40, BG_Y_LH + 10, WHITE, "%d", 30 - boss_attack_count / 60);
		SetFontSize(10);
		for (int i = 0; i < BOSS_FURAN_RED_SHOT_MAX; i++) {
			for (int j = 0; j < BOSS_FURAN_RED_NUM_MAX; j++) {
				if (boss_furan_red_circle_mode[i][j] != false) {
					if (display_handle_furan_red_shot_mode[i][j] == DISPLAY) DrawRectRotaGraphF(boss_furan_red_circle_shot[i][j].x, boss_furan_red_circle_shot[i][j].y, 0, 20, 20, 20, 0.9, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_furan_red_circle_shot[i][j].x, boss_furan_red_circle_shot[i][j].y, BOSS_FURAN_RED_SHOT_R, CIRCLEAA_SQUARE, RED, TRUE);
				}
			}
		}
		for (int i = 0; i < BOSS_FURAN_BLUE_SHOT_MAX; i++) {
			for (int j = 0; j < BOSS_FURAN_BLUE_NUM_MAX; j++) {
				for (int k = 0; k < BOSS_FURAN_BLUE_LB; k++) {
					if (boss_furan_blue_circle_mode[i][j][k] != false) {
						if (display_handle_furan_blue_shot_mode[i][j][k] == DISPLAY) DrawRectRotaGraphF(boss_furan_blue_circle_shot[i][j][k].x, boss_furan_blue_circle_shot[i][j][k].y, 0, 0, 20, 20, 0.9, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_furan_blue_circle_shot[i][j][k].x, boss_furan_blue_circle_shot[i][j][k].y, BOSS_FURAN_BLUE_SHOT_R, CIRCLEAA_SQUARE, SKYBLUE, TRUE);
					}
				}
			}
		}
		for (int i = 0; i < BOSS_FURAN_PURPLE_SHOT_MAX; i++) {
			for (int j = 0; j < BOSS_FURAN_PURPLE_NUM_MAX; j++) {
				if (boss_furan_purple_circle_mode[i][j] != false) {
					if (display_handle_furan_purple_shot_mode[i][j] == DISPLAY) DrawRectRotaGraphF(boss_furan_purple_circle_shot[i][j].x, boss_furan_purple_circle_shot[i][j].y, 20, 20, 20, 20, 0.9, 0, gr_enemy_shot_b, 1);//DrawCircleAA(boss_furan_purple_circle_shot[i][j].x, boss_furan_purple_circle_shot[i][j].y, BOSS_FURAN_PURPLE_SHOT_R, CIRCLEAA_SQUARE, PINK, TRUE);
				}
			}
		}
	}
	//　ボス座標boss_magic_img
	if (boss_mode == MODE_MOVE) {
		DrawRotaGraph(boss.x, boss.y, 1, 0, boss_magic_img, TRUE);
		DrawRotaGraph(boss.x, boss.y, 0.5, 0, boss_img, TRUE);//DrawCircleAA(boss.x, boss.y, BOSS_ROT_SIZE, CIRCLEAA_SQUARE, RED, TRUE);
	}

	// =====================================================


	// =====================================================
	// デバック表示
	//　中央線
//	DrawLineAA(WINDOW_W / 2, 0, WINDOW_W / 2, WINDOW_H, GetColor(0, 255, 255));
	//DrawFormatString(0, 0, WHITE, "%d", furan_circle_shot_num);

//	DrawFormatString(300, 30, WHITE, "%d", frame_count);

//	DrawLine(BG_X_LW, 0, BG_X_LW, WINDOW_H, RED);		//　左
//	DrawLine(BG_X_HW, 0, BG_X_HW, WINDOW_H, BLUE);		//　右
//	DrawLine(0, BG_Y_LH, WINDOW_W, BG_Y_LH, GREEN);		//　上
//	DrawLine(0, BG_Y_HH, WINDOW_W, BG_Y_HH, YELLOW);	//　下

//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
//	DrawFillBox(0, 0, BG_X_LW, WINDOW_W, GetColor(0, 255, 255));
//	DrawFillBox(BG_X_HW, 0, WINDOW_H, WINDOW_W, GetColor(0, 128, 255));
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//　薄さを戻す

	//DrawFormatString(0, 400, WHITE, "boss : %d", boss_hp);

}
// =====================================================
//		終了
//	ゲームが終了する前に1回だけ実行される関数
//	何か最後に後片付けを行うときに使う
// =====================================================
void EnemyExit()
{
	DeleteGraph(enemy_rb_image);
	DeleteGraph(boss_img);
	DeleteGraph(boss_magic_img);
	DeleteGraph(boss_worning);
	DeleteGraph(gr_enemy_shot[0]);
	DeleteGraph(gr_enemy_shot[1]);
	DeleteGraph(gr_enemy_shot[2]);
	DeleteGraph(gr_enemy_shot[3]);
	DeleteGraph(gr_enemy_shot_a[0]);
	DeleteGraph(gr_enemy_shot_a[1]);
	DeleteGraph(gr_enemy_shot_b);
//	DeleteSoundMem(bgm);
	DeleteSoundMem(se_enemy_attack[0]);
	DeleteSoundMem(se_enemy_attack[1]);
	DeleteSoundMem(se_enemy_attack[2]);
	DeleteSoundMem(se_enemy_attack[3]);
}