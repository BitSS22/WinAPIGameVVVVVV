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

	void operator<< (int _Data)
	{
		Write(&_Data, sizeof(int));
	}
	void operator<< (size_t _Data)
	{
		Write(&_Data, sizeof(size_t));
	}
	void operator<< (float _Data)
	{
		Write(&_Data, sizeof(float));
	}
	void operator<< (bool _Data)
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
		*this << _Data.size();
		Write(_Data.data(), _Data.size());
	}
	template<typename T>
	void operator<< (std::vector<T>& _Vec)
	{
		*this << _Vec.size();

		for (size_t i = 0; i < _Vec.size(); ++i)
			*this << _Vec[i];
	}

	void operator>> (ISerializObject& _Data);

	void operator>> (int _Data)
	{
		Read(&_Data, sizeof(int));
	}
	void operator>> (size_t _Data)
	{
		Read(&_Data, sizeof(size_t));
	}
	void operator>> (float _Data)
	{
		Read(&_Data, sizeof(float));
	}
	void operator>> (bool _Data)
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
		Read(_Data.data(), _Data.size());
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
	size_t WriteOffset = 0;
	size_t ReadOffset = 0;

public:
	void Write(void* _Data, size_t _Size);
	void Read(void* _Data, size_t _Size);

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