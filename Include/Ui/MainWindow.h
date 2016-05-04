#pragma once

#include "Interfaces\Ui\IMainWindow.h"

#include <map>
#include <vector>

class ICustomer;
class IItem;
class IRentalOrder;
class IToolbarElement;

class MainWindow : public IMainWindow
{
public:
  MainWindow();
  ~MainWindow();

  // Receives a command from the application and forwards it to its interface elements.
  // A command is a simple character input entered by the user while browsing the store.
  void processCommand(const char* c) override;

  // Draws the contents of the main window.
  void draw() override;

  // Forbidden methods.
  MainWindow(const MainWindow& m)     = delete;
  void operator=(const MainWindow& m) = delete;

private:
  static const std::string s_customerControlPanelName;
  static const std::string s_orderManagementPanelName;

  std::string _getCustomerName();
  std::vector<IItem*> _getOrderItems();
  void _closeOrdersForCustomer(ICustomer* customer);
  void _closeOrder(IRentalOrder* order);
  void _processCashPayment(IRentalOrder* order);
  void _processCardPayment(IRentalOrder* order);
  float _getTotalOrderValue(IRentalOrder* order);

  // Command buttons.
  std::vector<IToolbarElement*> _toolbarElements;

  // Maps an element to its frame name.
  std::map<const IToolbarElement*, std::string> _elementFrames;
};