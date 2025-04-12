# 📚 CS253: Library Management System

This project implements a **Library Management System** in C++ using **Object-Oriented Programming (OOP)** principles. The system supports multiple user roles with distinct functionalities. The main implementation can be found in [`main.cpp`](/main.cpp). All functionalities mentioned in the [Problem Statement](/Problem_statement.pdf) have been implemented accordingly.

---

## 📄 Features & Functionalities

### 🔑 **User Roles & Access**
- 👨‍🎓 **Students & Professors**
  - Must **log in** using their **Roll/PF Number** and password.
  - Professors **Cannot register themselves** to prevent unauthorized accounts by studnets.
  - Can **borrow, return, and reserve books**.
  - **Borrowing Limits:**
    - Students: **15 days**
    - Professors: **30 days**
  - **Reservations:** Books can be reserved **only if available** and for **a maximum of 2 days**.
  - **Fines are calculated in real-time** based on the overdue period.

- 👨‍🏫 **Librarians**
  - Can **add, update, or remove books** from the library.
  - Can **register or remove users**.
  - Can **update user information** (change username/password).
  
### 🛠️ **System Features**
- 🔐 **Secure Authentication** – Users must log in with **Roll/PF Number and password**.
- 📚 **Book Management** – Search, borrow, return, and reserve books.
- 📊 **Fine Calculation** – Automatically calculates overdue fines.
- 👤 **Role-Based Permissions** – Different access levels for Students, Professors, and Librarians.
- 🏛️ **CSV Database System** – Persistent storage for all records.

---

### 🔑 User Authentication and Features

- Students can register themselves, but professors cannot register themselves to prevent  **unauthorized** accounts. This ensures that students do not register as professors to avail extra benefits.

- Users are automatically identified as students, professors, or librarians based on their roll/PF number and password.

---

## 📂 Database Files
The system uses CSV files as a database to store user and book records:

### 📚 `acc.csv` – User Account Details
```plaintext
[roll/PF number, current_book_balance, reserve_balance, issued_books (with timestamps), reserved_books (with timestamps)]
```
- **User Types:**  
  - `[1]` → Student  
  - `[2]` → Professor  
  - `[3]` → Librarian  

### 📚 `books.csv` – Book Details
```plaintext
[book title, author, publisher, year, ISBN number, availability, borrowed/reserved by user]
```

### 📚 `student_user.csv` & `professor_user.csv` – User Records
```plaintext
[username, password, fine, roll/PF number, user type]
```

### 📚 `librarian_user.csv` – Librarian Records
```plaintext
[username, password, PF number, user type]
```

---

## 🚀 Running the System
To compile and run the program, execute the following commands in the terminal:

```sh
g++ main.cpp -o main
./main
```

---

## 🛏️ User Menus & Navigation

### 📲 **Login & Registration Page**
```plaintext
===============================================================================
                      WELCOME TO LIBRARY MANAGEMENT SYSTEM                     
===============================================================================
[1] Log In    [2] Register    [3] Exit
===============================================================================
   Please enter your choice:
```
- **Registration is ONLY for Students** – Professors and Librarians must be added manually.
- **Users are automatically identified** based on their Roll/PF Number and password.

---

### 📖 **Student & Professor Main Menu**
```plaintext
==================================================
                    MAIN MENU                    
==================================================
Hello, [USERNAME]!
[0] Change Username or Password
[1] Manage Fines
[2] Check Book Availability
[3] Reserve a Book
[4] Unreserve a Book
[5] Borrow a Book
[6] Return a Book
[7] Check Issued/Reserved Books
[8] Check Books by Author
[9] Sign Out
Enter your choice:
```
- **Reservations last for only 2 days** – No other user can borrow the book during this time.
- **Borrow Limits:** Students (**15 days**) | Professors (**30 days**)
- **Fine Calculation is Real-Time** – Users must return books on time.

---

### 📚 **Librarian Main Menu**
```plaintext
[0]  Change Username or Password
[1]  Add a new book to the library
[2]  Remove a book from the library
[3]  Update book details
[4]  Register a new user
[5]  Remove a user
[6]  Sign out
```
- **Librarians can add, update, and remove books**.
- **User management (registering/removing) is handled by the librarian**.
