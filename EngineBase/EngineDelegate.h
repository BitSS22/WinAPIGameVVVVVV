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

private:
	vector<function<void()>> Functions = {};

public:
	bool IsBind() const
	{
		return Functions.empty() == false;
	}

	void operator= (function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	void operator()() const
	{
		for (const auto& i : Functions)
			i();
	}

private:

};

