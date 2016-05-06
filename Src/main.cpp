#include <iostream>
#include <string>
#include <vector>

#include "Core\Application.h"
#include "Data\Catalog.h"
#include "Data\Movie.h"
#include "Data\Game.h"
#include "Data\Book.h"
#include "Store\Manager.h"

int main()
{
  Catalog* c1 = new Catalog(CatalogType::Movies);
  c1->addItem(new Movie("Alien", 1979, "In the near future, a commercial spaceship intercepts a distress signal.", "20th Century Fox", GenreType::Horror | GenreType::ScienceFiction, 1, 120, MediaType::Movie_BluRay));
  c1->addItem(new Movie("Matrix", 1999, "By day he is an average computer programmer and by night a hacker known as Neo.", "Warner Bros.", GenreType::Action | GenreType::ScienceFiction, 3, 150, MediaType::Movie_BluRay));
  c1->addItem(new Movie("A Little Princess", 1992, "Sara is treated as a princess until, one day, word comes of her father’s tragic death.", "Warner Bros.", GenreType::Drama, 1, 100, MediaType::Movie_VHS));
  c1->addItem(new Movie("Monty Python and the Holy Grail", 1975, "King Arthur and his knights embark on a search for the Grail.", "EMI Films", GenreType::Comedy, 1, 96, MediaType::Movie_VHS));
  c1->addItem(new Movie("The Room", 2005, "Can you ever really trust anyone?", "Chloe Productions", GenreType::Drama, 1, 99, MediaType::Movie_DVD));
  c1->addItem(new Movie("Touching the void", 2003, "The true story of two climbers and their perilous journey.", "Pathe", GenreType::Documentary, 2, 106, MediaType::Movie_BluRay));
  c1->addItem(new Movie("Star Wars: The Empire Strikes Back", 1980, "Luke takes Jedi training with Yoda, while his friends are pursued by Darth Vader.", "20th Century Fox", GenreType::Adventure | GenreType::ScienceFiction, 6, 124, MediaType::Movie_BluRay));
  c1->addItem(new Movie("The Revenant", 2015, "A frontiersman on a fur trading expedition in the 1820s fights for survival after being mauled by a bear and left for dead by members of his own hunting team.", "20th Century Fox", GenreType::Adventure | GenreType::Drama, 10, 156, MediaType::Movie_BluRay));
  
  Catalog* c2 = new Catalog(CatalogType::Games);
  
  c2->addItem(new Game("Resident Evil 4", 2005, "Leon S. Kennedy, now a federal agent, is hired to rescue the president's daughter from a sinister cult.", "Capcom", GenreType::Action | GenreType::Horror, 5, "PlayStation 2", MediaType::Game_DVD));
  c2->addItem(new Game("Zelda: Ocarina of Time", 1998, "Through the power of the Ocarina of Time, Link travels back and forth through time to set things right again.", "Nintendo", GenreType::Adventure, 3, "Nintendo 64", MediaType::Game_Cartridge));
  c2->addItem(new Game("Pokken Tournament", 2016, "A fighting game starring Pokemon. ", "Bandai Namco", GenreType::Action, 2, "Nintendo WiiU", MediaType::Game_BluRay));
  c2->addItem(new Game("Anarchy Reigns", 2012, "An action-fighting game in which players assume the role of survivors battling their way through a post-apocalyptic world.", "Sega", GenreType::Action, 1, "Xbox 360", MediaType::Game_DVD));
  c2->addItem(new Game("Heavy Rain", 2010, "A city on the US east coast is being terrorized by the 'Origami Killer', whose victims are all discovered drowned.", "Sony", GenreType::Drama | GenreType::Horror, 1, "PlayStation 4", MediaType::Game_BluRay));
  
  Catalog* c3 = new Catalog(CatalogType::Books);
  
  c3->addItem(new Book("The Dead Zone", 1979, "John Smith awakens from a coma to discover he has a psychic detective ability.", "Viking Press", GenreType::Horror, 4, "Stephen King", MediaType::Book_Hardcover));


  ICatalogManager* cmgr = Manager::instance().catalogManager();
  cmgr->addCatalog(c1);
  cmgr->addCatalog(c2);
  cmgr->addCatalog(c3);

  Application app;
  app.run();

  return 0;
}
