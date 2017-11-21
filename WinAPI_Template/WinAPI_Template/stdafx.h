// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#ifdef _DEBUG
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")
#endif // _DEBUG

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <time.h>
#include <chrono>
#include <iostream>
#include <assert.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

//==================================================================
//		## 디파인문 - 메크로 ## (윈도우창 초기화)
//==================================================================
#define W_NAME (LPCWSTR)(TEXT("THE LEGEND OF ZELDA : A LINK TO THE PAST"))
#define W_START_POS_X		0
#define W_START_POS_Y		0
#define W_WIDTH		        768
#define W_HEIGHT		    672

#define VIEWPORT_WIDTH      256
#define VIEWPORT_HEIGHT     224

#define WINDOW_STYLE		WS_CAPTION | WS_SYSMENU
#define PURE			    = 0

#define MAGENTA_COLOR       RGB(255, 0, 255)

#define RSC_LIST_KEY "rsc-list"

//#define FPS_TEST
//==================================================================
//		## MACRO FUNCTION ##
//==================================================================
#define SAFE_DELETE(p)          { if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)    { if(p) { delete[]{p); (p) = NULL; } } }


//==================================================================
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//==================================================================
#include "DataStructure.h"
#include "EnumState.h"
//==================================================================
//		## 매니져 추가 ##
//==================================================================
#include "DbManager.h"
#include "FileDataManager.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "LogManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "PixelCollision.h"


//==================================================================
//		## Helper 추가 ##
//==================================================================
#include "DrawHelper.h"
#include "GeometryHelper.h"
#include "PhysicsHelper.h"

#define RSC_LIST_PATH "data\\resource-list.json"

#define GLOBAL_WIN_SIZE     UnitSize{W_WIDTH, W_HEIGHT}
#define GLOBAL_WIN_HSIZE    UnitSize{W_WIDTH * 0.5f, W_HEIGHT * 0.5f}
#define GLOBAL_CENTER_POS   UnitPos{W_WIDTH * 0.5f, W_HEIGHT * 0.5f}

//==================================================================
//		## 전역변수 ##
//==================================================================
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;
extern HDC          g_hDC;
extern RECT         g_rtViewPort;