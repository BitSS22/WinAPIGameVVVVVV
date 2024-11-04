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
