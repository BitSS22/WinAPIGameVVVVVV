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
        MSGASSERT("ũ�Ⱑ 0�� �����͸� �� �� �����ϴ�.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT("�������� �ʴ� �޸𸮸� ����� �� �����ϴ�.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT("���� ���� ���Ͽ� ������ �� �� �����ϴ�");
        return;
    }

    fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(void* _Ptr, size_t _Size)
{
    if (_Size == 0)
    {
        MSGASSERT("ũ�Ⱑ 0�� �����͸� �� �� �����ϴ�.");
        return;
    }
    else if (_Ptr == nullptr)
    {
        MSGASSERT("�������� �ʴ� �޸𸮸� ����� �� �����ϴ�.");
        return;
    }
    else if (File == nullptr)
    {
        MSGASSERT("���� ���� ���Ͽ� ������ �� �� �����ϴ�.");
        return;
    }

    fread(_Ptr, _Size, 1, File);
}

void UEngineFile::FileOpen(const char* _Mode)
{
    fopen_s(&File, Path, _Mode);

    if (File == nullptr)
        MSGASSERT("��ȿ���� ���� Path�Դϴ�.");
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
