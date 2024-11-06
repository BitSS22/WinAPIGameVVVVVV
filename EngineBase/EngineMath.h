#pragma once

struct FIntPoint;

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
	FVector2D(FIntPoint _Value);
	FVector2D(POINT _Value)
		: X(static_cast<float>(_Value.x))
		, Y(static_cast<float>(_Value.y)) {}
	FVector2D(long _X, long _Y)
		: X(static_cast<float>(_X))
		, Y(static_cast<float>(_Y)) {}

	FVector2D operator+ (FVector2D _Other) const
	{
		return FVector2D(X + _Other.X, Y + _Other.Y);
	}
	FVector2D& operator+= (FVector2D _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
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
			MSGASSERT(nullptr, "0���� ���� �� �����ϴ�.");
		return FVector2D(X / _Value, Y / _Value);
	}
	bool operator== (FVector2D _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}
	bool operator!= (FVector2D _Other) const
	{
		return !(*this == _Other);
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
	float Length() const
	{
		return sqrt(X * X + Y * Y);
	}
	FVector2D& SetNomalize()
	{
		float Scalar = Length();
		if (Scalar == 0.f)
			MSGASSERT(nullptr, "Scalar ���� 0�� Vector�� Nomalize �� �� �����ϴ�.");
		X /= Scalar;
		Y /= Scalar;
		return *this;
	}
	FVector2D GetNomalize() const
	{
		float Scalar = Length();
		if (Scalar == 0.f)
			MSGASSERT(nullptr, "Scalar ���� 0�� Vector�� Nomalize �� �� �����ϴ�.");
		return FVector2D(X / Scalar, Y / Scalar);
	}
	float Dot(FVector2D _Other) const
	{
		return X * _Other.X + Y * _Other.Y;
	}
	std::string ToString() const
	{
		std::string Stream = {};

		Stream += "X : ";
		Stream += std::to_string(X);
		Stream += ", Y : ";
		Stream += std::to_string(Y);

		return Stream;
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

struct FIntPoint
{
public:
	FIntPoint()
	{}
	~FIntPoint()
	{}
	FIntPoint(float _X, float _Y)
		: X(static_cast<int>(_X))
		, Y(static_cast<int>(_Y)) {}
	FIntPoint(int _X, int _Y)
		: X(_X)
		, Y(_Y) {}
	FIntPoint(POINT _Value)
		: X(_Value.x)
		, Y(_Value.y) {}
	FIntPoint(long _X, long _Y)
		: X(_X)
		, Y(_Y) {}
	FIntPoint(FVector2D _Value)
		: X(static_cast<int>(_Value.X))
		, Y(static_cast<int>(_Value.Y)) {}

	FIntPoint operator+ (FIntPoint _Other) const
	{
		return FIntPoint(X + _Other.X, Y + _Other.Y);
	}
	FIntPoint& operator+= (FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}
	FIntPoint operator- (FIntPoint _Value) const
	{
		return FIntPoint(X - _Value.X, Y - _Value.Y);
	}
	FIntPoint& operator-= (FIntPoint _Value)
	{
		X -= _Value.X;
		Y -= _Value.Y;
		return *this;
	}
	FIntPoint operator* (int _Value) const
	{
		return FIntPoint(X * _Value, Y * _Value);
	}
	FIntPoint operator/ (int _Value) const
	{
		if (_Value == 0)
			MSGASSERT(nullptr, "0���� ���� �� �����ϴ�.");
		return FIntPoint(X / _Value, Y / _Value);
	}
	bool operator== (FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}
	bool operator!= (FIntPoint _Other) const
	{
		return !(*this == _Other);
	}

public:
	static const FIntPoint ZERO;
	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	int X = 0;
	int Y = 0;

public:
	float fX() const
	{
		return static_cast<float>(X);
	}
	float fY() const
	{
		return static_cast<float>(Y);
	}
	FIntPoint Half() const
	{
		return FIntPoint(X / 2, Y / 2);
	}
	std::string ToString() const
	{
		std::string Stream = {};

		Stream += "X : ";
		Stream += std::to_string(X);
		Stream += ", Y : ";
		Stream += std::to_string(Y);

		return Stream;
	}

public:
	bool IsZeroOr() const
	{
		return X == 0 || Y == 0;
	}
	bool IsZeroAnd() const
	{
		return X == 0 && Y == 0;
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
	UColor(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
		: R(_r)
		, G(_g)
		, B(_b)
		, A(_a)
	{}
	UColor(unsigned long _Value)
		: Color(_Value)
	{}

	bool operator== (const UColor& _Other)
	{
		return R == _Other.R && G == _Other.G && B == _Other.B;
	}
public:
	static const UColor WHITE;
	static const UColor BLACK;
	union
	{
		int Color = {};
		struct
		{
			uint8_t R;
			uint8_t G;
			uint8_t B;
			uint8_t A;
		};
	};
};