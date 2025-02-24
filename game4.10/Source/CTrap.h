#ifndef CTRAP_H
#define CTRAP_H

namespace game_framework {

	enum class CTraps {
		CClaw,
		CSpike,
		CBouncingBrick,
	};

	class CTrap {
	public:
		CTrap(int x, int y);
		~CTrap();

		int GetX1();
		int GetY1();
		int  GetCurAnimationNum();
		int  GetCurAnimationLastNum();
		void ResetCurAnimation();

		void SetXY(int nx, int ny);
		void SetMode(int mode);
		void SetState(int state);

		virtual void SwitchState() = 0;

		virtual void Initialize(int x, int y) = 0;
		virtual void LoadBitmap() = 0;
		virtual void OnMove(CGameMap *map, CApu *apu) = 0;
		virtual void OnShow(CGameMap *map) = 0;
	protected:
		CAnimation trap_up;
		CAnimation trap_down;
		POINT pos;
		POINT pos_show;
		bool switchState;
		int curMode;  // 1 : still, 2 move
		int curState; // 1 : up, 2 : down
		int counter;
	};

	class CClaw : public CTrap {
	public:
		CClaw(int x, int y);
		~CClaw();

		void SwitchState() override;
		void Initialize(int x, int y) override;
		void LoadBitmap() override;
		void OnMove(CGameMap *map, CApu *apu) override;
		void OnShow(CGameMap *map) override;
	};
	class CSpike : public CTrap {
	public:
		CSpike(int x, int y);
		~CSpike();

		void SwitchState() override;
		void Initialize(int x, int y) override;
		void LoadBitmap() override;
		void OnMove(CGameMap *map, CApu *apu) override;
		void OnShow(CGameMap *map) override;
	};
	class CBouncingBrick : public CTrap {
	public:
		CBouncingBrick(int x, int y);
		~CBouncingBrick();

		void SwitchState() override;
		void Initialize(int x, int y) override;
		void LoadBitmap() override;
		void OnMove(CGameMap *map, CApu *apu) override;
		void OnShow(CGameMap *map) override;
	};
}
#endif