#pragma once

#include "Interfaces\Data\ICatalog.h"

#include <map>

#include "Interfaces\Data\IItem.h"

// Describes the collection of items from a rental store
class Catalog : public ICatalog
{
public:
	Catalog(CatalogType type);
	~Catalog();

	// Sets the catalog type.
	void setCatalogType(CatalogType type) override;

	// Retuns the catalog type.
	CatalogType getCatalogType() const override;

	// Adds an item to the catalog.
	void addItem(IItem* item) override;

	// Returns an item for a given id.
	IItem* getItem(unsigned int productId) const override;

	// Returns the list of items in this catalog.
	std::vector<IItem*> getItems() const override;

  // Returns the rent price for the given item.
  float getRentForItem(unsigned int itemId) const override;

	// Forbidden methods and operators to enforce strict creation of sections with necessary data.
	Catalog()                        = delete;
	Catalog(const Catalog& c)        = delete;
	void operator=(const Catalog& c) = delete;

private:
	CatalogType _catalogType;
	std::vector<IItem*> _items;
	std::map<MediaType, float> _mediaRentValues;
};