#pragma once

#include "Interfaces\Ui\IToolbarElement.h"

#include <string>

class ToolbarElement : public IToolbarElement
{
  // Output operator; prints this element's data.
  friend std::ostream& operator<<(std::ostream& os, const ToolbarElement& element);
  friend std::ostream& operator<<(std::ostream& os, const ToolbarElement* element);

public:
  ToolbarElement();
  ToolbarElement(const char* title, const char* command);

  // Assigns the element callback.
  // The callback is called by processCommand when the user enters a command.
  void setCallback(std::function<bool(const char*)> elementCb) override;

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  bool processCommand(const char* c) override;

  // Sets this element's ui display label.
  void setTitle(const char* title) override;

  // Returns this element's ui display label.
  const char* getTitle() const override;

  // Sets this element's ui command.
  void setCommand(const char* command) override;

  // Returns this element's ui command.
  const char* getCommand() const override;

private:
  // Callback called by processCommand that receives the command sent by the user and processes it.
  std::function<bool(const char*)> _elementCb;

  std::string _title;
  std::string _command;
};