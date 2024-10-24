#include "pch.h"
#include "EngineMath.h"

const FVector2D FVector2D::ZERO = FVector2D(0.f, 0.f);
const FVector2D FVector2D::LEFT = FVector2D(-1.f, 0.f);
const FVector2D FVector2D::RIGHT = FVector2D(1.f, 0.f);
const FVector2D FVector2D::UP = FVector2D(0.f, -1.f);
const FVector2D FVector2D::DOWN = FVector2D(0.f, 1.f);

const FIntPoint FIntPoint::LEFT = { -1, 0 };
const FIntPoint FIntPoint::RIGHT = { 1, 0 };
const FIntPoint FIntPoint::UP = { 0, -1 };
const FIntPoint FIntPoint::DOWN = { 0, 1 };