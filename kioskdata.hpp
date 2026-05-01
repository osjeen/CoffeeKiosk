#include"menudata.hpp"
#include"orderdata.hpp"

class KioskData{
    private:
    int profit;
    public:
    std::vector<Menu> menuList;
    OrderData orderData;

    //주문 과정
    void TypeQuery(int query);
    int GetMenu(std::string label);
    void SetNewOrder(int indx);

    Order cur_order;

    //수동 메뉴추가
    void AddMenu();

    //이익
    int getProfit(){
        return profit;
    }
    void addProfit(int val){
        profit+=val;
    }
};