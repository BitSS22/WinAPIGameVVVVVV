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
	void KeyCheck(float _DeltaTime);
	void EventCheck(float _DeltaTime);
	void BindAction(int _KeyIndex, KeyEvent _EventType, function<void(float)> _Function);

private:

public:
	static UEngineInput& GetInst()
	{
		static UEngineInput Inst = {};
		return Inst;
	}
	bool IsDown(int _KeyIndex)
	{
		if (_KeyIndex >= Keys.size())
			MSGASSERT(nullptr, "키 값을 벗어남.");
		return Keys[_KeyIndex].IsDown;
	}
	bool IsPress(int _KeyIndex)
	{
		if (_KeyIndex >= Keys.size())
			MSGASSERT(nullptr, "키 값을 벗어남.");
		return Keys[_KeyIndex].IsPress;
	}
	bool IsUp(int _KeyIndex)
	{
		if (_KeyIndex >= Keys.size())
			MSGASSERT(nullptr, "키 값을 벗어남.");
		return Keys[_KeyIndex].IsUp;
	}
	bool IsFree(int _KeyIndex)
	{
		if (_KeyIndex >= Keys.size())
			MSGASSERT(nullptr, "키 값을 벗어남.");
		return Keys[_KeyIndex].IsFree;
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
		vector<function<void(float)>> DownEvents = {};
		vector<function<void(float)>> PressEvents = {};
		vector<function<void(float)>> UpEvents = {};
		vector<function<void(float)>> FreeEvents = {};

	public:
		void KeyCheck(float _DeltaTime);
		void EventCheck(float _DeltaTime);

	};
};

