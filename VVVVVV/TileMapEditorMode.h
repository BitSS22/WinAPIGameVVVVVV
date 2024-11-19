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
	std::vector<RoomTileData> TileDatas[static_cast<int>(ETileType::Last)] = {};
	ETileType CurTileType = ETileType::Collision;
	int CurTileIndex = 0;

	std::vector<RoomBackGroundData> BackGroundDatas[static_cast<int>(EBackGroundType::Last)] = {};
	EBackGroundType CurBackGroundType = EBackGroundType::Space;
	int CurBackGroundIndex = 0;

	std::vector<RoomEntityData> EntityDatas[static_cast<int>(EEntityType::Last)] = {};
	EEntityType CurEntityType = EEntityType::Enermy;
	int CurEntityIndex = 0;

	USpriteRenderer* CurSelectTile = nullptr;
	USpriteRenderer* CurSelectEntity = nullptr;
	
	AEntity* CurAdjustmentEntity = nullptr;
	int CurAdjustmentEntityIndex = -1;
	
	AGameWorld* GameWorld = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;


private:
	int GetCheckAroundTileIndex(std::string_view _Name, const FIntPoint& _Index) const;
	bool IsSameTileName(std::string_view _Name, const FIntPoint& _Index) const;

	void PickUpTile();
	void ChangeTile(bool _AroundTileChange, FIntPoint _Index);
	void DeleteTile(bool _AroundTileChange, FIntPoint _Index);

	void CreateEntity();
	void DeleteEntity();

	void MoveRoom(FIntPoint _Index);

	void SwitchLoopRoom();

	void SetTileType(ETileType _Type);
	void AddTileList(int _Value);
	void AddTileSpriteIndex(int _Value);

	void SetBackGroundType(EBackGroundType _Type);
	void AddBackGroundList(int _Value);

	void SetEntityType(EEntityType _Type);
	void AddEntityList(int _Value);

	void PrevSelectEntity();
	void NextSelectEntity();

	void AddEntityLocation(const FVector2D& _AddPos);
	void AddEntitySpeed(float _Speed);
	void AddEntityMoveLenght(float _Lenght);
	void AddEntityMoveOffSet(float _Offset);
	void AddEntityDir(const FVector2D& _Dir);
	void SetEntityDir(const FVector2D& _Dir);

	void LoadResourceList();
	void EditorKeyCheck();
	void DebugText();

	void SaveWorldDataFile();
	void LoadWorldDataFile();

public:
	AGameWorld* GetGameWorld() const
	{
		return GameWorld;
	}

};