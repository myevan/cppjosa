#ifndef _MYEVAN_KOREAN_H_
#define _MYEVAN_KOREAN_H_

#include "system_text.h"

#include <boost/regex.hpp>

namespace Myevan { 

class Korean 
{ 
public:
    class Josa
    {
        public:
            Josa();

            void Replace(const std::wstring& srcText, std::wstring& outText);

        private:
            typedef std::pair<std::wstring, std::wstring> JosaPair;
            typedef std::map<std::wstring, JosaPair> JosaPatternPaird;

        private:
            void InsertJosaPatternPair(const std::wstring& pattern, const std::wstring& first, const std::wstring& second);

        private:
            static bool HasJong(wchar_t inChar);

        private:
            boost::basic_regex<wchar_t> _josaRegex;
            JosaPatternPaird _josaPatternPaird;
    };

    static Josa& GetJosaInstance();

    static std::wstring U(const char* mbcs);

    static void ReplaceJosa(const std::wstring& srcText, std::wstring& outText);

    static std::wstring ReplaceJosa(const std::wstring& srcText);

}; // end_of_class Korean

} // end_of_namespace Myevan

#endif
