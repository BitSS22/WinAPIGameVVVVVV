#include "pch.h"
#include "EngineDirectory.h"
#include "EngineFile.h"

UEngineDirectory::UEngineDirectory()
{
}

UEngineDirectory::UEngineDirectory(string_view _Path)
	: UEnginePath(_Path)
{
}

UEngineDirectory::UEngineDirectory(std::filesystem::path _Path)
	: UEnginePath(_Path)
{
}

UEngineDirectory::~UEngineDirectory()
{
}

vector<UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive)
{
	vector<UEngineFile> Result = {};

	std::filesystem::directory_iterator iter = std::filesystem::directory_iterator(Path);

	while (iter._At_end() == false)
	{
		std::filesystem::path FilePath = *iter;

		UEnginePath LocalPath = FilePath;
		if (LocalPath.IsDirectory() == true)
		{
			if (_IsRecursive == true)
				GetAllFileRecursive(FilePath, &Result);

			++iter;
			continue;
		}

		Result.push_back(UEngineFile(FilePath));
		++iter;
	}

	return Result;
}

void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path, vector<UEngineFile>* _Result)
{
	std::filesystem::directory_iterator iter = std::filesystem::directory_iterator(_Path);

	while (iter._At_end() == false)
	{
		std::filesystem::path FilePath = *iter;

		UEnginePath LocalPath = FilePath;
		if (LocalPath.IsDirectory() == true)
		{
			GetAllFileRecursive(FilePath, _Result);
			++iter;
			continue;
		}

		_Result->push_back(UEngineFile(FilePath));
		++iter;
	}
}

