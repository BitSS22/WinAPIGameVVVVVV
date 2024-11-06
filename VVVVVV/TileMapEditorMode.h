#pragma once
#include <EngineCore/SpriteRenderer.h>
#include "TileMap.h"

// Ό³Έν :
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
	FIntPoint WorldIndexSize = { 5, 5 };
	FIntPoint CurSelectTileMap = { 0, 0 };
	ATileMap* TileMap = nullptr;
	std::vector<USpriteRenderer*> Sprites = {};
	USpriteRenderer* CurSelectSprite = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	int AroundTileChange(int _X, int _Y);
	int FindAroundTile(uint8_t _Bit) const;
	bool IsSameTileName(int x, int y) const;

};
