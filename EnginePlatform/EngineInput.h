#pragma once

enum class KeyEvent
{
	Down,
	Press,
	Up,
	Free
};

class UEngineInput
{
public:
	INNER_CLASS class UEngineKey;
private:
	UEngineInput();
public:
	~UEngineInput();

	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;

private:
	vector<UEngineKey> Keys = {};

public:
	void BindAction(int _KeyIndex, KeyEvent _EventType, function<void()> _Function);

private:
	void KeyCheck(float _Delta);
	void EventCheck();
	void KeyIndexInvalidCheck(int _KeyIndex)
	{
		if (_KeyIndex < 0 || _KeyIndex >= Keys.size())
			MSGASSERT(nullptr, "키 값을 벗어남.");
	}

public:
	static UEngineInput& GetInst()
	{
		static UEngineInput Inst = {};
		return Inst;
	}
	bool IsDown(int _KeyIndex)
	{
		KeyIndexInvalidCheck(_KeyIndex);
		return Keys[_KeyIndex].IsDown;
	}
	bool IsPress(int _KeyIndex)
	{
		KeyIndexInvalidCheck(_KeyIndex);
		return Keys[_KeyIndex].IsPress;
	}
	bool IsUp(int _KeyIndex)
	{
		KeyIndexInvalidCheck(_KeyIndex);
		return Keys[_KeyIndex].IsUp;
	}
	bool IsFree(int _KeyIndex)
	{
		KeyIndexInvalidCheck(_KeyIndex);
		return Keys[_KeyIndex].IsFree;
	}
	float GetPressTime(int _KeyIndex)
	{
		KeyIndexInvalidCheck(_KeyIndex);
		return Keys[_KeyIndex].PressTime;
	}

private:
	INNER_CLASS
	class UEngineKey
	{
	public:
		UEngineKey(int _Key)
			:Key(_Key)
		{}
		~UEngineKey()
		{}

	public:
		int Key = -1;
		bool IsDown = false;
		bool IsPress = false;
		bool IsUp = false;
		bool IsFree = false;
		float PressTime = 0.f;
		vector<function<void()>> DownEvents = {};
		vector<function<void()>> PressEvents = {};
		vector<function<void()>> UpEvents = {};
		vector<function<void()>> FreeEvents = {};

	public:
		void KeyCheck(float _Delta);
		void EventCheck();

	};
};

