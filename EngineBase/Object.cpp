#include "pch.h"
#include "Object.h"

UObject::UObject()
{
}

UObject::~UObject()
{
}

void UObject::Destroy(float _Time)
{
	DeathTime = _Time;

	if (DeathTime > 0.f)
	{
		IsDeathTimeCheck = true;
		return;
	}
	IsDestroyValue = true;
}

void UObject::ReleaseCheck()
{
	if (IsDeathTimeCheck == false)
		return;

	CurDeathTime += UEngineTimer::GetInst()->GetDeltaTime();
	
	if (DeathTime <= CurDeathTime)
		IsDestroyValue = true;
}

