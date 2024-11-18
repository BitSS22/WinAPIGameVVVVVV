#pragma once
#include "Entity.h"

// Ό³Έν :
class ATeleport : public AEntity
{
public:
	ATeleport();
	~ATeleport();

	ATeleport(const ATeleport& _Other) = delete;
	ATeleport(ATeleport&& _Other) noexcept = delete;
	ATeleport& operator=(const ATeleport& _Other) = delete;
	ATeleport& operator=(ATeleport&& _Other) noexcept = delete;

private:

public:

private:

};

