#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct User {
    string username;
    string password;
};

void registration();
void login();
bool check_duplicate(string username);
void save_user(User u);
bool verify_user(string username, string password);

void select() {
    char op;
    cout << "=====================================" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Quit" << endl;
    cout << "=====================================" << endl;
    cout << "Enter your choice: ";
    cin >> op;
    
    if (op == '1') {
        registration();
        select();
    }
    else if (op == '2') {
        login();
        select();
    }
    else if (op == '3') {
        cout << "THANK YOU FOR USING OUR SYSTEM!" << endl;
    }
    else {
        cout << "Invalid option! Try again." << endl;
        select();
    }
}

int main() {
    cout << "WELCOME TO LOGIN & REGISTRATION SYSTEM!" << endl << endl;
    select();
    return 0;
}

bool check_duplicate(string username) {
    ifstream file("users.txt");
    if (!file) {
        return false;
    }
    
    User u;
    while (file >> u.username >> u.password) {
        if (u.username == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void save_user(User u) {
    ofstream file("users.txt", ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    file << u.username << " " << u.password << endl;
    file.close();
}

void registration() {
    User u;
    string confirm_password;
    
    cout << "\n--- REGISTRATION FORM ---" << endl;
    cout << "Enter username: ";
    cin >> u.username;
    if (check_duplicate(u.username)) {
        cout << "ERROR: Username already exists! Please try another username." << endl << endl;
        return;
    }
    
    cout << "Enter password: ";
    cin >> u.password;
    cout << "Confirm password: ";
    cin >> confirm_password;
    
    if (u.password != confirm_password) {
        cout << "ERROR: Passwords do not match! Registration failed." << endl << endl;
        return;
    }
    
    if (u.password.length() < 4) {
        cout << "ERROR: Password must be at least 4 characters long!" << endl << endl;
        return;
    }
    
    save_user(u);
    cout << "SUCCESS! Account created successfully!" << endl << endl;
}

bool verify_user(string username, string password) {
    ifstream file("users.txt");
    if (!file) {
        cout << "No users found! Please register first." << endl;
        return false;
    }
    
    User u;
    while (file >> u.username >> u.password) {
        if (u.username == username && u.password == password) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void login() {
    string username, password;
    int attempts = 0;
    
    cout << "\n--- LOGIN FORM ---" << endl;
    
    while (attempts < 3) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        if (verify_user(username, password)) {
            cout << "ACCESS GRANTED! Welcome " << username << "!" << endl << endl;
            return;
        }
        else {
            attempts++;
            cout << "ERROR: Invalid username or password!" << endl;
            cout << "Attempts remaining: " << 3 - attempts << endl << endl;
        }
    }
    
    cout << "TOO MANY FAILED ATTEMPTS! Please try again later." << endl << endl;
}
