#include "framework.h"
#include "Audio.h"

Audio* Audio::_instance = nullptr;
Audio::Audio()
{
	FMOD::System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
}

Audio::~Audio()
{
	for (auto pair : _soundMap)
	{
		pair.second->_sound->release();
	}
	_soundSystem->release();
}

void Audio::Update()
{
	_soundSystem->update();
}

void Audio::Add(string key, string file, bool bgm)
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

void Audio::Play(string key, float volume)
{
	if (_soundMap.count(key) == 0)
		return;
	if (_soundMap[key]->_channel == nullptr)
		return;

	_soundSystem->playSound(_soundMap[key]->_sound, nullptr, false, &_soundMap[key]->_channel);
	_soundMap[key]->_channel->setVolume(volume);
}

void Audio::Stop(string key)
{
	if (_soundMap.count(key) == 0)
		return;
	if (_soundMap[key]->_channel == nullptr)
		return;

	_soundMap[key]->_channel->stop();
}

void Audio::Pause(string key)
{
	if (_soundMap.count(key) == 0)
		return;
	if (_soundMap[key]->_channel == nullptr)
		return;

	_soundMap[key]->_channel->setPaused(true);
}

void Audio::Resume(string key)
{
	if (_soundMap.count(key) == 0)
		return;
	if (_soundMap[key]->_channel == nullptr)
		return;

	_soundMap[key]->_channel->setPaused(false);
}

void Audio::SetVolume(string key, float volume)
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

bool Audio::IsPlaySound(string key)
{
	if (_soundMap.count(key) == 0)
		return false;
	if (_soundMap[key]->_channel == nullptr)
		return false;

	bool isPlay = false;
	_soundMap[key]->_channel->isPlaying(IN & isPlay);

	return isPlay;
}
