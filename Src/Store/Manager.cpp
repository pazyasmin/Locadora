#include "Store\Manager.h"

Manager::Manager()
{
  _catalogManager = new CatalogManager();
  _customerManager = new CustomerManager();
  _mainWindow = new MainWindow();
}

Manager::~Manager()
{
  delete _catalogManager;
  delete _customerManager;
  delete _mainWindow;
}

ICatalogManager* Manager::catalogManager() const
{
  return _catalogManager;
}

ICustomerManager* Manager::customerManager() const
{
  return _customerManager;
}

IMainWindow* Manager::mainWindow() const
{
  return _mainWindow;
}