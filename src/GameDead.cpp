#include "GameDead.h"
#include "DxLib.h"

int GameOver_serect_num;
enum
{
	SerectContinue,
	SerectMenu,
//	SerectExit,
};

int serect_count;
int serect_display_handle;
extern enum {
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

extern int score;


void GameDeadInit() {
}

void GameDeadUpdate() {
	serect_count++;
	if (serect_count >= 20) {
		serect_count = 0;
		if (serect_display_handle == HIDDEN) {
			serect_display_handle = DISPLAY;
		}
		else if (serect_display_handle == DISPLAY) {
			serect_display_handle = HIDDEN;
		}
	}

	if (IsKeyOn(KEY_INPUT_UP)) {
		if (GameOver_serect_num > 0) {
			GameOver_serect_num--;
		}
	}
	if (IsKeyOn(KEY_INPUT_DOWN)) {
		if (GameOver_serect_num < 1) {
			GameOver_serect_num++;
		}
	}
	//　決定
	if (IsKeyOn(KEY_INPUT_Z)) {
		if (GameOver_serect_num == SerectMenu)game_start_mode = Menu;
		score = 0;
		if (GameOver_serect_num == SerectContinue) {
			game_start_mode = Game;
			//HitShotExit();
		}
		//if (GameOver_serect_num == SerectExit)DxLib_End();
		GameOver_serect_num = 0;
	}

}
void GameDeadDraw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawFillBox(0,0,WINDOW_W,WINDOW_H,BLACK);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//　薄さを戻す
	SetFontSize(30);
	DrawString(WINDOW_W / 2 - 75, WINDOW_H / 2 - 120,"Game Over",RED);
	SetFontSize(20);
	DrawFormatString(WINDOW_W / 2 - 75, WINDOW_H / 2 - 80,WHITE,"Score: %d",score);
	DrawString(WINDOW_W / 2 - 25, WINDOW_H / 2 - 10,"Menu",WHITE);
	DrawString(WINDOW_W / 2 - 47, WINDOW_H / 2 - 50,"Continue",WHITE);
//	DrawString(WINDOW_W / 2 - 25, WINDOW_H / 2 + 30,"Exit",WHITE);
//	DrawString(WINDOW_W / 2 - 25, WINDOW_H / 2 - 10,"Exit",WHITE);


	if (serect_display_handle == DISPLAY) {
		if (GameOver_serect_num == SerectContinue) {
			DrawCircleAA(WINDOW_W / 2 - 72, WINDOW_H / 2 - 40, 14, 3, BLACK, TRUE, 0, 0);
			DrawCircleAA(WINDOW_W / 2 - 72, WINDOW_H / 2 - 40, 10, 3, WHITE, TRUE, 0, 0);
		}
		else if (GameOver_serect_num == SerectMenu) {
			DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2, 14, 3, BLACK, TRUE, 0, 0);
			DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2, 10, 3, WHITE, TRUE, 0, 0);
		}
		//else if (GameOver_serect_num == SerectExit) {
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 + 40, 14, 3, BLACK, TRUE, 0, 0);
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 + 40, 10, 3, WHITE, TRUE, 0, 0);
		//}
		//else if (GameOver_serect_num == SerectExit) {
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2, 14, 3, BLACK, TRUE, 0, 0);
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2, 10, 3, WHITE, TRUE, 0, 0);
		//}
	}
	SetFontSize(15);
	DrawString(WINDOW_W - 120, WINDOW_H - 40, "十字キー：移動", WHITE);
	DrawString(WINDOW_W - 80, WINDOW_H - 20, "Ｚ：決定", WHITE);

}
void GameDeadExit() {
}