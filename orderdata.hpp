#include<iostream>
#include<vector>
#include <algorithm>
#include <queue>

struct OrderCell{
    int indx,option,delay,price;
};
struct Order{
    std::vector<OrderCell> cells;
    int id;
    int delay_total;
    int price_total;
    void AddCell(OrderCell orderCell){
        cells.push_back(orderCell);
        delay_total+=orderCell.delay;
        price_total+=orderCell.price;
    }

    bool operator<(const Order& other) const {
        return delay_total < other.delay_total;
    }
};

class OrderData{
    private:
    std::deque<Order> orders;

    public:
    int order_cnt(){
        return orders.size();
    }
    void AddOrder(Order order){
        orders.push_back(order);
    }
    void Init_Sim(){
        //delay_total기준으로 정리
        std::sort(orders.begin(), orders.end());
    }
    Order PrepareOrder(int cur_tick){
        Order val;
        val.delay_total=-1;//sentiel value
        if(orders[0].delay_total<=cur_tick){
            val=orders[0];
            orders.pop_front();
        }
        return val;
    }
};