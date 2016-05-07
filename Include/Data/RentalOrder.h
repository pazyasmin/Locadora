#pragma once

#include "Interfaces\Data\IRentalOrder.h"

class RentalOrder : public IRentalOrder
{
	friend std::ostream& operator<<(std::ostream& os, const RentalOrder* ro);

public:
	RentalOrder(const char* rentalDate);
	~RentalOrder();

	// Returns a rental order id.
	unsigned int getOrderId() const override;

	// Returns the rental date.
	const char* getRentalDate() const override;

	// Closes order so it cannot be edited eni.
	virtual void closeOrder() override;

	// Returns whether this order has been closed.
	bool isOrderClosed() const override;

	// Adds an item to this order as long as it is open.
	void addItem(IItem* item) override;

	// Returns the list of items in this order.
	const std::vector<IItem*> getItems() const override;
	
	RentalOrder& RentalOrder::operator+=(const RentalOrder& ro);

	// Forbidden methods.
	RentalOrder() = delete;
	RentalOrder(const RentalOrder& ro) = delete;
	void operator=(const RentalOrder& ro) = delete;

private:
	static unsigned int s_globalId;

	unsigned int _orderId;
	float _orderRent;
	bool _orderClosed;
	std::string _rentalDate;
	ReturnStatus _returnStatus;
	std::vector<IItem*> _rentalOrder;

};