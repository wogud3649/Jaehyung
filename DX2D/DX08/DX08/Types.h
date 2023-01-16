#pragma once
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360

#define DEVICE Device::GetInstance()->GetDevice()
#define DC Device::GetInstance()->GetDeviceContext()

#define SAMPLER StateManager::GetInstance()->GetSampler()
#define ALPHA StateManager::GetInstance()->GetAlpha()
#define ADDITIVE StateManager::GetInstance()->GetAdditive()