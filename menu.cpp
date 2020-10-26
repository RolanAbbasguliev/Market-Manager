#include "menu.h"
#include "algorithm"
#include "unistd.h"
#include <vector>
#include "stock.h"




int Menu::start()
{
  Stock stock;
  int run = 1;
  while (run)
  {
    system("clear");
    print();
    cout << "INPUT: ";

    int key;
    cin >> key;
    switch (key)
    {
      case 1: // Create market
      {
        stock.First();
        break;
      }
      case 2: // Create product
      {
        stock.Second();
        break;
      }
      case 3: //Fill in market
      {
        stock.Third();
        break;
      }
      case 4: //Search market with cheapest product
      {
        stock.Quarter();
        break;
      }
      case 5: // Money handle
      {
        stock.Fifth();
        break;
      }
      case 6:  // Buy product
      {
        stock.Six();
        break;
      }
      case 7: //Search cheapest market
      {
        stock.Seven();
        break;
      }
      case 0:
      {
        run = 0;
        break;
      }
      default:
      {
        cout << "No such key\n";
        break;
      }
    }
  }
  return 0;
}
