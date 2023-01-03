// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

#include "Types.h"

// Framework
#include "Framework/Math/Vector2.h"
#include "Framework/Math/DisJointSet.h"

#include "Framework/Collider/Line.h"
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/CircleCollider.h"
#include "Framework/Collider/RectCollider.h"

// Obj
#include "Object/Cannon/Ball.h"
#include "Object/Cannon/Barrel.h"
#include "Object/Cannon/Cannon.h"

// Arkanoid
#include "Object/Arkanoid/ArkBlock.h"
#include "Object/Arkanoid/ArkBall.h"
#include "Object/Arkanoid/Bar.h"
#include "Object/Arkanoid/ArkItem.h"
#include "Object/Arkanoid/Arkanoid.h"

// Maze
#include "Object/Maze/Block.h"
#include "Object/Maze/Maze.h"
#include "Object/Maze/Player.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/Program.h"

extern Vector2 mousePos;
extern HWND hWnd;