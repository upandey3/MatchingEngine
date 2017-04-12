#include "TestME.h"

TestME::TestME(){
    demo_orderId = 3000;
    priceMap bTable = {{98, 50},{99, 1},{97, 8}};
    priceMap sTable = {{103, 20},{101, 10},{102, 5}};
    MatchingEngine a(bTable, sTable);
    engine = a;
}
void TestME::test_init(){

    std::cout << "Initializing tests..."<< std::endl;

    std::cout << "Initial Order Book and Order Table: "<< std::endl;
    printTables();

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test_init2();
    test7();
}
void TestME::addBuyOrder(int price, int amount){
    std::cout << "Adding a buy limit order - " << "OrderId: " << demo_orderId << ", Price: " << price <<", Qty: "<< amount << std::endl;
    if (-1 == engine.addLimitOrder(demo_orderId++, price, amount, true)){
        std::cout << "\nOperation failed. Either invalid orderID or price\n" << std::endl;
        return;
    }
    printTables();
}
void TestME::removeBuyOrder(int demo_orderId){
    std::cout << "Removing a buy limit order - " << "OrderId: " << demo_orderId << std::endl;
    if (-1 == engine.cancelLimitOrder(demo_orderId)){
        std::cout << "\nOperation failed. Either invalid orderID or price\n" << std::endl;
        return;
    }
    printTables();

}
void TestME::addSellOrder(int price, int amount){
    std::cout << "Adding a sell limit order - " << "OrderId: " << demo_orderId << ", Price: " << price <<", Qty: "<< amount << std::endl;
    if (-1 == engine.addLimitOrder(demo_orderId++, price, amount, false)){
        std::cout << "\nOperation failed. Either invalid orderID or price\n" << std::endl;
        return;
    }
    printTables();

}
void TestME::removeSellOrder(int demo_orderId){
    std::cout << "Removing a sell limit order - " << "OrderId: " << demo_orderId << std::endl;
    if (-1 == engine.cancelLimitOrder(demo_orderId)){
        std::cout << "\nOperation failed. Either invalid orderID or price\n" << std::endl;
        return;
    }
    printTables();
}
void TestME::printTables(){
    //std::cout << "Printing current tables..."<< std::endl;
    engine.printOrderBook();
    engine.printOrdersTable();

}
void TestME::test1(){
    std::cout << "-------- Test 1 -----------" <<  std::endl << "---------------------------" <<  std::endl;
    addBuyOrder(96, 15);
    removeBuyOrder(demo_orderId - 1);
}
void TestME::test2(){
    std::cout << "-------- Test 2 -----------" << std::endl << "---------------------------" <<  std::endl;;
    addBuyOrder(96, 15);
    addBuyOrder(96, 10);
    removeBuyOrder(demo_orderId - 1);
}
void TestME::test3(){
    std::cout << "-------- Test 3 -----------" << std::endl << "---------------------------" <<  std::endl;;
    addSellOrder(104, 10);
    removeSellOrder(demo_orderId - 1);
}
void TestME::test4(){
    std::cout << "-------- Test 4 -----------" << std::endl << "---------------------------" <<  std::endl;;
    addSellOrder(104, 20);
    addSellOrder(104, 10);
    removeSellOrder(demo_orderId - 2);
}
void TestME::test5(){
    std::cout << "-------- Test 5 (bad price/qty input)-----" << std::endl << "------------------------------------------" <<  std::endl;;
    addSellOrder(-104, 20);
    addBuyOrder(94, -10);

}
void TestME::test6(){
    std::cout << "\n-------- Test 6 (bad orderID input)-----" << std::endl << "-----------------------------------------" <<  std::endl;;
    removeSellOrder(4000);
    removeBuyOrder(4000);
}
void TestME::test_init2(){
    priceMap bTable = {{98, 10},{96, 20}};
    priceMap sTable = {{100, 20},{99, 15},{101, 10}};
    MatchingEngine a(bTable, sTable);
    engine = a;
    std::cout << "\n--------------------------------------------------\nInitializing new Order Book for testing trade..." << std::endl;
    printTables();

}
void TestME::test7(){
    std::cout << "------- Test 7 - TRADE ------------" << std::endl << "-----------------------------------" <<  std::endl;
    addSellOrder(98, 10);
    addBuyOrder(98, 10);
    addBuyOrder(99, 5);
    addBuyOrder(100, 20);
    addSellOrder(100, 10);
    addSellOrder(99, 10);
    addBuyOrder(100, 35);
    addSellOrder(95, 45);
}
