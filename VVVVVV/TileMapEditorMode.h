#pragma once

// ���� :
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
	void AroundTileCheckSwap(int _X, int _Y, int _CA, int _CB);
	bool IsTile(int x, int y);

};

