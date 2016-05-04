#include "Store\CatalogManager.h"

#include "Data\Catalog.h"
#include "Data\Movie.h"

CatalogManager::CatalogManager()
{
  _catalogNames.insert(std::pair<CatalogType, const char*>(CatalogType::Games, "Games"));
  _catalogNames.insert(std::pair<CatalogType, const char*>(CatalogType::Movies, "Movies"));
}

CatalogManager::~CatalogManager()
{
  // Item pointers are owned by their catalogs.
  _rentalItems.clear();

  for (unsigned int i = 0; i < _itemCatalogs.size(); i++)
  {
    delete _itemCatalogs.at(i);
  }
  _itemCatalogs.clear();
}

void CatalogManager::addCatalog(ICatalog* newCatalog)
{
  if (newCatalog != nullptr)
  {
    _itemCatalogs.push_back(newCatalog);
  }
}

std::vector<const char*> CatalogManager::getCatalogNames() const
{
  std::vector<const char*> catalogNames;
  std::map<CatalogType, const char*>::const_iterator it;
  for (it = _catalogNames.begin(); it != _catalogNames.end(); it++)
  {
    catalogNames.push_back(it->second);
  }

  return catalogNames;
}

void CatalogManager::addItemToCatalog(CatalogType type, IItem* newItem)
{
  ICatalog* c = _getCatalogByType(type);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid catalog type.");
  }

  if (newItem != nullptr)
  {
    c->addItem(newItem);
  }
}

const IItem* CatalogManager::getItem(unsigned int itemId) const
{
  for (unsigned int i = 0; i < _itemCatalogs.size(); i++)
  {
    IItem* item = _itemCatalogs.at(i)->getItem(itemId);
    if (item != nullptr)
    {
      return item;
    }
  }

  throw std::invalid_argument("Invalid item id.");
}

const std::vector<IItem*> CatalogManager::getItemsFromCatalog(const char* catalogName) const
{
  ICatalog* c = _getCatalogByName(catalogName);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid catalog type.");
  }

  return c->getItems();
}

const std::vector<IItem*> CatalogManager::getItemsFromCatalog(CatalogType type) const
{
  ICatalog* c = _getCatalogByType(type);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid catalog type.");
  }

  return c->getItems();
}

float CatalogManager::getRentForItem(unsigned int itemId) const
{
  for (unsigned int i = 0; i < _itemCatalogs.size(); i++)
  {
    ICatalog* c = _itemCatalogs.at(i);
    IItem* item = c->getItem(itemId);
    if (item != nullptr)
    {
      return c->getRentForItem(itemId);
    }
  }

  throw std::invalid_argument("Invalid item id.");
}

void CatalogManager::addToAvailableCopies(CatalogType type, unsigned int itemId, unsigned int amount)
{
  ICatalog* c = _getCatalogByType(type);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid catalog type.");
  }

  IItem* item = c->getItem(itemId);
  if (item == nullptr)
  {
    throw std::invalid_argument("Invalid item id.");
  }

  item->addToAvailableCopies(amount);
}

void CatalogManager::removeFromAvailableCopies(CatalogType type, unsigned int itemId, unsigned int amount)
{
  ICatalog* c = _getCatalogByType(type);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid catalog type.");
  }

  IItem* item = c->getItem(itemId);
  if (item == nullptr)
  {
    throw std::invalid_argument("Invalid item id.");
  }

  item->removeFromAvailableCopies(amount);
}

unsigned int CatalogManager::getAvailableCopies(CatalogType type, unsigned int itemId) const
{
  ICatalog* c = _getCatalogByType(type);
  if (c == nullptr)
  {
    throw std::invalid_argument("Invalid catalog type.");
  }

  IItem* item = c->getItem(itemId);
  if (item == nullptr)
  {
    throw std::invalid_argument("Invalid item id.");
  }

  return item->getAvailableCopies();
}

ICatalog* CatalogManager::_getCatalogByType(CatalogType type) const
{
  for (unsigned int i = 0; i < _itemCatalogs.size(); i++)
  {
    ICatalog* c = _itemCatalogs.at(i);
    if (c->getCatalogType() == type)
    {
      return c;
    }
  }

  // Error: Catalog not found.
  return nullptr;
}

ICatalog* CatalogManager::_getCatalogByName(const char* catalogName) const
{
  std::map<CatalogType, const char*>::const_iterator it;

  for (it = _catalogNames.begin(); it != _catalogNames.end(); it++)
  {
    if (std::strcmp(it->second, catalogName) == 0)
    {
      return _getCatalogByType(it->first);
    }
  }

  // Error: Catalog not found.
  return nullptr;
}