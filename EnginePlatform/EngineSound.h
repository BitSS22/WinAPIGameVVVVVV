#pragma once
#include <EngineBase/EngineResources.h>
#include <map>

#include "ThirdParty/FMOD/inc/fmod.hpp"

class USoundPlayer
{
public:
	friend class UEngineSound;
public:
	USoundPlayer() = default;
	~USoundPlayer() = default;

private:
	FMOD::Channel* Control = nullptr;

public:
	void SetPlay(bool _Value)
	{
		Control->setPaused(_Value);
	}
	void SwitchPlay()
	{
		bool Check = false;
		Control->getPaused(&Check);
		Control->setPaused(!Check);
	}
	void Loop(int _Count = -1)
	{
		Control->setLoopCount(_Count);
	}

};

class UEngineSound : public UEngineResources
{
public:
	UEngineSound();
	~UEngineSound();

	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

private:
	static std::map<std::string, UEngineSound*> Sounds;
	FMOD::Sound* SoundHandle = nullptr;

public:
	static void Load(std::string_view _Path);
	static void Load(std::string_view _Name, std::string_view _Path);
	static void Update();
	static void Release();

	static USoundPlayer Play(std::string_view _Name);
	static UEngineSound* Find(std::string_view _Name);

private:
	bool ResLoad(std::string_view _Path);

};

