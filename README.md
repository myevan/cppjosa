cppjosa
=======

c++11 기반 한글 조사 처리 입니다. Windows(VS2013, VS2015)와 OS X 에서 빌드 및 테스트 되었습니다.

예제
----

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

#### 결과

    아노아(은)는 자루(와)과 오리(을)를 칭송하고 절(으)로 들어갔습니다.
    아노아는 자루와 오리를 칭송하고 절로 들어갔습니다.


빌드
----

### Windows

VisualStudio 로 WinTest 디렉토리의 WinTest.sln 을 오픈해 빌드합니다.


### OS X / Linux

    $ make
    $ ./cppjosa.exe


참고
---

#### 인코딩

* VisualStudio 에서 utf8-without-bom 인코딩을 지원 하지 못해 utf8-bom 인코딩을 사용합니다.
* c++11 new unicode literals <https://en.wikipedia.org/wiki/C%2B%2B11#New_string_literals>
* `#pragma execution_character_set( "utf-8" )` VS2008 Latest SP, VS2010 Latest SP, VS2013 (VS2012 미지원?!)
* gcc utf8-bom 컴파일 옵션 <http://stackoverflow.com/questions/7899795/is-it-possible-to-get-gcc-to-compile-utf-8-with-bom-source-files>

#### 로케일

* std::locale() 함수의 경우 Windows 에서 `ko_KR.UTF-8` 을 지원하지 않아 `Korean` 을 사용합니다.
* utf8-unicode 변환 <http://includes.egloos.com/v/1504676>
* 윈도우-리눅스 `wchar_t` 공용 사용 <http://sjc333.egloos.com/3137637>

#### 프로젝트 

* 비주얼 스튜디오 통합 프로젝트 <http://stackoverflow.com/questions/29515566/how-do-i-make-a-visual-studio-2015-c-project-compatible-with-visual-studio-201>

