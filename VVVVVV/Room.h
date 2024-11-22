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
	bool LoopRoom = false;

public:
	virtual void BeginPlay() override;

	void MoveRoom(FIntPoint _Index);
	
	RoomData GetRoomData();

	const ATile* GetTile(const FIntPoint& _Index) const;
	FIntPoint GetOnTileIndex(const FVector2D& _Pos) const;
	int GetOnTileXIndex(float _X) const;
	int GetOnTileYIndex(float _Y) const;
	FTransform GetTileTransform(const FIntPoint& _TileIndex) const;
	float GetTileTopLine(int _YIndex);
	float GetTileBottomLine(int _YIndex);
	float GetTileLeftLine(int _XIndex);
	float GetTileRightLine(int _XIndex);
	ETileType GetTileType(const FVector2D& _Location) const;
	ETileType GetTileType(const FIntPoint& _Index) const;

	// Return Out Dir, Not Out To Return ZERO Dir.
	FVector2D IsOutScreen(const FTransform& Transform) const;
	FVector2D IsOutScreen(const FVector2D& _Location) const;
	bool IsOutTileIndex(const FIntPoint& _Index) const;

private:
	void SetRoom(const FIntPoint& _RoomIndex);
	void SetRoom(const RoomData& _Data);

	void FileLoadInit();

public:
	ABackGround* GetBackGround() const
	{
		return BackGround;
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
	void SetEntityMove(bool _Value);

};

