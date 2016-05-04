#include "Data\Catalog.h"

#include "Interfaces\Data\IItem.h"



Catalog::Catalog(CatalogType type)
{
  _catalogType = type;

  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Game_Cartridge, 1.5f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Game_DVD, 5.0f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Game_BluRay, 9.0f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Movie_VHS, 1.5f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Movie_DVD, 3.5f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Movie_BluRay, 5.0f));

  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Game_Cartridge, 1.5f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Game_DVD, 5.0f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Game_BluRay, 9.0f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Movie_VHS, 1.5f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Movie_DVD, 3.5f));
  _mediaRentValues.insert(std::pair<MediaType, float>(MediaType::Movie_BluRay, 5.0f));

}

Catalog::~Catalog()
{
  for (unsigned int i = 0; i < _items.size(); i++)
  {
    delete _items.at(i);
  }
	_items.clear();
}

void Catalog::setCatalogType(CatalogType type)
{
	_catalogType = type;
}

CatalogType Catalog::getCatalogType() const
{
	return _catalogType;
}

void Catalog::addItem(IItem* item)
{
	if (item == nullptr)
	{
		return;
	}
	_items.push_back(item);
}

IItem* Catalog::getItem(unsigned int itemId) const
{
  for (unsigned int i = 0; i < _items.size(); i++)
  {
    IItem* a = _items.at(i);
    if (a->getItemId() == itemId)
    {
      return a;
    }
  }
  // Error: Item not found.
  return nullptr;
}

std::vector<IItem*> Catalog::getItems() const
{
  return _items;
}

float Catalog::getRentForItem(unsigned int itemId) const
{
  for (unsigned int i = 0; i < _items.size(); i++)
  {
    IItem* item = _items.at(i);
    if (item->getItemId() == itemId)
    {
      return _mediaRentValues.at(item->getMediaType());
    }
  }

  throw std::invalid_argument("Invalid item id.");
}