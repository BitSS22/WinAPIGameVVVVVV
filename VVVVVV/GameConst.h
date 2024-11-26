#pragma once
#include "EngineBase/EngineMath.h"

// Ό³Έν :
class EGameConst
{
private:
	EGameConst()
	{}
	~EGameConst()
	{}

	EGameConst(const EGameConst& _Other) = delete;
	EGameConst(EGameConst&& _Other) noexcept = delete;
	EGameConst& operator=(const EGameConst& _Other) = delete;
	EGameConst& operator=(EGameConst&& _Other) noexcept = delete;

public:
	static const FIntPoint WorldMaxIndex;
	static const FVector2D TileScale;
	static const FIntPoint TileCount;

	static const FIntPoint DefualtSaveRoomIndex;
	static const FVector2D DefualtSaveLocation;

	static const FIntPoint ClearRoom;

	static const float AnimationTime;
	static const float DefualtSpeed;
	static const float DefualtMoveLen;
	static const float RailSpeed;
	static const float HideTime;
	static const float BGMFadeTimeScale;

};

