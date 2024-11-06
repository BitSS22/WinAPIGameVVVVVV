#pragma once
#include "EngineBase/EngineMath.h"

// ���� :
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
	static const FIntPoint WorldSize;
	static const FIntPoint TileScale;
	static const FIntPoint TileCount;

};
