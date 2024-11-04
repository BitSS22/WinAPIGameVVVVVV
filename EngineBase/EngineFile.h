#pragma once
#include "EnginePath.h"
#include <io.h>

class UEngineSerializer;

class UEngineFile : public UEnginePath
{
public:
	UEngineFile();
	UEngineFile(std::string_view _Path);
	UEngineFile(const std::string& _Path);
	UEngineFile(std::filesystem::path _Path);
	~UEngineFile();

private:
	FILE* File = nullptr;

public:
	void Write(UEngineSerializer& _Ser);
	void Write(const void* _Ptr, size_t _Size);
	void Read(UEngineSerializer& _Ser);
	void Read(void* _Ptr, size_t _Size);
	void FileOpen(const char* _Mode);
	void Close();

private:

public:
	size_t GetFileSize()
	{
		if (IsFile() == false)
			MSGASSERT(nullptr, Path, "는 파일이 아닙니다.");

		return std::filesystem::file_size(Path);
	}


};

