#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlayMap : public AActor
{
public:
	APlayMap();
	~APlayMap();

	APlayMap(const APlayMap& _Other) = delete;
	APlayMap(APlayMap&& _Other) noexcept = delete;
	APlayMap& operator=(const APlayMap& _Other) = delete;
	APlayMap& operator=(APlayMap&& _Other) noexcept = delete;

private:
	USpriteRenderer* SpriteRenderer = nullptr;

public:

private:

};

