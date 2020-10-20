#include "product.h"

int Product::pid = 0;

Product::Product(string _name, int _cost)
{
  this->name = _name;
  this->id = pid++;
  this->cost = _cost;
  this->num = 0;
}

Product::Product(const Product &_product)
{
  this->num = _product.num;
  this->name = _product.name;
  this->cost = _product.cost;
  this->id =  _product.id;
  this->pid = _product.pid;
}
