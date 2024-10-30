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
		MSGASSERT(nullptr, "Sprite�� ���� ������ �� �� �����ϴ�.");

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWindowImage* BackBufferImage = MainWindow.GetBackBufferImage();

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image->CopyToTrans(BackBufferImage, Transfrom, CurData.Transform);
}

