#include "Core\Application.h"

#include <string>
#include <iostream>

#include "Store\Manager.h"

Application::Application()
{

}

void Application::run()
{
  while (true)
  {
    
    system("cls");

    Manager::instance().mainWindow()->draw();

    std::cout << "[Q] Quit." << std::endl << std::endl;
    std::cout << "Please input operation command: ";
    std::string command;
    std::cin >> command;

    if (strcmp("Q", static_cast<const char*>(command.c_str())) == 0)
    {
      return;
    }

    Manager::instance().mainWindow()->processCommand(static_cast<const char*>(command.c_str()));
  }
}