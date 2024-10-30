#pragma once
#include <filesystem>

// Ό³Έν :
class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

protected:
	std::filesystem::path Path = {};

public:
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
	string GetFileName()
	{
		return Path.filename().string();
	}
	string GetExtension()
	{
		return Path.extension().string();
	}

};

