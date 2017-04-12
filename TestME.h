#ifndef TESTME_H
#define TESTME_H

#include "MatchingEngine.h"

class TestME{
public:
    TestME();
    void test_init();
    void test_init2();

private:
    MatchingEngine engine;
    void addBuyOrder(int price, int amount);
    void removeBuyOrder(int orderId);
    void addSellOrder(int price, int amount);
    void removeSellOrder(int orderId);
    void printTables();
    int demo_orderId;
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();

};

#endif
