#include "EngineFile.h"
#include "EngineDebug.h"

UEngineFile::UEngineFile()
{
}

UEngineFile::~UEngineFile()
{
    Close();
}

void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
    if (_Size == 0)
    {
        MSGASSERT("크기가 0인 데이터를 쓸 수 없습니다.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT("존재하지 않는 메모리를 사용할 수 없습니다.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT("열지 않은 파일에 내용을 쓸 수 없습니다");
        return;
    }

    fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(void* _Ptr, size_t _Size)
{
    if (_Size == 0)
    {
        MSGASSERT("크기가 0인 데이터를 쓸 수 없습니다.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT("존재하지 않는 메모리를 사용할 수 없습니다.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT("열지 않은 파일에 내용을 쓸 수 없습니다.");
        return;
    }

    fread(_Ptr, _Size, 1, File);
}

void UEngineFile::FileOpen(const char* _Mode)
{
    fopen_s(&File, Path, _Mode);

    if (File == nullptr)
        MSGASSERT("유효하지 않은 Path입니다.");
}

bool UEngineFile::IsExits()
{
    return _access(Path, 00) == 0;
}

void UEngineFile::Close()
{
    if (File != nullptr)
    {
        fclose(File);
        File = nullptr;
    }
}
