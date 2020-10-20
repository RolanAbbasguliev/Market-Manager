#ifndef MARKET_MANAGER_PRODUCT_H
#define MARKET_MANAGER_PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product
{
private:
  static int pid;
  int id;
public:
  string name;
  int cost;
  int num;
public:
  Product(string _name, int _cost);
  Product(const Product &_product);
  int GetID()
  {
    return this->id;
  }
};

#endif //MARKET_MANAGER_PRODUCT_H
