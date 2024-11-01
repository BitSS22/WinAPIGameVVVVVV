#pragma once

class UEngineWindowImage;

namespace UEngineDebug
{
	void WinAPIOutputString(UEngineWindowImage* _Image, std::string_view _Text, FVector2D _Pos);
}