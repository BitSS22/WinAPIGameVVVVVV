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
	static const FIntPoint TileScale;
	static const FIntPoint TileCount;

	static const float AnimationTime;
	static const float DefualtSpeed;
	static const float DefualtMoveLen;
	static const float RailSpeed;

};

