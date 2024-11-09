#pragma once

class AAnimationManager : public AActor
{
public:
	AAnimationManager();
	~AAnimationManager();

private:
	static AAnimationManager* Inst;
	std::map<string, USpriteRenderer*> Animations = {};

public:
	virtual void BeginPlay() override;

private:
	void CreateAnimation(std::string_view _SpriteName, std::vector<int> _indexs, float frames, bool _Loop);

public:
	static AAnimationManager* GetInst()
	{
		return Inst;
	}
	USpriteRenderer* GetTileAnimation(std::string_view _AnimationName);

};

