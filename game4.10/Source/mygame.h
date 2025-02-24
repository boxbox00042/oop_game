#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "CApu.h"
#include "CGhost.h"
#include "CTrap.h"
#include "CGameMap.h"

namespace game_framework {

	enum AUDIO_ID {				// 定義各種音效的編號
		//AUDIO_DING,				// 0
		//AUDIO_LAKE,				// 1
		//AUDIO_NTUT,				// 2
		AUDIO_BGM,				// 0
		AUDIO_WIN,				// 1
		AUDIO_LOSE,				// 2
		AUDIO_FIGHT,			// 3
		AUDIO_BUTTON			// 4
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);
	
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();
		bool isBeginButtonDown;
		bool isHomeButtonDown;
		bool isAboutusButtonDown;
		bool isExplainButtonDown;
		bool isBackButtonDown;
		bool isLevelButtonDown[3];
	private:
		CAnimation page_begin;
		CMovingBitmap page_aboutus;
		CMovingBitmap page_explain;
		CMovingBitmap page_level;
		CAnimation button_begin;
		CMovingBitmap button_aboutus;
		CMovingBitmap button_explain;
		CMovingBitmap button_back;
		CAnimation button_home;
		CMovingBitmap levels[3];
		int curPage;									// 1(begin) 2(level)
		int curLevel;
	};	

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		
		int  TheGhostNearbyApu(int x1, int y1, int x2, int y2);
		void AddGhost(int type, int x, int y);
		bool isMenuButtonDown;
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	
	private:
		int				GHOSTNUM;
		CAnimation		button_menu;
		CGameMap		*gamemap;
		vector<CGhost*> ghost;
		CApu            *apu;		// 阿噗

		int				overCounter;	// 倒數計時數
		int				curKeyState;
		int				curLevel;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CAnimation apu_relive;
		int  apu_curMode;
		int  counter;	// 倒數之計數器
		int  curLevel;
		int  curState;
	};

}