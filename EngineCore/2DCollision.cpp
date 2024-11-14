#include "pch.h"
#include "2DCollision.h"

U2DCollision::U2DCollision()
{
}

U2DCollision::~U2DCollision()
{
}

void U2DCollision::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionGroup < 0)
		MSGASSERT(nullptr, "Collision Group은 양수로 지정해 주세요.");

	GetActor()->GetWorld()->PushCollision(this);

	if (Enter != nullptr && Stay != nullptr && End != nullptr)
		GetActor()->GetWorld()->PushCheckCollision(this);
}

void U2DCollision::ComponentTick()
{
	Super::ComponentTick();

	if (IsDebug() == true || GetActor()->IsDebug() == true)
	{
		FTransform ActorTransform = GetComponentTransform();
		FVector2D CameraPos = GetActor()->GetWorld()->GetCameraPos();

		ActorTransform.Location -= CameraPos;

		switch (CollisionType)
		{
		case ECollisionType::Rect:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Rect);
			break;
		case ECollisionType::Circle:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Circle);
			break;
		default:
			break;
		}
	}
}

bool U2DCollision::Collision(int _OtherCollisionGroup, std::vector<AActor*>& _Result, FVector2D _NextPos, UINT _Limit)
{
	U2DCollision* ThisCollision = this;
	if (ThisCollision->IsActive() == false)
		return false;

	list<U2DCollision*>& OtherCollisions = GetActor()->GetWorld()->Collisions[_OtherCollisionGroup];

	for (const auto& DestCollision : OtherCollisions)
	{
		if (DestCollision->IsActive() == false)
			continue;

		FTransform ThisTrans = ThisCollision->GetComponentOffsetTransform();
		FTransform DestTrans = DestCollision->GetComponentOffsetTransform();

		ThisTrans.Location += _NextPos;

		ECollisionType ThisType = ThisCollision->CollisionType;
		ECollisionType DestType = DestCollision->CollisionType;

		bool Result = FTransform::Collision(ThisType, ThisTrans, DestType, DestTrans);

		if (Result == true)
		{
			_Result.push_back(DestCollision->GetActor());
			--_Limit;

			if (_Limit == 0)
				return _Result.size() != 0;
		}
	}

	return _Result.size() != 0;
}

void U2DCollision::CollisionEventCheck(U2DCollision* _Other)
{
	FTransform ThisTrans = GetComponentOffsetTransform();
	FTransform DestTrans = _Other->GetComponentOffsetTransform();

	ECollisionType ThisType = GetCollisionType();
	ECollisionType DestType = _Other->GetCollisionType();

	bool Result = FTransform::Collision(ThisType, ThisTrans, DestType, DestTrans);

	if (Result == true)
	{
		if (CollisionCheckSet.contains(_Other))
		{
			if (Enter != nullptr)
				Enter(_Other->GetActor());
			CollisionCheckSet.insert(_Other);
		}
		else
		{
			if (Stay != nullptr)
				Stay(_Other->GetActor());
		}
	}
	else
	{
		if (CollisionCheckSet.contains(_Other))
		{
			if (End != nullptr)
				End(_Other->GetActor());
			CollisionCheckSet.erase(_Other);
		}
	}
}

void U2DCollision::SetCollisionEnter(std::function<void(AActor*)> _Function)
{
	Enter = _Function;
	if (GetActor()->GetWorld() != nullptr)
		GetActor()->GetWorld()->PushCheckCollision(this);
}

void U2DCollision::SetCollisionStay(std::function<void(AActor*)> _Function)
{
	Stay = _Function;
	if (GetActor()->GetWorld() != nullptr)
		GetActor()->GetWorld()->PushCheckCollision(this);
}

void U2DCollision::SetCollisionEnd(std::function<void(AActor*)> _Function)
{
	End = _Function;
	if (GetActor()->GetWorld() != nullptr)
		GetActor()->GetWorld()->PushCheckCollision(this);
}

