#include "Interfaces\Data\IItem.h"

// Describes the interface of a game item.
class IGame: public IItem
{
public:
	virtual ~IGame() {}

	// Sets the game's platform.
	virtual void setPlatform(const char* platform) = 0;

	// Returns the game's platform.
	virtual const char* getPlatform() const = 0;
};