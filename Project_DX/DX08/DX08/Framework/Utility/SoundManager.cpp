#include "framework.h"
#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;
SoundManager::SoundManager()
{
	FMOD::System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
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

void SoundManager::Play(string key, float volume)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundSystem->playSound(_soundMap[key]->_sound, nullptr, false, &_soundMap[key]->_channel);
	_soundMap[key]->_channel->setVolume(volume);
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
