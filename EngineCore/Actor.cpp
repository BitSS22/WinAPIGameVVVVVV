#include "pch.h"
#include "Actor.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Render() const
{
	if (Sprite == nullptr)
		MSGASSERT(nullptr, "Sprite가 없어 렌더링 할 수 없습니다.");

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWindowImage* BackBufferImage = MainWindow.GetBackBufferImage();

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image->CopyToTrans(BackBufferImage, Transfrom, CurData.Transform);
}

