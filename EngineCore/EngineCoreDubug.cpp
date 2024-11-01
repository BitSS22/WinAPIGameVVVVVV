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

	vector<DebugTextInfo> DebugTexts = {};
	FVector2D EngineTextPos = FVector2D::ZERO;
	bool IsDebug = false;

	void CoreOutputString(std::string_view _Text)
	{
		DebugTexts.push_back(DebugTextInfo(_Text.data(), EngineTextPos));
		EngineTextPos.Y += 20;
	}

	void CoreOutputString(std::string_view _Text, FVector2D _Pos)
	{
		DebugTexts.push_back(DebugTextInfo(_Text.data(), _Pos));
	}

	void PrintEngineDebugText()
	{
		UEngineWindowImage* BackBuffer = UEngineAPICore::GetCore()->GetMainWindow().GetBackBufferImage();

		for (size_t i = 0; i < DebugTexts.size(); ++i)
		{
			DebugTextInfo& Debug = DebugTexts[i];
			WinAPIOutputString(BackBuffer, Debug.Text, Debug.Pos);
		}

		EngineTextPos = FVector2D::ZERO;
		DebugTexts.clear();
	}

	void SetIsDebug(bool _IsDebug)
	{
		IsDebug = _IsDebug;
	}
	void SwitchIsDebug()
	{
		IsDebug = !IsDebug;
	}
}

