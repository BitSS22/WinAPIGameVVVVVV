#pragma once

#include <vector>
#include "EnginePath.h"

class UEngineFile;

class UEngineDirectory : public UEnginePath
{
public:
	UEngineDirectory();
	UEngineDirectory(string_view _Path);
	UEngineDirectory(std::filesystem::path _Path);
	~UEngineDirectory();

	UEngineDirectory(const UEngineDirectory& _Other) = delete;
	UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

private:

public:
	vector<UEngineFile> GetAllFile(bool _IsRecursive = true);

private:
	void GetAllFileRecursive(std::filesystem::path _Path, vector<UEngineFile>* _Result);

public:

};

