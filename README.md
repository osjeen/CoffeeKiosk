# CoffeeKiosk

*설계 설명서

*메뉴 입력,주문 처리,시뮬레이션(주문 내역 확인) 순서로 진행.

*MenuData들은 SimData와 KioskData로 Is-A관계로 상속.

*OrderData는 각 주문과 주문의 세부 정보를 Has-A관계로 가짐.

**필수 활용 요소

클래스:위에서 언급한 구조체들,상속관계:MenuData,조건문:쿼리 처리,Explicit 형변환:예외처리,예외처리:수량 오류,잔액부족 상황