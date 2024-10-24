#pragma once

class FVector2D
{
public:
	FVector2D()
	{}
	~FVector2D()
	{}
	FVector2D(float _X, float _Y)
		: X(_X)
		, Y(_Y) {}
	FVector2D(int _X, int _Y)
		: X(static_cast<float>(_X))
		, Y(static_cast<float>(_Y)) {}

	FVector2D operator* (float _Value) const
	{
		return FVector2D(X * _Value, Y * _Value);
	}
	FVector2D operator+ (FVector2D _Value) const
	{
		return FVector2D(X + _Value.X, Y + _Value.Y);
	}
	FVector2D operator- (FVector2D _Value) const
	{
		return FVector2D(X - _Value.X, Y - _Value.Y);
	}
	FVector2D operator/ (FVector2D _Value) const
	{
		if (_Value.X == 0.f || _Value.Y == 0.f)
			MSGASSERT(nullptr, "0으로 나눌 수 없습니다.");
		return FVector2D(X / _Value.X, Y / _Value.Y);
	}
	FVector2D operator/ (int _Value) const
	{
		if (_Value == 0.f)
			MSGASSERT(nullptr, "0으로 나눌 수 없습니다.");
		return FVector2D(X / _Value, Y / _Value);
	}
	bool operator== (FVector2D _Other)
	{
		return X == _Other.X && Y == _Other.Y;
	}
	FVector2D& operator+= (FVector2D _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

public:
	static const FVector2D ZERO;
	static const FVector2D LEFT;
	static const FVector2D RIGHT;
	static const FVector2D UP;
	static const FVector2D DOWN;

	float X = 0.f;
	float Y = 0.f;

public:
	int iX()
	{
		return static_cast<int>(X);
	}
	int iY()
	{
		return static_cast<int>(Y);
	}
	FVector2D Half()
	{
		return FVector2D(X * 0.5f, Y * 0.5f);
	}

};

class FIntPoint
{
public:
	FIntPoint()
	{}
	FIntPoint(int _X, int _Y)
		: X(_X)
		, Y(_Y) {};

	FIntPoint operator+ (FIntPoint _Other) const
	{
		return FIntPoint(X + _Other.X, Y + _Other.Y);
	}
	FIntPoint operator/ (FIntPoint _Other) const
	{
		if (_Other.X == 0 || _Other.Y == 0)
			MSGASSERT(nullptr, "0으로 나눌 수 없습니다.");
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

public:
	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;	
	int X = 0;
	int Y = 0;

public:
	
};

