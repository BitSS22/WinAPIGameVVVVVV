#pragma once

#include <EngineBase/EngineMath.h>
#include <EngineCore/ImageManager.h>

class ULevel;
class UEngineSprite;

class AActor : public UObject
{
public:
	using Super = AActor;
	friend class ULevel;
public:
	AActor();
	~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

private:
	ULevel* World = nullptr;
	UEngineSprite* Sprite = nullptr;
	FTransform Transfrom = {};
	int CurIndex = 0;

public:
	virtual void BeginPlay()
	{}
	virtual void Tick()
	{}
	virtual void Render() const;

private:

public:
	ULevel* GetWorld() const
	{
		return World;
	}
	FVector2D GetActorLocation() const
	{
		return Transfrom.Location;
	}
	void SetActorLocation(FVector2D _Location)
	{
		Transfrom.Location = _Location;
	}
	void AddActorLocation(FVector2D _Location)
	{
		Transfrom.Location += _Location;
	}
	void SetActorScale(FVector2D _Scale)
	{
		Transfrom.Scale = _Scale;
	}
	void SetSprite(string_view _Name, int _CurIndex = 0)
	{
		Sprite = UImageManager::GetInst().FindSprite(_Name);

		if (Sprite == nullptr)
			MSGASSERT(nullptr, _Name, "는 로드 되지 않은 스프라이트입니다");

		CurIndex = _CurIndex;
	}

};

