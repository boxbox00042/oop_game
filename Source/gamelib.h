/////////////////////////////////////////////////////////////////////////////
// 定義遊戲可設定的環境與條件
/////////////////////////////////////////////////////////////////////////////

#define SIZE_X				 640		// 設定遊戲畫面的解析度為676*364, 640*480
#define SIZE_Y				 480		// 註：若不使用標準的解析度，則不能切換到全螢幕
#define OPEN_AS_FULLSCREEN	 false		// 是否以全螢幕方式開啟遊戲
#define SHOW_LOAD_PROGRESS   true		// 是否顯示loading(OnInit)的進度
#define DEFAULT_BG_COLOR	 RGB(0,0,0)	// 遊戲畫面預設的背景顏色(黑色)
#define GAME_CYCLE_TIME		 33		    // 每33ms跑一次Move及Show(每秒30次)
#define SHOW_GAME_CYCLE_TIME false		// 是否在debug mode顯示cycle time
#define ENABLE_GAME_PAUSE	 true		// 是否允許以 Ctrl-Q 暫停遊戲
#define ENABLE_AUDIO		 true		// 啟動音效介面

/////////////////////////////////////////////////////////////////////////////
// 定義CGame及CGameState所使用的三個狀態常數
/////////////////////////////////////////////////////////////////////////////

enum GAME_STATES {
	GAME_STATE_INIT,
	GAME_STATE_RUN,
	GAME_STATE_OVER
};

/////////////////////////////////////////////////////////////////////////////
// Header for STL (Standard Template Library)
/////////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <map>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// 回報程式錯誤用的macro
// 備註：這裡使用macro以便保留檔案名稱及行號，利於debug。
/////////////////////////////////////////////////////////////////////////////

#define GAME_ASSERT(boolexp,str)											\
		if (!(boolexp)) {													\
			int id;															\
			char s[300]="";													\
			sprintf(s,"Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"		\
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);									\
			id = AfxMessageBox(s, MB_RETRYCANCEL);							\
			if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();												\
		}

namespace game_framework {

/////////////////////////////////////////////////////////////////////////////
// 這個class提供時間、錯誤等控制
// 一般的遊戲並不需直接操作這個物件，因此可以不管這個class的使用方法
/////////////////////////////////////////////////////////////////////////////

class CSpecialEffect {
public:
	static void  SetCurrentTime();					// 儲存目前的時間至ctime
	static DWORD GetEllipseTime();					// 讀取目前的時間 - ctime
	static int   GetCurrentTimeCount();				// 讀取儲存ctime的次數
	static void  Delay(DWORD ms);					// 延遲 x ms
	static void  DelayFromSetCurrentTime(DWORD ms);	// 自ctime起算，延遲 x ms
private:
	static DWORD ctime;
	static int	 ctimeCount;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class會建立DirectDraw物件，以提供其他class使用
// 一般的遊戲並不需直接操作這個物件，因此可以不管這個class的使用方法
/////////////////////////////////////////////////////////////////////////////

class CDDraw {
	friend class CMovingBitmap;
public:
	~CDDraw();
	static void  BltBackColor(DWORD);		// 將Back plain全部著上指定的顏色
	static void  BltBackToPrimary();		// 將Back plain貼至Primary plain
	static CDC*  GetBackCDC();				// 取得Back Plain的DC (device context)
	static void  GetClientRect(CRect &r);	// 取得設定的解析度
	static void  Init(int, int);			// Initialize direct draw
	static void  ReleaseBackCDC();			// 放掉Back Plain的DC (device context)
	static bool  SetFullScreen(bool);		// 設定為全螢幕模式/視窗模式
	static bool  IsFullScreen();			// 回答是否為全螢幕模式/視窗模式
private:
	CDDraw();								// private constructor
	static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
	static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
	static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
	static void	 CheckDDFail(char *s);
	static bool  CreateSurface();
	static bool  CreateSurfaceFullScreen();
	static bool  CreateSurfaceWindowed();
	static void  LoadBitmap(int i, int IDB_BITMAP);
	static void  LoadBitmap(int i, char *filename);
	static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
	static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
	static int   RegisterBitmap(char *filename, COLORREF ColorKey);
	static void  ReleaseSurface();
	static void  RestoreSurface();
	static void  SetColorKey(unsigned SurfaceID, COLORREF color);
    static HDC					hdc;
	static CDC					cdc;
	static CView				*pCView;
    static LPDIRECTDRAW2		lpDD;
	static LPDIRECTDRAWCLIPPER	lpClipperPrimary;   
	static LPDIRECTDRAWCLIPPER	lpClipperBack;   
	static LPDIRECTDRAWSURFACE	lpDDSPrimary;
	static LPDIRECTDRAWSURFACE	lpDDSBack;
	static vector<LPDIRECTDRAWSURFACE>	lpDDS;
    static HRESULT				ddrval;
	static vector<int>			BitmapID;
	static vector<string>		BitmapName;
	static vector<CRect>		BitmapRect;
	static vector<COLORREF>		BitmapColorKey;
	static bool					fullscreen;
	static CDDraw				ddraw;
	static int					size_x, size_y;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class提供動態(可以移動)的圖形
// 每個Public Interface的用法都要懂，Implementation可以不懂
/////////////////////////////////////////////////////////////////////////////

class CMovingBitmap {
public:
	CMovingBitmap();
	int   Height();						// 取得圖形的高度
	int   Left();						// 取得圖形的左上角的 x 座標
	void  LoadBitmap(int,COLORREF=CLR_INVALID);		// 載入圖，指定圖的編號(resource)及透明色
	void  LoadBitmap(char *,COLORREF=CLR_INVALID);	// 載入圖，指定圖的檔名及透明色
	void  SetTopLeft(int,int);			// 將圖的左上角座標移至 (x,y)
	void  ShowBitmap();					// 將圖貼到螢幕
	void  ShowBitmap(double factor);	// 將圖貼到螢幕 factor < 1時縮小，>1時放大。注意：需要VGA卡硬體的支援，否則會很慢
	void  ShowBitmap(CMovingBitmap &);	// 將圖貼到到另一張圖上 (僅供特殊用途)
	int   Top();						// 取得圖形的左上角的 y 座標
	int   Width();						// 取得圖形的寬度
protected:
	CRect    location;			// location of the bitmap
	bool     isBitmapLoaded;	// whether a bitmap has been loaded
	unsigned SurfaceID;			// the surface id of this bitmap
};

/////////////////////////////////////////////////////////////////////////////
// 這個class提供可以移動的動畫
// 每個Public Interface的用法都要懂，Implementation可以不懂
/////////////////////////////////////////////////////////////////////////////

class CAnimation {
public:
	CAnimation(int=10);				// Constructor (預設動畫播放頻率每1/3秒換一張圖)
	void  AddBitmap(int,COLORREF=CLR_INVALID);
									// 增加一張圖形至動畫(圖的編號及透明色)
	void  AddBitmap(char *,COLORREF=CLR_INVALID);
									// 增加一張圖形至動畫(圖的編號及透明色)
	int   GetCurrentBitmapNumber();	// 取得正在撥放的bitmap是第幾個bitmap
	int   GetLastBitmapNumber();
	bool  IsFinalBitmap();			// 回傳正在撥放的bitmap是否為最後一個bitmap
	void  OnMove();					// 依頻率更換bitmap
	void  OnShow();					// 將動畫貼到螢幕
	void  Reset();					// 重設播放順序回到第一張圖形
	void  SetDelayCount(int);		// 設定動畫播放速度的常數(越大越慢)
	void  SetTopLeft(int,int);		// 將動畫的左上角座標移至 (x,y)
	int   Left();					// 取得動畫的左上角的 x 座標
	int   Top();					// 取得動畫的左上角的 y 座標
	int   Height();					// 取得動畫的高度
	int   Width();					// 取得動畫的寬度
private:
	list<CMovingBitmap>				bmp;			// list of CMovingBitmap
	list<CMovingBitmap>::iterator	bmp_iter;		// list iterator
	int								bmp_counter;	// 儲存bmp_iter為第n個bmp
	int								delay_counter;	// 延緩動畫播放速度的計數器
	int								delay_count;	// 動畫播放速度的常數
	int								x, y;			// 動畫的座標
};

/////////////////////////////////////////////////////////////////////////////
// 這個class提供顯示整數圖形的能力
// 每個Public Interface的用法都要懂，Implementation可以不懂
/////////////////////////////////////////////////////////////////////////////

class CInteger {
public:
	CInteger(int=5);			// default 5 digits
	void Add(int n);			// 增加整數值
	int  GetInteger();			// 回傳整數值
	void LoadBitmap();			// 載入0..9及負號之圖形
	void SetInteger(int);		// 設定整數值
	void SetTopLeft(int,int);	// 將動畫的左上角座標移至 (x,y)
	void ShowBitmap();			// 將動畫貼到螢幕
private:
	const int NUMDIGITS;			// 共顯示NUMDIGITS個位數
	static CMovingBitmap digit[11]; // 儲存0..9及負號之圖形(bitmap)
	int x, y;						// 顯示的座標
	int n;							// 整數值
	bool isBmpLoaded;				// 是否已經載入圖形
};

/////////////////////////////////////////////////////////////////////////////
// 宣告尚未定義的class
/////////////////////////////////////////////////////////////////////////////

class CGame;
class CGameStateInit;
class CGameStateRun;
class CGameStateOver;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的各種狀態之Base class(是一個abstract class)
// 每個Public Interface的用法都要懂，Implementation可以不懂
/////////////////////////////////////////////////////////////////////////////

class CGameState {
public:
	CGameState(CGame *g);
	void OnDraw();			// Template Method
	void OnCycle();			// Template Method
	//
	// virtual functions, 由繼承者提供implementation
	//
	virtual ~CGameState() {}								// virtual destructor
	virtual void OnBeginState() {}							// 設定每次進入這個狀態時所需的初值
	virtual void OnInit() {}								// 狀態的初值及圖形設定
	virtual void OnKeyDown(UINT, UINT, UINT) {}				// 處理鍵盤Down的動作
	virtual void OnKeyUp(UINT, UINT, UINT) {}				// 處理鍵盤Up的動作
	virtual void OnLButtonDown(UINT nFlags, CPoint point) {}// 處理滑鼠的動作
	virtual void OnLButtonUp(UINT nFlags, CPoint point) {}	// 處理滑鼠的動作
	virtual void OnMouseMove(UINT nFlags, CPoint point) {}  // 處理滑鼠的動作 
	virtual void OnRButtonDown(UINT nFlags, CPoint point) {}// 處理滑鼠的動作
	virtual void OnRButtonUp(UINT nFlags, CPoint point) {}	// 處理滑鼠的動作
protected:
	void GotoGameState(int state);							// 跳躍至指定的state
	void ShowInitProgress(int percent);						// 顯示初始化的進度
	//
	// virtual functions, 由繼承者提供implementation
	//
	virtual void OnMove() {}								// 移動這個狀態的遊戲元素
	virtual void OnShow() = 0;								// 顯示這個狀態的遊戲畫面
	CGame *game;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class是遊戲的核心，控制遊戲的進行
// 一般的遊戲並不需直接操作這個物件，因此可以不管這個class的使用方法
/////////////////////////////////////////////////////////////////////////////

class CGame {
public:
	CGame();										// Constructor
	~CGame();										// Destructor
	bool IsRunning();								// 讀取遊戲是否正在進行中
	void OnDraw();									// 對應CGameView的OnDraw()
	void OnFilePause();								// 遊戲暫停
	void OnInit();									// 遊戲繪圖及音效的初始化
	void OnInitStates();							// 遊戲各狀態的初值及圖形設定
	bool OnIdle();									// 遊戲的主迴圈
	void OnKeyDown(UINT, UINT, UINT);				// 處理鍵盤Down的動作
	void OnKeyUp(UINT, UINT, UINT);					// 處理鍵盤Up的動作
	void OnKillFocus();								// 遊戲被迫暫停
	void OnLButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnMouseMove(UINT nFlags, CPoint point);    // 處理滑鼠的動作 
	void OnRButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnResume();								// 處理自「待命」還原的動作
	void OnSetFocus();								// 處理Focus
	void OnSuspend();								// 處理「待命」的動作
	void SetGameState(int);
	void SetLevel(int);
	void SetDead(int);
	void SetFinish(int);
	void SetApuXY(POINT);
	int  GetLevel();
	bool GetDead(int);
	bool GetFinish(int);
	POINT GetApuXY();

	static CGame *Instance();
private:
	bool			running;			// 遊戲是否正在進行中(未被Pause)
	bool            suspended;			// 遊戲是否被suspended
	const int		NUM_GAME_STATES;	// 遊戲的狀態數(3個狀態)
	int				level;
	bool			dead[3];
	bool			finish[3];
	POINT			apu_xy;
	CGameState		*gameState;			// pointer指向目前的遊戲狀態
	CGameState		*gameStateTable[3];	// 遊戲狀態物件的pointer
	static CGame	instance;			// 遊戲唯一的instance
};

}