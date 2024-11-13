#pragma once
#include <EngineCore/SpriteRenderer.h>
#include "BackGround.h"
#include "Room.h"
#include "GameWorld.h"

enum class TileList
{
	BackGroundTileList,
	TileList,
	SpikeTileList,
	AnimationTileList,
	BackGroundList,
	LAST
};
enum class EntityList
{
	Platforms,
	InterObjects,
	Enemies,
	LAST
};

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
	std::vector<std::string> TileLists[static_cast<int>(TileList::LAST)] = {};
	std::vector<std::string> EntityLists[static_cast<int>(EntityList::LAST)] = {};
	TileList CurSelectTileList = TileList::TileList;
	EntityList CurSelectEntityList = EntityList::Enemies;
	int CurTileSetIndex = 0;
	int CurEntityIndex = 0;
	int CurBackGroundIndex = 0;
	AGameWorld* GameWorld = nullptr;
	USpriteRenderer* CurSelectSprite = nullptr;
	USpriteRenderer* CurSelectEntityType = nullptr;
	AEntity* CurAdjustmentEntity = nullptr;
	int CurAdjustmentEntityIndex = -1;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	int AroundTileChange(const string& _Name, int _X, int _Y);
	int FindAroundTile(uint8_t _Bit) const;
	bool IsSameTileName(const string& _Name, int x, int y) const;
	std::vector<std::vector<USpriteRenderer*>>& GetCurSelectTileMap() const
	{
		switch (CurSelectTileList)
		{
		case TileList::BackGroundTileList:
			return GameWorld->GetRoom()->BackGroundTiles;
			break;
		case TileList::TileList:
		case TileList::SpikeTileList:
		case TileList::AnimationTileList:
			return GameWorld->GetRoom()->Tiles;
			break;
		default:
			MSGASSERT(nullptr, "타일 리스트가 제대로 선택되지 않았습니다.");
			break;
		}
		return GameWorld->GetRoom()->Tiles;
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
	void AddTileList(std::string_view _Name)
	{
		TileLists[static_cast<int>(TileList::TileList)].push_back(_Name.data());
	}
	void AddBackGroundTileList(std::string_view _Name)
	{
		TileLists[static_cast<int>(TileList::BackGroundTileList)].push_back(_Name.data());
	}
	void AddSpikeTileList(std::string_view _Name)
	{
		TileLists[static_cast<int>(TileList::SpikeTileList)].push_back(_Name.data());
	}
	void AddAnimationTileList(std::string_view _Name)
	{
		TileLists[static_cast<int>(TileList::AnimationTileList)].push_back(_Name.data());
	}
	void AddBackGroundList(std::string_view _Name)
	{
		TileLists[static_cast<int>(TileList::BackGroundList)].push_back(_Name.data());
	}
	void AddPlatformList(std::string_view _Name)
	{
		EntityLists[static_cast<int>(EntityList::Platforms)].push_back(_Name.data());
	}
	void AddInterObjectList(std::string_view _Name)
	{
		EntityLists[static_cast<int>(EntityList::InterObjects)].push_back(_Name.data());
	}
	void AddEnermyList(std::string_view _Name)
	{
		EntityLists[static_cast<int>(EntityList::Enemies)].push_back(_Name.data());
	}

	void EditorKeyCheck();
	void DebugText();

public:
	AGameWorld* GetGameWorld()
	{
		return GameWorld;
	}

};


TileList& operator++(TileList& _List);
TileList& operator--(TileList& _List);
EntityList& operator++(EntityList& _List);
EntityList& operator--(EntityList& _List);