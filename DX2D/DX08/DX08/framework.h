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
#include <memory>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <string>
#include <functional>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// DirectXTex
#include "../DirectXTex/DirectXTex.h"

// ImGui
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_dx11.h"
#include "../ImGUI/imgui_impl_win32.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;

#include "Types.h"

// Framework
#include "Framework/Device/Device.h"

// Math
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

// Render
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/VertexLayout.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"

// Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/RectCollider.h"
#include "Framework/Collider/CircleCollider.h"

// Utility
#include "Framework/Utility/InputManager.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/tinyxml2.h"

// Texture
#include "Framework/Texture/SRV.h"
#include "Framework/Texture/SRVManager.h"
#include "Framework/Texture/SamplerState.h"
#include "Framework/Texture/BlendState.h"
#include "Framework/Texture/StateManager.h"

// Animation
#include "Framework/Animation/Action.h"

// Object
#include "Object/BasicObj/Quad.h"
#include "Object/BasicObj/Sprite.h"

// Bow
#include "Object/GameObj/Bow/Bow_Monster.h"
#include "Object/GameObj/Bow/Bow_Arrow.h"
#include "Object/GameObj/Bow/Bow.h"

// Zelda
#include "Object/GameObj/Zelda/Zelda.h"

// CupHead
#include "Object/GameObj/CupHead/Cup_Bg.h"
#include "Object/GameObj/CupHead/Cup_Player.h"
#include "Object/GameObj/CupHead/Cup_Bullet.h"

// SolarSystem
#include "Object/GameObj/SolarSystem/Planet.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/Program.h"
