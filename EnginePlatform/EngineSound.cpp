#include "pch.h"
#include "EngineSound.h"
#include "EngineBase/EngineString.h"

std::map<std::string, UEngineSound*> UEngineSound::Sounds = {};

FMOD::System* SoundSystem = nullptr;

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif // _DEBUG

class SoundInit
{
public:
	SoundInit()
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
			MSGASSERT(nullptr, "FMOD Init Fail.");

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
			MSGASSERT(nullptr, "FMOD Init Fail.");
	}
};

SoundInit SountIninObject = {};

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
	if (SoundHandle != nullptr)
	{
		SoundHandle->release();
		SoundHandle = nullptr;
	}
}

void UEngineSound::Load(std::string_view _Path)
{
	UEnginePath EnginePath = _Path;
	string FileName = EnginePath.GetFileName();

	UEngineSound::Load(FileName.data(), _Path);
}

void UEngineSound::Load(std::string_view _Name, std::string_view _Path)
{
	string UpperName = UEngineString::ToUpper(_Name);

	UEngineSound* NewSound = new UEngineSound();

	if (NewSound->ResLoad(_Path) == false)
	{
		delete NewSound;
		MSGASSERT(nullptr, _Name, "Sound Load Fail.");
	}

	Sounds.insert(make_pair(UpperName, NewSound));
}

void UEngineSound::Update()
{
	if (SoundSystem == nullptr)
		return;

	if (SoundSystem->update() != FMOD_RESULT::FMOD_OK)
		MSGASSERT(nullptr, "FMODE SYSTEM ERROR.");
}

void UEngineSound::Release()
{
	for (auto& Sound : Sounds)
	{
		if (Sound.second != nullptr)
		{
			delete Sound.second;
			Sound.second = nullptr;
		}
	}
	
	Sounds.clear();

	if (SoundSystem != nullptr)
	{
		SoundSystem->release();
		SoundSystem = nullptr;
	}
}

USoundPlayer UEngineSound::Play(std::string_view _Name)
{
	UEngineSound* FindSound = Find(_Name);

	if (FindSound == nullptr)
		MSGASSERT(nullptr, _Name, " is Unload.");

	FMOD::Channel* Channel = nullptr;
	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Channel);

	Channel->setLoopCount(0);
	Channel->setVolume(1.f);

	USoundPlayer NewPlayer = {};
	NewPlayer.Control = Channel;
	return NewPlayer;
}

UEngineSound* UEngineSound::Find(std::string_view _Name)
{
	string UpperName = UEngineString::ToUpper(_Name);

	if (Sounds.contains(UpperName) == false)
		return nullptr;

	return Sounds[UpperName];
}

bool UEngineSound::ResLoad(std::string_view _Path)
{
	SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (SoundHandle == nullptr)
	{
		MSGASSERT(nullptr, _Path, " Sound Load fail.");
		return false;
	}

	return true;
}
