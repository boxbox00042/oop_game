#ifndef CAPU_H
#define CAPU_H
#include "CGameMap.h"
namespace game_framework {

	class CApu
	{
	public:
		CApu();
		CApu(int x, int y);
		~CApu();
		int	  GetInitX1();
		int	  GetInitY1();
		int	  GetX1();					// 阿噗左上角 x 座標
		int   GetY1();					// 阿噗左上角 y 座標
		int   GetX2();					// 阿噗右下角 x 座標
		int   GetY2();					// 阿噗右下角 y 座標
		POINT GetXY();
		int   GetMode();
		int   GetState();
		bool  GetMoved();
		int   GetCurAnimationNum();
		int   GetCurAnimationLastNum();
		void  ResetCurAnimation();

		void  SetXY(int nx, int ny);		// 設定阿噗左上角座標
		void  SetXY(int stepSize);
		//void SetInitTopLeft();

		void  SetMoving(int flag);
		void  SetMoved(bool flag);
		void  SetMode(int flag);
		void  SetState(int flag);

		bool  IsSucceed();
		bool  IsFail();

		void  Initialize(int x, int y);
		void  LoadBitmap();
		void  OnMove(CGameMap *map);
		void  OnShow(CGameMap *map);

	protected:
		CAnimation moveUp;
		CAnimation moveDown;
		CAnimation moveLeft;
		CAnimation moveRight;
		CAnimation fightUp;
		CAnimation fightDown;
		CAnimation fightLeft;
		CAnimation fightRight;
		CAnimation fail;
		CAnimation success;
		CMovingBitmap initApu;
		CMovingBitmap initUp;
		CMovingBitmap initDown;
		CMovingBitmap initLeft;
		CMovingBitmap initRight;
		POINT pos;
		POINT pos_init;
		POINT pos_show;
		int curState;				// 阿噗現在的方向:1(上)2(下)3(左)4(右)5(打上)6(打下)7(打左)8(打右)
		int curMode;				// 阿噗現在的狀態:1(靜止), 2(移動)
		bool isMoved;
		bool isSpace;
	};
}

#endif