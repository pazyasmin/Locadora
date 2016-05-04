#pragma once

#include <vector>

#include "Interfaces\Data\ICatalog.h"

class IItem;

// Manages operations regarding catalogs and their items.
class ICatalogManager
{
public:
  virtual ~ICatalogManager() {}

  // Adds a new catalog.
  virtual void addCatalog(ICatalog* newCatalog) = 0;

  // Returns the list of catalog names.
  virtual std::vector<const char*> getCatalogNames() const = 0;

  // Adds a new item to a given catalog.
  virtual void addItemToCatalog(CatalogType type, IItem* newitem) = 0;

  // Gets an item given its id.
  virtual const IItem* getItem(unsigned int itemId) const = 0;

  // Returns the list of items for the given catalog.
  virtual const std::vector<IItem*> getItemsFromCatalog(const char* catalogName) const = 0;

  // Returns the list of items for the given catalog.
  virtual const std::vector<IItem*> getItemsFromCatalog(CatalogType type) const = 0;

  // Returns the rent price for the given item.
  virtual float getRentForItem(unsigned int itemId) const = 0;

  // Adds the given amount of items to the number of available copies.
  virtual void addToAvailableCopies(CatalogType type, unsigned int itemId, unsigned int amount) = 0;

  // Removes a given amount of items from the number of available copies.
  virtual void removeFromAvailableCopies(CatalogType type, unsigned int itemId, unsigned int amount) = 0;

  // Returns the amount of copies available for rent. 
  virtual unsigned int getAvailableCopies(CatalogType type, unsigned int itemId) const = 0;
};