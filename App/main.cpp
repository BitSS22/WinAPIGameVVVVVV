#include "pch.h"
#include <EngineCore/EngineAPICore.h>
#include <VVVVVV/V6ContentsCore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "VVVVVV.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(231);

	V6ContentsCore User = {};

	return UEngineAPICore::EngineStart(hInstance, &User);
}