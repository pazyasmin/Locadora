#pragma once

#include "Interfaces\Store\ICatalogManager.h"

#include <map>

class CatalogManager : public ICatalogManager
{
public:
  CatalogManager();
  ~CatalogManager();

  // Adds a new catalog.
  void addCatalog(ICatalog* newCatalog) override;

  // Returns the list of catalog names.
  std::vector<const char*> getCatalogNames() const override;

  // Adds a new item to a given catalog.
  void addItemToCatalog(CatalogType type, IItem* newItem) override;

  // Gets an item given its id.
  const IItem* getItem(unsigned int itemId) const override;

  // Returns the list of items for the given catalog.
  const std::vector<IItem*> getItemsFromCatalog(const char* catalogName) const override;

  // Returns the list of items for the given catalog.
  const std::vector<IItem*> getItemsFromCatalog(CatalogType type) const override;

  // Returns the rent price for the given item.
  float getRentForItem(unsigned int itemId) const override;

  // Adds a given amount of items to the number of available copies.
  void addToAvailableCopies(CatalogType type, unsigned int itemId, unsigned int amount) override;

  // Removes a given amount of items from the available number of copies.
  void removeFromAvailableCopies(CatalogType type, unsigned int itemId, unsigned int amount) override;

  // Returns the amount of items available for the given item.
  unsigned int getAvailableCopies(CatalogType type, unsigned int itemId) const override;

private:
  // Returns an ICatalog* given its type.
  ICatalog* _getCatalogByType(CatalogType type) const;

  // Returns an ICatalog* given its name.
  ICatalog* _getCatalogByName(const char* catalogName) const;

  // Stores a catalog name given its type.
  std::map<CatalogType, const char*> _catalogNames;

  std::vector<IItem*> _rentalItems;
  std::vector<ICatalog*> _itemCatalogs;
};