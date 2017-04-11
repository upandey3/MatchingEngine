#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#define PRICE 0
#define QTY 1
#define BUY 2

typedef int price;
typedef int amount;
typedef int orderId;
typedef int orderDetails;

using std::map;
using std::unordered_map;
using std::vector;

class MatchingEngine{

public:
    MatchingEngine(map<price, amount, std::greater<int>> bTable, map<price, amount, std::greater<int>> sTable);
    int addLimitOrder(int orderId, int price, int qty, bool buy);
    int cancelLimitOrder(int orderId);
    void printOrderBook();
    void printOrdersTable();

private:
    void limitOrderAdded(int orderId, int price, int qty);
    void limitOrderCancelled(int orderId);
    void limitOrderTraded(int orderId, int price, int tradedQty);

    map<price, amount, std::greater<int>> buy_table, sell_table;
    unordered_map<orderId, vector<orderDetails>> orders_table;


};

#endif
