
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Book class
class Book {
private:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

public:
    Book(string t, string a, string isbn) {
        title = t;
        author = a;
        ISBN = isbn;
        isAvailable = true;
    }

    // Getters and Setters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    bool getAvailability() const { return isAvailable; }

    void setAvailability(bool status) { isAvailable = status; }

    void printDetails() const {
        cout << "Title: " << title << ", Author: " << author
             << ", ISBN: " << ISBN << ", Available: "
             << (isAvailable ? "Yes" : "No") << endl;
    }
};

// User class
class User {
private:
    int userId;
    string name;
    vector<Book*> borrowedBooks;

public:
    User(int id, string n) : userId(id), name(n) {}

    int getUserId() const { return userId; }
    string getName() const { return name; }

    void borrowBook(Book* book) {
        if (book->getAvailability()) {
            borrowedBooks.push_back(book);
            book->setAvailability(false);
            cout << name << " borrowed " << book->getTitle() << endl;
        } else {
            cout << "Book is not available.\n";
        }
    }

    void returnBook(Book* book) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == book) {
                borrowedBooks.erase(it);
                book->setAvailability(true);
                cout << name << " returned " << book->getTitle() << endl;
                return;
            }
        }
        cout << "Book not found in borrowed list.\n";
    }

    void showBorrowedBooks() const {
        cout << name << "'s Borrowed Books:\n";
        for (const auto& book : borrowedBooks) {
            book->printDetails();
        }
    }
};

// Library class
class Library {
private:
    vector<Book*> books;
    vector<User*> users;

public:
    void addBook(Book* book) {
        books.push_back(book);
    }

    void removeBook(Book* book) {
        books.erase(remove(books.begin(), books.end(), book), books.end());
    }

    void showBooks() const {
        for (const auto& book : books) {
            book->printDetails();
        }
    }

    Book* findBook(string search) {
        for (auto& book : books) {
            if (book->getTitle() == search || book->getISBN() == search) {
                return book;
            }
        }
        return nullptr;
    }

    void registerUser(User* user) {
        users.push_back(user);
    }

    User* findUser(int id) {
        for (auto& user : users) {
            if (user->getUserId() == id) return user;
        }
        return nullptr;
    }
};

// Main function
int main() {
    Library lib;
    User* user1 = new User(1, "Ahmed");
    lib.registerUser(user1);

    int choice;
    string title, author, isbn, search;
    int userId;

    do {
        cout << "\n--- Library Menu ---\n";
        cout << "1. Add Book\n2. Show Books\n3. Borrow Book\n4. Return Book\n5. Show My Books\n0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter Title, Author, ISBN:\n";
            cin >> title >> author >> isbn;
            Book* book = new Book(title, author, isbn);
            lib.addBook(book);
            break;
        }
        case 2:
            lib.showBooks();
            break;
        case 3: {
            cout << "Enter your User ID: ";
            cin >> userId;
            cout << "Enter book title or ISBN to borrow: ";
            cin >> search;
            User* user = lib.findUser(userId);
            Book* book = lib.findBook(search);
            if (user && book) user->borrowBook(book);
            else cout << "User or Book not found.\n";
            break;
        }
        case 4: {
            cout << "Enter your User ID: ";
            cin >> userId;
            cout << "Enter book title or ISBN to return: ";
            cin >> search;
            User* user = lib.findUser(userId);
            Book* book = lib.findBook(search);
            if (user && book) user->returnBook(book);
            else cout << "User or Book not found.\n";
            break;
        }
        case 5: {
            cout << "Enter your User ID: ";
            cin >> userId;
            User* user = lib.findUser(userId);
            if (user) user->showBorrowedBooks();
            else cout << "User not found.\n";
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
