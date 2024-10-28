#include "pch.h"
#include "EngineInput.h"

UEngineInput::UEngineInput()
{
	Keys.reserve(0xFF);

	for (int i = 0; i <= 0xFF; ++i)
		Keys.push_back(i);
}

UEngineInput::~UEngineInput()
{
}

void UEngineInput::KeyCheck(float _DeltaTime)
{
	for (size_t i = 0; i < Keys.size(); ++i)
		Keys[i].KeyCheck(_DeltaTime);
}

void UEngineInput::EventCheck(float _DeltaTime)
{
	for (size_t i = 0; i < Keys.size(); ++i)
		Keys[i].EventCheck(_DeltaTime);
}

void UEngineInput::BindAction(int _KeyIndex, KeyEvent _EventType, function<void(float)> _Function)
{
	if (_KeyIndex >= Keys.size())
		MSGASSERT(nullptr, "키 값을 벗어남.");

	switch (_EventType)
	{
	case KeyEvent::Down:
		Keys[_KeyIndex].DownEvents.push_back(_Function);
		return;
	case KeyEvent::Press:
		Keys[_KeyIndex].PressEvents.push_back(_Function);
		return;
	case KeyEvent::Up:
		Keys[_KeyIndex].UpEvents.push_back(_Function);
		return;
	case KeyEvent::Free:
		Keys[_KeyIndex].FreeEvents.push_back(_Function);
		return;
	}

	MSGASSERT(nullptr, "error");
}

void UEngineInput::UEngineKey::KeyCheck(float _DeltaTime)
{
	if (GetAsyncKeyState(Key) & 0x8000) // 이번 프레임 키가 눌림
	{
		PressTime += _DeltaTime;

		if (IsPress == true) // 이전 프레임 키가 눌림
		{
			IsDown = false;
			IsPress = true;
			IsUp = false;
			IsFree = false;
		}
		else if (IsPress == false)  // 이전 프레임 키가 안 눌림
		{
			IsDown = true;
			IsPress = true;
			IsUp = false;
			IsFree = false;
		}
	}
	else  // 이번 프레임 키가 안 눌림
	{
		PressTime = 0.f;

		if (IsPress == true) // 이전 프레임 키가 눌림
		{
			IsDown = false;
			IsPress = false;
			IsUp = true;
			IsFree = true;
		}
		else if (IsPress == false)  // 이전 프레임 키가 안 눌림
		{
			IsDown = false;
			IsPress = false;
			IsUp = false;
			IsFree = true;
		}
	}
}

void UEngineInput::UEngineKey::EventCheck(float _DeltaTime)
{
	if (IsDown == true)
		for (size_t i = 0; i < DownEvents.size(); ++i)
			DownEvents[i](_DeltaTime);

	if (IsPress == true)
		for (size_t i = 0; i < PressEvents.size(); ++i)
			PressEvents[i](_DeltaTime);

	if (IsUp == true)
		for (size_t i = 0; i < UpEvents.size(); ++i)
			UpEvents[i](_DeltaTime);

	if (IsFree == true)
		for (size_t i = 0; i < FreeEvents.size(); ++i)
			FreeEvents[i](_DeltaTime);
}
