#pragma once
#include "GameMode.h"
#include <list>
#include "SpriteRenderer.h"
#include "2DCollision.h"

struct CollisionLinkData
{
public:
	union
	{
		struct
		{
			int Left;
			int Right;
		};
		__int64 Key = 0;
	};
};

class ULevel : public UObject
{
public:
	friend class UEngineAPICore;
	friend class USpriteRenderer;
	friend class U2DCollision;
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
	std::map<int, std::list<U2DCollision*>> Collisions = {};
	static std::vector<CollisionLinkData> CollisionLink;
	std::map<int, std::list<U2DCollision*>> CheckCollisions = {};

	AGameMode* GameMode = nullptr;
	AActor* MainPawn = nullptr;

	bool IsCameraToMainPawn = false;
	FVector2D CameraPos = {};
	FVector2D CameraPivot = {};

public:
	void Tick();
	void Render();
	void Realease();
	void Collision();

	void LevelChangeStart();
	void LevelChangeEnd();

	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->GameWorld = this;

		BeginPlayList.push_back(ActorPtr);
		return NewActor;
	}

	template<typename LeftEnumType, typename RightEnumType>
	static void CollisionGroupLink(LeftEnumType _Left, RightEnumType _Right)
	{
		CollisionGroupLink(static_cast<int>(_Left), static_cast<int>(_Right));
	}

	static void CollisionGroupLink(int _Left, int _Right)
	{
		CollisionLinkData Data = { _Left, _Right };

		for (size_t i = 0; i < CollisionLink.size(); ++i)
		{
			if (CollisionLink[i].Key == _Right)
				return;
		}

		CollisionLink.push_back(Data);
	}

private:
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();

		MainPawn->GameWorld = this;
		GameMode->GameWorld = this;

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
	void PushCollision(U2DCollision* _Collision)
	{
		Collisions[_Collision->GetCollisionGroup()].push_back(_Collision);
	}
	void PushCheckCollision(U2DCollision* _Collision)
	{
		CheckCollisions[_Collision->GetCollisionGroup()].push_back(_Collision);
	}
	void CollisionEventCheck(U2DCollision* _Left, U2DCollision* _Right);

	void DoubleBuffering();
	void ScreenClear();
	void BeginPlayCheck();

public:
	void SetCameraToMainPawn(bool _IsCameraToMainPawn)
	{
		IsCameraToMainPawn = _IsCameraToMainPawn;
	}
	void SetCameraPivot(FVector2D _Pivot)
	{
		CameraPivot = _Pivot;
	}
	void SetCameraPos(FVector2D _Pos)
	{
		CameraPos = _Pos;
	}
	void AddCameraPos(FVector2D _Pos)
	{
		CameraPos += _Pos;
	}
	FVector2D GetCameraPos() const
	{
		return CameraPos;
	}
	AActor* GetMainPawn()
	{
		return MainPawn;
	}
	template<typename ConvertType>
	ConvertType* GetMainPawn()
	{
		return dynamic_cast<ConvertType*>(MainPawn);
	}
	AActor* GetGameMode()
	{
		return GameMode;
	}
	template<typename ConvertType>
	ConvertType* GetGameMode()
	{
		return dynamic_cast<ConvertType*>(GameMode);
	}

};

