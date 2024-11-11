#pragma once
#include <EngineCore/SpriteRenderer.h>
#include "BackGround.h"
#include "Room.h"
#include "World.h"

enum class TileList
{
	BackGroundTileList,
	TileList,
	SpikeTileList,
	AnimationTileList,
	BackGroundList,
	LAST
};
enum class ObjectList
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
	std::vector<std::string> ObjectLists[static_cast<int>(ObjectList::LAST)] = {};
	TileList CurSelectTileList = TileList::TileList;
	ObjectList CurSelectObjectList = ObjectList::Enemies;
	int CurTileSetIndex = 0;
	int CurObjectIndex = 0;
	int CurBackGroundIndex = 0;
	AWorld* World = nullptr;
	USpriteRenderer* CurSelectSprite = nullptr;
	AActor* CurSelectObject = nullptr;

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
			return World->GetRoom()->BackGroundTiles;
			break;
		case TileList::TileList:
		case TileList::SpikeTileList:
		case TileList::AnimationTileList:
			return World->GetRoom()->Tiles;
			break;
		default:
			MSGASSERT(nullptr, "타일 리스트가 제대로 선택되지 않았습니다.");
			break;
		}
		return World->GetRoom()->Tiles;
	}

	void ChangeTile(bool _AroundTileChange, FIntPoint _Index);
	void DeleteTile(bool _AroundTileChange, FIntPoint _Index);

	void NextTileList();
	void PrevTileList();
	void PrevTileSet();
	void NextTileSet();
	void PrevTile();
	void NextTile();
	void PrevBackGroundImage();
	void NextBackGroundImage();

	void ShowTiles();
	void ShowBackGroundTiles();

	void PickUpTile();

	void MoveRoom(FIntPoint _Index);

	void SaveRoomData();
	void LoadRoomData(FIntPoint _Index);


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
		ObjectLists[static_cast<int>(ObjectList::Platforms)].push_back(_Name.data());
	}
	void AddInterObjectList(std::string_view _Name)
	{
		ObjectLists[static_cast<int>(ObjectList::InterObjects)].push_back(_Name.data());
	}
	void AddEnermyList(std::string_view _Name)
	{
		ObjectLists[static_cast<int>(ObjectList::Enemies)].push_back(_Name.data());
	}


	void DebugText();

public:

};


TileList& operator++(TileList& _List);
TileList& operator--(TileList& _List);
ObjectList& operator++(ObjectList& _List);
ObjectList& operator--(ObjectList& _List);