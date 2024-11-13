#pragma once
#include <EngineCore/EngineAPICore.h>

// Ό³Έν :
class V6ContentsCore : public UContentsCore
{
public:
	V6ContentsCore();
	~V6ContentsCore();

	V6ContentsCore(const V6ContentsCore& _Other) = delete;
	V6ContentsCore(V6ContentsCore&& _Other) noexcept = delete;
	V6ContentsCore& operator=(const V6ContentsCore& _Other) = delete;
	V6ContentsCore& operator=(V6ContentsCore&& _Other) noexcept = delete;

private:
	ULevel* TitleLevel = nullptr;

public:

private:
	void BeginPlay() override;
	void Tick() override;

	void ResourceLoad();

	void SpriteLoad();

	void TileImageLoad();
	void BackGroundImageLoad();
	void PlayerImageLoad();
	void FontImageLoad();

	void BackGroundObjectImageLoad();

	void FlatformImageLoad();
	void InterObjectImageLoad();
	void EnermyImageLoad();

};

