#pragma once

// TODO. 아직 구현하지 않은 클래스

// 설명 :
class GameString : public AActor
{
public:
	GameString();
	~GameString();

	GameString(const GameString& _Other) = delete;
	GameString(GameString&& _Other) noexcept = delete;
	GameString& operator=(const GameString& _Other) = delete;
	GameString& operator=(GameString&& _Other) noexcept = delete;

private:
	std::vector<USpriteRenderer*> Fonts = {};

public:
	void InsertFont(USpriteRenderer* _Sprite, FIntPoint _Size)
	{}

private:

public:
	void SetFontColor(GameColor _Color)
	{

	}
};

