#pragma once
#include <vector>

class ISerializObject;
// Ό³Έν :
class UEngineSerializer
{
public:
	UEngineSerializer();
	~UEngineSerializer();

	UEngineSerializer(const UEngineSerializer& _Other) = delete;
	UEngineSerializer(UEngineSerializer&& _Other) noexcept = delete;
	UEngineSerializer& operator=(const UEngineSerializer& _Other) = delete;
	UEngineSerializer& operator=(UEngineSerializer&& _Other) noexcept = delete;

	void operator<< (ISerializObject& _Data);

	void operator<< (int& _Data)
	{
		Write(&_Data, sizeof(int));
	}
	void operator<< (float& _Data)
	{
		Write(&_Data, sizeof(float));
	}
	void operator<< (bool& _Data)
	{
		Write(&_Data, sizeof(bool));
	}
	void operator<< (FVector2D& _Data)
	{
		Write(&_Data, sizeof(FVector2D));
	}
	void operator<< (FIntPoint& _Data)
	{
		Write(&_Data, sizeof(FIntPoint));
	}
	void operator<< (std::string& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		*this << Size;
		Write(_Data.data(), static_cast<int>(_Data.size()));
	}
	template<typename T>
	void operator<< (std::vector<T>& _Vec)
	{
		int Size = static_cast<int>(_Vec.size());
		*this << Size;

		for (size_t i = 0; i < _Vec.size(); ++i)
			*this << _Vec[i];
	}

	void operator>> (ISerializObject& _Data);

	void operator>> (int& _Data)
	{
		Read(&_Data, sizeof(int));
	}
	void operator>> (float& _Data)
	{
		Read(&_Data, sizeof(float));
	}
	void operator>> (bool& _Data)
	{
		Read(&_Data, sizeof(bool));
	}
	void operator>> (FVector2D& _Data)
	{
		Read(&_Data, sizeof(FVector2D));
	}
	void operator>> (FIntPoint& _Data)
	{
		Read(&_Data, sizeof(FIntPoint));
	}
	void operator>> (std::string& _Data)
	{
		int Size = 0;
		*this >> Size;
		_Data.resize(Size);
		Read(_Data.data(), static_cast<int>(_Data.size()));
	}
	template<typename T>
	void operator>> (std::vector<T>& _Vec)
	{
		int Size = 0;
		*this >> Size;
		_Vec.resize(Size);

		for (size_t i = 0; i < _Vec.size(); ++i)
			*this >> _Vec[i];
	}

private:
	std::vector<char> Data = {};
	int WriteOffset = 0;
	int ReadOffset = 0;

public:
	void Write(void* _Data, int _Size);
	void Read(void* _Data, int _Size);

private:

public:
	void* GetDataPtr()
	{
		return Data.data();
	}
	size_t GetWriteOffset()
	{
		return WriteOffset;
	}
	void DataResize(size_t _Value)
	{
		Data.resize(_Value);
	}

};

class ISerializObject
{
public:
	virtual void Serialize(UEngineSerializer& _Class) = 0;
	virtual void DeSerialize(UEngineSerializer& _Class) = 0;
};