#include "pch.h"
#include "EngineWindowDebug.h"
#include "EngineWindowImage.h"

void UEngineDebug::WinAPIOutputString(UEngineWindowImage* _Image, std::string_view _Text, FVector2D _Pos)
{
	TextOutA(_Image->GetDC(), _Pos.iX(), _Pos.iY(), _Text.data(), static_cast<int>(_Text.size()));
}
