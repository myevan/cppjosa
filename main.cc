#include "myevan_korean.h"

int main()
{
    std::wstring dstText;
    std::wstring srcText = Myevan::Korean::U("아노아(은)는 자루(와)과 오리(을)를 칭송하고 절(으)로 들어갔습니다.");
    Myevan::Korean::ReplaceJosa(srcText, dstText);

    std::vector<char> buf;
    puts(System::Text::UTF8Encoding.GetBytes(srcText, buf));
    puts(System::Text::UTF8Encoding.GetBytes(dstText, buf));

    return 0;
}


