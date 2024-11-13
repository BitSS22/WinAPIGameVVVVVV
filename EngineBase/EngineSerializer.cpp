#include "pch.h"
#include "EngineSerializer.h"

UEngineSerializer::UEngineSerializer()
{
}

UEngineSerializer::~UEngineSerializer()
{
}

void UEngineSerializer::operator<< (ISerializObject& _Data)
{
	_Data.Serialize(*this);
}

void UEngineSerializer::operator>> (ISerializObject& _Data)
{
	_Data.DeSerialize(*this);
}

void UEngineSerializer::Write(void* _Data, int _Size)
{
	if (Data.size() <= WriteOffset + _Size)
		Data.resize(Data.size() * 2 + _Size);

	memcpy_s(&Data[WriteOffset], _Size, _Data, _Size);
	WriteOffset += _Size;
}

void UEngineSerializer::Read(void* _Data, int _Size)
{
	memcpy_s(_Data, _Size, &Data[ReadOffset], _Size);
	ReadOffset += _Size;
}
