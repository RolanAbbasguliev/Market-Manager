#include "stock.h"

void Stock::AddMarketToStock(Market _market)
{
  this->marketList.insert(make_pair(_market.GetId(), _market));
}

void Stock::AddProductToStock(Product _product)
{
  this->productList.insert(make_pair(_product.GetID(), _product));
}

