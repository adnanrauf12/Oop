#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

// Base class for MenuItem and OrderItem
class Item {
public:
    virtual void display() const = 0;
};

// Derived class for MenuItem
class MenuItem : public Item {
public:
    int itemNumber;
    string itemName;
    float itemPrice;

    MenuItem(int number, const string& name, float price) : itemNumber(number), itemName(name), itemPrice(price) {}

    void display() const override {
        cout<<itemNumber<<"\t "<<itemName<<"\t"<<itemPrice<<endl;
    }
};

// Derived class for OrderItem
class OrderItem : public Item {
public:
    MenuItem menuItem;
    int quantity;

    OrderItem(MenuItem item, int qty) : menuItem(item), quantity(qty) {}

    float getTotal() const {
        return menuItem.itemPrice * quantity;
    }

    void display() const override {
        cout<<menuItem.itemNumber<<" "<<menuItem.itemName<<" "<<menuItem.itemPrice<<" "<<quantity<<" "<<getTotal()<<endl;
    }
};

// Restaurant class to manage the menu and orders
class Restaurant {
private:
    vector<MenuItem> menu;
    vector<OrderItem> order;
    float taxRate;
    float discount;

public:
    Restaurant(float tax, float disc) : taxRate(tax), discount(disc) {
        loadMenu();
    }

    void loadMenu() {
        menu.emplace_back(  1,    "Burger",     5.99);
        menu.emplace_back(  2,    "Fries",      2.99);
        menu.emplace_back(  3,    "Drink",      1.99);
        menu.emplace_back(  4,    "Salad",      3.99);
        menu.emplace_back(  5,    "Soup",       2.99);
        menu.emplace_back(  6,    "Naan",     14.99);
        menu.emplace_back(  7,    "Pizza",      8.99);
        menu.emplace_back(  8,    "Pasta",      7.99);
        menu.emplace_back(  9,    "Salad",      4.99);
        menu.emplace_back(  10,    "Soda",      1.99);
    
    }

    void displayMenu() const {
        cout<<"   No      Item    Price"<<endl;
        cout<<"------------------------------------------"<<endl;
        for (const auto& item : menu) {
            item.display();
        }
    }

    void takeOrder() {
        int itemNumber, quantity;
        char choice;

        do {
            displayMenu();
            cout<<"Enter the item number you wish to order: ";
            cin >> itemNumber;
            cout<<"Enter the quantity: ";
            cin >> quantity;

            for (const auto& item : menu) {
                if (item.itemNumber == itemNumber) {
                    order.emplace_back(item, quantity);
                    break;
                }
            }

            cout<<"Do you want to order another item? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');

        printBill();
        processPayment();
    }

    void printBill() const {
        float subTotal = 0.0;

        cout<<"No Item Price Qty Total"<<endl;
        cout<<"------------------------------------------------------------"<<endl;
        for (const auto& ord : order) {
            ord.display();
            subTotal += ord.getTotal();
        }

        float taxAmount = subTotal * taxRate;
        float discountAmount = subTotal * discount;
        float total = subTotal + taxAmount - discountAmount;

        cout<<"\nSubtotal: $"<<subTotal<<endl;
        cout<<"Tax: $"<<taxAmount<<endl;
        cout<<"Discount: $"<<discountAmount<<endl;
        cout<<"Total: $"<<total<<endl;
    }

    void processPayment() {
        float total = 0.0;
        for (const auto& ord : order) {
            total += ord.getTotal();
        }
        total = total + (total * taxRate) - (total * discount);

        float amountPaid;
        cout<<"---------------------------------"<<endl;
        cout<<"              Bill             "<<endl;
        cout<<"---------------------------------"<<endl; 
        cout<<"Total Amount Due: $"<<total<<endl; 
        cout<<"Enter amount paid: ";
        cin >> amountPaid;



        if (amountPaid >= total) {
        cout<<"\t\t--------------------------------- \t\t"<<endl;
        cout<<"\t\t              Receipt             \t\t"<<endl;
        cout<<"\t\t--------------------------------- \t\t"<<endl;
                                    cout<<endl; 
              
        cout<<"\t\tPayment successful! Change: $\t\t"<<amountPaid - total<<endl;
        cout<<"\t\t---------------------------------\t\t"<<endl;
        cout<<"\t\tThank you for shopping with us!\t\t"<<endl;
        cout<<"\t\t---------------------------------\t\t"<<endl;

            cout<<endl;
            
            cout<<"\t Thnaks for visiting\n";
        } else {
            cout<<"Insufficient payment. Please pay the full amount."<<endl;
        }
    }

    void addMenuItem() {
        int number;
        string name;
        float price;

        cout<<"Enter item number: ";
        cin >> number;
        cin.ignore();
        cout<<"Enter item name: ";
        getline(cin, name);
        cout<<"Enter item price: ";
        cin >> price;

        menu.emplace_back(number, name, price);
        cout<<"Item added successfully."<<endl;
    }

    void customizeMenuItem() {
        int number;
        cout<<"Enter the item number to customize: ";
        cin >> number;

        for (auto& item : menu) {
            if (item.itemNumber == number) {
                string name;
                float price;

                cout<<"Enter new item name: ";
                cin.ignore();
                getline(cin, name);
                cout<<"Enter new item price: ";
                cin >> price;

                item.itemName = name;
                item.itemPrice = price;
                cout<<"Item updated successfully."<<endl;
                return;
            }
        }

        cout<<"Item not found."<<endl;
    }
};

// Base class for Users
class User {
public:
    virtual void showMenu(Restaurant& restaurant) = 0;
};

// Derived class for Customer
class Customer : public User {
public:
    void showMenu(Restaurant& restaurant) override {
        char choice;

        do {
            cout<<"1. Display Menu"<<endl;
            cout<<"2. Place Order"<<endl;
            cout<<"3. Exit"<<endl;
            cout<<"Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case '1':
                    restaurant.displayMenu();
                    break;
                case '2':
                    restaurant.takeOrder();
                    break;
                case '3':
                    return;
                default:
                    cout<<"Invalid choice! Please try again."<<endl;
            }

            cout<<"\nPress Enter to continue...";
            cin.ignore();
            cin.get();

        } while (choice != '3');
    }
};

// Derived class for Admin
class Admin : public User {
public:
    void showMenu(Restaurant& restaurant) override {
        char choice;

        do {
            cout<<"1. Display Menu"<<endl;
            cout<<"2. Add Menu Item"<<endl;
            cout<<"3. Customize Menu Item"<<endl;
            cout<<"4. Exit"<<endl;
            cout<<"Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case '1':
                    restaurant.displayMenu();
                    break;
                case '2':
                    restaurant.addMenuItem();
                    break;
                case '3':
                    restaurant.customizeMenuItem();
                    break;
                case '4':
                    return;
                default:
                    cout<<"Invalid choice! Please try again."<<endl;
            }

            cout<<"\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        } while (choice != '4');
    }
};

// Main function
int main() {
    Restaurant restaurant(0.08, 0.10);  // Tax rate 8%, discount 10%
    User* user;
     cout<<"\t\t*************************************************************\t\t"<<endl;
     cout<<"\t\t***                WELCOME TO OUR RESTAURENT              ***\t\t"<<endl;
     cout<<"\t\t*************************************************************\t\t"<<endl;
     cout<<endl;
    cout<<"1. Customer"<<endl;
    cout<<"2. Admin"<<endl;
    cout<<"Enter user type: ";
    char userType;
    cin >> userType;

    if (userType == '1') {
        user = new Customer();
    } else if (userType == '2') {
        user = new Admin();
    } else {
        cout<<"Invalid user type!"<<endl;
        return 1;
    }

    user->showMenu(restaurant);

    delete user;
}