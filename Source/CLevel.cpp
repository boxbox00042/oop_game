#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CLevel.h"

namespace game_framework {
	/* Constructor */
	CLevel::CLevel() {
		level = 0;
		delta = POINT();
	}

	CLevel::CLevel(int l) {
		level = l;
		delta = POINT();
	}

	CLevel::~CLevel() {
		clean();
	}

	/* Getter */

	/* Setter */
	void CLevel::SetMoving(POINT delta) {
		/*for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				;
			}
		}

		int is = items.size();
		for (int i = 0; i < is; i++)
			items.at(i)->SetMoving(delta);
		int gs;*/

	}
	/* Member Function */
	void CLevel::clean() {

	}
	//
	void CLevel::OnInit(int l) {
		level = l;

		clean();

		switch (level) {
			// Level 1
			case static_cast<int>(LEVELS::LEVEL_1) :
				// Backgrount
				// Item
				// Ghost
				break;
				case static_cast<int>(LEVELS::LEVEL_2) :
					// Background
					// Item
					// Ghost
					break;
					case static_cast<int>(LEVELS::LEVEL_3) :
						// Background
						// Item
						// Ghost
						break;
		}
	}

	void CLevel::OnMove() {

	}
	void CLevel::OnShow() {

	}
}