#include "EXP.h"
#include "DxLib.h"

//extern struct Floatxy {
//	float x;	//　ｘ座標
//	float y;	//　ｙ座標
//};
//
//extern int stage_map_mode;	//　０：なしの状態　１：雑魚敵２体　２：雑魚敵４体　３：咲夜　４：雑魚敵６体　５：フラン　６：フラン＆レミリア
//
//extern enum StageMap {
//	StageNull,
//	StageFirst,
//	StageSecond,
//	StageThird,
//	StageFourth,
//	StageFifth,
//	StageSixth,
//};
//
////　自機移動設定
//extern Floatxy	player_coordinate;				//　プレイヤーの座標
//
//extern Floatxy enemy_red_coordinate[ENEMY_RED_NUM];
//extern int enemy_red_hp[ENEMY_RED_NUM];
////　青色の雑魚敵
//extern Floatxy enemy_blue_coordinate[ENEMY_BLUE_NUM];							//　青色の雑魚敵の座標
//extern int enemy_blue_hp[ENEMY_BLUE_NUM];
//
////　経験値用
//Floatxy	experience_value_coordinate[EXPERIENCE_VALUE_NUM][EXPERIENCE_VALUE_MAX];		//　経験値の座標
//int		experience_value_num;															//　現在の番号
//float	experience_value_speed[EXPERIENCE_VALUE_NUM][EXPERIENCE_VALUE_MAX];
//int		experience_value_mode[EXPERIENCE_VALUE_NUM][EXPERIENCE_VALUE_MAX];
//float	experience_value_rot[EXPERIENCE_VALUE_NUM][EXPERIENCE_VALUE_MAX];
//int		experience_value_count;	//　１００になったら一応レベルアップ
//
//enum
//{
//	MODE_WAIT,
//	//MODE_PREPARATION,
//	MODE_MOVE,
//	MODE_PLAYER,	//　プレイヤーに向かって
//};
//
//
//extern int player_level;	//	０：レベル１（攻撃単発）　１：レベル２（）　２：レベル３（）　３：レベル４（）　４：レベル５（）
//extern enum PlayerLevel {
//	LEVEL1,
//	LEVEL2,
//	LEVEL3,
//	LEVEL4,
//	LEVEL5,
//};

void ExpInit() {
}

void ExpUpdate() {
//	if (stage_map_mode != StageNull) {
//		for (int i = 0; i < EXPERIENCE_VALUE_NUM; i++) {
//			for (int j = 0; j < ENEMY_RED_NUM; j++) {
//				if (experience_value_mode[i][experience_value_num] == MODE_WAIT) {
//					if (enemy_red_hp[j] <= 0) {
//						experience_value_coordinate[i][experience_value_num].x = GetRand(float(EXPERIENCE_VALUE_DISTANCE)) + enemy_red_coordinate[j].x - EXPERIENCE_VALUE_DISTANCE / 2;
//						experience_value_coordinate[i][experience_value_num].y = GetRand(float(EXPERIENCE_VALUE_DISTANCE)) + enemy_red_coordinate[j].y - EXPERIENCE_VALUE_DISTANCE / 2;
//						experience_value_speed[i][experience_value_num] = -EXPERIENCE_VALUE_SPEED;
//						experience_value_mode[i][experience_value_num] = MODE_MOVE;
//					}
//				}
//			}
//			if (experience_value_num >= EXPERIENCE_VALUE_MAX) {
//				experience_value_num = 0;
//			}
//		}
//
//		//for (int i = 0; i < EXPERIENCE_VALUE_NUM; i++) {
//		//	for (int j = 0; j < ENEMY_BLUE_NUM; j++) {
//		//		if (experience_value_mode[i][experience_value_num] == MODE_WAIT) {
//		//			if (enemy_red_hp[j] <= 0) {
//		//				experience_value_coordinate[i][experience_value_num].x = GetRand(float(EXPERIENCE_VALUE_DISTANCE)) + enemy_blue_coordinate[j].x - EXPERIENCE_VALUE_DISTANCE / 2;
//		//				experience_value_coordinate[i][experience_value_num].y = GetRand(float(EXPERIENCE_VALUE_DISTANCE)) + enemy_blue_coordinate[j].y - EXPERIENCE_VALUE_DISTANCE / 2;
//		//				experience_value_speed[i][experience_value_num] = -EXPERIENCE_VALUE_SPEED;
//		//				experience_value_mode[i][experience_value_num] = MODE_MOVE;
//		//			}
//		//		}
//		//	}
//		//	if (experience_value_num >= EXPERIENCE_VALUE_MAX) {
//		//		experience_value_num = 0;
//		//	}
//		//}
//
//		for (int i = 0; i < EXPERIENCE_VALUE_NUM; i++) {
//			for (int j = 0; j < EXPERIENCE_VALUE_MAX; j++) {
//				if (experience_value_mode[i][j] == MODE_MOVE) {
//					if (experience_value_speed[i][j] <= EXPERIENCE_VALUE_SPEED) {
//						experience_value_speed[i][j] = experience_value_speed[i][j] + 0.1f;
//					}
//					experience_value_coordinate[i][j].y += experience_value_speed[i][j];
//					if (experience_value_coordinate[i][j].y >= BG_Y_HH + EXPERIENCE_VALUE_DISTANCE) {
//						experience_value_mode[i][j] = MODE_WAIT;
//					}
//					//　プレイヤーに近づいたら
//					if (isHit(player_coordinate.x, player_coordinate.y, EXPERIENCE_VALUE_ABSORPTION, experience_value_coordinate[i][j].x, experience_value_coordinate[i][j].y, EXPERIENCE_VALUE_R)) {
//						experience_value_mode[i][j] = MODE_PLAYER;
//					}
//				}
//				else if (experience_value_mode[i][j] == MODE_PLAYER) {
//					experience_value_rot[i][j] = atan2f(player_coordinate.y - experience_value_coordinate[i][j].y, player_coordinate.x - experience_value_coordinate[i][j].x);
//					experience_value_coordinate[i][j].x += cosf(experience_value_rot[i][j]) * EXPERIENCE_VALUE_PLAYER_SPEED;	//　ENEMY_RED_SPEED の速さでｘ軸移動
//					experience_value_coordinate[i][j].y += sinf(experience_value_rot[i][j]) * EXPERIENCE_VALUE_PLAYER_SPEED;	//　ENEMY_RED_SPEED の速さでｙ軸移動
//					if ((isHit(player_coordinate.x, player_coordinate.y, EXPERIENCE_VALUE_PLAYER_R, experience_value_coordinate[i][j].x, experience_value_coordinate[i][j].y, EXPERIENCE_VALUE_R))) {
//						experience_value_count += EXPERIENCE_VALUE_AMOUNT;
//						experience_value_mode[i][j] = MODE_WAIT;
//					}
//				}
//			}
//		}
//	}
//
//	//　レベルアップ
//	if (player_level < LEVEL5) {
//		if (experience_value_count >= EXPERIENCE_VALUE) {
//			experience_value_count = START_ZERO;
//			player_level += 1;
//		}
//	}
//
}
void ExpDraw() {
//	for (int i = 0; i < EXPERIENCE_VALUE_NUM; i++) {
//		for (int j = 0; j < EXPERIENCE_VALUE_MAX; j++) {
//			if (experience_value_mode[i][j] != MODE_WAIT) {
//				DrawCircleAA(experience_value_coordinate[i][j].x, experience_value_coordinate[i][j].y, EXPERIENCE_VALUE_R, CIRCLEAA_SQUARE, YELLOW, TRUE);
//			}
//		}
//	}
//	DrawFormatString(BG_X_HW + 20 , 10 , WHITE, "%d", experience_value_count);
//	DrawCircleAA(player_coordinate.x, player_coordinate.y, EXPERIENCE_VALUE_ABSORPTION, CIRCLEAA_SQUARE, RED, FALSE);
//	DrawCircleAA(player_coordinate.x, player_coordinate.y, EXPERIENCE_VALUE_PLAYER_R, CIRCLEAA_SQUARE, BLUE, FALSE);
}
void ExpExit() {
}