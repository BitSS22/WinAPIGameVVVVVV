#include "pch.h"
#include "UGameString.h"
#include <EnginePlatform/EngineWindowImage.h>

std::map<std::string, UEngineWindowImage*> UGameString::Strings = {};
const FVector2D UGameString::FontSize = FVector2D(32.f, 32.f);

UGameString::~UGameString()
{
}

UEngineWindowImage* UGameString::CreateGameString(std::string_view _String, unsigned int _LineMaxCount, bool _TextBox, EGameColor _Color)
{
	string FindName = _String.data();

	switch (_Color)
	{
	case EGameColor::Cyan:
		FindName += " Cyan";
		break;
	case EGameColor::Pink:
		FindName += " Pink";
		break;
	case EGameColor::Red:
		FindName += " Red";
		break;
	case EGameColor::Blue:
		FindName += " Blue";
		break;
	case EGameColor::Yellow:
		FindName += " Yellow";
		break;
	case EGameColor::Green:
		FindName += " Green";
		break;
	case EGameColor::Grey:
		FindName += " Grey";
		break;
	case EGameColor::White:
		FindName += " White";
		break;
	}

	if (Strings.contains(_String.data()) == true)
		return Strings[_String.data()];

	int XCount = _LineMaxCount;
	int YCount = _String.size() / XCount;
	if (_String.size() % _LineMaxCount != 0)
		++YCount;

	if (_TextBox == true)
	{
		XCount += 2;
		YCount += 2;
	}

	UEngineWindowImage* NewImage = nullptr;
	NewImage->Create(UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage(), FVector2D(XCount * FontSize.X, YCount * FontSize.Y));

	Strings.insert(make_pair(FindName, NewImage));

	string KeyName = "Fonts:: ";

	switch (_Color)
	{
	case EGameColor::Cyan:
		KeyName += "Cyan";
		break;
	case EGameColor::Pink:
		KeyName += "Pink";
		break;
	case EGameColor::Red:
		KeyName += "Red";
		break;
	case EGameColor::Blue:
		KeyName += "Blue";
		break;
	case EGameColor::Yellow:
		KeyName += "Yellow";
		break;
	case EGameColor::Green:
		KeyName += "Green";
		break;
	case EGameColor::Grey:
		KeyName += "Grey";
		break;
	case EGameColor::White:
		KeyName += "White";
		break;
	}

	UEngineWindowImage* ColorSprite = UImageManager::GetInst().FindImage(KeyName);
	

	if (_TextBox == true)
	{
		for (int y = 0; y < YCount; ++y)
		{
			for (int x = 0; x < XCount; ++x)
			{
				
			}
		}
	}
}
