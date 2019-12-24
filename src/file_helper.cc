//---------------------------------------------------------------------------
#include "file_helper.h"
//---------------------------------------------------------------------------
namespace base
{

//---------------------------------------------------------------------------
FileHelper::FileHelper()
:   fp_(nullptr)
{
}
//---------------------------------------------------------------------------
FileHelper::~FileHelper()
{
    Close();
}
//---------------------------------------------------------------------------
void FileHelper::Open(const std::string& file_path, bool truncate)
{
    const char* mode = truncate ? "w+b" : "a+b";
    fp_ = ::fopen(file_path.c_str(), mode);
    if(0 == fp_)
        throw std::fstream::failure("open file:" + file_path + " failed!");

    path_ = file_path;
    return;
}
//---------------------------------------------------------------------------
void FileHelper::Flush(bool sync)
{
    if(fp_)
    {
        ::fflush_unlocked(fp_);
        if(sync)
            fsync(::fileno(fp_));
    }
}
//---------------------------------------------------------------------------
void FileHelper::Close()
{
    if(fp_)
    {
        ::fclose(fp_);
        fp_ = nullptr;
    }
}
//---------------------------------------------------------------------------
void FileHelper::Write(const void* dat, size_t len)
{
    if(fp_)
    {
        //写磁盘一般不会写失败,除非硬盘真不够或者账号可以使用的空间已满
        size_t wlen = ::fwrite_unlocked(dat, 1, len, fp_);
        if(wlen != len)
        {
            throw std::fstream::failure("write failed");
        }
    }

    return;
}
//---------------------------------------------------------------------------
void FileHelper::Write(const std::string& dat)
{
    Write(dat.c_str(), dat.length());
}
//---------------------------------------------------------------------------
void FileHelper::Write(int8_t dat)
{
    Write(reinterpret_cast<void*>(&dat), sizeof(dat));
}
//---------------------------------------------------------------------------
void FileHelper::Write(int16_t dat)
{
    Write(reinterpret_cast<void*>(&dat), sizeof(dat));
}
//---------------------------------------------------------------------------
void FileHelper::Write(int32_t dat)
{
    Write(reinterpret_cast<void*>(&dat), sizeof(dat));
}
//---------------------------------------------------------------------------
void FileHelper::Write(int64_t dat)
{
    Write(reinterpret_cast<void*>(&dat), sizeof(dat));
}
//---------------------------------------------------------------------------
std::string FileHelper::ReadString(size_t len)
{
    if(fp_)
    {
        std::string data(len, 0);
        size_t rlen = ::fread_unlocked(const_cast<char*>((data.data())), 1, len, fp_);
        if(rlen != len)
        {
            data.resize(rlen);
        }
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int8_t FileHelper::ReadInt8()
{
    if(fp_)
    {
        int8_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint8_t), fp_);
        if(rlen != sizeof(uint8_t))
        {
            throw std::fstream::failure("read failed");
        }
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int16_t FileHelper::ReadInt16()
{
    if(fp_)
    {
        int16_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint16_t), fp_);
        if(rlen != sizeof(uint16_t))
        {
            throw std::fstream::failure("read failed");
        }
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int32_t FileHelper::ReadInt32()
{
    if(fp_)
    {
        int32_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint32_t), fp_);
        if(rlen != sizeof(uint32_t))
        {
            throw std::fstream::failure("read failed");
        }
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int64_t FileHelper::ReadInt64()
{
    if(fp_)
    {
        int64_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint64_t), fp_);
        if(rlen != sizeof(uint64_t))
        {
            throw std::fstream::failure("read failed");
        }
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
std::string FileHelper::PeekString(size_t len)
{
    if(fp_)
    {
        std::string data(len, 0);
        size_t rlen = ::fread_unlocked(const_cast<char*>((data.data())), 1, len, fp_);
        if(rlen != len)
        {
            data.resize(rlen);
        }
        ::fseek(fp_, -rlen, SEEK_CUR);
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int8_t FileHelper::PeekInt8()
{
    if(fp_)
    {
        int8_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint8_t), fp_);
        if(rlen != sizeof(uint8_t))
        {
            throw std::fstream::failure("read failed");
        }
        ::fseek(fp_, -rlen, SEEK_CUR);
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int16_t FileHelper::PeekInt16()
{
    if(fp_)
    {
        int16_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint16_t), fp_);
        if(rlen != sizeof(uint16_t))
        {
            throw std::fstream::failure("read failed");
        }
        ::fseek(fp_, -rlen, SEEK_CUR);
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int32_t FileHelper::PeekInt32()
{
    if(fp_)
    {
        int32_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint32_t), fp_);
        if(rlen != sizeof(uint32_t))
        {
            throw std::fstream::failure("read failed");
        }
        ::fseek(fp_, -rlen, SEEK_CUR);
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
int64_t FileHelper::PeekInt64()
{
    if(fp_)
    {
        int64_t data;
        size_t rlen = ::fread_unlocked(reinterpret_cast<char*>(&data), 1, sizeof(uint64_t), fp_);
        if(rlen != sizeof(uint64_t))
        {
            throw std::fstream::failure("read failed");
        }
        ::fseek(fp_, -rlen, SEEK_CUR);
        return data;
    }

    throw std::fstream::failure("read failed");
}
//---------------------------------------------------------------------------
size_t FileHelper::Size()
{
    if(fp_)
    {
        struct stat st;
        if(-1 != fstat(fileno(fp_), &st))
            return static_cast<size_t>(st.st_size);
    }

    return 0;
}
//---------------------------------------------------------------------------

}//namespace base
//---------------------------------------------------------------------------
