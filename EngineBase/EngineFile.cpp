#include "pch.h"
#include "io.h"
#include "EngineFile.h"
#include "EngineDebug.h"

UEngineFile::UEngineFile()
{
}

UEngineFile::UEngineFile(string_view _Path)
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

void UEngineFile::Write(const void* _Ptr, size_t _Size) const
{
    if (_Size == 0)
    {
        MSGASSERT(nullptr, "크기가 0인 데이터를 쓸 수 없습니다.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT(nullptr, "존재하지 않는 메모리를 사용할 수 없습니다.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT(nullptr, "열지 않은 파일에 내용을 쓸 수 없습니다.");
        return;
    }

    fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(void* _Ptr, size_t _Size) const
{
    if (_Size == 0)
    {
        MSGASSERT(nullptr, "크기가 0인 데이터를 읽을 수 없습니다.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT(nullptr, "존재하지 않는 메모리를 사용할 수 없습니다.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT(nullptr, "열지 않은 파일의 내용을 읽을 수 없습니다.");
        return;
    }

    fread(_Ptr, _Size, 1, File);
}

void UEngineFile::FileOpen(const char* _Mode)
{
    fopen_s(&File, Path, _Mode);

    if (File == nullptr)
        MSGASSERT(nullptr, "유효하지 않은 Path입니다.");
}

void UEngineFile::Close()
{
    if (File != nullptr)
    {
        fclose(File);
        File = nullptr;
    }
}
