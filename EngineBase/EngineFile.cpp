#include "pch.h"
#include "io.h"
#include "EngineFile.h"
#include "EngineDebug.h"
#include "EngineSerializer.h"

UEngineFile::UEngineFile()
{
}

UEngineFile::UEngineFile(string_view _Path)
    : UEnginePath(_Path)
{
}

UEngineFile::UEngineFile(const string& _Path)
    : UEnginePath(_Path)
{
}

UEngineFile::UEngineFile(std::filesystem::path _Path)
    : UEnginePath(_Path)
{
}

UEngineFile::~UEngineFile()
{
    Close();
}

void UEngineFile::Write(UEngineSerializer& _Ser)
{
    Write(_Ser.GetDataPtr(), _Ser.GetWriteOffset());
}

void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
    if (_Size == 0)
    {
        MSGASSERT(nullptr, "ũ�Ⱑ 0�� �����͸� �� �� �����ϴ�.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT(nullptr, "�������� �ʴ� �޸𸮸� ����� �� �����ϴ�.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT(nullptr, "���� ���� ���Ͽ� ������ �� �� �����ϴ�.");
        return;
    }

    fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(UEngineSerializer& _Ser)
{
    size_t FileSize = GetFileSize();

    _Ser.DataResize(FileSize);

    Read(_Ser.GetDataPtr(), FileSize);
}

void UEngineFile::Read(void* _Ptr, size_t _Size)
{
    if (_Size == 0)
    {
        MSGASSERT(nullptr, "ũ�Ⱑ 0�� �����͸� ���� �� �����ϴ�.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT(nullptr, "�������� �ʴ� �޸𸮸� ����� �� �����ϴ�.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT(nullptr, "���� ���� ������ ������ ���� �� �����ϴ�.");
        return;
    }

    fread(_Ptr, _Size, 1, File);
}

void UEngineFile::FileOpen(const char* _Mode)
{
    fopen_s(&File, GetPathToString().c_str(), _Mode);

    if (File == nullptr)
        MSGASSERT(nullptr, "��ȿ���� ���� Path�Դϴ�.");
}

void UEngineFile::Close()
{
    if (File != nullptr)
    {
        fclose(File);
        File = nullptr;
    }
}
