#include "Data\Customer.h"

#include <cassert>

#include "Data\RentalOrder.h"

unsigned int Customer::s_globalId = 0;

Customer::Customer(const char* name)
{
  assert(name && std::strlen(name) != 0);

  _name = name;
  _customerId = s_globalId;

  s_globalId++;
}

Customer::~Customer()
{

}

void Customer::setName(const char* name)
{
  if (name != nullptr)
  {
    _name = name;
  }
}

const char* Customer::getName() const
{
  return _name.c_str();
}

unsigned int Customer::getCustomerId() const
{
  return _customerId;
}

void Customer::addRentalOrder(IRentalOrder* rental)
{
  if (rental != nullptr)
  {
    _rentals.push_back(rental);
  }
}

IRentalOrder* Customer::getRentalOrder(unsigned int rentalId) const
{
  for (unsigned int i = 0; i < _rentals.size(); i++)
  {
    IRentalOrder* o = _rentals.at(i);
    if (o->getOrderId() == rentalId)
    {
      return o;
    }
  }

  return nullptr;
}

std::vector<IRentalOrder*> Customer::getRentalOrders() const
{
  return _rentals;
}