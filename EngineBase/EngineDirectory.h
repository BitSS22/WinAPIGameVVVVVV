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

private:

public:
	vector<UEngineFile> GetAllFile(bool _IsRecursive = true);
	vector<UEngineDirectory> GetAllDirectory();

private:
	void GetAllFileRecursive(std::filesystem::path _Path, vector<UEngineFile>* _Result);

public:

};

