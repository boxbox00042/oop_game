#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <iostream>

#define WHITE RGB(255, 255, 255)
using namespace std;

namespace game_framework {

	/* 這個class為遊戲的遊戲開頭畫面物件*/

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g) {

	}

	void CGameStateInit::OnInit() {
		ShowInitProgress(0);

		curPage = 1;
		curLevel = 0;

		page_begin.AddBitmap(IDB_BEGIN_PAGE1);
		page_begin.AddBitmap(IDB_BEGIN_PAGE1);
		page_begin.AddBitmap(IDB_BEGIN_PAGE2);
		page_begin.AddBitmap(IDB_BEGIN_PAGE2);
		page_aboutus.LoadBitmap(IDB_ABOUT_PAGE);
		page_explain.LoadBitmap(IDB_EXPLAIN_PAGE);

		button_begin.AddBitmap(IDB_BUTTON_BEGIN1, WHITE);
		button_begin.AddBitmap(IDB_BUTTON_BEGIN2, WHITE);
		button_aboutus.LoadBitmap(IDB_BUTTON_ABOUTUS, WHITE);
		button_explain.LoadBitmap(IDB_BUTTON_EXPLAIN, WHITE);
		button_back.LoadBitmap(IDB_BUTTON_BACK);

		button_home.AddBitmap(IDB_BUTTON_HOME1, WHITE);
		button_home.AddBitmap(IDB_BUTTON_HOME2, WHITE);
		page_level.LoadBitmap(IDB_LEVEL_PAGE, WHITE);
		levels[0].LoadBitmap(IDB_LEVEL1, WHITE);
		levels[1].LoadBitmap(IDB_LEVEL2, WHITE);
		levels[2].LoadBitmap(IDB_LEVEL3, WHITE);
	}

	void CGameStateInit::OnBeginState() {
		isBeginButtonDown = false;
		isAboutusButtonDown = false;
		isExplainButtonDown = false;
		isBackButtonDown = false;
		isHomeButtonDown = false;
		for (int i = 0; i < 3; i++) isLevelButtonDown[i] = false;
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE) {
			CGame::Instance()->SetLevel(curLevel);
			GotoGameState(GAME_STATE_RUN);
		}
		else if (nChar == KEY_ESC) {
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
		}
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point) {
		int x1 = point.x, y1 = point.y;
		int x2, y2, x3, y3;
		int x4, y4, x5, y5;
		int x6, y6, x7, y7;
		if (curPage == 1) {
			x2 = button_begin.Left();
			y2 = button_begin.Top();
			x3 = x2 + button_begin.Width();
			y3 = x2 + button_begin.Height();
			x4 = button_aboutus.Left();
			y4 = button_aboutus.Top();
			x5 = x4 + button_aboutus.Width();
			y5 = y4 + button_aboutus.Height();
			x6 = button_explain.Left();
			y6 = button_explain.Top();
			x7 = x6 + button_explain.Width();
			y7 = y6 + button_explain.Height();
			if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
				isBeginButtonDown = true;
			}
			else if (x1 >= x4 && x1 <= x5 && y1 >= y4 && y1 <= y5) {
				isAboutusButtonDown = true;
			}
			else if (x1 >= x6 && x1 <= x7 && y1 >= y6 && y1 <= y7) {
				isExplainButtonDown = true;
			}
		}
		else if (curPage == 2) {
			for (int i = 0; i < 3; i++) {
				x2 = levels[i].Left();
				y2 = levels[i].Top();
				x3 = x2 + levels[i].Width();
				y3 = y2 + levels[i].Height();
				x4 = button_home.Left();
				y4 = button_home.Top();
				x5 = x4 + button_home.Width();
				y5 = y4 + button_home.Height();
				if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
					isLevelButtonDown[i] = true;
					curLevel = i + 1;
					break;
				}

			}
			if (x1 >= x4 && x1 <= x5 && y1 >= y4 && y1 <= y5) {
				isHomeButtonDown = true;
			}

		}
		else if (curPage == 3 || curPage == 4) {
			x2 = button_back.Left();
			y2 = button_back.Top();
			x3 = x2 + button_back.Width();
			y3 = y2 + button_back.Height();
			if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
				isBackButtonDown = true;
			}
		}
	}

	void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point) {}

	void CGameStateInit::OnMove() {
		if (curPage == 1) {
			page_begin.OnMove();
			if (isBeginButtonDown) {
				if (button_begin.GetCurrentBitmapNumber() == button_begin.GetLastBitmapNumber()) {
					button_begin.Reset();
					Sleep(500);
					isBeginButtonDown = false;
					curPage = 2;
					return;
				}
				CAudio::Instance()->Play(AUDIO_BUTTON);
				button_begin.OnMove();
			}
			if (isAboutusButtonDown) {
				CAudio::Instance()->Play(AUDIO_BUTTON);
				curPage = 3;
				isAboutusButtonDown = false;
				return;
			}
			if (isExplainButtonDown) {
				CAudio::Instance()->Play(AUDIO_BUTTON);
				curPage = 4;
				isExplainButtonDown = false;
				return;
			}
		}
		else if (curPage == 2) {
			for (int i = 0; i < 3; i++) {
				if (isLevelButtonDown[i]) {
					CAudio::Instance()->Play(AUDIO_BUTTON);
					Sleep(500);
					CGame::Instance()->SetLevel(curLevel);
					GotoGameState(GAME_STATE_RUN);
					break;
				}
			}
			if (isHomeButtonDown) {
				if (button_home.GetCurrentBitmapNumber() == button_home.GetLastBitmapNumber()) {
					button_home.Reset();
					Sleep(500);
					isHomeButtonDown = false;
					curPage = 1;
					return;
				}
				CAudio::Instance()->Play(AUDIO_BUTTON);
				button_home.OnMove();
			}

		}
		else if (curPage == 3) {
			if (isBackButtonDown) {
				CAudio::Instance()->Play(AUDIO_BUTTON);
				curPage = 1;
				isBackButtonDown = false;
			}
		}
		else if (curPage == 4) {
			if (isBackButtonDown) {
				CAudio::Instance()->Play(AUDIO_BUTTON);
				curPage = 1;
				isBackButtonDown = false;
			}
		}
	}

	void CGameStateInit::OnShow()
	{
		if (curPage == 1) {
			page_begin.SetTopLeft(0, 65);
			page_begin.OnShow();
			button_aboutus.SetTopLeft(560, 75);
			button_aboutus.ShowBitmap();
			button_explain.SetTopLeft(485, 75);
			button_explain.ShowBitmap();
			button_begin.SetTopLeft(550, 330);
			button_begin.OnShow();
		}
		else if (curPage == 2) {
			page_level.SetTopLeft(0, 60);
			page_level.ShowBitmap();
			levels[0].SetTopLeft(80, 170);
			levels[1].SetTopLeft(80, 270);
			levels[2].SetTopLeft(155, 270);
			levels[0].ShowBitmap();
			levels[1].ShowBitmap();
			levels[2].ShowBitmap();
			button_home.SetTopLeft(5, 65);
			button_home.OnShow();
		}
		else if (curPage == 3) {
			page_aboutus.SetTopLeft(0, 120);
			page_aboutus.ShowBitmap();
			button_back.SetTopLeft(30, 350);
			button_back.ShowBitmap();
		}
		else if (curPage == 4) {
			page_explain.SetTopLeft(0, 65);
			page_explain.ShowBitmap();
			button_back.SetTopLeft(20, 420);
			button_back.ShowBitmap();
		}
	}

	/* 這個class為遊戲的結束狀態(Game Over)*/

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
		curLevel = CGame::Instance()->GetLevel();
		curState = CGame::Instance()->GetFinish(curLevel);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 45; // 1.5 seconds
		curLevel = CGame::Instance()->GetLevel();
		curState = CGame::Instance()->GetFinish(curLevel);
		apu_curMode = 2;

	}

	void CGameStateOver::OnInit()
	{
		ShowInitProgress(66);
		ShowInitProgress(100);

		apu_relive.AddBitmap(IDB_APU_RELIVE1, WHITE);
		apu_relive.AddBitmap(IDB_APU_RELIVE2, WHITE);
		apu_relive.AddBitmap(IDB_APU_RELIVE3, WHITE);
		apu_relive.AddBitmap(IDB_APU_RELIVE4, WHITE);
		apu_relive.AddBitmap(IDB_APU_RELIVE5, WHITE);
		apu_relive.AddBitmap(IDB_APU_RELIVE5, WHITE);
	}

	void CGameStateOver::OnMove()
	{
		if (curState) {
			;
		}
		else {
			if (apu_relive.GetCurrentBitmapNumber() == apu_relive.GetLastBitmapNumber()) {
				apu_curMode = 1;
			}
			if (apu_curMode == 2) {
				apu_relive.OnMove();
				apu_relive.OnMove();
			}
		}

		counter--;
		if (counter < 0) {
			apu_curMode = 2;
			apu_relive.Reset();
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateOver::OnShow()
	{
		if (curState)
		{
			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CFont f, *fp;
			f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 0));
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, "Apu Succeed!");
			pDC->TextOut(240, 210, str);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		}
		else {
			POINT pos = CGame::Instance()->GetApuXY();
			apu_relive.SetTopLeft(pos.x, pos.y);
			apu_relive.OnShow();
		}
	}

	/* 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡 */

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g) {
		curLevel = CGame::Instance()->GetLevel();

	}

	CGameStateRun::~CGameStateRun() {
		delete gamemap;
		delete apu;
		for (unsigned int i = 0; i < ghost.size(); i++) delete ghost[i];
		//ghost.clear();
	}

	void CGameStateRun::OnBeginState() {
		overCounter = 30;	// 5 seconds
		curLevel = CGame::Instance()->GetLevel();
		isMenuButtonDown = false;
		delete gamemap;
		delete apu;
		for (unsigned int i = 0; i < ghost.size(); i++) delete ghost[i];
		ghost.clear();
		switch (curLevel) {
		case 1:
			apu = new CApu(130, 390);
			gamemap = new CGameMap_1();

			AddGhost(1, 65 * 13, 390);

			break;
		case 2:
			apu = new CApu(130, 390);
			gamemap = new CGameMap_2();

			AddGhost(1, 65 * 3, 390);
			AddGhost(2, 65 * 13, 390);
			break;
		case 3:
			apu = new CApu(130, 390);
			gamemap = new CGameMap_3();

			AddGhost(1, 65 * 3, 390);
			AddGhost(2, 65 * 7, 390);
			AddGhost(3, 65 * 13, 390);

			break;
		default:
			break;
		}
		button_menu.AddBitmap(IDB_BUTTON_MENU1, WHITE);
		button_menu.AddBitmap(IDB_BUTTON_MENU2, WHITE);
		gamemap->LoadBitmap();
		for (unsigned int i = 0; i < ghost.size(); i++)
			ghost[i]->LoadBitmap();
		apu->LoadBitmap();


	}

	void CGameStateRun::OnInit() {
		ShowInitProgress(33);
		ShowInitProgress(50);
		isMenuButtonDown = false;

		CAudio::Instance()->Load(AUDIO_BGM, "sounds\\bgm.mp3");
		CAudio::Instance()->Load(AUDIO_WIN, "sounds\\win.mp3");
		CAudio::Instance()->Load(AUDIO_LOSE, "sounds\\lose.mp3");
		CAudio::Instance()->Load(AUDIO_FIGHT, "sounds\\fight.mp3");
		CAudio::Instance()->Load(AUDIO_BUTTON, "sounds\\button.mp3");
		CAudio::Instance()->Play(AUDIO_BGM, true);

		gamemap = NULL;
		apu = NULL;
		for (unsigned int i = 0; i < ghost.size(); i++) ghost[i] = NULL;

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
		const char KEY_LEFT = 0x25;
		const char KEY_UP = 0x26;
		const char KEY_RIGHT = 0x27;
		const char KEY_DOWN = 0x28;
		const char KEY_Q = 0x51;
		int apuX1 = apu->GetX1();
		int apuY1 = apu->GetY1();
		int apuX2 = apu->GetX2();
		int apuY2 = apu->GetY2();
		int exist = -1;
		int RANGE = 65;

		if (apu->GetMode() == 1) {
			apu->SetMode(2);
		}
		else { return; }

		if (nChar == KEY_Q) {
			apu->SetXY(65 * 17, 65 * 6);
			curKeyState = 10;
		}
		if (nChar == KEY_UP) {
			curKeyState = 1;
			exist = TheGhostNearbyApu(apuX1, apuY1 - RANGE, apuX2, apuY2 - RANGE);
		}
		if (nChar == KEY_DOWN) {
			curKeyState = 2;
			exist = TheGhostNearbyApu(apuX1, apuY1 + RANGE, apuX2, apuY2 + RANGE);
		}
		if (nChar == KEY_LEFT) {
			curKeyState = 3;
			exist = TheGhostNearbyApu(apuX1 - RANGE, apuY1, apuX2 - RANGE, apuY2);
		}
		if (nChar == KEY_RIGHT) {
			curKeyState = 4;
			exist = TheGhostNearbyApu(apuX1 + RANGE, apuY1, apuX2 + RANGE, apuY2);
		}

		if (exist != -1) {
			apu->SetMoving(curKeyState + 4);
			CAudio::Instance()->Play(AUDIO_FIGHT);
			ghost[exist]->SetFighted(true);
		}
		else {
			apu->SetMoving(curKeyState);
		}
	}
	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
		const char KEY_LEFT = 0x25;
		const char KEY_UP = 0x26;
		const char KEY_RIGHT = 0x27;
		const char KEY_DOWN = 0x28;
	}
	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) {
		int x1 = point.x, y1 = point.y;
		int x2, y2, x3, y3;
		x2 = button_menu.Left();
		y2 = button_menu.Top();
		x3 = x2 + button_menu.Width();
		y3 = y2 + button_menu.Height();
		if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
			isMenuButtonDown = true;

		}
	}
	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) {}
	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) {}
	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) {}
	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) {}

	int CGameStateRun::TheGhostNearbyApu(int x1, int y1, int x2, int y2) {
		for (unsigned int i = 0; i < ghost.size(); i++) {
			if (ghost[i]->GetX1() == x1 && ghost[i]->GetY1() == y1) {
				//if (x2 >= ghost[i]->GetX1() && x1 <= (ghost[i]->GetX1()+64) && y2 >= ghost[i]->GetY1()  && y1 <= (ghost[i]->GetY1()+64)) {
				if (ghost[i]->IsAlive()) return i;
				else break;
			}
		}
		return -1;
	}
	void CGameStateRun::AddGhost(int type, int x, int y) {
		switch (type) {
		case 1:
			ghost.push_back(new CBallon(x, y));
			break;
		case 2:
			ghost.push_back(new CBat(x, y));
			break;
		case 3:
			ghost.push_back(new CPumpkin(x, y));
			break;
		default:
			break;
		}
	}

	void CGameStateRun::OnMove() {
		if (isMenuButtonDown) {
			if (button_menu.GetCurrentBitmapNumber() == button_menu.GetLastBitmapNumber()) {
				button_menu.Reset();
				Sleep(250);
				isMenuButtonDown = false;
				GotoGameState(GAME_STATE_INIT);
				return;
			}
			CAudio::Instance()->Play(AUDIO_BUTTON);
			button_menu.OnMove();
		}
		apu->OnMove(gamemap);
		for (unsigned int i = 0; i < ghost.size(); i++)
			ghost[i]->OnMove(gamemap, apu);

		if (apu->IsSucceed()) {
			CGame::Instance()->SetFinish(curLevel);
			CGame::Instance()->SetApuXY(gamemap->ScreenXY(apu->GetXY()));
			apu->OnMove(gamemap);
			overCounter--;
			if (overCounter < 0)
				GotoGameState(GAME_STATE_OVER);
		}
		else if (apu->IsFail()) {
			CGame::Instance()->SetDead(curLevel);
			CGame::Instance()->SetApuXY(gamemap->ScreenXY(apu->GetXY()));
			apu->OnMove(gamemap);
			overCounter--;
			if (overCounter < 0)
				GotoGameState(GAME_STATE_OVER);
		}
	}
	void CGameStateRun::OnShow() {
		gamemap->OnShow();
		for (unsigned int i = 0; i < ghost.size(); i++)
			ghost[i]->OnShow(gamemap);
		apu->OnShow(gamemap);
		button_menu.SetTopLeft(10, 10);
		button_menu.OnShow();

	}

}


