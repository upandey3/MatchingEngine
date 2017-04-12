#include "MatchingEngine.h"

/* Default Constructor*/
MatchingEngine::MatchingEngine(){}
/* Constructor that initialize buy and sell tables in the order book*/
MatchingEngine::MatchingEngine(priceMap bTable, priceMap sTable): buy_table(bTable), sell_table(sTable){}

/* Uses the buy flag to distinguish whether it is a buy or sell limit order.
   Makes an entry into the appropriate table(buy or sell). Records the orderId
   and details in orders_table and executes a potential trade.
   INPUT: orderId: used in the orders_table and for canceling orders_table
          price: price of the share
          qty: quanity of the share
          buy: boolean value for whether it is a buy limit order,
               if false it is a sell limit order
   RETURN VALUE: 0 on success, -1 on failure                                     */
int MatchingEngine::addLimitOrder(int orderId, int price, int qty, bool buy){
    //If the orderId has been used already or if price is less than 0, it's an invalid request
    if (price < 0 || orders_table.find(orderId) != orders_table.end() || qty <= 0)
        return -1;

    if (buy)
        buy_table[price] += qty;
    else
        sell_table[price] += qty;

    int tradedQty = executeTrade();
    if (tradedQty) // If trade is successful,
        limitOrderTraded(orderId, price, tradedQty);
    else { // else limit order is added to the order book
        orders_table[orderId] = vector<orderDetails> {price, qty, buy};
        limitOrderAdded(orderId, price, qty);
    }
    std::cout << "Traded quantity is " << tradedQty << std::endl;
    return 0;
}

/* Helper function for addLimitOrder to detect and execute
   potential trade.
   RETURN VALUE: the quantity traded if there is a possible trade,
                 0 otherwise.                                 */
int MatchingEngine::executeTrade(){

    auto ib = buy_table.begin(); // Buy limit order iterator
    auto is = sell_table.rbegin(); // Sell limit order iterator
    //if buy limit order price is less than the sell limit order price, no trade
    if (ib == buy_table.end() || is == sell_table.rend() || ib->first < ib->first)
        return 0;
    int sellLimit = is->first, buyLimit = ib->first, tradedQty = 0, minQty = 0;
    //while there is a buy order above sell limit and a sell order below buy limit
    while (ib->first >= sellLimit && is->first <= buyLimit){

        minQty = std::min(ib->second, is->second);
        tradedQty += minQty;
        ib->second -= minQty;
        is->second -= minQty;

        if (ib->second == 0){
            buy_table.erase(ib->first);
            ib = buy_table.begin();
        }
        if (is->second == 0){
            sell_table.erase(is->first);
            is = sell_table.rbegin();
        }
        if (ib == buy_table.end() || is == sell_table.rend()) break;
    }
    return tradedQty;
}

/* Takes an orderID, looks it up in the order_tables map, retrieves the
   details(price, amount and buy flag) and removes it from the buy or sell
   tables accordingly in the orderbook.
   RETURN VALUE: 0 on success, -1 on failure                            */
int MatchingEngine::cancelLimitOrder(int orderId){
    //If the orderId has not been used before, it's an invalid request
    if (orders_table.find(orderId) == orders_table.end())
        return -1;
    vector<orderDetails> order = orders_table[orderId];

    if (order[BUY]){

        if ((buy_table[order[PRICE]] -= order[QTY]) <= 0)
            buy_table.erase(order[PRICE]);

    } else {

        if ((sell_table[order[PRICE]] -= order[QTY]) <= 0)
            sell_table.erase(order[PRICE]);
    }
    orders_table.erase(orderId);
    limitOrderCancelled(orderId);
    return 0;

}
/* Prints the order book. Used for testing */
void MatchingEngine::printOrderBook(){

    auto it = buy_table.end();
    --it;
    int minPrice = it->first;
    auto is = sell_table.begin();
    int maxPrice = is->first;

    std::cout << "\n   Order Book " << std::endl;
    for (int i = maxPrice; i >= minPrice; i--){

        string s = "";
        // Print buy amounts
        auto it2 = buy_table.find(i);
        if (it2 == buy_table.end())
            std::cout << "0     ";
        else
            std::cout << it2->second << "     " ;

        //Print price
        std::cout << i << "      ";

        //Print sell amounts
        auto it3 = sell_table.find(i);
        if (it3 == sell_table.end())
            std::cout << "0" << std::endl;
        else
            std::cout << it3->second << ""  << std::endl;
    }
}

/* Prints the order_tables entries(list of all the orders) */
void MatchingEngine::printOrdersTable(){

    std::cout << "\n         Orders Table" << std::endl;
    std::cout << "OrderID" << "   Price" << "   Amount" << "   Buy Flag" << std::endl;
    for (auto key : orders_table)
        std::cout << key.first << "       " << key.second[PRICE]
        << "        " << key.second[QTY] << "        " << key.second[BUY] << std::endl;
    std::cout << std::endl << std::endl;
}

/* Prints the buy and sell tables separately (for testing)) */
void MatchingEngine::printBuySellTables(){

    std::cout << "  Buy Table" << std::endl;
    for (auto a : buy_table)
        std::cout << "  " << a.first << " : " << a.second << std::endl;
    std::cout << "\n  Sell Table" << std::endl;
    for (auto b : sell_table)
        std::cout << "  " << b.first << " : " << b.second << std::endl;

}

/* Functions called by the exchange on a successful add, cancel or trade */
void MatchingEngine::limitOrderAdded(int orderId, int price, int qty){
    /* STUBBED OUT */
}

void MatchingEngine::limitOrderCancelled(int orderId){
    /* STUBBED OUT */
}

void MatchingEngine::limitOrderTraded(int orderId, int price, int tradedQty){
    /* STUBBED OUT */
}
