#pragma once

// Ό³Έν :
class AGameText : public AActor
{
public:
	AGameText();
	~AGameText();

	AGameText(const AGameText& _Other) = delete;
	AGameText(AGameText&& _Other) noexcept = delete;
	AGameText& operator=(const AGameText& _Other) = delete;
	AGameText& operator=(AGameText&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;

public:
	void CreateText(std::string_view _String);
	void Say(std::string_view _String);

private:

public:

};

