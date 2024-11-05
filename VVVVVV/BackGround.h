#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ABackGround : public AActor
{
public:
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

private:
	std::vector<USpriteRenderer*> BackGrounds;

public:
	void Insert(USpriteRenderer*);
	
private:
	USpriteRenderer* GetBackGround();
};

