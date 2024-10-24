#pragma once

// Ό³Έν :
class EngineDelegate
{
public:
	EngineDelegate();
	EngineDelegate(function<void()> _Function)
	{
		Functions.push_back(_Function);
	}
	~EngineDelegate();

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

