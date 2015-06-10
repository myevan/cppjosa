#include "myevan_korean.h"

namespace Myevan { 

Korean::Josa::Josa()
: _josaRegex(U("\\(이\\)가|\\(와\\)과|\\(을\\)를|\\(은\\)는|\\(아\\)야|\\(이\\)여|\\(으\\)로|\\(이\\)라"))
{
    InsertJosaPatternPair(U("(이)가"), U("이"), U("가"));
    InsertJosaPatternPair(U("(와)과"), U("과"), U("와"));
    InsertJosaPatternPair(U("(을)를"), U("을"), U("를"));
    InsertJosaPatternPair(U("(은)는"), U("은"), U("는"));
    InsertJosaPatternPair(U("(아)야"), U("아"), U("야"));
    InsertJosaPatternPair(U("(으)로"), U("으로"), U("로"));
    InsertJosaPatternPair(U("(이)여"), U("이여"), U("여"));
    InsertJosaPatternPair(U("(이)라"), U("이라"), U("라"));
}

void Korean::Josa::Replace(const std::wstring& srcText, std::wstring& outText)
{
    outText.clear();
    outText.reserve(srcText.size());

    std::wstring::const_iterator srcTextEnd = srcText.end();
    std::wstring::const_iterator srcTextBegin = srcText.begin();
    std::wstring::const_iterator srcTextIter = srcTextBegin;

    std::regex_constants::match_flag_type flags = std::regex_constants::match_default;
    std::match_results<std::wstring::const_iterator> what;
    while(std::regex_search(srcTextIter, srcTextEnd, what, _josaRegex, flags))
    {
        outText.append(srcTextIter, what[0].first);

        std::wstring josaKey(what[0].first, what[0].second);
        if (what[0].first == srcTextBegin)
        {
            outText.append(josaKey);
        }
        else
        {
            JosaPatternPaird::iterator f = _josaPatternPaird.find(josaKey);
            if (f == _josaPatternPaird.end())
            {
                outText.append(josaKey);
            }
            else
            {
                const JosaPair& josaPair = f->second;
                std::wstring::const_iterator srcTextPrev = what[0].first;
                srcTextPrev--;

                wchar_t prevChar = *srcTextPrev;
                outText.append(ChooseJosa(prevChar, josaKey, josaPair));
            }
        }
       
        srcTextIter = what[0].second;
        flags |= std::regex_constants::match_prev_avail;
        // CHEKCME::  match_not_bob for c++
        // flags |= std::regex_constants::match_not_bob;
    }
    outText.append(srcTextIter, srcTextEnd);
}

void Korean::Josa::InsertJosaPatternPair(const std::wstring& pattern, const std::wstring& first, const std::wstring& second)
{
    _josaPatternPaird.insert(JosaPatternPaird::value_type(pattern, JosaPair(first, second)));
}

const std::wstring& Korean::Josa::ChooseJosa(wchar_t prevChar, const std::wstring& josaKey, const JosaPair& josaPair)
{
    // 한글 코드 영역(가 ~ 힣) 이 아닌 경우
    if (prevChar < 0xAC00 || prevChar > 0xD7A3) 
        return josaPair.second;

    int localCode = prevChar - 0xAC00; // 가~ 이후 로컬 코드 
    int jongCode = localCode % 28;

    // 이전 글자에 종성이 없는 경우
    if (jongCode == 0)
        return josaPair.second;

    static std::wstring euroJosaKey(U("(으)로"));
    if (josaKey == euroJosaKey)
    {
        if (jongCode == 8) // ㄹ 종성 예외 처리
            return josaPair.second;
    }

    return josaPair.first;
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

