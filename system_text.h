#ifndef _SYSTEM_TEXT_H_
#define _SYSTEM_TEXT_H_

#include <boost/shared_ptr.hpp>
#include <boost/locale.hpp>
#include <boost/archive/detail/utf8_codecvt_facet.hpp>

namespace System { 

class Text 
{
public:
    class Encoding
    {
        public:
            Encoding(std::locale locale)
                : _locale(locale)
            {
            }

            std::wstring GetString(char const* chars, size_t charSize)
            {
                // http://cpplog.tistory.com/19
                typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
                codecvt_t const& codecvt = std::use_facet<codecvt_t>(_locale);
                std::mbstate_t state = std::mbstate_t();
                std::vector<wchar_t> buf(charSize + 1);
                char const* in_next = chars;
                wchar_t* out_next = &buf[0];
                std::codecvt_base::result r = codecvt.in(state, 
                        chars, chars + charSize, in_next, 
                        &buf[0], &buf[0] + buf.size(), out_next);
                if (r == std::codecvt_base::error)
                    throw std::runtime_error("can't convert string to wstring");   
                return std::wstring(&buf[0]);
            }
            std::wstring GetString(std::vector<char> const& buf)
            {
                return GetString(&buf[0], buf.size());
            }
            std::wstring GetString(std::string const& buf)
            {
                return GetString(buf.c_str(), buf.size());
            }

            const char* GetBytes(std::wstring const& str, std::vector<char>& buf)
            {
                // http://cpplog.tistory.com/19
                typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
                codecvt_t const& codecvt = std::use_facet<codecvt_t>(_locale);
                std::mbstate_t state = std::mbstate_t();

                buf.clear();
                buf.resize((str.size() + 1) * codecvt.max_length());
                wchar_t const* in_next = str.c_str();
                char* out_next = &buf[0];
                std::codecvt_base::result r = codecvt.out(state, 
                        str.c_str(), str.c_str() + str.size(), in_next, 
                        &buf[0], &buf[0] + buf.size(), out_next);
                if (r == std::codecvt_base::error)
                    throw std::runtime_error("can't convert wstring to string");   
                return &buf[0];
            }
            const char* GetBytes(std::wstring const& str, std::string& buf)
            {
                std::vector<char> cvec;
                GetBytes(str, cvec);
                buf.assign(&cvec[0], cvec.size());
                return &buf[0];
            }

        private:
            std::locale _locale;
    };

    static Encoding UTF8Encoding;//(std::locale(std::locale(), new boost::archive::detail::utf8_codecvt_facet));

}; // end_of_class Text

} // end_of_namespace System

#endif
