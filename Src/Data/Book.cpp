#include "Data\Book.h"

#include <cassert>

unsigned int Book::s_globalId = 0;

Book::Book(const char* title, unsigned int year, const char* synopsis, const char* company, unsigned short genres, unsigned int availableCopies, const char* author, MediaType mediaType)
{
	assert(title);
	assert(synopsis);
	assert(company);
	assert(author);

	_bookId = s_globalId;

	_year = year;
	_genres = genres;

	_title = title;
	_author = author;
	_synopsis = synopsis;
	_company = company;

	_availableCopies = availableCopies;
	_mediaType = mediaType;

	s_globalId++;
}

void Book::setTitle(const char* title)
{
	_title = title;
}

const char* Book::getTitle() const
{
	return _title.c_str();
}

void Book::setYear(unsigned int year)
{
	_year = year;
}


unsigned int Book::getYear() const
{
	return _year;
}

unsigned int Book::getItemId() const
{
	return _bookId;
}

void Book::setSynopsis(const char* synopsis)
{
	_synopsis = synopsis;
}

const char* Book::getSynopsis() const
{
	return _synopsis.c_str();
}

void Book::setCompany(const char* company)
{
	_company = company;
}

const char* Book::getCompany() const
{
	return _company.c_str();
}

void Book::setGenres(unsigned short genres)
{
	_genres = genres;
}

unsigned short Book::getGenres() const
{
	return _genres;
}

void Book::addToAvailableCopies(unsigned int amount)
{
	_availableCopies += amount;
}

void Book::removeFromAvailableCopies(unsigned int amount)
{
	_availableCopies -= amount;
}

unsigned int Book::getAvailableCopies() const
{
	return _availableCopies;
}

void Book::setAuthor(const char* author)
{
	_author = author;
}

const char* Book::getAuthor() const
{
	return _author.c_str();
}

void Book::setMediaType(MediaType type)
{
	_mediaType = type;
}

MediaType Book::getMediaType() const
{
	return _mediaType;
}

std::ostream& operator<<(std::ostream& os, const Book* item)
{
	os << item->getTitle() << " by " << item->getAuthor() <<", " << item->getCompany() << " (" << item->getYear() << ")  " << std::endl
		<< "Synopsis: " << item->getSynopsis();
	return os;
}