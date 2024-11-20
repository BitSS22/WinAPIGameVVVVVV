#pragma once

// 설명 :
class UFSMStateManager
{
public:
	INNER_CLASS struct FSMState;
public:
	UFSMStateManager() {};
	~UFSMStateManager() {};

	UFSMStateManager(const UFSMStateManager& _Other) = delete;
	UFSMStateManager(UFSMStateManager&& _Other) noexcept = delete;
	UFSMStateManager& operator=(const UFSMStateManager& _Other) = delete;
	UFSMStateManager& operator=(UFSMStateManager&& _Other) noexcept = delete;

private:
	FSMState* CurState = nullptr;
	std::map<int, FSMState> States = {};

public:
	void Update()
	{
		if (CurState == nullptr)
			MSGASSERT(nullptr, "FSM이 없습니다.");
		CurState->UpdateFunction();
	}

	template<typename EnumType>
	void CreateState(EnumType _Key, std::function<void()> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		CreateState(static_cast<int>(_Key), _UpdateFunction, _Start);
	}
	void CreateState(int _Key, std::function<void()> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		if (States.contains(_Key) == true)
			MSGASSERT(nullptr, "이 FSMState는 이미 존재합니다.");

		States[_Key].UpdateFunction = _UpdateFunction;
		States[_Key].StartFunction = _Start;
	}
	template<typename EnumType>
	void ChangeState(EnumType _Key)
	{
		ChangeState(static_cast<int>(_Key));
	}
	void ChangeState(int _Key)
	{
		if (States.contains(_Key) == false)
			MSGASSERT(nullptr, "이 FSM은 없습니다.");

		CurState = &States[_Key];
		if (CurState->StartFunction != nullptr)
			CurState->StartFunction();
	}

private:

public:
	INNER_CLASS struct FSMState
	{
		std::function<void()> StartFunction = nullptr;
		std::function<void()> UpdateFunction = nullptr;
		std::function<void()> EndFunction = nullptr;
	};
};

