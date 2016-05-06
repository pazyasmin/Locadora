#include "Interfaces\Data\IBook.h"

#include <string>

class Book : public IBook
{
	friend std::ostream& operator<<(std::ostream& os, const Book* item);
public:
	Book(const char* title, unsigned int year, const char* synopsis, const char* company, unsigned short genres, unsigned int availableCopies, const char* author, MediaType mediaType);

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

	// Sets the item's company (Book studio, book developer, publishing company, etc).
	void setCompany(const char* company) override;

	// Returns the item's company.
	const char* getCompany() const override;

	// Sets the item's genres.
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

	// Sets the book's author.
	void setAuthor(const char* author) override;

	// Returns the book's author.
	const char* getAuthor() const override;

	// Sets the book's media type.
	void setMediaType(MediaType type) override;

	// Returns the book's media type.
	MediaType getMediaType() const override;

	// Forbidden methods.
	Book::Book() = delete;
	Book::Book(const Book& b) = delete;
	void operator=(const Book& b) = delete;

private:
	static unsigned int s_globalId;

	unsigned int _year;
	unsigned int _bookId;
	unsigned short _genres; 
	unsigned short _pages;

	std::string _title;
	std::string _author;
	std::string _company;
	std::string _synopsis;

	unsigned int _availableCopies;

	MediaType _mediaType;

};