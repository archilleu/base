//---------------------------------------------------------------------------
#ifndef BASE_JSON_CHAR_READER_H_
#define BASE_JSON_CHAR_READER_H_
//---------------------------------------------------------------------------
#include <string>
#include <assert.h>
//---------------------------------------------------------------------------
namespace base
{

namespace json
{

class CharReader
{
public:
    CharReader()
    :   pos_(0)
    {
    }
    ~CharReader()
    {
    }

    void set_dat(std::string&& dat) { dat_ = std::move(dat); }

    bool HasMore() { return pos_ < dat_.size(); }
    size_t Remain() { return dat_.size() - pos_; }

    char Peek()
    {
        assert(true == HasMore());
        
        return dat_[pos_];
    }

    char Next()
    {
        assert(true == HasMore());

        char c = dat_[pos_];
        ++pos_;

        return c;
    }

    std::string Next(size_t size)
    {
        assert((pos_+size) <= dat_.size());

        std::string val(dat_.data()+pos_, size);
        pos_ += size;

        return val;
    }

private:
    size_t pos_;
    std::string dat_;
};

}//namespace json

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_JSON_CHAR_READER_H_
