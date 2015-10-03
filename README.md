cppjosa
=======
원 버전(https://github.com/myevan/cppjosa)을 Windows + Visual Studio 2015에서 동작하도록 약간 수정한 버전.
원 버전은 c++11 기반 한글 조사 처리. 맥에서만 빌드 및 실행 테스트되었다.

## 수정된 부분
- 소스 파일의 인코딩 변경
    - 원 버전은 UTF-8(Bom 없음)이지만 VS에서는 인코딩 문제로 컴파일 실패
    - '유니코드 코드페이지 1200'으로 변경
- std::locale("ko_KR.UTF-8") 문제. Windows에는 "ko_KR.UTF-8"을 지원하지 않음
    - 프리프로세스를 이용하여 윈도우 플랫폼에서 빌드할 때는 std::locale("Korean")을 사용하도록 변경
    - 이 문제는 아래의 링크 글을 참고하기 바란다. http://includes.egloos.com/v/1504676, http://sjc333.egloos.com/3137637

## Visual Studio 실행
- WinTest 디렉토리의 WinTest.sln을 실행하면 된다.



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
