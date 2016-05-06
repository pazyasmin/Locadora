#pragma once

// Responsible for storing and managing the store's interface elements.
class IMainWindow
{
public:
  virtual ~IMainWindow() {}

  // Receives a command from the application and forwards it to its interface elements.
  // A command is a character input entered by the rental shop cashier.
  virtual void processCommand(const char* c) = 0;

  // Draws the contents of the main window.
  virtual void draw() = 0;
};