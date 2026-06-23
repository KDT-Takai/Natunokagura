#include "ui.h"
#include "DxLib.h"

extern int BG_frame_img;						//　フレーム背景の画像
extern int player_hp;
extern int player_level;
extern int player_hp_img;
extern int player_exp_count;
extern int spellcard_num;
extern int score;
extern int spellcard_count;
extern int spellcard_shot_mode;

extern enum SpellCardMode {
	Spellcard_COUNT,
	Spellcard_WAIT,
	Spellcard_MOVE,
};

int sp;

void UiInit() {
	sp = LoadGraph("data/player/Shot1.png");

}
void UiUpdate() {


}
void UiDraw() {
	DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, PLAYER_IMG_SAME_SIZE, 0, BG_frame_img, TRUE);
	//　HP
	for (int i = 0; i < player_hp; i++) {
		DrawRotaGraph(BG_X_HW + 50 + 20 * i, 70, 1, 0, player_hp_img, TRUE);
	}
	SetFontSize(15);
	DrawFormatString(BG_X_HW + 10, 64, WHITE, "HP:");

	DrawFormatString(BG_X_HW + 10, 94, WHITE, "LEVEL:%d", player_level + 1);


	if (player_level != 4) {
		DrawFormatString(BG_X_HW + 10, 114, WHITE, "EXP:%d/100", player_exp_count);
		DrawFillBox(BG_X_HW + 10, 134, BG_X_HW + 10 + (player_exp_count * 2), 154, WHITE);
		DrawBox(BG_X_HW + 10, 134, BG_X_HW + 10 + 200, 154, WHITE, FALSE);
	}
	else if (player_level == 4) {
		DrawFormatString(BG_X_HW + 10, 114, WHITE, "EXP:MAX", player_exp_count);
		DrawFillBox(BG_X_HW + 10, 134, BG_X_HW + 10 + 200, 154, WHITE);
		DrawFormatString(BG_X_HW + 10 + 170, 137, RED,"MAX");
	}



	DrawFormatString(BG_X_HW + 10, 174, WHITE, "スペルカード残り", spellcard_num);
	for (int i = 0; i < spellcard_num; i++) {
		DrawRotaGraph(BG_X_HW + 30 + 20 * i, 204, 1, 0, sp, TRUE);
	}

	DrawFormatString(BG_X_HW + 10, 214, WHITE, "スペルカードゲージ", spellcard_count / 60);

	if(spellcard_shot_mode == Spellcard_COUNT)DrawFillBox(BG_X_HW + 10, 234, BG_X_HW + 10 + (spellcard_count / 7.5 * 3.75), 254, WHITE);
	if (spellcard_shot_mode == Spellcard_WAIT)DrawFillBox(BG_X_HW + 10, 234, BG_X_HW + 10 + (spellcard_count / 7.5 * 3.75), 254, RED);
	DrawBox(BG_X_HW + 10, 234, BG_X_HW + 10 + 200, 254, WHITE, FALSE);
	SetFontSize(20);
	DrawFormatString(BG_X_HW + 10, 40, WHITE, "SCORE:%d", score);
//	DrawFormatString(BG_X_HW + 10, 244, WHITE, "SCORE:%d", score);
	SetFontSize(15);
	DrawFormatString(BG_X_HW + 10, 264, WHITE, "Z:shot");
	DrawFormatString(BG_X_HW + 10, 284, WHITE, "X:スペルカード");
	DrawFormatString(BG_X_HW + 10, 304, WHITE, "Lshit:グレイズ");
	DrawFormatString(BG_X_HW + 10, 324, WHITE, "十字キー:移動");

}
void UiExit() {
	DeleteGraph(sp);
}