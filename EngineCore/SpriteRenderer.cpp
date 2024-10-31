#include "pch.h"
#include "SpriteRenderer.h"
#include <EngineCore/ImageManager.h>

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

void USpriteRenderer::Render()
{
	if (Sprite == nullptr)
		MSGASSERT(nullptr, "Sprite가 없어 렌더링 할 수 없습니다.");

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWindowImage* BackBufferImage = MainWindow.GetBackBufferImage();

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image->CopyToTrans(BackBufferImage, GetActorTransform(), CurData.Transform);
}

void USpriteRenderer::BeginPlay()
{
	Super::BeginPlay();

	GetActor()->GetWorld()->PushRenderer(this);
}

void USpriteRenderer::ComponentTick()
{
	Super::ComponentTick();
}


void USpriteRenderer::SetSprite(std::string_view _Name, int _CurIndex)
{
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (Sprite == nullptr)
		MSGASSERT(nullptr, _Name, "은 로드 되지 않은 Image입니다.");

	CurIndex = _CurIndex;
}

void USpriteRenderer::SetSpriteScale(float _Ratio, int _CurIndex)
{
	if (Sprite == nullptr)
		MSGASSERT(nullptr, "Sprite가 nullptr입니다.");

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	FVector2D Scale = CurData.Transform.Scale * _Ratio;
	SetComponentScale(Scale);
}

void USpriteRenderer::SetOrder(int _Order)
{
	int PrevOrder = Order;
	Order = _Order;

	ULevel* Level = GetActor()->GetWorld();

	if (Level != nullptr)
		Level->ChangeRenderOrder(this, PrevOrder);
}
