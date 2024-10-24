#include "pch.h"
#include <EngineCore/EngineAPICore.h>
#include <VVVVVV/V6ContentsCore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "VVVVVV.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	V6ContentsCore User = {};

	return UEngineAPICore::EngineStart(hInstance, &User);
}