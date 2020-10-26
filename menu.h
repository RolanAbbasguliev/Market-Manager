#ifndef MARKET_MANAGER_MENU_H
#define MARKET_MANAGER_MENU_H

#include "stock.h"

class Menu
{
public:
  static void print()
  {
    cout << "============== MARKET MANAGER ==============\n";
    cout << "[1] - [Create market]\n";
    cout << "[2] - [Create product]\n";
    cout << "[3] - [Fill in market]\n";
    cout << "[4] - [Search market with cheapest product]\n";
    cout << "[5] - [Money handle]\n";
    cout << "[6] - [Buy a batch of products in the store]\n";
    cout << "[7] - [Search cheapest market]\n";
    //cout << "[8] - [Get info about the market/product]\n";
    //cout << "[9] - [Generate objects and fill in]";
    cout << "[0] - [Exit]\n";
    cout << "============================================\n";
  }
  static int start();
};
#endif //MARKET_MANAGER_MENU_H
