#include "Interfaces\Data\IItem.h"

class IBook : public IItem
{
public:
	virtual ~IBook() {}

	virtual void setAuthor(const char* author) = 0;

	virtual const char* getAuthor() const = 0;

};