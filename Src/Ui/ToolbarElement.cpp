#include "Ui\ToolbarElement.h"

ToolbarElement::ToolbarElement()
{
  _title = "No title";
  _command = "";
  _elementCb = nullptr;
}

ToolbarElement::ToolbarElement(const char* title, const char* command)
{
  _title = title;
  _command = command;
  _elementCb = nullptr;
}

void ToolbarElement::setCallback(std::function<bool(const char*)> elementCb)
{
  _elementCb = elementCb;
}

bool ToolbarElement::processCommand(const char* c)
{
  if (_elementCb == nullptr)
  {
    return false;
  }

  if (std::strcmp(_command.c_str(), c) != 0)
  {
    return false;
  }

  return _elementCb(c);
}

void ToolbarElement::setTitle(const char* title)
{
  _title = title;
}

const char* ToolbarElement::getTitle() const
{
  return _title.c_str();
}

void ToolbarElement::setCommand(const char* command)
{
  _command = command;
}

const char* ToolbarElement::getCommand() const
{
  return _command.c_str();
}

std::ostream& operator<<(std::ostream& os, const ToolbarElement& element)
{
  return os << "[" << element.getCommand() << "] " << element.getTitle();
}

std::ostream& operator<<(std::ostream& os, const ToolbarElement* element)
{
  return os << "[" << element->getCommand() << "] " << element->getTitle();
}