
namespace option_convert{

enum Menu_QueryType{
    Coffee=0,
    NonCoffee=1,
    Tea=2,
    Bakery=3
};

/*

LSB부터

0번째:식사/테이크아웃
1번째:아이스/핫
2~3번째(사이즈):
톨(00)/라지(01)/그란데(10)/옵션없음(11)
4~5번째:
디카페인(00),연하게(01),샷추가(10),옵션없음(11)
*/

// 0: 식사/테이크아웃 (1비트)
int set_takeout(int target, int val) {
    return (target & ~0b1) | (val & 0b1);
}

// 1: 아이스/핫 (1비트)
int set_temp(int target, int val) {
    return (target & ~(0b1 << 1)) | ((val & 0b1) << 1);
}

// 2~3: 사이즈 (2비트)
int set_size(int target, int val) {
    // 0b11 << 2 == 0b1100 (12) 위치를 지우고 시작
    return (target & ~(0b11 << 2)) | ((val & 0b11) << 2);
}

// 4~5: 샷/카페인 (2비트)
int set_shot(int target, int val) {
    // 0b11 << 4 == 0b110000 (48) 위치를 지우고 시작
    return (target & ~(0b11 << 4)) | ((val & 0b11) << 4);
}

int get_option_force(int qu){
    return 1;
}

#include <iostream>
#include <string>
#include <vector>

void print_options(int opt) {

    int takeout = (opt & 0b1);           // 0번째 비트
    int temp    = (opt >> 1) & 0b1;      // 1번째 비트
    int size    = (opt >> 2) & 0b11;     // 2~3번째 비트
    int shot    = (opt >> 4) & 0b11;     // 4~5번째 비트

    std::string size_names[] = {"Tall", "Large", "Grande", "No Option"};
    std::string shot_names[] = {"Decaf", "Light", "Add Shot", "No Option"};

    std::cout << "========= 주문 옵션 =========" << std::endl;
    std::cout << "포장 여부: " << (takeout ? "테이크아웃" : "매장식사") << std::endl;
    std::cout << "온도 설정: " << (temp ? "아이스" : "핫") << std::endl;
    std::cout << "사이즈:    " << size_names[size] << std::endl;
    std::cout << "추가 옵션: " << shot_names[shot] << std::endl;
    std::cout << "============================" << std::endl;
}

}

