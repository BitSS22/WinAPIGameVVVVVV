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

void UEngineInput::KeyCheck(float _Delta)
{
	for (size_t i = 0; i < Keys.size(); ++i)
		Keys[i].KeyCheck(_Delta);
}

void UEngineInput::EventCheck()
{
	for (size_t i = 0; i < Keys.size(); ++i)
		Keys[i].EventCheck();
}

void UEngineInput::BindAction(int _KeyIndex, KeyEvent _EventType, function<void()> _Function)
{
	KeyIndexInvalidCheck(_KeyIndex);

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

	MSGASSERT(nullptr, "키 이벤트 타입이 존재하지 않음.");
}

void UEngineInput::UEngineKey::KeyCheck(float _Delta)
{
	if (GetAsyncKeyState(Key) & 0x8000) // 이번 프레임 키가 눌림
	{
		PressTime += _Delta;

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

void UEngineInput::UEngineKey::EventCheck()
{
	if (IsDown == true)
		for (size_t i = 0; i < DownEvents.size(); ++i)
			DownEvents[i]();

	if (IsPress == true)
		for (size_t i = 0; i < PressEvents.size(); ++i)
			PressEvents[i]();

	if (IsUp == true)
		for (size_t i = 0; i < UpEvents.size(); ++i)
			UpEvents[i]();

	if (IsFree == true)
		for (size_t i = 0; i < FreeEvents.size(); ++i)
			FreeEvents[i]();
}
