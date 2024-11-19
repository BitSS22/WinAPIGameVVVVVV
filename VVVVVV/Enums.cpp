#include "pch.h"
#include "Enums.h"

EEntityType& operator++(EEntityType& _Type)
{
	int Index = static_cast<int>(_Type) + 1;
	if (Index >= static_cast<int>(EEntityType::Last))
		Index = 0;
	_Type = static_cast<EEntityType>(Index);
	return _Type;
}

EEntityType& operator--(EEntityType& _Type)
{
	int Index = static_cast<int>(_Type) - 1;
	if (Index < 0)
		Index = static_cast<int>(EEntityType::Last) - 1;
	_Type = static_cast<EEntityType>(Index);
	return _Type;
}

ETileType& operator++(ETileType& _Type)
{
	int Index = static_cast<int>(_Type) + 1;
	if (Index >= static_cast<int>(ETileType::Last))
		Index = 0;
	_Type = static_cast<ETileType>(Index);
	return _Type;
}

ETileType& operator--(ETileType& _Type)
{
	int Index = static_cast<int>(_Type) - 1;
	if (Index < 0)
		Index = static_cast<int>(ETileType::Last) - 1;
	_Type = static_cast<ETileType>(Index);
	return _Type;
}

EBackGroundType& operator++(EBackGroundType& _Type)
{
	int Index = static_cast<int>(_Type) + 1;
	if (Index >= static_cast<int>(EBackGroundType::Last))
		Index = 0;
	_Type = static_cast<EBackGroundType>(Index);
	return _Type;
}

EBackGroundType& operator--(EBackGroundType& _Type)
{
	int Index = static_cast<int>(_Type) - 1;
	if (Index < 0)
		Index = static_cast<int>(EBackGroundType::Last) - 1;
	_Type = static_cast<EBackGroundType>(Index);
	return _Type;
}
