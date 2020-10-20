#include "menu.h"
#include "algorithm"
#include "unistd.h"



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
        system("clear");
        string name;
        string address;

        cout << "Input [market] name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Input [market] address: ";
        getline(cin, address);

        Market market(name, address);
        stock.AddMarketToStock(market);

        cout << "Set [market]: " << market.name << ", " << market.address << endl;
        cout << "press any key to exit...\n";
        cin.get();
        break;
      }
      case 2: // Create product
      {
        system("clear");
        string name = "";
        int cost = 0;

        cout << "Input [product] name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Input [product] cost: ";
        cin >> cost;

        if (cost <= 0)
        {
          cout << "error cost value\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }

        Product product(name, cost);
        stock.AddProductToStock(product);

        cout << "Set [product]: " << product.name << ", " << product.cost << "$" << endl;
        cout << "press any key to exit...\n";
        cin.ignore();
        cin.get();

        break;
      }
      case 3: //Fill in market
      {
        system("clear");
        int product_id = -1;
        int market_id = -1;
        int quantity = 0;

        if (stock.marketList.empty())
        {
          system("clear");
          cout << "============== MARKET LIST ==============\n";
          cout << "Empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(!stock.marketList.empty() && "stock.marketList is empty");

        if (stock.productList.empty())
        {
          system("clear");
          cout << "============== PRODUCT LIST ==============\n";
          cout << "Empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(!stock.productList.empty() && "stock.productList is empty");

        system("clear");
        cout << "============== MARKET LIST ==============\n";

        for (int i = 0; i < stock.marketList.size(); i++)
        {
          cout << i + 1 << "] "<< stock.marketList.find(i)->second.name;
          cout << ", " << stock.marketList.find(i)->second.address << "\n";
        }

        int market_number = 0;
        cout << "Enter [market] number: ";
        cin >> market_number;
        market_id = market_number;
        market_id -= 1;

        if (market_number <= 0 || market_number > stock.marketList.size())
        {
          cout << "error no such market at list\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(stock.marketList.find(market_id)->second.GetId() == market_id && "market_id is wrong");

        system("clear");
        cout << "============== PRODUCT LIST ==============\n";
        for (int i = 0; i < stock.productList.size(); i++)
        {
          cout << i + 1 << "] "<< stock.productList.find(i)->second.name;
          cout << ", " << stock.productList.find(i)->second.cost << " $\n";
        }
        int product_number = 0;
        cout << "Enter [product] number: ";
        cin >> product_number;
        product_id = product_number - 1;

        if (product_number <= 0 || product_number > stock.productList.size())
        {
          cout << "error no such product at list\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }

        assert(stock.productList.find(product_id)->second.GetID() == product_id && "product_id is wrong");

        cout << "Set the quantity of [product]: ";
        cin >> quantity;
        stock.productList.find(product_id)->second.num = quantity;    // change product quantity

        cout << "Set the cost ? [y/n]: ";
        string choose;
        cin >> choose;

        if (choose == "y")
        {
          cout << "Input your cost: ";
          int value;
          cin >> value;
          stock.productList.find(product_id)->second.cost = value;
        }
        else if (choose != "n")
        {
          cout << "Error input\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        stock.marketList.find(market_id)->second.AddProduct(stock.productList.find(product_id)->second);
        break;
      }
      case 4: //Search market with cheapest product
      {
        system("clear");
        int product_id = -1;
        int index = -1;
        int min = INT_MAX;
        int _cost = -1;

        if (stock.marketList.empty())
        {
          system("clear");
          cout << "============== MARKET LIST ==============\n";
          cout << "Empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }

        if (stock.productList.empty())
        {
          system("clear");
          cout << "============== PRODUCT LIST ==============\n";
          cout << "Empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }


        cout << "============== PRODUCT LIST ==============\n";
        for (int i = 0; i < stock.productList.size(); i++)
        {
          cout << i + 1 << "] "<< stock.productList.find(i)->second.name;
          cout << ", " << stock.productList.find(i)->second.cost << "$\n";
        }
        assert(!stock.productList.empty() && "stock.productList is empty");

        int product_number = 0;
        cout << "Enter [product] number: ";
        int flag = 0;
        cin >> product_number;
        product_id = product_number - 1;

        if (product_number <= 0 || product_number > stock.productList.size())
        {
          cout << "error no such product at list\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        // Product in market check
        for (int i = 0; i < stock.marketList.size(); i++)
        {
          if (stock.marketList.find(i)->second.productInfo.find(product_id)->second.num == 0)
          {
            cout << "Error: The product was not delivered to the markets!\n";
            cout << "press any key to exit...\n";
            cin.ignore();
            cin.get();
            flag = 1;
          }
        }
        if (flag)
          break;
        assert(stock.productList.find(product_id)->second.GetID() == product_id && "product_id is wrong");

        // Searching for minimal product cost in marketList
        for (int i = 0; i < stock.marketList.size(); i++)
        {
          _cost = stock.marketList.find(i)->second.productInfo.find(product_id)->second.cost;
          if (_cost < min)
          {
            min = _cost;
            index = i;
          }
        }
        assert(stock.marketList.find(index)->second.productInfo.find(product_id)->second.cost == min && "Minial cost product found worng");

        system("clear");
        cout << "============== RESULT ==============\n\n";
        cout << stock.marketList.find(index)->second.name << ", " << stock.marketList.find(index)->second.address << "\n";
        cout << stock.marketList.find(index)->second.productInfo.find(product_id)->second.name << ", ";
        cout << stock.marketList.find(index)->second.productInfo.find(product_id)->second.cost << "$\n";
        cout << "\n====================================\n";
        cout << "press any key to exit...\n";
        cin.ignore();
        cin.get();
        break;
      }
      case 5: // Money handle
      {
        int market_id = -1;
        system("clear");
        if (stock.marketList.empty())
        {
          system("clear");
          cout << "============== MARKET LIST ==============\n";
          cout << "Empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(!stock.marketList.empty() && "stock.marketList is empty");

        cout << "============== MARKET LIST ==============\n";
        for (int i = 0; i < stock.marketList.size(); i++)
        {
          cout << i + 1 << "] "<< stock.marketList.find(i)->second.name;
          cout << ", " << stock.marketList.find(i)->second.address << "\n";
        }
        int market_number;
        cout << "Enter [market] number: ";
        cin >> market_number;
        market_id = market_number - 1;

        if (stock.marketList.find(market_id)->second.GetId() != market_id)
        {
          cout << "No such market at list\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }

        assert(stock.marketList.find(market_id)->second.GetId() == market_id && "market_id is wrong");

        if (stock.marketList.find(market_id)->second.productInfo.empty())
        {
          cout << "Marker stock is empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }

        assert(!stock.marketList.find(market_id)->second.productInfo.empty() && "Market stock is empty");

        cout << "Enter the cash you want to spend ($): ";
        int money;
        cin >> money;
        if (money <= 0)
        {
          cout << "You'd change your work :)\n";
          break;
        }

        int flag = 0;


        system("clear");
        cout << "============== RESULT =============\n";
        cout << "BALANCE: " << money << "$\n";
        for (int i = 0; i < stock.marketList.find(market_id)->second.productInfo.size(); i++)
        {
          int counter_cost = 0;
          int product_cost = 0;
          int number = 0;
          int raz = 0;
          counter_cost = stock.marketList.find(market_id)->second.productInfo.find(i)->second.cost;
          product_cost = counter_cost;
          if (counter_cost > money && (i == stock.marketList.find(market_id)->second.productInfo.size() - 1))
          {
            flag = 1;
            cout << "Not enough money :(\n";
            cout << "press any key to exit...\n";
            cin.ignore();
            cin.get();
            break;
          }
          while (counter_cost < money)
          {
            number += 1;
            counter_cost += product_cost;
            if (counter_cost == money)
            {
              number += 1;
              break;
            }
          }
          raz = money - number * product_cost;

          cout << stock.marketList.find(market_id)->second.productInfo.find(i)->second.name;
          cout << " " << stock.marketList.find(market_id)->second.productInfo.find(i)->second.cost << "$ ";
          cout << " - " << number << " pieces\n" << "balance after buy: " << raz << "$\n";
        }
        if (flag == 1)
          break;
        cout << "press any key to exit...\n";
        cin.ignore();
        cin.get();
        break;
      }
      case 6:  // Buy product
      {
        system("clear");
        int product_id = -1;
        int market_id = -1;

        if (stock.marketList.empty())
        {
          system("clear");
          cout << "============== MARKET LIST ==============\n";
          cout << "Empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(!stock.marketList.empty() && "stock.marketList is empty");

        cout << "============== MARKET LIST ==============\n";
        for (int i = 0; i < stock.marketList.size(); i++)
        {
          cout << i + 1 << "] "<< stock.marketList.find(i)->second.name;
          cout << ", " << stock.marketList.find(i)->second.address << "\n";
        }
        int market_number = 0;
        cout << "Enter [market] number: ";
        cin >> market_number;
        market_id = market_number - 1;

        if (market_number <= 0 || market_number > stock.marketList.size())
        {
          cout << "No such market at list\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(stock.marketList.find(market_id)->second.GetId() == market_id && "market_id is wrong");
        if (stock.marketList.find(market_id)->second.productInfo.empty())
        {
          system("clear");
          cout << "============== PRODUCT LIST ==============\n";
          cout << "Empty :(\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(!stock.productList.empty() && "No product in market");

        system("clear");
        cout << "==========================================\n\n";
        cout << "MARKET: ";
        cout << stock.marketList.find(market_id)->second.name << ", " << stock.marketList.find(market_id)->second.address << "\n";
        cout << "\n============== PRODUCT LIST ==============\n";
        for (int i = 0; i < stock.marketList.find(market_id)->second.productInfo.size(); i++)
        {
          cout << i + 1 << "] ";
          cout << stock.marketList.find(market_id)->second.productInfo.find(i)->second.name << ", ";
          cout << stock.marketList.find(market_id)->second.productInfo.find(i)->second.cost << "$, ";
          cout << stock.marketList.find(market_id)->second.productInfo.find(i)->second.num << " pieces\n";
        }
        int product_number;
        cout << "Enter [product] number: ";
        cin >> product_number;
        product_id = product_number - 1;
        if (product_number <= 0 || product_number > stock.marketList.find(market_id)->second.productInfo.size())
        {
          cout << "No such product at list\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        assert(stock.marketList.find(market_id)->second.productInfo.find(product_id)->second.GetID() == product_id && "product_id is wrong");

        int quantity = -1;
        cout << "Enter [product] quantity: ";
        cin >> quantity;
        if (quantity <= 0)
        {
          cout << "error input\n";
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        int result_money = stock.marketList.find(market_id)->second.BuyProduct(stock.marketList.find(market_id)->second.productInfo.find(product_id)->second, quantity);
        if (result_money < 0)
        {
          cout << "press any key to exit...\n";
          cin.ignore();
          cin.get();
          break;
        }
        cout << "SPEND MONEY: " << result_money << "$\n";
        cout << "[Product] amount at market stock: " << stock.marketList.find(market_id)->second.productInfo.find(product_id)->second.num << "\n";
        cout << "press any key to exit...\n";
        cin.ignore();
        cin.get();
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

