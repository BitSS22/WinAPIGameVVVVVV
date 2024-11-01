#pragma once

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
	static const int TileCountX = 40;
	static const int TileCountY = 30;
	static const int TileSizeX = 16;
	static const int TileSizeY = 16;
	std::vector<std::vector<USpriteRenderer*>> Tiles = {};
	USpriteRenderer* CurSelectSprite = nullptr;
	POINT CursorPos = {};

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	int AroundTileChange(int _X, int _Y);
	int FindIndex(uint8_t _Bit);
	bool IsTile(int x, int y);

};
