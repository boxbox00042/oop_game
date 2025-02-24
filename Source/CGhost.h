#ifndef CGHOST_H
#define CGHOST_H

namespace game_framework {

	enum class CGhosts {
		CBallon,
		CBat,
		CPumpkin,
	};

	class CGhost
	{
	public:
		CGhost(int x, int y);
		~CGhost();

		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		int  GetCurAnimationNum();
		int  GetCurAnimationLastNum();
		void ResetCurAnimation();

		void SetXY(int nx, int ny);	
		void SetMoving();
		void SetAlive(bool alive);
		void SetFighted(bool fighted);
		void SetMode(int mode);
		void SetState(int state);
		void SetFork();

		bool IsAlive();
		bool IsFighted();
		bool HitApu(CApu *apu);

		/* Apu Function */
		void SwitchState(CGameMap *map, CApu *apu);
		int  WhereIsApu(CApu *apu);
		void FollowApu(CGameMap *map, CApu *apu);

		void Initialize(int x, int y);
		virtual void LoadBitmap() = 0;
		void OnMove(CGameMap *map, CApu *apu);
		void OnShow(CGameMap *map);

	protected:
		CAnimation ghost_up;
		CAnimation ghost_down;
		CAnimation ghost_die;
		CMovingBitmap fork1;
		CMovingBitmap fork2;
		CMovingBitmap fork3;
		CMovingBitmap fork4;
		POINT pos;
		POINT pos_show;
		bool isAlive;
		bool isFighted;
		bool isMoving;
		bool switchState;
		bool followApu;
		int  curMode;								// 鬼怪現在的狀態:1(靜止), 2(移動)
		int  curState;								// 鬼怪現在的模樣:1(不動), 2(攻擊), 3(死亡)
		int  curDirect;
		int  dieCounter;
	};

	class CBallon : public CGhost {
	public:
		CBallon(int x, int y);
		~CBallon();
		void LoadBitmap() override;		
	};

	class CBat : public CGhost {
	public:
		CBat(int x, int y);
		~CBat();
		void LoadBitmap() override;
	};

	class CPumpkin : public CGhost {
	public:
		CPumpkin(int x, int y);
		~CPumpkin();
		CAnimation ghost_left;
		CAnimation ghost_right;
		void LoadBitmap() override;
	};
}


#endif
