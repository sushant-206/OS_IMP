#include <iostream>  // For input and output operations
#include <vector>    // For using the vector container
#include <string>    // For using the string class
using namespace std;

// Define a structure to hold an address record
struct Record {
    string name;  // Field for storing the name
    string phone; // Field for storing the phone number
    string email; // Field for storing the email address
};

// Function prototypes to declare the functions before defining them
void createAddressBook(vector<Record> &addressBook); // Clears the address book
void viewAddressBook(const vector<Record> &addressBook); // Displays all records
void insertRecord(vector<Record> &addressBook); // Adds a new record
void deleteRecord(vector<Record> &addressBook); // Deletes a specific record
void modifyRecord(vector<Record> &addressBook); // Modifies an existing record

int main() {
    vector<Record> addressBook; // The address book to store records
    int choice; // Variable to store the user's menu choice

    do {
        // Display menu options
        cout << "\nAddress Book Menu\n";
        cout << "1. Create Address Book\n";
        cout << "2. View Address Book\n";
        cout << "3. Insert a Record\n";
        cout << "4. Delete a Record\n";
        cout << "5. Modify a Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Get the user's choice

        // Execute the appropriate function based on the user's choice
        switch (choice) {
            case 1: createAddressBook(addressBook); break; // Clear the address book
            case 2: viewAddressBook(addressBook); break; // Display all records
            case 3: insertRecord(addressBook); break; // Add a new record
            case 4: deleteRecord(addressBook); break; // Delete a specific record
            case 5: modifyRecord(addressBook); break; // Modify an existing record
            case 6: cout << "Exiting program.\n"; break; // Exit the program
            default: cout << "Invalid choice. Try again.\n"; // Handle invalid input
        }
    } while (choice != 6); // Continue until the user chooses to exit

    return 0; // Exit successfully
}

// Function to create/clear the address book
void createAddressBook(vector<Record> &addressBook) {
    addressBook.clear(); // Remove all records from the address book
    cout << "Address book created successfully.\n"; // Inform the user
}

// Function to view the address book
void viewAddressBook(const vector<Record> &addressBook) {
    if (addressBook.empty()) { // Check if the address book is empty
        cout << "Address book is empty.\n"; // Inform the user
        return;
    }

    // Display all records
    cout << "\nAddress Book Records:\n";
    for (size_t i = 0; i < addressBook.size(); ++i) {
        cout << i + 1 << ". Name: " << addressBook[i].name
             << ", Phone: " << addressBook[i].phone
             << ", Email: " << addressBook[i].email << endl;
    }
}

// Function to insert a new record into the address book
void insertRecord(vector<Record> &addressBook) {
    Record newRecord; // Create a new record
    cout << "Enter name: ";
    cin.ignore(); // Clear the input buffer before taking a new line input
    getline(cin, newRecord.name); // Get the name from the user
    cout << "Enter phone: ";
    cin >> newRecord.phone; // Get the phone number
    cout << "Enter email: ";
    cin >> newRecord.email; // Get the email

    addressBook.push_back(newRecord); // Add the new record to the address book
    cout << "Record added successfully.\n"; // Inform the user
}

// Function to delete a specific record from the address book
void deleteRecord(vector<Record> &addressBook) {
    if (addressBook.empty()) { // Check if the address book is empty
        cout << "Address book is empty.\n"; // Inform the user
        return;
    }

    int index; // Variable to store the record number to delete
    cout << "Enter the record number to delete: ";
    cin >> index; // Get the record number from the user

    if (index < 1 || index > (int)addressBook.size()) { // Validate the record number
        cout << "Invalid record number.\n"; // Inform the user if invalid
    } else {
        addressBook.erase(addressBook.begin() + index - 1); // Delete the record
        cout << "Record deleted successfully.\n"; // Inform the user
    }
}

// Function to modify an existing record in the address book
void modifyRecord(vector<Record> &addressBook) {
    if (addressBook.empty()) { // Check if the address book is empty
        cout << "Address book is empty.\n"; // Inform the user
        return;
    }

    int index; // Variable to store the record number to modify
    cout << "Enter the record number to modify: ";
    cin >> index; // Get the record number from the user

    if (index < 1 || index > (int)addressBook.size()) { // Validate the record number
        cout << "Invalid record number.\n"; // Inform the user if invalid
    } else {
        Record &record = addressBook[index - 1]; // Reference to the specific record
        // Prompt user for new values and update the record
        cout << "Enter new name (current: " << record.name << "): ";
        cin.ignore(); // Clear the input buffer before taking a new line input
        getline(cin, record.name); // Get the new name
        cout << "Enter new phone (current: " << record.phone << "): ";
        cin >> record.phone; // Get the new phone number
        cout << "Enter new email (current: " << record.email << "): ";
        cin >> record.email; // Get the new email
        cout << "Record modified successfully.\n"; // Inform the user
    }
}
