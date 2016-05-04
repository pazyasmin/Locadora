#pragma once

// Describes a basic text-based interface element.
class IUiElement
{
public:
  virtual ~IUiElement() {}

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the rental shop cashier.
  // Returns true if the given command could be processed.
  virtual bool processCommand(const char* c) = 0;
};