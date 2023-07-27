#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

struct MenuItem {
    string name;
    double price;
};

struct Employee {
    string name;
    string employeeId;
    string email;
};

class Restaurant {
private:
    vector<MenuItem> menu;
    vector<Employee> employees;
    double totalSales;
    vector<double> dailySales;

public:
    Restaurant() {
        totalSales = 0.0;
        dailySales.resize(3, 0.0); // Initialize daily sales for three menu items (Burger, Pizza, Salad)
    }

    void addMenuItem(const string& name, double price) {
        MenuItem item;
        item.name = name;
        item.price = price;
        menu.push_back(item);
    }

    void addEmployee(const string& name, const string& employeeId, const string& email) {
        Employee emp;
        emp.name = name;
        emp.employeeId = employeeId;
        emp.email = email;
        employees.push_back(emp);
    }

    void displayMenu() {
        cout << "Menu:" << endl;
        for (size_t i = 0; i < menu.size(); i++) {
            const MenuItem& item = menu[i];
            cout << item.name << " - $" << fixed << setprecision(2) << item.price << endl;
        }
    }

    bool isMenuItemAvailable(const string& itemName) {
        for (size_t i = 0; i < menu.size(); i++) {
            if (menu[i].name == itemName) {
                return true;
            }
        }
        return false;
    }

    double getItemPrice(const string& itemName) {
        for (size_t i = 0; i < menu.size(); i++) {
            if (menu[i].name == itemName) {
                return menu[i].price;
            }
        }
        return 0.0; // Return 0.0 if item not found
    }

    void processOrder() {
        string itemName;
        cout << "Enter the food item you want to order: ";
        getline(cin, itemName);

        if (!isMenuItemAvailable(itemName)) {
            cout << "Item not found in the menu." << endl;
            return;
        }

        double itemPrice = getItemPrice(itemName);
        cout << "Item " << itemName << " is available. Price: $" << fixed << setprecision(2) << itemPrice << endl;

        string customerName, address, email;
        cout << "Enter customer details:" << endl;
        cout << "Customer Name: ";
        getline(cin, customerName);
        cout << "Address: ";
        getline(cin, address);
        cout << "Email: ";
        getline(cin, email);

        // Prompt user to select the employee who served the customer
        cout << "Select the Employee who served the customer:" << endl;
        for (size_t i = 0; i < employees.size(); i++) {
            cout << i + 1 << ") " << employees[i].name << endl;
        }
        int selectedEmployee;
        cin >> selectedEmployee;

        if (selectedEmployee < 1 || selectedEmployee > static_cast<int>(employees.size())) {
            cout << "Invalid selection. Order canceled." << endl;
            return;
        }

        cin.ignore(); // Ignore the newline character left in the input buffer

        cout << "Food ordered: " << itemName << endl;
        cout << "Payment method (cash or mpesa): ";
        string paymentMethod;
        getline(cin, paymentMethod);

        // Update the stock and daily sales based on the item sold
        if (itemName == "Burger") {
            dailySales[0] += itemPrice;
        } else if (itemName == "Pizza") {
            dailySales[1] += itemPrice;
        } else if (itemName == "Salad") {
            dailySales[2] += itemPrice;
        }

        // Update the total sales
        totalSales += itemPrice;

        cout << "Order placed successfully." << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Served by: " << employees[selectedEmployee - 1].name << endl;
        cout << "Payment method: " << paymentMethod << endl;
        generateReceipt(customerName, itemName, itemPrice);
    }

    void generateReceipt(const string& customerName, const string& itemName, double itemPrice) {
        cout << endl;
        cout << "Receipt:" << endl;
        cout << "---------------------------------" << endl;
        cout << "Restaurant: FUKO FUKO" << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Item: " << itemName << endl;
        cout << "Price: $" << fixed << setprecision(2) << itemPrice << endl;
        cout << "---------------------------------" << endl;
        cout << "Food First'" << endl;
        cout << endl;
    }

    void displayTotalSales() {
        cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    }

    void displayDailySales() {
        cout << "Daily Sales:" << endl;
        cout << "Burger - $" << fixed << setprecision(2) << dailySales[0] << endl;
        cout << "Pizza - $" << fixed << setprecision(2) << dailySales[1] << endl;
        cout << "Salad - $" << fixed << setprecision(2) << dailySales[2] << endl;
    }
};

int main() {
    Restaurant restaurant;

    // Adding menu items with updated quantities
    restaurant.addMenuItem("Burger", 9.99);
    restaurant.addMenuItem("Pizza", 12.99);
    restaurant.addMenuItem("Salad", 7.99);

    // Adding employees
    restaurant.addEmployee("John Mkutano", "EM001", "johnmkutano@gmail.com");

    // Displaying the menu
    restaurant.displayMenu();

    // Processing orders
    restaurant.processOrder();

    // Displaying the total sales and daily sales
    restaurant.displayTotalSales();
    restaurant.displayDailySales();

    return 0;
}
