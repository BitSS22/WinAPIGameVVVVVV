#pragma once

namespace UEngineDebug
{
	enum class EDebugPosType
	{
		Rect,
		Circle
	};

	void CoreOutputString(std::string_view _Text);
	void CoreOutputString(std::string_view _Text, FVector2D _Pos);
	void CoreDebugRender(FTransform _Trans, EDebugPosType _Type);

	void PrintEngineDebugRender();

	void SetIsDebug(bool _IsDebug);
	void SwitchIsDebug();
}