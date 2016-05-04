#include "Interfaces\Store\ICustomerManager.h"

#include <map>

class CustomerManager : public ICustomerManager
{
public:
  CustomerManager();
  ~CustomerManager();

  // Adds a new customer.
  void addCustomer(ICustomer* customer) override;

  // Returns the customer with the given id.
  ICustomer* getCustomer(unsigned int customerId) const override;

  // Returns the customer with the given name.
  ICustomer* getCustomer(const char* customerName) const override;

  // Adds the given rental order and marks it as on schedule.
  void addRentalOrderForCustomer(unsigned int customerId, IRentalOrder* order) override;

  // Marks the given rental order as closed.
  void closeRentalOrder(unsigned int customerId, unsigned int orderId) override;

  // Returns the list of open rental orders for the given user.
  std::vector<IRentalOrder*> getOpenOrdersForCustomer(unsigned int customerId) const override;

  // Returns the list of open rental orders for the given user.
  std::vector<const IRentalOrder*> getClosedOrdersForCustomer(unsigned int customerId) const override;

private:
  // Returns a customer given its id of nullptr if no customer has been found.
  ICustomer* _getCustomerById(unsigned int customerId) const;

  std::vector<ICustomer*> _customers;
};