#include "myevan_korean.h"

namespace Myevan { 

Korean::Josa::Josa()
: _josaRegex(U("\\(이\\)가|\\(와\\)과|\\(을\\)를|\\(은\\)는|\\(으\\)로"))
{
    InsertJosaPatternPair(U("(이)가"), U("이"), U("가"));
    InsertJosaPatternPair(U("(와)과"), U("과"), U("와"));
    InsertJosaPatternPair(U("(을)를"), U("을"), U("를"));
    InsertJosaPatternPair(U("(은)는"), U("은"), U("는"));
    InsertJosaPatternPair(U("(으)로"), U("으로"), U("로"));
}

void Korean::Josa::Replace(const std::wstring& srcText, std::wstring& outText)
{
    outText.clear();
    outText.reserve(srcText.size());

    std::wstring::const_iterator srcTextEnd = srcText.end();
    std::wstring::const_iterator srcTextBegin = srcText.begin();
    std::wstring::const_iterator srcTextIter = srcTextBegin;

    boost::match_flag_type flags = boost::match_default;
    boost::match_results<std::wstring::const_iterator> what;
    while(boost::regex_search(srcTextIter, srcTextEnd, what, _josaRegex, flags))
    {
        outText.append(srcTextIter, what[0].first);

        std::wstring josa(what[0].first, what[0].second);
        if (what[0].first == srcTextBegin)
        {
            outText.append(josa);
        }
        else
        {
            JosaPatternPaird::iterator f = _josaPatternPaird.find(josa);
            if (f == _josaPatternPaird.end())
            {
                outText.append(josa);
            }
            else
            {
                const JosaPair& pair = f->second;
                std::wstring::const_iterator srcTextPrev = what[0].first;
                srcTextPrev--;

                wchar_t prevChar = *srcTextPrev;
                if (HasJong(prevChar))
                {
                    outText.append(pair.first);
                }
                else
                {
                    outText.append(pair.second);
                }
            }
        }
       
        srcTextIter = what[0].second;
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    outText.append(srcTextIter, srcTextEnd);
}

void Korean::Josa::InsertJosaPatternPair(const std::wstring& pattern, const std::wstring& first, const std::wstring& second)
{
    _josaPatternPaird.insert(JosaPatternPaird::value_type(pattern, JosaPair(first, second)));
}

bool Korean::Josa::HasJong(wchar_t inChar)
{
    if (inChar >= 0xAC00 && inChar <= 0xD7A3) // 가 ~ 힣
    {
        int localCode = inChar - 0xAC00; // 가~ 이후 로컬 코드 
        int jongCode = localCode % 28;
        if (jongCode > 0)
        {
            if (jongCode == 8) // ㄹ 종성 예외 처리
                return false;
            else
                return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

Korean::Josa& Korean::GetJosaInstance()
{
    static Korean::Josa josa;
    return josa;
}

std::wstring Korean::U(const char* mbcs)
{
    return System::Text::UTF8Encoding.GetString(mbcs);
}

void Korean::ReplaceJosa(const std::wstring& srcText, std::wstring& outText)
{
    Korean::Josa& josa = GetJosaInstance();
    josa.Replace(srcText, outText);
}

std::wstring Korean::ReplaceJosa(const std::wstring& srcText)
{
    std::wstring outText;
    Korean::Josa& josa = GetJosaInstance();
    josa.Replace(srcText, outText);
    return outText;
}

} // end_of_namespace Myevan

