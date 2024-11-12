#pragma once
#include "Entity.h"

class APlayer;

class AGuy : public AEntity
{
public:
	AGuy();
	~AGuy();

	AGuy(const AGuy& _Other) = delete;
	AGuy(AGuy&& _Other) noexcept = delete;
	AGuy& operator=(const AGuy& _Other) = delete;
	AGuy& operator=(AGuy&& _Other) noexcept = delete;

private:
	APlayer* Player = nullptr;

};

