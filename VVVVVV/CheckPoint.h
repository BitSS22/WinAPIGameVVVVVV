#pragma once
#include "Entity.h"

// Ό³Έν :
class ACheckPoint : public AEntity
{
public:
	ACheckPoint();
	~ACheckPoint();

	ACheckPoint(const ACheckPoint& _Other) = delete;
	ACheckPoint(ACheckPoint&& _Other) noexcept = delete;
	ACheckPoint& operator=(const ACheckPoint& _Other) = delete;
	ACheckPoint& operator=(ACheckPoint&& _Other) noexcept = delete;

private:

public:

private:

};

