#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

#define PRICE 0
#define QTY 1
#define BUY 2

typedef int price;
typedef int amount;
typedef int orderId;
typedef int orderDetails;
typedef std::map<price, amount, std::greater<int>> priceMap;

using std::unordered_map;
using std::vector;
using std::string;

struct orderDet_t{
    int price;
    int quantity;
    int buy;
    orderDet_t(){}
    orderDet_t(int a, int b, int c): price(a), quantity(b), buy(c){}
};

class MatchingEngine{
public:
    /* Constructors */
    MatchingEngine();
    MatchingEngine(priceMap bTable, priceMap sTable);

    /* Functions for adding and cancelling limit orders */
    int addLimitOrder(int orderId, int price, int qty, bool buy);
    int cancelLimitOrder(int orderId);

    /* Prints the order book. Used for testing */
    void printOrderBook();
    /* Prints the order_tables entries(list of all the orders) */
    void printOrdersTable();
    /* Prints the buy and sell tables separately (for testing)) */
    void printBuySellTables();

private:
    /* Functions called by the exchange on a successful add, cancel or trade */
    void limitOrderAdded(int orderId, int price, int qty);
    void limitOrderCancelled(int orderId);
    void limitOrderTraded(int orderId, int price, int tradedQty);

    /* Helper function for addLimitOrder to detect and execute potential trade */
    int executeTrade();

    /* Tables mapping price as a key to buy amounts and sell amounts */
    priceMap buy_table, sell_table;
    /* A map of orderID's to array of price, amount and buy flag, updated on add & cancel */
    //unordered_map<orderId, vector<orderDetails>> orders_table;
    unordered_map<orderId, orderDet_t> orders_table;

};

#endif
