#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream> 
#include <cstdio>  

using namespace std;

// ===== COLOR CODES =====
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

const string USER_FILE = "users.txt";

// Function to calculate total price
double calculate_total(double price[], int quantity[], int n) {
    double total = 0;
    for (int i = 0; i < n; i++) {
        total += price[i] * quantity[i];
    }
    return total;
}

// Function to save bill to file and print summary
void save_and_print_summary(string customer_name, int bill_number, char *dt, string products[], double price[], int quantity[],  int total_items, double total_bill, double discount, double tax, double sub_total) 
{
    ofstream file("bill_summary.txt" , ios::app); 

    // Print to Console
    cout << BLUE << "==================================================" << RESET << endl;
    cout << GREEN << "                   BILL RECEIPT                 " << RESET << endl;
    cout << BLUE << "==================================================" << RESET << endl;
    cout << CYAN << "\nCustomer name : " << RESET << customer_name << endl;
    cout << CYAN << "Bill number   : " << RESET << bill_number << endl;
    cout << CYAN << "Date and Time : " << RESET << dt;
    cout << BLUE << "--------------------------------------------------" << RESET << endl;

    cout << left << YELLOW << setw(15) << "Products" << setw(10) << "Price" << setw(12) << "Quantity" << setw(10) << "Total(Rs.)" << RESET << endl;
    cout << BLUE << "--------------------------------------------------" << RESET << endl;

    // Save Header to File
    file << "======= BILL SUMMARY =======\n";
    file << "Customer Name : " << customer_name << endl;
    file << "Bill Number   : " << bill_number << endl;
    file << "Date & Time   : " << dt;
    file << "---------------------------------------\n";
    file << left << setw(15) << "Product" << setw(10) << "Price" << setw(10) << "Qty" << "Total\n";
    file << "---------------------------------------\n";

    // Loop to print items
    for (int i = 0; i < total_items; i++) {
        double product_total = price[i] * quantity[i];

        // Console
        cout << left << WHITE << setw(16) << products[i] << setw(12) << price[i] << setw(10) << quantity[i] << GREEN << product_total << " Rs." << RESET << endl;
        cout << BLUE << "--------------------------------------------------" << RESET << endl;

        // File
        file << left << setw(15) << products[i] << setw(10) << price[i] << setw(10) << quantity[i] << product_total << endl;
    }

    // Console Footer
    cout << CYAN << "\n              Total Bill : " << GREEN << total_bill << " Rs." << RESET << endl;
    cout << CYAN << "                Discount : " << GREEN << discount << " Rs." << RESET << endl;
    cout << CYAN << "                     Tax : " << GREEN << tax << " Rs." << RESET << endl;
    cout << BLUE << "--------------------------------------------------" << RESET << endl;
    cout << CYAN << "               Sub Total : " << GREEN << sub_total << " Rs." << RESET << endl;
    cout << BLUE << "--------------------------------------------------" << RESET << endl;

    // File Footer
    file << "\nTotal Bill : " << total_bill << endl;
    file << "Discount   : " << discount << endl;
    file << "Tax        : " << tax << endl;
    file << "Sub Total  : " << sub_total << endl;
    file << "\n======= END OF BILL =======\n\n";

    file.close();
    cout << GREEN << "\nReceipt saved to 'bill_summary.txt'" << RESET << endl;
}

// ===== HELPER: CHECK IF USERNAME EXISTS =====
bool is_username_taken(string username) {
    ifstream file(USER_FILE.c_str());
    string f_user, f_pass;
    if (!file.is_open()) return false; 
    while (file >> f_user >> f_pass) {
        if (f_user == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// ===== 1. REGISTER USER (Called from Dashboard) =====
void register_user() {
    cout << BLUE << "--------------------------------" << RESET << endl;
    cout << MAGENTA << "       REGISTER NEW USER        " << RESET << endl;
    cout << BLUE << "--------------------------------" << RESET << endl;

    string username, password;
    cout << CYAN << "Enter New Username : " << RESET;
    cin >> username;

    if (is_username_taken(username)) {
        cout << RED << "Error: Username already exists!" << RESET << endl;
        return;
    }

    cout << CYAN << "Enter New Password : " << RESET;
    cin >> password;

    ofstream file(USER_FILE.c_str(), ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
        cout << GREEN << "User added successfully." << RESET << endl;
    } else {
        cout << RED << "Error: Could not save data." << RESET << endl;
    }
}

// ===== 2. DELETE USER (Called from Dashboard) =====
void delete_user() {
    cout << BLUE << "--------------------------------" << RESET << endl;
    cout << RED << "          DELETE USER           " << RESET << endl;
    cout << BLUE << "--------------------------------" << RESET << endl;

    string username, password, target_user;
    cout << CYAN << "Enter Username to DELETE: " << RESET;
    cin >> target_user;

    if (!is_username_taken(target_user)) {
        cout << RED << "Error: User does not exist." << RESET << endl;
        return;
    }

    ifstream inFile(USER_FILE.c_str());
    ofstream outFile("temp.txt");

    bool found = false;
    while (inFile >> username >> password) {
        if (username != target_user) {
            outFile << username << " " << password << endl;
        } else {
            found = true; 
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove(USER_FILE.c_str());
        rename("temp.txt", USER_FILE.c_str());
        cout << GREEN << "User removed successfully." << RESET << endl;
    } else {
        remove("temp.txt");
    }
}

// ===== 3. BILLING SYSTEM (Moved from Main) =====
void start_billing_system() {
    cin.ignore(); // clear buffer
    string customer_name;
    cout << BLUE << "\n===================================" << RESET << endl;
    cout << YELLOW << "      STARTING BILLING MODE        " << RESET << endl;
    cout << BLUE << "===================================" << RESET << endl;
    
    cout << CYAN << "Enter Customer Name : " << RESET;
    getline(cin, customer_name);
    
    int total_number_of_products;
    cout << CYAN << "Enter total number of products : " << RESET;
    do {
        cin >> total_number_of_products;
        if (total_number_of_products < 0) cout << RED << "Invalid input! " << RESET;
    } while (total_number_of_products < 0);

    string products[total_number_of_products];
    double price[total_number_of_products];
    int quantity[total_number_of_products];

    for (int i = 0; i < total_number_of_products; i++) {
        cout << MAGENTA << "Enter name of product " << i + 1 << " : " << RESET;
        cin.ignore();
        getline(cin, products[i]);

        cout << YELLOW << "Enter price: " << RESET;
        do { cin >> price[i]; } while (price[i] < 0);

        cout << YELLOW << "Enter quantity: " << RESET;
        do { cin >> quantity[i]; } while (quantity[i] < 0);
        cout << endl;
    }

    srand(time(0));
    int bill_number = rand() % 10000;
    time_t now = time(0); 
    char *dt = ctime(&now);

    cout << GREEN << "\nCalculating Bill...\n" << RESET;
    double total_bill = calculate_total(price, quantity, total_number_of_products);
    double discount = (total_bill > 1000) ? 0.10 * total_bill : 0;
    double tax = 0.05 * total_bill;
    double sub_total = (total_bill - discount) + tax;

    // Print Receipt
    save_and_print_summary(customer_name, bill_number, dt, products, price, quantity, total_number_of_products, total_bill, discount, tax, sub_total);

    // --- Payment ---
    int choice;
    double recieved_cash, remaining_amount;
    cout << MAGENTA << "\nPayment Methods: " << RESET << endl; 
    cout << CYAN << "1-Jazzcash\n2-Card\n3-Easypaisa\n4-Cash" << RESET << endl;
    cout << YELLOW << "Select Method: " << RESET;
    
    do {
        cin >> choice;
        switch(choice) {
            case 1: cout << GREEN << "Paid via JazzCash." << RESET << endl; break;
            case 2: cout << GREEN << "Paid via Card." << RESET << endl; break;
            case 3: cout << GREEN << "Paid via EasyPaisa." << RESET << endl; break;
            case 4:
                 cout << YELLOW << "Selected Cash. Total to Pay: " << sub_total << RESET << endl;
                 remaining_amount = sub_total;
                 while (remaining_amount > 0) {
                    cout << CYAN << "Enter Cash: " << RESET;
                    cin >> recieved_cash;
                    remaining_amount -= recieved_cash;
                    if (remaining_amount > 0) cout << YELLOW << "Remaining: " << remaining_amount << endl;
                 }
                 if (remaining_amount < 0) cout << GREEN << "Change: " << -remaining_amount << " Rs." << RESET << endl;
                 break;
            default: cout << RED << "Invalid!" << RESET << endl;
        }
    } while (choice < 1 || choice > 4);

    cout << GREEN << "\nTransaction Complete! returning to Dashboard..." << RESET << endl;
}

// ===== 4. ADMIN DASHBOARD (Post-Login Menu) =====
void admin_dashboard() {
    int choice;
    while (true) {
        cout << endl << BLUE << "==========================================" << RESET << endl;
        cout << GREEN << "           ADMIN DASHBOARD                " << RESET << endl;
        cout << BLUE << "==========================================" << RESET << endl;
        cout << "1. Start Billing System" << endl;
        cout << "2. Add New User" << endl;
        cout << "3. Remove User" << endl;
        cout << "4. Logout" << endl;
        cout << YELLOW << "Select Option: " << RESET;
        cin >> choice;

        switch(choice) {
            case 1:
                start_billing_system();
                break;
            case 2:
                register_user();
                break;
            case 3:
                delete_user();
                break;
            case 4:
                cout << GREEN << "Logging out..." << RESET << endl;
                return; // Returns to main, which exits
            default:
                cout << RED << "Invalid option!" << RESET << endl;
        }
    }
}

// ===== 5. LOGIN FUNCTION =====
bool perform_login() {
    string input_user, input_pass, f_user, f_pass;
    int attempts = 3;

    cout << BLUE << "================================" << RESET << endl;
    cout << GREEN << "           LOGIN SYSTEM         " << RESET << endl;
    cout << BLUE << "================================" << RESET << endl;

    // Check if file exists/is empty. If empty, allow creating admin.
    ifstream checkFile(USER_FILE.c_str());
    if (!checkFile.good()) {
        cout << RED << "No users found in database." << RESET << endl;
        cout << YELLOW << "Entering Setup Mode to create first Admin." << RESET << endl;
        register_user(); // Force register if no file exists
    }
    checkFile.close();

    while (attempts > 0) {
        cout << CYAN << "Enter Username : " << RESET;
        cin >> input_user;
        cout << CYAN << "Enter Password : " << RESET;
        cin >> input_pass;

        ifstream file(USER_FILE.c_str());
        bool login_success = false;

        if (file.is_open()) {
            while (file >> f_user >> f_pass) {
                if (f_user == input_user && f_pass == input_pass) {
                    login_success = true;
                    break;
                }
            }
            file.close();
        }

        if (login_success) {
            cout << GREEN << "\n======= LOGIN SUCCESSFUL =======" << RESET << endl;
            return true;
        } else {
            attempts--;
            cout << RED << "Invalid Credentials! Attempts left: " << attempts << RESET << endl;
        }
    }
    return false;
}

int main() {
    // 1. Attempt to Login
    if (perform_login()) {
        // 2. If Login Success, Go to Admin Dashboard
        admin_dashboard();
    } else {
        cout << RED << "Access Denied. Terminating." << RESET << endl;
    }

    return 0;
}