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
	Super::BeginPlay();

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("BackGrounds::00 Space", 0);
	Sprite->SetSpriteScale(1.f, Sprite->GetCurIndex());
	Sprite->SetOrder(ERenderOrder::BACKGROUND);
	Sprite->SetComponentLocation(WindowSize.Half());


	// Create Star Effect
	for (size_t i = 0; i < 6; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Effects:: Stars", 0);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-440.f, -360.f);
		StarEffects.push_back(StarEffect(StarSprite, RandNumber, FVector2D::RIGHT));
	}
	for (size_t i = 0; i < 10; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Effects:: Stars", 1);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-520.f, -400.f);
		StarEffects.push_back(StarEffect(StarSprite, RandNumber, FVector2D::RIGHT));
	}
	for (size_t i = 0; i < 20; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Effects:: Stars", 2);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-600.f, -440.f);
		StarEffects.push_back(StarEffect(StarSprite, RandNumber, FVector2D::RIGHT));
	}

	for (size_t i = 0; i < 12; ++i)
	{
		USpriteRenderer* RectSprite = CreateDefaultSubObject<USpriteRenderer>();
		RectSprite->SetSprite("Effects:: Rect Horizontal", i % 6);
		RectSprite->SetSpriteScale(1.f, RectSprite->GetCurIndex());
		RectSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		RectSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-440.f, -360.f);
		RectEffects[static_cast<int>(RectDir::Horizontal)].push_back(RectEffect(RectSprite, RandNumber, FVector2D::RIGHT));
	}
	for (size_t i = 0; i < 12; ++i)
	{
		USpriteRenderer* RectSprite = CreateDefaultSubObject<USpriteRenderer>();
		RectSprite->SetSprite("Effects:: Rect Vertical", i % 6);
		RectSprite->SetSpriteScale(1.f, RectSprite->GetCurIndex());
		RectSprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
		RectSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		float RandNumber = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(-440.f, -360.f);
		RectEffects[static_cast<int>(RectDir::Vertical)].push_back(RectEffect(RectSprite, RandNumber, FVector2D::UP));
	}

	SetEffect(EEffectType::Star);

	FileLoadInit();
}

void ABackGround::Tick()
{
	Super::Tick();

	if (CurAnimation != nullptr)
		CurAnimation();

	if (CurEffect != nullptr)
		CurEffect();
}

void ABackGround::PlayHorizontalAnimation()
{
	Sprite->AddComponentLocation(FVector2D::LEFT * AnimationSpeed * GET_DELTA);
	if (Sprite->GetComponentLocation().X < UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X - 16.f)
		Sprite->AddComponentLocation(FVector2D(32.f, 0.f));
}

void ABackGround::PlayVerticalAnimation()
{
	Sprite->AddComponentLocation(FVector2D::UP * AnimationSpeed * GET_DELTA);
	if (Sprite->GetComponentLocation().Y < UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y - 16.f)
		Sprite->AddComponentLocation(FVector2D(0.f, 32.f));
}

void ABackGround::PlayTowerAnimation()
{
	Sprite->AddComponentLocation(FVector2D::UP * AnimationSpeed * 0.25f * GET_DELTA);
	if (Sprite->GetComponentLocation().Y < UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y - 960.f)
		Sprite->AddComponentLocation(FVector2D(0.f, 1920.f));
}

void ABackGround::PlayStarEffect()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	for (size_t i = 0; i < StarEffects.size(); ++i)
	{
		StarEffects[i].Sprite->AddComponentLocation(StarEffects[i].Dir * StarEffects[i].Speed * GET_DELTA);
		FVector2D Pos = StarEffects[i].Sprite->GetComponentLocation();

		if (Pos.X < 0)
		{
			Pos.X += WindowSize.X;
			Pos.Y = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y);
			StarEffects[i].Sprite->SetComponentLocation(Pos);
		}
	}
}

void ABackGround::PlayRectEffect()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	for (size_t i = 0; i < RectEffects[static_cast<int>(RectDir::Horizontal)].size(); ++i)
	{
		RectEffects[static_cast<int>(RectDir::Horizontal)][i].Sprite->AddComponentLocation(RectEffects[static_cast<int>(RectDir::Horizontal)][i].Dir * RectEffects[static_cast<int>(RectDir::Horizontal)][i].Speed * GET_DELTA);
		FVector2D Pos = RectEffects[static_cast<int>(RectDir::Horizontal)][i].Sprite->GetComponentLocation();

		if (Pos.X < 0 || Pos.X > WindowSize.X)
		{
			Pos.Y = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y);
			if (UEngineAPICore::GetCore()->GetRandomDevice().GetRandomInt(0, 1) == 0)
			{
				RectEffects[static_cast<int>(RectDir::Horizontal)][i].Dir = FVector2D::RIGHT;
				Pos.X = WindowSize.X;
			}
			else
			{
				RectEffects[static_cast<int>(RectDir::Horizontal)][i].Dir = FVector2D::LEFT;
				Pos.X = 0.f;
			}
			RectEffects[static_cast<int>(RectDir::Horizontal)][i].Sprite->SetComponentLocation(Pos);
		}
	}

	for (size_t i = 0; i < RectEffects[static_cast<int>(RectDir::Vertical)].size(); ++i)
	{
		RectEffects[static_cast<int>(RectDir::Vertical)][i].Sprite->AddComponentLocation(RectEffects[static_cast<int>(RectDir::Vertical)][i].Dir * RectEffects[static_cast<int>(RectDir::Vertical)][i].Speed * GET_DELTA);
		FVector2D Pos = RectEffects[static_cast<int>(RectDir::Vertical)][i].Sprite->GetComponentLocation();

		if (Pos.Y < 0 || Pos.Y > WindowSize.Y)
		{
			Pos.X = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X);
			if (UEngineAPICore::GetCore()->GetRandomDevice().GetRandomInt(0, 1) == 0)
			{
				RectEffects[static_cast<int>(RectDir::Vertical)][i].Dir = FVector2D::DOWN;
				Pos.Y = WindowSize.Y;
			}
			else
			{
				RectEffects[static_cast<int>(RectDir::Vertical)][i].Dir = FVector2D::UP;
				Pos.Y = 0.f;
			}
			RectEffects[static_cast<int>(RectDir::Vertical)][i].Sprite->SetComponentLocation(Pos);
		}
	}

}

void ABackGround::SetEffect(EEffectType _Type)
{
	switch (_Type)
	{
	case EEffectType::Star:
		for (size_t i = 0; i < StarEffects.size(); ++i)
			StarEffects[i].Sprite->SetActive(true);
		for (int z = 0; z < static_cast<int>(RectDir::None); ++z)
			for (size_t i = 0; i < RectEffects[z].size(); ++i)
				RectEffects[z][i].Sprite->SetActive(false);
		CurEffect = bind(&ABackGround::PlayStarEffect, this);
		return;
	case EEffectType::Rect:
		for (size_t i = 0; i < StarEffects.size(); ++i)
			StarEffects[i].Sprite->SetActive(false);
		for (int z = 0; z < static_cast<int>(RectDir::None); ++z)
			for (size_t i = 0; i < RectEffects[z].size(); ++i)
				RectEffects[z][i].Sprite->SetActive(true);
		CurEffect = bind(&ABackGround::PlayRectEffect, this);
		return;
	case EEffectType::None:
		for (size_t i = 0; i < StarEffects.size(); ++i)
			StarEffects[i].Sprite->SetActive(false);
		for (int z = 0; z < static_cast<int>(RectDir::None); ++z)
			for (size_t i = 0; i < RectEffects[z].size(); ++i)
				RectEffects[z][i].Sprite->SetActive(false);
		CurEffect = nullptr;
		return;
	}

	MSGASSERT(nullptr, "Unknown BackGround Effect Type.");
}

void ABackGround::SetBackGround(const RoomBackGroundData& _Data)
{
	EBackGroundType PrevType = BackGroundType;

	AnimationSpeed = _Data.AnimationSpeed;
	BackGroundType = _Data.BackGroundType;

	Sprite->SetSprite(_Data.Name, _Data.Index);
	UEngineSprite* SpriteImage = UImageManager::GetInst().FindSprite(_Data.Name);
	Sprite->SetComponentScale(SpriteImage->GetSpriteData(_Data.Index).Transform.Scale);

	if (PrevType != BackGroundType)
	{
		Sprite->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());

		switch (BackGroundType)
		{
		case EBackGroundType::Space:
			CurAnimation = nullptr;
			SetEffect(EEffectType::Star);
			return;
		case EBackGroundType::Horizontal:
			CurAnimation = bind(&ABackGround::PlayHorizontalAnimation, this);
			SetEffect(EEffectType::None);
			return;
		case EBackGroundType::Vertical:
			CurAnimation = bind(&ABackGround::PlayVerticalAnimation, this);
			SetEffect(EEffectType::None);
			return;
		case EBackGroundType::Tower:
			CurAnimation = bind(&ABackGround::PlayTowerAnimation, this);
			SetEffect(EEffectType::None);
			return;
		case EBackGroundType::Ending:
			CurAnimation = nullptr;
			SetEffect(EEffectType::None);
			return;
		case EBackGroundType::Maze:
			CurAnimation = nullptr;
			SetEffect(EEffectType::Rect);
			return;
		}

		MSGASSERT(nullptr, "Unknown BackGround Type.");
	}
}

RoomBackGroundData ABackGround::GetBackGroundData()
{
	RoomBackGroundData Data = {};

	Data.Name = Sprite->GetCurSpriteName();
	Data.Index = Sprite->GetCurIndex();
	Data.BackGroundType = BackGroundType;
	Data.AnimationSpeed = AnimationSpeed;

	return Data;
}

void ABackGround::FileLoadInit()
{
	FIntPoint CurRoomIndex = AGameWorld::GetCurRoomIndex();
	SetBackGround(AGameWorld::GetRoomDatasRef(CurRoomIndex).BackGroundData);
}

void ABackGround::AddBackGroundColor(int _AddValue)
{
	int CurIndex = Sprite->GetCurIndex();
	int MaxIndex = Sprite->GetMaxIndex();

	CurIndex += _AddValue;

	Sprite->SetSprite(Sprite->GetCurSpriteName(), CurIndex % MaxIndex);
}
