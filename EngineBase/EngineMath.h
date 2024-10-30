#pragma once

struct FVector2D
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
	FVector2D(POINT _Value)
		: X(static_cast<float>(_Value.x))
		, Y(static_cast<float>(_Value.y)) {}
	FVector2D(long _X, long _Y)
		: X(static_cast<float>(_X))
		, Y(static_cast<float>(_Y)) {}

	FVector2D operator+ (FVector2D _Value) const
	{
		return FVector2D(X + _Value.X, Y + _Value.Y);
	}
	FVector2D operator- (FVector2D _Value) const
	{
		return FVector2D(X - _Value.X, Y - _Value.Y);
	}
	FVector2D& operator-= (FVector2D _Value)
	{
		X -= _Value.X;
		Y -= _Value.Y;
		return *this;
	}
	FVector2D operator* (float _Value) const
	{
		return FVector2D(X * _Value, Y * _Value);
	}
	FVector2D operator/ (float _Value) const
	{
		if (_Value == 0.f)
			MSGASSERT(nullptr, "0으로 나눌 수 없습니다.");
		return FVector2D(X / _Value, Y / _Value);
	}
	bool operator== (FVector2D _Other) const
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
	bool EqualInt(FVector2D _Other) const
	{
		return iX() == _Other.iX() && iY() == _Other.iY();
	}
	int iX() const
	{
		return static_cast<int>(X);
	}
	int iY() const
	{
		return static_cast<int>(Y);
	}
	FVector2D Half() const
	{
		return FVector2D(X * 0.5f, Y * 0.5f);
	}
	float Getscalar() const
	{
		return sqrt(X * X + Y * Y);
	}
	FVector2D& SetNomalize()
	{
		float Scalar = Getscalar();
		if (Scalar == 0.f)
			MSGASSERT(nullptr, "Scalar 값이 0인 Vector를 Nomalize 할 수 없습니다.");
		X /= Scalar;
		Y /= Scalar;
		return *this;
	}
	FVector2D GetNomalize()
	{
		float Scalar = Getscalar();
		if (Scalar == 0.f)
			MSGASSERT(nullptr, "Scalar 값이 0인 Vector를 Nomalize 할 수 없습니다.");
		return FVector2D(X / Scalar, Y / Scalar);
	}

public:
	bool IsZeroOr() const
	{
		return X == 0.f || Y == 0.f;
	}
	bool IsZeroAnd() const
	{
		return X == 0.f && Y == 0.f;
	}

};

struct FTransform
{
public:
	FVector2D Location = {};
	FVector2D Scale = {};

public:
	FVector2D CenterLeftTop() const
	{
		return Location - Scale.Half();
	}
	FVector2D CenterRightBottom() const
	{
		return Location + Scale.Half();
	}

};

struct UColor
{
public:
	UColor(UCHAR _r, UCHAR _g, UCHAR _b, UCHAR _a)
		: R(_r)
		, G(_g)
		, B(_b)
		, A(_a)
	{}
public:
	union
	{
		int Color = {};
		struct
		{
			UCHAR R;
			UCHAR G;
			UCHAR B;
			UCHAR A;
		};
	};
};