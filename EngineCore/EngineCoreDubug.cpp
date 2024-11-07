#include "pch.h"
#include "EngineCoreDubug.h"
#include "EnginePlatform/EngineWindowDebug.h"

namespace UEngineDebug
{
	struct DebugTextInfo
	{
	public:
		string Text;
		FVector2D Pos;
	};

	struct DebugRenderInfo
	{
	public:
		FTransform Trans;
		EDebugPosType Type;
	};

	vector<DebugRenderInfo> DebugPoses = {};
	vector<DebugTextInfo> DebugTexts = {};
	FVector2D EngineTextPos = FVector2D::ZERO;
	bool IsDebug = false;

	void CoreDebugRender(FTransform _Trans, EDebugPosType _Type)
	{
		DebugPoses.push_back({ _Trans, _Type });
	}

	void CoreOutputString(std::string_view _Text)
	{
		DebugTexts.push_back(DebugTextInfo(_Text.data(), EngineTextPos));
		EngineTextPos.Y += 20;
	}

	void CoreOutputString(std::string_view _Text, FVector2D _Pos)
	{
		DebugTexts.push_back(DebugTextInfo(_Text.data(), _Pos));
	}

	void PrintEngineDebugRender()
	{
		UEngineWindowImage* BackBuffer = UEngineAPICore::GetCore()->GetMainWindow().GetBackBufferImage();

		for (size_t i = 0; i < DebugTexts.size(); ++i)
		{
			DebugTextInfo& Debug = DebugTexts[i];
			WinAPIOutputString(BackBuffer, Debug.Text, Debug.Pos);
		}

		EngineTextPos = FVector2D::ZERO;
		DebugTexts.clear();

		for (size_t i = 0; i < DebugPoses.size(); ++i)
		{
			EDebugPosType Type = DebugPoses[i].Type;

			FVector2D LT = DebugPoses[i].Trans.CenterLeftTop();
			FVector2D RB = DebugPoses[i].Trans.CenterRightBottom();

			switch (Type)
			{
			case UEngineDebug::EDebugPosType::Rect:
				Rectangle(BackBuffer->GetDC(), LT.iX(), LT.iY(), RB.iX(), RB.iY());
				break;
			case UEngineDebug::EDebugPosType::Circle:
				Ellipse(BackBuffer->GetDC(), LT.iX(), LT.iY(), RB.iX(), RB.iY());
				break;
			default:
				break;
			}
		}

		DebugPoses.clear();
	}

	void SetIsDebug(bool _IsDebug)
	{
		IsDebug = _IsDebug;
	}
	void SwitchIsDebug()
	{
		IsDebug = !IsDebug;
	}

	void CoreDebugBox(FTransform _Trans)
	{

	}
}

