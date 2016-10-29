//---------------------------------------------------------------------------
#ifndef BASE_FILE_HELPER_H_
#define BASE_FILE_HELPER_H_
//---------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <cstring>
//---------------------------------------------------------------------------
namespace base
{

class FileHelper 
{
public:
    FileHelper()
    :   fp_(0)
    {
    }
    ~FileHelper()
    {
        Close();
    }
    FileHelper(const FileHelper&) =delete;
    FileHelper operator=(const FileHelper&) =delete;

    bool Open(const std::string& file_path, bool truncate=false)
    {
        const char* mode = truncate ? "wb" : "ab";
        fp_ = ::fopen(file_path.c_str(), mode);
        if(0 == fp_)
            return false;

        path_ = file_path;
        return true;
    }

    void Flush(bool sync=false)
    {
        ::fflush_unlocked(fp_);
        if(sync)
            fsync(::fileno(fp_));
    }

    void Close()
    {
        if(fp_)
        {
            ::fclose(fp_);
            fp_ = 0;
        }
    }

    bool Write(const void* dat, size_t len)
    {
        //写磁盘一般不会写失败,除非硬盘真不够或者账号可以使用的空间已满
        size_t wlen = ::fwrite_unlocked(dat, 1, len, fp_);
        if(wlen != len)
        {
            char buf[64];
            fprintf(stderr, "AppendFile::Append() failed: %s\n", strerror_r(ferror(fp_), buf, sizeof(buf)));
            return false;
        }

        return true;
    }

    //Flush befor call
    size_t Size()
    {
        struct stat st;
        if(-1 != fstat(fileno(fp_), &st))
            return static_cast<size_t>(st.st_size);

        return 0;
    }

    const std::string& path() { return path_; }

private:
    FILE* fp_;
    std::string path_;
};

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_FILE_HELPER_H_
