#include "Data\RentalOrder.h"

#include <cassert>
#include <iostream>

#include "Data\Movie.h"
#include "Data\Game.h"

unsigned int RentalOrder::s_globalId = 0;

RentalOrder::RentalOrder(const char* rentalDate)
{
  assert(rentalDate && std::strlen(rentalDate) != 0);

	_orderId = s_globalId;

	_rentalDate = rentalDate;
	_returnStatus = Pending;
	_orderClosed = false;

	s_globalId++;
}

RentalOrder::~RentalOrder()
{
	_rentalOrder.clear();
}

unsigned int RentalOrder::getOrderId() const
{
	return _orderId;
}

const char* RentalOrder::getRentalDate() const
{
	return _rentalDate.c_str();
}

void RentalOrder::closeOrder()
{
  _returnStatus = ReturnStatus::Returned;
}

bool RentalOrder::isOrderClosed() const
{
  return _returnStatus == ReturnStatus::Returned;
}

void RentalOrder::addItem(IItem* item)
{
	if (item != nullptr)
	{
		_rentalOrder.push_back(item);
	}
}

const std::vector<IItem*> RentalOrder::getItems() const
{
	return _rentalOrder;
}

std::ostream& operator<<(std::ostream& os, const RentalOrder* o)
{
  os << "Rental order date: " << o->getRentalDate() << std::endl
     << "Items rented:" << std::endl;

  std::vector<IItem*> items = o->getItems();
  for (unsigned int i = 0; i < items.size(); i++)
  {
    IItem* item = items.at(i);
    if (dynamic_cast<Movie*>(item) != nullptr)
    {
      os << std::endl
         << dynamic_cast<Movie*>(items.at(i)) << std::endl;
    }
    else if (dynamic_cast<Game*>(item) != nullptr)
    {
      os << dynamic_cast<Game*>(items.at(i)) << std::endl << std::endl;
    }
  }
	return os;
}