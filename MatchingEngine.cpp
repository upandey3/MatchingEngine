#include "MatchingEngine.h"

MatchingEngine::MatchingEngine(map<price, amount, std::greater<int>> bTable, map<price, amount, std::greater<int>> sTable): buy_table(bTable), sell_table(sTable){}

int MatchingEngine::addLimitOrder(int orderId, int price, int qty, bool buy){

    if (price < 0)
        return -1;

    if (buy)
        buy_table[price] += qty;
    else
        sell_table[price] += qty;

    orders_table[orderId] = vector<orderDetails> {price, qty, buy};
    limitOrderAdded(orderId, price, qty);
    return 0;
}


int MatchingEngine::cancelLimitOrder(int orderId){

    vector<orderDetails> order = orders_table[orderId];
    if (order[BUY]){

        if (buy_table[order[PRICE]] -= order[QTY] <= 0)
            buy_table.erase(order[PRICE]);

    } else {

        if (sell_table[order[PRICE]] -= order[QTY] <= 0)
            sell_table.erase(order[PRICE]);

    }
    orders_table.erase(orderId);
    limitOrderCancelled(orderId);
    return 0;

}


void printOrderBook();
void printOrdersTable();


void MatchingEngine::limitOrderAdded(int orderId, int price, int qty){
    /* STUBBED OUT */
}

void MatchingEngine::limitOrderCancelled(int orderId){
    /* STUBBED OUT */
}

void MatchingEngine::limitOrderTraded(int orderId, int price, int tradedQty){
    /* STUBBED OUT */
}
