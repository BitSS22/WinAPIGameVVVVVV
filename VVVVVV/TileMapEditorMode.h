#pragma once
#include <EngineCore/SpriteRenderer.h>
#include "BackGround.h"
#include "Room.h"
#include "GameWorld.h"
#include "Tile.h"

class ATileMapEditorMode : public AGameMode
{
public:
	ATileMapEditorMode();
	~ATileMapEditorMode();

	ATileMapEditorMode(const ATileMapEditorMode& _Other) = delete;
	ATileMapEditorMode(ATileMapEditorMode&& _Other) noexcept = delete;
	ATileMapEditorMode& operator=(const ATileMapEditorMode& _Other) = delete;
	ATileMapEditorMode& operator=(ATileMapEditorMode&& _Other) noexcept = delete;

private:
	std::vector<AGameWorld::RoomData::RoomTileData> TileDatas[static_cast<int>(ETileType::Last)] = {};
	ETileType CurTileType = ETileType::Last;
	int CurTileListIndex = 0;

	std::vector<AGameWorld::RoomData::RoomEntityData> EntityDatas[static_cast<int>(EEntityType::Last)] = {};
	EEntityType CurEntityType = EEntityType::Last;
	int CurEntityIndex = 0;
	
	std::vector<AGameWorld::RoomData::RoomBackGroundData> BackGroundDatas[static_cast<int>(EBackGroundType::Last)] = {};
	EBackGroundType CurBackGroundType = EBackGroundType::Last;
	int CurBackGroundIndex = 0;

	USpriteRenderer* CurSelectTile = nullptr;
	USpriteRenderer* CurSelectEntity = nullptr;
	
	AEntity* CurAdjustmentEntity = nullptr;
	int CurAdjustmentEntityIndex = -1;
	
	AGameWorld* GameWorld = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	int GetCheckAroundTileIndex(std::string_view _Name, int _X, int _Y) const;
	bool IsSameTileName(std::string_view _Name, int x, int y) const;

	void ChangeTile(bool _AroundTileChange, FIntPoint _Index);
	void DeleteTile(bool _AroundTileChange, FIntPoint _Index);

	void CreateEntity();
	void DeleteEntity();

	void MoveRoom(FIntPoint _Index);
	void SwitchLoopRoom();

	void NextTileType();
	void PrevTileType();
	void PrevTileSet();
	void NextTileSet();
	void PrevTileIndex();
	void NextTileIndex();

	void PrevBackGroundImage();
	void NextBackGroundImage();

	void PrevEntityList();
	void NextEntityList();
	void PrevEntityType(int _AddIndex);
	void NextEntityType(int _AddIndex);

	void PrevSelectEntity();
	void NextSelectEntity();

	void AddEntityLocation(FVector2D _AddPos);
	void AddEntitySpeed(float _Speed);
	void AddEntityMoveLenght(float _Lenght);
	void AddEntityMoveOffSet(float _Offset);
	void AddEntityDir(FVector2D _Dir);
	void SetEntityDir(FVector2D _Dir);

	void ShowTiles();
	void ShowBackGroundTiles();

	void PickUpTile();

	void LoadResourceList();

	void EditorKeyCheck();
	void DebugText();

public:
	AGameWorld* GetGameWorld() const
	{
		return GameWorld;
	}

};