#include "market.h"
int Market::mid = 0;

Market::Market(string _name, string _address)
{
  this->name= _name;
  this->address = _address;
  this->id = mid++;
}

int Market::GetId()
{
  return this->id;
}

void Market::AddProduct(Product _product)
{
  this->productInfo.insert(make_pair(_product.GetID(), _product));
}

int Market::BuyProduct(Product _product, int quantity)
{
  int _num = this->productInfo.find(_product.GetID())->second.num;
  if (quantity > _num)
  {
    cout << "Insufficient amount of product\n";
    cout << "Your request: " << quantity << "\n";
    cout << "In market stock: " << _num << "\n";
    return -1;
  }
  assert(this->productInfo.find(_product.GetID())->second.num >= quantity && "Not enough product in market");
  this->productInfo.find(_product.GetID())->second.num -= quantity;
  if ( this->productInfo.find(_product.GetID())->second.num == 0)
  {
    map <int, Product>::iterator it;
    it = this->productInfo.find(_product.GetID());
    this->productInfo.erase(it);
  }
  return quantity * this->productInfo.find(_product.GetID())->second.cost;
}


