#pragma once
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360

#define PI 3.141592

#define DEVICE Device::GetInstance()->GetDevice()
#define DC Device::GetInstance()->GetDeviceContext()

#define SAMPLER StateManager::GetInstance()->GetSampler()
#define ALPHA StateManager::GetInstance()->GetAlpha()
#define ADDITIVE StateManager::GetInstance()->GetAdditive()

#define MOUSE_POS InputManager::GetInstance()->GetMousePos()
#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)
#define KEY_UP(k) InputManager::GetInstance()->Up(k)