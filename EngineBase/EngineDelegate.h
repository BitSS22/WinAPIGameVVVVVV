#pragma once

// Ό³Έν :
class UEngineDelegate
{
public:
	UEngineDelegate();
	UEngineDelegate(function<void()> _Function)
	{
		Functions.push_back(_Function);
	}
	~UEngineDelegate();

	void operator+= (function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	void operator()() const
	{
		for (const auto& i : Functions)
			i();
	}

private:
	vector<function<void()>> Functions = {};

public:
	
private:

public:
	bool IsBind() const
	{
		return Functions.empty() == false;
	}
};

