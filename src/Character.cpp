#include "Character.h"
#include "WinMain.h"

//　キャラクターの選択画面
int character_bg;
int character_fream;
int character_count;
int triangle_display_handle;
enum {
	HIDDEN,		//　隠れてる
	DISPLAY,	//　出てる
};
int character_num;
enum 
{
	Reimu,
	Marisa,
};
//　ゲーム画面操作
extern int game_start_mode;
extern enum
{
	Menu,
	Character,
	Game,
	Options,
};

extern bool	player_character_mode;			//　０：霊夢　１：魔理沙
extern enum CharacterMode {
	REIMU,
	MARISA,
};

int reimu_img;
int marisa_img;

int se_chara_select;

extern struct Floatxy {
	float x;	//　ｘ座標
	float y;	//　ｙ座標
};

extern enum SwayMode {
	MODE_WAIT,									//	０：飛んでいない（待ち状態）
	MODE_MOVE,									//	１：飛んでいる　（移動状態）
};

extern enum {
	No_Hit,		//　当たっていない
	Hit,		//　当たった
	Hit_Count,	//　カウント
};

extern enum {
	none,
	first,
	second,
	third,
};

extern Floatxy player_coordinate;
extern int player_hp;
extern int spellcard_num;
extern int player_display_handle;
extern int player_hit_mode;
extern int player_exp_count;
extern int player_level;
extern bool sway_mode[SWAY_MAX_NUM][SWAY_NUM];
extern bool hr_shot_mode[HR_SHOT_MAX_NUM][HR_SHOT_NUM];
extern int frame_count;//フレームのカウント
extern bool game_shot[ATTACK_NO];//ゲームのモード
extern int display_handle_1_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
extern int display_handle_1_shot_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
extern int display_handle_2_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
extern int display_handle_2_shot_mode[ATTACK_1_2_MAX][ATTACK_1_2__NUM];
extern int display_handle_3_mode[ATTACK_3_4_MAX];
extern int display_handle_3_shot_mode[ATTACK_3_4_MAX][ATTACK_3_4_NUM];
extern int display_handle_4_mode[ATTACK_3_4_MAX];
extern int display_handle_4_shot_mode[ATTACK_3_4_MAX][ATTACK_3_4_NUM];
extern int display_handle_5_mode[ATTACK_5_MAX];
extern int display_handle_5_shot_mode[ATTACK_5_MAX][ATTACK_5_NUM];
extern int display_handle_5_c_mode;
extern float attack_5_shot_r[ATTACK_5_SHOT_NUM];
extern int display_handle_5_c_shot_mode[ATTACK_5_SHOT_NUM];
extern int display_handle_5_nekomimi_shot_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];
extern int display_handle_6_mode[ATTACK_6_MAX];
extern int display_handle_6_shot_mode[ATTACK_6_MAX][ATTACK_6_NUM];
extern int display_handle_6_c_mode;
extern float attack_6_teki_shot_r[ATTACK_6_SHOT_NUM];
extern int display_handle_6_c_shot_mode[ATTACK_6_SHOT_NUM];
extern int display_handle_6_nekomimi_shot_mode[NEKOMIMI_MAX][NEKOMIMI_NUM];
extern int display_handle_7_mode[ATTACK_7_MAX];
extern int display_handle_7_shot_mode[ATTACK_7_MAX][ATTACK_7_NUM];
extern int display_handle_8_mode[ATTACK_8_MAX];
extern int display_handle_8_shot_mode[ATTACK_8_MAX][ATTACK_8_NUM];
extern int attack_9_zako_mode[ATTACK_9_NUM];
extern int display_handle_9_mode[ATTACK_9_NUM];
extern int display_handle_9_shot_mode[ATTACK_9_NUM][ATTACK_9_MAX];
extern int display_handle_9_nekomimi_mode;
extern int display_handle_9_nekomimi_shot_mode[ATTACK_9_NEKOMIMI_MAX][ATTACK_9_NEKOMIMI_NUM];
extern int display_handle_10_mode[ATTACK_10_NUM];
extern int display_handle_10_shot_mode[ATTACK_10_NUM][ATTACK_10_MAX];
extern int display_handle_10_nekomimi_mode;
extern int display_handle_10_nekomimi_shot_mode[ATTACK_10_NEKOMIMI_MAX][ATTACK_10_NEKOMIMI_NUM];
extern int display_handle_11_mode[ATTACK_11_NUM];
extern int display_handle_11_shot_mode[ATTACK_11_NUM][ATTACK_11_MAX];
extern int display_handle_11_nekomimi_mode;
extern int display_handle_11_nekomimi_shot_mode[ATTACK_11_NEKOMIMI_MAX][ATTACK_11_NEKOMIMI_NUM];
extern int display_handle_12_shot_mode[ATTACK_12_SHOT_MAX];
extern int display_handle_12_mode;
extern int display_handle_12_nekomimi_shot_mode[ATTACK_12_NEKOMIMI_MAX][ATTACK_12_NEKOMIMI_NUM];
extern int display_handle_boss_shot_mode_big[BOSS_BIG_LEFT_1_SHOT_MAX][BOSS_BIG_LEFT_1_SHOT_NUM][6];
extern int display_handle_boss_shot_mode_small[BOSS_SMALL_LEFT_1_SHOT_MAX][BOSS_SMALL_LEFT_1_SHOT_NUM][6];
extern int display_handle_snow_1_shot_mode[BOSS_RAND_NUM1];
extern int display_handle_snow_2_shot_mode[BOSS_RAND_NUM2];
extern int display_handle_snow_3_shot_mode[BOSS_RAND_NUM3];
extern int display_handle_rotate_shot_mode[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
extern int boss_rotate_shot_mode[BOSS_ROTATE_SHOT_MAX][BOSS_ROTATE_NUM][BOSS_ROTATE_NUMBER];
extern int boss_nekomimi_attack_mode[BOSS_NEKOMIMI_MAX][BOSS_NEKOMIMI_NUM];
extern bool boss_small_shot_mode[BOSS_SMALL_SHOT_MAX];
extern bool boss_small_mode[BOSS_SMALL_AMAX];
extern int display_handle_furan_red_shot_mode[BOSS_FURAN_RED_SHOT_MAX][BOSS_FURAN_RED_NUM_MAX];
extern int display_handle_furan_blue_shot_mode[BOSS_FURAN_BLUE_SHOT_MAX][BOSS_FURAN_BLUE_NUM_MAX][BOSS_FURAN_BLUE_LB];
extern int display_handle_furan_purple_shot_mode[BOSS_FURAN_PURPLE_SHOT_MAX][BOSS_FURAN_PURPLE_NUM_MAX];
extern float boss_nekomimi_rr;
extern float boss_small_s1;
extern float boss_small_r1;
extern int boss_stage_now;
extern int attack_7_count;
extern int attack_7_num;
extern int attack_7_zako_mode[ATTACK_7_MAX];
extern int attack_8_count;
extern int attack_8_num;
extern int attack_8_zako_mode[ATTACK_8_MAX];

int grHandleChara;
int grHandleTama;
int grHandleGraibs;

int grHandleCount;
Floatxy Chara;
Floatxy Tama;
Floatxy Spell;

void CharacterInit() {
	character_bg = LoadGraph("data/BG/setumei1.jpg");
	reimu_img = LoadGraph("data/player/I-threimu001.png");
	marisa_img = LoadGraph("data/player/I-th_marisa1.png");
	se_chara_select = LoadSoundMem("data/se/SELECT.wav");

	grHandleChara = LoadGraph("data/player/Reimudot.png");
	grHandleTama = LoadGraph("data/item/Hitbox1.png");
	grHandleGraibs = LoadGraph("data/player/Hitbox1.png");
	Tama.y = WINDOW_H / 2 - 110;
	Spell.y = WINDOW_H / 2;
}

void CharacterUpdate() {
	ChangeVolumeSoundMem(SE_PLAYER_VOLUME, se_chara_select);

	character_fream++;
	//if (IsKeyOn(KEY_INPUT_RIGHT)) {
	//	character_num = Marisa;
	//	player_character_mode = MARISA;
	//}
	//if (IsKeyOn(KEY_INPUT_LEFT)) {
		character_num = Reimu;
		player_character_mode = REIMU;
	//}
	if (character_fream > 20 && IsKeyOn(KEY_INPUT_Z)) {
		PlaySoundMem(se_chara_select, DX_PLAYTYPE_BACK);
		//GameInit();
		//PlayerInit();
		//　自機開始位置
		
		player_coordinate.x = 223.5f;
		player_coordinate.y = 420.0f;
		player_hp = 3;
		spellcard_num = SPELLCARD_NUM;
		player_display_handle = DISPLAY;
		player_hit_mode = No_Hit;
		player_exp_count = 0;
		player_level = 0;
		for (int i = 0; i < SWAY_MAX_NUM; i++) {
			for (int j = 0; j < SWAY_NUM; j++) {
				sway_mode[i][j] = MODE_WAIT;
			}
		}
		for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
			for (int j = 0; j < HR_SHOT_NUM; j++) {
				hr_shot_mode[i][j] = MODE_WAIT;
			}
		}
		//EnemyInit();
		frame_count = 0;
		for (int i = 0; i < 16; i++) {
			game_shot[i] = MODE_WAIT;
		}
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

		//HitShotInit();
		//ExpInit();
		game_start_mode = Game;
	}



	character_count++;
	if (character_count >= 20) {
		character_count = 0;
		if (triangle_display_handle == HIDDEN) {
			triangle_display_handle = DISPLAY;
		}
		else if (triangle_display_handle == DISPLAY) {
			triangle_display_handle = HIDDEN;
		}
	}

	if (CheckHitKey(KEY_INPUT_X)) {
		PlaySoundMem(se_chara_select, DX_PLAYTYPE_BACK);
		game_start_mode = Menu;
	}

	grHandleCount++;
	if (grHandleCount >= PLAYER_IMG_TIMING) {
		grHandleCount = 0;
		Chara.x += PLAYER_IMG_WIDTH;
		if (Chara.x >= PLAYER_IMG_WIDTH_MAX) {
			//　０に戻す
			Chara.x = 0;
		}
	}
	Tama.y -= SWAY_SPEED;
	if (Tama.y <= -10) {
		Tama.y = WINDOW_H / 2 - 110;
	}
	Spell.y -= HR_SPELLCARD_R_SPEED;
	if (Spell.y <= -70) {			//　半径が５００よりも大きいときは
		Spell.y = WINDOW_H / 2;
	}
}

void CharacterDraw() {
	DrawGraph(0,0, character_bg,1);
	SetFontSize(15);
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, character_bg, 1);
	DrawString(WINDOW_W - 80, WINDOW_H - 40, "Ｚ：決定", WHITE);
	DrawFormatString(WINDOW_W - 80, WINDOW_H - 20, WHITE, "Ｘ：戻る");
	//DrawGraph(0,0, reimu_img,1);
	//DrawGraph(0,0, marisa_img,1);
	if (character_num == Reimu) {
		DrawRotaGraph(WINDOW_W / 4, WINDOW_H / 2, 3, 0, reimu_img, 1);
		//if (triangle_display_handle == DISPLAY) {
		//	DrawCircleAA(WINDOW_W - 20, WINDOW_H / 2, 14, 3, BLACK, TRUE, 0, 0);
		//	DrawCircleAA(WINDOW_W - 20, WINDOW_H / 2, 10, 3, WHITE, TRUE, 0, 0);
		//}
		SetFontSize(25);
		DrawFormatString(WINDOW_W / 4 - 55, WINDOW_H / 2 + 150, RED, "博麗霊夢");
		DrawFormatString(WINDOW_W / 4 -  80, WINDOW_H / 2 - 230, WHITE, "操作説明");
		SetFontSize(20);
		DrawFormatString(WINDOW_W / 4 - 100, WINDOW_H / 2 - 200, WHITE, "十字キーで移動");
		//DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 130, WHITE, "Ｚ:サブショット");
		//DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 110, WHITE, "針弾、まっすぐ飛ぶ");
		//DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 90, WHITE, "Ⅹ:スペルカード　夢符「封魔陣」");
		//DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 70, WHITE, "スペルカードは敵の弾を消す弾を、\n前方に飛ばす");
		//DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 30, WHITE, "ＳＨＩＦＴ:グレイズ");
		//DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 10, WHITE, "自機の当たり判定を表示することが可能");

		//DrawRotaGraph(0,0,1,0, grHandleChara, TRUE);
		DrawFormatString(WINDOW_W / 2 - 18, WINDOW_H / 2 - 80, WHITE, "Ｚ:ショット");
		DrawRotaGraph(WINDOW_W / 2 + 50, Tama.y, 1, 0, grHandleTama, TRUE);
		DrawRectRotaGraph(WINDOW_W / 2 + 50, WINDOW_H / 2 - 110, Chara.x, Chara.y, PLAYER_IMG_WIDTH, PLAYER_IMG_HEIGHT, PLAYER_IMG_SAME_SIZE, 0, grHandleChara, TRUE);
		DrawFormatString(WINDOW_W / 2 + 120, WINDOW_H / 2 + 30, WHITE, "Ｘ:スペルカード\n　 敵の玉を消す");
		DrawRectRotaGraph(WINDOW_W / 2 + 200, WINDOW_H / 2, Chara.x, Chara.y, PLAYER_IMG_WIDTH, PLAYER_IMG_HEIGHT, PLAYER_IMG_SAME_SIZE, 0, grHandleChara, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawCircleAA(WINDOW_W / 2 + 200, Spell.y, 70, CIRCLEAA_SQUARE, GetColor(255, 255, 255));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//　薄さを戻す
		DrawFormatString(WINDOW_W / 2 - 18, WINDOW_H / 2 + 140, WHITE, "Lshit:グレイブス\n 当たり判定表示\n　速度低下");
		DrawRectRotaGraph(WINDOW_W / 2 + 50, WINDOW_H / 2 + 110, Chara.x, Chara.y, PLAYER_IMG_WIDTH, PLAYER_IMG_HEIGHT, PLAYER_IMG_SAME_SIZE, 0, grHandleChara, TRUE);
		DrawRotaGraph(WINDOW_W / 2 + 50, WINDOW_H / 2 + 110,1,0, grHandleGraibs,TRUE);
	}
	//if (character_num == Marisa) {
	//	DrawRotaGraph(WINDOW_W / 4, WINDOW_H / 2, 3, 0, marisa_img, 1);
	//	//if (triangle_display_handle == DISPLAY) {
	//	//	DrawCircleAA(20, WINDOW_H / 2, 14, 3, BLACK, TRUE, 0, D2R(180));
	//	//	DrawCircleAA(20, WINDOW_H / 2, 10, 3, WHITE, TRUE, 0, D2R(180));
	//	//}
	//	SetFontSize(25);
	//	DrawFormatString(WINDOW_W / 4 - 60, WINDOW_H / 2 + 150, YELLOW, "霧雨魔理沙");
	//	DrawFormatString(WINDOW_W / 2, WINDOW_H / 2 - 180, WHITE, "操作説明");
	//	SetFontSize(15);
	//	DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 150, WHITE, "Ｚ:ＳＷＡＹ弾");
	//	DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 130, WHITE, "Ｚ:サブショット");
	//	DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 110, WHITE, "敵を貫通するレーザー\nレベルに応じて太くなる");
	//	DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 70, WHITE, "Ⅹ:スペルカード　マスタースパーク\n必要ＬＶ：３");
	//	DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 - 30, WHITE, "スペルカードは前方に、\n高火力なビームを出す");
	//	DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 + 10, WHITE, "ＳＨＩＦＴ:グレイズ");
	//	DrawFormatString(WINDOW_W / 2 - 20, WINDOW_H / 2 + 30, WHITE, "自機の当たり判定を表示することが可能");
	//}
}
void CharacterExit() {
	DeleteGraph(character_bg);
	DeleteGraph(reimu_img);
	DeleteGraph(marisa_img);
	DeleteSoundMem(se_chara_select);
}