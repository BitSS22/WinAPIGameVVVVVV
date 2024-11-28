#include "pch.h"
#include "GameConst.h"

const FIntPoint EGameConst::WorldMaxIndex = { 10, 10 };
const FVector2D EGameConst::TileScale = { 16, 16 };
const FIntPoint EGameConst::TileCount = { 40, 30 };

const FIntPoint EGameConst::DefualtSaveRoomIndex = { 0, 0 };
const FVector2D EGameConst::DefualtSaveLocation = { 120.f, 384.f };

const FIntPoint EGameConst::ClearRoom = { 9, 9 };

const float EGameConst::AnimationTime = 0.15f;
const float EGameConst::DefualtSpeed = 0.f;
const float EGameConst::DefualtMoveLen = 0.f;
const float EGameConst::RailSpeed = 300.f;
const float EGameConst::HideTime = 0.3f;
const float EGameConst::BGMFadeTimeScale = 0.33f;