#include "Menu.h"
#include "DxLib.h"

int bg;
int title;
int title_num;
enum
{
	//Game_Start,
	//Option,
	//Exit,
	Game_Start,
	//Option,
//	Exit,
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

extern int character_fream;

int menu_count;
int menu_display_handle;
enum {
	HIDDEN,		//　隠れてる
	DISPLAY,	//　出てる
};


int se_select;


void MenuInit() {
	bg = LoadGraph("data/BG/result.jpg");
	title = LoadGraph("data/BG/natunokagura.png");
	se_select = LoadSoundMem("data/se/SELECT.wav");
}

void MenuUpdate() {
	ChangeVolumeSoundMem(SE_PLAYER_VOLUME, se_select);


	menu_count++;
	if (menu_count >= 20) {
		menu_count = 0;
		if (menu_display_handle == HIDDEN) {
			menu_display_handle = DISPLAY;
		}
		else if (menu_display_handle == DISPLAY) {
			menu_display_handle = HIDDEN;
		}
	}

	//if (IsKeyOn(KEY_INPUT_UP)) {
	//	if (title_num > 0) {
	//	title_num--;
	//	}
	//}
	//if (IsKeyOn(KEY_INPUT_DOWN)) {
	//	if (title_num < 1) {
	//		title_num++;
	//	}	
	//}
	//　決定
	if (IsKeyOn(KEY_INPUT_Z)) {
		PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		if (title_num == Game_Start) {
			game_start_mode = Character;
			//EnemyInit();
		}
		character_fream = 0;
	}
	//if (IsKeyOn(KEY_INPUT_Z)) {
	//	if (title_num == Option) game_start_mode = Options;
	//}
	//if (IsKeyOn(KEY_INPUT_Z)) {
	//	if (title_num == Exit)DxLib_End();
	//}
}

void MenuDraw() {
	DrawGraph(0, 0, bg, 1);
	DrawRotaGraph(220,80,0.08,0,title,1);
	SetFontSize(25);
	DrawFormatString(70,180,WHITE,"GAME START");
//	DrawFormatString(70,240,WHITE,"OPERATING INSTRUCTIONS");
//	DrawFormatString(70,300,WHITE,"EXIT");
//	DrawFormatString(70,280,WHITE,"EXIT");
//	DrawFormatString(0, 0, RED, "%d", title_num);

	if (menu_display_handle == DISPLAY) {
		if (title_num == Game_Start) {
			DrawCircleAA(50, 190, 14, 3, BLACK, TRUE, 0, 0);
			DrawCircleAA(50, 190, 10, 3, WHITE, TRUE, 0, 0);
		}
	/*	else if (title_num == Option) {
			DrawCircleAA(50, 250, 14, 3, BLACK, TRUE, 0, 0);
			DrawCircleAA(50, 250, 10, 3, WHITE, TRUE, 0, 0);
		}*/
	//	else if (title_num == Exit) {
			//DrawCircleAA(50, 310, 14, 3, BLACK, TRUE, 0, 0);
			//DrawCircleAA(50, 310, 10, 3, WHITE, TRUE, 0, 0);
	//		DrawCircleAA(50, 290, 14, 3, BLACK, TRUE, 0, 0);
	//		DrawCircleAA(50, 290, 10, 3, WHITE, TRUE, 0, 0);
	//	}
	}
	SetFontSize(15);
	DrawString(WINDOW_W - 80, WINDOW_H - 20, "Ｚ：決定", WHITE);
}

void MenuExit() {
	DeleteGraph(bg);
	DeleteGraph(title);
	DeleteSoundMem(se_select);

}