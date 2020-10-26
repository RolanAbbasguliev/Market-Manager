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
        stock.MCreateMarket();
        break;
      }
      case 2: // Create product
      {
        stock.MCreateProduct();
        break;
      }
      case 3: //Fill in market
      {
        stock.MFillIn();
        break;
      }
      case 4: //Search market with cheapest product
      {
        stock.MCheapProd();
        break;
      }
      case 5: // Money handle
      {
        stock.MMoneyHand();
        break;
      }
      case 6:  // Buy product
      {
        stock.MBatch();
        break;
      }
      case 7: //Search cheapest market
      {
        stock.MCheapMark();
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
        cout << "press any key to exit...\n";
        cin.ignore();
        cin.get();
        break;
      }
    }
  }
  return 0;
}
