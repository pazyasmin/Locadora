#pragma once

#include "Store\CatalogManager.h"
#include "Store\CustomerManager.h"
#include "Ui\MainWindow.h"

// Specifies the access to the one and only Manager instance.
class Manager
{
public:
  ~Manager();

  // Returns the global Manager instance.
  static Manager& instance()
  {
    static Manager mgr;
    return mgr;
  }

  // Returns the ICatalogManager, used to retrieve catalog data.
  ICatalogManager* catalogManager() const;

  // Returns the ICustomerManager, used to manipulate customer data.
  ICustomerManager* customerManager() const;

  // Returns the IMainWindow instance.
  IMainWindow* mainWindow() const;

  // Forbidden methods.
  Manager(const Manager& m) = delete;
  void operator=(const Manager& m) = delete;

private:
  Manager();

  ICatalogManager* _catalogManager;
  ICustomerManager* _customerManager;
  IMainWindow* _mainWindow;
};