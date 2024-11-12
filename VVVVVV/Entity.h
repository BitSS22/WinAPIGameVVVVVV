#pragma once

// ���� :
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
	USpriteRenderer* Renderer = nullptr;

public:
	virtual void BeginPlay() override;

private:

public:
	USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}
	void EntityDefaultSetUp(std::string_view _Name, FVector2D _Location);

	virtual void AddEntityLocation(FVector2D _Location)
	{
		AddActorLocation(_Location);
	}

};

