#include "Player.h"
#include "DxLib.h"

//　背景画像
extern int BG_stage_img;						//　ステージ背景の画像
extern int BG_frame_img;						//　フレーム背景の画像
//　背景画像のスクロール
extern float BG_stage_y;						//　ステージ背景の画像を縦スクロールさせる

extern struct Floatxy {
	float x;	//　ｘ座標
	float y;	//　ｙ座標
};

//　自機移動設定
Floatxy	player_coordinate;				//　プレイヤーの座標
Floatxy	player_img_coordinate;			//　プレイヤーの座標を動かす
int		player_hit_mode;				//　当たっているか
enum 
{
	No_Hit,		//　当たっていない
	Hit,		//　当たった
	Hit_Count,	//　カウント
};
enum {
	HIDDEN,		//　隠れてる
	DISPLAY,	//　出てる
};
int		player_hit_count;				//　６０フレーム間は無敵
int		player_hp;						//　ヒットポイント
int		player_display_handle_count;	//　ダメージを受けている判定をわかりやすくする
int		player_display_handle;			//　表示
int		player_exp_count;
int		player_hp_img;					//　ヒットポイント画像
int		reimu_player_img;				//　霊夢の画像
int		marisa_player_img;				//　魔理沙の画像
bool	player_character_mode;			//　０：霊夢　１：魔理沙
enum CharacterMode {
	REIMU,
	MARISA,
};
int		player_direction_mode;	//　プレイヤーの移動している向き（０：正面　１：左　２：右）
enum Direction {
	FRONT,	//　正面
	LEFT,	//　左
	RIGHT,	//　右
};

int player_img_count;					//　プレイヤーの画像が変わるタイミングのカウント
Floatxy player_reifu;					//　霊夢の横にある丸
float player_raifu_rot;					//　角度（回転させる）

int player_level;	//	０：レベル１（攻撃単発）　１：レベル２（）　２：レベル３（）　３：レベル４（）　４：レベル５（）
enum PlayerLevel {
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
};

//　自機の Sway 弾用の変数
Floatxy	sway_coordinate[SWAY_MAX_NUM][SWAY_NUM];				//　座標
float	sway_angle[SWAY_MAX_NUM][SWAY_NUM];						//　目的角度
bool	sway_mode[SWAY_MAX_NUM][SWAY_NUM];						//　一つ一つがうつ状態か否か　SwayMode　を使う
int		sway_num;												//　現在の番号
int		sway_count_timing;										//　弾を出すタイミングをカウントする用の変数
int		sway_rot;												//　複数の弾を出すときのための角度保存用の変数
enum SwayMode {
	MODE_WAIT,									//	０：飛んでいない（待ち状態）
	MODE_MOVE,									//	１：飛んでいる　（移動状態）
};

int		hr_sway_img;
int		km_sway_img;

//　自機（霊夢専用のサブショット）
Floatxy hr_shot_coordinate[HR_SHOT_MAX_NUM][HR_SHOT_NUM];		//　座標	
bool	hr_shot_mode[HR_SHOT_MAX_NUM][HR_SHOT_NUM];				//　一つ一つのモード			
int		hr_shot_num;											//　現在の番号
int		hr_shot_count_timing;									//　タイミングのカウント


//　自機（魔理沙用のビーム）
Floatxy km_shot_coordinate[KM_SHOT_MAX];		//　座標
float km_shot_width;							//　ビームの横の幅
float km_shot_height;							//　ビームの高さ
bool km_shot_mode;								//　モード　（０：撃っている状態　１：撃っていない状態）
int km_shot_count;								//　ビームのカウント
enum KmShotMode {
	Km_Shot_WAIT,									//　撃っていない状態
	Km_Shot_MOVE,									//　撃っている状態
};

//　グレイズ用の変数
bool glaze_mode;								//　０：シフトを押していない間グレイズモードじゃない　１：シフトを押している間グレイズモード中になる
int  glaze_mode_hr_img;							//　霊夢用のグレイズモード画像
int  glaze_mode_km_img;							//　まり作用のグレイズモード画像
enum GlazeMode {
	NotGlazeMode,								//　シフト押していない
	DoGlazeMode,								//　シフト押している
};

//　霊夢のスペルカード
Floatxy	hr_spellcard;							//　スペルカード用の座標
float	hr_spellcard_r;							//　中心から広げて敵の攻撃に重なったら消すイメージ

Floatxy km_spellcard;							//　スペルカード用の座標
Floatxy km_spellcard_coordinate;				//　スペルカードを動かす用の変数
float	km_spellcard_count;						//　秒数を数える
int		km_spellcard_img;						//　魔理沙のスペルカードの画像

int		spellcard_count;
int		spellcard_shot_mode;					//　０：スペルカード撃たない　１：カウントを待つ状態　２：スペルカード撃つ
enum SpellCardMode {
	Spellcard_COUNT,
	Spellcard_WAIT,
	Spellcard_MOVE,
};

int score;
int spellcard_num;

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
//	音
// =====================================================
int se_player_attack;
int se_level_up;
int se_hr_spellcard;
int se_km_spellcard;

void PlayerInit()
{
	// DrawStringやDrawFormatStrinで描画する文字を
	// アンチエイリアスを使用してきれいに描画する
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	//　画像の用意
	reimu_player_img = LoadGraph("data/player/Reimudot.png");		//　霊夢画像
	marisa_player_img = LoadGraph("data/player/Marisadot.png");		//　魔理沙画像
	//　グレイズモード画像
	glaze_mode_hr_img = LoadGraph("data/player/Hitbox1.png");		//　霊夢
	glaze_mode_km_img = LoadGraph("data/player/Hitbox2.png");		//　魔理沙
	//　スペルカード画像
	km_spellcard_img = LoadGraph("data/player/Spark.png");			//　スペルカードの画像
	//　HP画像
	player_hp_img = LoadGraph("data/player/playerhp.png");
	hr_sway_img = LoadGraph("data/item/Hitbox1.png");
	km_sway_img = LoadGraph("data/item/Hitbox2.png");
	//　自機開始位置
	player_coordinate.x = 223.5f;
	player_coordinate.y = 420.0f;
	player_hp = 3;
	spellcard_num = SPELLCARD_NUM;

	//　音
	se_player_attack = LoadSoundMem("data/se/Shot00.wav");
	se_level_up = LoadSoundMem("data/se/powerup.wav");
	se_hr_spellcard = LoadSoundMem("data/se/echo5.wav");
	se_km_spellcard = LoadSoundMem("data/se/aaa.wav");
//	player_hp = 3;
	player_display_handle = DISPLAY;
	player_hit_mode = No_Hit;
	player_exp_count = 0;
	player_level = 0;
	//score = 0;
	//for (int x = 0; x < HR_SHOT_MAX_NUM; x++) {
	//	for (int j = 0; j < SWAY_L2; j++) {
	//		sway_mode[x][j] = MODE_WAIT;
	//	}
	//}
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
}
void PlayerUpdate()
{
	/*if (IsKeyOn(KEY_INPUT_P) && IsKeyOn(KEY_INPUT_Q) && IsKeyOn(KEY_INPUT_B)) {
		player_hp += 10;
		player_level = 4;
	}*/


	ChangeVolumeSoundMem(SE_PLAYER_VOLUME, se_player_attack);
	ChangeVolumeSoundMem(SE_PLAYER_VOLUME, se_level_up);
	ChangeVolumeSoundMem(SE_PLAYER_VOLUME, se_hr_spellcard);
	ChangeVolumeSoundMem(SE_PLAYER_VOLUME, se_km_spellcard);

//	player_hp = 3;

	//　ウインドウモード・フルスクリーンモードの表示を行う
	//　デバック用　レベル上げ
//	if (IsKeyOn(KEY_INPUT_P))	player_level++;
//	if (IsKeyOn(KEY_INPUT_O))	player_level--;
	if (player_level >= 5)		player_level = 0;
	if (player_level < 0)		player_level = 0;
	
	//　経験値でレベリング
	if (player_exp_count >= 100) {
		if (player_level == 0) {
			player_exp_count = 0;
			player_level++;
			spellcard_num++;
			PlaySoundMem(se_level_up, DX_PLAYTYPE_BACK);
		}
		else if (player_level == 1) {
			player_exp_count = 0;
			player_level++;
			spellcard_num++;
			PlaySoundMem(se_level_up, DX_PLAYTYPE_BACK);
		}
		else if (player_level == 2) {
			player_exp_count = 0;
			player_level++;
			spellcard_num++;
			PlaySoundMem(se_level_up, DX_PLAYTYPE_BACK);
		}
		else if (player_level == 3) {
			player_exp_count = 0;
			player_level++;
			spellcard_num++;
			PlaySoundMem(se_level_up, DX_PLAYTYPE_BACK);
		}
		else if (player_level == 4) {
			player_exp_count = 0;
			//player_level++;
		}
	}

	if (spellcard_num >= 4) {
		spellcard_num = 3;
	}

	//　自機切り替え
//	if (IsKeyOn(KEY_INPUT_1)) player_character_mode = REIMU;	//　霊夢
//	if (IsKeyOn(KEY_INPUT_2)) player_character_mode = MARISA;	//　魔理沙
	//　自機のモーション
	player_img_count++;	//カウント
	//　カウントがタイミングよりも大きくなったら
	if (player_img_count >= PLAYER_IMG_TIMING) {
		//　カウントを０にする
		player_img_count = 0;
		//　プレイヤーの画像の横幅分を足す
		player_img_coordinate.x += PLAYER_IMG_WIDTH;
		//　もし一番右の画像まで行ったら　
		if (player_img_coordinate.x >= PLAYER_IMG_WIDTH_MAX) {
			//　０に戻す
			player_img_coordinate.x = 0;
		}
	}
	//　自機操作
	//　上に移動
//	if (spellcard_shot_mode != Spellcard_MOVE) {	//　スペルカードを撃っていない時は動ける
		if (CheckHitKey(KEY_INPUT_UP)) {
			if (glaze_mode == NotGlazeMode) {
				player_coordinate.y -= PLAYER_SPEED_NORMAL;
			}
			else {
				player_coordinate.y -= PLAYER_SPEED_GLAZE;
			}
			player_direction_mode = FRONT;
		}
		//　下に移動
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			if (glaze_mode == NotGlazeMode) {
				player_coordinate.y += PLAYER_SPEED_NORMAL;
			}
			else {
				player_coordinate.y += PLAYER_SPEED_GLAZE;
			}
			player_direction_mode = FRONT;
		}
		//　左に移動
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			if (glaze_mode == NotGlazeMode) {
				player_coordinate.x -= PLAYER_SPEED_NORMAL;
			}
			else {
				player_coordinate.x -= PLAYER_SPEED_GLAZE;
			}
			player_direction_mode = LEFT;
		}
		//　右に移動
		else if (CheckHitKey(KEY_INPUT_RIGHT)) {
			if (glaze_mode == NotGlazeMode) {
				player_coordinate.x += PLAYER_SPEED_NORMAL;
			}
			else {
				player_coordinate.x += PLAYER_SPEED_GLAZE;
			}
			player_direction_mode = RIGHT;
		}
		else {
			player_direction_mode = FRONT;
		}
//	}
	//　プレイヤーの向いている向きに画像を合わせるために画像の位置を変更させる
	switch (player_direction_mode) {
	case FRONT:
		//　正面or後ろ移動の時
		player_img_coordinate.y = 0;
		break;
	case LEFT:
		//　左
		player_img_coordinate.y = PLAYER_IMG_HEIGHT;
		break;
	case RIGHT:
		//　右
		player_img_coordinate.y = PLAYER_IMG_HEIGHT * 2;
		break;
	}
	//　プレイヤーの範囲制限
	if (player_coordinate.x <= BG_X_LW + PLAYER_IMG_WIDTH / 2)	player_coordinate.x = BG_X_LW + PLAYER_IMG_WIDTH / 2;	//　左
	if (player_coordinate.x >= BG_X_HW - PLAYER_IMG_WIDTH / 2)	player_coordinate.x = BG_X_HW - PLAYER_IMG_WIDTH / 2;	//　右
	if (player_coordinate.y <= BG_Y_LH + PLAYER_IMG_HEIGHT / 2)	player_coordinate.y = BG_Y_LH + PLAYER_IMG_HEIGHT / 2;	//　上
	if (player_coordinate.y >= BG_Y_HH - PLAYER_IMG_HEIGHT / 2)	player_coordinate.y = BG_Y_HH - PLAYER_IMG_HEIGHT / 2;	//　下
	//　霊夢の横の画像
	player_reifu.x = player_coordinate.x;
	player_reifu.y = player_coordinate.y;
	player_raifu_rot += PLAYER_REIFU_SPEED;
	//　グレイズモード
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		glaze_mode = DoGlazeMode;
	} else {
		glaze_mode = NotGlazeMode;
	}

	switch (player_level) {
	case LEVEL1:
		//　自機の攻撃（ Sway ）
		if (CheckHitKey(KEY_INPUT_Z)) {												//　ｚを押したとき
			sway_count_timing++;													//　タイミングを調整
			if (sway_count_timing >= SWAY_TIMING) {									//　カウントがタイミングになった時に弾を撃つ準備をする
				PlaySoundMem(se_player_attack, DX_PLAYTYPE_BACK);
				sway_count_timing = START_ZERO;										//　カウントを０に戻す
				if (sway_mode[sway_num][0] == MODE_WAIT) {
					sway_mode[sway_num][0] = MODE_MOVE;								//　動く状態にする
					sway_coordinate[sway_num][0].x = player_coordinate.x;			//　自機の位置にｘを合わせる
					sway_coordinate[sway_num][0].y = player_coordinate.y;			//　自機の位置にｙを合わせる
					sway_angle[sway_num][0] = D2R(SWAY_ROT);						//　角度
					sway_num += 1;													//　現在のナンバーを１増やす
					if (sway_num >= SWAY_MAX_NUM) {									//　もし現在のナンバーが上限を超えそうになったら
						sway_num = START_ZERO;										//　ナンバーを０からに戻す
					}
				}
			}
		}
		for (int i = 0; i < SWAY_MAX_NUM; i++) {
			for (int j = 0; j < SWAY_L4; j++) {
				if (sway_mode[i][j] == MODE_MOVE) {									//　撃つ状態だった時に
					sway_coordinate[i][j].x += cosf(sway_angle[i][j]) * SWAY_SPEED;	//　Ｘにスピードを与える
					sway_coordinate[i][j].y += sinf(sway_angle[i][j]) * SWAY_SPEED;	//　ｙにスピードを与える
				}
			}
		}
		for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
			for (int j = 0; j < 6; j++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {								//　動く状態なら
					hr_shot_coordinate[i][j].y -= HR_SHOT_SPEED;					//　真上に動かす
				}
			}
		}
		break;
	case LEVEL2:
		//　自機の攻撃（ Sway ）
		if (CheckHitKey(KEY_INPUT_Z)) {												//　ｚを押したとき
			sway_count_timing++;													//　タイミングを調整
			if (sway_count_timing >= SWAY_TIMING) {									//　カウントがタイミングになった時に弾を撃つ準備をする
				sway_count_timing = START_ZERO;										//　カウントを０に戻す
				PlaySoundMem(se_player_attack, DX_PLAYTYPE_BACK);
				for (int j = 0; j < SWAY_L2; j++) {
					if (sway_mode[sway_num][j] == MODE_WAIT) {
						sway_mode[sway_num][j] = MODE_MOVE;							//　動く状態にする
						sway_coordinate[sway_num][j].x = player_coordinate.x;		//　自機の位置にｘを合わせる
						sway_coordinate[sway_num][j].y = player_coordinate.y;		//　自機の位置にｙを合わせる
						sway_rot = SWAY_ROT - SWAY_ROT_L2 + SWAY_ROT_L2 * j;
						sway_angle[sway_num][j] = D2R(sway_rot);					//　角度
						sway_num += 1;												//　現在のナンバーを１増やす
						if (sway_num >= SWAY_MAX_NUM) {								//　もし現在のナンバーが上限を超えそうになったら
							sway_num = START_ZERO;									//　ナンバーを０からに戻す
						}
					}
				}
			}
		}
		for (int i = 0; i < SWAY_MAX_NUM; i++) {
			for (int j = 0; j < SWAY_L4; j++) {
				if (sway_mode[i][j] == MODE_MOVE) {									//　撃つ状態だった時に
					sway_coordinate[i][j].x += cosf(sway_angle[i][j]) * SWAY_SPEED;	//　Ｘにスピードを与える
					sway_coordinate[i][j].y += sinf(sway_angle[i][j]) * SWAY_SPEED;	//　ｙにスピードを与える
				}
			}
		}
		for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
			for (int j = 0; j < 6; j++) {
				if (hr_shot_mode[i][j] == MODE_MOVE) {								//　動く状態なら
					hr_shot_coordinate[i][j].y -= HR_SHOT_SPEED;					//　真上に動かす
				}
			}
		}
		break;
	case LEVEL3:
		//　自機の攻撃（ Sway ）
		if (CheckHitKey(KEY_INPUT_Z)) {												//　ｚを押したとき
			sway_count_timing++;													//　タイミングを調整
			if (sway_count_timing >= SWAY_TIMING) {									//　カウントがタイミングになった時に弾を撃つ準備をする
				PlaySoundMem(se_player_attack, DX_PLAYTYPE_BACK);
				sway_count_timing = START_ZERO;										//　カウントを０に戻す
				for (int j = 0; j < SWAY_L2; j++) {
					if (sway_mode[sway_num][j] == MODE_WAIT) {
						sway_mode[sway_num][j] = MODE_MOVE;							//　動く状態にする
						sway_coordinate[sway_num][j].x = player_coordinate.x;		//　自機の位置にｘを合わせる
						sway_coordinate[sway_num][j].y = player_coordinate.y;		//　自機の位置にｙを合わせる
						sway_rot = SWAY_ROT - SWAY_ROT_L2 + SWAY_ROT_L2 * j;
						sway_angle[sway_num][j] = D2R(sway_rot);					//　角度
						sway_num += 1;												//　現在のナンバーを１増やす
						if (sway_num >= SWAY_MAX_NUM) {								//　もし現在のナンバーが上限を超えそうになったら
							sway_num = START_ZERO;									//　ナンバーを０からに戻す
						}
					}
				}
			}
		}
		for (int i = 0; i < SWAY_MAX_NUM; i++) {
			for (int j = 0; j < SWAY_L4; j++) {
				if (sway_mode[i][j] == MODE_MOVE) {									//　撃つ状態だった時に
					sway_coordinate[i][j].x += cosf(sway_angle[i][j]) * SWAY_SPEED;	//　Ｘにスピードを与える
					sway_coordinate[i][j].y += sinf(sway_angle[i][j]) * SWAY_SPEED;	//　ｙにスピードを与える
				}
			}
		}
		break;
	case LEVEL4:
		//　自機の攻撃（ Sway ）
		if (CheckHitKey(KEY_INPUT_Z)) {												//　ｚを押したとき
			sway_count_timing++;													//　タイミングを調整
			if (sway_count_timing >= SWAY_TIMING) {									//　カウントがタイミングになった時に弾を撃つ準備をする
				PlaySoundMem(se_player_attack, DX_PLAYTYPE_BACK);
				sway_count_timing = START_ZERO;										//　カウントを０に戻す
				for (int j = 0; j < SWAY_L4; j++) {
					if (sway_mode[sway_num][j] == MODE_WAIT) {
						sway_mode[sway_num][j] = MODE_MOVE;							//　動く状態にする
						sway_coordinate[sway_num][j].x = player_coordinate.x;		//　自機の位置にｘを合わせる
						sway_coordinate[sway_num][j].y = player_coordinate.y;		//　自機の位置にｙを合わせる
						sway_rot = SWAY_ROT - SWAY_ROT_L2 * 2 + SWAY_ROT_L2 * j;
						sway_angle[sway_num][j] = D2R(sway_rot);					//　角度
						sway_num += 1;												//　現在のナンバーを１増やす
						if (sway_num >= SWAY_MAX_NUM) {								//　もし現在のナンバーが上限を超えそうになったら
							sway_num = START_ZERO;									//　ナンバーを０からに戻す
						}
					}
				}
			}
		}
		for (int i = 0; i < SWAY_MAX_NUM; i++) {
			for (int j = 0; j < SWAY_L4; j++) {
				if (sway_mode[i][j] == MODE_MOVE) {									//　撃つ状態だった時に
					sway_coordinate[i][j].x += cosf(sway_angle[i][j]) * SWAY_SPEED;	//　Ｘにスピードを与える
					sway_coordinate[i][j].y += sinf(sway_angle[i][j]) * SWAY_SPEED;	//　ｙにスピードを与える
				}
			}
		}
		break;
	case LEVEL5:
		//　自機の攻撃（ Sway ）
		if (CheckHitKey(KEY_INPUT_Z)) {												//　ｚを押したとき
			sway_count_timing++;													//　タイミングを調整
			if (sway_count_timing >= SWAY_TIMING) {									//　カウントがタイミングになった時に弾を撃つ準備をする
				PlaySoundMem(se_player_attack, DX_PLAYTYPE_BACK);
				sway_count_timing = START_ZERO;										//　カウントを０に戻す
				for (int j = 0; j < SWAY_L4; j++) {
					if (sway_mode[sway_num][j] == MODE_WAIT) {
						sway_mode[sway_num][j] = MODE_MOVE;							//　動く状態にする
						sway_coordinate[sway_num][j].x = player_coordinate.x;		//　自機の位置にｘを合わせる
						sway_coordinate[sway_num][j].y = player_coordinate.y;		//　自機の位置にｙを合わせる
						sway_rot = SWAY_ROT - SWAY_ROT_L2 * 2 + SWAY_ROT_L2 * j;
						sway_angle[sway_num][j] = D2R(sway_rot);					//　角度
						sway_num += 1;												//　現在のナンバーを１増やす
						if (sway_num >= SWAY_MAX_NUM) {								//　もし現在のナンバーが上限を超えそうになったら
							sway_num = START_ZERO;									//　ナンバーを０からに戻す
						}
					}
				}
			}
		}
		for (int i = 0; i < SWAY_MAX_NUM; i++) {
			for (int j = 0; j < SWAY_L4; j++) {
				if (sway_mode[i][j] == MODE_MOVE) {									//　撃つ状態だった時に
					sway_coordinate[i][j].x += cosf(sway_angle[i][j]) * SWAY_SPEED;	//　Ｘにスピードを与える
					sway_coordinate[i][j].y += sinf(sway_angle[i][j]) * SWAY_SPEED;	//　ｙにスピードを与える
				}
			}
		}
		break;
	}
	//　キャラ特有の攻撃（０：霊夢　１：魔理沙）
	switch (player_character_mode) {
	case REIMU:		//　霊夢
		switch (player_level) {
		case LEVEL3:
			//　自機の攻撃（ 霊夢のサブショット ）
			if (CheckHitKey(KEY_INPUT_Z)) {															//　ｚを押している時
				hr_shot_count_timing++;																//　カウント
				if (hr_shot_count_timing >= HR_SHOT_TIMING) {
					hr_shot_count_timing = START_ZERO;												//　カウントを０に戻す
					for (int i = 0; i < 2; i++) {
						hr_shot_mode[hr_shot_num][i] = MODE_MOVE;									//　動く状態にする
						hr_shot_coordinate[hr_shot_num][i].x = player_coordinate.x - 20 + 40 * i;	//　ｘ座標をプレイヤーに合わせる
						hr_shot_coordinate[hr_shot_num][i].y = player_coordinate.y;					//　ｙ座標をプレイヤーに合わせる
						hr_shot_num += 1;															//　現在の番号
						if (hr_shot_num >= HR_SHOT_MAX_NUM) {										//　現在の番号が最大値を超えると０に戻す
							hr_shot_num = START_ZERO;												//　０にする
						}
					}
				}
			}
			for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
				for (int j = 0; j < 6; j++) {
					if (hr_shot_mode[i][j] == MODE_MOVE) {							//　動く状態なら
						hr_shot_coordinate[i][j].y -= HR_SHOT_SPEED;				//　真上に動かす
					}
				}
			}
			break;
		case LEVEL4:
			//　自機の攻撃（ 霊夢のサブショット ）
			if (CheckHitKey(KEY_INPUT_Z)) {															//　ｚを押している時
				hr_shot_count_timing++;																//　カウント
				if (hr_shot_count_timing >= HR_SHOT_TIMING) {
					hr_shot_count_timing = START_ZERO;												//　カウントを０に戻す
					for (int i = 0; i < 4; i++) {
						hr_shot_mode[hr_shot_num][i] = MODE_MOVE;									//　動く状態にする
						hr_shot_coordinate[hr_shot_num][i].x = player_coordinate.x - 30 + 20 * i;	//　ｘ座標をプレイヤーに合わせる
						hr_shot_coordinate[hr_shot_num][i].y = player_coordinate.y;					//　ｙ座標をプレイヤーに合わせる
						hr_shot_num += 1;															//　現在の番号
						if (hr_shot_num >= HR_SHOT_MAX_NUM) {										//　現在の番号が最大値を超えると０に戻す
							hr_shot_num = START_ZERO;												//　０にする
						}
					}
				}
			}
			for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
				for (int j = 0; j < 6; j++) {
					if (hr_shot_mode[i][j] == MODE_MOVE) {							//　動く状態なら
						hr_shot_coordinate[i][j].y -= HR_SHOT_SPEED;				//　真上に動かす
					}
				}
			}
			break;
		case LEVEL5:
			//　自機の攻撃（ 霊夢のサブショット ）
			if (CheckHitKey(KEY_INPUT_Z)) {															//　ｚを押している時
				hr_shot_count_timing++;	//　カウント
				if (hr_shot_count_timing >= HR_SHOT_TIMING) {
					hr_shot_count_timing = START_ZERO;												//　カウントを０に戻す
					for (int i = 0; i < 6; i++) {
						hr_shot_mode[hr_shot_num][i] = MODE_MOVE;									//　動く状態にする
						hr_shot_coordinate[hr_shot_num][i].x = player_coordinate.x - 50 + 20 * i;	//　ｘ座標をプレイヤーに合わせる
						hr_shot_coordinate[hr_shot_num][i].y = player_coordinate.y;					//　ｙ座標をプレイヤーに合わせる
						if (i == 1 || i == 4) {
							hr_shot_coordinate[hr_shot_num][i].y += 20;								//　見栄え的に少しずらすとおしゃれに見えるかも
						}
						hr_shot_num += 1;															//　現在の番号
						if (hr_shot_num >= HR_SHOT_MAX_NUM) {										//　現在の番号が最大値を超えると０に戻す
							hr_shot_num = START_ZERO;												//　０にする
						}
					}
				}
			}
			for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
				for (int j = 0; j < 6; j++) {
					if (hr_shot_mode[i][j] == MODE_MOVE) {											//　動く状態なら
						hr_shot_coordinate[i][j].y -= HR_SHOT_SPEED;								//　真上に動かす
					}
				}
			}
			break;
		}
		//　霊夢のスペルカード
		if (spellcard_shot_mode == Spellcard_COUNT && spellcard_num > 0) {		//　カウントモード
			spellcard_count++;								//　カウントしていく
			if (spellcard_count >= SPELLCARD_TIMING) {		//　カウントしてもし４００フレームになったら
				spellcard_shot_mode = Spellcard_WAIT;		//　WAITモードにして撃つ準備をする
			}
		}
		if (IsKeyOn(KEY_INPUT_X)) {							//　Xを押したときに
	//	if (IsKeyOn(KEY_INPUT_X)) {
			if (spellcard_shot_mode == Spellcard_WAIT && spellcard_num > 0) {	//　WAITモードなら	
				PlaySoundMem(se_hr_spellcard, DX_PLAYTYPE_BACK);
				spellcard_num--;
				spellcard_shot_mode = Spellcard_MOVE;		//　スペルモードをMOVEに変えて撃つ
				hr_spellcard.x = player_coordinate.x;		//　プレイヤーの座標から
				hr_spellcard.y = WINDOW_H + 70;					//　プレイヤーの座標から
				//	hr_spellcard_r = START_ZERO;				//　半径は０からスタートさせる
				hr_spellcard_r = 70;
			}
		}
		if (spellcard_shot_mode == Spellcard_MOVE) {		//　もしMOVEのときは
			hr_spellcard.y -= HR_SPELLCARD_R_SPEED;			//　半径を足していって大きくしていく
			if (hr_spellcard.y <= -70) {			//　半径が５００よりも大きいときは
				spellcard_shot_mode = Spellcard_COUNT;		//　モードをカウントに変えて終了させる
				spellcard_count = START_ZERO;				//　カウントを初期化
			}
		}
		//if (IsKeyOn(KEY_INPUT_X)) {							//　Xを押したときに
		//	if (spellcard_shot_mode == Spellcard_WAIT) {	//　WAITモードなら	
		//		spellcard_shot_mode = Spellcard_MOVE;		//　スペルモードをMOVEに変えて撃つ
		//		hr_spellcard.x = player_coordinate.x;		//　プレイヤーの座標から
		//		hr_spellcard.y = player_coordinate.y;		//　プレイヤーの座標から
		//		hr_spellcard_r = START_ZERO;				//　半径は０からスタートさせる
		//	}
		//}
		//if (spellcard_shot_mode == Spellcard_MOVE) {		//　もしMOVEのときは
		//	hr_spellcard_r += HR_SPELLCARD_R_SPEED;			//　半径を足していって大きくしていく
		//	if (hr_spellcard_r >= HR_CIRCLE_SIZE) {			//　半径が５００よりも大きいときは
		//		spellcard_shot_mode = Spellcard_COUNT;		//　モードをカウントに変えて終了させる
		//		spellcard_count = START_ZERO;				//　カウントを初期化
		//	}
		//}
		break;

	case MARISA:	//　魔理沙
		switch (player_level) {
		case LEVEL1:													//　レベル１	
			km_shot_mode = Km_Shot_WAIT;								//　撃っていない状態にする
			break;
		case LEVEL2:													//　レベル２
			km_shot_mode = Km_Shot_WAIT;								//　撃っていない状態															
			break;
		case LEVEL3:													//　レベル３
			km_shot_width = KM_SHOT_L3_WIDTH;							//　ビームの幅の設定
			if (IsKeyOn(KEY_INPUT_Z)) {									//　押した瞬間にカウントを
				km_shot_count = START_ZERO;								//　０にする
			}
			if (CheckHitKey(KEY_INPUT_Z)) {								//　ｚを押したとき
				km_shot_count += KM_SHOT_SPEED;							//　カウントを足す（ビームが自機から出ている感じにするために）
				km_shot_height = player_coordinate.y - km_shot_count;	//　ビームを自機の位置からだんだんカウントした分を引いて上にビームが伸びているようにする
				km_shot_mode = Km_Shot_MOVE;							//　撃っている状態にする
				km_shot_coordinate[0].x = player_coordinate.x - PLAYER_REIFU_WIDTH - km_shot_width / 2;	//　ビーム（左側）のｘ座標を決める（※ここの km_shot_width は多分 KM_SHOT_L3_WIDTH にしたら良かった）
				km_shot_coordinate[0].y = player_coordinate.y;											//　ビーム（左側）のｙ座標
				km_shot_coordinate[1].x = player_coordinate.x + PLAYER_REIFU_WIDTH - km_shot_width / 2;	//　ビーム（右側）のｘ座標
				km_shot_coordinate[1].y = player_coordinate.y;											//　ビーム（右側）のｙ座標
			}
			else {
				km_shot_mode = Km_Shot_WAIT;							//　ｚを押していないときは撃っていない状態にする
			}
			break;
		case LEVEL4:											//　レベル４		
			km_shot_width = KM_SHOT_L4_WIDTH;					//　ビームの幅の設定
			if (IsKeyOn(KEY_INPUT_Z)) {							//　押した瞬間にカウントを
				km_shot_count = START_ZERO;								//　０にする
			}
			if (CheckHitKey(KEY_INPUT_Z)) {						//　ｚを押したとき
				km_shot_count += KM_SHOT_SPEED;							//　カウントを足す（ビームが自機から出ている感じにするために）
				km_shot_height = player_coordinate.y - km_shot_count;	//　ビームを自機の位置からだんだんカウントした分を引いて上にビームが伸びているようにする
				km_shot_mode = Km_Shot_MOVE;							//　撃っている状態にする
				km_shot_coordinate[0].x = player_coordinate.x - PLAYER_REIFU_WIDTH - km_shot_width / 2;	//　ビーム（左側）のｘ座標
				km_shot_coordinate[0].y = player_coordinate.y;											//　ビーム（左側）のｙ座標
				km_shot_coordinate[1].x = player_coordinate.x + PLAYER_REIFU_WIDTH - km_shot_width / 2;	//　ビーム（右側）のｘ座標
				km_shot_coordinate[1].y = player_coordinate.y;											//　ビーム（右側）のｙ座標
			}
			else {
				km_shot_mode = Km_Shot_WAIT;							//　ｚを押していないときは撃っていない状態にする
			}
			break;
		case LEVEL5:											//　レベル４		
			km_shot_width = KM_SHOT_L5_WIDTH;					//　ビームの幅の設定
			if (IsKeyOn(KEY_INPUT_Z)) {							//　押した瞬間にカウントを
				km_shot_count = START_ZERO;								//　０にする
			}
			if (CheckHitKey(KEY_INPUT_Z)) {						//　ｚを押したとき
				km_shot_count += KM_SHOT_SPEED;							//　カウントを足す（ビームが自機から出ている感じにするために）
				km_shot_height = player_coordinate.y - km_shot_count;	//　ビームを自機の位置からだんだんカウントした分を引いて上にビームが伸びているようにする
				km_shot_mode = Km_Shot_MOVE;							//　撃っている状態にする
				km_shot_coordinate[0].x = player_coordinate.x - PLAYER_REIFU_WIDTH - km_shot_width / 2; //　ビーム（左側）のｘ座標
				km_shot_coordinate[0].y = player_coordinate.y;											//　ビーム（左側）のｙ座標
				km_shot_coordinate[1].x = player_coordinate.x + PLAYER_REIFU_WIDTH - km_shot_width / 2;	//　ビーム（右側）のｘ座標
				km_shot_coordinate[1].y = player_coordinate.y;											//　ビーム（右側）のｙ座標
			}
			else {
				km_shot_mode = Km_Shot_WAIT;							//　ｚを押していないときは撃っていない状態にする
			}
			break;
		}
		//　魔理沙のスペルカード
		if (spellcard_shot_mode == Spellcard_COUNT) {		//　カウントモードの時
			spellcard_count++;								//　カウントを数える
			if (spellcard_count >= SPELLCARD_TIMING) {		//　カウントが４００フレームになったとき
				spellcard_shot_mode = Spellcard_WAIT;		//　モードをWAITにする
			}
		}
		if (player_level >= 2) {
			if (IsKeyOn(KEY_INPUT_X)) {							//　Xを押したとき
				if (spellcard_shot_mode == Spellcard_WAIT) {	//　WAITモードなら
					PlaySoundMem(se_km_spellcard, DX_PLAYTYPE_BACK);
					spellcard_shot_mode = Spellcard_MOVE;		//　モードをMOVEに変える
					km_spellcard.x = player_coordinate.x;		//　座標を合わせる
					km_spellcard.y = player_coordinate.y - KM_SPELLCARD_Y_ADJUSTMENT;	//　座標を合わせる
				}
			}
		}

		if (spellcard_shot_mode == Spellcard_MOVE) {		//　もしMOVEモードなら
			km_spellcard_coordinate.x += KM_SPELLCARD_SPEED_X;			//　ｘを足していく
			km_spellcard_coordinate.y -= KM_SPELLCARD_SPEED_Y;			//　ｙを引いて行って上に伸ばしていく
			if (km_spellcard_coordinate.x >= KM_SPELLCARD_SIZE) {
				km_spellcard_coordinate.x = KM_SPELLCARD_SIZE;
			}
			km_spellcard_count++;							//　カウントを数える
			if (km_spellcard_count >= KM_SPELLCARD_LONG) {	//　カウントが１２０フレームを超えたら
				spellcard_shot_mode = Spellcard_COUNT;		//　モードをカウントに戻す
				spellcard_count = START_ZERO;				//　カウントを初期化
				km_spellcard_coordinate.x = START_ZERO;				//　ｘを初期化
				km_spellcard_coordinate.y = START_ZERO;				//　ｙを初期化
				km_spellcard_count = START_ZERO;			//　カウントを初期化
			}
		}
		break;
	}

	//　swayの弾が一番上まで行ったら止める
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_L4; j++) {
			if (sway_coordinate[i][j].y <= 0) {
				sway_mode[i][j] = MODE_WAIT;	//　”とまれ！！”
			}
		}
	}
	//　霊夢のショットも上に行ったら止める
	for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
		for (int j = 0; j < HR_SHOT_NUM; j++) {
			if (hr_shot_coordinate[i][j].y <= 0) {
				hr_shot_mode[i][j] = MODE_WAIT;	//　”とまれ！！”
			}
		}
	}

	//　HITしたときに１秒無敵
	if (player_hit_mode == No_Hit) {
		player_hit_count = 0;
		player_display_handle = DISPLAY;
	} else if (player_hit_mode == Hit) {
		player_hp -= 1;
		player_hit_count = 0;
		player_hit_mode = Hit_Count;
	} else if (player_hit_mode == Hit_Count) {
		player_hit_count++;
		if (player_hit_count >= PLAYER_HIT_INVINCIBLE) {
			player_hit_mode = No_Hit;
		}
	}
	//　点滅用
	if (player_hit_mode != No_Hit) {
		player_display_handle_count++;
		if (player_display_handle_count <= 30) {
			player_display_handle_count = 0;
			if (player_display_handle == HIDDEN) player_display_handle = DISPLAY;
			else if (player_display_handle == DISPLAY) player_display_handle = HIDDEN;
		}
	}
	if (player_hp <= 0) {
		EnemyInit();
		PlayerInit();
		game_start_mode = Game_Dead;
	}
}

void PlayerDraw()
{
	//	全てのミサイルの描画処理
	SetFontSize(10);
	for (int i = 0; i < SWAY_MAX_NUM; i++) {
		for (int j = 0; j < SWAY_NUM; j++) {
			if (sway_mode[i][j] == MODE_MOVE) {	//　動いている時だけ表示する
				//DrawCircleAA(sway_coordinate[i][j].x, sway_coordinate[i][j].y, SWAY_R, CIRCLEAA_SQUARE, YELLOW, TRUE);
				if (player_character_mode == REIMU) DrawRotaGraph(sway_coordinate[i][j].x, sway_coordinate[i][j].y, 1, 0, hr_sway_img, 0);
				if (player_character_mode == MARISA) DrawRotaGraph(sway_coordinate[i][j].x, sway_coordinate[i][j].y, 1, 0, km_sway_img, 0);
				//DrawFormatString(sway_coordinate[i][j].x, sway_coordinate[i][j].y, RED, "%d %d", i, j);
			}
		}
	}
	switch (player_character_mode) {
	case REIMU:
		//　自機の隣の魔法陣
		if (player_level < 2) {
			//　レベル２以下は魔法陣一つにすることで視覚的にわかりやすくする
			DrawRectRotaGraph(player_reifu.x, player_reifu.y - PLAYER_REIFU_HEIGHT, 0, PLAYER_IMG_HEIGHT * 3, PLAYER_REIFU_SIZE, PLAYER_REIFU_SIZE, PLAYER_IMG_SAME_SIZE, player_raifu_rot, reimu_player_img, TRUE);
		}
		else {
			//　それ以外の時は２つ表示
			DrawRectRotaGraph(player_reifu.x - PLAYER_REIFU_WIDTH, player_reifu.y, 0, PLAYER_IMG_HEIGHT * 3, PLAYER_REIFU_SIZE, PLAYER_REIFU_SIZE, PLAYER_IMG_SAME_SIZE, player_raifu_rot, reimu_player_img, TRUE);
			DrawRectRotaGraph(player_reifu.x + PLAYER_REIFU_WIDTH, player_reifu.y, 0, PLAYER_IMG_HEIGHT * 3, PLAYER_REIFU_SIZE, PLAYER_REIFU_SIZE, PLAYER_IMG_SAME_SIZE, -player_raifu_rot, reimu_player_img, TRUE);
		}
		for (int i = 0; i < HR_SHOT_MAX_NUM; i++) {
			for (int j = 0; j < HR_SHOT_NUM; j++) {
				//　霊夢のショット表示
				if (hr_shot_mode[i][j] == MODE_MOVE) DrawCircleAA(hr_shot_coordinate[i][j].x, hr_shot_coordinate[i][j].y, HR_SHOT_R, CIRCLEAA_SQUARE, RED, TRUE);
			}
		}
		//　自機の描画
		if (player_display_handle == DISPLAY) DrawRectRotaGraph(player_coordinate.x, player_coordinate.y, player_img_coordinate.x, player_img_coordinate.y, PLAYER_IMG_WIDTH, PLAYER_IMG_HEIGHT, PLAYER_IMG_SAME_SIZE, 0, reimu_player_img, TRUE);
		//　グレイズモードの時
		if (glaze_mode == DoGlazeMode) {
			DrawRotaGraph(player_coordinate.x, player_coordinate.y,1,64, glaze_mode_hr_img, 1);
			//DrawCircleAA(player_coordinate.x, player_coordinate.y, PLAYER_R, CIRCLEAA_SQUARE, GetColor(255, 255, 255));
		}
		
		//　スペルカード
		if (spellcard_shot_mode == Spellcard_MOVE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawCircleAA(hr_spellcard.x, hr_spellcard.y, hr_spellcard_r, CIRCLEAA_SQUARE, GetColor(255, 255, 255));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//　薄さを戻す
		}
		break;

	case MARISA:
		//　自機の隣の魔法陣
		if (player_level < 2) {
			//　レベル２以下は魔法陣一つにすることで視覚的にわかりやすくする
			DrawRectRotaGraph(player_reifu.x, player_reifu.y - PLAYER_REIFU_HEIGHT, 0, PLAYER_IMG_HEIGHT * 3, PLAYER_REIFU_SIZE, PLAYER_REIFU_SIZE, PLAYER_IMG_SAME_SIZE, player_raifu_rot, marisa_player_img, TRUE);
		}
		else {
			//　それ以外の時は２つ表示
			DrawRectRotaGraph(player_reifu.x - PLAYER_REIFU_WIDTH, player_reifu.y, 0, PLAYER_IMG_HEIGHT * 3, PLAYER_REIFU_SIZE, PLAYER_REIFU_SIZE, PLAYER_IMG_SAME_SIZE, player_raifu_rot, marisa_player_img, TRUE);
			DrawRectRotaGraph(player_reifu.x + PLAYER_REIFU_WIDTH, player_reifu.y, 0, PLAYER_IMG_HEIGHT * 3, PLAYER_REIFU_SIZE, PLAYER_REIFU_SIZE, PLAYER_IMG_SAME_SIZE, -player_raifu_rot, marisa_player_img, TRUE);
		}
		//　ビームを撃っている時
		if (km_shot_mode == Km_Shot_MOVE) {
			for (int i = 0; i < KM_SHOT_MAX; i++) {
				//　ビームの描画
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);	//　ビームを少し薄くして表示（いい画像が見つかれば変更する）
				DrawFillBox(km_shot_coordinate[i].x, km_shot_coordinate[i].y, km_shot_coordinate[i].x + km_shot_width, km_shot_height, GetColor(255, 255, 255));
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//　薄さを戻す
			}
		}
		//　自機の描画
		if (player_display_handle == DISPLAY) DrawRectRotaGraph(player_coordinate.x, player_coordinate.y, player_img_coordinate.x, player_img_coordinate.y, PLAYER_IMG_WIDTH, PLAYER_IMG_HEIGHT, PLAYER_IMG_SAME_SIZE, 0, marisa_player_img, TRUE);
		//　グレイズモードの時
		if (glaze_mode == DoGlazeMode) {
			DrawRotaGraph(player_coordinate.x, player_coordinate.y, 1, 64, glaze_mode_km_img, 1);
		}
		//　スペルカード
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawFillBox(km_spellcard.x - km_spellcard_coordinate.x / 2, km_spellcard.y, km_spellcard.x + km_spellcard_coordinate.x / 2, km_spellcard.y + km_spellcard_coordinate.y, GetColor(255, 255, 0));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//　薄さを戻す
		break;
	}
	//DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, PLAYER_IMG_SAME_SIZE, 0, BG_frame_img, TRUE);
	////　HP
	//for (int i = 0; i < player_hp; i++) {
	//	DrawRotaGraph(BG_X_HW + 50 + 20 * i, 70, 1, 0, player_hp_img, TRUE);
	//}
	//SetFontSize(15);
	//DrawFormatString(BG_X_HW + 10, 64, WHITE, "HP:");
	//if (player_level != 4) {
	//	DrawFormatString(BG_X_HW + 10, 94, WHITE, "EXP:%d/100", player_exp_count);
	//}
	//else if (player_level == 4) {
	//	DrawFormatString(BG_X_HW + 10, 94, WHITE, "EXP:MAX", player_exp_count);
	//}
	//DrawFormatString(BG_X_HW + 10, 114, WHITE, "LEVEL:%d", player_level + 1);

	//DrawFormatString(BG_X_HW + 10, 134, WHITE, "スペルカード残り:%d/3", spellcard_num);
	//DrawFormatString(BG_X_HW + 10, 154, WHITE, "スペルカードゲージ:%d/6", spellcard_count / 60);

	//DrawFormatString(BG_X_HW + 10, 204, WHITE, "SCORE:%d", score);
	SetFontSize(10);
	
//	DrawRectGraph(player_coordinate.x - 300, player_coordinate.y - 700, 0, 0, 600, 700,  km_spellcard_img, TRUE);
//	DrawRectRotaGraph(player_coordinate.x, player_coordinate.y - 330, 0, 0, 600, 700, 1, 0, km_spellcard_img, TRUE);
	
//	DrawModiGraph(player_coordinate.x - a, 0, player_coordinate.x + a, 0 , player_coordinate.x + a, player_coordinate.y, player_coordinate.x - a, player_coordinate.y, km_spellcard_img,TRUE);


	//---------------------------デバックの確認用----------------------------
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", BG_stage_y);
//	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", sway_num);
//	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", hr_shot_num);
//	DrawFormatString(0, 60, GetColor(255, 255, 255), "現在のレベル：%d", player_level);
//	DrawFormatString(0, 80, GetColor(255, 255, 255), "%d", km_shot_width);
//	DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", spellcard_count);
//	DrawFormatString(0, 150, GetColor(255, 0, 255), "%d", player_exp_count);

//	DrawLine(BG_X_LW, 0, BG_X_LW, WINDOW_H, RED);		//　左
//	DrawLine(BG_X_HW, 0, BG_X_HW, WINDOW_H, BLUE);		//　右
//	DrawLine(0, BG_Y_LH, WINDOW_W, BG_Y_LH, GREEN);		//　上
//	DrawLine(0, BG_Y_HH, WINDOW_W, BG_Y_HH, YELLOW);		//　下
	//-----------------------------------------------------------------------
}
void PlayerExit()
{
	DeleteGraph(reimu_player_img);
	DeleteGraph(marisa_player_img);
	DeleteGraph(glaze_mode_hr_img);
	DeleteGraph(glaze_mode_km_img);
	DeleteGraph(player_hp_img);
	DeleteGraph(hr_sway_img);
	DeleteGraph(km_sway_img);
	DeleteGraph(km_spellcard_img);
	DeleteSoundMem(se_player_attack);
	DeleteSoundMem(se_level_up);
	DeleteSoundMem(se_hr_spellcard);
	DeleteSoundMem(se_km_spellcard);

}