#include "stock.h"

void Stock::AddMarketToStock(Market _market)
{
  this->marketList.insert(make_pair(_market.GetId(), _market));
}

void Stock::AddProductToStock(Product _product)
{
  this->productList.insert(make_pair(_product.GetID(), _product));
}

int Stock::First()
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
  this->AddMarketToStock(market);

  cout << "Set [market]: " << market.name << ", " << market.address << endl;
  cout << "press any key to exit...\n";
  cin.get();
  return 0;
}

int Stock::Second()
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
    return -1;
  }

  Product product(name, cost);
  this->AddProductToStock(product);

  cout << "Set [product]: " << product.name << ", " << product.cost << "$" << endl;
  cout << "press any key to exit...\n";
  cin.ignore();
  cin.get();
  return 0;
}

int Stock::Third()
{
  system("clear");
  int product_id = -1;
  int market_id = -1;
  int quantity = 0;

  if (this->marketList.empty())
  {
    system("clear");
    cout << "============== MARKET LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(!this->marketList.empty() && "stock.marketList is empty");

  if (this->productList.empty())
  {
    system("clear");
    cout << "============== PRODUCT LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(!this->productList.empty() && "stock.productList is empty");

  system("clear");
  cout << "============== MARKET LIST ==============\n";
  for (int i = 0; i < this->marketList.size(); i++)
  {
    cout << i + 1 << "] "<< this->marketList.find(i)->second.name;
    cout << ", " << this->marketList.find(i)->second.address << "\n";
  }

  int market_number = 0;
  cout << "Enter [market] number: ";
  cin >> market_number;
  market_id = market_number;
  market_id -= 1;

  if (market_number <= 0 || market_number > this->marketList.size())
  {
    cout << "error no such market at list\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(this->marketList.find(market_id)->second.GetId() == market_id && "market_id is wrong");

  system("clear");
  cout << "============== PRODUCT LIST ==============\n";
  for (int i = 0; i < this->productList.size(); i++)
  {
    cout << i + 1 << "] "<< this->productList.find(i)->second.name;
    cout << ", " << this->productList.find(i)->second.cost << " $\n";
  }
  int product_number = 0;
  cout << "Enter [product] number: ";
  cin >> product_number;
  product_id = product_number - 1;

  if (product_number <= 0 || product_number > this->productList.size())
  {
    cout << "error no such product at list\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }

  assert(this->productList.find(product_id)->second.GetID() == product_id && "product_id is wrong");

  cout << "Set the quantity of [product]: ";
  cin >> quantity;
  this->productList.find(product_id)->second.num = quantity;    // change product quantity

  cout << "Set the cost ? [y/n]: ";
  string choose;
  cin >> choose;

  if (choose == "y")
  {
    cout << "Input your cost: ";
    int value;
    cin >> value;
    this->productList.find(product_id)->second.cost = value;
    this->marketList.find(market_id)->second.AddProduct(this->productList.find(product_id)->second);
    return 1;
  }
  else if (choose != "n")
  {
    cout << "Error input\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  this->marketList.find(market_id)->second.AddProduct(this->productList.find(product_id)->second);
  return 0;
}

int Stock::Quarter()
{
  system("clear");
  int product_id = -1;
  int index = -1;
  int min = INT_MAX;
  int _cost = -1;

  if (this->marketList.empty())
  {
    system("clear");
    cout << "============== MARKET LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }

  if (this->productList.empty())
  {
    system("clear");
    cout << "============== PRODUCT LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }


  cout << "============== PRODUCT LIST ==============\n";
  for (int i = 0; i < this->productList.size(); i++)
  {
    cout << i + 1 << "] "<< this->productList.find(i)->second.name;
    cout << ", " << this->productList.find(i)->second.cost << "$\n";
  }
  assert(!this->productList.empty() && "stock.productList is empty");

  int product_number = 0;
  cout << "Enter [product] number: ";
  int flag = 0;
  cin >> product_number;
  product_id = product_number - 1;

  if (product_number <= 0 || product_number > this->productList.size())
  {
    cout << "error no such product at list\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  // Product in market check
  for (int i = 0; i < this->marketList.size(); i++)
  {
    if (this->marketList.find(i)->second.productInfo.find(product_id)->second.num == 0)
    {
      cout << "Error: The product was not delivered to the markets!\n";
      cout << "press any key to exit...\n";
      cin.ignore();
      cin.get();
      flag = 1;
    }
  }
  if (flag)
    return 1;
  assert(this->productList.find(product_id)->second.GetID() == product_id && "product_id is wrong");

  // Searching for minimal product cost in marketList
  for (int i = 0; i < this->marketList.size(); i++)
  {
    _cost = this->marketList.find(i)->second.productInfo.find(product_id)->second.cost;
    if (_cost < min)
    {
      min = _cost;
      index = i;
    }
  }
  assert(this->marketList.find(index)->second.productInfo.find(product_id)->second.cost == min && "Minial cost product found worng");

  system("clear");
  cout << "============== RESULT ==============\n\n";
  cout << this->marketList.find(index)->second.name << ", " << this->marketList.find(index)->second.address << "\n";
  cout << this->marketList.find(index)->second.productInfo.find(product_id)->second.name << ", ";
  cout << this->marketList.find(index)->second.productInfo.find(product_id)->second.cost << "$\n";
  cout << "\n====================================\n";
  cout << "press any key to exit...\n";
  cin.ignore();
  cin.get();
  return 0;
}

int Stock::Fifth()
{
  int market_id = -1;
  system("clear");
  if (this->marketList.empty())
  {
    system("clear");
    cout << "============== MARKET LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(!this->marketList.empty() && "stock.marketList is empty");

  cout << "============== MARKET LIST ==============\n";
  for (int i = 0; i < this->marketList.size(); i++)
  {
    cout << i + 1 << "] "<< this->marketList.find(i)->second.name;
    cout << ", " << this->marketList.find(i)->second.address << "\n";
  }
  int market_number;
  cout << "Enter [market] number: ";
  cin >> market_number;
  market_id = market_number - 1;

  if (this->marketList.find(market_id)->second.GetId() != market_id)
  {
    cout << "No such market at list\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }

  assert(this->marketList.find(market_id)->second.GetId() == market_id && "market_id is wrong");

  if (this->marketList.find(market_id)->second.productInfo.empty())
  {
    cout << "Marker stock is empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }

  assert(!this->marketList.find(market_id)->second.productInfo.empty() && "Market stock is empty");

  cout << "Enter the cash you want to spend ($): ";
  int money;
  cin >> money;
  if (money <= 0)
  {
    cout << "You'd change your work :)\n";
    return 1;
  }

  int flag = 0;


  system("clear");
  cout << "============== RESULT =============\n";
  cout << "BALANCE: " << money << "$\n";
  for (int i = 0; i < this->marketList.find(market_id)->second.productInfo.size(); i++)
  {
    int counter_cost = 0;
    int product_cost = 0;
    int number = 0;
    int raz = 0;
    counter_cost = this->marketList.find(market_id)->second.productInfo.find(i)->second.cost;
    product_cost = counter_cost;
    if (counter_cost > money && (i == this->marketList.find(market_id)->second.productInfo.size() - 1))
    {
      flag = 1;
      cout << "Not enough money :(\n";
      cout << "press any key to exit...\n";
      cin.ignore();
      cin.get();
      return 1;
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

    cout << this->marketList.find(market_id)->second.productInfo.find(i)->second.name;
    cout << " " << this->marketList.find(market_id)->second.productInfo.find(i)->second.cost << "$ ";
    cout << " - " << number << " pieces\n" << "balance after buy: " << raz << "$\n";
  }
  if (flag == 1)
    return 1;
  cout << "press any key to exit...\n";
  cin.ignore();
  cin.get();
  return 0;
}

int Stock::Six()
{
  system("clear");
  int product_id = -1;
  int market_id = -1;

  if (this->marketList.empty())
  {
    system("clear");
    cout << "============== MARKET LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(!this->marketList.empty() && "stock.marketList is empty");

  cout << "============== MARKET LIST ==============\n";
  for (int i = 0; i < this->marketList.size(); i++)
  {
    cout << i + 1 << "] "<< this->marketList.find(i)->second.name;
    cout << ", " << this->marketList.find(i)->second.address << "\n";
  }
  int market_number = 0;
  cout << "Enter [market] number: ";
  cin >> market_number;
  market_id = market_number - 1;

  if (market_number <= 0 || market_number > this->marketList.size())
  {
    cout << "No such market at list\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(this->marketList.find(market_id)->second.GetId() == market_id && "market_id is wrong");
  if (this->marketList.find(market_id)->second.productInfo.empty())
  {
    system("clear");
    cout << "============== PRODUCT LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(!this->productList.empty() && "No product in market");

  system("clear");
  cout << "==========================================\n\n";
  cout << "MARKET: ";
  cout << this->marketList.find(market_id)->second.name << ", " << this->marketList.find(market_id)->second.address << "\n";
  cout << "\n============== PRODUCT LIST ==============\n";
  for (int i = 0; i < this->marketList.find(market_id)->second.productInfo.size(); i++)
  {
    cout << i + 1 << "] ";
    cout << this->marketList.find(market_id)->second.productInfo.find(i)->second.name << ", ";
    cout << this->marketList.find(market_id)->second.productInfo.find(i)->second.cost << "$, ";
    cout << this->marketList.find(market_id)->second.productInfo.find(i)->second.num << " pieces\n";
  }
  int product_number;
  cout << "Enter [product] number: ";
  cin >> product_number;
  product_id = product_number - 1;
  if (product_number <= 0 || product_number > this->marketList.find(market_id)->second.productInfo.size())
  {
    cout << "No such product at list\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(this->marketList.find(market_id)->second.productInfo.find(product_id)->second.GetID() == product_id && "product_id is wrong");

  int quantity = -1;
  cout << "Enter [product] quantity: ";
  cin >> quantity;
  if (quantity <= 0)
  {
    cout << "error input\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  int result_money = this->marketList.find(market_id)->second.BuyProduct(this->marketList.find(market_id)->second.productInfo.find(product_id)->second, quantity);
  if (result_money < 0)
  {
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  cout << "SPEND MONEY: " << result_money << "$\n";
  map <int, Product>::iterator it = this->marketList.find(market_id)->second.productInfo.find(product_id);
  if (it != this->marketList.find(market_id)->second.productInfo.end() )
  {
    cout << "[Product] amount at market stock: 0";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  cout << "[Product] amount at market stock: " << this->marketList.find(market_id)->second.productInfo.find(product_id)->second.num << "\n";
  cout << "press any key to exit...\n";
  cin.ignore();
  cin.get();
  return 1;
}

int Stock::Seven()
{
  int flag = 0;

  system("clear");
  cout << "============== PRODUCT LIST ==============\n";
  for (int i = 0; i < this->productList.size(); i++)
  {
    cout << i + 1 << "] "<< this->productList.find(i)->second.name;
    cout << ", " << this->productList.find(i)->second.cost << "$\n";
  }
  if (this->productList.empty())
  {
    system("clear");
    cout << "============== PRODUCT LIST ==============\n";
    cout << "Empty :(\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  assert(!this->productList.empty() && "stock.productList is empty");

  int product_count = 0;
  cout << "Enter [product] count: ";
  cin >> product_count;
  if (product_count <= 0 || product_count > this->productList.size())
  {
    cout << "error input\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
    return 1;
  }
  map <int, int> selec_product;  // <id, amout> of selected product
  for (int i = 0; i < product_count; i++)
  {
    system("clear");
    cout << "============== PRODUCT LIST ==============\n";
    for (int i = 0; i < this->productList.size(); i++)
    {
      cout << i + 1 << "] "<< this->productList.find(i)->second.name;
      cout << ", " << this->productList.find(i)->second.cost << "$\n";
    }
    int product_id = -1;
    int product_number = 0;
    cout << "Enter [product] number: ";
    cin >> product_number;
    product_id = product_number - 1;
    if (product_number <= 0 || product_number > this->productList.size())
    {
      flag = 1;
      cout << "error no such product at list\n";
      cout << "press any key to exit...\n";
      cin.ignore();
      cin.get();
      break;
    }
    assert(this->productList.find(product_id)->second.GetID() == product_id && "wrong produсt_id");
    int product_amount = 0;
    cout << "Enter [product] amount: ";
    cin >> product_amount;
    if (product_amount <= 0)
    {
      flag = 1;
      cout << "error [product] amount \n";
      cout << "press any key to exit...\n";
      cin.ignore();
      cin.get();
      return 1;
    }
    selec_product[product_id] = product_amount;
  }
  if (flag == 1)
    return 1;
  int index = 0;
  int sum = 0;
  int min = INT_MAX;
  int id_product = 0;
  int num_product = 0;
  for (int i = 0; i < this->marketList.size(); i++)
  {
    sum = 0;
    for (auto elem : selec_product)
    {
      id_product = elem.first;
      num_product = elem.second;
      int cost_product = this->marketList.find(i)->second.productInfo.find(id_product)->second.cost;
      if (this->marketList.find(i)->second.productInfo.find(id_product)->second.num >= num_product)
        sum += cost_product * num_product;
      else
        break;
    }
    if (sum < min && sum != 0)
    {
      min = sum;
      index = i;
    }
  }

  if (min != INT_MAX && min != 0)
  {
    cout << "Market: " << this->marketList.find(index)->second.name << " is the most profitable\n";
    cout << "Total price: " << min << "\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
  }
  else
  {
    cout << "No result for your request\n";
    cout << "press any key to exit...\n";
    cin.ignore();
    cin.get();
  }
  return 0;
}



