#include "pch.h"
#include "EnginePath.h"

UEnginePath::UEnginePath()
	: Path(std::filesystem::current_path())
{
}

UEnginePath::UEnginePath(string_view _Path)
	: Path(_Path)
{
}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

UEnginePath::~UEnginePath()
{
}

bool UEnginePath::MoveParentToDirectory(string_view _Path)
{
	UEnginePath TempPath = Path;

	if (TempPath.IsDirectory() == false)
		MSGASSERT(nullptr, Path.string(), "는 Directory Path가 아닙니다.");

	std::filesystem::path CurPath = TempPath.Path;

	std::filesystem::path Root = CurPath.root_path();

	while (true)
	{
		CurPath = TempPath.Path;

		if (CurPath == Root)
			break;

		CurPath.append(_Path);

		if (std::filesystem::exists(CurPath) == true)
		{
			Path = CurPath;
			return true;
		}

		TempPath.MoveParent();
	}

	return false;
}
