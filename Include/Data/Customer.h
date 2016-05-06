#pragma once

#include "Interfaces\Data\ICustomer.h"

#include <string>

class Customer : public ICustomer
{
public:
  Customer(const char* name);
  ~Customer();

  // Sets the customer name.
  void setName(const char* name) override;

  // Returns the customer name.
  const char* getName() const override;

  // Returns the customer id.
  unsigned int getCustomerId() const override;

  // Adds a rental to the history of this customer.
  void addRentalOrder(IRentalOrder* order) override;

  // Gets an rental order by its id.
  IRentalOrder* getRentalOrder(unsigned int orderId) const override;

  // Gets the list of rentals made by this user.
  std::vector<IRentalOrder*> getRentalOrders() const override;

private:
  static unsigned int s_globalId;

  unsigned int _customerId;
  std::string _name;

  std::vector<IRentalOrder*> _rentals;
};