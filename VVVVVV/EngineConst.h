#pragma once
#include "EngineBase/EngineMath.h"

// Ό³Έν :
class EEngineConst
{
private:
	EEngineConst()
	{}
	~EEngineConst()
	{}

	EEngineConst(const EEngineConst& _Other) = delete;
	EEngineConst(EEngineConst&& _Other) noexcept = delete;
	EEngineConst& operator=(const EEngineConst& _Other) = delete;
	EEngineConst& operator=(EEngineConst&& _Other) noexcept = delete;

public:
	static const FIntPoint WorldSize;
	static const FIntPoint TileSize;
	static const FIntPoint TileCount;

};

