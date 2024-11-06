#pragma once
#include <EngineCore/SpriteRenderer.h>
#include "BackGround.h"
#include "Room.h"
#include "World.h"

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
	std::vector<std::string> TileList = {};
	std::vector<std::string> BackGroundTileList = {};
	std::vector<std::string> SpikeTileList = {};
	std::vector<std::string> BackGroundList = {};
	std::vector<std::string>* CurSelectTileSet = &TileList;
	AWorld* World = nullptr;
	USpriteRenderer* CurSelectSprite = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	void AddTileList(std::string_view _Name)
	{
		TileList.push_back(_Name.data());
	}
	void AddBackGroundTileList(std::string_view _Name)
	{
		BackGroundTileList.push_back(_Name.data());
	}
	void AddSpikeTileList(std::string_view _Name)
	{
		SpikeTileList.push_back(_Name.data());
	}
	void AddBackGroundList(std::string_view _Name)
	{
		BackGroundList.push_back(_Name.data());
	}

private:
	int AroundTileChange(int _X, int _Y);
	int FindAroundTile(uint8_t _Bit) const;
	bool IsSameTileName(int x, int y) const;
	void NextTileSet();
	void ShowTiles()
	{
		auto& room = World->GetRoom()->Tiles;
		for (size_t y = 0; y < room.size(); ++y)
		{
			for (size_t x = 0; x < room[y].size(); ++x)
			{
				room[y][x]->SetActive(!room[y][x]->IsActive());
			}
		}
	}
	void ShowBackGroundTiles()
	{
		auto& room = World->GetRoom()->BackGroundTiles;
		for (size_t y = 0; y < room.size(); ++y)
		{
			for (size_t x = 0; x < room[y].size(); ++x)
			{
				room[y][x]->SetActive(!room[y][x]->IsActive());
			}
		}
	}

public:
	void SetCurSelectSprite(std::string_view _Name, int _Index)
	{
		CurSelectSprite->SetSprite(_Name, _Index);
	}
	void SetBackGroundImage(std::string_view _Name, int _Index)
	{
		World->GetRoom()->BackGround->SetBackGround(_Name, _Index);
	}
};
