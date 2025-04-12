#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>  

using namespace std;

int account_fine();
void main_menu();
int userType = 0;
string user_roll_number;
int fine_amount;

class Book{
    private:
        string title, author, publisher, year, ISBN, availability, borrower, reserved_by_user;
    
    public:
        bool IsAvailable(){
            if(availability == "1")return true;
            else if(availability == "3"){
                if(this->reserved_by_user == user_roll_number)return true;
                else false;
            }
            return false;
        }
        void set_avail(string ava){
            this->availability = ava;
        }
        bool match_ISBN(string &ISBN){
            if(this->ISBN == ISBN)return true;
            else return false;
        }
        void set_ISBN(string &ISBN){
            this->ISBN = ISBN;
        }
        void set_borrower(string borrower){
            this->borrower = borrower;
        }
        void set_title(string &title){
            this->title = title;
        }
        void set_author(string &author){
            this->author = author;
        }
        void set_publisher(string &publisher){
            this->publisher = publisher;
        }
        void set_year(string &year){
            this->year = year;
        }
        void reserve(string &res_user){
            this->reserved_by_user = res_user;
        }
        string get_year(){
            return this->year;
        }
        string get_ISBN(){
            return this->ISBN;
        }
        string get_publisher(){
            return this->publisher;
        }
        string get_title(){
            return this->title;
        }
        string get_author(){
            return this->author;
        }

        Book(vector<string>&row){
            if(row.size() < 7)return;
            this->title = row[0];
            this->author = row[1];
            this->publisher = row[2];
            this->year = row[3];
            this->ISBN = row[4];
            this->availability = row[5];
            this->borrower = row[6];
        }

        string getISBN(){
            return this->ISBN;
        }

        friend void writeBooksToCSV(const string& filename);
        friend void check_available_books();
};


class User{
    protected:
        string roll_number;
        string username, password;
        int fine = 0;
        int user_type;
    
    public:
        bool match_password(string pass){
            if(pass == this->password)return true;
            else return false;
        }
        string get_roll_number(){
            return this->roll_number;
        }
        void set_username(string username){
            this->username = username;
        }
        bool match_roll_number(string &roll_number){
            if(this->roll_number == roll_number)return true;
            else return false;
        }
        void update_fine(){
            this->fine = account_fine();
        }
        string get_username(){
            return this->username;
        }
        void set_password(string &new_password){
            this->password = new_password;
        }
        int fine_amount(){
            return this->fine;
        }
        void manage_fine();
};

class Student:public User{
    private:

    public:
        Student(vector<string>&row){
            this->username = row[0];
            this->password = row[1];
            this->fine = stoi(row[2]);
            this->roll_number = row[3];
            this->user_type = stoi(row[4]);
        }
        friend void clear_fine(Student& obj);
        friend void writeStudentsToCSV(const string& filename);
};

class Professor:public User{
    private:

    public:
        Professor(vector<string>&row){
            this->username = row[0];
            this->password = row[1];
            this->fine = stoi(row[2]);
            this->roll_number = row[3];
            this->user_type = stoi(row[4]);
        }

        friend void writeProfessorsToCSV(const string& filename);
};

class Librarian:public User{
    public:
        Librarian(vector<string>&row){
            this->username = row[0];
            this->password = row[1];
            this->roll_number = row[2];
            this->user_type = stoi(row[3]);
        }
        friend void writeLibrariansToCSV(const string& filename);
};

class Account{
    private:
        string roll_number; 
        int balance;
        int reserve_balance;

    public:
        pair<string, string> reserved_book;
        vector<pair<string, string>>books_issued;

        Account(vector<string>& account_details){
            this->balance = stoi(account_details[1]);
            this->roll_number = account_details[0];
            this->reserve_balance = stoi(account_details[2]);
            for(int i=3; i<3+(3 - this->balance)*2; i+=2){
                this->books_issued.push_back({account_details[i], account_details[i+1]});
            }
            int index = account_details.size();
            if(reserve_balance == 1)return;
            else if(reserve_balance == 0){
                this->reserved_book = make_pair(account_details[index-2], account_details[index-1]);
            }
        }

        bool match_roll_number(string &roll_number){
            if(this->roll_number == roll_number)return true;
            return false;
        }
        
        Account();

        int check_balance(){
            return this->balance;
        }

        void set_balance(int balance){
            this->balance = balance;
        }

        int check_reserve_balance(){
            return this->reserve_balance;
        }

        void set_reserve_balance(int reserve_balance){
            this->reserve_balance = reserve_balance;
        }

        void add_books(pair<string, string> book_details){
            this->books_issued.push_back(book_details);
        }

        void add_reserve_books(pair<string, string> res_book_details){
            this->reserved_book = res_book_details;
        }
        friend int account_fine();
        void set_issued_books(vector<pair<string, string>>&issued){
            this->books_issued = issued;
        }
        friend void writeAccountsToCSV(const string& filename);
};

vector<Student>student_user;
vector<Professor>professor_user;
vector<Librarian>librarian_user;
vector<Book>books;
vector<Account>accounts;
User* user = nullptr;
Account* account = nullptr;
Book* book = nullptr;

void register_user();
void login_page();
int clear_fine();
vector<Student> readCSVtoStudent(const string &filename);
vector<Professor> readCSVtoProfessor(const string &filename);
vector<Librarian> readCSVtoLibrarian(const string &filename);
vector<Book> readCSVBook(const string &filename);
vector<Account> readCSVtoAccount(const string &filename);

void writeCSV(const string &filename, const vector<vector<string>> &data);
int search_account_index(string &roll_number);
int search_user_index(string &roll_number);
void fill_stud_cred(Student &obj, vector<string>&credential);
void fetch_account_details(string roll_number);
void main_menu();
void librarian_menu();
void sign_out();
void exit();
// int account_fine();
void author_books_display();
void remove_over_reservation();
void fill_prof_cred(Professor &obj, vector<string>&credential);
void print_student_list();
void print_prof_list();
void check_student_list();
void check_professor_list();
void check_issued_books();
void check_reserved_books();
void check_available_books();
void return_book();
void print_book_status(string availibility_type);
void remove_Student();
void writeStudentsToCSV(const string &filename);
void writeProfessorsToCSV(const string &filename);
void writeAccountsToCSV(const string &filename);
void writeBooksToCSV(const string &filename);
void writeLibrariansToCSV(const string &filename);
void add_books_library();
void remove_books_library();
void update_books_library();
void add_user_to_library();
void update_books_library();
void borrow_book();
void check_out();
void get_reserved_and_issued_books();
void get_printed_issued_books();
void get_reserved_books();
void unreserve_book();
void reserve_book();
void change_password();
void remove_user();
void reserve_book_further();
void user_borrowed_book_list();
void update_attribute(int change_option);
int search_book_index(string &ISBN);
time_t stringToTimeT(const std::string& datetime);
string addDays(const std::string& originalTime, int daysToAdd);
string getPassword();
string format_time(time_t time);

int main(){
    cout << "\033[1;34m"
    << "===============================================================================\n"
    << "                      WELCOME TO LIBRARY MANAGEMENT SYSTEM                     \n"
    << "===============================================================================\n\033[0m"
    << "\n\033[1;32m[1]\033[0m Log In    \033[1;32m[2]\033[0m Register    \033[1;31m[3]\033[0m Exit\n"
    << "===============================================================================\n"
    << "   Please enter your choice: ";

    int log_status; 
    string log_status_str; cin>>log_status_str;
    
    if(log_status_str == "1")log_status = 1;
    else if(log_status_str == "2")log_status = 2;
    else if(log_status_str == "3")log_status = 3;
    else log_status = 4;

    if(userType == 0){
        student_user = readCSVtoStudent("student_users.csv");
        professor_user = readCSVtoProfessor("professor_users.csv");
        librarian_user = readCSVtoLibrarian("librarian.csv");
        books = readCSVBook("books.csv");
        accounts = readCSVtoAccount("acc.csv");
        remove_over_reservation();
    }
    
    if(log_status == 1){
        login_page();
    } else if(log_status == 2){
        register_user();
    } else if(log_status == 3){
        exit();
        return 0;
    } else {
        cout << "\033[1;31m"
        << "--------------------------------------------------\n"
        << "  ERROR: Invalid Entry!\n"
        << "  Please Try Again.\n"
        << "--------------------------------------------------\n"
        << "\033[0m";
        return main();
    }
    return 0;
}

void user_borrowed_book_list(){
    cout<<"Sl. No | ISBN | Due Data and Time | Title | Author"<<endl;
    for(int i=1; i<=(userType*2+1 - account->check_balance()); i++){
        int index = search_book_index(account->books_issued[i-1].first);
        cout<<i<<"      | "<<account->books_issued[i-1].first<<" | "<<stringToTimeT(account->books_issued[i-1].second) + 15*24*3600 <<" | "<<books[index].get_title()<<" | "<<books[index].get_author()<<endl;
    }
}

void change_password(){
    cout << "Hello, " << user->get_username() << "!\n";
    cout << "Please enter your current password to proceed.\n";
    cout << "(Or enter \033[1;34m[1]\033[0m to return to the main menu)\n";

    cout << "\n\033[1;34m=============================================\033[0m\n";
    cout << "\033[1;32m            Hello, " << user->get_username() << "!   \033[0m\n";
    cout << "\033[1;34m=============================================\033[0m\n\n";
    cout << "\033[1;37m Please enter your \033[1;33mcurrent password\033[1;37m to proceed.\033[0m\n";
    cout << "(\033[1;34mEnter [1] to return to the main menu\033[0m)\n";
    

    string old_password, new_password, new_username;
    // old_password = getPassword();
    cin >> old_password;

    if (old_password == "1") {
        if(userType != 3)main_menu();
        else librarian_menu();
        return;
    }
    cout << "\n\033[1;34m========================================\033[0m\n";
    cout << "   \033[1;36m        Account Settings\033[0m\n";
    cout << "\033[1;34m========================================\033[0m\n\n";
    cout << "\033[1;33m[1]\033[0m Change Username\n";
    cout << "\033[1;33m[2]\033[0m Change Password\n";

    int option; cin>>option;
    if(option == 1){
        if (user->match_password(old_password)) {
            cout << "Enter new Username:\n";
            // cin >> new_username;
            cin.ignore();
            getline(cin, new_username);
            user->set_username(new_username);
            cout << "\033[1;32mUsername changed successfully!\033[0m\n";
        } else {
            cout << "\033[1;31mError: Incorrect password entered. Please try again.\033[0m\n";
        }
        if(userType != 3)main_menu();
        else librarian_menu();
        return;
    } else if(option != 2){
        cout<<"Invalid entry"<<endl; 
        if(userType != 3)main_menu();
        else librarian_menu(); 
        return;
    }
    if (user->match_password(old_password)) {
        cout << "Enter a new, strong password:\n";
        cin >> new_password;
        // new_password = getPassword();
        user->set_password(new_password);
        cout << "\033[1;32mPassword changed successfully!\033[0m\n";
    } else {
        cout << "\033[1;31mError: Incorrect password entered. Please try again.\033[0m\n";
    }
    if(userType != 3)main_menu();
    else librarian_menu();
}

void remove_over_reservation(){
    time_t  now = time(0);
    for(int i=0; i<accounts.size(); i++){
        if(accounts[i].check_reserve_balance() == 0){
            time_t then = stringToTimeT(accounts[i].reserved_book.second);
            if((now - then) > 2*24*3600){
                accounts[i].set_reserve_balance(1);
                int index = search_book_index(accounts[i].reserved_book.first);
                book = &books[index];
                book->set_avail("1");
                book->set_borrower("ava#");
            }
        }
    }
}

void get_reserved_and_issued_books(){
    get_printed_issued_books();cout<<endl;
    get_reserved_books();cout<<endl;
    main_menu();
}

void get_reserved_books(){
    if(account == nullptr)cout<<"Acc NULL"<<endl;
    if (account->check_reserve_balance() == 1) {
        cout << "\033[1;31m No books have been Reserved.\033[0m\n"; return;
    }
    cout << "\033[1;36m====================================\n";
    cout << "           Reserved Books\n";
    cout << "====================================\033[0m\n\n";
    
    cout << "\033[1;34mSl. No | Title                     | Author             | Publisher         | ISBN          | Checked Out Date    | Due Date\033[0m\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < 1; i++) {
        int index = search_book_index(account->reserved_book.first);
        book = &books[index];
    
        cout << "\033[1;33m" << i + 1 << "\033[0m      | " 
            << book->get_title() << string(max(0, (int)(26 - book->get_title().length())), ' ') << "| " 
            << book->get_author() 
            << string(std::max(0, 19 - static_cast<int>(book->get_author().length())), ' ') << "| "  
            << book->get_publisher()  
            << string(std::max(0, 18 - static_cast<int>(book->get_publisher().length())), ' ') << "| "  
            << book->getISBN()  
            << string(std::max(0, 14 - static_cast<int>(book->getISBN().length())), ' ') << "| "  
            << account->reserved_book.second << " | " 
            << addDays(account->reserved_book.second, 2) << "\n";
    }
}

void get_printed_issued_books(){
    if(account == nullptr)cout<<"Acc NULL"<<endl;
    if (account->check_balance() == 2 * userType + 1) {
        cout << "\033[1;31m No books have been issued.\033[0m\n"; return;
    }
    cout << "\033[1;36m====================================\n";
    cout << "              Issued Books\n";
    cout << "====================================\033[0m\n\n";
    
    cout << "\033[1;34mSl. No | Title                     | Author             | Publisher         | ISBN           | Checked Out Date    | Due Date\033[0m\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < ((2*userType) +1 - account->check_balance()); i++) {
        int index = search_book_index(account->books_issued[i].first);
        if(index == -1)cout<<"index error"<<endl;
        book = &books[index];
    
        cout << "\033[1;33m" << i + 1 << "\033[0m      | " 
        << book->get_title() << string(max(0, (int)(26 - book->get_title().length())), ' ') << "| " 
        << book->get_author() 
        << string(std::max(0, 19 - static_cast<int>(book->get_author().length())), ' ') << "| "  
        << book->get_publisher()  
        << string(std::max(0, 18 - static_cast<int>(book->get_publisher().length())), ' ') << "| "  
        << book->getISBN()  
        << string(std::max(0, 14 - static_cast<int>(book->getISBN().length())), ' ') << " | "  
        << account->books_issued[i].second << " | " 
        << addDays(account->books_issued[i].second, 15) << "\n";
    }
}

string addDays(const std::string& originalTime, int daysToAdd) {
    tm timeStruct = {};
    istringstream ss(originalTime);
    ss >> get_time(&timeStruct, "%Y-%m-%d %H:%M:%S");
    time_t timeEpoch = std::mktime(&timeStruct);
    timeEpoch += daysToAdd * 24 * 60 * 60; 
    tm* updatedTime = localtime(&timeEpoch);
    ostringstream result;
    result << put_time(updatedTime, "%Y-%m-%d %H:%M:%S");

    return result.str();
}

void return_book(){
    if(account->check_balance() == (userType*2+1)){
        cout<<"You have not borrowed any book\n"<<endl;
        main_menu();
    }
    cout<<"Here's the list of your borrowed books"<<endl<<endl;
    user_borrowed_book_list();cout<<endl;
    cout<<"Press 1 to return a book"<<endl;
    cout<<"Press 2 to return to main menu"<<endl;
    int option; cin>>option;
    if(option == 2){
        main_menu(); return;
    } else if(option != 1){
        cout<<"Wrong key pressed !"<<endl; return_book(); return;
    }

    cout<<"Please enter the ISBN Number of the book you want to return: ";
    string ISBN; cin>>ISBN; bool matched = false; int index = -1;
    for(int i=1; i<=(userType*2+1 - account->check_balance()); i++){
        if(ISBN == account->books_issued[i-1].first){
            matched = true; index = i-1;
        }
    }
    if(matched == false){
        cout<<"You entered wrong ISBN number"<<endl; return_book(); return;
    }
    vector<pair<string, string>>issued;
    for(int i=0; i<(userType*2+1 - account->check_balance()); i++){
        if(index == i)continue;
        issued.push_back(account->books_issued[i]);
    }
    cout<<"Return succesfull.\n";
    book = &books[search_book_index(ISBN)];
    string availibility = "1";
    book->set_avail(availibility); 
    book->set_borrower("ava#");
    account->set_issued_books(issued);
    account->set_balance(account->check_balance() + 1);
    main_menu();
}

int account_fine(){
    int fine = 0; 
    if(userType == 2)return 0; 
    int one_day_second = 24*3600; 
    time_t now = time(0);  
    time_t var; 
    if(account == nullptr){
        cout<<"NULL";
    }
    for(auto record: account->books_issued){
        var = stringToTimeT(record.second);
        if((now-var) <= 15*one_day_second)continue;
        fine += (now-var-14*one_day_second-1)/one_day_second;
    }
    return 10*fine;
}

void unreserve_book(){
    if(account->check_reserve_balance() == 1){
        cout << "\n\033[36m🔍 No reserved books found! \033[0m\033[32mYou have no books available for unreservation.\033[0m" << endl;
        main_menu(); return;
    }
    int index = search_book_index(account->reserved_book.first);
    book = &books[index];

    cout << "\033[33mAre you sure you want to unreserve the book\033[0m \033[36m\"" 
    << book->get_title() << "\"\033[0m \033[33mby\033[0m \033[36m" 
    << book->get_author() << "?\033[0m\n" << endl;
    cout << "\033[32m[1] Unreserve 📖  \033[0m\033[34m[2] Return to Main Menu 🔙\033[0m" << endl;

    string option; cin>>option;
    if(option == "2"){
        main_menu(); return;
    } else if(option != "1"){
        cout << "\033[31mInvalid entry. Please try again.\033[0m" << endl;
        unreserve_book(); return;
    }

    account->set_reserve_balance(1);
    book->set_avail("1");
    book->set_borrower("ava#");
    cout << "\033[1;32m✅ \"" << book->get_title() << "\" by " << book->get_author() 
    << " is now unreserved.\033[0m\n";
    main_menu();
}

void User::manage_fine() {
    this->fine = user->fine_amount() + account_fine();
    if (this->fine == 0) {
        cout << "\033[1;32m"  
            << " Dear User, You have no dues.\n"
            << "\033[0m";  
        main_menu();
        return;
    }
    cout << "\033[1;33m"  
        << "Dear User, You have ₹" << this->fine << " as a fine for late book return.\n"
        << "\n[1] Clear Dues\n"
        << "[2] Go Back to Main Menu\n"
        << "\033[0m";

    int option; cin >> option;

    if (option == 1) {
        int fine_status = clear_fine();
        if (fine_status == 1) {
            this->fine = 0;
            cout << "\033[1;32m"  
                << "Your fine has been cleared successfully!\n"
                << "\033[0m";
        } else {
            cout << "\033[1;31m"  
                << "Payment failed. Returning to main menu...\n"
                << "\033[0m";
        }
        main_menu();
        return;
    } else if (option == 2) {
        main_menu();
    } else {
        cout << "\033[1;31m"  
            << "Invalid Input! Reloading...\n"
            << "\033[0m";
        manage_fine();
        return;
    }
}

time_t stringToTimeT(const std::string& datetime) {
    std::tm tm = {}; 
    string format = "%Y-%m-%d %H:%M:%S";
    istringstream ss(datetime);
    ss >> std::get_time(&tm, format.c_str()); 
    if (ss.fail()) {
        throw std::invalid_argument("Failed to parse datetime string");
    }
    return std::mktime(&tm); 
}

string format_time(time_t time) {
    tm *ltm = localtime(&time);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S"); 
    return ss.str();
}

int clear_fine() {
    cout << "\033[1;33m"  
        << "To clear your dues, type 'CLEAR' in uppercase: "
        << "\033[0m";
    string confirmation; cin >> confirmation;
    if (confirmation == "CLEAR") {
        cout << "\033[1;32m"  
            << "Dues Cleared Successfully!\n"
            << "\033[0m";
        return 1;
    } else {
        cout << "\033[1;31m"  
            << "Dues NOT Cleared. Action Cancelled.\n"
            << "\033[0m";
        return 0;
    }
}


void main_menu(){
    cout << endl << "\033[1;36m"  
    << "==================================================\n"
    << "                    MAIN MENU                    \n"
    << "==================================================\n"
    << "\033[0m";  
    cout << "\033[1;32m  \n Hello, " << user->get_username() << "!\033[0m\n\n";
    cout << "\033[1;33m"  
    << "[0] Change Username or Password\n"
    << "[1] Manage Fines\n"
    << "[2] Check Book Availability\n"
    << "[3] Reserve a Book\n"
    << "[4] Unreserve a Book\n"
    << "[5] Borrow a Book\n"
    << "[6] Return a Book\n"
    << "[7] Check Issued/Reserved Books\n"
    << "[8] Check Books by Author\n"
    << "[9] Sign Out\n"
    << "\033[0m";  
    cout << "\nEnter your choice: ";

    int verified_input; string option; 
    cin>>option;
    if(option.length() == 1 && (int)option[0] >= 48  && (int)option[0] <= 57){
        verified_input = (int)(option[0] - '0');
    } else {
        cout << "\033[1;31m"  
        << "⚠ ERROR: Invalid Input! Please enter a number.\n"
        << "Reloading the menu...\n"
        << "\033[0m";
        main_menu(); return;
    }
    switch (verified_input)
    {
    case 0:
        change_password();
        break;
    case 1:
        user->manage_fine();
        break;
    case 2:
        check_available_books();
        main_menu();
        break;
    case 3:
        reserve_book();
        break;
    case 4:
        unreserve_book();
        break;
    case 5:
        check_out();
        break;
    case 6:
        return_book();
        break;
    case 7:
        get_reserved_and_issued_books();
        break;
    case 8:
        author_books_display();
        break;
    case 9:
        sign_out();
        break;
    default:
        break;
    }
}

void print_student_list(){
    for(int i=0; i<student_user.size(); i++){
        cout<<"Student   "<<student_user[i].get_roll_number()<<" | "<<student_user[i].get_username()<<endl;
    }
}
void print_prof_list(){
    for(int i=0; i<professor_user.size(); i++){
        cout<<"Professor "<<professor_user[i].get_roll_number()<<" | "<<professor_user[i].get_username()<<endl;
    }
}

void librarian_menu(){
    cout << "\033[1;34m"
    << "=====================================================================\n"
    << "                       WELCOME, LIBRARIAN                           \n"
    << "=====================================================================\n\033[0m";
    cout << "\033[1;32m  \n Hello, " << user->get_username() << "!\033[0m\n\n";

    cout 
    << "\033[1;32m[0]\033[0m  Change Username or Password\n"
    << "\033[1;32m[1]\033[0m  Add a new book to the library\n"
    << "\033[1;32m[2]\033[0m  Remove a book from the library\n"
    << "\033[1;32m[3]\033[0m  Update book details\n"
    << "\033[1;32m[4]\033[0m  Register a new user\n"
    << "\033[1;32m[5]\033[0m  Remove a user\n"
    << "\033[1;31m[6]\033[0m  Sign out\n\n";

    cout << "\033[1;34m=====================================================================\n\033[0m"
    << "   \033[1;33mPlease enter your choice:\033[0m ";


    string option; cin>>option;
    int verified_input;
    if(!(option.length()==1 && (int)(option[0])>=48 && (option[0])<=57)){
        cout<<"Invalid entry"<<endl; 
        librarian_menu(); return;
    } else {
        verified_input = (int)(option[0]-'0');
    }
    switch (verified_input)
    {
    case 0:
        change_password();
        break;
    case 1:
        add_books_library();
        break;
    case 2:
        remove_books_library();
        break;
    case 3:
        update_books_library();
        break;  
    case 4:
        add_user_to_library();
        break;
    case 5:
        remove_user();
        break;
    case 6:
        sign_out();
        break;
    default:
        break;
    }
}

void remove_user(){
    cout << "\n\033[1;34mListed Users:\033[0m\n\n";
    cout << "--------------------------------------\n";
    cout << " User Type  | Roll/PF Number | Username \n";
    cout << "--------------------------------------\n";
    

    print_student_list(); cout<<endl;
    print_prof_list(); cout<<endl;

    string roll_number;
    cout << "\033[1;34mEnter the Roll/PF number to remove,\033[0m or press \033[1;32m[1]\033[0m to return to the main menu: ";
    cin>>roll_number;
    if(roll_number == "1"){
        librarian_menu(); return;
    }
    User* userRM =  nullptr;
    userRM = user;
    int index = search_user_index(roll_number);
    if(index == -1){
        cout << "\033[1;31mNo user found.\033[0m\n";
        cout << "\033[1;33mTry again.\033[0m\n";        
        remove_user();
    }
    if(userType == 3){
        cout << "\033[1;31mError:\033[0m You cannot remove another \033[1;34mLibrarian!\033[0m\n";
        librarian_menu();
    }
    if(userType == 1){
        user = &student_user[index];
    } else {
        user = &professor_user[index];
    }
    user->set_username("");
    cout<<user->get_username();
    cout << "\033[1;32mUser removed successfully!\033[0m\n";
    writeStudentsToCSV("student_users.csv");
    writeProfessorsToCSV("professor_users.csv");
    student_user = readCSVtoStudent("student_users.csv");
    professor_user = readCSVtoProfessor("professor_users.csv");
    userType = 3; user = userRM;
    librarian_menu();
}

void add_user_to_library(){
    cout << "\033[1;34m"
    << "------------------------------------------------------------\n"
    << "                     ADD USER DETAILS                      \n"
    << "------------------------------------------------------------\n\033[0m"
    << endl;
    cout << "\033[1;32m  Please enter the details of the user to be updated.\033[0m\n" << endl;    
    string roll_number, username, password, fine, userType;
    cout << "\033[1;36m  Enter Roll Number: \033[0m";

    cin>>roll_number;
    int index = search_account_index(roll_number);
    if(index != -1){
        cout << "\033[1;31m  Error: A user with this Roll/PF Number already exists.\033[0m" << endl;
        librarian_menu(); return;
    } else {
        cout << "\033[1;36m  Please enter your username: \033[0m";
        cin.ignore();
        getline(cin, username);
        cout << "\033[1;36m  Please enter your password: \033[0m";
        cin>>password;
        string confirm_pass;
        system("clear");
        cout << "\033[1;36m  Please re-enter your password: \033[0m";
        cin>>confirm_pass;
        if(password != confirm_pass){
            cout << "\033[1;31m  Error: Your passwords do not match.\033[0m" << endl;
            cout << "\033[1;33m  Redirecting to Main Menu... Please wait.\033[0m" << endl;            
            librarian_menu(); return;
        }
        cout << "\033[1;36m🔹 Please select your user type:\033[0m\n" << endl;
        cout << "\033[1;32m[1] Student\033[0m" << endl;
        cout << "\033[1;34m[2] Professor\033[0m" << endl;
        cout << "\033[1;35m[3] Librarian\033[0m\n" << endl;
        cout << "\033[1;36mEnter your choice: \033[0m";                
        cin>>userType;
        if(userType == "1"){
            vector<string> data = {username, password, "0", roll_number, "1"};
            Student stud(data);
            student_user.push_back(stud);
            cout << "\033[1;32m Student added successfully!\033[0m" << endl;
            writeStudentsToCSV("student_users.csv");
            student_user = readCSVtoStudent("student_users.csv");
            data.clear();
            data = {roll_number, "3", "1"};
            Account acc(data);
            accounts.push_back(acc);
            writeAccountsToCSV("acc.csv");
            accounts = readCSVtoAccount("acc.csv");
        } else if(userType == "2"){
            vector<string> data = {username, password, "0", roll_number, "2"};
            Professor prof(data);
            professor_user.push_back(prof);
            cout << "\033[1;32m  Professor added successfully!\033[0m" << endl;
            writeProfessorsToCSV("professor_users.csv");
            professor_user = readCSVtoProfessor("professor_users.csv");
            data.clear();
            data = {roll_number, "5", "1"};
            Account acc(data);
            accounts.push_back(acc);
            writeAccountsToCSV("acc.csv");
            accounts = readCSVtoAccount("acc.csv");
        } else if(userType == "3"){
            vector<string> data = {username, password, roll_number, "3"};
            Librarian libr(data);
            librarian_user.push_back(libr);
            cout << "\033[1;32m Librarian added successfully!\033[0m" << endl;
        } else {
            cout << "\033[1;31m  Invalid User Type!\033[0m\n";
            cout << "\033[1;33m  Reloading... Please wait.\033[0m" << endl;            
            librarian_menu(); return; 
        }
        librarian_menu();
    }
}

void update_attribute(int change_option, string attribute){
    cout<<"Please enter ISBN Number of the book whose "<<attribute<<" you want to update"<<endl;
    string ISBN; cin>>ISBN;
    int index = search_book_index(ISBN);
    if(index == -1){
        cout<<"No book with this ISBN exist"<<endl; 
    } else {
        book = &books[index];
        cout<<"Please enter the correct "<<attribute<<" of the book"<<endl;
        string changed_attribute; cin.ignore();
        getline(cin, changed_attribute);
        switch (change_option)
        {
        case 1:
            book->set_title(changed_attribute);
            break;
        case 2:
            book->set_author(changed_attribute);
            break;
        case 3:
            book->set_publisher(changed_attribute);
            break;
        case 4:
            book->set_year(changed_attribute);
            break;
        default:
            break;
        }
        cout<<"Your "<<attribute<<" changed successfully to "<<changed_attribute<<endl;
    }
    return update_books_library();
}

void change_availability_status(){
    cout << "\033[1;34m📚 Please enter the ISBN number of the book whose availability status is to be updated:\033[0m" << endl;
    string ISBN;
    cin >> ISBN;
    int index = search_book_index(ISBN);
    if (index == -1) {
        cout << "\033[1;31m❌ No books found!\033[0m" << endl;
        return;
    }
    book = &books[index];
    if (book->IsAvailable()) {
        cout << "\033[1;33m⚠️ You cannot allot available books without user's authorization!\033[0m" << endl;
        update_books_library();
        return;
    } else {
        cout << "\033[1;32m✅ Are you sure you want to make the book available?\033[0m" << endl;
        cout << "📌 Press \033[1m[1]\033[0m to confirm\n";
        cout << "🚫 Press \033[1m[2]\033[0m to abort process" << endl;
        
        string option;
        cin >> option;
        
        if (option == "2") {
            cout << "\033[1;31m🚨 Process aborted!\033[0m" << endl;
            change_availability_status();
            return;
        } else if (option != "1") {
            cout << "\033[1;31m❌ Invalid entry!\033[0m" << endl;
            change_availability_status();
            return;
        } else {
            book->set_avail("1");
            book->set_borrower("ava#");
        }
    }
    change_availability_status();
    return;
}


void update_books_library(){
    cout << "\n\033[1;34m[1]\033[0m Update the book title\n";
    cout << "\033[1;34m[2]\033[0m Update the author\n";
    cout << "\033[1;34m[3]\033[0m Update the publisher\n";
    cout << "\033[1;34m[4]\033[0m Update the publication year\n";
    cout << "\033[1;34m[5]\033[0m Update availability status\n";
    cout << "\033[1;34m[6]\033[0m Return to the main menu\n";    

    int option; cin>>option;
    switch (option)
    {
    case 1:
        update_attribute(1, "'Title'");
        return;
    case 2:
        update_attribute(2, "'Author'");
        return;
    case 3:
        update_attribute(3, "'Publisher'");
        return;
    case 4:
        update_attribute(4, "'Year'");
        return;
    case 5:
        ////To be seen
        change_availability_status();
        return;
    case 6:
        librarian_menu(); 
        return;
    default:
        cout<<"Invalid entry......"<<endl<<endl;
        librarian_menu(); 
        return;
    }
    librarian_menu();
}

void add_books_library(){
    string title, author, publisher, year, ISBN;
    cout << "\n\033[1;34m Add Book Details\033[0m\n";
    cout << "------------------------------------------\n\n";
    cout << "\033[1;37mEnter the book details to add it to the library.\033[0m\n";
    cout << "(Press \033[1;33m[Enter]\033[0m to return to the main menu)\n\n";
    cout << "\033[1;36m Title:\033[0m ";
    
    cin.ignore();
    getline(cin, title);
    if(title == ""){
        librarian_menu(); return;
    }
    cout << "\033[1;36m Please enter the author's name: \033[0m";
    getline(cin, author);
    cout << "\033[1;36m Please enter the publisher's name: \033[0m";
    getline(cin, publisher);
    cout << "\033[1;36m Please enter the publication year: \033[0m";
    getline(cin, year);
    cout << "\033[1;36m Please enter the ISBN number: \033[0m";
    getline(cin, ISBN);

    cout << "\n\033[1;34m Book Details to be Added:\033[0m\n";
    cout << "--------------------------------------\n";
    cout << "\033[1;36mTitle:\033[0m " << title << "\n";
    cout << "\033[1;36mAuthor:\033[0m " << author << "\n";
    cout << "\033[1;36mPublisher:\033[0m " << publisher << "\n";
    cout << "\033[1;36mYear:\033[0m " << year << "\n";
    cout << "\033[1;36mISBN Number:\033[0m " << ISBN << "\n\n";
    
    cout << "\033[1;32m[1]\033[0m Add Book\n";
    cout << "\033[1;31m[2]\033[0m Abort Addition of Book\n";    

    int option; cin>>option;
    if(option == 1){
        vector<string> book_detail= {title, author, publisher, year, ISBN, "1", "ava#"};
        Book bk(book_detail);
        books.push_back(bk);
        cout << "\033[1;32m   Book added successfully!\033[0m\n";
    } else if(option == 2){
        cout << "\033[1;31m Process aborted! Book not added.\033[0m\n";
    } else {
        cout << "\033[1;31m Invalid entry! Please try again.\033[0m\n";
        add_books_library(); return;
    }
    librarian_menu();
}

void remove_books_library(){
    cout << "\n\033[1;34m  Here’s the list of available books:\033[0m\n";
    check_available_books();
    string ISBN;
    cout << "\n\033[1;33mEnter the ISBN number of the available book:\033[0m\n";
    
    cin>>ISBN;
    int index = search_book_index(ISBN);
    if(index == -1){
        cout << "\033[1;31m Book with ISBN " << ISBN << " does not exist.\033[0m\n";
    } else {
        if(books[index].IsAvailable()){
            books[index].set_borrower("removed_book");
            cout << "\033[1;32m  Book successfully removed.\033[0m\n";
            writeBooksToCSV("books.csv");
            books = readCSVBook("books.csv");
        } else {
            cout << "\033[1;31m  Sorry, this book is not available. Please choose from the available options.\033[0m\n";
        }
    }
    cout << "\n\033[1;34m[1]\033[0m Remove another book\n";
    cout << "\033[1;34m[2]\033[0m Return to the main menu\n";    

    int option; cin>>option;
    if(option == 1){
        remove_books_library(); return;
    } else if(option == 2){
        librarian_menu(); return;
    } else {
        cout<<"Invalid Entry...."<<endl;
        librarian_menu(); return;
    }
}

void author_books_display(){
    cout << "\033[1;34m Enter the name of the author whose book you want to search:\033[0m\n";
    string author; 
    cin.ignore();
    getline(cin, author);
    int author_count = 0;
    for(int i=0; i<books.size(); i++){
        if(books[i].get_author() == author){
            author_count++;
            if(author_count == 1){
                cout << "\n\033[1;36m Title            | Author         | Publisher       | Year | ISBN        | Availability\033[0m\n\n";

                
            }
            cout<<books[i].get_title()<<" | "<<books[i].get_author()<<" | "<<books[i].get_publisher()<<" | "<<books[i].get_year()<<" | "<<books[i].get_ISBN()<<" | ";
            if (books[i].IsAvailable())cout << "\033[1;32m Available\033[0m\n";  
            else cout << "\033[1;31m Not Available\033[0m\n";
        }
    }
    if (author_count == 0) {
        cout << "\033[1;31m No books by this author are available. The author may not be in the database.\033[0m\n";
    }
    cout << "\n\033[1;34m[1]\033[0m Return to the Main Menu\n";
    cout << "\033[1;34m[2]\033[0m Search for another author\n";        
    int option; cin>>option;
    if(option == 1)main_menu();
    else if(option == 2)author_books_display();
    else {
        cout<<"Exception Occured"<<endl;
        main_menu();
    }
}

void reserve_book() {
    int reserve_balance = account->check_reserve_balance();
    user->update_fine();
    int fine = user->fine_amount();
    if (reserve_balance == 0) {
        cout << "\033[1;31m Check-out limit exceeded!\033[0m\n";
        cout << "\033[1;33m  You have already checked out the maximum allowed number of books (1).\033[0m\n";
        main_menu();
        return;
    } else if (fine > 0) {
        cout << "\033[1;31m You have an outstanding due amount. Please clear it before reserving a book.\033[0m\n";
        main_menu();
        return;
    } else {
        reserve_book_further();
    }
}

void reserve_book_further(){
    check_available_books();
    cout << "\033[1;33m📌 Please carefully note the ISBN number of the book you want to reserve.\033[0m" << endl;
    cout << "\033[1;34m(Press [1] to return to the main menu)\033[0m\n" << endl;    
    string ISBN_book; cin>>ISBN_book;
    if(ISBN_book == "1"){
        main_menu(); return;
    } 
    int index = search_book_index(ISBN_book);
    if(index == -1){
        cout<<"Please enter a correct ISBN number\n"<<endl; reserve_book_further(); return;
    }
    book = &books[index];
    book->set_avail("3");
    book->set_borrower(user->get_roll_number());
    time_t now = time(0);
    account->reserved_book = {ISBN_book, format_time(now)};
    account->set_reserve_balance(0);
    cout << "\033[1;36m " << book->get_title() << " by " << book->get_author() 
    << " has been reserved for you for a maximum of 2 days.\033[0m\n";
    main_menu();
}

void check_out(){
    int balance = account->check_balance();
    user->update_fine();
    int fine = user->fine_amount();
    if(balance == 0){
        cout << "\033[1;31mCheck Out Limit Exceeded\033[0m\n";
        cout << "\033[1;33mYou have checked out the maximum of " << 2 * userType + 1 << " books.\033[0m\n";        
        main_menu(); return;
    } else if(fine > 0){
        cout << "\n\033[1;31mYou have some Due Amount. Please clear it first.\033[0m\n";
    } else {
        borrow_book();
    }
}

void borrow_book(){
    check_available_books();
    if(account->check_reserve_balance() == 0){
        int index = search_book_index(account->reserved_book.first);
        if(index != -1){
            book = &books[index];
            cout<<book->get_title()<<" | "<<book->get_author()<<" | "<<book->get_publisher()<<" | "<<book->get_year()<<" | "<<book->get_ISBN()<<endl;
        }
    }
    cout << "\033[1;33m"
    << "=============================================================\n"
    << "           PLEASE NOTE THE ISBN NUMBER CAREFULLY            \n"
    << "=============================================================\n\033[0m"
    << endl;
    cout << "\033[1;35m (Or press 1 to return to the main menu)\033[0m\n";
    string ISBN_book; cin>>ISBN_book;
    if(ISBN_book == "1"){
        return main_menu();
    }
    int index = search_book_index(ISBN_book);
    if(index == -1){
        cout << "\033[33m⚠ Invalid ISBN! \033[0m\033[36mPlease enter a correct ISBN number.\033[0m" << endl;
        borrow_book(); return;
    }
    if(account->reserved_book.first == ISBN_book){
        unreserve_book();
    }
    book = &books[index];
    cout << "\033[32mBook successfully checked out! ✅\033[0m" << endl;
    book->set_avail("2");
    book->set_borrower(user->get_roll_number());
    time_t now = time(0);
    account->add_books({book->getISBN(), format_time(now)});
    account->set_balance(account->check_balance() - 1);
    main_menu();
}

void register_user(){
    cout << "\n\033[34m====================================================\033[0m" << endl;
    cout << "\033[32m      📜   WELCOME TO THE REGISTER PAGE   📜\033[0m" << endl;
    cout << "\033[34m====================================================\033[0m\n" << endl;
    
    string roll_number, password, username, confirm_password;
    userType = -1;
    cout << "\033[33mPlease enter your Roll/PF Number:\033[0m" << endl;
    cout << "\033[34m(Press [1] to return to the Home Page.)\033[0m\n" << endl;
    cin>>roll_number;    
    if(roll_number == "1"){
        main(); return;
    }
    int index = search_user_index(roll_number);
    if(index != -1){
        cout<<"index: "<<index<<endl;
        cout<<endl<<"User Already Exists"<<endl;
        cout<<"Redirecting to Home Page................"<<endl<<endl;
        login_page(); return;
    }
    cout<<"Please set a username: ";
    cin.ignore();
    getline(cin, username);
    cout<<"Please set a password: ";
    // password = getPassword();
    cin>>password;
    system("clear");
    cout<<"Please re-enter your password: ";
    // confirm_password = getPassword();
    cin>>confirm_password;
    if(password != confirm_password){
        cout<<"Your password did not match!\nTry again\n\n";
        register_user();
    }
    for (size_t i = 0; i < confirm_password.length(); i += 2) {
        confirm_password[i] = '*';
    }
    cout << endl;
    cout << "\033[33m⚠ Are you sure you want to add a user with the following details?\033[0m\n" << endl;
    cout << "\033[36mUsername:\033[0m " << username << endl;
    cout << "\033[36mRoll Number:\033[0m " << roll_number << endl;

    cout << "\n\033[32m[1] Register Student 📜\033[0m" << endl;
    cout << "\033[31m[2] Abort Process ❌\033[0m" << endl;
    
    string final_option;
    cout << "\n\033[35mEnter your choice:\033[0m ";
    cin >> final_option;

    if(final_option == "2"){
        register_user(); return;
    } else if(final_option != "1"){
        cout << "\033[31m❌ Invalid entry. Please try again.\033[0m" << endl;
        register_user(); return;
    } 

    vector<string>row = {username, password, "0", roll_number, "1"};
    Student stud(row);
    student_user.push_back(stud);
    vector<string> account_string = {roll_number, "3", "1"};
    Account acc1(account_string);
    accounts.push_back(acc1);
    cout<<"Dear Student, You are have been successfully registered."<<endl<<endl;
    login_page();
}

void exit(){
    cout << "\033[1;32m"  
    << "--------------------------------------------------\n"
    << "       THANK YOU FOR USING THE LIBRARY SYSTEM    \n"
    << "--------------------------------------------------\n"
    << "\033[0m";  

    writeBooksToCSV("books.csv");
    writeAccountsToCSV("acc.csv");
    writeStudentsToCSV("student_users.csv");
    writeProfessorsToCSV("professor_users.csv");
    writeLibrariansToCSV("librarian.csv");
    return;
}

void sign_out() {
    cout << "\033[1;32m"  
        << "--------------------------------------------------\n"
        << "     Successfully Signed Out! See you again.      \n"
        << "--------------------------------------------------\n"
        << "\033[0m"<<endl<<endl; 
    main();  
}

// string getPassword() {
//     string password;
//     char ch;
//     while ((ch = _getch()) != '\r') {  
//         password.push_back(ch);
//         cout << '*'; 
//     }
//     cout << endl;
//     return password;
// }

void login_page() {
    cout << "\n\033[1;34m---------------------------- Login Page ---------------------------\033[0m\n";
    
    string roll_number, password;
    cout << "\n\033[1;32mPlease enter your Roll/PF Number: \033[0m";
    cout << "\n\033[1;33m(Press 1 to return to Home Page)\033[0m\n";
    cin >> roll_number;

    if (roll_number == "1") {
        main(); 
        return;
    }

    int index = search_user_index(roll_number);
    
    if (index == -1) {
        cout << "\n\033[1;31mUser Not Registered!\033[0m\n";
        cout << "\033[1;36m[1]\033[0m Register\n";
        cout << "\033[1;36m[2]\033[0m Retry Login\n";
        cout << "Enter your choice: ";
        
        int decision;
        cin >> decision;

        if (decision == 1) {
            register_user();
        } else if (decision == 2) {
            login_page();
        } else {
            cout << "\033[1;31mInvalid Entry! Redirecting to Home Page...\033[0m\n";
            main();
        }
        return;
    }

    switch (userType) {
        case 1: user = &student_user[index]; fine_amount = user->fine_amount(); break;
        case 2: user = &professor_user[index]; break;
        case 3: user = &librarian_user[index]; break;
        default: 
            cout << "\033[1;31mError: Invalid user type!\033[0m\n"; 
            return;
    }
    cin.ignore();
    cout << "\n\033[1;32mPlease enter your password: \033[0m";
    string passcode;
    cin>>passcode;
    // passcode = getPassword();

    // cout<<passcode; cout<<passcode.length()<<endl;

    if (user->match_password(passcode)) {
        int acc_index = search_account_index(roll_number);
        if (acc_index != -1) {
            account = &accounts[acc_index];
        }
        user_roll_number = roll_number;
        cout << "\n\033[1;32mLogin Successful! Redirecting...\033[0m\n";
        if (userType == 3) 
            librarian_menu();
        else 
            main_menu();
    } else {
        cout << "\n\033[1;31mIncorrect Password! Please try again.\033[0m\n";
        login_page();
    }
}

int search_book_index(string &ISBN){
    for(int i=0; i<books.size(); i++){
        if(books[i].match_ISBN(ISBN) == true){
            return i;
        }
    }
    return -1;
}

void check_available_books(){
    int available_book_count = 0;
    for(int i=0; i<books.size(); i++){
        if(books[i].availability == "1" || (books[i].availability == "3" && books[i].reserved_by_user == user->get_roll_number())){
            available_book_count ++;
            if (available_book_count == 1) {
                cout << "\033[1;34m-------------------------------------------------------------\n";
                cout << "                           Available Books                   \n";
                cout << "-------------------------------------------------------------\033[0m\n\n";
                cout << "\033[1;32mSl No. | Title                    | Author                 | Publisher                      | Year | ISBN          \n";
                cout << "---------------------------------------------------------------------------------------\033[0m\n";
            }
            cout << "\033[1;33m" << i + 1 << "\033[0m      | " 
            << books[i].get_title() << string(max(0, 26 - (int)books[i].get_title().length()), ' ') << "| " 
            << books[i].get_author() << string(max(0, 19 - (int)books[i].get_author().length()), ' ') << "| "  
            << books[i].get_publisher() << string(max(0, 18 - (int)books[i].get_publisher().length()), ' ') << "| "  
            << books[i].get_year() <<" | "
            << books[i].getISBN() << string(max(0, 14 - (int)books[i].getISBN().length()), ' ') << "| "  
            << endl;
            // cout<<books[i].title<<" | "<<books[i].author<<" | "<<books[i].publisher<<" | "<<books[i].year<<" | "<<books[i].ISBN<<endl;
        }
    }
    if(available_book_count == 0){
        cout << "\033[1;31m No books available.\033[0m";
    }
    cout<<"\n\n";
    return;
}

int search_user_index(string &roll_number){
    for(int i=0; i<student_user.size(); i++){
        if(student_user[i].match_roll_number(roll_number)){
            userType = 1; return i;
        }
    }
    for(int i=0; i<professor_user.size(); i++){
        if(professor_user[i].match_roll_number(roll_number)){
            userType = 2; return i;
        }
    }
    for(int i=0; i<librarian_user.size(); i++){
        if(librarian_user[i].match_roll_number(roll_number)){
            userType = 3; return i;
        }
    }
    return -1;
}
int search_account_index(string &roll_number){
    for(int i=0; i<accounts.size(); i++){
        if(accounts[i].match_roll_number(roll_number)){
            return i;
        }
    }
    return -1;
}

vector<Account> readCSVtoAccount(const string &filename){
    ifstream file(filename);
    vector<Account> data;
    if (!file) {
        cerr << "Error: Could not open file!" <<filename<< endl;
        return data; 
    }
    vector<string> row;
    string line;
    
    while (getline(file, line)) { 
        stringstream ss(line);
        string field;
        row.clear();
        
        while (getline(ss, field, ',')) { 
            row.push_back(field);
        }
        Account acc(row);
        data.push_back(acc);
    }
    file.close();
    return data;
}

vector<Student> readCSVtoStudent(const string &filename){
    ifstream file(filename);
    vector<Student> data;
    if (!file) {
        cerr << "Error: Could not open file!" <<filename<< endl;
        return data; 
    }
    vector<string> row;
    string line;
    while (getline(file, line)) { 
        stringstream ss(line);
        string field;
        row.clear();
        while (getline(ss, field, ',')) { 
            row.push_back(field);
        }
        Student st(row);
        data.push_back(st);
    }
    file.close();
    return data;
}

vector<Book> readCSVBook(const string &filename){
    ifstream file(filename);
    vector<Book> data;
    if (!file) {
        cerr << "Error: Could not open file!" <<filename<< endl;
        return data; 
    }
    vector<string> row;
    string line;
    while (getline(file, line)) { 
        stringstream ss(line);
        string field;
        row.clear();
        while (getline(ss, field, ',')) { 
            row.push_back(field);
        }
        Book book(row);
        data.push_back(book);
    }
    file.close();
    return data;
}

vector<Professor> readCSVtoProfessor(const string &filename){
    ifstream file(filename);
    vector<Professor> data;
    if (!file) {
        cerr << "Error: Could not open file!" <<filename<< endl;
        return data; 
    }
    vector<string> row;
    string line;
    while (getline(file, line)) { 
        stringstream ss(line);
        string field;
        row.clear();
        while (getline(ss, field, ',')) { 
            row.push_back(field);
        }
        Professor prof(row);
        data.push_back(prof);
    }
    file.close();
    return data;
}

vector<Librarian> readCSVtoLibrarian(const string &filename){
    ifstream file(filename);
    vector<Librarian> data;
    if (!file) {
        cerr << "Error: Could not open file!" <<filename<< endl;
        return data; 
    }
    vector<string> row;
    string line;
    while (getline(file, line)) { 
        stringstream ss(line);
        string field;
        row.clear();
        while (getline(ss, field, ',')) { 
            row.push_back(field);
        }
        Librarian libr(row);
        data.push_back(libr);
    }
    file.close();
    return data;
}

void writeBooksToCSV(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (const auto& book : books) {
        if(book.borrower == "removed_book")continue;
        file << book.title << "," 
            << book.author << "," 
            << book.publisher << "," 
            << book.year << "," 
            << book.ISBN << "," 
            << book.availability << "," 
            << book.borrower << "\n";
    }
    file.close();
}

void writeStudentsToCSV(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (const auto& student : student_user) {
        if(student.username == "")continue;
        file << student.username << "," 
            << student.password << "," 
            << student.fine << "," 
            << student.roll_number << "," 
            << student.user_type << "\n";
    }
    file.close();
}

void writeProfessorsToCSV(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (const auto& prof : professor_user) {
        if(prof.username == "")continue;
        file << prof.username << "," 
            << prof.password << "," 
            << prof.fine << "," 
            << prof.roll_number << "," 
            << prof.user_type << "\n";
    }
    file.close();
}

void writeAccountsToCSV(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }
    for (const auto& account : accounts) {
        file << account.roll_number << "," 
            << account.balance << "," << account.reserve_balance; 
        for(auto &issued_book: account.books_issued){
            file << "," << issued_book.first << "," << issued_book.second;
        }
        if(account.reserve_balance == 0){
            file <<"," << account.reserved_book.first << "," << account.reserved_book.second;
        }
        file << "\n";
    }
    file.close();
}

void writeLibrariansToCSV(const string& filename){
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (const auto& libr : librarian_user) {
        file << libr.username << "," 
            << libr.password << "," 
            << libr.roll_number << "," 
            << libr.user_type << "\n";
    }
    file.close();
}