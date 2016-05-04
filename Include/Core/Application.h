#pragma once

#include "Interfaces\Core\IApplication.h"
#include "Ui\MainWindow.h"

class Application : public IApplication
{
public:
  Application();

  // Runs the application's main event loop, which consists of:
  // 1. Waits for user input.
  // 2. Process command.
  // 3. Updates interface accordingly.
  void run() override;
};
