#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"
#include "CData.h"

using namespace std;

namespace game_framework {

	CGameMap::CGameMap() 
		:X(0), Y(0), MW(65), MH(65), sx(0), sy(130) {	
	}
	
	CGameMap::~CGameMap() {}

	POINT CGameMap::GetPieceXY() {
		POINT p = POINT();
		p.x = MW * 18;
		p.y = MH * 6;
		return p;
	}
	POINT CGameMap::GetSXY() {
		POINT p = POINT();
		p.x = sx;
		p.y = sy;
		return p;
	}

	int CGameMap::GetSX() { return sx; }
	int CGameMap::GetSY() { return sy; }
	
	int *CGameMap::GetMap() { return map[0]; }
	void CGameMap::SetSX(int x) { sx = 0 + x; }
	void CGameMap::SetSY(int y) { sy = 130 + y; }
	int CGameMap::ScreenX(int x) { return x - sx; }
	int CGameMap::ScreenY(int y) { return y - sy; }
	POINT CGameMap::ScreenXY(POINT xy) {
		POINT _xy = POINT();
		_xy.x = xy.x - sx;
		_xy.y = xy.y - sy;
		return _xy;
	}

	bool CGameMap::IsEmpty(int x, int y) {
		int gx = x / MW;
		int gy = y / MH;
		return (map[gx][gy] == 1) || (map[gx][gy] == 2);
	}

	bool CGameMap::HasPiece(int x1, int y1, int x2, int y2) {
		int x3 = GetPieceXY().x;
		int y3 = GetPieceXY().y;
		int x4 = GetPieceXY().x + piece.Width();
		int y4 = GetPieceXY().y +piece.Height();
		return (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4);
	}
	
	/* CGameMap_1 */
	CGameMap_1::CGameMap_1() : CGameMap::CGameMap() {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				map[i][j] = LEVEL1_MAP[i][j];
	}
	CGameMap_1::~CGameMap_1() {}
	void CGameMap_1::LoadBitmap() {
		brick1.LoadBitmap(IDB_BRICK1);
		brick2.LoadBitmap(IDB_BRICK3);
		piece.LoadBitmap(IDB_MAP_FINAL, WHITE);
		turf.LoadBitmap(IDB_TURF);
		brick3.LoadBitmap(IDB_BRICK2);
		brick4.LoadBitmap(IDB_BRICK4);
		explination.LoadBitmap(IDB_EXPLINATION, WHITE);
		for (int i = 0; i < Fourty; i++)
			tree[i].LoadBitmap(IDB_TREE1, WHITE);
		for (int i = 0; i < Ten; i++)
			grass[i].LoadBitmap(IDB_GRASS4, WHITE);
	}
	void CGameMap_1::OnMove(){}
	void CGameMap_1::OnShow() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int x = i * MW - sx;
				int y = j * MH - sy;

				switch (map[i][j]) {
				case 0:
					turf.SetTopLeft(x, y);
					turf.ShowBitmap();
					break;
				case 1:
					brick1.SetTopLeft(x, y);
					brick1.ShowBitmap();
					break;
				case 2:
					brick2.SetTopLeft(x, y);
					brick2.ShowBitmap();
					break;
				case 3:
					brick3.SetTopLeft(x, y);
					brick3.ShowBitmap();
					break;
				case 4:
					brick4.SetTopLeft(x, y);
					brick4.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
		for (int i = 0; i < Fourty; i++) {
			tree[i].SetTopLeft(LEVEL1_TREE[i][0] - sx, LEVEL1_TREE[i][1] - sy);
			tree[i].ShowBitmap();
		}
		for (int i = 0; i < Ten; i++) {
			grass[i].SetTopLeft(LEVEL1_GRASS[i][0] - sx, LEVEL1_GRASS[i][1] - sy);
		}
		piece.SetTopLeft(MW * 18 - sx, MH * 6 - sy);
		piece.ShowBitmap();
		explination.SetTopLeft(90 - sx, 250 - sy);
		explination.ShowBitmap();
	}

	/* CGameMap_2 */
	CGameMap_2::CGameMap_2() : CGameMap::CGameMap()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				map[i][j] = LEVEL2_MAP[i][j];
	}
	CGameMap_2::~CGameMap_2() {}
	void CGameMap_2::LoadBitmap() {
		brick1.LoadBitmap(IDB_BRICK1);
		brick2.LoadBitmap(IDB_BRICK3);
		piece.LoadBitmap(IDB_MAP_FINAL, WHITE);
		brick3.LoadBitmap(IDB_BRICK2);
		brick4.LoadBitmap(IDB_BRICK4);
		turf.LoadBitmap(IDB_TURF);
		wall.LoadBitmap(IDB_WALL1);
		for (int i = 0; i < Fourty;) {
			tree[i++].LoadBitmap(IDB_TREE1, WHITE);
			tree[i++].LoadBitmap(IDB_TREE2, WHITE);
		}
		for (int i = 0; i < Twenty; i++)
			grass[i].LoadBitmap(IDB_GRASS4, WHITE);
	}
	void CGameMap_2::OnMove() {}
	void CGameMap_2::OnShow() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int x = i * MW - sx;
				int y = j * MH - sy;

				switch (map[i][j]) {
				case 0:
					turf.SetTopLeft(x, y);
					turf.ShowBitmap();
					break;
				case 1:
					brick1.SetTopLeft(x, y);
					brick1.ShowBitmap();
					break;
				case 2:
					brick2.SetTopLeft(x, y);
					brick2.ShowBitmap();
					break;
				case 3:
					brick3.SetTopLeft(x, y);
					brick3.ShowBitmap();
					break;
				case 4:
					brick4.SetTopLeft(x, y);
					brick4.ShowBitmap();
					break;
				case 5:
					wall.SetTopLeft(x, y);
					wall.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
		for (int i = 0; i < Fourty; i++) {
			tree[i].SetTopLeft(LEVEL2_TREE[i][0] - sx, LEVEL2_TREE[i][1] - sy);
			tree[i].ShowBitmap();
		}
		piece.SetTopLeft(MW * 18 - sx, MH * 6 - sy);
		piece.ShowBitmap();
	}

	/* CGameMap_3 */
	CGameMap_3::CGameMap_3() : CGameMap::CGameMap()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				map[i][j] = LEVEL3_MAP[i][j];
	}
	CGameMap_3::~CGameMap_3() {}
	void CGameMap_3::LoadBitmap() {
		brick1.LoadBitmap(IDB_BRICK1);
		brick2.LoadBitmap(IDB_BRICK3);
		piece.LoadBitmap(IDB_MAP_FINAL, WHITE);
		brick3.LoadBitmap(IDB_BRICK5);
		brick4.LoadBitmap(IDB_BRICK6);
		floor.LoadBitmap(IDB_FLOOR);
		for (int i = 0; i < Fourty;) {
			/*tree[i++].LoadBitmap(IDB_TREE4, WHITE);
			tree[i++].LoadBitmap(IDB_TREE3, WHITE);*/
			tree[i++].LoadBitmap(IDB_TREE5, WHITE);
			tree[i++].LoadBitmap(IDB_TREE6, WHITE);
		}
		//for (int i = 0; i < 10; i++)
		//	tombs[i].LoadBitmap(IDB_GRASS4, WHITE);
	}
	void CGameMap_3::OnMove() {}
	void CGameMap_3::OnShow() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int x = i * MW - sx;
				int y = j * MH - sy;

				switch (map[i][j]) {
				case 0:
					floor.SetTopLeft(x, y);
					floor.ShowBitmap();
					break;
				case 1:
					brick1.SetTopLeft(x, y);
					brick1.ShowBitmap();
					break;
				case 2:
					brick2.SetTopLeft(x, y);
					brick2.ShowBitmap();
					break;
				case 3:
					brick3.SetTopLeft(x, y);
					brick3.ShowBitmap();
					break;
				case 4:
					brick4.SetTopLeft(x, y);
					brick4.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
		for (int i = 0; i < Fourty; i++) {
			tree[i].SetTopLeft(LEVEL3_TREE[i][0] - sx, LEVEL3_TREE[i][1] - sy);
			tree[i].ShowBitmap();
		}
		piece.SetTopLeft(MW * 18 - sx, MH * 6 - sy);
		piece.ShowBitmap();
	}

}