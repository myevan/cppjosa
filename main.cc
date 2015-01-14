#include "myevan_korean.h"

bool test(const char* srcTextz, const char* correctTextz)
{
    std::wstring dstText;
    std::wstring srcText = System::Text::UTF8Encoding.GetString(srcTextz);
    Myevan::Korean::ReplaceJosa(srcText, dstText);

    std::vector<char> buf;

    std::wstring correctText = System::Text::UTF8Encoding.GetString(correctTextz);
    if (dstText == correctText)
    {
        printf("before : %s\n", System::Text::UTF8Encoding.GetBytes(srcText, buf));
        printf("after  : %s\n", System::Text::UTF8Encoding.GetBytes(dstText, buf));
        puts("");
        return true;
    }

    puts("FAILURE!");
    puts("");
    printf("before : %s\n", System::Text::UTF8Encoding.GetBytes(srcText, buf));
    printf("after  : %s\n", System::Text::UTF8Encoding.GetBytes(dstText, buf));
    printf("correct: %s\n", System::Text::UTF8Encoding.GetBytes(correctText, buf));
    puts("");
    puts("");
    return false;
}

int main()
{
    test(
        "아노아(이)가 공격했다", 
        "아노아가 공격했다");

    test(
        "주펫(이)가 공격했다",
        "주펫이 공격했다");

    test(
        "아노아(은)는 자루(와)과 오리(을)를 칭송하고 절(으)로 들어갔습니다.",
        "아노아는 자루와 오리를 칭송하고 절로 들어갔습니다.");

    test(
        "네(이)가 잘못했어. 확률(이)가 이상해. 덫(이)가 깔렸어.",
        "네가 잘못했어. 확률이 이상해. 덫이 깔렸어.");

    test(
        "너(와)과 함께 할게. 글(와)과 그림. 빛(와)과 어둠.",
        "너와 함께 할게. 글과 그림. 빛과 어둠.");

    test(
        "수녀(을)를 존경했어. 남자들(을)를 입히다. 버튼(을)를 만지지 마.",
        "수녀를 존경했어. 남자들을 입히다. 버튼을 만지지 마.");

    test(
        "우리(은)는 끝이야. 쌀(은)는 필요없어. 갑옷(은)는 찢었다.",
        "우리는 끝이야. 쌀은 필요없어. 갑옷은 찢었다.");

    test(
        "진우(아)야, 그것도 몰라? 경렬(아)야, 진정해. 상현(아)야, 뭐해?",
        "진우야, 그것도 몰라? 경렬아, 진정해. 상현아, 뭐해?");

    test(
        "진우(이)여, 닥쳐라. 경렬(이)여, 이리 오라. 상현(이)여, 아무 일도 아니다.",
        "진우여, 닥쳐라. 경렬이여, 이리 오라. 상현이여, 아무 일도 아니다.");

    test(
        "부두(으)로 가야 해. 대궐(으)로 가거나. 집(으)로 갈래?",
        "부두로 가야 해. 대궐로 가거나. 집으로 갈래?");

    test(
        "나(이)라고 어쩔 수 있겠니? 별(이)라고 불러줘. 라면(이)라고 했잖아.",
        "나라고 어쩔 수 있겠니? 별이라고 불러줘. 라면이라고 했잖아.");

    return 0;
}


