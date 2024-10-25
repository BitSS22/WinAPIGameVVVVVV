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

public:
	bool IsExits() const
	{
		return _access(Path, 00) == 0;
	}


};

