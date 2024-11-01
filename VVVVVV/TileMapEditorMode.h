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
	std::vector<std::vector<bool>> CheckTiles = {};
	USpriteRenderer* CursorImage = nullptr;
	POINT CursorPos = {};

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	int AroundTileCheckSwap(int _X, int _Y);
	int FindIndex(uint8_t _Bit);
	bool IsTile(int x, int y);

};

enum class TILE_TYPE
{
	CLOSE_TOP_LEFT,
	CLOSE_TOP,
	CLOSE_TOP_RIGHT,
	OPEN_BOTTOM,
	DIAGONAL_RIGHT_BOTTOM,
	DIAGONAL_LEFT_BOTTOM,
	CLOSE_LEFT,
	OPEN,
	CLOSE_RIGHT,
	CLOSE_LEFT_RIGHT,
	DIAGONAL_RIGHT_TOP,
	DIAGONAL_LEFT_TOP,
	CLOSE_LEFT_BOTTOM,
	CLOSE_BOTTOM,
	CLOSE_RIGHT_BOTTOM,
	OPEN_TOP,
	POINT_RIGHT_BOTTOM,
	POINT_LEFT_BOTTOM,
	OPEN_RIGHT,
	CLOSE_TOP_BOTTOM,
	OPEN_LEFT,
	CLOSE,
	POINT_RIGHT_TOP,
	POINT_LEFT_TOP,
};
