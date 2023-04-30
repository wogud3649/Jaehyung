#include "framework.h"
#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;
SoundManager::SoundManager()
{
	FMOD::System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);

	AddSounds();
}

SoundManager::~SoundManager()
{
	for (auto pair : _soundMap)
	{
		pair.second->_sound->release();
	}

	_soundSystem->release();
}

void SoundManager::Update()
{
	_soundSystem->update();
}

void SoundManager::Add(string key, string file, bool bgm)
{
	if (_soundMap.count(key) > 0)
		return;

	shared_ptr<SoundInfo> info = make_shared<SoundInfo>();

	if (bgm)
		_soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, IN & info->_sound);
	else
		_soundSystem->createStream(file.c_str(), FMOD_DEFAULT, nullptr, IN & info->_sound);

	assert(info->_sound != nullptr);

	_soundMap[key] = info;
}

void SoundManager::Play(string key, bool bgm, float volume)
{
	if (_soundMap.count(key) == 0)
		return;

	if (bgm)
	{
		if (_curBgm == key)
			return;
		else
		{
			Stop(_curBgm);
			_curBgm = key;
		}
	}

	_soundSystem->playSound(_soundMap[key]->_sound, nullptr, false, &_soundMap[key]->_channel);
	_soundMap[key]->_channel->setVolume(volume);
}

void SoundManager::StopBgm()
{
	if (_curBgm == "")
		return;

	if (_soundMap.count(_curBgm) == 0)
		return;

	if (_soundMap[_curBgm]->_channel == nullptr)
		return;

	_soundMap[_curBgm]->_channel->stop();
	_curBgm = "";
}

void SoundManager::Stop(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]->_channel == nullptr)
		return;

	_soundMap[key]->_channel->stop();
}

void SoundManager::Pause(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]->_channel == nullptr)
		return;

	_soundMap[key]->_channel->setPaused(true);
}

void SoundManager::Resume(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]->_channel == nullptr)
		return;

	_soundMap[key]->_channel->setPaused(false);
}

void SoundManager::SetVolume(string key, float volume)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]->_channel == nullptr)
		return;

	if (volume < 0)
		volume = 0;

	if (volume > 2.0f)
		volume = 2.0f;

	_soundMap[key]->_channel->setVolume(volume);
}

bool SoundManager::IsPlaySound(string key)
{
	if (_soundMap.count(key) == 0)
		return false;

	if (_soundMap[key]->_channel == nullptr)
		return false;

	bool isPlay = false;
	_soundMap[key]->_channel->isPlaying(IN & isPlay);

	return isPlay;
}

void SoundManager::AddSounds()
{
	// BGM
	Add("Tutorial", "Resources/Sound/Tutorial.wav", true);
	Add("Chapter1", "Resources/Sound/Chapter1.wav", true);
	Add("DemonCastle", "Resources/Sound/DemonCastle.wav", true);
	Add("Chapter1_Boss", "Resources/Sound/Chapter1_Boss.wav", true);

	// SoundEffect
	// Player
	{
		// Common
		Add("Dash_Small", "Resources/Sound/Dash_Small.wav");
		Add("Default_Dash", "Resources/Sound/Default_Dash.wav");

		// Skul
		Add("Skul_Atk_1", "Resources/Sound/Skul_Atk_1.wav");
		Add("Skul_Atk_2", "Resources/Sound/Skul_Atk_2.wav");
		Add("Skul_Jump_Atk", "Resources/Sound/Skul_Jump_Atk.wav");
		Add("Skul_SkullBack", "Resources/Sound/Skul_SkullBack.wav");
		Add("Skul_SkullThrowing", "Resources/Sound/Skul_SkullThrowing.wav");

		// Wizard
		Add("Wizard_Hit", "Resources/Sound/Wizard_Hit.wav");
		Add("Wizard_Hit_Large", "Resources/Sound/Wizard_Hit_Large.wav");
		Add("Wizard_FireArrow_Ready", "Resources/Sound/Wizard_FireArow_Ready.wav");
		Add("Wizard_FireArrow_Shot", "Resources/Sound/Wizard_FireArow_Shot.wav");
		Add("Wizard_Meteor_Throw", "Resources/Sound/Wizard_Meteor_Throw.wav");
		Add("Wizard_Meteor_Falling", "Resources/Sound/Wizard_Meteor_Falling.wav");
	}

	// Monster
	{
		// Boss
		Add("ElderEnt_FistSlam", "Resources/Sound/ElderEnt_FistSlam.wav");
		Add("ElderEnt_FistSlam_Recovery", "Resources/Sound/ElderEnt_FistSlam_Recovery.wav");
		Add("ElderEnt_Groggy_Recovery", "Resources/Sound/ElderEnt_Groggy_Recovery.wav");
		Add("ElderEnt_Roar_Short", "Resources/Sound/ElderEnt_Roar_Short.wav");
		Add("ElderEnt_Sweeping", "Resources/Sound/ElderEnt_Sweeping.wav");
		Add("ElderEnt_Sweeping_Roar", "Resources/Sound/ElderEnt_Sweeping_Roar.wav");
		Add("ElderEnt_Up_1", "Resources/Sound/ElderEnt_Up_1.wav");
		Add("ElderEnt_Up_2", "Resources/Sound/ElderEnt_Up_2.wav");

		// MushroomEnt
		Add("GiantMushroomEnt_Impact", "Resources/Sound/GiantMushroomEnt_Impact.wav");
		Add("GiantMushroomEnt_Ready", "Resources/Sound/GiantMushroomEnt_Ready.wav");
		Add("GiantMushroomEnt_Sit_Impact", "Resources/Sound/GiantMushroomEnt_Sit_Impact.wav");
		Add("GiantMushroomEnt_Sit_Ready", "Resources/Sound/GiantMushroomEnt_Sit_Ready.wav");
		Add("GiantMushroomEnt_SitToStand", "Resources/Sound/GiantMushroomEnt_SitToStand.wav");
		Add("GiantMushroomEnt_StandToSit", "Resources/Sound/GiantMushroomEnt_StandToSit.wav");
		Add("GiantMushroomEnt_Voice", "Resources/Sound/GiantMushroomEnt_Voice.wav");
		Add("Trap_Jump", "Resources/Sound/Trap_Jump.wav");
	}

	// UI
	{
		Add("UI_Close", "Resources/Sound/UI_Close.wav");
		Add("UI_GetAbility", "Resources/Sound/UI_GetAbility.wav");
		Add("UI_Inventory_Close", "Resources/Sound/UI_Inventory_Close.wav");
		Add("UI_Inventory_Open", "Resources/Sound/UI_Inventory_Open.wav");
		Add("UI_MenuClose", "Resources/Sound/UI_MenuClose.wav");
		Add("UI_MenuMove", "Resources/Sound/UI_MenuMove.wav");
		Add("UI_MenuOpen", "Resources/Sound/UI_MenuOpen.wav");
		Add("UI_Move", "Resources/Sound/UI_Move.wav");
		Add("UI_Open", "Resources/Sound/UI_Open.wav");
	}

	// Object
	{
		Add("Object_DestroyItem_loop", "Resources/Sound/Object_DestroyItem_loop.wav");
		Add("Object_DestroyItem_Completed", "Resources/Sound/Object_DestroyItem_Completed.wav");
		Add("Object_GainGold", "Resources/Sound/Object_GainGold.wav");
		Add("Object_GainItem", "Resources/Sound/Object_GainItem.wav");
		Add("Object_OpenBox", "Resources/Sound/Object_OpenBox.wav");
		Add("GetHealingOrb", "Resources/Sound/GetHealingOrb.wav");
		Add("GetItem", "Resources/Sound/GetItem.wav");
	}

	// Hit
	{
		Add("Burn", "Resources/Sound/Burn.wav");
		Add("Hit_Flame_Short", "Resources/Sound/Wizard_FireArow_Ready.wav");
		Add("Hit_Flame_Small", "Resources/Sound/Hit_Flame_Small.wav");
		Add("Hit_Sword_Small", "Resources/Sound/Hit_Sword_Small.wav");
		Add("Atk_Flame_Very_Small", "Resources/Sound/Atk_Flame_Very_Small.wav");
	}

	// Atmosphere
	{
		Add("Earthquake", "Resources/Sound/Earthquake.wav");
		Add("State_Earthquake", "Resources/Sound/State_Earthquake.wav");
		Add("Wind", "Resources/Sound/Wind.wav");
		Add("Forest", "Resources/Sound/Forest.wav");
		Add("Atk_Smoke_Medium", "Resources/Sound/Atk_Smoke_Medium.wav");
		Add("Atk_Smoke_Small", "Resources/Sound/Atk_Smoke_Small.wav");
		Add("Atk_Smoke_Large", "Resources/Sound/Atk_Smoke_Large.wav");
		Add("Atk_Smoke_Long", "Resources/Sound/Atk_Smoke_Long.wav");
	}

	// FadeOut
	{
		Add("SkulTeleport", "Resources/Sound/SkulTeleport.wav");
	}

	// ETC
	Add("Atk_Stomp_Medium", "Resources/Sound/Atk_Stomp_Medium.wav");
	Add("DQG_Atk_Ready", "Resources/Sound/DQG_Atk_Ready.wav");
	Add("enm_tp", "Resources/Sound/enm_tp.wav");
	Add("EntSkul_Root_Attack", "Resources/Sound/EntSkul_Root_Attack.wav");
	Add("Fighter_Whoosh_Light2", "Resources/Sound/Fighter_Whoosh_Light2.wav");
	Add("HammerGiant_Stomp_Charge", "Resources/Sound/HammerGiant_Stomp_Charge.wav");
	Add("Skul_LandingImpact", "Resources/Sound/Skul_LandingImpact.wav");
}