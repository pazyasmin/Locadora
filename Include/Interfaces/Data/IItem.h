#pragma once

enum GenreType
{
  Action         = 1,
  Adventure      = 2,
  Documentary    = 4,
  Drama          = 8,
  Comedy         = 16,
  Romance        = 32,
  ScienceFiction = 64,
  Horror         = 128
};

enum MediaType
{
  Game_Cartridge,
  Game_DVD,
  Game_BluRay,
  Movie_VHS,
  Movie_DVD,
  Movie_BluRay,
  Book_Hardcover,
  Book_Paperback

};

// Represents an item to be rented, such as movie, game, etc.
class IItem
{
public:
  virtual ~IItem() {}

  // Sets the item's title.
  virtual void setTitle(const char* title) = 0;

  // Returns the item's title.
  virtual const char* getTitle() const = 0;

  // Sets the item's year of release.
  virtual void setYear(unsigned int year) = 0;

  // Gets the item's year of release.
  virtual unsigned int getYear() const = 0;

  // Sets the item's synopsis.
  virtual void setSynopsis(const char* synopsis) = 0;

  // Returns the item's synopsis.
  virtual const char* getSynopsis() const = 0;

  // Sets the item's company (movie studio, game developer, publishing company, etc).
  virtual void setCompany(const char* company) = 0;

  // Returns the item's company.
  virtual const char* getCompany() const = 0;

  // Returns the item's global id.
  virtual unsigned int getItemId() const = 0;
 
  // Sets the item's genres.
  // Note: Parameter genres will be checked in bitwise operations with each GenreType. 
  virtual void setGenres(unsigned short genres) = 0;

  // Returns existing genres.
  virtual unsigned short getGenres() const = 0;

  // Sets the item's media type.
  virtual void setMediaType(MediaType type) = 0;

  // Returns the item's media type.
  virtual MediaType getMediaType() const = 0;

  // Increases the amount of copies available for the item.
  virtual void addToAvailableCopies(unsigned int amount) = 0;

  // Decreases the amount of copies available for the item.
  virtual void removeFromAvailableCopies(unsigned int amount) = 0;

  // Returns the amount of copies available for rent.
  virtual unsigned int getAvailableCopies() const = 0;
};