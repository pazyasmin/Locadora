#pragma once

#include <vector>

class IDate;
class IItem;

enum ReturnStatus
{
	Returned,
	Pending,
};

// Contains data about a rental order.
class IRentalOrder
{
public:
	virtual ~IRentalOrder() {}

	// Returns the rental order id.
	virtual unsigned int getOrderId() const = 0;

	// Closes order so no more items can be added to it.
	virtual void closeOrder() = 0;

  // Returns whether this order has been closed.
  virtual bool isOrderClosed() const = 0;

	// Returns this order's rental date.
	virtual const char* getRentalDate() const = 0;

	// Adds an item to this order as long as it is open.
	virtual void addItem(IItem* item) = 0;

	// Returns the list of items in this order.
	virtual const std::vector<IItem*> getItems() const = 0;

};