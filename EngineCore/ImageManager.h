#pragma once

// Ό³Έν :
class UImageManager
{
private:
	UImageManager();
public:
	~UImageManager();

	UImageManager(const UImageManager& _Other) = delete;
	UImageManager(UImageManager&& _Other) noexcept = delete;
	UImageManager& operator=(const UImageManager& _Other) = delete;
	UImageManager& operator=(UImageManager&& _Other) noexcept = delete;

private:
	map<string, UEngineWindowImage*> Images = {};

public:
	void Load(string_view _Path);

private:

public:
	static UImageManager& GetInst()
	{
		static UImageManager Inst = {};
		return Inst;
	}

};

