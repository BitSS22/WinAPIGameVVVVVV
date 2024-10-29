#pragma once
#include "EnginePath.h"
#include <io.h>

const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
public:
	UEngineFile();
	UEngineFile(string_view _Path);
	UEngineFile(std::filesystem::path _Path);
	~UEngineFile();

private:
	char Path[MAXPATH] = {};
	FILE* File = nullptr;

public:
	void Write(const void* _Ptr, size_t _Size) const;
	void Read(void* _Ptr, size_t _Size) const;
	void FileOpen(const char* _Mode);
	void Close();

private:

public:
	void SetPath(const char* _Path)
	{
		strcpy_s(Path, _Path);
	}
	bool IsExits() const
	{
		return _access(Path, 00) == 0;
	}


};

