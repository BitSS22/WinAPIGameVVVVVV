#include "pch.h"
#include "BackGround.h"
#include "Room.h"

ABackGround::ABackGround()
{
}

ABackGround::~ABackGround()
{
}

void ABackGround::BeginPlay()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	for (size_t i = 0; i < 6; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Stars", 0);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		StarSprite->SetActive(false);
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-440.f, -360.f);
		Effects.push_back(Effect(StarSprite, EEffectType::Star ,RandNumber, FVector2D::RIGHT));
	}
	for (size_t i = 0; i < 10; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Stars", 1);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		StarSprite->SetActive(false);
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-520.f, -400.f);
		Effects.push_back(Effect(StarSprite, EEffectType::Star, RandNumber, FVector2D::RIGHT));
	}
	for (size_t i = 0; i < 20; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Stars", 2);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		StarSprite->SetActive(false);
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-600.f, -440.f);
		Effects.push_back(Effect(StarSprite, EEffectType::Star, RandNumber, FVector2D::RIGHT));
	}

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	FIntPoint CurRoomIndex = Room->GameWorld->CurRoomIndex;
	if (Room->GameWorld->RoomDatas[CurRoomIndex.Y][CurRoomIndex.X].RoomBackGroundData != "Debug BackGround.png")
		SetBackGround(Room->GameWorld->RoomDatas[CurRoomIndex.Y][CurRoomIndex.X].RoomBackGroundData);
	else
		SetBackGround("Debug BackGround.png");
	Sprite->SetSpriteScale(1.f, Sprite->GetCurIndex());
	Sprite->SetOrder(ERenderOrder::BACKGROUND);
	Sprite->SetComponentLocation(WindowSize.Half());

}

void ABackGround::Tick()
{
	// Space Star Effect
	if (EffectValue == true)
	{
		FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

		for (size_t i = 0; i < Effects.size(); ++i)
		{
			Effects[i].Sprite->AddComponentLocation(FVector2D(Effects[i].Speed * GET_DELTA, 0.f));
			FVector2D Pos = Effects[i].Sprite->GetComponentLocation();

			if (Pos.X < 0)
			{
				Pos.X += WindowSize.X;
				Pos.Y = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y);
				Effects[i].Sprite->SetComponentLocation(Pos);
			}
		}
	}

	switch (CurBackGroundType)
	{
	case EBackGroundType::Horizontal:
		Sprite->AddComponentLocation(FVector2D(-AnimationSpeed * GET_DELTA, 0.f));
		if (Sprite->GetComponentLocation().X < UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X - 16.f)
			Sprite->AddComponentLocation(FVector2D(32.f, 0.f));
		break;
	case EBackGroundType::Vertical:
		Sprite->AddComponentLocation(FVector2D(0.f, -AnimationSpeed * GET_DELTA));
		if (Sprite->GetComponentLocation().Y < UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y - 16.f)
			Sprite->AddComponentLocation(FVector2D(0.f, 32.f));
		break;
	case EBackGroundType::Tower:
		break;
	}
}

void ABackGround::SetBackGround(std::string_view _Name)
{
	Sprite->SetSprite(_Name, 0);
	UEngineSprite* SpriteImage = UImageManager::GetInst().FindSprite(_Name);
	Sprite->SetComponentScale(SpriteImage->GetSpriteData(0).Transform.Scale);

	EBackGroundType PrevType = CurBackGroundType;

	if (_Name.find("SPACE") != std::string::npos)
		CurBackGroundType = EBackGroundType::SPACE;
	else if (_Name.find("HORIZONTAL") != std::string::npos)
		CurBackGroundType = EBackGroundType::HORIZONTAL;
	else if (_Name.find("VERTICAL") != std::string::npos)
		CurBackGroundType = EBackGroundType::VERTICAL;
	else if (_Name.find("TOWER") != std::string::npos)
		CurBackGroundType = EBackGroundType::TOWER;
	else if (_Name.find("ENDING") != std::string::npos)
		CurBackGroundType = EBackGroundType::ENDING;
	else
		CurBackGroundType = EBackGroundType::DEBUG;

	if (CurBackGroundType == EBackGroundType::SPACE)
		SetEffect(true);
	else
		SetEffect(false);

	if (PrevType != CurBackGroundType)
		Sprite->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
}

