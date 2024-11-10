#pragma once
class AEntity : public AActor
{
public:
	AEntity();
	~AEntity();

	AEntity(const AEntity& _Other) = delete;
	AEntity(AEntity&& _Other) noexcept = delete;
	AEntity& operator=(const AEntity& _Other) = delete;
	AEntity& operator=(AEntity&& _Other) noexcept = delete;

private:

public:

};

