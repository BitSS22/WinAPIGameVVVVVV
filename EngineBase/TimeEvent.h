#pragma once
#include <functional>

struct TimeEventFunction
{
public:
	float Time = 0.f;
	float MaxTime = 0.f;
	std::function<void()> Event = {};
	bool Loop = false;
};
// Ό³Έν :
class UTimeEvent
{
public:
	UTimeEvent();
	~UTimeEvent();

	UTimeEvent(const UTimeEvent& _Other) = delete;
	UTimeEvent(UTimeEvent&& _Other) noexcept = delete;
	UTimeEvent& operator=(const UTimeEvent& _Other) = delete;
	UTimeEvent& operator=(UTimeEvent&& _Other) noexcept = delete;

private:
	std::list<TimeEventFunction> Events = {};

public:
	void PushEvent(float _Time, std::function<void()> _Function, bool _Loop = false)
	{
		Events.push_front({ _Time, _Time, _Function, _Loop });
	}
	void Update()
	{
		for (auto iter = Events.begin(); iter != Events.end();)
		{
			TimeEventFunction& TimeEvent = *iter;
			TimeEvent.Time -= GET_DELTA;

			if (TimeEvent.Time < 0.f)
			{
				TimeEvent.Event();
				if (TimeEvent.Loop == false)
					iter = Events.erase(iter);
				else
				{
					++iter;
					TimeEvent.Time = TimeEvent.MaxTime;
				}
			}
			else
				++iter;
		}
	}

private:

};

