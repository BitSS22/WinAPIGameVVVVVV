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
	
	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	FTransform Trans = GetComponentOffsetTransform();
	ULevel* Level = GetActor()->GetWorld();
	
	if (IsCameraEffect == true)
		Trans.Location = Trans.Location - Level->CameraPos * CameraEffectScale;

	FVector2D PivotRealScale = {};

	PivotRealScale.X = std::floorf((0.5f - Pivot.X) * Trans.Scale.X);
	PivotRealScale.Y = std::floorf((0.5f - Pivot.Y) * Trans.Scale.Y);

	Trans.Location += PivotRealScale;

	if (Alpha == 255)
		CurData.Image->CopyToTrans(UEngineAPICore::GetCore()->GetMainWindow().GetBackBufferImage(), Trans, CurData.Transform);
	else
		CurData.Image->CopyToAlpha(UEngineAPICore::GetCore()->GetMainWindow().GetBackBufferImage(), Trans, CurData.Transform, Alpha);
}

void USpriteRenderer::BeginPlay()
{
	Super::BeginPlay();

	GetActor()->GetWorld()->ChangeRenderOrder(this, GetOrder());
}

void USpriteRenderer::ComponentTick()
{
	Super::ComponentTick();

	if (CurAnimation != nullptr)
	{
		CurAnimation->IsEnd = false;
		vector<int>& Indexs = CurAnimation->FrameIndex;
		vector<float>& Times = CurAnimation->FrameTime;

		Sprite = CurAnimation->Sprite;

		CurAnimation->CurTime += UEngineTimer::GetInst()->GetDeltaTime() * CurAnimationSpeed;

		float CurFrameTime = Times[CurAnimation->CurIndex];

		if (CurAnimation->CurTime > CurFrameTime)
		{
			CurAnimation->CurTime -= CurFrameTime;
			++CurAnimation->CurIndex;

			if (CurAnimation->Events.contains(CurIndex))
				CurAnimation->Events[CurIndex]();

			if (CurAnimation->CurIndex >= Indexs.size())
				CurAnimation->IsEnd = true;
			else
				CurAnimation->IsEnd = false;

			if (CurAnimation->CurIndex >= Indexs.size())
			{
				if (CurAnimation->Loop == true)
				{
					CurAnimation->CurIndex = 0;
					if (CurAnimation->Events.contains(CurIndex))
						CurAnimation->Events[CurIndex]();
				}
				else
				{
					CurAnimation->IsEnd = true;
					--CurAnimation->CurIndex;
				}
			}
		}

		CurIndex = Indexs[CurAnimation->CurIndex];
	}
}

void USpriteRenderer::SetCameraEffectScale(float _Effect)
{
	CameraEffectScale = _Effect;
}

void USpriteRenderer::SetSprite(std::string_view _Name, int _Index)
{
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (Sprite == nullptr)
		MSGASSERT(nullptr, _Name, "은 로드 되지 않은 Image입니다.");
	ChangeAnimation(_Name);

	CurIndex = _Index;
}

void USpriteRenderer::SetSpriteScale(float _Ratio, int _CurIndex)
{
	if (Sprite == nullptr)
		MSGASSERT(nullptr, "Sprite가 nullptr입니다.");

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(_CurIndex);
	FVector2D Scale = CurData.Transform.Scale * _Ratio;
	SetComponentScale(Scale);
}

void USpriteRenderer::SetPivotValue(FVector2D _Pivot)
{
	Pivot = _Pivot;
}

void USpriteRenderer::SetPivotType(PivotType _Type)
{
	if (PivotType::Center == _Type)
	{
		Pivot = FVector2D::ZERO;
		return;
	}

	if (Sprite == nullptr)
		MSGASSERT(nullptr, "Image가 없어 Pivot 설정이 불가능합니다.");

	switch (_Type)
	{
	case PivotType::Center:
		Pivot.X = 0.5f;
		Pivot.Y = 0.5f;
		break;
	case PivotType::Left:
		Pivot.X = 0.f;
		Pivot.Y = 0.5f;
		break;
	case PivotType::LeftTop:
		Pivot.X = 0.f;
		Pivot.Y = 0.f;
		break;
	case PivotType::Top:
		Pivot.X = 0.5f;
		Pivot.Y = 0.f;
		break;
	case PivotType::Botttom:
		Pivot.X = 0.5f;
		Pivot.Y = 1.f;
		break;
	default:
		break;
	}
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop)
{
	string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_Frame.size() != _Indexs.size())
		MSGASSERT(nullptr, _AnimationName, "의 Frame과 Time 갯수가 상이합니다.");

	if (FrameAnimations.contains(UpperName))
		return;

	UEngineSprite* FindSprite = UImageManager::GetInst().FindSprite(_SpriteName);

	if (FindSprite == nullptr)
		MSGASSERT(nullptr, _SpriteName, "는 로드 되지 않은 Sprite입니다.");

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
	vector<int> Indexs = {};
	vector<float> Times(_End - _Start + 1, _Time);

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
	{
		OffAnimation();
		return;
	}
		//MSGASSERT(nullptr, _AnimationName, "이라는 Animation은 없습니다.");

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && _Force == false)
		return;

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();
	CurIndex = CurAnimation->FrameIndex[CurAnimation->CurIndex];

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
		CurAnimation->Events[CurAnimation->CurIndex]();

	Sprite = CurAnimation->Sprite;
}

void USpriteRenderer::SetAnimationEvent(std::string_view _AnimationName, int _AnimationFrame, std::function<void()> _Function)
{
	string UpperName = UEngineString::ToUpper(_AnimationName);

	if (FrameAnimations.contains(UpperName) == false)
		MSGASSERT(nullptr, _AnimationName, "은 없는 Animation입니다.");

	if (FrameAnimations[UpperName].FrameIndex.size() <= _AnimationFrame)
		MSGASSERT(nullptr, _AnimationName, "은 없는 Animation Frame입니다.");

	FrameAnimations[UpperName].Events[_AnimationFrame] += _Function;
}

void USpriteRenderer::SetOrder(int _Order)
{
	int PrevOrder = Order;
	Order = _Order;

	if (PrevOrder == Order)
		return;

	ULevel* Level = GetActor()->GetWorld();

	if (Level != nullptr)
		Level->ChangeRenderOrder(this, PrevOrder);
}
