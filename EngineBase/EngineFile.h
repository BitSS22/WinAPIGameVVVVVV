#pragma once

const int MAXPATH = 256;

class UEngineFile
{
public:
	UEngineFile();
	~UEngineFile();

private:
	char Path[MAXPATH] = {};
	FILE* File = nullptr;

public:
	
	void Write(const void* _Ptr, size_t _Size);
	void Read(void* _Ptr, size_t _Size);
	void FileOpen(const char* _Mode);
	bool IsExits();
	void Close();

public:
	void SetPath(const char* _Path)
	{
		strcpy_s(Path, _Path);
	}

};

