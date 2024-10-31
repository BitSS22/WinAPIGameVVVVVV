#pragma once
#include "GameMode.h"
#include <list>
#include "SpriteRenderer.h"

// ���� :
class ULevel
{
public:
	friend class UEngineAPICore;
	friend class USpriteRenderer;
public:
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

private:
	std::list<AActor*> AllActors = {};
	std::list<AActor*> BeginPlayList = {};
	std::map<int, std::list<USpriteRenderer*>> Renderers = {};
	AGameMode* GameMode = nullptr;
	AActor* MainPawn = nullptr;

public:
	void Tick();
	void Render();

	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->World = this;

		BeginPlayList.push_back(ActorPtr);
		return NewActor;
	}

private:
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();

		MainPawn->World = this;
		GameMode->World = this;

		BeginPlayList.push_back(GameMode);
		BeginPlayList.push_back(MainPawn);
	}
	void ChangeRenderOrder(USpriteRenderer* _Renderer, int _PrevOrder)
	{
		Renderers[_PrevOrder].remove(_Renderer);
		Renderers[_Renderer->GetOrder()].push_back(_Renderer);
	}

	void PushRenderer(USpriteRenderer* _Renderer)
	{
		Renderers[_Renderer->GetOrder()].push_back(_Renderer);
	}
	void DoubleBuffering();
	void ScreenClear();

};

