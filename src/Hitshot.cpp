#include "Hitshot.h"
#include "DxLib.h"

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

// ==========================================================================================================
//　霊夢の関係
extern bool	player_character_mode;			//　０：霊夢　１：魔理沙
extern enum CharacterMode {
	REIMU,
	MARISA,
};

extern int score;

extern Floatxy	player_coordinate;				//　プレイヤーの座標
//　霊夢のの Sway 弾用の変数
extern Floatxy	sway_coordinate[SWAY_MAX_NUM][SWAY_NUM];				//　座標	半径：SWAY_R
extern bool	sway_mode[SWAY_MAX_NUM][SWAY_NUM];						//　一つ一つがうつ状態か否か　SwayMode　を使う

extern int		player_hit_mode;				//　当たっているか
extern enum
{
	No_Hit,		//　当たっていない
	Hit,		//　当たった
	Hit_Count,	//　カウント
};
extern int		player_exp_count;
extern int		player_hp;						//　ヒットポイント

// =====================================================
// 霊夢の弾
// =====================================================
extern Floatxy hr_shot_coordinate[HR_SHOT_MAX_NUM][HR_SHOT_NUM];		//　座標	HR_SHOT_R
extern bool	hr_shot_mode[HR_SHOT_MAX_NUM][HR_SHOT_NUM];				//　一つ一つのモード	

// =====================================================
// スペルカード（霊夢）
// =====================================================
extern Floatxy	hr_spellcard;							//　スペルカード用の座標
extern float	hr_spellcard_r;							//　中心から広げて敵の攻撃に重なったら消すイメージ

// =====================================================
// 魔理沙のビーム
// =====================================================
extern Floatxy km_shot_coordinate[KM_SHOT_MAX];		//　座標
extern float km_shot_width;							//　ビームの横の幅
extern float km_shot_height;							//　ビームの高さ
extern bool km_shot_mode;								//　モード　（０：撃っている状態　１：撃っていない状態）
//　ビーム強すぎるから１５フレーム１ダメにする
int	km_hit_count;

// =====================================================
// スペルカード（魔理沙）
// =====================================================
extern Floatxy km_spellcard;							//　スペルカード用の座標
extern Floatxy km_spellcard_coordinate;					//　スペルカードを動かす用の変数
int	km_spellcard_hit_count;

extern int		spellcard_count;
extern int		spellcard_shot_mode;					//　０：スペルカード撃たない　１：カウントを待つ状態　２：スペルカード撃つ
extern enum SpellCardMode {
	Spellcard_COUNT,
	Spellcard_WAIT,
	Spellcard_MOVE,
};
// ==========================================================================================================
//　敵関係

// =====================================================
// 攻撃１

extern Floatxy zako_attack_1_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];				//　敵		座標								
extern Floatxy zako_attack_1_shot_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　敵の弾　座標	

extern int		display_handle_1_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];					//　敵を表示するかしないか
extern int		display_handle_1_shot_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　弾の表示するかしないか

extern int		attack_1_hp[ATTACK_1_2_MAX][ATTACK_1_2__NUM];

// =====================================================
// 攻撃２

extern Floatxy zako_attack_2_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];				//　敵		座標							
extern Floatxy zako_attack_2_shot_coordinate[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　敵の弾　座標

extern int		display_handle_2_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];					//　敵を表示するかしないか
extern int		display_handle_2_shot_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];			//　弾の表示するかしないか

extern int		attack_2_hp[ATTACK_1_2_MAX][ATTACK_1_2__NUM];

// =====================================================
// 攻撃３

extern Floatxy zako_attack_3_coordinate[ATTACK_3_4_MAX];								//　敵		座標			
extern Floatxy zako_attack_3_shot_coordinate[ATTACK_3_4_MAX][ATTACK_3_4_NUM];			//　敵の弾　座標		

extern int		display_handle_3_mode[ATTACK_3_4_MAX];									//　敵を表示するかしないか
extern int		display_handle_3_shot_mode[ATTACK_3_4_MAX][ATTACK_3_4_NUM];				//　弾の表示するかしないか

extern int		attack_3_hp[ATTACK_3_4_MAX];

// =====================================================
// 攻撃４

extern Floatxy zako_attack_4_coordinate[ATTACK_3_4_MAX];								//　敵		座標			
extern Floatxy zako_attack_4_shot_coordinate[ATTACK_3_4_MAX][ATTACK_3_4_NUM];			//　敵の弾　座標

extern int		display_handle_4_mode[ATTACK_3_4_MAX];									//　敵を表示するかしないか
extern int		display_handle_4_shot_mode[ATTACK_3_4_MAX][ATTACK_3_4_NUM];				//　弾の表示するかしないか

extern int		attack_4_hp[ATTACK_3_4_MAX];

// =====================================================
// 攻撃５

extern Floatxy attack_5_coordinate;													//　敵		座標
extern Floatxy attack_5_shot_coordinate[ATTACK_5_SHOT_NUM];							//　敵の弾　座標

extern int		display_handle_5_c_mode;												//　敵を表示するかしないか
extern int		display_handle_5_c_shot_mode[ATTACK_5_SHOT_NUM];						//　弾の表示するかしないか

extern int		attack_5_hp;

extern Floatxy attack_5_zako_coordinate[ATTACK_5_MAX];									//　敵		座標	
extern Floatxy attack_5_zako_shot_coordinate[ATTACK_5_MAX][ATTACK_5_NUM];				//　敵の弾　座標	

extern int		display_handle_5_mode[ATTACK_5_MAX];									//　敵を表示するかしないか
extern int		display_handle_5_shot_mode[ATTACK_5_MAX][ATTACK_5_NUM];					//　弾の表示するかしないか

extern int		attack_zako_5_hp[ATTACK_5_MAX];

//　猫耳
extern Floatxy attack_5_nekomimi_attack_shot_coordinate[NEKOMIMI_MAX][NEKOMIMI_NUM];	//　敵の弾　座標

extern int		display_handle_5_nekomimi_shot_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];		//　弾の表示するかしないか

// =====================================================
// 攻撃６

extern Floatxy attack_6_teki_coordinate;												//　敵	　座標
extern Floatxy attack_6_teki_shot_coordinate[ATTACK_6_SHOT_NUM];						//　敵の弾　座標

extern int		display_handle_6_c_mode;												//　敵を表示するかしないか
extern int		display_handle_6_c_shot_mode[ATTACK_6_SHOT_NUM];						//　弾の表示するかしないか

extern int		attack_6_hp;

extern Floatxy attack_6_zako_coordinate[ATTACK_6_MAX];									//　敵	　座標	
extern Floatxy attack_6_zako_shot_coordinate[ATTACK_6_MAX][ATTACK_6_NUM];				//　敵の弾　座標

extern int		display_handle_6_mode[ATTACK_6_MAX];									//　敵を表示するかしないか
extern int		display_handle_6_shot_mode[ATTACK_6_MAX][ATTACK_6_NUM];					//　弾の表示するかしないか

extern int		attack_zako_6_hp[ATTACK_6_MAX];

extern Floatxy attack_6_nekomimi_attack_shot_coordinate[NEKOMIMI_MAX][NEKOMIMI_NUM];	//　敵	　座標

extern int		display_handle_6_nekomimi_shot_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];		//　弾の表示するかしないか

// =====================================================
// 攻撃７

extern Floatxy attack_7_zako_coordinate[ATTACK_7_MAX];
extern Floatxy attack_7_zako_shot_coordinate[ATTACK_7_MAX][ATTACK_7_NUM];

extern int		display_handle_7_mode[ATTACK_7_MAX];									//　敵を表示するかしないか
extern int		display_handle_7_shot_mode[ATTACK_7_MAX][ATTACK_7_NUM];					//　弾の表示するかしないか

extern int		attack_7_hp[ATTACK_7_MAX];

// =====================================================
// 攻撃８

extern Floatxy attack_8_zako_coordinate[ATTACK_8_MAX];
extern Floatxy attack_8_zako_shot_coordinate[ATTACK_8_MAX][ATTACK_8_NUM];

extern int		display_handle_8_mode[ATTACK_8_MAX];									//　敵を表示するかしないか
extern int		display_handle_8_shot_mode[ATTACK_8_MAX][ATTACK_8_NUM];					//　弾の表示するかしないか

extern int		attack_8_hp[ATTACK_8_MAX];

// =====================================================
// 攻撃９

extern Floatxy attack_9_nekomimi_attack_coordinate;
extern Floatxy attack_9_nekomimi_attack_shot_coordinate[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];

extern int		display_handle_9_nekomimi_mode;																//　敵を表示するかしないか
extern int		display_handle_9_nekomimi_shot_mode[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];			//　弾の表示するかしないか

extern int		attack_9_hp;

extern Floatxy attack_9_zako_coordinate[ATTACK_9_NUM];
extern Floatxy attack_9_zako_shot_coordinate[ATTACK_9_NUM][ATTACK_9_MAX];

extern int		display_handle_9_mode[ATTACK_9_NUM];									//　敵を表示するかしないか
extern int		display_handle_9_shot_mode[ATTACK_9_NUM][ATTACK_9_MAX];					//　弾の表示するかしないか

extern int		attack_zako_9_hp[ATTACK_9_NUM];

// =====================================================
// 攻撃１０

extern Floatxy attack_10_nekomimi_attack_coordinate;
extern Floatxy attack_10_nekomimi_attack_shot_coordinate[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];

extern int		display_handle_10_nekomimi_mode;															//　敵を表示するかしないか
extern int		display_handle_10_nekomimi_shot_mode[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];		//　弾の表示するかしないか

extern int		attack_10_hp;

extern Floatxy attack_10_zako_coordinate[ATTACK_10_NUM];
extern Floatxy attack_10_zako_shot_coordinate[ATTACK_10_NUM][ATTACK_10_MAX];

extern int		display_handle_10_mode[ATTACK_10_NUM];									//　敵を表示するかしないか
extern int		display_handle_10_shot_mode[ATTACK_10_NUM][ATTACK_10_MAX];				//　弾の表示するかしないか

extern int		attack_zako_10_hp[ATTACK_10_NUM];

// =====================================================
// 攻撃１１

extern Floatxy attack_11_nekomimi_attack_coordinate;
extern Floatxy attack_11_nekomimi_attack_shot_coordinate[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];

extern int		display_handle_11_nekomimi_mode;																//　敵を表示するかしないか
extern int		display_handle_11_nekomimi_shot_mode[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];			//　弾の表示するかしないか

extern int		attack_11_hp;

extern Floatxy attack_11_zako_coordinate[ATTACK_11_NUM];
extern Floatxy attack_11_zako_shot_coordinate[ATTACK_11_NUM][ATTACK_11_MAX];

extern int		display_handle_11_mode[ATTACK_11_NUM];									//　敵を表示するかしないか
extern int		display_handle_11_shot_mode[ATTACK_11_NUM][ATTACK_11_MAX];				//　弾の表示するかしないか

extern int		attack_zako_11_hp[ATTACK_11_NUM];

// =====================================================
// 攻撃１２

extern Floatxy attack_12_nekomimi_coordinate;

extern Floatxy attack_12_nekomimi_attack_shot_coordinate[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];
extern Floatxy attack_12_circle_shot[ATTACK_12_SHOT_MAX];					//　赤色の雑魚敵の弾

extern int		display_handle_12_nekomimi_shot_mode[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];			//　弾の表示するかしないか

extern int		display_handle_12_mode;										//　敵を表示するかしないか
extern int		display_handle_12_shot_mode[ATTACK_12_SHOT_MAX];			//　弾の表示するかしないか

extern int		attack_12_hp;

// =====================================================
//	ボス
// =====================================================
extern Floatxy boss;
extern int boss_hp;
extern int boss_stage_now;
extern bool boss_mode;
extern enum {
	none,
	first,
	second,
	third,
};
extern int boss_attack_count;
// ==========================================================================================================
//　ステージ１攻撃１
// =====================================================
//　時計回り１
extern Floatxy boss_big_left_1_shot_shot[BOSS_BIG_LEFT_1_SHOT_MAX][BOSS_BIG_LEFT_1_SHOT_NUM];
extern Floatxy boss_small_left_1_shot_shot[BOSS_SMALL_LEFT_1_SHOT_MAX][BOSS_SMALL_LEFT_1_SHOT_NUM];
// =====================================================
//　反時計回り１
extern Floatxy boss_big_right_1_shot_shot[BOSS_BIG_LEFT_1_SHOT_MAX][BOSS_BIG_LEFT_1_SHOT_NUM];
extern Floatxy boss_small_right_1_shot_shot[BOSS_SMALL_LEFT_1_SHOT_MAX][BOSS_SMALL_LEFT_1_SHOT_NUM];
// =====================================================
//　時計回り２
extern Floatxy boss_big_left_2_shot_shot[BOSS_BIG_LEFT_2_SHOT_MAX][BOSS_BIG_LEFT_2_SHOT_NUM];
extern Floatxy boss_small_left_2_shot_shot[BOSS_SMALL_LEFT_2_SHOT_MAX][BOSS_SMALL_LEFT_2_SHOT_NUM];
// =====================================================
//　反時計回り２
extern Floatxy boss_big_right_2_shot_shot[BOSS_BIG_LEFT_2_SHOT_MAX][BOSS_BIG_LEFT_2_SHOT_NUM];
extern Floatxy boss_small_right_2_shot_shot[BOSS_SMALL_LEFT_2_SHOT_MAX][BOSS_SMALL_LEFT_2_SHOT_NUM];
// =====================================================
//　時計回り３
extern Floatxy boss_big_left_3_shot_shot[BOSS_BIG_LEFT_3_SHOT_MAX][BOSS_BIG_LEFT_3_SHOT_NUM];
extern Floatxy boss_small_left_3_shot_shot[BOSS_SMALL_LEFT_3_SHOT_MAX][BOSS_SMALL_LEFT_3_SHOT_NUM];
// =====================================================
//　反時計回り３
extern Floatxy boss_big_right_3_shot_shot[BOSS_BIG_LEFT_3_SHOT_MAX][BOSS_BIG_LEFT_3_SHOT_NUM];
extern Floatxy boss_small_right_3_shot_shot[BOSS_SMALL_LEFT_3_SHOT_MAX][BOSS_SMALL_LEFT_3_SHOT_NUM];

extern int		display_handle_boss_shot_mode_big[9][4][6];				//　大きいほうの弾の表示するかしないか
extern int		display_handle_boss_shot_mode_small[9][3][6];			//　大きいほうの弾の表示するかしないか

// ==========================================================================================================
//　ステージ１攻撃２
extern Floatxy boss_rand_shot_1[BOSS_RAND_NUM1];
extern Floatxy boss_rand_shot_2[BOSS_RAND_NUM2];
extern Floatxy boss_rand_shot_3[BOSS_RAND_NUM3];

extern int		display_handle_snow_1_shot_mode[BOSS_RAND_NUM1];			//　雪弾１の表示するかしないか
extern int		display_handle_snow_2_shot_mode[BOSS_RAND_NUM2];			//　雪弾２の表示するかしないか
extern int		display_handle_snow_3_shot_mode[BOSS_RAND_NUM3];			//　雪弾３の表示するかしないか

// ==========================================================================================================
//　ステージ２
extern Floatxy boss_rotate_coordinate[BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];				//　周りぐるぐる回ってるやつ
extern Floatxy boss_rotate_shot_coordinate[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];										//　赤色の雑魚敵の座標

extern int		display_handle_rotate_shot_mode[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];			//　弾の表示するかしないか

extern Floatxy boss_nekomimi_attack_shot_coordinate[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
extern Floatxy boss_small_shot_shot[BOSS_SMALL_SHOT_MAX];
extern Floatxy boss_small_shot[BOSS_SMALL_AMAX];
// =====================================================
//　時計回り１
extern enum {
	TOP,
	RIGHT,
	BOT,
	LEFT,
};
extern int		boss_rotate_mode[BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
extern int		boss_rotate_shot_mode[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
extern int		boss_nekomimi_attack_mode[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
extern float	boss_nekomimi_attack_missile_rot[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
extern float	boss_nekomimi_attack_speed[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
extern bool	boss_small_shot_mode[BOSS_SMALL_SHOT_MAX];
extern bool	boss_small_mode[BOSS_SMALL_AMAX];
// ==========================================================================================================
//　ステージ３
extern Floatxy boss_furan_red_circle_shot[BOSS_FURAN_RED_SHOT_MAX][BOSS_FURAN_RED_NUM_MAX];				//　赤色の雑魚敵の弾
extern Floatxy boss_furan_blue_circle_shot[BOSS_FURAN_BLUE_SHOT_MAX][BOSS_FURAN_BLUE_NUM_MAX][BOSS_FURAN_BLUE_LB];				//　赤色の雑魚敵の弾
extern Floatxy boss_furan_purple_circle_shot[BOSS_FURAN_PURPLE_SHOT_MAX][BOSS_FURAN_PURPLE_NUM_MAX];				//　赤色の雑魚敵の弾

extern int		display_handle_furan_red_shot_mode[BOSS_FURAN_RED_SHOT_MAX][BOSS_FURAN_RED_NUM_MAX];							//　弾を表示するかしないか
extern int		display_handle_furan_blue_shot_mode[BOSS_FURAN_BLUE_SHOT_MAX][BOSS_FURAN_BLUE_NUM_MAX][BOSS_FURAN_BLUE_LB];		//　弾を表示するかしないか
extern int		display_handle_furan_purple_shot_mode[BOSS_FURAN_PURPLE_SHOT_MAX][BOSS_FURAN_PURPLE_NUM_MAX];					//　弾を表示するかしないか

#include "Animation.h"
#include "EffectImg.h"

namespace
{
	Animation anim_burst1[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
	Animation anim_burst2[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
	Animation anim_burst3[ATTACK_3_4_MAX];
	Animation anim_burst4[ATTACK_3_4_MAX];
	Animation anim_burst5solo;
	Animation anim_burst5[ATTACK_5_MAX];
	Animation anim_burst6solo;
//	Animation anim_burst6[ATTACK_6_MAX];
	Animation anim_burst7[ATTACK_7_MAX];
	Animation anim_burst8[ATTACK_8_MAX];
	Animation anim_burst9solo;
	Animation anim_burst9[ATTACK_9_NUM];
	Animation anim_burst10solo;
//	Animation anim_burst10[ATTACK_10_NUM];
	Animation anim_burst11solo;
	Animation anim_burst11[ATTACK_11_NUM];
	Animation anim_burst12;
	Animation anim10[ATTACK_10_NUM];
	Animation anim6[ATTACK_6_MAX];

	Animation tama[SWAY_MAX_NUM][SWAY_NUM];
	Animation r_shot[HR_SHOT_MAX_NUM][HR_SHOT_NUM];

	EffectImg effect_slash;

	int x1 = 100;
}

void HitShotInit() {
	// 画像の読み込み
	const char* path = "data/animation/burst2";	// パス
	const int	img_num = 8;						// 画像の枚数
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			anim_burst1[x][p].load(path, img_num);
			anim_burst1[x][p].setSpeed(8);
			anim_burst2[x][p].load(path, img_num);
			anim_burst2[x][p].setSpeed(8);
		}
	}
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		anim_burst3[x].load(path, img_num);
		anim_burst3[x].setSpeed(8);
		anim_burst4[x].load(path, img_num);
		anim_burst4[x].setSpeed(8);
	}
	anim_burst5solo.load(path, img_num);
	anim_burst5solo.setSpeed(8);
	for (int x = 0; x < ATTACK_5_MAX; x++) {
		anim_burst5[x].load(path, img_num);
		anim_burst5[x].setSpeed(8);
	}
	anim_burst6solo.load(path, img_num);
	anim_burst6solo.setSpeed(8);
	for (int x = 0; x < ATTACK_6_MAX; x++) {
	//	anim_burst6[x].load(path, img_num);
	//	anim_burst6[x].setSpeed(8);
		anim6[x].load(path, img_num);
		anim6[x].setSpeed(8);
	}
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		anim_burst7[x].load(path, img_num);
		anim_burst7[x].setSpeed(8);
	}
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		anim_burst8[x].load(path, img_num);
		anim_burst8[x].setSpeed(8);
	}
	anim_burst9solo.load(path, img_num);
	anim_burst9solo.setSpeed(8);
	for (int x = 0; x < ATTACK_9_NUM; x++) {
		anim_burst9[x].load(path, img_num);
		anim_burst9[x].setSpeed(8);
	}
	anim_burst10solo.load(path, img_num);
	anim_burst10solo.setSpeed(8);
	//for (int x = 0; x < ATTACK_10_NUM; x++) {
		//anim_burst10[x].load(path, img_num);
		//anim_burst10[x].setSpeed(8);
	//}
	//　実験
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		anim10[x].load(path, img_num);
		anim10[x].setSpeed(8);
	}

	anim_burst11solo.load(path, img_num);
	anim_burst11solo.setSpeed(8);
	for (int x = 0; x < ATTACK_11_NUM; x++) {
		anim_burst11[x].load(path, img_num);
		anim_burst11[x].setSpeed(8);
	}
	anim_burst12.load(path, img_num);
	anim_burst12.setSpeed(8);

	// 画像の読み込み
	const char* tamapath = "data/animation/hit1";	// パス
//	const int	img_num = 8;						// 画像の枚数

	//　自機の弾エフェクト
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			tama[i][j].load(tamapath, img_num);
			tama[i][j].setSpeed(1);
		}
	}
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			r_shot[i][j].load(tamapath, img_num);
			r_shot[i][j].setSpeed(1);
		}
	}

}
void HitShotUpdate() {
	// =====================================================
	// 雑魚敵のＨＰが０になったとき
	// =====================================================
	// 攻撃１
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (attack_1_hp[x][p] <= 0) {
				if (display_handle_1_mode[x][p] == DISPLAY) {
					display_handle_1_mode[x][p] = HIDDEN;
					player_exp_count += EXP_LEVEL1;
					score += SCORE_LEVEL1;
					anim_burst1[x][p].play();
				}
			}
		}
	}
	// =====================================================
	// 攻撃２
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (attack_2_hp[x][p] <= 0) {
				//if (zako_attack_2_coordinate[x][p].y >= 14) {
					if (display_handle_2_mode[x][p] == DISPLAY) {
						display_handle_2_mode[x][p] = HIDDEN;
						player_exp_count += EXP_LEVEL1;
						score += SCORE_LEVEL1;
						anim_burst2[x][p].play();
					}
				//}
			}
		}
	}
	// =====================================================
	// 攻撃３
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		if (attack_3_hp[x] <= 0) {
			if (display_handle_3_mode[x] == DISPLAY) {
				display_handle_3_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				anim_burst3[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃４
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		if (attack_4_hp[x] <= 0) {
			if (display_handle_4_mode[x] == DISPLAY) {
				display_handle_4_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				anim_burst4[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃５
	if (attack_5_hp <= 0) {
		if (display_handle_5_c_mode == DISPLAY) {
			display_handle_5_c_mode = HIDDEN;
			player_exp_count += EXP_LEVEL2;
			score += SCORE_LEVEL2;
			anim_burst5solo.play();
		}
	}
	for (int x = 0; x < ATTACK_5_MAX; x++) {
		if (attack_zako_5_hp[x] <= 0) {
			if (display_handle_5_mode[x] == DISPLAY) {
				display_handle_5_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				anim_burst5[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃６
	if (attack_6_hp <= 0) {
		if (display_handle_6_c_mode == DISPLAY) {
			display_handle_6_c_mode = HIDDEN;
			player_exp_count += EXP_LEVEL2;
			score += SCORE_LEVEL2;
			anim_burst6solo.play();
		}
	}
	for (int x = 0; x < ATTACK_6_MAX; x++) {
		if (attack_zako_6_hp[x] <= 0) {
			if (display_handle_6_mode[x] == DISPLAY) {
				display_handle_6_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				//anim_burst6[x].play();
				anim6[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃７
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		if (attack_7_hp[x] <= 0) {
			if (display_handle_7_mode[x] == DISPLAY) {
				display_handle_7_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				anim_burst7[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃８
	for (int x = 0; x < ATTACK_8_MAX; x++) {
		if (attack_8_hp[x] <= 0) {
			if (display_handle_8_mode[x] == DISPLAY) {
				display_handle_8_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				anim_burst8[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃９
	if (attack_9_hp <= 0) {
		if (display_handle_9_nekomimi_mode == DISPLAY) {
			display_handle_9_nekomimi_mode = HIDDEN;
			player_exp_count += EXP_LEVEL2;
			score += SCORE_LEVEL2;
			anim_burst9solo.play();
		}
	}
	for (int x = 0; x < ATTACK_9_NUM; x++) {
		if (attack_zako_9_hp[x] <= 0) {
			if (display_handle_9_mode[x] == DISPLAY) {
				display_handle_9_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				anim_burst9[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃１０
	if (attack_10_hp <= 0) {
		if (display_handle_10_nekomimi_mode == DISPLAY) {
			display_handle_10_nekomimi_mode = HIDDEN;
			player_exp_count += EXP_LEVEL2;
			score += SCORE_LEVEL2;
			anim_burst10solo.play();
		}
	}
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		if (attack_zako_10_hp[x] <= 0) {
			if (display_handle_10_mode[x] == DISPLAY) {
				display_handle_10_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				//anim_burst10[x].play();
				anim10[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃１１
	if (attack_11_hp <= 0) {
		if (display_handle_11_nekomimi_mode == DISPLAY) {
			display_handle_11_nekomimi_mode = HIDDEN;
			player_exp_count += EXP_LEVEL2;
			score += SCORE_LEVEL2;
			anim_burst11solo.play();
		}
	}
	for (int x = 0; x < ATTACK_11_NUM; x++) {
		if (attack_zako_11_hp[x] <= 0) {
			if (display_handle_11_mode[x] == DISPLAY) {
				display_handle_11_mode[x] = HIDDEN;
				player_exp_count += EXP_LEVEL1;
				score += SCORE_LEVEL1;
				anim_burst11[x].play();
			}
		}
	}
	// =====================================================
	// 攻撃１２
	if (attack_12_hp <= 0) {
		if (display_handle_12_mode == DISPLAY) {
			display_handle_12_mode = HIDDEN;
			player_exp_count += EXP_LEVEL3;
			score += SCORE_LEVEL3;
			anim_burst12.play();
		}
	}
	// =====================================================
	//	ボス
	// =====================================================
	if (boss_hp < 0 && boss_stage_now == first) {
		score += BOSS_SCORE_LEVEL1;
		player_hp++;
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
	if (boss_hp < 0 && boss_stage_now == second) {
		score += BOSS_SCORE_LEVEL2;
		boss_hp = BOSS_MAX_HP3;
		boss_stage_now = third;
		boss_attack_count = 0;
		player_hp++;
	}
	if (boss_hp < 0 && boss_stage_now == third) {
		score += BOSS_SCORE_LEVEL3;
	//	boss_stage_now = 10;
		player_hp++;
		game_start_mode = Game_Clear;
	}

	// ==========================================================================================================
	//　当たり判定

	// =====================================================
	// 通常弾
	// =====================================================

	// =====================================================
	// 攻撃１の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_1_2_MAX; x++) {
				for (int p = 0; p < ATTACK_1_2__NUM; p++) {
					if (sway_mode[i][j] == MODE_MOVE) {
						if (display_handle_1_mode[x][p] == DISPLAY) {
							if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, zako_attack_1_coordinate[x][p].x, zako_attack_1_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE)) {
								sway_mode[i][j] = MODE_WAIT;
								//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
								attack_1_hp[x][p]--;
								tama[i][j].play();
							}
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃２の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_1_2_MAX; x++) {
				for (int p = 0; p < ATTACK_1_2__NUM; p++) {
					if (sway_mode[i][j] == MODE_MOVE) {
						if (display_handle_2_mode[x][p] == DISPLAY) {
						//	if (zako_attack_2_coordinate[x][p].y >= 12) {
								if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, zako_attack_2_coordinate[x][p].x, zako_attack_2_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE)) {
									sway_mode[i][j] = MODE_WAIT;
									//display_handle_2_mode[x][p] = HIDDEN; //　HP作って０にするで
									attack_2_hp[x][p]--;
									tama[i][j].play();
								}
						//	}
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃３の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_3_4_MAX; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_3_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, zako_attack_3_coordinate[x].x, zako_attack_3_coordinate[x].y, ATTACK_3_4_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_3_mode[x] = HIDDEN; //　HP作って０にするで
							attack_3_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃４の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_3_4_MAX; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_4_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, zako_attack_4_coordinate[x].x, zako_attack_4_coordinate[x].y, ATTACK_3_4_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_4_mode[x] = HIDDEN; //　HP作って０にするで
							attack_4_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃５の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {
				if (display_handle_5_c_mode == DISPLAY) {
					if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_5_coordinate.x, attack_5_coordinate.y, ATTACK_5_ROT_SIZE)) {
						sway_mode[i][j] = MODE_WAIT;
						//display_handle_5_c_mode = HIDDEN; //　HP作って０にするで
						attack_5_hp--;
						tama[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_5_MAX; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_5_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_5_zako_coordinate[x].x, attack_5_zako_coordinate[x].y, ATTACK_5_ZAKO_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_5_mode[x] = MODE_WAIT; //　HP作って０にするで
							attack_zako_5_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃６の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {
				if (display_handle_6_c_mode == DISPLAY) {
					if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, ATTACK_6_ROT_SIZE)) {
						sway_mode[i][j] = MODE_WAIT;
						//display_handle_6_c_mode = HIDDEN; //　HP作って０にするで
						attack_6_hp--;
						tama[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_6_MAX; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_6_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_6_zako_coordinate[x].x, attack_6_zako_coordinate[x].y, ATTACK_6_ZAKO_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_6_mode[x] = HIDDEN; //　HP作って０にするで
							attack_zako_6_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃７の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_7_MAX; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_7_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_7_zako_coordinate[x].x, attack_7_zako_coordinate[x].y, ATTACK_7_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_7_mode[x] = HIDDEN;
							attack_7_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃８の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_8_MAX; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_8_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_8_zako_coordinate[x].x, attack_8_zako_coordinate[x].y, ATTACK_8_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_8_mode[x] = HIDDEN;
							attack_8_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃９の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {
				if (display_handle_9_nekomimi_mode == DISPLAY) {
					if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, ATTACK_9_ROT_SIZE)) {
						sway_mode[i][j] = MODE_WAIT;
						//display_handle_9_nekomimi_mode = HIDDEN;
						attack_9_hp--;
						tama[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_9_NUM; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_9_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_9_zako_coordinate[x].x, attack_9_zako_coordinate[x].y, ATTACK_9_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_9_mode[x] = HIDDEN;
							attack_zako_9_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１０の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {
				if (display_handle_10_nekomimi_mode == DISPLAY) {
					if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, ATTACK_10_ROT_SIZE)) {
						sway_mode[i][j] = MODE_WAIT;
						//display_handle_10_nekomimi_mode = HIDDEN;
						attack_10_hp--;
						tama[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_10_NUM; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_10_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_10_zako_coordinate[x].x, attack_10_zako_coordinate[x].y, ATTACK_10_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_10_mode[x] = HIDDEN;
							attack_zako_10_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１１の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {
				if (display_handle_11_nekomimi_mode == DISPLAY) {
					if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, ATTACK_11_ROT_SIZE)) {
						sway_mode[i][j] = MODE_WAIT;
						//display_handle_11_nekomimi_mode = HIDDEN;
						attack_11_hp--;
						tama[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			for (int x = 0; x < ATTACK_11_NUM; x++) {
				if (sway_mode[i][j] == MODE_MOVE) {
					if (display_handle_11_mode[x] == DISPLAY) {
						if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_11_zako_coordinate[x].x, attack_11_zako_coordinate[x].y, ATTACK_11_ROT_SIZE)) {
							sway_mode[i][j] = MODE_WAIT;
							//display_handle_11_mode[x] = HIDDEN;
							attack_zako_11_hp[x]--;
							tama[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１２の敵と自機弾のヒット
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {
				if (display_handle_12_mode == DISPLAY) {
					if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, ATTACK_12_ROT_SIZE)) {
						sway_mode[i][j] = MODE_WAIT;
						//display_handle_12_mode = HIDDEN;
						attack_12_hp--;
						tama[i][j].play();
					}
				}
			}
		}
	}
	// =====================================================
	//	ボス
	// =====================================================
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {
				if (boss_mode == MODE_MOVE) {
					if (isHit(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, boss.x, boss.y, BOSS_ROT_SIZE)) {
						sway_mode[i][j] = MODE_WAIT;
						boss_hp--;
						score += BOSS_HIT_DAMAG;
						tama[i][j].play();
					}
				}
			}
		}
	}


	// =====================================================
	// 霊夢の弾
	// =====================================================
	
	// =====================================================
	// 攻撃１の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_1_2_MAX; x++) {
				for (int p = 0; p < ATTACK_1_2__NUM; p++) {
					if (hr_shot_mode[i][j] == MODE_MOVE) {
						if (display_handle_1_mode[x][p] == DISPLAY) {
							if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, zako_attack_1_coordinate[x][p].x, zako_attack_1_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE)) {
								hr_shot_mode[i][j] = MODE_WAIT;
								//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
								attack_1_hp[x][p]--;
								r_shot[i][j].play();
							}
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃２の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_1_2_MAX; x++) {
				for (int p = 0; p < ATTACK_1_2__NUM; p++) {
					if (hr_shot_mode[i][j] == MODE_MOVE) {
						if (display_handle_2_mode[x][p] == DISPLAY) {
							if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, zako_attack_2_coordinate[x][p].x, zako_attack_2_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE)) {
								hr_shot_mode[i][j] = MODE_WAIT;
								//display_handle_2_mode[x][p] = HIDDEN; //　HP作って０にするで
								attack_2_hp[x][p]--;
								r_shot[i][j].play();
							}
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃３の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_3_4_MAX; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_3_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, zako_attack_3_coordinate[x].x, zako_attack_3_coordinate[x].y, ATTACK_3_4_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_3_mode[x] = HIDDEN; //　HP作って０にするで
							attack_3_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃４の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_3_4_MAX; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_4_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, zako_attack_4_coordinate[x].x, zako_attack_4_coordinate[x].y, ATTACK_3_4_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_4_mode[x] = HIDDEN; //　HP作って０にするで
							attack_4_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃５の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_mode[i][j] == MODE_MOVE) {
				if (display_handle_5_c_mode == DISPLAY) {
					if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_5_coordinate.x, attack_5_coordinate.y, ATTACK_5_ROT_SIZE)) {
						hr_shot_mode[i][j] = MODE_WAIT;
						//display_handle_5_c_mode = HIDDEN; //　HP作って０にするで
						attack_5_hp--;
						r_shot[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_5_MAX; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_5_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_5_zako_coordinate[x].x, attack_5_zako_coordinate[x].y, ATTACK_5_ZAKO_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_5_mode[x] = MODE_WAIT; //　HP作って０にするで
							attack_zako_5_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃６の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_mode[i][j] == MODE_MOVE) {
				if (display_handle_6_c_mode == DISPLAY) {
					if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, ATTACK_6_ROT_SIZE)) {
						hr_shot_mode[i][j] = MODE_WAIT;
						//display_handle_6_c_mode = HIDDEN; //　HP作って０にするで
						attack_6_hp--;
						r_shot[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_6_MAX; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_6_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_6_zako_coordinate[x].x, attack_6_zako_coordinate[x].y, ATTACK_6_ZAKO_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_6_mode[x] = HIDDEN; //　HP作って０にするで
							attack_zako_6_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃７の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_7_MAX; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_7_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_7_zako_coordinate[x].x, attack_7_zako_coordinate[x].y, ATTACK_7_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_7_mode[x] = HIDDEN;
							attack_7_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃８の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_8_MAX; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_8_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_8_zako_coordinate[x].x, attack_8_zako_coordinate[x].y, ATTACK_8_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_8_mode[x] = HIDDEN;
							attack_8_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃９の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_mode[i][j] == MODE_MOVE) {
				if (display_handle_9_nekomimi_mode == DISPLAY) {
					if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, ATTACK_9_ROT_SIZE)) {
						hr_shot_mode[i][j] = MODE_WAIT;
						//display_handle_9_nekomimi_mode = HIDDEN;
						attack_9_hp--;
						r_shot[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_9_NUM; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_9_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_9_zako_coordinate[x].x, attack_9_zako_coordinate[x].y, ATTACK_9_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_9_mode[x] = HIDDEN;
							attack_zako_9_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１０の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_mode[i][j] == MODE_MOVE) {
				if (display_handle_10_nekomimi_mode == DISPLAY) {
					if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, ATTACK_10_ROT_SIZE)) {
						hr_shot_mode[i][j] = MODE_WAIT;
						//display_handle_10_nekomimi_mode = HIDDEN;
						attack_10_hp--;
						r_shot[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_10_NUM; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_10_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_10_zako_coordinate[x].x, attack_10_zako_coordinate[x].y, ATTACK_10_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_10_mode[x] = HIDDEN;
							attack_zako_10_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１１の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_mode[i][j] == MODE_MOVE) {
				if (display_handle_11_nekomimi_mode == DISPLAY) {
					if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, ATTACK_11_ROT_SIZE)) {
						hr_shot_mode[i][j] = MODE_WAIT;
						//display_handle_11_nekomimi_mode = HIDDEN;
						attack_11_hp--;
						r_shot[i][j].play();
					}
				}
			}
		}
	}

	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			for (int x = 0; x < ATTACK_11_NUM; x++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {
					if (display_handle_11_mode[x] == DISPLAY) {
						if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_11_zako_coordinate[x].x, attack_11_zako_coordinate[x].y, ATTACK_11_ROT_SIZE)) {
							hr_shot_mode[i][j] = MODE_WAIT;
							//display_handle_11_mode[x] = HIDDEN;
							attack_zako_11_hp[x]--;
							r_shot[i][j].play();
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１２の敵と霊夢の弾のヒット
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_mode[i][j] == MODE_MOVE) {
				if (display_handle_12_mode == DISPLAY) {
					if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, ATTACK_12_ROT_SIZE)) {
						hr_shot_mode[i][j] = MODE_WAIT;
						//display_handle_12_mode = HIDDEN;
						attack_12_hp--;
						r_shot[i][j].play();
					}
				}
			}
		}
	}
	// =====================================================
	//	ボス
	// =====================================================
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_mode[i][j] == MODE_MOVE) {
				if (boss_mode == MODE_MOVE) {
					if (isHit(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, boss.x, boss.y, BOSS_ROT_SIZE)) {
						hr_shot_mode[i][j] = MODE_WAIT;
						boss_hp--;
						score += BOSS_HIT_DAMAG;
						r_shot[i][j].play();
					}
				}
			}
		}
	}

	// =====================================================
	// 魔理沙の弾
	// =====================================================

	// =====================================================
	// 攻撃１の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_1_2_MAX; x++) {
			for (int p = 0; p < ATTACK_1_2__NUM; p++) {
				if (km_shot_mode == MODE_MOVE) {
					if (display_handle_1_mode[x][p] == DISPLAY) {
						if (CheckHitBoxCircle(zako_attack_1_coordinate[x][p].x, zako_attack_1_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
							km_hit_count++;
							if (km_hit_count >= KM_COUNT) {
								km_hit_count = 0;
								attack_1_hp[x][p]--;
							}
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃２の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_1_2_MAX; x++) {
			for (int p = 0; p < ATTACK_1_2__NUM; p++) {
				if (km_shot_mode == MODE_MOVE) {
					if (display_handle_2_mode[x][p] == DISPLAY) {
						if (CheckHitBoxCircle(zako_attack_2_coordinate[x][p].x, zako_attack_2_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
							km_hit_count++;
							if (km_hit_count >= KM_COUNT) {
								km_hit_count = 0;
								attack_2_hp[x][p]--;
							}
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃３の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_3_4_MAX; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_3_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(zako_attack_3_coordinate[x].x, zako_attack_3_coordinate[x].y, ATTACK_3_4_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_3_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃４の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_3_4_MAX; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_4_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(zako_attack_4_coordinate[x].x, zako_attack_4_coordinate[x].y, ATTACK_3_4_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_4_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃５の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		if (km_shot_mode == MODE_MOVE) {
			if (display_handle_5_c_mode == DISPLAY) {
				if (CheckHitBoxCircle(attack_5_coordinate.x, attack_5_coordinate.y, ATTACK_5_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
					km_hit_count++;
					if (km_hit_count >= KM_COUNT) {
						km_hit_count = 0;
						attack_5_hp--;
					}
				}
			}
		}
	}


	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_5_MAX; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_5_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(attack_5_zako_coordinate[x].x, attack_5_zako_coordinate[x].y, ATTACK_5_ZAKO_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_zako_5_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃６の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		if (km_shot_mode == MODE_MOVE) {
			if (display_handle_6_c_mode == DISPLAY) {
				if (CheckHitBoxCircle(attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, ATTACK_6_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
					km_hit_count++;
					if (km_hit_count >= KM_COUNT) {
						km_hit_count = 0;
						attack_6_hp--;
					}
				}
			}
		}
	}


	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_6_MAX; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_6_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(attack_6_zako_coordinate[x].x, attack_6_zako_coordinate[x].y, ATTACK_6_ZAKO_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_zako_6_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃７の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_7_MAX; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_7_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(attack_7_zako_coordinate[x].x, attack_7_zako_coordinate[x].y, ATTACK_7_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_7_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃８の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_8_MAX; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_8_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(attack_8_zako_coordinate[x].x, attack_8_zako_coordinate[x].y, ATTACK_8_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_8_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃９の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		if (km_shot_mode == MODE_MOVE) {
			if (display_handle_9_nekomimi_mode == DISPLAY) {
				if (CheckHitBoxCircle(attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, ATTACK_9_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
					km_hit_count++;
					if (km_hit_count >= KM_COUNT) {
						km_hit_count = 0;
						attack_9_hp--;
					}
				}
			}
		}
	}

	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_9_NUM; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_9_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(attack_9_zako_coordinate[x].x, attack_9_zako_coordinate[x].y, ATTACK_9_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_zako_9_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１０の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		if (km_shot_mode == MODE_MOVE) {
			if (display_handle_10_nekomimi_mode == DISPLAY) {
				if (CheckHitBoxCircle(attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, ATTACK_10_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
					km_hit_count++;
					if (km_hit_count >= KM_COUNT) {
						km_hit_count = 0;
						attack_10_hp--;
					}
				}
			}
		}
	}

	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_10_NUM; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_10_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(attack_10_zako_coordinate[x].x, attack_10_zako_coordinate[x].y, ATTACK_10_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_zako_10_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１１の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		if (km_shot_mode == MODE_MOVE) {
			if (display_handle_11_nekomimi_mode == DISPLAY) {
				if (CheckHitBoxCircle(attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, ATTACK_11_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
					km_hit_count++;
					if (km_hit_count >= KM_COUNT) {
						km_hit_count = 0;
						attack_11_hp--;
					}
				}
			}
		}
	}

	for (int i = 0; i < KM_SHOT_MAX; i++) {
		for (int x = 0; x < ATTACK_11_NUM; x++) {
			if (km_shot_mode == MODE_MOVE) {
				if (display_handle_11_mode[x] == DISPLAY) {
					if (CheckHitBoxCircle(attack_11_zako_coordinate[x].x, attack_11_zako_coordinate[x].y, ATTACK_11_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							attack_zako_11_hp[x]--;
						}
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１２の敵と魔理沙のビーム
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		if (km_shot_mode == MODE_MOVE) {
			if (display_handle_12_mode == DISPLAY) {
				if (CheckHitBoxCircle(attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, ATTACK_12_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
					km_hit_count++;
					if (km_hit_count >= KM_COUNT) {
						km_hit_count = 0;
						attack_12_hp--;
					}
				}
			}
		}
	}
	// =====================================================
	//	ボス
	// =====================================================
	for (int i = 0; i < KM_SHOT_MAX; i++) {
		if (km_shot_mode == MODE_MOVE) {
			if (display_handle_12_mode == DISPLAY) {
				if (boss_mode == MODE_MOVE) {
					if (CheckHitBoxCircle(boss.x, boss.y, BOSS_ROT_SIZE, km_shot_coordinate[i].x, km_shot_height, km_shot_width, km_shot_coordinate[i].y - km_shot_height)) {
						km_hit_count++;
						if (km_hit_count >= KM_COUNT) {
							km_hit_count = 0;
							boss_hp--;
							score += BOSS_HIT_DAMAG;
						}
					}
				}
			}
		}
	}
	// ==========================================================================================================
	// スペルカード（霊夢）
	switch (player_character_mode)
	{
	case REIMU:
		
		// =====================================================
		// 攻撃１の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_1_2_MAX; x++) {
			for (int p = 0; p < ATTACK_1_2__NUM; p++) {
				if (display_handle_1_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, zako_attack_1_shot_coordinate[x][p].x, zako_attack_1_shot_coordinate[x][p].y, ATTACK_1_2_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_1_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃２の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_1_2_MAX; x++) {
			for (int p = 0; p < ATTACK_1_2__NUM; p++) {
				if (display_handle_2_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, zako_attack_2_shot_coordinate[x][p].x, zako_attack_2_shot_coordinate[x][p].y, ATTACK_1_2_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_2_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃３の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_3_4_MAX; x++) {
			for (int p = 0; p < ATTACK_3_4_NUM; p++) {
				if (display_handle_3_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, zako_attack_3_shot_coordinate[x][p].x, zako_attack_3_shot_coordinate[x][p].y, ATTACK_3_4_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_3_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃４の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_3_4_MAX; x++) {
			for (int p = 0; p < ATTACK_3_4_NUM; p++) {
				if (display_handle_4_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, zako_attack_4_shot_coordinate[x][p].x, zako_attack_4_shot_coordinate[x][p].y, ATTACK_3_4_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_4_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃５の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_5_SHOT_NUM; x++) {
			if (display_handle_5_c_shot_mode[x] == DISPLAY) {
				if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_5_shot_coordinate[x].x, attack_5_shot_coordinate[x].y, ATTACK_5_SHOT_ROT_SIZE)) {
					//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
					display_handle_5_c_shot_mode[x] = HIDDEN;
				}
			}
		}
		for (int x = 0; x < ATTACK_5_MAX; x++) {
			for (int p = 0; p < ATTACK_5_NUM; p++) {
				if (display_handle_5_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_5_zako_shot_coordinate[x][p].x, attack_5_zako_shot_coordinate[x][p].y, ATTACK_5_ZAKO_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_5_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < NEKOMIMI_MAX; x++) {
			for (int p = 0; p < NEKOMIMI_NUM; p++) {
				if (display_handle_5_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_5_nekomimi_attack_shot_coordinate[x][p].x, attack_5_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_5_NEKOMIMI_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_5_nekomimi_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃６の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_6_SHOT_NUM; x++) {
			if (display_handle_6_c_shot_mode[x] == DISPLAY) {
				if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_6_teki_shot_coordinate[x].x, attack_6_teki_shot_coordinate[x].y, ATTACK_6_SHOT_ROT_SIZE)) {
					//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
					display_handle_6_c_shot_mode[x] = HIDDEN;
				}
			}
		}
		for (int x = 0; x < ATTACK_6_MAX; x++) {
			for (int p = 0; p < ATTACK_6_NUM; p++) {
				if (display_handle_6_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_6_zako_shot_coordinate[x][p].x, attack_6_zako_shot_coordinate[x][p].y, ATTACK_6_ZAKO_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_6_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < NEKOMIMI_MAX; x++) {
			for (int p = 0; p < NEKOMIMI_NUM; p++) {
				if (display_handle_6_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_6_nekomimi_attack_shot_coordinate[x][p].x, attack_6_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_6_NEKOMIMI_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_6_nekomimi_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃７の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_7_MAX; x++) {
			for (int p = 0; p < ATTACK_7_NUM; p++) {
				if (display_handle_7_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_7_zako_shot_coordinate[x][p].x, attack_7_zako_shot_coordinate[x][p].y, ATTACK_7_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_7_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃８の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_8_MAX; x++) {
			for (int p = 0; p < ATTACK_8_NUM; p++) {
				if (display_handle_8_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_8_zako_shot_coordinate[x][p].x, attack_8_zako_shot_coordinate[x][p].y, ATTACK_8_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_8_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃９の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_9_NEKOMIMI_MAX; x++) {
			for (int p = 0; p < ATTACK_9_NEKOMIMI_NUM; p++) {
				if (display_handle_9_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_9_nekomimi_attack_shot_coordinate[x][p].x, attack_9_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_9_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_9_nekomimi_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < ATTACK_9_NUM; x++) {
			for (int p = 0; p < ATTACK_9_MAX; p++) {
				if (display_handle_9_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_9_zako_shot_coordinate[x][p].x, attack_9_zako_shot_coordinate[x][p].y, ATTACK_9_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_9_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃１０の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_10_NEKOMIMI_MAX; x++) {
			for (int p = 0; p < ATTACK_10_NEKOMIMI_NUM; p++) {
				if (display_handle_10_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_10_nekomimi_attack_shot_coordinate[x][p].x, attack_10_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_10_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_10_nekomimi_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < ATTACK_10_NUM; x++) {
			for (int p = 0; p < ATTACK_10_MAX; p++) {
				if (display_handle_10_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_10_zako_shot_coordinate[x][p].x, attack_10_zako_shot_coordinate[x][p].y, ATTACK_10_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_10_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃１１の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_11_NEKOMIMI_MAX; x++) {
			for (int p = 0; p < ATTACK_11_NEKOMIMI_NUM; p++) {
				if (display_handle_11_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_11_nekomimi_attack_shot_coordinate[x][p].x, attack_11_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_11_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_11_nekomimi_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < ATTACK_11_NUM; x++) {
			for (int p = 0; p < ATTACK_11_MAX; p++) {
				if (display_handle_11_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_11_zako_shot_coordinate[x][p].x, attack_11_zako_shot_coordinate[x][p].y, ATTACK_11_SHOT_ROT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_11_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		// 攻撃１２の敵の弾と霊夢のスペカ
		for (int x = 0; x < ATTACK_12_NEKOMIMI_MAX; x++) {
			for (int p = 0; p < ATTACK_12_NEKOMIMI_NUM; p++) {
				if (display_handle_12_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_12_nekomimi_attack_shot_coordinate[x][p].x, attack_12_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_12_SHOT_ROT)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_12_nekomimi_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < ATTACK_12_SHOT_MAX; x++) {
			if (display_handle_12_shot_mode[x] == DISPLAY) {
				if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, attack_12_circle_shot[x].x, attack_12_circle_shot[x].y, ATTACK_12_SHOT_ROT)) {
					//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
					display_handle_12_shot_mode[x] = HIDDEN;
				}
			}
		}

		// ==========================================================================================================
		//	ボス
		// =====================================================

		// =====================================================
		//　ステージ１攻撃１
		// =====================================================

		// =====================================================
		//　時計回り１
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_big[x][p][0] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_big_left_1_shot_shot[x][p].x, boss_big_left_1_shot_shot[x][p].y, BOSS_BIG_LEFT_1_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_big[x][p][0] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_small[x][p][0] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_small_left_1_shot_shot[x][p].x, boss_small_left_1_shot_shot[x][p].y, BOSS_SMALL_LEFT_1_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_small[x][p][0] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		//　反時計回り１
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_big[x][p][1] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_big_right_1_shot_shot[x][p].x, boss_big_right_1_shot_shot[x][p].y, BOSS_BIG_RIGHT_1_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_big[x][p][1] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_small[x][p][1] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_small_right_1_shot_shot[x][p].x, boss_small_right_1_shot_shot[x][p].y, BOSS_SMALL_RIGHT_1_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_small[x][p][1] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		//　時計回り２
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_big[x][p][2] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_big_left_2_shot_shot[x][p].x, boss_big_left_2_shot_shot[x][p].y, BOSS_BIG_LEFT_2_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_big[x][p][2] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_small[x][p][2] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_small_left_2_shot_shot[x][p].x, boss_small_left_2_shot_shot[x][p].y, BOSS_SMALL_LEFT_2_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_small[x][p][2] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		//　反時計回り２
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_big[x][p][3] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_big_right_2_shot_shot[x][p].x, boss_big_right_2_shot_shot[x][p].y, BOSS_BIG_RIGHT_2_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_big[x][p][3] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_small[x][p][3] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_small_right_2_shot_shot[x][p].x, boss_small_right_2_shot_shot[x][p].y, BOSS_SMALL_RIGHT_2_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_small[x][p][3] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		//　時計回り３
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_big[x][p][4] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_big_left_3_shot_shot[x][p].x, boss_big_left_3_shot_shot[x][p].y, BOSS_BIG_LEFT_3_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_big[x][p][4] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_small[x][p][4] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_small_left_3_shot_shot[x][p].x, boss_small_left_3_shot_shot[x][p].y, BOSS_SMALL_LEFT_3_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_small[x][p][4] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		//　反時計回り３
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_big[x][p][5] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_big_right_3_shot_shot[x][p].x, boss_big_right_3_shot_shot[x][p].y, BOSS_BIG_RIGHT_3_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_big[x][p][5] = HIDDEN;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (display_handle_boss_shot_mode_small[x][p][5] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_small_right_3_shot_shot[x][p].x, boss_small_right_3_shot_shot[x][p].y, BOSS_SMALL_RIGHT_3_SHOT_SIZE)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_boss_shot_mode_small[x][p][5] = HIDDEN;
					}
				}
			}
		}
		// =====================================================
		//　ステージ１攻撃２
		// =====================================================
		for (int x = 0; x < BOSS_RAND_NUM1; x++) {
			if (display_handle_snow_1_shot_mode[x] == DISPLAY) {
				if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_rand_shot_1[x].x, boss_rand_shot_1[x].y, BOSS_RAND_SIZE1)) {
					//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
					display_handle_snow_1_shot_mode[x] = HIDDEN;
				}
			}
		}
		for (int x = 0; x < BOSS_RAND_NUM2; x++) {
			if (display_handle_snow_2_shot_mode[x] == DISPLAY) {
				if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_rand_shot_2[x].x, boss_rand_shot_2[x].y, BOSS_RAND_SIZE2)) {
					//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
					display_handle_snow_2_shot_mode[x] = HIDDEN;
				}
			}
		}
		for (int x = 0; x < BOSS_RAND_NUM3; x++) {
			if (display_handle_snow_3_shot_mode[x] == DISPLAY) {
				if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_rand_shot_3[x].x, boss_rand_shot_3[x].y, BOSS_RAND_SIZE3)) {
					//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
					display_handle_snow_3_shot_mode[x] = HIDDEN;
				}
			}
		}
		// =====================================================
		//　ステージ２
		// =====================================================
		for (int x = 0; x < BOSS_ROTATE_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
				for (int t = 0; t < BOSS_ROTATE_NUMBER; t++) {
					if (display_handle_rotate_shot_mode[x][p][t] == DISPLAY) {
						if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_rotate_shot_coordinate[x][p][t].x, boss_rotate_shot_coordinate[x][p][t].y, BOSS_ROTATE_SHOT_SIZE)) {
							//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
							display_handle_rotate_shot_mode[x][p][t] = HIDDEN;
						}
					}
				}
			}
		}
		// =====================================================
		//　ステージ３
		// =====================================================
		//　赤
		for (int x = 0; x < BOSS_FURAN_RED_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_FURAN_RED_NUM_MAX; p++) {
				if (display_handle_furan_red_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_furan_red_circle_shot[x][p].x, boss_furan_red_circle_shot[x][p].y, BOSS_FURAN_RED_SHOT_R)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_furan_red_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		//　青
		for (int x = 0; x < BOSS_FURAN_BLUE_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_FURAN_BLUE_NUM_MAX; p++) {
				for (int t = 0; t < BOSS_FURAN_BLUE_LB; t++) {
					if (display_handle_furan_blue_shot_mode[x][p][t] == DISPLAY) {
						if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_furan_blue_circle_shot[x][p][t].x, boss_furan_blue_circle_shot[x][p][t].y, BOSS_FURAN_BLUE_SHOT_R)) {
							//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
							display_handle_furan_blue_shot_mode[x][p][t] = HIDDEN;
						}
					}
				}
			}
		}
		//　紫
		for (int x = 0; x < BOSS_FURAN_PURPLE_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_FURAN_PURPLE_NUM_MAX; p++) {
				if (display_handle_furan_purple_shot_mode[x][p] == DISPLAY) {
					if (isHit(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, boss_furan_purple_circle_shot[x][p].x, boss_furan_purple_circle_shot[x][p].y, BOSS_FURAN_PURPLE_SHOT_R)) {
						//display_handle_1_mode[x][p] = HIDDEN; //　HP作って０にするで
						display_handle_furan_purple_shot_mode[x][p] = HIDDEN;
					}
				}
			}
		}
		break;
		// ==========================================================================================================
		// スペルカード（魔理沙）
	case MARISA:

		// =====================================================
		// 攻撃１の敵の弾と魔理沙のスペカ
		for (int x = 0; x < ATTACK_1_2_MAX; x++) {
			for (int p = 0; p < ATTACK_1_2__NUM; p++) {
				if (display_handle_1_mode[x][p] == DISPLAY) {
					if (CheckHitBoxCircle(zako_attack_1_coordinate[x][p].x, zako_attack_1_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
						km_spellcard_hit_count++;
						if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
							km_spellcard_hit_count = 0;
							attack_1_hp[x][p]--;
						}
					}
				}
			}
		}
		// =====================================================
		// 攻撃２の敵の弾と魔理沙のスペカ
		for (int x = 0; x < ATTACK_1_2_MAX; x++) {
			for (int p = 0; p < ATTACK_1_2__NUM; p++) {
				if (display_handle_2_mode[x][p] == DISPLAY) {
					if (CheckHitBoxCircle(zako_attack_2_coordinate[x][p].x, zako_attack_2_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
						km_spellcard_hit_count++;
						if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
							km_spellcard_hit_count = 0;
							attack_2_hp[x][p]--;
						}
					}
				}
			}
		}
		// =====================================================
		// 攻撃３の敵の弾と魔理沙のスペカ
		for (int x = 0; x < ATTACK_3_4_MAX; x++) {
			if (display_handle_3_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(zako_attack_3_coordinate[x].x, zako_attack_3_coordinate[x].y, ATTACK_3_4_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_3_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃４の敵の弾と魔理沙のスペカ
		for (int x = 0; x < ATTACK_3_4_MAX; x++) {
			if (display_handle_4_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(zako_attack_4_coordinate[x].x, zako_attack_4_coordinate[x].y, ATTACK_3_4_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_4_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃５の敵の弾と魔理沙のスペカ
		if (display_handle_5_c_mode == DISPLAY) {
			if (CheckHitBoxCircle(attack_5_coordinate.x, attack_5_coordinate.y, ATTACK_5_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
				km_spellcard_hit_count++;
				if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
					km_spellcard_hit_count = 0;
					attack_5_hp--;
				}
			}
		}

		for (int x = 0; x < ATTACK_5_MAX; x++) {
			if (display_handle_5_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(attack_5_zako_coordinate[x].x, attack_5_zako_coordinate[x].y, ATTACK_5_ZAKO_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_zako_5_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃６の敵の弾と魔理沙のスペカ
		if (display_handle_6_c_mode == DISPLAY) {
			if (CheckHitBoxCircle(attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, ATTACK_6_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
				km_spellcard_hit_count++;
				if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
					km_spellcard_hit_count = 0;
					attack_6_hp--;
				}
			}
		}

		for (int x = 0; x < ATTACK_6_MAX; x++) {
			if (display_handle_6_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(attack_6_zako_coordinate[x].x, attack_6_zako_coordinate[x].y, ATTACK_6_ZAKO_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_zako_6_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃７の敵の弾と魔理沙のスペカ
		for (int x = 0; x < ATTACK_7_MAX; x++) {
			if (display_handle_7_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(attack_7_zako_coordinate[x].x, attack_7_zako_coordinate[x].y, ATTACK_7_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_7_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃８の敵の弾と魔理沙のスペカ
		for (int x = 0; x < ATTACK_8_MAX; x++) {
			if (display_handle_8_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(attack_8_zako_coordinate[x].x, attack_8_zako_coordinate[x].y, ATTACK_8_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_8_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃９の敵の弾と魔理沙のスペカ
		if (display_handle_9_nekomimi_mode == DISPLAY) {
			if (CheckHitBoxCircle(attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, ATTACK_9_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
				km_spellcard_hit_count++;
				if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
					km_spellcard_hit_count = 0;
					attack_9_hp--;
				}
			}
		}

		for (int x = 0; x < ATTACK_9_NUM; x++) {
			if (display_handle_9_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(attack_9_zako_coordinate[x].x, attack_9_zako_coordinate[x].y, ATTACK_9_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_zako_9_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃１０の敵の弾と魔理沙のスペカ
		if (display_handle_10_nekomimi_mode == DISPLAY) {
			if (CheckHitBoxCircle(attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, ATTACK_10_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
				km_spellcard_hit_count++;
				if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
					km_spellcard_hit_count = 0;
					attack_10_hp--;
				}
			}
		}

		for (int x = 0; x < ATTACK_10_NUM; x++) {
			if (display_handle_10_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(attack_10_zako_coordinate[x].x, attack_10_zako_coordinate[x].y, ATTACK_10_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_zako_10_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃１１の敵の弾と魔理沙のスペカ
		if (display_handle_11_nekomimi_mode == DISPLAY) {
			if (CheckHitBoxCircle(attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, ATTACK_11_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
				km_spellcard_hit_count++;
				if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
					km_spellcard_hit_count = 0;
					attack_11_hp--;
				}
			}
		}

		for (int x = 0; x < ATTACK_11_NUM; x++) {
			if (display_handle_11_mode[x] == DISPLAY) {
				if (CheckHitBoxCircle(attack_11_zako_coordinate[x].x, attack_11_zako_coordinate[x].y, ATTACK_11_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						attack_zako_11_hp[x]--;
					}
				}
			}
		}
		// =====================================================
		// 攻撃１２の敵の弾と魔理沙のスペカ
		if (display_handle_12_mode == DISPLAY) {
			if (CheckHitBoxCircle(attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, ATTACK_12_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
				km_spellcard_hit_count++;
				if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
					km_spellcard_hit_count = 0;
					attack_12_hp--;
				}
			}
		}
		// =====================================================
		//	ボス
		// =====================================================
		if (spellcard_shot_mode == Spellcard_MOVE) {
			if (boss_mode == MODE_MOVE) {
				if (CheckHitBoxCircle(boss.x, boss.y, BOSS_ROT_SIZE, km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, km_spellcard_coordinate.x, -km_spellcard_coordinate.y)) {
					km_spellcard_hit_count++;
					if (km_spellcard_hit_count >= KM_SPELLCARD_COUNT) {
						km_spellcard_hit_count = 0;
						boss_hp--;
						score += BOSS_HIT_DAMAG;
					}
				}
			}
		}
		break;
	}
	// ==========================================================================================================
	// プレイヤーの当たり判定
	// =====================================================
	// 攻撃１の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_1_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_1_shot_coordinate[x][p].x, zako_attack_1_shot_coordinate[x][p].y, ATTACK_1_2_SHOT_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃２の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_2_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_2_shot_coordinate[x][p].x, zako_attack_2_shot_coordinate[x][p].y, ATTACK_1_2_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃３の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		for (int p = 0; p < ATTACK_3_4_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_3_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_3_shot_coordinate[x][p].x, zako_attack_3_shot_coordinate[x][p].y, ATTACK_3_4_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃４の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		for (int p = 0; p < ATTACK_3_4_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_4_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_4_shot_coordinate[x][p].x, zako_attack_4_shot_coordinate[x][p].y, ATTACK_3_4_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃５の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_5_SHOT_NUM; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_5_c_shot_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_5_shot_coordinate[x].x, attack_5_shot_coordinate[x].y, ATTACK_5_SHOT_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	for (int x = 0; x < ATTACK_5_MAX; x++) {
		for (int p = 0; p < ATTACK_5_MAX; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_5_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_5_zako_shot_coordinate[x][p].x, attack_5_zako_shot_coordinate[x][p].y, ATTACK_5_ZAKO_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	for (int x = 0; x < NEKOMIMI_MAX; x++) {
		for (int p = 0; p < NEKOMIMI_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_5_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_5_nekomimi_attack_shot_coordinate[x][p].x, attack_5_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_5_NEKOMIMI_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃６の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_6_SHOT_NUM; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_6_c_shot_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_6_teki_shot_coordinate[x].x, attack_6_teki_shot_coordinate[x].y, ATTACK_6_SHOT_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	for (int x = 0; x < ATTACK_6_MAX; x++) {
		for (int p = 0; p < ATTACK_6_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_6_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_6_zako_shot_coordinate[x][p].x, attack_6_zako_shot_coordinate[x][p].y, ATTACK_6_ZAKO_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	for (int x = 0; x < NEKOMIMI_MAX; x++) {
		for (int p = 0; p < NEKOMIMI_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_6_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_6_nekomimi_attack_shot_coordinate[x][p].x, attack_6_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_6_NEKOMIMI_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃７の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		for (int p = 0; p < ATTACK_7_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_7_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_7_zako_shot_coordinate[x][p].x, attack_7_zako_shot_coordinate[x][p].y, ATTACK_7_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃８の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_8_MAX; x++) {
		for (int p = 0; p < ATTACK_8_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_8_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_8_zako_shot_coordinate[x][p].x, attack_8_zako_shot_coordinate[x][p].y, ATTACK_8_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃９の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_9_NEKOMIMI_MAX; x++) {
		for (int p = 0; p < ATTACK_9_NEKOMIMI_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_9_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_9_nekomimi_attack_shot_coordinate[x][p].x, attack_9_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_9_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	for (int x = 0; x < ATTACK_9_NUM; x++) {
		for (int p = 0; p < ATTACK_9_MAX; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_9_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_9_zako_shot_coordinate[x][p].x, attack_9_zako_shot_coordinate[x][p].y, ATTACK_9_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１０の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_10_NEKOMIMI_MAX; x++) {
		for (int p = 0; p < ATTACK_10_NEKOMIMI_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_10_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_10_nekomimi_attack_shot_coordinate[x][p].x, attack_10_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_10_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		for (int p = 0; p < ATTACK_10_MAX; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_10_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_10_zako_shot_coordinate[x][p].x, attack_10_zako_shot_coordinate[x][p].y, ATTACK_10_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１１の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_11_NEKOMIMI_MAX; x++) {
		for (int p = 0; p < ATTACK_11_NEKOMIMI_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_11_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_11_nekomimi_attack_shot_coordinate[x][p].x, attack_11_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_11_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	for (int x = 0; x < ATTACK_11_NUM; x++) {
		for (int p = 0; p < ATTACK_11_MAX; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_11_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_11_zako_shot_coordinate[x][p].x, attack_11_zako_shot_coordinate[x][p].y, ATTACK_11_SHOT_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃１２の敵の弾とプレイヤー
	for (int x = 0; x < ATTACK_12_NEKOMIMI_MAX; x++) {
		for (int p = 0; p < ATTACK_12_NEKOMIMI_NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_12_nekomimi_shot_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_12_nekomimi_attack_shot_coordinate[x][p].x, attack_12_nekomimi_attack_shot_coordinate[x][p].y, ATTACK_12_SHOT_ROT)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	for (int x = 0; x < ATTACK_12_SHOT_MAX; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_12_shot_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_12_circle_shot[x].x, attack_12_circle_shot[x].y, ATTACK_12_SHOT_ROT)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	//	ボス
	// =====================================================
	if (boss_stage_now == first) {
		// =====================================================
		//　時計回り１
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_big[x][p][0] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_big_left_1_shot_shot[x][p].x, boss_big_left_1_shot_shot[x][p].y, BOSS_BIG_LEFT_1_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_small[x][p][0] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_left_1_shot_shot[x][p].x, boss_small_left_1_shot_shot[x][p].y, BOSS_SMALL_LEFT_1_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		// =====================================================
		//　反時計回り１
		for (int x = 0; x < BOSS_BIG_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_1_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_big[x][p][1] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_big_right_1_shot_shot[x][p].x, boss_big_right_1_shot_shot[x][p].y, BOSS_BIG_RIGHT_1_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_1_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_1_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_small[x][p][1] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_right_1_shot_shot[x][p].x, boss_small_right_1_shot_shot[x][p].y, BOSS_SMALL_RIGHT_1_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		// =====================================================
		//　時計回り２
		for (int x = 0; x < BOSS_BIG_LEFT_2_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_2_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_big[x][p][2] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_big_left_2_shot_shot[x][p].x, boss_big_left_2_shot_shot[x][p].y, BOSS_BIG_LEFT_2_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_2_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_2_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_small[x][p][2] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_left_2_shot_shot[x][p].x, boss_small_left_2_shot_shot[x][p].y, BOSS_SMALL_LEFT_2_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		// =====================================================
		//　反時計回り２
		for (int x = 0; x < BOSS_BIG_LEFT_2_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_2_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_big[x][p][3] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_big_right_2_shot_shot[x][p].x, boss_big_right_2_shot_shot[x][p].y, BOSS_BIG_RIGHT_2_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_2_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_2_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_small[x][p][3] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_right_2_shot_shot[x][p].x, boss_small_right_2_shot_shot[x][p].y, BOSS_SMALL_RIGHT_2_SHOT_SIZE)) {
							//DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		// =====================================================
		//　時計回り３
		for (int x = 0; x < BOSS_BIG_LEFT_3_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_2_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_big[x][p][4] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_big_left_3_shot_shot[x][p].x, boss_big_left_3_shot_shot[x][p].y, BOSS_BIG_LEFT_3_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_3_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_3_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_small[x][p][4] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_left_3_shot_shot[x][p].x, boss_small_left_3_shot_shot[x][p].y, BOSS_SMALL_LEFT_3_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		// =====================================================
		//　反時計回り３
		for (int x = 0; x < BOSS_BIG_LEFT_3_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_BIG_LEFT_3_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_big[x][p][5] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_big_right_3_shot_shot[x][p].x, boss_big_right_3_shot_shot[x][p].y, BOSS_BIG_RIGHT_3_SHOT_SIZE)) {
							//DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_SMALL_LEFT_3_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_SMALL_LEFT_3_SHOT_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_boss_shot_mode_small[x][p][5] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_right_3_shot_shot[x][p].x, boss_small_right_3_shot_shot[x][p].y, BOSS_SMALL_RIGHT_3_SHOT_SIZE)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		// ==========================================================================================================
		//　ステージ１攻撃２
		for (int x = 0; x < BOSS_RAND_NUM1; x++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_snow_1_shot_mode[x] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_rand_shot_1[x].x, boss_rand_shot_1[x].y, BOSS_RAND_SIZE1)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_RAND_NUM2; x++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_snow_2_shot_mode[x] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_rand_shot_2[x].x, boss_rand_shot_2[x].y, BOSS_RAND_SIZE2)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
		for (int x = 0; x < BOSS_RAND_NUM3; x++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_snow_3_shot_mode[x] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_rand_shot_3[x].x, boss_rand_shot_3[x].y, BOSS_RAND_SIZE3)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// ==========================================================================================================
	//　ステージ２
	if (boss_stage_now == second) {
		for (int x = 0; x < BOSS_ROTATE_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_ROTATE_NUM; p++) {
				for (int y = 0; y < BOSS_ROTATE_NUMBER; y++) {
					if (player_hit_mode == No_Hit) {
						if (display_handle_rotate_shot_mode[x][p][y] == DISPLAY) {
							if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_rotate_shot_coordinate[x][p][y].x, boss_rotate_shot_coordinate[x][p][y].y, BOSS_ROTATE_SHOT_SIZE)) {
								//		DrawFillBox(0, 0, 2000, 2000, RED);
								player_hit_mode = Hit;
							}
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_NEKOMIMI_MAX; x++) {
			for (int p = 0; p < BOSS_NEKOMIMI_NUM; p++) {
				if (player_hit_mode == No_Hit) {
					//if (display_handle_rotate_shot_mode[x][p][y] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_nekomimi_attack_shot_coordinate[x][p].x, boss_nekomimi_attack_shot_coordinate[x][p].y, BOSS_ROTATE_SHOT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
				//	}
			}
		}
		for (int x = 0; x < BOSS_SMALL_SHOT_MAX; x++) {
			if (player_hit_mode == No_Hit) {
				//if (display_handle_rotate_shot_mode[x][p][y] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_shot_shot[x].x, boss_small_shot_shot[x].y, BOSS_SMALL_SHOT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
				//}
			}
		}
		for (int x = 0; x < BOSS_SMALL_AMAX; x++) {
			if (player_hit_mode == No_Hit) {
				//if (display_handle_rotate_shot_mode[x][p][y] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_small_shot[x].x, boss_small_shot[x].y, BOSS_SMALL_SIZE)) {
					//DrawFillBox(0,0,2000,2000,RED);
					player_hit_mode = Hit;
				}
			}
			//	}
		}
	}
	// ==========================================================================================================
	//　ステージ３
	if (boss_stage_now == third) {
		for (int x = 0; x < BOSS_FURAN_RED_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_FURAN_RED_NUM_MAX; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_furan_red_shot_mode[x][p] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_furan_red_circle_shot[x][p].x, boss_furan_red_circle_shot[x][p].y, BOSS_FURAN_RED_SHOT_R)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_FURAN_BLUE_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_FURAN_BLUE_NUM_MAX; p++) {
				for (int y = 0; y < BOSS_FURAN_BLUE_LB; y++) {
					if (player_hit_mode == No_Hit) {
						if (display_handle_furan_blue_shot_mode[x][p][y] == DISPLAY) {
							if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_furan_blue_circle_shot[x][p][y].x, boss_furan_blue_circle_shot[x][p][y].y, BOSS_FURAN_BLUE_SHOT_R)) {
								//	DrawFillBox(0, 0, 2000, 2000, RED);
								player_hit_mode = Hit;
							}
						}
					}
				}
			}
		}
		for (int x = 0; x < BOSS_FURAN_PURPLE_SHOT_MAX; x++) {
			for (int p = 0; p < BOSS_FURAN_PURPLE_NUM_MAX; p++) {
				if (player_hit_mode == No_Hit) {
					if (display_handle_furan_purple_shot_mode[x][p] == DISPLAY) {
						if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss_furan_purple_circle_shot[x][p].x, boss_furan_purple_circle_shot[x][p].y, BOSS_FURAN_PURPLE_SHOT_R)) {
							//	DrawFillBox(0, 0, 2000, 2000, RED);
							player_hit_mode = Hit;
						}
					}
				}
			}
		}
	}
	// ==========================================================================================================
	// プレイヤーと敵
	// =====================================================
	// 攻撃１の敵とプレイヤー
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_1_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_1_coordinate[x][p].x, zako_attack_1_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃２の敵とプレイヤー
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (player_hit_mode == No_Hit) {
				if (display_handle_2_mode[x][p] == DISPLAY) {
					if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_2_coordinate[x][p].x, zako_attack_2_coordinate[x][p].y, ATTACK_1_2_ROT_SIZE)) {
						//	DrawFillBox(0, 0, 2000, 2000, RED);
						player_hit_mode = Hit;
					}
				}
			}
		}
	}
	// =====================================================
	// 攻撃３の敵とプレイヤー
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_3_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_3_coordinate[x].x, zako_attack_3_coordinate[x].y, ATTACK_3_4_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃４の敵とプレイヤー
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_4_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, zako_attack_4_coordinate[x].x, zako_attack_4_coordinate[x].y, ATTACK_3_4_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃５の敵とプレイヤー
	if (player_hit_mode == No_Hit) {
		if (display_handle_5_c_mode == DISPLAY) {
			if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_5_coordinate.x, attack_5_coordinate.y, ATTACK_5_ROT_SIZE)) {
				//	DrawFillBox(0, 0, 2000, 2000, RED);
				player_hit_mode = Hit;
			}
		}
	}
	for (int x = 0; x < ATTACK_5_MAX; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_5_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_5_zako_coordinate[x].x, attack_5_zako_coordinate[x].y, ATTACK_5_ZAKO_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃６の敵とプレイヤー
	if (player_hit_mode == No_Hit) {
		if (display_handle_6_c_mode == DISPLAY) {
			if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, ATTACK_6_ROT_SIZE)) {
				//	DrawFillBox(0, 0, 2000, 2000, RED);
				player_hit_mode = Hit;
			}
		}
	}
	for (int x = 0; x < ATTACK_6_MAX; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_6_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_6_zako_coordinate[x].x, attack_6_zako_coordinate[x].y, ATTACK_6_ZAKO_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃７の敵とプレイヤー
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_7_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_7_zako_coordinate[x].x, attack_7_zako_coordinate[x].y, ATTACK_7_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃８の敵とプレイヤー
	for (int x = 0; x < ATTACK_8_MAX; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_8_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_8_zako_coordinate[x].x, attack_8_zako_coordinate[x].y, ATTACK_8_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃９の敵とプレイヤー
	if (player_hit_mode == No_Hit) {
		if (display_handle_9_nekomimi_mode == DISPLAY) {
			if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, ATTACK_9_ROT_SIZE)) {
				//	DrawFillBox(0, 0, 2000, 2000, RED);
				player_hit_mode = Hit;
			}
		}
	}
	for (int x = 0; x < ATTACK_9_NUM; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_9_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_9_zako_coordinate[x].x, attack_9_zako_coordinate[x].y, ATTACK_9_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃１０の敵とプレイヤー
	if (player_hit_mode == No_Hit) {
		if (display_handle_10_nekomimi_mode == DISPLAY) {
			if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, ATTACK_10_ROT_SIZE)) {
				//	DrawFillBox(0, 0, 2000, 2000, RED);
				player_hit_mode = Hit;
			}
		}
	}
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_10_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_10_zako_coordinate[x].x, attack_10_zako_coordinate[x].y, ATTACK_10_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃１１の敵とプレイヤー
	if (player_hit_mode == No_Hit) {
		if (display_handle_11_nekomimi_mode == DISPLAY) {
			if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, ATTACK_11_ROT_SIZE)) {
				//	DrawFillBox(0, 0, 2000, 2000, RED);
				player_hit_mode = Hit;
			}
		}
	}
	for (int x = 0; x < ATTACK_11_NUM; x++) {
		if (player_hit_mode == No_Hit) {
			if (display_handle_11_mode[x] == DISPLAY) {
				if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_11_zako_coordinate[x].x, attack_11_zako_coordinate[x].y, ATTACK_11_ROT_SIZE)) {
					//	DrawFillBox(0, 0, 2000, 2000, RED);
					player_hit_mode = Hit;
				}
			}
		}
	}
	// =====================================================
	// 攻撃１２の敵とプレイヤー
	if (player_hit_mode == No_Hit) {
		if (display_handle_12_mode == DISPLAY) {
			if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, ATTACK_12_ROT_SIZE)) {
				//	DrawFillBox(0, 0, 2000, 2000, RED);
				player_hit_mode = Hit;
			}
		}
	}
	// =====================================================
	//	ボス
	// =====================================================
	if (player_hit_mode == No_Hit) {
		if (boss_mode == MODE_MOVE) {
			if (isHit(player_coordinate.x, player_coordinate.y, PLAYER_R, boss.x, boss.y, BOSS_ROT_SIZE)) {
				//	DrawFillBox(0, 0, 2000, 2000, RED);
				player_hit_mode = Hit;
			}
		}
	}

	// =====================================================
	//　エフェクト
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			anim_burst1[x][p].update();
		}
	}
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			anim_burst2[x][p].update();
		}
	}
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		anim_burst3[x].update();
		anim_burst4[x].update();
	}
	anim_burst5solo.update();
	for (int x = 0; x < ATTACK_5_MAX; x++) {
		anim_burst5[x].update();
	}
	anim_burst6solo.update();
	//for (int x = 0; x < ATTACK_6_MAX; x++) {
	//	anim_burst6[x].update();
	//}
	for (int x = 0; x < ATTACK_6_MAX; x++) {
		anim6[x].update();
	}
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		anim_burst7[x].update();
	}
	for (int x = 0; x < ATTACK_8_MAX; x++) {
		anim_burst8[x].update();
	}
	anim_burst9solo.update();
	for (int x = 0; x < ATTACK_9_NUM; x++) {
		anim_burst9[x].update();
	}
	anim_burst10solo.update();
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		//anim_burst10[x].update();
	}
	anim_burst11solo.update();
	for (int x = 0; x < ATTACK_11_NUM; x++) {
		anim_burst11[x].update();
	}
	anim_burst12.update();
	// =====================================================

	//　実験
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		anim10[x].update();
	}


	//　自機弾のエフェクト]
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			tama[i][j].update();
		}
	}
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			r_shot[i][j].update();
		}
	}
}
void HitShotDraw() {
	// =====================================================
	//　エフェクト描画
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (anim_burst1[x][p].isPlay()) {
				int anim = anim_burst1[x][p].getImg();
				DrawRotaGraph(zako_attack_1_coordinate[x][p].x, zako_attack_1_coordinate[x][p].y, 2, 0, anim, TRUE);
			}
		}
	}
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			if (anim_burst2[x][p].isPlay()) {
				int anim = anim_burst2[x][p].getImg();
				DrawRotaGraph(zako_attack_2_coordinate[x][p].x, zako_attack_2_coordinate[x][p].y, 2, 0, anim, TRUE);
			}
		}
	}
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		if (anim_burst3[x].isPlay()) {
			int anim = anim_burst3[x].getImg();
			DrawRotaGraph(zako_attack_3_coordinate[x].x, zako_attack_3_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		if (anim_burst4[x].isPlay()) {
			int anim = anim_burst4[x].getImg();
			DrawRotaGraph(zako_attack_4_coordinate[x].x, zako_attack_4_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	if (anim_burst5solo.isPlay()) {
		int anim = anim_burst5solo.getImg();
		DrawRotaGraph(attack_5_coordinate.x, attack_5_coordinate.y, 2, 0, anim, TRUE);
	}
	for (int x = 0; x < ATTACK_5_MAX; x++) {
		if (anim_burst5[x].isPlay()) {
			int anim = anim_burst5[x].getImg();
			DrawRotaGraph(attack_5_zako_coordinate[x].x, attack_5_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	if (anim_burst6solo.isPlay()) {
		int anim = anim_burst6solo.getImg();
		DrawRotaGraph(attack_6_teki_coordinate.x, attack_6_teki_coordinate.y, 2, 0, anim, TRUE);
	}
	for (int x = 0; x < ATTACK_6_MAX; x++) {
		/*if (anim_burst6[x].isPlay()) {
			int anim = anim_burst6[x].getImg();
			DrawRotaGraph(attack_6_zako_coordinate[x].x, attack_6_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}*/
		if (anim6[x].isPlay()) {
			int anim = anim6[x].getImg();
			DrawRotaGraph(attack_6_zako_coordinate[x].x, attack_6_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		if (anim_burst7[x].isPlay()) {
			int anim = anim_burst7[x].getImg();
			DrawRotaGraph(attack_7_zako_coordinate[x].x, attack_7_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	for (int x = 0; x < ATTACK_8_MAX; x++) {
		if (anim_burst8[x].isPlay()) {
			int anim = anim_burst8[x].getImg();
			DrawRotaGraph(attack_8_zako_coordinate[x].x, attack_8_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	if (anim_burst9solo.isPlay()) {
		int anim = anim_burst9solo.getImg();
		DrawRotaGraph(attack_9_nekomimi_attack_coordinate.x, attack_9_nekomimi_attack_coordinate.y, 2, 0, anim, TRUE);
	}
	for (int x = 0; x < ATTACK_9_NUM; x++) {
		if (anim_burst9[x].isPlay()) {
			int anim = anim_burst9[x].getImg();
			DrawRotaGraph(attack_9_zako_coordinate[x].x, attack_9_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	if (anim_burst10solo.isPlay()) {
		int anim = anim_burst10solo.getImg();
		DrawRotaGraph(attack_10_nekomimi_attack_coordinate.x, attack_10_nekomimi_attack_coordinate.y, 2, 0, anim, TRUE);
	}
	//for (int x = 0; x < ATTACK_10_NUM; x++) {
		//if (anim_burst10[x].isPlay()) {
		//	int anim = anim_burst10[x].getImg();
		//	DrawRotaGraph(attack_10_zako_coordinate[x].x, attack_10_zako_coordinate[x].y, 2, 0, anim, TRUE);
		//}
	//}
	if (anim_burst11solo.isPlay()) {
		int anim = anim_burst11solo.getImg();
		DrawRotaGraph(attack_11_nekomimi_attack_coordinate.x, attack_11_nekomimi_attack_coordinate.y, 2, 0, anim, TRUE);
	}
	for (int x = 0; x < ATTACK_11_NUM; x++) {
		if (anim_burst11[x].isPlay()) {
			int anim = anim_burst11[x].getImg();
			DrawRotaGraph(attack_11_zako_coordinate[x].x, attack_11_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}
	if (anim_burst12.isPlay()) {
		int anim = anim_burst12.getImg();
		DrawRotaGraph(attack_12_nekomimi_coordinate.x, attack_12_nekomimi_coordinate.y, 2, 0, anim, TRUE);
	}
	// =====================================================
	
	//　実験
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		if (anim10[x].isPlay()) {
			int anim = anim10[x].getImg();
			DrawRotaGraph(attack_10_zako_coordinate[x].x, attack_10_zako_coordinate[x].y, 2, 0, anim, TRUE);
		}
	}


	// =====================================================

	//　自機弾エフェクト
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (tama[i][j].isPlay()) {
				int anim = tama[i][j].getImg();
				DrawRotaGraph(sway_coordinate[i][j].x, sway_coordinate[i][j].y + 10, 1, 0, anim, TRUE);
			}
		}
	}
	if (boss_stage_now == none) {
		for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
			for (int j = 0; j < HR_SHOT_NUM; j++) {
				if (r_shot[i][j].isPlay()) {
					int anim = r_shot[i][j].getImg();
					DrawRotaGraph(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y + 10, 1, 0, anim, TRUE);
				}
			}
		}
	}
	else {
		for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
			for (int j = 0; j < HR_SHOT_NUM; j++) {
				if (r_shot[i][j].isPlay()) {
					int anim = r_shot[i][j].getImg();
					DrawRotaGraph(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y + 30, 1, 0, anim, TRUE);
				}
			}
		}
	}

	//　後で消す
	//for (int i = 0; i < ATTACK_10_NUM; i++) {
	//	DrawFormatString(100, 100 + 20 * i, WHITE, "%d", attack_zako_10_hp[i]);
	//}
}
void HitShotExit() {
	for (int x = 0; x < ATTACK_1_2_MAX; x++) {
		for (int p = 0; p < ATTACK_1_2__NUM; p++) {
			anim_burst1[x][p].exit();
			anim_burst2[x][p].exit();
		}
	}
	for (int x = 0; x < ATTACK_3_4_MAX; x++) {
		anim_burst3[x].exit();
		anim_burst4[x].exit();
	}
	anim_burst5solo.exit();
	for (int x = 0; x < ATTACK_5_MAX; x++) {
		anim_burst5[x].exit();
	}
	anim_burst6solo.exit();
	for (int x = 0; x < ATTACK_6_MAX; x++) {
		//anim_burst6[x].exit();
		anim6[x].exit();
	}
	for (int x = 0; x < ATTACK_7_MAX; x++) {
		anim_burst7[x].exit();
	}
	for (int x = 0; x < ATTACK_8_MAX; x++) {
		anim_burst8[x].exit();
	}
	anim_burst9solo.exit();
	for (int x = 0; x < ATTACK_9_NUM; x++) {
		anim_burst9[x].exit();
	}
	anim_burst10solo.exit();
	//for (int x = 0; x < ATTACK_10_NUM; x++) {
		//anim_burst10[x].exit();
	//}
	for (int x = 0; x < ATTACK_10_NUM; x++) {
		anim10[x].exit();
	}
	anim_burst11solo.exit();
	for (int x = 0; x < ATTACK_11_NUM; x++) {
		anim_burst11[x].exit();
	}
	anim_burst12.exit();

	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			tama[i][j].exit();
		}
	}

}