#include "GameClear.h"
#include "DxLib.h"

int clear_bg;

int clear_serect_num;
enum
{
	ClearMenu,
//	ClearContinue,
//	CleartExit,
};

int clear_count;
int clear_display_handle;
enum {
	HIDDEN,		//　隠れてる
	DISPLAY,	//　出てる
};

extern int score;

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

void GameClearInit() {
	clear_bg = LoadGraph("data/BG/setumei1.jpg");
}
void GameClearUpdate() {
	clear_count++;
	if (clear_count >= 20) {
		clear_count = 0;
		if (clear_display_handle == HIDDEN) {
			clear_display_handle = DISPLAY;
		}
		else if (clear_display_handle == DISPLAY) {
			clear_display_handle = HIDDEN;
		}
	}

	//if (IsKeyOn(KEY_INPUT_UP)) {
	//	if (clear_serect_num > 0) {
	//		clear_serect_num--;
	//	}
	//}
	//if (IsKeyOn(KEY_INPUT_DOWN)) {
	//	if (clear_serect_num < 1) {
	//		clear_serect_num++;
	//	}
	//}
	//　決定
	if (IsKeyOn(KEY_INPUT_Z)) {
		if (clear_serect_num == ClearMenu)game_start_mode = Menu;
	//	if (clear_serect_num == ClearContinue)game_start_mode = Game;
		//if (clear_serect_num == CleartExit)DxLib_End();
	}

}
void GameClearDraw() {
//	DrawFillBox(0, 0, 111000, 1000, BLUE);
	DrawGraph(0,0, clear_bg,TRUE);
	SetFontSize(30);
	DrawString(WINDOW_W / 2 - 100, WINDOW_H / 2 - 120, "Game Clear!!", YELLOW);
	SetFontSize(20);
	DrawFormatString(WINDOW_W / 2 - 75, WINDOW_H / 2 - 80, WHITE, "Score: %d", score);

	DrawString(WINDOW_W / 2 - 25, WINDOW_H / 2 - 50, "Menu", WHITE);
//	DrawString(WINDOW_W / 2 - 47, WINDOW_H / 2 - 10, "Continue", WHITE);
//	DrawString(WINDOW_W / 2 - 25, WINDOW_H / 2 + 30, "Exit", WHITE);
//	DrawString(WINDOW_W / 2 - 25, WINDOW_H / 2 - 10, "Exit", WHITE);

	if (clear_display_handle == DISPLAY) {
		if (clear_serect_num == ClearMenu) {
			DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 - 40, 14, 3, BLACK, TRUE, 0, 0);
			DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 - 40, 10, 3, WHITE, TRUE, 0, 0);
		}
		//else if (clear_serect_num == ClearContinue) {
		//	DrawCircleAA(WINDOW_W / 2 - 72, WINDOW_H / 2, 14, 3, BLACK, TRUE, 0, 0);
		//	DrawCircleAA(WINDOW_W / 2 - 72, WINDOW_H / 2, 10, 3, WHITE, TRUE, 0, 0);
		//}
		//else if (clear_serect_num == CleartExit) {
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 + 40, 14, 3, BLACK, TRUE, 0, 0);
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 + 40, 10, 3, WHITE, TRUE, 0, 0);
		//}
		//else if (clear_serect_num == CleartExit) {
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 + 14, 14, 3, BLACK, TRUE, 0, 0);
		//	DrawCircleAA(WINDOW_W / 2 - 50, WINDOW_H / 2 + 10, 10, 3, WHITE, TRUE, 0, 0);
		//}

	}
	SetFontSize(15);
//	DrawString(WINDOW_W - 120, WINDOW_H - 40, "十字キー：移動", WHITE);
	DrawString(WINDOW_W - 80, WINDOW_H - 20, "Ｚ：決定", WHITE);
}
void GameClearExit() {
	DeleteGraph(clear_bg);
}