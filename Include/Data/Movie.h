#pragma once

#include "Interfaces\Data\IMovie.h"

#include <string>

class Movie : public IMovie
{
  friend std::ostream& operator<<(std::ostream& os, const Movie* item);
  public:
    Movie(const char* title, unsigned int year, const char* synopsis, const char* company, unsigned short genres, unsigned int availableCopies, unsigned int length, MediaType mediaType);

    // Sets the item's title.
    void setTitle(const char* title) override;

    // Returns the item's title.
    const char* getTitle() const override;

	// Sets the item's year of release.
	void setYear(unsigned int year) override;

	// Returns the item's year of release.
	unsigned int getYear() const override;

    // Returns the item's global id.
    unsigned int getItemId() const override;

    // Sets the item's synopsis.
    void setSynopsis(const char* synopsis) override;

    // Returns the item's synopsis.
    const char* getSynopsis() const override;

    // Sets the item's company (movie studio, game developer, publishing company, etc).
    void setCompany(const char* company) override;

    // Returns the item's company.
    const char* getCompany() const override;

    // Sets the item's genres. One item can belong to multiple genres.
    // Note: Parameter genres will be checked in bitwise operations with each GenreType (yet to be implemented)
    void setGenres(unsigned short genres) override;

    // Returns the item's genres.
    unsigned short getGenres() const override;

    // Adds the given amount to this item's number of available items.
    void addToAvailableCopies(unsigned int amount) override;

    // Decreases the amount of items available.
    // Note: Assumes the given amount is NOT greater than the current number of available items.
    void removeFromAvailableCopies(unsigned int amount) override;

    // Returns the amount of items available for rent.
    unsigned int getAvailableCopies() const override;

    // Sets the movie's length.
    void setLength(unsigned int length) override;

    // Returns the movie's length in seconds.
    unsigned int getLength() const override;

    // Sets the movie's media type.
    void setMediaType(MediaType type) override;

    // Returns the movie's media type.
    MediaType getMediaType() const override;

    // Forbidden methods.
    Movie::Movie()                 = delete;
    Movie::Movie(const Movie& m)   = delete;
    void operator=(const Movie& m) = delete;

private:
    static unsigned int s_globalId;

    unsigned int _movieId;
    unsigned int _length;
	unsigned int _year;
	unsigned short _genres;

    std::string _title;
    std::string _synopsis;
    std::string _company;

    unsigned int _availableCopies;

    MediaType _mediaType;

};