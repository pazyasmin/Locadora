#pragma once

#include <vector>

class IRentalOrder;

// Contains customer-related data, such as name, list of rentals, etc.
class ICustomer
{
public:
  virtual ~ICustomer() {}

  // Sets the customer name.
  virtual void setName(const char* name) = 0;

  // Returns the customer name.
  virtual const char* getName() const = 0;

  // Returns the customer id.
  virtual unsigned int getCustomerId() const = 0;

  // Adds a rental to the history of this customer.
  virtual void addRentalOrder(IRentalOrder* order) = 0;

  // Gets an rental order by its id.
  virtual IRentalOrder* getRentalOrder(unsigned int orderId) const = 0;

  // Gets the list of rentals made by this user.
  virtual std::vector<IRentalOrder*> getRentalOrders() const = 0;
};