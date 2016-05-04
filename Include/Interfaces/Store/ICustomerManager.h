#pragma once

#include <vector>

class ICustomer;
class IRentalOrder;

class ICustomerManager
{
public:
  virtual ~ICustomerManager() {}

  // Adds a new customer.
  virtual void addCustomer(ICustomer* customer) = 0;

  // Returns the customer with the given id.
  virtual ICustomer* getCustomer(unsigned int customerId) const = 0;

  // Returns the customer with the given name.
  virtual ICustomer* getCustomer(const char* customerName) const = 0;

  // Adds the given rental order and marks it as on schedule.
  virtual void addRentalOrderForCustomer(unsigned int customerId, IRentalOrder* order) = 0;

  // Marks the given rental order as closed.
  virtual void closeRentalOrder(unsigned int customerId, unsigned int orderId) = 0;

  // Returns the list of open rental orders for the given user.
  virtual std::vector<IRentalOrder*> getOpenOrdersForCustomer(unsigned int customerId) const = 0;

  // Returns the list of open rental orders for the given user.
  virtual std::vector<const IRentalOrder*> getClosedOrdersForCustomer(unsigned int customerId) const = 0;
};