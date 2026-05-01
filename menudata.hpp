#include<iostream>
#include<vector>
struct Menu_SimData{
    int delay;
};

typedef struct Menu_SimData Menu_SimData;

struct Menu_KioskData{
    int price;
    std::string label;
};

typedef struct Menu_KioskData Menu_KioskData;

enum Menu_QueryType{
    Coffee=0,
    NonCoffee=1,
    Tea=2,
    Bakery=3
};

class Menu{
    private:
    Menu_KioskData kiosk_data;
    int option_force;//옵션 강제변수

    public:
    //query데이터
    Menu_QueryType queryType;
    bool is_new_menu;//Query 4로 검색,5는 전체

    //시뮬레이션 데이터
    Menu_SimData sim_data;

    void ForceOption(int *opt){
        //잘못된 옵션이 있을때 메뉴의 option_force를 or연산으로 고침
        *opt=option_force|(*opt);
    }
    Menu_KioskData GetData(){
        return kiosk_data;
    }

    Menu(int price, int delay, Menu_QueryType queryType, std::string label, int option_force, bool is_new_menu)
        : queryType(queryType), option_force(option_force), is_new_menu(is_new_menu) {
        kiosk_data.price = price;
        kiosk_data.label = label;
        sim_data.delay = delay;
    }
};