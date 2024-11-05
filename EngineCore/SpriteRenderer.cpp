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
	if (CurAnimation != nullptr)
	{
		vector<int>& Indexs = CurAnimation->FrameIndex;
		vector<float>& Times = CurAnimation->FrameTime;

		Sprite = CurAnimation->Sprite;

		CurAnimation->CurTime += UEngineTimer::GetInst()->GetDeltaTime();

		float CurFrameTime = Times[CurAnimation->CurIndex];

		if (CurAnimation->CurTime > CurFrameTime)
		{
			CurAnimation->CurTime -= CurFrameTime;
			++CurAnimation->CurIndex;

			if (CurAnimation->Events.contains(CurAnimation->CurIndex))
				CurAnimation->Events[CurAnimation->CurIndex]();

			if (CurAnimation->CurIndex >= Indexs.size())
			{
				if (CurAnimation->Loop == true)
				{
					CurAnimation->CurIndex = 0;
					if (CurAnimation->Events.contains(CurAnimation->CurIndex))
						CurAnimation->Events[CurAnimation->CurIndex]();
				}
				else
					--CurAnimation->CurIndex;
			}
		}

		CurIndex = Indexs[CurAnimation->CurIndex];
	}


	if (Sprite == nullptr)
		MSGASSERT(nullptr, "Sprite�� ���� ������ �� �� �����ϴ�.");

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWindowImage* BackBufferImage = MainWindow.GetBackBufferImage();

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	FTransform Trans = FTransform(GetComponentLocation(), GetComponentScale());
	ULevel* Level = GetActor()->GetWorld();
	
	if (IsCameraEffect == true)
		Trans.Location = Trans.Location - Level->CameraPos * CameraEffectScale;

	CurData.Image->CopyToTrans(BackBufferImage, Trans, CurData.Transform);
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
		MSGASSERT(nullptr, _Name, "�� �ε� ���� ���� Image�Դϴ�.");

	CurIndex = _CurIndex;
}

void USpriteRenderer::SetSpriteScale(float _Ratio, int _CurIndex)
{
	if (Sprite == nullptr)
		MSGASSERT(nullptr, "Sprite�� nullptr�Դϴ�.");

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(_CurIndex);
	FVector2D Scale = CurData.Transform.Scale * _Ratio;
	SetComponentScale(Scale);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop)
{
	string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_Frame.size() != _Indexs.size())
		MSGASSERT(nullptr, _AnimationName, "�� Frame�� Time ������ �����մϴ�.");

	if (FrameAnimations.contains(UpperName))
		return;

	UEngineSprite* FindSprite = UImageManager::GetInst().FindSprite(_SpriteName);

	if (FindSprite == nullptr)
		MSGASSERT(nullptr, _SpriteName, "�� �ε� ���� ���� Sprite�Դϴ�.");

	FrameAnimation NewAnimation = {};
	NewAnimation.Sprite = FindSprite;
	NewAnimation.FrameIndex = std::move(_Indexs);
	NewAnimation.FrameTime = std::move(_Frame);
	NewAnimation.Loop = _Loop;
	NewAnimation.Reset();

	FrameAnimations.insert(make_pair(UpperName, NewAnimation));
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float _Time, bool _Loop)
{
	if (_Start > _End)
		MSGASSERT(nullptr, _AnimationName, ", ������ Start���� End�� Ů�ϴ�.");

	vector<int> Indexs = {};
	vector<float> Times(_End - _Start, _Time);

	for (size_t i = _Start; i <= _End; ++i)
	{
		Indexs.push_back(_Start);
		++_Start;
	}

	CreateAnimation(_AnimationName, _SpriteName, Indexs, Times, _Loop);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _FrameTime, bool _Loop)
{
	CreateAnimation(_AnimationName, _SpriteName, _Indexs, vector<float>(_Indexs.size(), _FrameTime), _Loop);
}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force)
{
	string UpperName = UEngineString::ToUpper(_AnimationName);

	if (FrameAnimations.contains(UpperName) == false)
		MSGASSERT(nullptr, _AnimationName, "�̶�� Animation�� �����ϴ�.");

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && _Force == false)
		return;

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
		CurAnimation->Events[CurAnimation->CurIndex]();

	Sprite = CurAnimation->Sprite;
}

void USpriteRenderer::SetAnimationEvent(std::string_view _AnimationName, int _AnimationFrame, std::function<void()> _Function)
{
	string UpperName = UEngineString::ToUpper(_AnimationName);

	if (FrameAnimations.contains(UpperName) == false)
		MSGASSERT(nullptr, _AnimationName, "�� ���� Animation�Դϴ�.");

	if (FrameAnimations[UpperName].FrameIndex.size() <= _AnimationFrame)
		MSGASSERT(nullptr, _AnimationName, "�� ���� Animation Frame�Դϴ�.");

	FrameAnimations[UpperName].Events[_AnimationFrame] += _Function;
}

void USpriteRenderer::SetOrder(int _Order)
{
	int PrevOrder = Order;
	Order = _Order;

	ULevel* Level = GetActor()->GetWorld();

	if (Level != nullptr)
		Level->ChangeRenderOrder(this, PrevOrder);
}
