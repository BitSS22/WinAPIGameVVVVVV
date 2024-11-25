#pragma once
#include <string>

class USpriteRenderer;
// Ό³Έν :
class UGameString
{
public:
	UGameString() = delete;
	~UGameString();

	UGameString(const UGameString& _Other) = delete;
	UGameString(UGameString&& _Other) noexcept = delete;
	UGameString& operator=(const UGameString& _Other) = delete;
	UGameString& operator=(UGameString&& _Other) noexcept = delete;

private:
	static const FVector2D FontSize;
	static std::map<std::string, UEngineWindowImage*> Strings;

public:
	static UEngineWindowImage* CreateGameString(std::string_view _String, unsigned int _LineMaxCount, bool _TextBox, EGameColor _Color);

private:

public:

};

