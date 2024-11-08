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
	RailTileList,
	BackGroundList,
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
	TileList CurSelectTileList = TileList::TileList;
	int CurTileSetIndex = 0;
	int CurBackGroundIndex = 0;
	AWorld* World = nullptr;
	USpriteRenderer* CurSelectSprite = nullptr;

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
		case TileList::RailTileList: 
			return World->GetRoom()->Tiles;
			break;
		default:
			MSGASSERT(nullptr, "타일 리스트가 제대로 선택되지 않았습니다.");
			break;
		}
		return World->GetRoom()->Tiles;
	}

	void ChangeTile(bool _AroundTileChange);
	void DeleteTile(bool _AroundTileChange);
	void NextTileList();
	void PrevTileList();
	void PrevTileSet();
	void NextTileSet();
	void PrevTile();
	void NextTile();

	void ShowTiles();
	void ShowBackGroundTiles();

	void PickUpTile();
	void DrawingRect();

	void MoveRoom(FIntPoint _Index);

	void SaveRoomData();
	void LoadRoomData(FIntPoint _Index);

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
	void AddRailTileList(std::string_view _Name)
	{
		TileLists[static_cast<int>(TileList::RailTileList)].push_back(_Name.data());
	}
	void AddBackGroundList(std::string_view _Name)
	{
		TileLists[static_cast<int>(TileList::BackGroundList)].push_back(_Name.data());
	}

	void PrevBackGroundImage();
	void NextBackGroundImage();

public:

};


TileList& operator++(TileList& _List);
TileList& operator--(TileList& _List);