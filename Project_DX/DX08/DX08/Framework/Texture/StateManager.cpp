#include "framework.h"
#include "StateManager.h"

StateManager* StateManager::_instance = nullptr;
StateManager::StateManager()
{
	_sampler = make_shared<SamplerState>();

	_alphaState = make_shared<BlendState>();
	_alphaState->Alpha();

	_additiveState = make_shared<BlendState>();
	_additiveState->Additive();

	_blendState = make_shared<BlendState>();
}

StateManager::~StateManager()
{
}
