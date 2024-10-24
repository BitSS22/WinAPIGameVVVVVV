#pragma once

// Ό³Έν :
class ULevel
{
public:
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

private:
	class AGameMode* GameMode = nullptr;

public:

private:

};

