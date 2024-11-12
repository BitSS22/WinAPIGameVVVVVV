#pragma once
#include <string>

// Ό³Έν :
class UObject
{
public:
	UObject();
	virtual ~UObject();

	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

private:
	std::string Name = {};
	float DeathTime = 0.f;
	float CurDeathTime = 0.f;
	bool IsDestroyValue = false;
	bool IsActiveValue = true;
	bool IsDeathTimeCheck = false;
	bool IsDebugValue = false;

public:
	void Destroy(float _Time = 0.f);
	virtual void ReleaseCheck() {}
	virtual void ReleaseTimeCheck();

private:

public:
	void SetName(std::string_view _Name)
	{
		Name.reserve(_Name.size());
		Name = _Name.data();
	}
	std::string GetName() const
	{
		return Name;
	}
	std::string_view GetNameView() const
	{
		return Name.data();
	}
	virtual bool IsActive() const
	{
		return IsActiveValue == true && IsDestroyValue == false;
	}
	virtual bool IsDestroy() const
	{
		return IsDestroyValue;
	}
	void SetActive(bool _IsActive)
	{
		IsActiveValue = _IsActive;
	}
	void SetActiveSwitch()
	{
		IsActiveValue = !IsActiveValue;
	}
	bool IsDebug()
	{
		return IsDebugValue;
	}
	void DebugOn()
	{
		IsDebugValue = true;
	}
	void DebugOff()
	{
		IsDebugValue = false;
	}
	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

};

