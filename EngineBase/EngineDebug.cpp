#include "pch.h"
#include "EngineDebug.h"

namespace UEngineDebug
{
	void OutputString(const std::string& Text)
	{
		string Result = Text + "\n";
		OutputDebugStringA(Result.c_str());
	}
}