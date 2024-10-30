#pragma once

// Ό³Έν :
class UEngineString
{
private:
	UEngineString();
public:
	~UEngineString();

	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;

private:

public:
	static string ToUpper(string_view _str);
	static std::wstring AnsiToUnicode(string_view _Name);

private:

};

