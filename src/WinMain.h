#pragma once

#include "DxLib.h"
#include "typedef.h"
#include "InputKey.h"
#include "InputMouse.h"
#include "GameMain.h"
#include "Player.h"
#include "Enemy.h"
#include "Hitshot.h"
#include "EXP.h"
#include "Menu.h"
#include "Character.h"
#include "GameClear.h"
#include "GameDead.h"
#include "ui.h"
#include <cmath>

// ============================================================
//	 ç\ë¢ëÃ
// ============================================================
struct int2
{
	int x = 0, y = 0;
};

#define PI		 3.141592653589793
#define RadToDeg 57.29577951f
#define R2D(rad) rad * RadToDeg

#define DegToRad 0.017453293f
#define D2R(deg) deg * DegToRad

#define BLACK	GetColor(0, 0, 0)
#define WHITE	GetColor(255, 255, 255)
#define RED		GetColor(255, 0, 0)
#define GREEN	GetColor(60, 179, 113)
#define BLUE	GetColor(0, 0, 255)
#define YELLOW	GetColor(255, 255, 0)
#define PINK	GetColor(255, 0, 255)
#define SKYBLUE	GetColor(0, 255, 255)

#define WINDOW_W	640
#define WINDOW_H	480

#define IMG_SIZE	32

// â~Ç∆â~Ç∆ÇÃìñÇΩÇËîªíË
bool isHit(int x1, int y1, int r1, int x2, int y2, int r2);