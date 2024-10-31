#pragma once
#include <Windows.h>

// Ό³Έν :
class UEngineTimer
{
public:
	UEngineTimer();
	~UEngineTimer();

	UEngineTimer(const UEngineTimer& _Other) = delete;
	UEngineTimer(UEngineTimer&& _Other) noexcept = delete;
	UEngineTimer& operator=(const UEngineTimer& _Other) = delete;
	UEngineTimer& operator=(UEngineTimer&& _Other) noexcept = delete;

private:
	static UEngineTimer* Inst;
	LARGE_INTEGER Count = {};
	LARGE_INTEGER PrevTime = {};
	LARGE_INTEGER CurTime = {};

	double TimeCounter = 0.f;
	double DeltaTime = 0.;
	float fDeltaTime = 0.f;
	float AccumulateDT = 0.f;
	UINT Frame = 0;
	UINT FrameCount = 0;

public:
	void TimeCheck();
	void TimeStart();
	float End();
	double DEnd();

private:

public:
	static UEngineTimer* GetInst()
	{
		return Inst;
	}
	float GetDeltaTime() const
	{
		return fDeltaTime;
	}
	double GetDoubleDeltaTime() const
	{
		return DeltaTime;
	}
	UINT GetFrame() const
	{
		return Frame;
	}

};

