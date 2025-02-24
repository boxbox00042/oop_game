#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CTrap.h"
#include "mygame.h"
#define WHITE RGB(255, 255, 255)

namespace game_framework {
	
	CTrap::CTrap(int x, int y) {
		
	}
	CTrap::~CTrap() {}
	
	int  CTrap::GetX1() { return pos.x; }
	int  CTrap::GetY1() { return pos.y; }

	int  CTrap::GetCurAnimationNum() {
		switch (curState) {
		case 1: return trap_up.GetCurrentBitmapNumber();
		case 2: return trap_down.GetCurrentBitmapNumber();
		default: return 0;
		}
	}
	int CTrap::GetCurAnimationLastNum() {
		switch (curState) {
		case 1: return trap_up.GetLastBitmapNumber();
		case 2: return trap_down.GetLastBitmapNumber();
		default: return 0;
		}
	}
	void CTrap::ResetCurAnimation() {
		if (curState == 1) trap_up.Reset();
		else if (curState == 2) trap_down.Reset();
	}

	void CTrap::SetXY(int nx, int ny) {
		pos.x = nx; pos.y = ny;
	}
	void CTrap::SetMode(int mode) { curMode = mode; }
	void CTrap::SetState(int state) { curState = state; }

	CClaw::CClaw(int x, int y) : CTrap::CTrap(x, y) {
		Initialize(x, y);
	}
	CClaw::~CClaw() {}
	void CClaw::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
		switchState = true;
		curMode = 1;
		curState = 1;
		counter = 30;
	}
	void CClaw::LoadBitmap() {
		trap_up.AddBitmap(IDB_CLAW1, WHITE);
		trap_up.AddBitmap(IDB_CLAW2, WHITE);
		trap_up.AddBitmap(IDB_CLAW3, WHITE);
		trap_up.AddBitmap(IDB_CLAW4, WHITE);
		trap_up.AddBitmap(IDB_CLAW5, WHITE);
		trap_up.AddBitmap(IDB_CLAW6, WHITE);
		trap_up.AddBitmap(IDB_CLAW7, WHITE);

		trap_down.AddBitmap(IDB_CLAW7, WHITE);
		trap_down.AddBitmap(IDB_CLAW6, WHITE);
		trap_down.AddBitmap(IDB_CLAW5, WHITE);
		trap_down.AddBitmap(IDB_CLAW4, WHITE);
		trap_down.AddBitmap(IDB_CLAW3, WHITE);
		trap_down.AddBitmap(IDB_CLAW2, WHITE);
		trap_down.AddBitmap(IDB_CLAW1, WHITE);
	}
	void CClaw::SwitchState() {
		/* if apu hit ghost then curMode = 2*/
		if (curMode == 1) curMode = 2;

	};
	void CClaw::OnMove(CGameMap *map, CApu *apu) {};
	void CClaw::OnShow(CGameMap *map) {};

	CSpike::CSpike(int x, int y) : CTrap::CTrap(x, y) {
		Initialize(x, y);
	}
	CSpike::~CSpike() {}
	void CSpike::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
		switchState = true;
		curMode = 1;
		curState = 1;
		counter = 30;
	}
	void CSpike::LoadBitmap() {
		trap_up.AddBitmap(IDB_SPIKE1, WHITE);
		trap_up.AddBitmap(IDB_SPIKE2, WHITE);
		trap_up.AddBitmap(IDB_SPIKE3, WHITE);
		trap_up.AddBitmap(IDB_SPIKE4, WHITE);
		trap_up.AddBitmap(IDB_SPIKE5, WHITE);
		trap_up.AddBitmap(IDB_SPIKE6, WHITE);

		trap_down.AddBitmap(IDB_SPIKE6, WHITE);
		trap_down.AddBitmap(IDB_SPIKE5, WHITE);
		trap_down.AddBitmap(IDB_SPIKE4, WHITE);
		trap_down.AddBitmap(IDB_SPIKE3, WHITE);
		trap_down.AddBitmap(IDB_SPIKE2, WHITE);
		trap_down.AddBitmap(IDB_SPIKE1, WHITE);
	}
	void CSpike::SwitchState() {
		/* if apu hit ghost then curMode = 2*/
		
	
	};
	void CSpike::OnMove(CGameMap *map, CApu *apu) {
		if (curMode == 2) {
			if (GetCurAnimationNum() == GetCurAnimationLastNum()) {
				ResetCurAnimation();
				curMode = 1;
				return;
			}
			if (curState == 1) {
				for (int i = 0; i < 4; i++) trap_up.OnMove();
			}
		}
	};
	void CSpike::OnShow(CGameMap *map) {
		trap_up.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y));
		trap_up.OnShow();
	};

	CBouncingBrick::CBouncingBrick(int x, int y) : CTrap::CTrap(x, y) {
		Initialize(x, y);
	}
	CBouncingBrick::~CBouncingBrick() {}
	void CBouncingBrick::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
		switchState = true;
		curMode = 1;
		curState = 1;
		counter = 30;
	}
	void CBouncingBrick::LoadBitmap() {
		/*trap_up.AddBitmap(IDB_SPIKE1, WHITE);
		trap_up.AddBitmap(IDB_SPIKE2, WHITE);
		trap_up.AddBitmap(IDB_SPIKE3, WHITE);
		trap_up.AddBitmap(IDB_SPIKE4, WHITE);
		trap_up.AddBitmap(IDB_SPIKE5, WHITE);
		trap_up.AddBitmap(IDB_SPIKE6, WHITE);

		trap_down.AddBitmap(IDB_SPIKE6, WHITE);
		trap_down.AddBitmap(IDB_SPIKE5, WHITE);
		trap_down.AddBitmap(IDB_SPIKE4, WHITE);
		trap_down.AddBitmap(IDB_SPIKE3, WHITE);
		trap_down.AddBitmap(IDB_SPIKE2, WHITE);
		trap_down.AddBitmap(IDB_SPIKE1, WHITE);*/
	}
	void CBouncingBrick::SwitchState() {
		/* if apu hit ghost then curMode = 2*/
		if (curMode == 1) curMode = 2;

	};
	void CBouncingBrick::OnMove(CGameMap *map, CApu *apu) {};
	void CBouncingBrick::OnShow(CGameMap *map) {};
}
