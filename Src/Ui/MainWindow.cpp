#include "Ui\MainWindow.h"

#include <algorithm>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <typeinfo>

#include "Data\Customer.h"
#include "Data\Movie.h"
#include "Data\Game.h"
#include "Data\RentalOrder.h"
#include "Store\Manager.h"
#include "Ui\ToolbarElement.h"

#define WINDOW_SEPARATOR "_________________________________________________________________"
#define FRAME_SEPARATOR  "----- "

const std::string MainWindow::s_customerControlPanelName = "User Control Panel";
const std::string MainWindow::s_orderManagementPanelName = "Rentals Management";

MainWindow::MainWindow()
{
  // Add user button.
  IToolbarElement* addCustomer = new ToolbarElement("Register New Customer", "N");
  std::function<bool(const char*)> addCustomerCb = [this](const char* c)
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string customerName = _getCustomerName();
    if (!customerName.empty())
    {
      try
      {
        ICustomer* c = Manager::instance().customerManager()->getCustomer(customerName.c_str());

        std::cout << std::endl
                  << "  There is already a customer named " << c->getName() << "." << std::endl << std::endl
                  << "Press any key to continue...";
        _getch();

        return true;
      }
      catch (...)
      {
        // Proceed to add a new customer.
      }

      ICustomer* customer = new Customer(customerName.c_str());
      Manager::instance().customerManager()->addCustomer(customer);

      std::cout << std::endl
                << "  Added customer " << customer->getName() << " under the ID number " << customer->getCustomerId() << "." << std::endl << std::endl
                << "Press any key to continue...";
      _getch();
    }

    return true;
  };
  addCustomer->setCallback(addCustomerCb);
  _toolbarElements.push_back(addCustomer);
  _elementFrames.insert(std::pair<const IToolbarElement*, std::string>(addCustomer, s_customerControlPanelName));

  // Check customer history button.
  IToolbarElement* checkHistory = new ToolbarElement("Check Customer History", "H");
  std::function<bool(const char*)> checkHistoryCb = [this](const char* c)
  {
    // Registered customer to retrieve the history.
    ICustomer* customer = nullptr;
    std::string customerName;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
      customerName = _getCustomerName();
      if (customerName.empty())
      {
        // User aborted.
        return true;
      }
      try
      {
        customer = Manager::instance().customerManager()->getCustomer(customerName.c_str());
      }
      catch (...)
      {
        std::cin.clear();
        std::cout << std::endl
                  << "Invalid user name." << std::endl;
        continue;
      }

      break;
    }

    std::cout << std::endl
              << FRAME_SEPARATOR "Open rental orders for customer " << customer->getName() << "." << std::endl;
    std::vector<IRentalOrder*> openOrders = Manager::instance().customerManager()->getOpenOrdersForCustomer(customer->getCustomerId());
    if (openOrders.size() > 0)
    {
      for (unsigned int i = 0; i < openOrders.size(); i++)
      {
        std::cout << std::endl
                  << "[" << i + 1 << "] " << dynamic_cast<const RentalOrder*>(openOrders.at(i)) << std::endl;
      }
    }
    else
    {
      std::cout << std::endl
                << "  This customer has no open rental orders." << std::endl;
    }

    std::cout << std::endl
              << FRAME_SEPARATOR "Closed rental orders for customer " << customer->getName() << "." << std::endl;
    std::vector<const IRentalOrder*> closedOrders = Manager::instance().customerManager()->getClosedOrdersForCustomer(customer->getCustomerId());
    if (closedOrders.size() > 0)
    {
      for (unsigned int i = 0; i < closedOrders.size(); i++)
      {
        std::cout << std::endl
                  << "[" << i + 1 << "] " << dynamic_cast<const RentalOrder*>(closedOrders.at(i)) << std::endl;
      }
    }
    else
    {
      std::cout << std::endl
                << "  This customer has no closed orders." << std::endl;
    }

    std::cout << std::endl
              << "Press any key to continue...";
    _getch();

    return false;
  };
  checkHistory->setCallback(checkHistoryCb);
  _toolbarElements.push_back(checkHistory);
  _elementFrames.insert(std::pair<const IToolbarElement*, std::string>(checkHistory, s_customerControlPanelName));

  // New rental order button.
  IToolbarElement* newOrder = new ToolbarElement("Add new Rental Order", "A");
  std::function<bool(const char*)> newOrderCb = [this](const char* c)
  {
    // Registered customer to associate to this rental order.
    ICustomer* customer = nullptr;
    std::string customerName;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
      customerName = _getCustomerName();
      if (customerName.empty())
      {
        // User aborted.
        return true;
      }
      try
      {
        customer = Manager::instance().customerManager()->getCustomer(customerName.c_str());

        unsigned int customerOrderCount = Manager::instance().customerManager()->getOpenOrdersForCustomer(customer->getCustomerId()).size();
        if (customerOrderCount > 0)
        {
          std::cin.clear();
          std::cout << std::endl
            << "Notice: This customer has " << customerOrderCount << " open rental order(s)." << std::endl << std::endl
            << "Press any key to continue...";
          _getch();
          std::cout << std::endl;
        }
      }
      catch (...)
      {
        std::cin.clear();
        std::cout << std::endl
                  << "Invalid user name." << std::endl;
        continue;
      }

      break;
    }

    std::vector<IItem*> orderItems;
    orderItems = _getOrderItems();
    if (orderItems.empty())
    {
      // User aborted.
      return true;
    }

    // Gets the order date.
    std::time_t t = std::time(0);
    char d[30];
    ctime_s(d, sizeof(d), &t);
    std::string date = d;
    IRentalOrder* order = new RentalOrder(date.c_str());
    // Add items.
    for (unsigned int i = 0; i < orderItems.size(); i++)
    {
      order->addItem(orderItems.at(i));
    }
    // Finally, add it to the user history.
    customer->addRentalOrder(order);

    std::cout << std::endl
      << "  Added rental under the ID number " << order->getOrderId() << " to history of customer " << customer->getName() << "." << std::endl << std::endl
      << "Payments are done when the items are returned on the Return Rentals menu." << std::endl << std::endl
      << "Press any key to continue...";
    _getch();

    return true;
  };
  newOrder->setCallback(newOrderCb);
  _toolbarElements.push_back(newOrder);
  _elementFrames.insert(std::pair<const IToolbarElement*, std::string>(newOrder, s_orderManagementPanelName));

  // Return rental button.
  IToolbarElement* returnRental = new ToolbarElement("Return Rentals", "R");
  std::function<bool(const char*)> returnRentalCb = [this](const char* c)
  {
    // Registered customer to retrieve orders from.
    ICustomer* customer = nullptr;
    std::string customerName;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
      customerName = _getCustomerName();
      if (customerName.empty())
      {
        // User aborted.
        return true;
      }
      try
      {
        customer = Manager::instance().customerManager()->getCustomer(customerName.c_str());
      }
      catch (...)
      {
        std::cin.clear();
        std::cout << std::endl
          << "Invalid customer name." << std::endl;
        continue;
      }

      break;
    }

    _closeOrdersForCustomer(customer);

    std::cout << std::endl
              << "Press any key to continue...";
    _getch();

    return false;
  };
  returnRental->setCallback(returnRentalCb);
  _toolbarElements.push_back(returnRental);
  _elementFrames.insert(std::pair<const IToolbarElement*, std::string>(returnRental, s_orderManagementPanelName));
}

MainWindow::~MainWindow()
{
  _toolbarElements.clear();
}

void MainWindow::processCommand(const char* c)
{
  // Toolbar elements.
  for (unsigned int i = 0; i < _toolbarElements.size(); i++)
  {
    if (_toolbarElements.at(i)->processCommand(c))
    {
      return;
    }
  }
}

void MainWindow::draw()
{
  std::cout << std::endl << "\t\t ::: Rental Store ::: " << std::endl
            << WINDOW_SEPARATOR
            << std::endl << std::endl;

  // User Control Panel controls.
  std::cout << FRAME_SEPARATOR << s_customerControlPanelName << std::endl << std::endl;
  for (unsigned int i = 0; i < _toolbarElements.size(); i++)
  {
    IToolbarElement* t = _toolbarElements.at(i);
    if (_elementFrames.at(t) == s_customerControlPanelName)
    {
      std::cout << dynamic_cast<ToolbarElement*>(_toolbarElements.at(i)) << std::endl;
    }
  }

  std::cout << std::endl;

  // Order Management controls.
  std::cout << FRAME_SEPARATOR << s_orderManagementPanelName << std::endl << std::endl;
  for (unsigned int i = 0; i < _toolbarElements.size(); i++)
  {
    IToolbarElement* t = _toolbarElements.at(i);
    if (_elementFrames.at(t) == s_orderManagementPanelName)
    {
      std::cout << dynamic_cast<ToolbarElement*>(_toolbarElements.at(i)) << std::endl;
    }
  }

  std::cout << std::endl
            << WINDOW_SEPARATOR
            << std::endl << std::endl;
}

std::string MainWindow::_getCustomerName()
{
  std::string customerName;
  while (true)
  {
    std::cout << std::endl
              << "Please enter the customer name ([B] to abort): ";
    std::cin.clear();
    std::getline(std::cin, customerName);

    if (customerName == "B")
    {
      break;
    }
    else if (customerName.length() == 0)
    {
      std::cout << std::endl
                << "Customer name cannot be empty." << std::endl;
      continue;
    }

    return customerName;
  }

  return std::string();
}

std::vector<IItem*> MainWindow::_getOrderItems()
{
  std::vector<IItem*> itemsInOrder;
  std::string command;
  while (true)
  {
    // Item catalogs.
    std::vector<const char*> catalogNames = Manager::instance().catalogManager()->getCatalogNames();
    std::cout << std::endl
              << FRAME_SEPARATOR "Catalog list:" << std::endl;
    for (unsigned int i = 0; i < catalogNames.size(); i++)
    {
      std::cout << std::endl
                << "[" << i + 1 << "] " << catalogNames.at(i) << std::endl;
    }
    std::cout << std::endl
              << "Please select an item catalog ([B] to abort or [C] to continue): ";
    std::cin.clear();
    std::getline(std::cin, command);
    if (command == "B")
    {
      return std::vector<IItem*>();
    }
    if (command == "C")
    {
      if (itemsInOrder.size() > 0)
      {
        return itemsInOrder;
      }
      else
      {
        std::cout << std::endl
          << "Please add items to the rental order before proceeding." << std::endl;
        continue;
      }
    }

    int selection = -1;
    // std::stoi throws a std::invalid_argument exception if no conversion could be performed.
    // Therefore, simply abort processing of input command if an exception is caught.
    try
    {
      selection = std::stoi(command) - 1;
    }
    catch (...)
    {
      std::cout << std::endl
                << "Invalid selection." << std::endl;
      continue;
    }

    std::string catalogName;
    // If command was successfully converted, check if it is within the array bounds.
    if (selection >= 0 && selection < static_cast<int>(catalogNames.size()))
    {
      catalogName = catalogNames.at(static_cast<unsigned int>(selection));
    }
    else
    {
      std::cout << std::endl
        << "Invalid selection." << std::endl;
      continue;
    }

    // Items from the selected catalog.
    std::vector<IItem*> itemsInCatalog;
    try
    {
      itemsInCatalog = Manager::instance().catalogManager()->getItemsFromCatalog(catalogName.c_str());
    }
    catch (...)
    {
      std::cout << std::endl
                << "Invalid selection." << std::endl;
      continue;
    }

    std::cout << std::endl
              << FRAME_SEPARATOR "Items in catalog " << catalogName << ":" << std::endl;
    for (unsigned int i = 0; i < itemsInCatalog.size(); i++)
    {
      std::cout << std::endl;
      // Cast to the concrete IItem type.
      if (dynamic_cast<Movie*>(itemsInCatalog.at(i)) != nullptr)
      {
        std::cout << dynamic_cast<Movie*>(itemsInCatalog.at(i)) << std::endl;
      }
      else if (dynamic_cast<Game*>(itemsInCatalog.at(i)) != nullptr)
      {
        std::cout << dynamic_cast<Game*>(itemsInCatalog.at(i)) << std::endl;
      }
      else
      {
        throw std::bad_cast("Invalid item type.");
      }

      if (std::find(itemsInOrder.begin(), itemsInOrder.end(), itemsInCatalog.at(i)) != itemsInOrder.end())
      {
        std::cout << "Item already added. [" << i + 1 << "] to remove." << std::endl;
      }
      else
      {
        std::cout << "[" << i + 1 << "] Add item." << std::endl;
      }
    }
    std::cout << std::endl
              << "Please select an item ([B] to abort or [C] to continue): ";
    std::cin.clear();
    std::getline(std::cin, command);
    if (command == "B")
    {
      return std::vector<IItem*>();
    }
    if (command == "C")
    {
      if (itemsInOrder.size() > 0)
      {
        return itemsInOrder;
      }
      else
      {
        std::cout << std::endl
                  << "Please add items to the order before proceeding." << std::endl;
        continue;
      }
    }
    selection = -1;
    // std::stoi throws a std::invalid_argument exception if no conversion could be performed.
    // Therefore, simply abort processing of input command if an exception is caught.
    try
    {
      selection = std::stoi(command) - 1;
    }
    catch (...)
    {
      std::cout << std::endl
        << "Invalid selection." << std::endl;
      continue;
    }

    // If command was successfully converted, check if it is within the array bounds.
    if (selection >= 0 && selection < static_cast<int>(itemsInCatalog.size()))
    {
      // Remove if item was already added.
      if (std::find(itemsInOrder.begin(), itemsInOrder.end(), itemsInCatalog.at(selection)) != itemsInOrder.end())
      {
        IItem* item = itemsInCatalog.at(static_cast<unsigned int>(selection));

        std::vector<IItem*>::iterator it = itemsInOrder.begin();
        itemsInOrder.erase(it + selection);

        std::cout << std::endl
                  << "Removed " << item->getTitle() << " (" << item->getYear() << ") from the rental order" << std::endl;
      }
      else
      {
        IItem* item = itemsInCatalog.at(static_cast<unsigned int>(selection));
        itemsInOrder.push_back(item);
        std::cout << std::endl
                  << "Added " << item->getTitle() << " (" << item->getCompany() << ") to the rental order." << std::endl;

      }
    }
    else
    {
      std::cout << std::endl
        << "Invalid selection." << std::endl;
      continue;
    }
  }
}

void MainWindow::_closeOrdersForCustomer(ICustomer* customer)
{
  std::string command;

  while (true)
  {
    std::cout << std::endl
      << FRAME_SEPARATOR "Open rental orders for customer " << customer->getName() << "." << std::endl;
    std::vector<IRentalOrder*> openOrders = Manager::instance().customerManager()->getOpenOrdersForCustomer(customer->getCustomerId());
    if (openOrders.size() > 0)
    {
      for (unsigned int i = 0; i < openOrders.size(); i++)
      {
        std::cout << std::endl
          << dynamic_cast<const RentalOrder*>(openOrders.at(i)) << std::endl
          << "[" << i + 1 << "] Close rental order." << std::endl;
      }

      std::cout << std::endl
                << "Please select a rental order to close ([B] to abort): ";
      std::cin.clear();
      std::getline(std::cin, command);
      if (command == "B")
      {
        return;
      }
      int selection = -1;
      // std::stoi throws a std::invalid_argument exception if no conversion could be performed.
      // Therefore, simply abort processing of input command if an exception is caught.
      try
      {
        selection = std::stoi(command) - 1;
      }
      catch (...)
      {
        std::cout << std::endl
          << "Invalid selection." << std::endl;
        continue;
      }

      // If command was successfully converted, check if it is within the array bounds.
      if (selection >= 0 && selection < static_cast<int>(openOrders.size()))
      {
        IRentalOrder* o = openOrders.at(selection);

        

        std::cout << std::endl
          << "Payment methods:" << std::endl << std::endl
          << "[1] Cash" << std::endl << std::endl
          << "[2] Credit/debit card" << std::endl << std::endl
          << "Please select a payment method ([B] to abort): ";
        std::cin.clear();
        std::getline(std::cin, command);
        if (command == "B")
        {
          return;
        }
        selection = -1;
        // std::stoi throws a std::invalid_argument exception if no conversion could be performed.
        // Therefore, simply abort processing of input command if an exception is caught.
        try
        {
          selection = std::stoi(command);

          if (!(selection == 1 || selection == 2))
          {
            throw std::exception("Selection out of bounds.");
          }
        }
        catch (...)
        {
          std::cout << std::endl
                    << "Invalid selection." << std::endl << std::endl
                    << "Press any key to continue...";
          _getch();
          continue;
        }

        switch (selection)
        {
        case 1:
          _processCashPayment(o);
          break;
        case 2:
          _processCardPayment(o);
          break;
        default:
          std::cout << std::endl
                    << "An error has occurred. Please try again." << std::endl << std::endl
                    << "Press any key to continue...";
          _getch();
          return;
        }
      }
      else
      {
        std::cout << std::endl
                  << "Invalid selection." << std::endl << std::endl
                  << "Press any key to continue...";
        _getch();
        continue;
      }
    }
    else
    {
      std::cout << std::endl
                << "  This customer has no open rental orders." << std::endl;
      return;
    }
  }
}

void MainWindow::_processCashPayment(IRentalOrder* order)
{
  float orderValue = _getTotalOrderValue(order);
  std::string command;
  float cashAmount;
  // Display only two decimal digits.
  std::cout << std::endl
            << std::setprecision(2) << std::fixed
            << "Total value: R$ " << orderValue << std::endl << std::endl
            << "Please enter the amount for cash payment ([B] to abort): ";

  std::cin.clear();
  std::getline(std::cin, command);
  if (command == "B")
  {
    return;
  }
  // std::stoi throws a std::invalid_argument exception if no conversion could be performed.
  // Therefore, simply abort processing of input command if an exception is caught.
  try
  {
    cashAmount = std::stof(command);

    if ((orderValue - cashAmount) > 0.001f)
    {
      std::cout << std::endl
        << "Invalid amount." << std::endl << std::endl
        << "Press any key to continue...";
      _getch();
      return;
    }

    order->closeOrder();

    float change = cashAmount - orderValue;
    std::cout << std::endl
              << std::setprecision(2) << std::fixed
              << "Payment complete." << std::endl << std::endl
              << "Change: R$ " << ((change > 0.001f) ? change : 0.00f) << std::endl << std::endl;
    std::cout << "Press any key to continue...";
    _getch();
  }
  catch (...)
  {
    std::cout << std::endl
      << "Invalid amount." << std::endl << std::endl
      << "Press any key to continue...";
    _getch();
  }
}

void MainWindow::_processCardPayment(IRentalOrder* order)
{
  float orderValue = _getTotalOrderValue(order);

  // Display only two decimal digits.
  std::cout << std::endl
            << std::setprecision(2) << std::fixed
            << "Total value: R$ " << orderValue << std::endl << std::endl
            << "Press any key to insert credit card.";
  _getch();

  std::cout << std::endl << std::endl
    << "Press any key to type password: ";
  _getch();

  std::cout << "******";

  // Randomly compute payment success/failure to simulate different scenarios.
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, 100);
  int checkoutProb = distr(eng);

  // 75% chances of success.
  if (checkoutProb <= 75)
  {
    order->closeOrder();

    std::cout << std::endl << std::endl
      << "Payment complete." << std::endl << std::endl
      << "Press any key to continue...";
    _getch();
  }
  else
  {
    std::cout << std::endl << std::endl
      << "Error: Transaction declined by bank. Please try another card." << std::endl << std::endl
      << "Press any key to continue...";
    _getch();
  }
}

float MainWindow::_getTotalOrderValue(IRentalOrder* order)
{
  float orderValue = 0.0f;

  std::vector<IItem*> items = order->getItems();
  for (unsigned int i = 0; i < items.size(); i++)
  {
    orderValue += Manager::instance().catalogManager()->getRentForItem(items.at(i)->getItemId());
  }

  return orderValue;
}