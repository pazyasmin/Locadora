#pragma once

class IApplication
{
public:
  virtual ~IApplication() {}

  // Runs the application's main event loop, which consists of:
  // 1. Waits for user input.
  // 2. Process command.
  // 3. Updates interface accordingly.
  virtual void run() = 0;
};