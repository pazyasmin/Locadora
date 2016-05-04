#pragma once

#include "Interfaces\Data\IItem.h"

// Describes the interface of a video/movie item.
class IMovie : public IItem
{
public:
  virtual ~IMovie() {}

  // Sets the movie's length.
  virtual void setLength(unsigned int length) = 0;

  // Returns the movie's length in seconds.
  virtual unsigned int getLength() const = 0;
};