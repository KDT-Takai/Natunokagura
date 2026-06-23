#pragma once

#include "DxLib.h"
#include "typedef.h"
#include "InputKey.h"
#include "InputMouse.h"
#include "GameMain.h"
#include "Player.h"
#include "WinMain.h"
#include "Hitshot.h"
#include <cmath>

void ExpInit();
void ExpUpdate();
void ExpDraw();
void ExpExit();


//#define EXPERIENCE_VALUE_MAX				10				//　最大数
//#define EXPERIENCE_VALUE_NUM				10				//　数
//#define EXPERIENCE_VALUE_DISTANCE			75.0f			//　ランダムで配置（敵からの距離）
//#define EXPERIENCE_VALUE_R					5				//　経験値のサイズ
//#define EXPERIENCE_VALUE_PLAYER_R			5				//　当たり判定
//#define EXPERIENCE_VALUE_ABSORPTION			35				//　吸収する距離
//#define EXPERIENCE_VALUE_SPEED				1.5				//　落下速度
//#define EXPERIENCE_VALUE_PLAYER_SPEED		4.0f				//　落下速度
//#define EXPERIENCE_VALUE					50
//#define EXPERIENCE_VALUE_AMOUNT				5