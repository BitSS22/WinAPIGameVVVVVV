#include "pch.h"
#include "EngineDebug.h"

void OutputString(const std::string& Text)
{
	string Result = Text + "\n";
	OutputDebugStringA(Result.c_str());
}
