#include "Data\Game.h"

#include <cassert>

unsigned int Game::s_globalId = 0;

Game::Game(const char* title, unsigned int year, const char* synopsis, const char* company, unsigned short genres, unsigned int availableCopies, const char* platform, MediaType mediaType)
{
	assert(title);
	assert(synopsis);
	assert(company);
	assert(platform);

	_gameId = s_globalId;

	_year = year;
	_genres = genres;

	_title = title;
	_platform = platform;
	_synopsis = synopsis;
	_company = company;

	_availableCopies = availableCopies;
	_mediaType = mediaType;

	s_globalId++;
}

void Game::setTitle(const char* title)
{
	_title = title;
}

const char* Game::getTitle() const
{
	return _title.c_str();
}

void Game::setYear(unsigned int year)
{
	_year = year;
}


unsigned int Game::getYear() const
{
	return _year;
}

unsigned int Game::getItemId() const
{
	return _gameId;
}

void Game::setSynopsis(const char* synopsis)
{
	_synopsis = synopsis;
}

const char* Game::getSynopsis() const
{
	return _synopsis.c_str();
}

void Game::setCompany(const char* company)
{
	_company = company;
}

const char* Game::getCompany() const
{
	return _company.c_str();
}

void Game::setGenres(unsigned short genres)
{
	_genres = genres;
}

unsigned short Game::getGenres() const
{
	return _genres;
}

void Game::addToAvailableCopies(unsigned int amount)
{
	_availableCopies += amount;
}

void Game::removeFromAvailableCopies(unsigned int amount)
{
	_availableCopies -= amount;
}

unsigned int Game::getAvailableCopies() const
{
	return _availableCopies;
}

void Game::setPlatform(const char* platform)
{
	_platform = platform;
}

const char* Game::getPlatform() const
{
	return _platform.c_str();
}

void Game::setMediaType(MediaType type)
{
	_mediaType = type;
}

MediaType Game::getMediaType() const
{
	return _mediaType;
}

std::ostream& operator<<(std::ostream& os, const Game* item)
{
	os << item->getTitle() << " (" << item->getYear() << "), " << item->getCompany() << ", for " << item->getPlatform() << std::endl
		<< "Synopsis: " << item->getSynopsis();
	return os;
}