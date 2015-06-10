cppjosa
=======

c++11 기반 한글 조사 처리입니다. 현재 맥에서만 빌드 및 실행 테스트되었습니다.

## 예제

#### 코드

    #include "myevan_korean.h"

    int main()
    {
        std::wstring dstText;
        std::wstring srcText = System::Text::UTF8Encoding.GetString("아노아(은)는 자루(와)과 오리(을)를 칭송하고 절(으)로 들어갔습니다.");
        Myevan::Korean::ReplaceJosa(srcText, dstText);

        std::vector<char> buf;
        puts(System::Text::UTF8Encoding.GetBytes(srcText, buf));
        puts(System::Text::UTF8Encoding.GetBytes(dstText, buf));

        return 0;
    }


#### 빌드

    $ make

#### 실행

    $ ./cppjosa.exe
    아노아(은)는 자루(와)과 오리(을)를 칭송하고 절(으)로 들어갔습니다.
    아노아는 자루와 오리를 칭송하고 절로 들어갔습니다.
