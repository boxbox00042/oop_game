#ifndef CLEVEL_H
#define CLEVEL_H
#include "CApu.h"
#include "CGhost.h"
#include "CItem.h"
#include "CGameMap.h"

namespace game_framework {
	enum class LEVELS {
		LEVEL_1,
		LEVEL_2,
		LEVEL_3
	};

	class CLevel
	{
	public:
		/* Constructor */
		CLevel();
		CLevel(int);
		~CLevel();

		/* Getter */

		/* Setter */
		void SetMoving(POINT);

		/* Member Function */
		void clean();

		//
		void OnInit(int);
		void OnMove();
		void OnShow();
	protected:
	private:
		int level;
		POINT delta;
		CApu apu;
		CGameMap map;
		vector<CGhost*> balloon;
		vector<CItem*> grass;
		vector<CItem*> trees;
		CMovingBitmap piece;

	};
}
#endif
