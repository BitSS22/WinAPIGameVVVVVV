#pragma once

namespace UEngineDebug
{
	void CoreOutputString(std::string_view _Text);
	void CoreOutputString(std::string_view _Text, FVector2D _Pos);

	void PrintEngineDebugText();

	void SetIsDebug(bool _IsDebug);
	void SwitchIsDebug();
}