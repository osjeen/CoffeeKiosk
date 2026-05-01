
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

int get_option_force(int qu){
    return 1;
}

void PrintOption(int option){

}
}

