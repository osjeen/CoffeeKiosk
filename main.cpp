#include"kioskdata.hpp"
#include"option_convert.hpp"
int setDelay(Menu_QueryType qu){
    return 1;
}

/*
y
americano 0 1000 false
y
praffe 1 2500 true
y
ulong_tea 2 3000 false
y
waffle 3 4000 true
n
*/

void KioskData::AddMenu(){
    std::cout<<std::endl<<"[포맷] 띄어쓰기 구분"<<std::endl<<
    "| 이름 | 종류(0:커피,1:논커피,2:티,3:베이커리) | 가격 | 신메뉴 여부(true/false) |"<<std::endl;

    std::string label;
    int qu,price;
    bool is_new_menu;
    std::cin>>label;
    std::cin>>qu;
    std::cin>>price;
    std::cin>>std::boolalpha>>is_new_menu;
    std::cin>>std::noboolalpha;

    //변수 자동설정

    int delay=setDelay((Menu_QueryType)qu);
    int option_force=option_convert::get_option_force(qu);

    menuList.emplace_back(price,delay,(Menu_QueryType)qu,label,option_force,is_new_menu);
}


void ManuallyAddMenu(KioskData* kioskData){
    std::cout<<"====수동 메뉴 작성===="<<std::endl;
    while(1){
        std::cout<<"작성(y/n)";
        char yorn;
        std::cin>>yorn;
        if(yorn=='n')break;
        kioskData->AddMenu();
    }
}

//주문 프로시저

//쿼리로 찾은 모든 메뉴 출력
void KioskData::TypeQuery(int query){
    for(auto a:menuList){
        if(a.queryType==query
        ||query==5||(a.is_new_menu&&query==4)){
            std::cout<<a.GetData().label<<" "<<a.GetData().price<<std::endl;
        }
    }
}

//라벨링으로 메뉴의 인덱스 반환
int KioskData::GetMenu(std::string label){
    for(int i=0;i<menuList.size();i++){
        if(menuList[i].GetData().label==label)return i;
    }
    return -1;
}

//인덱스,추가적으로 옵션을받아 오더에 오더 셀 추가
void KioskData::SetNewOrder(int indx){
    int option=0;
    cur_order.AddCell(OrderCell{indx,option,menuList[indx].sim_data.delay});
}

void RequestOrder(KioskData* kioskData){
    int t;
    std::cout<<"====주문 받기 시작===="<<std::endl;
    std::cout<<"고객 수:";
    std::cin>>t;
    std::cout<<std::endl;
    for(int i=0;i<t;i++){
        std::cout<<i<<" 번째 주문"<<std::endl;
        while(1){
            int qu;
            std::cout<<"New(4) | 커피(0) | 논커피(1) | 티(2) | 베이커리(3) | 전체(5)"<<std::endl;
            std::cout<<"탭 선택:";
            std::cin>>qu;
            kioskData->TypeQuery(qu);

            std::cout<<"주문할 메뉴 이름(없을시 NONE):";
            std::string label;
            std::cin>>label;
            if(label=="NONE")continue;
            std::cout<<std::endl;

            int indx=kioskData->GetMenu(label);
            if(indx<0)continue;
            kioskData->SetNewOrder(indx);

            //결제
            std::cout<<"결제 하겠습니까?(y/n):";
            char yorn;
            std::cin>>yorn;
            if(yorn=='y'){
                kioskData->orderData.AddOrder(kioskData->cur_order);

                //오더 초기화
                kioskData->cur_order.cells.clear();
                kioskData->cur_order.delay_total=0;
                kioskData->cur_order.id++;
                break;
            }
        }
    }
}

//시뮬레이션
#include <thread>
#include <chrono>
void Simulation(KioskData* kioskData){
    std::cout<<"====시뮬레이션 시작===="<<std::endl;

    kioskData->orderData.Init_Sim();

    std::cout<<"가속모드 설정(y/n):";
    char yorn;
    std::cin>>yorn;

    int tick=(yorn=='y')?10:1000;
    int cur_tick=0;

    while(1){
        if(kioskData->orderData.order_cnt()==0)break;
        std::this_thread::sleep_for(std::chrono::milliseconds(tick));
        Order val=kioskData->orderData.PrepareOrder(cur_tick);

        if(val.delay_total<0){
            std::cout<<".";
        }else{
            std::cout<<
            std::endl<<
            val.id<<"번 고객님,"<<std::endl;

            for(const auto cell:val.cells){
                std::cout<<
                kioskData->menuList[cell.indx].GetData().label
                <<std::endl;
                option_convert::PrintOption(cell.option);
            }
            std::cout<<"총 "<<val.cells.size()<<"개 준비 되었습니다."<<std::endl;
        }

        cur_tick++;
    }
    std::cout<<"====시뮬레이션 종료===="<<std::endl;
    std::cout<<"총 이익:"<<kioskData->getProfit()<<std::endl;
}

int main(){
    KioskData* kioskData=new KioskData;
    std::cout<<"카페 관리 시스템 v0.1"<<std::endl;
    ManuallyAddMenu(kioskData);

    RequestOrder(kioskData);

    Simulation(kioskData);
}