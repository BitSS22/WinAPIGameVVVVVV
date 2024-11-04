#include "pch.h"
#include "EngineRandom.h"

UEngineRandom::UEngineRandom()
{
}

UEngineRandom::UEngineRandom(size_t _Seed)
	: Gen(std::mt19937_64(_Seed))
{
}

UEngineRandom::~UEngineRandom()
{
}

