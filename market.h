//
// Created by Rolan Abbasguliev on 18.10.2020.
//

#ifndef MARKET_MANAGER_MARKET_H
#define MARKET_MANAGER_MARKET_H

#include "product.h"
#include <map>


class Market
{
private:
  static int mid;
  int id;
public:
  map <int, Product> productInfo;
  string name;
  string address;
public:
  Market(string _name, string _address);
  void AddProduct(Product _product);
  int BuyProduct(Product _product, int quantity);  // returns spending money
  int GetId();

};

#endif //MARKET_MANAGER_MARKET_H
