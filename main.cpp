// main.cpp
#include <iostream>
#include <chrono>
#include <ctime>
//#include <regex>
#include <Python.h>


bool getStockData(std::string symbol, std::string start_date, std::string end_date) {
  const char* symbol_cstr = symbol.c_str();
  const char* start_cstr = start_date.c_str();
  const char* end_cstr = end_date.c_str();

  // Initialize the Python interpreter
  Py_Initialize();

  // Import the Python module
  PyRun_SimpleString("import sys\nsys.path.append('./python')");
  PyObject* pName = PyUnicode_DecodeFSDefault("get_stock_data");
  PyObject* pModule = PyImport_Import(pName);
  Py_XDECREF(pName);

  if (pModule != NULL) {
    // Get a reference to the Python function
    PyObject* pFunc = PyObject_GetAttrString(pModule, "fetch_and_store_stock_data");

    if (pFunc && PyCallable_Check(pFunc)) {
      // Prepare arguments and call the Python function
      PyObject* pArgs = PyTuple_Pack(4,
        PyUnicode_DecodeFSDefault(symbol_cstr),  // Replace with your symbol
        PyUnicode_DecodeFSDefault(start_cstr),  // Replace with your start_date
        PyUnicode_DecodeFSDefault(end_cstr),  // Replace with your end_date
        PyUnicode_DecodeFSDefault("stock_data.db")  // Replace with your database_path
      );

      PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
      Py_XDECREF(pArgs);

      if (pValue != NULL) {
        Py_XDECREF(pValue);
      } else {
        PyErr_Print();  // Print error message if the function call failed
        return false;
      }
      Py_XDECREF(pFunc);
    } else {
      PyErr_Print();  // Print error message if the function is not callable
      return false;
    }
    Py_XDECREF(pModule);
  } else {
    PyErr_Print();  // Print error message if the module import failed
    return false;
  }

  // Finalize the Python interpreter
  Py_Finalize();

  return true;

}

std::string getTodayDate() {
  // Get the current time point
  auto now = std::chrono::system_clock::now();

  // Convert to time_t
  std::time_t time = std::chrono::system_clock::to_time_t(now);

  // Format the time as a string
  std::tm tmStruct = *std::localtime(&time);
  char buffer[11];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tmStruct);

  return std::string(buffer);
}

std::string getDateFiveYearsAgo() {
  // Get the current time point
  auto now = std::chrono::system_clock::now();

  // Subtract 5 years
  auto fiveYearsAgo = now - std::chrono::hours(24 * 365 * 5);

  // Convert to time_t
  std::time_t time = std::chrono::system_clock::to_time_t(fiveYearsAgo);

  // Format the time as a string
  std::tm tmStruct = *std::localtime(&time);
  char buffer[11];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tmStruct);

  return std::string(buffer);
}

// bool isValidDate(const std::string& date) {
//   // Date should be in the format YYYY-MM-DD
//   return std::regex_match(date, std::regex("^\\d{4}-\\d{2}-\\d{2}$"));
// }

// bool isValidStartDate(const std::string& startDate) {
//   // Start date should not be in the future
//   return isValidDate(startDate);
// }

// bool isValidEndDate(const std::string& endDate, const std::string& startDate) {
//   // End date should not be in the future or before the start date
//   return isValidDate(endDate) && endDate >= startDate;
// }

bool getInput() {
  std::string end_date = getTodayDate();
  std::string start_date = getDateFiveYearsAgo();

  std::cout << "--------------------------------------------------------------\n";
  std::cout << "  Default Stock Data Information:\n";
  std::cout << "  Stock Symbol: AAPL\n";
  std::cout << "  Start Date: " << start_date << "\n";
  std::cout << "  End Date: " << end_date << "\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "  To keep this default, type 'default'.\n";
  std::cout << "  If you want to change the stock data, type 'change'.\n";
  std::cout << "--------------------------------------------------------------\n";

  std::string input;
  std::cin >> input;

  if (input == "default") {
    getStockData("AAPL", start_date, end_date);
  } 
  // else {
  //   std::string symbol;
  //   std::string start;
  //   std::string end;

  //   std::cout << "Enter valid stock symbol (Case Sensitive): ";
  //   std::cin >> symbol;
  //   std::cout << "Enter start date (YYYY-MM-DD): ";
  //   std::cin >> start;
  //   std::cout << "Enter end date (YYYY-MM-DD): ";
  //   std::cin >> end;

  //   // Check validity and print errors if any
  //   if (!isValidStartDate(start)) {
  //     std::cout << "Error: Invalid start date. Please provide a valid date in the format YYYY-MM-DD.\n";
  //     return false;
  //   }

  //   if (!isValidEndDate(end, start)) {
  //     std::cout << "Error: Invalid end date. Please provide a valid date in the format YYYY-MM-DD and ensure it's not in the future or before the start date.\n";
  //     return false;
  //   }

  //   getStockData(symbol, start, end);
  // }

  return true;
}

int main() {
  if (!getInput()) {
    return 0;
  }
  
  return 0;
}
