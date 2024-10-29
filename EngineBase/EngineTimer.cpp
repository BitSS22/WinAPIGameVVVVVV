#include "pch.h"
#include "EngineTimer.h"

UEngineTimer::UEngineTimer()
{
	QueryPerformanceFrequency(&Count);
	TimeCounter = static_cast<double>(Count.QuadPart);

	QueryPerformanceCounter(&PrevTime);
	QueryPerformanceCounter(&CurTime);
}

UEngineTimer::~UEngineTimer()
{
}

void UEngineTimer::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	double Tick = static_cast<double>(CurTime.QuadPart - PrevTime.QuadPart);
	DeltaTime = Tick / TimeCounter;
	fDeltaTime = static_cast<float>(DeltaTime);
	PrevTime.QuadPart = CurTime.QuadPart;

	// 프레임 체크
	AccumulateDT += fDeltaTime;
	++FrameCount;

	if (AccumulateDT >= 1.f)
	{
		Frame = FrameCount;
		AccumulateDT -= 1.f;
		FrameCount = 0;
	}
}

void UEngineTimer::TimeStart()
{
	QueryPerformanceCounter(&PrevTime);
}

float UEngineTimer::End()
{
	TimeCheck();
	return GetDeltaTime();
}

double UEngineTimer::DEnd()
{
	TimeCheck();
	return GetDoubleDeltaTime();
}
