#include "pch.h"
#include "EngineMath.h"

const FVector2D FVector2D::ZERO = FVector2D(0.f, 0.f);
const FVector2D FVector2D::LEFT = FVector2D(-1.f, 0.f);
const FVector2D FVector2D::RIGHT = FVector2D(1.f, 0.f);
const FVector2D FVector2D::UP = FVector2D(0.f, -1.f);
const FVector2D FVector2D::DOWN = FVector2D(0.f, 1.f);

const FIntPoint FIntPoint::ZERO = FIntPoint(0, 0);
const FIntPoint FIntPoint::LEFT = FIntPoint(-1, 0);
const FIntPoint FIntPoint::RIGHT = FIntPoint(1, 0);
const FIntPoint FIntPoint::UP = FIntPoint(0, -1);
const FIntPoint FIntPoint::DOWN = FIntPoint(0, 1);

const UColor UColor::WHITE = { 255, 255, 255, 0 };
const UColor UColor::BLACK = { 0, 0, 0, 0 };

std::function<bool(const FTransform&, const FTransform&)> FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)] = {};

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Circle)][static_cast<int>(ECollisionType::Circle)] = FTransform::CircleToCircle;
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Circle)] = FTransform::RectToCircle;
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Circle)][static_cast<int>(ECollisionType::Rect)] = FTransform::CircleToRect;
	}
};

CollisionFunctionInit Inst = CollisionFunctionInit();

FVector2D::FVector2D(FIntPoint _Value)
	: X(static_cast<float>(_Value.X))
	, Y(static_cast<float>(_Value.Y))
{}

bool FTransform::Collision(ECollisionType _LeftType, const FTransform& _Left, ECollisionType _RightType, const FTransform& _Right)
{
	return FTransform::AllCollisionFunction[static_cast<int>(_LeftType)][static_cast<int>(_RightType)](_Left, _Right);
}

bool FTransform::PointToCircle(const FTransform& _Left, const FTransform& _Right)
{
	float Lenght = (_Left.Location - _Right.Location).Length();
	if (_Right.Scale.X < Lenght)
		return true;
	return false;
}

bool FTransform::PointToRect(const FTransform& _Left, const FTransform& _Right)
{
	FVector2D LeftLocation = _Left.Location;

	if (LeftLocation.X > _Right.CenterLeft() && LeftLocation.X < _Right.CenterRight() && LeftLocation.Y > _Right.CenterTop() && LeftLocation.Y < _Right.CenterBottom())
		return true;
	return false;
}

bool FTransform::RectToRect(const FTransform& _Left, const FTransform& _Right)
{
	if (_Left.CenterLeft() > _Right.CenterRight())
		return false;
	if (_Left.CenterRight() < _Right.CenterLeft())
		return false;
	if (_Left.CenterTop() > _Right.CenterBottom())
		return false;
	if (_Left.CenterBottom() < _Right.CenterTop())
		return false;
	return true;
}

bool FTransform::RectToCircle(const FTransform& _Left, const FTransform& _Right)
{
	return CircleToRect(_Right, _Left);
}

bool FTransform::CircleToCircle(const FTransform& _Left, const FTransform& _Right)
{
	FVector2D Diff = _Left.Location - _Right.Location;

	if (Diff.Length() < _Left.Scale.HalfX() + _Right.Scale.HalfX())
		return true;
	return false;
}

bool FTransform::CircleToRect(const FTransform& _Left, const FTransform& _Right)
{
	float LeftHLen = _Left.Scale.HalfX();

	if ((_Left.Location - _Right.CenterLeftTop()).Length() < LeftHLen)
		return true;
	if ((_Left.Location - _Right.CenterRightTop()).Length() < LeftHLen)
		return true;
	if ((_Left.Location - _Right.CenterLeftBottom()).Length() < LeftHLen)
		return true;
	if ((_Left.Location - _Right.CenterRightBottom()).Length() < LeftHLen)
		return true;

	FTransform Rect1 = _Right;
	FTransform Rect2 = _Right;
	Rect1.Scale.X += LeftHLen;
	Rect2.Scale.Y += LeftHLen;

	if (PointToRect(_Left, Rect1))
		return true;
	if (PointToRect(_Left, Rect2))
		return true;

	return false;
}
