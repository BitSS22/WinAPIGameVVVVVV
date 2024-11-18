#pragma once
#include <EngineCore/SpriteRenderer.h>
#include "BackGround.h"
#include "Room.h"
#include "GameWorld.h"

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
	std::vector<std::string> TileLists[static_cast<int>(ETileType::Last)] = {};
	ETileType CurTileList = ETileType::Last;
	int CurTileSetIndex = 0;

	std::vector<std::string> EntityLists[static_cast<int>(EEntityType::Last)] = {};
	EEntityType CurEntityList = EEntityType::Last;
	int CurEntityIndex = 0;
	
	std::vector<std::string> BackGroundLists[static_cast<int>(EBackGroundType::Last)] = {};
	EBackGroundType CurBackGroundList = EBackGroundType::Last;
	int CurBackGroundIndex = 0;

	ATile* CurSelectTile = nullptr;
	AEntity* CurSelectEntity = nullptr;
	
	AEntity* CurAdjustmentEntity = nullptr;
	int CurAdjustmentEntityIndex = -1;
	
	AGameWorld* GameWorld = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	int AroundTileChange(const string& _Name, int _X, int _Y);
	int FindAroundTile(uint8_t _Bit) const;
	bool IsSameTileName(const string& _Name, int x, int y) const;
	std::vector<std::vector<ATile*>>& GetCurSelectTileMap() const
	{
		switch (CurTileList)
		{
		case ETileType::BackGround:
			return GameWorld->GetRoom()->BackGroundTiles;
			break;
		default:
			return GameWorld->GetRoom()->Tiles;
			break;
		}
	}

	void ChangeTile(bool _AroundTileChange, FIntPoint _Index);
	void DeleteTile(bool _AroundTileChange, FIntPoint _Index);

	void MoveRoom(FIntPoint _Index);
	void SwitchLoopRoom();

	void NextTileList();
	void PrevTileList();
	void PrevTileSet();
	void NextTileSet();
	void PrevTile();
	void NextTile();
	void PrevBackGroundImage();
	void NextBackGroundImage();

	void CreateEntity();
	void DeleteEntity();

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
	AGameWorld* GetGameWorld()
	{
		return GameWorld;
	}

};