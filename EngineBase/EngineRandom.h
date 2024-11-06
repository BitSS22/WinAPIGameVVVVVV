#pragma once
#include <random>

// ���� :
class UEngineRandom
{
public:
	UEngineRandom();
	UEngineRandom(size_t _Seed);
	~UEngineRandom();

	UEngineRandom(const UEngineRandom& _Other) = delete;
	UEngineRandom(UEngineRandom&& _Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& _Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& _Other) noexcept = delete;

private:
	std::random_device rd = {};
	std::mt19937_64 Gen = std::mt19937_64(rd());

public:

private:

public:
	void SetSeed(size_t _Seed)
	{
		Gen = std::mt19937_64(_Seed);
	}
	int GetRandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> Number(_Min, _Max + 1);
		return Number(Gen);
	}
	float GetRandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution<float> Number(_Min, _Max);
		return Number(Gen);
	}

};

