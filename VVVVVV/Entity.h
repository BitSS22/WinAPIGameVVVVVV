#pragma once

class AGameWorld;
class ARoom;

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
	ARoom* Room = nullptr;
protected:
	USpriteRenderer* SpriteRenderer = nullptr;

public:
	virtual void BeginPlay() override;
	void EntityDefaultSetUp(std::string_view _Name, FVector2D _Location);

private:

public:
	USpriteRenderer* GetRenderer()
	{
		return SpriteRenderer;
	}

	virtual void AddEntityLocation(FVector2D _Location)
	{
		AddActorLocation(_Location);
	}

	void SetRoom(ARoom* _Room)
	{
		Room = _Room;
	}
	ARoom* GetRoom()
	{
		return Room;
	}

};

