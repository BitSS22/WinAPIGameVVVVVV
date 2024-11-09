#include "pch.h"
#include "AnimationManager.h"

AAnimationManager* AAnimationManager::Inst = nullptr;

AAnimationManager::AAnimationManager()
{
	Inst = this;
}

AAnimationManager::~AAnimationManager()
{
}

void AAnimationManager::BeginPlay()
{
	CreateAnimation("AnimationTiles::01 Animation Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("AnimationTiles::02 Animation Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("AnimationTiles::03 Animation Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("AnimationTiles::04 Animation Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("AnimationTiles::05 Animation Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("AnimationTiles::06 Animation Green", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, EGameConst::AnimationTime, true);

	CreateAnimation("RailTiles::01 Rail Left Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::02 Rail Left Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::03 Rail Left Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::04 Rail Left Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::05 Rail Left Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::06 Rail Left Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::07 Rail Left Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);

	CreateAnimation("RailTiles::08 Rail Right Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::09 Rail Right Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::10 Rail Right Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::11 Rail Right Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::12 Rail Right Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::13 Rail Right Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	CreateAnimation("RailTiles::14 Rail Right Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
}

void AAnimationManager::CreateAnimation(string_view _SpriteName, vector<int> _indexs, float frames, bool _Loop)
{
	string UpperName = UEngineString::ToUpper(_SpriteName);
	USpriteRenderer* NewAnimation = CreateDefaultSubObject<USpriteRenderer>();
	NewAnimation->SetSprite(UpperName, 0);
	NewAnimation->CreateAnimation(UpperName, UpperName, _indexs, frames, _Loop);
	NewAnimation->SetActive(false);
	NewAnimation->ChangeAnimation(UpperName, false);
	Animations.insert(make_pair(UpperName, NewAnimation));
}

USpriteRenderer* AAnimationManager::GetTileAnimation(std::string_view _AnimationName)
{
	string UpperName = UEngineString::ToUpper(_AnimationName);
	if (Animations.contains(UpperName) == false)
		MSGASSERT(nullptr, _AnimationName, "은 존재하지 않습니다.");
	return Animations[UpperName];
}