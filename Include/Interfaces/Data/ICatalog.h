#pragma once

#include <vector>

class IItem;

enum CatalogType
{
  Movies,
  Games
};

class ICatalog
{
public:
  virtual ~ICatalog() {}

  // Sets the catalog type.
  virtual void setCatalogType(CatalogType type) = 0;

  // Retuns catalog type.
  virtual CatalogType getCatalogType() const = 0;

  // Adds an item to the catalog.
  virtual void addItem(IItem* item) = 0;

  // Returns an item from this catalog given its id.
  virtual IItem* getItem(unsigned int itemId) const = 0;

  // Returns the list of items in this catalog.
  virtual std::vector<IItem*> getItems() const = 0;

  // Returns the rent price for the given item.
  virtual float getRentForItem(unsigned int itemId) const = 0;
};