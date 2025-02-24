#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CGhost.h"
#include "mygame.h"
#define WHITE RGB(255, 255, 255)

namespace game_framework {

	CGhost::CGhost(int x, int y) {
		Initialize(x, y);
	}
	CGhost::~CGhost() {
	}

	void CGhost::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
		isAlive = true;
		isFighted = false;
		isMoving = true;
		switchState = true;
		followApu = true;
		curMode = 1;
		curState = 1;
		curDirect = 1;
		dieCounter = 18;
	}

	int  CGhost::GetX1() { return pos.x; }
	int  CGhost::GetY1() { return pos.y; }
	int  CGhost::GetX2() { return pos.x + ghost_up.Width(); }
	int  CGhost::GetY2() { return pos.y + ghost_up.Height(); }
	int  CGhost::GetCurAnimationNum() {
		switch (curState) {
		case 1: return ghost_up.GetCurrentBitmapNumber();
		case 2: return ghost_down.GetCurrentBitmapNumber();
		case 3: return ghost_die.GetCurrentBitmapNumber();
		default: return 0;
		}
	}
	int CGhost::GetCurAnimationLastNum() {
		switch (curState) {
		case 1: return ghost_up.GetLastBitmapNumber();
		case 2: return ghost_down.GetLastBitmapNumber();
		case 3: return ghost_die.GetLastBitmapNumber();
		default: return 0;
		}
	}
	void CGhost::ResetCurAnimation() {
		if (curState == 1) ghost_up.Reset();
		else if (curState == 2) ghost_down.Reset();
		else if (curState == 3) ghost_die.Reset();
	}
	void CGhost::SetXY(int nx, int ny) {
		pos.x = nx; pos.y = ny;
	}
	void CGhost::SetMoving() {
		const int STEP = 5;
		if (curDirect == 1)
			pos.y -= STEP;
		else if (curDirect == 2)
			pos.y += STEP;
		else if (curDirect == 3)
			pos.x -= STEP;
		else if (curDirect == 4)
			pos.x += STEP;
		else
			;
	}
	void CGhost::SetAlive(bool alive) { isAlive = alive; }
	void CGhost::SetFighted(bool fighted) { isFighted = fighted; }
	void CGhost::SetMode(int mode) { curMode = mode; }
	void CGhost::SetState(int state) { curState = state; }
	void CGhost::SetFork() {

	}
	
	bool CGhost::IsAlive() { return isAlive; }
	bool CGhost::IsFighted() { return isFighted; }

	bool CGhost::HitApu(CApu *apu) {
		int x1 = apu->GetX1();
		int y1 = apu->GetY1();
		//int x2 = apu->GetX1() + 64;//apu->GetX2();
		//int y2 = apu->GetY1() + 64;// apu->GetY2();
		int x3 = this->GetX1();
		int y3 = this->GetY1();
		int x4 = this->GetX1() + 64;
		int y4 = this->GetY1() + 64;
		//return (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4);
		return (x1 >= x3 && y1 >= y3 && x1 <= x4 && y1 <= y4);
	}

	void CGhost::FollowApu(CGameMap *map, CApu *apu) {
		const int RANGE = 65;
		int xUp = pos.x, yUp = pos.y - RANGE;
		int xDown = pos.x, yDown = pos.y + RANGE;
		int xLeft = pos.x - RANGE, yLeft = pos.y;
		int xRight = pos.x + RANGE, yRight = pos.y;
		float disUp = (float)sqrt((double)((xUp - apu->GetX1())*(xUp - apu->GetX1()) + (yUp - apu->GetY1())*(yUp - apu->GetY1())));
		float disDown = (float)sqrt((double)((xDown - apu->GetX1())*(xDown - apu->GetX1()) + (yDown - apu->GetY1())*(yDown - apu->GetY1())));
		float disLeft = (float)sqrt((double)((xLeft - apu->GetX1())*(xLeft - apu->GetX1()) + (yLeft - apu->GetY1())*(yLeft - apu->GetY1())));
		float disRight = (float)sqrt((double)((xRight - apu->GetX1())*(xRight - apu->GetX1()) + (xRight - apu->GetY1())*(xRight - apu->GetY1())));
		switch (WhereIsApu(apu)) {
		case 0:
			curDirect = 0;
			break;
		case 1:
			if (disUp <= disRight && map->IsEmpty(pos.x, pos.y - RANGE)) curDirect = 1;
			else if (map->IsEmpty(pos.x + RANGE, pos.y)) curDirect = 4;
			else if (map->IsEmpty(pos.x, pos.y + RANGE)) curDirect = 2;
			else if (map->IsEmpty(pos.x - RANGE, pos.y)) curDirect = 3;
			else curDirect = 0;
			break;
		case 2:
			if (disUp <= disLeft && map->IsEmpty(pos.x, pos.y - RANGE)) curDirect = 1;
			else if (map->IsEmpty(pos.x - RANGE, pos.y)) curDirect = 3;
			else if (map->IsEmpty(pos.x, pos.y + RANGE)) curDirect = 2;
			else if (map->IsEmpty(pos.x + RANGE, pos.y)) curDirect = 4;
			else curDirect = 0;
			break;
		case 3:
			if (disDown <= disLeft && map->IsEmpty(pos.x, pos.y + RANGE)) curDirect = 2;
			else if (map->IsEmpty(pos.x - RANGE, pos.y)) curDirect = 3;
			else if (map->IsEmpty(pos.x, pos.y - RANGE)) curDirect = 1;
			else if (map->IsEmpty(pos.x + RANGE, pos.y)) curDirect = 4;
			else curDirect = 0;
			break;
		case 4:
			if (disDown <= disRight && map->IsEmpty(pos.x, pos.y + RANGE)) curDirect = 2;
			else if (map->IsEmpty(pos.x + RANGE, pos.y)) curDirect = 4;
			else if (map->IsEmpty(pos.x, pos.y - RANGE)) curDirect = 1;
			else if (map->IsEmpty(pos.x - RANGE, pos.y)) curDirect = 3;
			else curDirect = 0;
			break;
		default:
			break;
		}
	}
	int CGhost::WhereIsApu(CApu *apu) {
		int X1 = pos.x, Y1 = pos.y;
		int X2 = apu->GetX1(), Y2 = apu->GetY1();
		float dis = (float)sqrt((double)((X2 - X1)*(X2 - X1) + (Y2 - Y1)*(Y2 - Y1)));
		if (dis < 0.001)
			return 0;
		X2 -= X1;
		Y2 -= Y1;
		if (X2 >= 0 && Y2 <= 0) return 1;       // 右上
		else if (X2 <= 0 && Y2 <= 0) return 2;  // 左上
		else if (X2 <= 0 && Y2 >= 0) return 3;  // 左下
		else if (X2 >= 0 && Y2 >= 0) return 4;  // 右下
		else return 0;
	}
	void CGhost::SwitchState(CGameMap *map, CApu *apu) {
		if (switchState) {
			curMode = 2;
			ResetCurAnimation();
			if (curState == 1) {
				curState = 2;
				FollowApu(map, apu);
				//followApu = true;
				//isMoving = true;
			}
			else if (curState == 2)  curState = 1;
			else if (curState == 3) dieCounter = 18;
		}
		switchState = false;
	}

	void CGhost::OnMove(CGameMap *map, CApu *apu) {
		if (isAlive) {
			if (isFighted) {
				curState = 3;
			} else {
				if (apu->GetMode() == 2) SwitchState(map, apu);
				else switchState = true;

				if (HitApu(apu)) {
					CAudio::Instance()->Play(AUDIO_LOSE);
					curMode = 1;
					apu->SetState(9);
				}
			}	

			if (curMode == 2) {
				if (GetCurAnimationNum() == GetCurAnimationLastNum()) {
					curMode = 1;
					return;
				}
				if (curState == 1) {
					for (int i = 0; i < 4; i++) ghost_up.OnMove();
				}
				else if (curState == 2) {
					for (int i = 0; i < 4; i++) ghost_down.OnMove();
					SetMoving();
				}
			}

			if (curState == 3) {
				for (int i = 0; i < 2; i++) ghost_die.OnMove();
			}
		}
	}

	void CGhost::OnShow(CGameMap *map) {
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
		if (isAlive) {
			switch (curState) {
			case 1:
				ghost_up.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y));
				ghost_up.OnShow();
				break;
			case 2:

				ghost_down.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y));
				ghost_down.OnShow();
				//fork1.SetTopLeft(map->ScreenX(pos_show.x - 50), map->ScreenY(pos_show.y));
				//fork2.SetTopLeft(map->ScreenX(pos_show.x + 50), map->ScreenY(pos_show.y));
				//fork3.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y - 80));
				//fork4.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y + 80));
				break;
			case 3:
				dieCounter--;
				if (dieCounter < 0) {
					isAlive = false;
				}
				ghost_die.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y));
				ghost_die.OnShow();
				break;
			default:
				break;
			}
		}
	}

	CBallon::CBallon(int x, int y) : CGhost::CGhost(x, y) {}
	CBallon::~CBallon() {}
	void CBallon::LoadBitmap() {

		ghost_up.AddBitmap(IDB_BALLOON5, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON5, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON4, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON3, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON1, WHITE);
		
		ghost_down.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON3, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON4, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON5, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON5, WHITE);

		ghost_die.AddBitmap(IDB_BALLOON_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE2, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, WHITE);

		fork1.LoadBitmap(IDB_FORK, WHITE);
		fork2.LoadBitmap(IDB_FORK, WHITE);
		fork3.LoadBitmap(IDB_FORK, WHITE);
		fork4.LoadBitmap(IDB_FORK, WHITE);
	}

	CBat::CBat(int x, int y) : CGhost::CGhost(x, y) {}
	CBat::~CBat() {}
	void CBat::LoadBitmap() {
		ghost_up.AddBitmap(IDB_BAT1, WHITE);
		ghost_up.AddBitmap(IDB_BAT1, WHITE);
		ghost_up.AddBitmap(IDB_BAT2, WHITE);
		ghost_up.AddBitmap(IDB_BAT2, WHITE);
		ghost_up.AddBitmap(IDB_BAT3, WHITE);
		ghost_up.AddBitmap(IDB_BAT3, WHITE);

		ghost_down.AddBitmap(IDB_BAT3, WHITE);
		ghost_down.AddBitmap(IDB_BAT3, WHITE);
		ghost_down.AddBitmap(IDB_BAT2, WHITE);
		ghost_down.AddBitmap(IDB_BAT2, WHITE);
		ghost_down.AddBitmap(IDB_BAT1, WHITE);
		ghost_down.AddBitmap(IDB_BAT1, WHITE);

		ghost_die.AddBitmap(IDB_BAT_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_BAT_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_BAT_DIE2, WHITE);
		ghost_die.AddBitmap(IDB_BAT_DIE3, WHITE);
		ghost_die.AddBitmap(IDB_BAT_DIE3, WHITE);

		fork1.LoadBitmap(IDB_FORK, WHITE);
		fork2.LoadBitmap(IDB_FORK, WHITE);
		fork3.LoadBitmap(IDB_FORK, WHITE);
		fork4.LoadBitmap(IDB_FORK, WHITE);
	}

	CPumpkin::CPumpkin(int x, int y) : CGhost::CGhost(x, y) {}
	CPumpkin::~CPumpkin() {}
	void CPumpkin::LoadBitmap() {
		/*ghost_up.AddBitmap(IDB_PUMPKIN_UP, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_UP, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_UP, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_UP, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_UP, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_UP, WHITE);*/
		ghost_up.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_up.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);

		ghost_down.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_down.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_down.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_down.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_down.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);
		ghost_down.AddBitmap(IDB_PUMPKIN_DOWN, WHITE);

		ghost_left.AddBitmap(IDB_PUMPKIN_LEFT, WHITE);
		ghost_left.AddBitmap(IDB_PUMPKIN_LEFT, WHITE);
		ghost_left.AddBitmap(IDB_PUMPKIN_LEFT, WHITE);
		ghost_left.AddBitmap(IDB_PUMPKIN_LEFT, WHITE);
		ghost_left.AddBitmap(IDB_PUMPKIN_LEFT, WHITE);
		ghost_left.AddBitmap(IDB_PUMPKIN_LEFT, WHITE);

		ghost_right.AddBitmap(IDB_PUMPKIN_RIGHT, WHITE);
		ghost_right.AddBitmap(IDB_PUMPKIN_RIGHT, WHITE);
		ghost_right.AddBitmap(IDB_PUMPKIN_RIGHT, WHITE);
		ghost_right.AddBitmap(IDB_PUMPKIN_RIGHT, WHITE);
		ghost_right.AddBitmap(IDB_PUMPKIN_RIGHT, WHITE);
		ghost_right.AddBitmap(IDB_PUMPKIN_RIGHT, WHITE);

		ghost_die.AddBitmap(IDB_PUMPKIN_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_PUMPKIN_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_PUMPKIN_DIE2, WHITE);
		ghost_die.AddBitmap(IDB_PUMPKIN_DIE2, WHITE);
		ghost_die.AddBitmap(IDB_PUMPKIN_DIE3, WHITE);
		ghost_die.AddBitmap(IDB_PUMPKIN_DIE3, WHITE);

		fork1.LoadBitmap(IDB_FORK, WHITE);
		fork2.LoadBitmap(IDB_FORK, WHITE);
		fork3.LoadBitmap(IDB_FORK, WHITE);
		fork4.LoadBitmap(IDB_FORK, WHITE);
	}
}