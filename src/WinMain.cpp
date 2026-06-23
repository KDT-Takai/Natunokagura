#include "WinMain.h"
#include <ctime>

static int is_window_mode = TRUE;	//　FALSE：フルスクリーン　TRUE：ウィンドウスクリーン


//　ゲーム画面操作
int game_start_mode;

enum 
{
	Menu,
	Character,
	Game,
	Options,
	Game_Clear,
	Game_Dead,
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
//	game_start_mode = Game_Clear;
//	game_start_mode = Game_Dead;

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(is_window_mode);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	if (is_window_mode == TRUE)
	{
		SetWindowSize(WINDOW_W, WINDOW_H);
	}
	SetBackgroundColor(0, 0, 0);
	SetMainWindowText("Re:ナツノカグラ");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	// ---------------
	// 初期化処理
	// ---------------
	SRand((int)time(NULL));
	InputKeyInit();
	InputMouseInit();
	MenuInit();
	GameInit();
	PlayerInit();
	EnemyInit();
	HitShotInit();
//	ExpInit();
	CharacterInit();
	GameClearInit();
	GameDeadInit();
	UiInit();

	while (ProcessMessage() == 0 )//&& CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;


		// ---------------
		// 更新処理
		// ---------------
		InputKeyUpdate();
		InputMouseUpdate();

		switch (game_start_mode) {
		case Menu:
			MenuUpdate();
			break;
		case Game:
			PlayerUpdate();
			GameUpdate();
			EnemyUpdate();
			HitShotUpdate();
		//	ExpUpdate();
			UiUpdate();
			break;
		case Character:
			CharacterUpdate();
			break;
		case Game_Clear:
			GameClearUpdate();
			break;
		case Game_Dead:
			GameDraw();
			HitShotDraw();
			PlayerDraw();
			EnemyDraw();
			UiDraw();
			GameDeadUpdate();
			break;
		}

		//if (game_start_mode == Menu) {
		//	MenuUpdate();
		//}
		//else if (game_start_mode == Game) {
		//	PlayerUpdate();
		//	GameUpdate();
		//	EnemyUpdate();
		//	HitShotUpdate();
		//	ExpUpdate();
		//}
		//else if (game_start_mode == Character) {
		//	CharacterUpdate();
		//}
		//else if (game_start_mode == Game_Clear) {
		//	GameClearUpdate();
		//}
		//else if (game_start_mode == Game_Dead) {
		//	GameDeadUpdate();
		//}
		ClearDrawScreen();
		clsDx();

		// ---------------
		// 描画処理
		// ---------------
		switch (game_start_mode) {
		case Menu:
			MenuDraw();
			break;
		case Game:
			GameDraw();
			HitShotDraw();
			PlayerDraw();
			EnemyDraw();
		//	ExpDraw();
			UiDraw();
			break;
		case Character:
			CharacterDraw();
			break;
		case Game_Clear:
			GameClearDraw();
			break;
		case Game_Dead:
		//	UiExit();
		//	MenuExit();
		//	GameExit();
		//	PlayerExit();
		//	EnemyExit();
		//	HitShotExit();
		//	CharacterExit();
		//	GameClearExit();
			GameDraw();
			HitShotDraw();
			PlayerDraw();
			EnemyDraw();
			//	ExpDraw();
			UiDraw();
			GameDeadDraw();
			break;
		}

		//if (game_start_mode == Menu) {
		//	MenuDraw();
		//}
		//else if (game_start_mode == Game) {
		//	GameDraw();
		//	HitShotDraw();
		//	PlayerDraw();
		//	EnemyDraw();
		//	ExpDraw();
		//	UiDraw();
		//}
		//else if (game_start_mode == Character) {
		//	CharacterDraw();
		//}
		//else if (game_start_mode == Game_Clear) {
		//	GameClearDraw();
		//}
		//else if (game_start_mode == Game_Dead) {
		//	GameDraw();
		//	HitShotDraw();
		//	PlayerDraw();
		//	EnemyDraw();
		//	ExpDraw();
		//	UiDraw();
		//	GameDeadDraw();
		//}

		while (clock() < check_fps) {}
		ScreenFlip();
	}

	// ---------------
	// 終了処理
	// ---------------
	UiExit();
	InputKeyExit();
	InputMouseExit();
	MenuExit();
	GameExit();
	PlayerExit();
	EnemyExit();
	HitShotExit();
//	ExpExit();
	CharacterExit();
	GameClearExit();
	GameDeadExit();
	DxLib_End();


	return 0;
}

// 円と円との当たり判定
bool isHit(int x1, int y1, int r1, int x2, int y2, int r2)
{
	float dx = (float)(x1 - x2);
	float dy = (float)(y1 - y2);
	float dr = (float)(r1 + r2);

	if (sqrtf(dx * dx + dy * dy) <= dr)
	{
		// 当たった
		return true;
	}
	// 当たってない
	return false;
}

//　ボックスと点の当たり判定
bool isBoxHit(int x1, int y1, int x2, int y2, int mouse_x, int mouse_y)
{
	if (x1 < mouse_x && x2 > mouse_x && y1 < mouse_y && y2 > mouse_y) {
		//　当たった
		return true;
	}
	//　当たってない
	return false;
}

//	文字の真ん中を指定の位置に描画　（洞ちゃん作成）
void DrawCenterString(float x, float y, const char* string, unsigned int Color) {
	int str;
	int size;

	str = strlen(string);
	size = GetDrawStringWidth(string, str);
	DrawString(x - size / 2, y - GetFontSize() / 2, string, Color);

}

//　円のｘ、円のｙ、円の半径、ボックスのｘ（左上）、ボックスのｙ（左上）、ボックスのサイズｘ、ボックスのサイズｙ
bool CheckHitBoxCircle(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_x_size, float box_y_size) {
	//　左上
	float left_above_x = box_x - circle_x;
	float left_above_y = box_y - circle_y;
	float left_above = sqrtf(left_above_x * left_above_x + left_above_y * left_above_y);
	//　右上
	float right_above_x = box_x + box_x_size - circle_x;
	float right_above_y = box_y - circle_y;
	float right_above = sqrtf(right_above_x * right_above_x + right_above_y * right_above_y);
	//　左下
	float left_under_x = box_x - circle_x;
	float left_under_y = box_y + box_y_size - circle_y;
	float left_under = sqrtf(left_under_x * left_under_x + left_under_y * left_under_y);
	//　右下
	float right_under_x = box_x + box_x_size - circle_x;
	float right_under_y = box_y + box_y_size - circle_y;
	float right_under = sqrtf(right_under_x * right_under_x + right_under_y * right_under_y);
	if (left_above <= circle_r || right_above <= circle_r || left_under <= circle_r || right_under <= circle_r || 
		circle_x + circle_r >= box_x + circle_r && circle_x - circle_r <= box_x + box_x_size - circle_r && 
		circle_y + circle_r >= box_y && circle_y - circle_r <= box_y + box_y_size || circle_x + circle_r >= box_x && 
		circle_x - circle_r <= box_x + box_x_size && circle_y + circle_r >= box_y + circle_r && 
		circle_y - circle_r <= box_y + box_y_size - circle_r) {
		return true;
	}
	else {
		return false;
	}
}