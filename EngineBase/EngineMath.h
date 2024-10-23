#pragma once
#include "EngineDebug.h"

class FIntPoint
{
public:
	FIntPoint()
	{}
	FIntPoint(int _X, int _Y)
		: X(_X)
		, Y(_Y) {};

	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

public:
	FIntPoint operator+ (FIntPoint _Other) const
	{
		return FIntPoint(X + _Other.X, Y + _Other.Y);
	}
	FIntPoint operator/ (FIntPoint _Other) const
	{
		if (_Other.X == 0 || _Other.Y == 0)
			MSGASSERT("0으로 나눌 수 없습니다.");
		return FIntPoint(X / _Other.X, Y / _Other.Y);
	}
	bool operator== (FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}
	FIntPoint& operator+= (FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}
};

