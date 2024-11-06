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
	std::vector<std::string> BackGroundTileList = {};
	std::vector<std::string> TileList = {};
	std::vector<std::string> SpikeTileList = {};
	std::vector<std::string> BackGroundList = {};
	std::vector<std::string>* CurSelectTileList = &TileList;
	int CurTileSetIndex = 0;
	int CurBackGroundIndex = 0;
	AWorld* World = nullptr;
	USpriteRenderer* CurSelectSprite = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	void PrevBackGroundImage();
	void NextBackGroundImage();

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
	void NextTileList();
	void PrevTileSet();
	void NextTileSet();
	void PrevTile();
	void NextTile();
	void ShowTiles();
	void ShowBackGroundTiles();

public:
	void SetCurSelectSprite(std::string_view _Name, int _Index)
	{
		CurSelectSprite->SetSprite(_Name, _Index);
	}
	
};
