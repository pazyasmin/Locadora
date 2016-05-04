#include "Data\Movie.h"

#include <cassert>

unsigned int Movie::s_globalId = 0;

Movie::Movie(const char* title, unsigned int year, const char* synopsis, const char* company, unsigned short genres, unsigned int availableCopies, unsigned int length, MediaType mediaType)
{
  assert(title);
  assert(synopsis);
  assert(company);

  _movieId = s_globalId;

  _year = year;
  _length = length;
  _genres = genres;

  _title = title;
  _synopsis = synopsis;
  _company = company;

  _availableCopies = availableCopies;
  _mediaType = mediaType;

  s_globalId++;
}

void Movie::setTitle(const char* title)
{
  _title = title;
}

const char* Movie::getTitle() const
{
  return _title.c_str();
}

void Movie::setYear(unsigned int year)
{
	_year = year;
}


unsigned int Movie::getYear() const
{
	return _year;
}

unsigned int Movie::getItemId() const
{
  return _movieId;
}

void Movie::setSynopsis(const char* synopsis)
{
  _synopsis = synopsis;
}

const char* Movie::getSynopsis() const
{
  return _synopsis.c_str();
}

void Movie::setCompany(const char* company)
{
  _company = company; 
}

const char* Movie::getCompany() const
{
  return _company.c_str();
}

void Movie::setGenres(unsigned short genres)
{
  _genres = genres; 
}

unsigned short Movie::getGenres() const
{
  return _genres;
}

void Movie::addToAvailableCopies(unsigned int amount)
{
  _availableCopies += amount;
}

void Movie::removeFromAvailableCopies(unsigned int amount)
{
  _availableCopies -= amount; 
}

unsigned int Movie::getAvailableCopies() const
{
  return _availableCopies;
}

void Movie::setLength(unsigned int length)
{
  _length = length;
}

unsigned int Movie::getLength() const
{
  return _length;
}

void Movie::setMediaType(MediaType type)
{
  _mediaType = type; 
}

MediaType Movie::getMediaType() const
{
  return _mediaType;
}

std::ostream& operator<<(std::ostream& os, const Movie* item)
{
	os << item->getTitle() << " (" << item->getYear() << "), " << item->getCompany() << ", " << item->getLength() << " min." << std::endl
		<< "Synopsis: " << item->getSynopsis() << std::endl;
  return os;
}