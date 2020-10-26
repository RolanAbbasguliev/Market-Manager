#ifndef MARKET_MANAGER_STOCK_H
#define MARKET_MANAGER_STOCK_H


#include "market.h"

class Stock
{
public:
  map <int, Product> productList;
  map <int, Market> marketList;
public:
  void AddMarketToStock(Market _market);
  void AddProductToStock(Product _product);
  int MCreateMarket();
  int MCreateProduct();
  int MFillIn();
  int MCheapProd();
  int MMoneyHand();
  int MBatch();
  int MCheapMark();
};

#endif //MARKET_MANAGER_STOCK_H
