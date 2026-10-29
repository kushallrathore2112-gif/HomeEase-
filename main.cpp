#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool userExists(const string& username)
{
    ifstream file("users.txt");
    string savedUser, savedPass;

    while (file >> savedUser >> savedPass)
    {
        if (savedUser == username)
        {
            return true;
        }
    }
    return false;
}

void registerUser()
{
    string username, password;

    cout << "\n--- REGISTER ---" << endl;
    cout << "Choose a username: ";
    cin >> username;

    if (userExists(username))
    {
        cout << "That username is already taken!" << endl;
        return;
    }

    cout << "Choose a password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << username << " " << password << endl;
        file.close();
        cout << "Registration successful! You can now log in." << endl;
    }
    else
    {
        cout << "Unable to save user!" << endl;
    }
}

bool login()
{
    int choice;
    string username, password;

    while (true)
    {
        cout << "\n===== HOME EASE =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            bool valid = false;
            ifstream file("users.txt");
            string savedUser, savedPass;

            while (file >> savedUser >> savedPass)
            {
                if (savedUser == username && savedPass == password)
                {
                    valid = true;
                    break;
                }
            }
            file.close();

            if (valid)
            {
                cout << "Login successful! Welcome to HomeEase, " << username << "!" << endl;
                return true;
            }
            else
            {
                cout << "Invalid username or password!" << endl;
            }
        }
        else if (choice == 2)
        {
            registerUser();
        }
        else if (choice == 0)
        {
            cout << "Goodbye!" << endl;
            return false;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}

void menu()
{
    int option;
    int service, price;
    string customerName, serviceName, savedName, savedService;
    bool found;

    do
    {
        cout << "\n===================================" << endl;
        cout << "             HomeEase" << endl;
        cout << "===================================" << endl;
        cout << "1. View Services" << endl;
        cout << "2. Book Services" << endl;
        cout << "3. View Bookings" << endl;
        cout << "4. Cancel Bookings" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1)
        {
            cout << "\n--- AVAILABLE SERVICES ---" << endl;
            cout << "1. Home Cleaning - Rs. 499" << endl;
            cout << "2. Plumbing      - Rs. 299" << endl;
            cout << "3. Electrician   - Rs. 399" << endl;
            cout << "4. AC Repair     - Rs. 699" << endl;
        }
        else if (option == 2)
        {
            cout << "\n--- BOOK A SERVICE ---" << endl;
            cout << "1. Home Cleaning - Rs. 499" << endl;
            cout << "2. Plumbing      - Rs. 299" << endl;
            cout << "3. Electrician   - Rs. 399" << endl;
            cout << "4. AC Repair     - Rs. 699" << endl;
            cout << "Select service number: ";
            cin >> service;

            if (service == 1)
            {
                serviceName = "Home_Cleaning";
                price = 499;
            }
            else if (service == 2)
            {
                serviceName = "Plumbing";
                price = 299;
            }
            else if (service == 3)
            {
                serviceName = "Electrician";
                price = 399;
            }
            else if (service == 4)
            {
                serviceName = "AC_Repair";
                price = 699;
            }
            else
            {
                cout << "Invalid service selection!" << endl;
                continue;
            }

            cout << "Enter your name: ";
            cin >> customerName;

            ofstream file("bookings.txt", ios::app);

            if (file.is_open())
            {
                file << customerName << " "
                     << serviceName << " "
                     << price << endl;
                file.close();

                cout << "\nBooking successful!" << endl;
                cout << "Service: " << serviceName << endl;
                cout << "Total bill: Rs. " << price << endl;
            }
            else
            {
                cout << "Unable to save booking!" << endl;
            }
        }
        else if (option == 3)
        {
            cout << "\n--- YOUR BOOKINGS ---" << endl;

            ifstream file("bookings.txt");
            found = false;

            while (file >> savedName >> savedService >> price)
            {
                cout << "Customer: " << savedName
                     << " | Service: " << savedService
                     << " | Price: Rs. " << price << endl;
                found = true;
            }

            file.close();

            if (!found)
            {
                cout << "No bookings found." << endl;
            }
        }
        else if (option == 4)
        {
            cout << "\nBookings are stored in bookings.txt." << endl;
            cout << "To support cancellation, we will add booking IDs next." << endl;
        }
        else if (option == 0)
        {
            cout << "Logged out successfully!" << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (option != 0);
}

int main()
{
    if (login())
    {
        menu();
    }
    return 0;
}