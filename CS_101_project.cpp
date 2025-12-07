#include<iostream>    
#include <string>
#include <ctime>
#include <cstdlib>                        //Header Files
#include <iomanip>
#include<fstream>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"               // Color codes for printing colored text in the console (ANSI escape sequences)                        
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

double calculate_total(double price[], int quantity[], int n) {
    double total = 0;
    for (int i = 0; i < n; i++) {
        total += price[i] * quantity[i];
    }
    return total;
}


bool login() {

    cout << BLUE << "================================" << RESET << endl;    //also giving colouring to each line
    cout << GREEN << "           LOGIN SYSTEM         " << RESET << endl;   //prints login system on screen
    cout << BLUE << "================================" << RESET << endl;

    string user_name;          //string variable to store username
    string password;           //string variable to store password

    int attempts = 3;          //giving three attempts for username and three attempts for password , if attempts becomes zero the software will be closed
    while (attempts > 0) {     //loop runs until attempts will be greater than zero
        cout << CYAN << "Enter Username : " << RESET;
        cin >> user_name;      //asking user to enter user name

        if (user_name == "admin" || user_name == "ADMIN") {
            break;              // if username will be correct it will exit the loop immediately
        } else {
            attempts--;         //if username will be incorrect it will decrease the number of attempts one by one
            cout << RED << "Wrong Username! Attempts left: " << attempts << RESET << endl;
        }
    }

    if (attempts == 0) {        //if there are 0 attempts remaining the program will end automatically
        cout << RED << "Too many wrong attempts. Program closed." << RESET << endl;
        return false;
    }

    attempts = 3;              //giving three attempts for password
    while (attempts > 0) {     //loop runs until attempts will be greater than zero
        cout << CYAN << "Enter Password : " << RESET;
        cin >> password;        //asking user to enter password

        if (password == "1234") {
            break;              // if password will be correct it will exit the loop immediately
        } else {
            attempts--;         //if username will be incorrect it will decrease the number of attempts one by one
            cout << RED << "Wrong Password! Attempts left: " << attempts << RESET << endl;
        }
    }

    if (attempts == 0) {        //if there are 0 attempts remaining the program will end automatically
        cout << RED << "Too many wrong attempts. Program closed." << RESET << endl;
        return false;
    }

    cout << GREEN << "\n======= LOGIN SUCCESSFUL =======" << RESET << endl << endl;   //if both username and password will be correct it will pring login successful on the screen

    return true;
}

    void save_and_print_summary(string customer_name, int bill_number, char *dt, string products[], double price[], int quantity[],  int total_items, double total_bill, double discount, double tax, double sub_total) 
{
    // Opening file to save bill
    ofstream file("bill_summary.txt" , ios::app);

    // Print & Save Header
    cout<<"\n\n======= BILL SUMMARY =======\n";
    file<<"======= BILL SUMMARY =======\n";

    cout<<"Customer Name : " << customer_name << endl;
    file<<"Customer Name : " << customer_name << endl;

    cout<<"Bill Number   : " << bill_number << endl;
    file<<"Bill Number   : " << bill_number << endl;

    cout<<"Date & Time   : " << dt;
    file<<"Date & Time   : " << dt;

    cout<<"---------------------------------------\n";
    file<<"---------------------------------------\n";

    cout<<left << setw(15) << "Product" 
         << setw(10) << "Price" 
         << setw(10) << "Qty" 
         << "Total\n";

    file << left << setw(15) << "Product" 
         << setw(10) << "Price" 
         << setw(10) << "Qty" 
         << "Total\n";

    cout<<"---------------------------------------\n";
    file<<"---------------------------------------\n";

    // Loop to print items
    for (int i = 0; i < total_items; i++) {
        double product_total = price[i] * quantity[i];

        cout<< left << setw(15) << products[i]
             << setw(10) << price[i]
             << setw(10) << quantity[i]
             << product_total << endl;

        file<< left << setw(15) << products[i]
             << setw(10) << price[i]
             << setw(10) << quantity[i]
             << product_total << endl;
    }

    cout<<"\nTotal Bill : " << total_bill << endl;
    file<<"\nTotal Bill : " << total_bill << endl;

    cout<<"Discount   : " << discount << endl;
    file<<"Discount   : " << discount << endl;

    cout<<"Tax        : " << tax << endl;
    file<<"Tax        : " << tax << endl;

    cout<<"Sub Total  : " << sub_total << endl;
    file<<"Sub Total  : " << sub_total << endl;

    cout<<"\nBill saved to 'bill_summary.txt'\n";
    file<<"\n======= END OF BILL =======\n";
    file<<endl;
    file<<"--------------------------------------" << endl;
    file<<endl;

    file.close();
}


int main(){


    if (!login()) {   // call the function
        return 0;     // stop program if login failed
    }

    cin.ignore();              //ignoring previous input so there is no mixing with coming input
    string customer_name;
    cout << CYAN << "Enter Customer Name : " << RESET;   //input customer name
    getline(cin, customer_name);           //using getline to also read name if there are two words in a name
    cout << endl;

    int total_number_of_products;
    cout << CYAN << "Enter total number of products : " << RESET;
    do {
        cin >> total_number_of_products;  //input total number of products
        if (total_number_of_products < 0) {
            cout << RED << "Invalid input! please again enter total number of products : " << RESET;
        }
    } while (total_number_of_products < 0);   //asking user again to enter total products if entered less than 1 products previously
    cout << endl;

    string products[total_number_of_products];    //storing products name in array as entered by cashier
    double price[total_number_of_products];        //storing price of each product in an array entered by cashier
    int quantity[total_number_of_products];       //storing quantity of each product in an array entered by cashier

    for (int i = 0; i < total_number_of_products; i++) {
        cout << MAGENTA << "Enter name of product " << i + 1 << " : " << RESET;
        cin.ignore();                      //ignoring previous input so there is no mixing with coming input
        getline(cin, products[i]);         //input names of product

        cout << YELLOW << "Enter price of product " << i + 1 << " : " << RESET;
        do {
            cin >> price[i];             //input price of product
            if (price[i] < 0) {
                cout << RED << "Invalid input! please again enter price of product : " << RESET;
            }
        } while (price[i] < 0);     //asking again for price if user enters less than 0 price

        cout << YELLOW << "Enter quantity of product " << i + 1 << " : " << RESET;
        do {
            cin >> quantity[i];    //input quantity of each product
            if (quantity[i] < 0) {
                cout << RED << "Invalid input! please again enter quantity of product :  " << RESET;
            }
        } while (quantity[i] < 0);        //asking again for quantity if user enters less than 0 quantity

        cout << endl;
    }

    srand(time(0));
    int bill_number = rand() % 10000;         //random bill generator in the range of 10000

    time_t now = time(0); 
    char *dt = ctime(&now);                  //printing current date and time


    cout << BLUE << "==================================================" << RESET << endl;
    cout << GREEN << "                   BILL RECEIPT                 " << RESET << endl;
    cout << BLUE << "==================================================" << RESET << endl;

    cout << CYAN << "\nCustomer name : " << RESET << customer_name << endl;
    cout << CYAN << "Bill number   : " << RESET << bill_number << endl;
    cout << CYAN << "Date and Time : " << RESET << dt;
    cout << BLUE << "--------------------------------------------------" << RESET << endl;

    cout << left
         << YELLOW << setw(15) << "Products"
         << setw(10) << "Price"
         << setw(12) << "Quantity"
         << setw(10) << "Total(Rs.)" << RESET << endl;

    cout << BLUE << "--------------------------------------------------" << RESET << endl;

    for (int i = 0; i < total_number_of_products; i++) {
        cout << left
             << WHITE << setw(16) << products[i]
             << setw(12) << price[i]
             << setw(10) << quantity[i]
             << GREEN << price[i] * quantity[i] << " Rs." << RESET << endl;

        cout << BLUE << "--------------------------------------------------" << RESET << endl;
    }

    double total_bill = calculate_total(price, quantity, total_number_of_products);
    cout << CYAN << "\n              Total Bill : " << GREEN << total_bill << " Rs." << RESET << endl;

    double discount = 0;
    if (total_bill > 1000) {
        discount = 0.10 * total_bill;
        cout << CYAN << "                Discount : " << GREEN << discount << " Rs." << RESET << endl;
    }

    double tax = (0.05 * total_bill);
    cout << CYAN << "                     Tax : " << GREEN << tax << " Rs." << RESET << endl << endl;

    cout << BLUE << "--------------------------------------------------" << RESET << endl << endl;

    float sub_total = ((total_bill - discount) + tax);
    cout << CYAN << "               Sub Total : " << GREEN << sub_total << " Rs." << RESET << endl << endl;

    cout << BLUE << "--------------------------------------------------" << RESET << endl << endl;

    int choice;
    double recieved_cash, remaining_amount;

    cout << MAGENTA << "Payment Methods : " << RESET << endl << endl;
    cout << "     " << CYAN << "1-Jazzcash" << RESET << endl;
    cout << "     " << CYAN << "2-Bank Credit Card" << RESET << endl;
    cout << "     " << CYAN << "3-Easypaisa" << RESET << endl;
    cout << "     " << CYAN << "4-Cash" << RESET << endl << endl;

    cout << YELLOW << "Select Payment Method : " << RESET;

    do {
        cin >> choice;
        switch (choice) {
        case 1:
            cout << GREEN << "Selected Method : JazzCash. Processing payment..." << endl;
            cout << "Payment Successful" << RESET << endl;
            break;

        case 2:
            cout << GREEN << "Selected Method : Credit Card. Redirecting..." << endl;
            cout << "Payment Successful" << RESET << endl;
            break;

        case 3:
            cout << GREEN << "Selected Method : EasyPaisa. Processing..." << endl;
            cout << "Payment Successful" << RESET << endl;
            break;

        case 4:
            cout << YELLOW << "Selected Method : Cash. Please pay at counter.\n" << RESET << endl;
            cout << CYAN << "Total Cash To Pay : " << GREEN << sub_total << " Rs." << RESET << endl;

            remaining_amount = sub_total;

            while (remaining_amount > 0) {
                cout << CYAN << "Enter Cash Received : " << RESET;
                cin >> recieved_cash;

                if (recieved_cash <= 0) {
                    cout << RED << "Invalid amount! Enter again." << RESET << endl;
                    continue;
                }

                remaining_amount -= recieved_cash;

                if (remaining_amount > 0) {
                    cout << YELLOW << "You still need to pay: " << remaining_amount << " Rs.\n" << RESET;
                }
            }

            if (remaining_amount < 0) {
                cout << GREEN << "Change : " << -remaining_amount << " Rs." << RESET << endl;
            }

            cout << GREEN << "Payment Successful!" << RESET << endl;
            break;

        default:
            cout << RED << "Invalid Choice! Please select a valid option (1 to 4): " << RESET;
        }
    } while (choice > 4 || choice < 1);

    save_and_print_summary(customer_name, bill_number, dt, products, price, quantity,  total_number_of_products,  total_bill, discount, tax, sub_total);
    

    cout << GREEN << "\n\nThank you for shopping " << customer_name << " !" << RESET << endl;


    return 0;
}