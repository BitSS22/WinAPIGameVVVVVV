#pragma once
#include <EnginePlatform/EngineWindowImage.h>
#include <vector>
#include "GameWorld.h"

class AEntity;
class ABackGround;
class ATile;

class ARoom : public AActor
{
public:
	friend class ATileMapEditorMode;
public:
	ARoom();
	~ARoom();

	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

private:
	ABackGround* BackGround = nullptr;
	std::vector<std::vector<ATile*>> Tiles = {};
	std::vector<AEntity*> Entites = {};
	FIntPoint CurRoomIndex = {};
	bool LoopRoom = false;

	AGameWorld* GameWorld = nullptr;

public:
	virtual void BeginPlay() override;

	void MoveRoom(FIntPoint _Index);
	
	void SetRoom(const FIntPoint& _Index);
	void SetRoom(const RoomData& _Data);
	RoomData GetRoomData();

	static FIntPoint GetOnTileIndex(FVector2D _Pos);
	ETileType GetTileType(const FVector2D& _Location) const;
	ETileType GetTileType(const FIntPoint& _Index) const;

	static bool IsOutScreen(const FVector2D& _Location);
	static bool IsOutTileIndex(const FIntPoint& _Index);

private:

public:
	void SetGameWorld(AGameWorld* _ptr)
	{
		GameWorld = _ptr;
	}
	AGameWorld* GetGameWorld() const
	{
		return GameWorld;
	}
	ABackGround* GetBackGround() const
	{
		return BackGround;
	}
	FIntPoint GetCurRoomIndex() const
	{
		return CurRoomIndex;
	}
	const std::vector<std::vector<ATile*>>& GetTilesCRef() const
	{
		return Tiles;
	}
	const std::vector<AEntity*>& GetEntitesCRef() const
	{
		return Entites;
	}
	bool GetIsLoop() const
	{
		return LoopRoom;
	}
	void SetIsLoop(bool _Value)
	{
		LoopRoom = _Value;
	}

};

