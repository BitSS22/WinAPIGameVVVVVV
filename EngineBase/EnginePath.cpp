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
		MSGASSERT(nullptr, Path.string(), "�� Directory Path�� �ƴմϴ�.");

	std::filesystem::path CurPath = TempPath.Path;
	
	while (CurPath != CurPath.root_path())
	{
		CurPath = TempPath.Path;
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
