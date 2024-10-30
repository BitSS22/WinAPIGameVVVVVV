#include "pch.h"
#include "EngineString.h"

UEngineString::UEngineString()
{
}

UEngineString::~UEngineString()
{
}

string UEngineString::ToUpper(string_view _str)
{
	string result = _str.data();
	result.resize(_str.size());

	for (size_t i = 0; i < _str.size(); ++i)
		result[i] = std::toupper(_str[i]);

	return result;
}

std::wstring UEngineString::AnsiToUnicode(string_view _Name)
{
	int size = MultiByteToWideChar(CP_ACP, 0, _Name.data(), static_cast<int>(_Name.size()), nullptr, 0);

	if (size == 0)
		MSGASSERT(nullptr, _Name, "�� ���ڿ� ��ȯ�� ������.");

	std::wstring result = {};
	result.resize(size);

	size = MultiByteToWideChar(CP_ACP, 0, _Name.data(), static_cast<int>(_Name.size()), result.data(), size);

	if (size == 0)
		MSGASSERT(nullptr, _Name, "�� ���ڿ� ��ȯ�� ������.");

	return result;
}

