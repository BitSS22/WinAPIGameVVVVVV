#pragma once

class Bullet : public AActor
{
public:
	Bullet();
	~Bullet();

private:
	FVector2D Dir = FVector2D(0.f, 0.f);

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:

public:
	void SetDir(FVector2D _Dir)
	{
		Dir = _Dir;
	}

};

