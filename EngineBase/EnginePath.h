#pragma once
#include <filesystem>

// 설명 :
class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(const std::string& _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

protected:
	std::filesystem::path Path = {};

public:
	void Append(string_view _AppendName)
	{
		Path.append(_AppendName);
	}
	void MoveParent()
	{
		Path = Path.parent_path();
	}
	bool MoveParentToDirectory(string_view _Path);

private:

public:
	string GetPathToString() const
	{
		return Path.string();
	}
	bool IsExists() const
	{
		return std::filesystem::exists(Path);
	}
	bool IsDirectory() const
	{
		return std::filesystem::is_directory(Path);
	}
	string GetExtension()
	{
		return Path.extension().string();
	}
	string GetFileName()
	{
		if (IsDirectory() == true)
			MSGASSERT(nullptr, Path.string(), "는 파일 경로가 아닙니다.");
		return Path.filename().string();
	}
	string GetDirectoryName()
	{
		if (IsDirectory() == false)
			MSGASSERT(nullptr, Path.string(), "는 디렉토리 경로가 아닙니다.");
		return Path.filename().string();
	}
	bool IsFile()
	{
		return IsDirectory() == false;
	}

};

