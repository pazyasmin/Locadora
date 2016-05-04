#include "Store\CustomerManager.h"

#include "Data\Customer.h"
#include "Data\RentalOrder.h"

CustomerManager::CustomerManager()
{

}

CustomerManager::~CustomerManager()
{
  for (unsigned int i = 0; i < _customers.size(); i++)
  {
    delete _customers.at(i);
  }
  _customers.clear();
}

void CustomerManager::addCustomer(ICustomer* customer)
{
  if (customer != nullptr)
  {
    _customers.push_back(customer);
  }
}

ICustomer* CustomerManager::getCustomer(unsigned int customerId) const
{
  ICustomer* c = _getCustomerById(customerId);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid customer id.");
  }

  return c;
}

ICustomer* CustomerManager::getCustomer(const char* customerName) const
{
  if (customerName != nullptr)
  {
    for (unsigned int i = 0; i < _customers.size(); i++)
    {
      ICustomer* c = _customers.at(i);
      if (std::strcmp(c->getName(), customerName) == 0)
      {
        return c;
      }
    }
  }

  throw std::invalid_argument("Invalid customer name.");
}

void CustomerManager::addRentalOrderForCustomer(unsigned int customerId, IRentalOrder* order)
{
  if (order == nullptr)
  {
    return;
  }

  ICustomer* customer = nullptr;
  for (unsigned int i = 0; i < _customers.size(); i++)
  {
    ICustomer* c = _customers.at(i);
    if (c->getCustomerId() == customerId)
    {
      customer = c;
    }
  }
  if (customer == nullptr)
  {
    throw std::invalid_argument("Invalid customer id.");
  }

  customer->addRentalOrder(order);
}

void CustomerManager::closeRentalOrder(unsigned int customerId, unsigned int orderId)
{
  ICustomer* c = _getCustomerById(customerId);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid customer id.");
  }

  IRentalOrder* o = c->getRentalOrder(orderId);
  if (o == nullptr)
  {
    throw std::invalid_argument("Invalid order id.");
  }

  o->closeOrder();
}

std::vector<IRentalOrder*> CustomerManager::getOpenOrdersForCustomer(unsigned int customerId) const
{
  ICustomer* c = _getCustomerById(customerId);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid customer id.");
  }

  std::vector<IRentalOrder*> openOrders;
  std::vector<IRentalOrder*> orders = c->getRentalOrders();
  for (unsigned int i = 0; i < orders.size(); i++)
  {
    IRentalOrder* o = orders.at(i);
    if (!o->isOrderClosed())
    {
      openOrders.push_back(o);
    }
  }

  return openOrders;
}

std::vector<const IRentalOrder*> CustomerManager::getClosedOrdersForCustomer(unsigned int customerId) const
{
  ICustomer* c = _getCustomerById(customerId);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid customer id.");
  }

  std::vector<const IRentalOrder*> closedOrders;
  std::vector<IRentalOrder*> orders = c->getRentalOrders();
  for (unsigned int i = 0; i < orders.size(); i++)
  {
    const IRentalOrder* o = orders.at(i);
    if (o->isOrderClosed())
    {
      closedOrders.push_back(o);
    }
  }

  return closedOrders;
}

ICustomer* CustomerManager::_getCustomerById(unsigned int customerId) const
{
  for (unsigned int i = 0; i < _customers.size(); i++)
  {
    ICustomer* c = _customers.at(i);
    if (c->getCustomerId() == customerId)
    {
      return c;
    }
  }

  // Error: Customer not found.
  return nullptr;
}