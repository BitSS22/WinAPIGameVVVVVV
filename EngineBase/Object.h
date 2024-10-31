#pragma once

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

public:

private:

public:
	void SetName(std::string_view _Name)
	{
		Name.reserve(_Name.size());
		Name = _Name.data();
	}
	string GetName() const
	{
		return Name;
	}
	string GetNameView() const
	{
		return Name.c_str();
	}

};

