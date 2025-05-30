#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Book {
private:
    string tit, aut, id;
    bool isAv;
public:
    Book(string t, string a, string i) {
        tit = t;
        aut = a;
        id = i;
        isAv = true;
    }
    string getTit() const { return tit; }
    string getAut() const { return aut; }
    string getId() const { return id; }
    bool getAv() const { return isAv; }
    void setAv(bool status) { isAv = status; }

    void printDetails() const {
        cout << "Title: " << tit
             << " ,Author: " << aut
             << " ,ISBN: " << id
             << " ,Available: " << (isAv ? "YES" : "NO") << endl;
    }
};

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
        if (book->getAv()) {
            borrowedBooks.push_back(book);
            book->setAv(false);
            cout << name << " borrowed " << book->getTit() << endl;
        } else {
            cout << "Book is not available.\n";
        }
    }

    void returnBook(Book* book) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == book) {
                borrowedBooks.erase(it);
                book->setAv(true);
                cout << name << " returned " << book->getTit() << endl;
                return;
            }
        }
        cout << "Book not found in borrowed list.\n";
    }

    void showBorrowedBooks() const {
        cout << name << "'s Borrowed Books:\n";
        for (const auto& book : borrowedBooks)
            book->printDetails();
    }
};

class Library {
private:
    vector<Book*> books;
    vector<User*> users;

public:
    void addBook(Book* book) { books.push_back(book); }

    void removeBook(Book* book) {
        books.erase(remove(books.begin(), books.end(), book), books.end());
    }

    void showBooks() const {
        for (const auto& book : books)
            book->printDetails();
    }

    Book* findBook(string search) {
        for (auto& book : books) {
            if (book->getTit() == search || book->getId() == search)
                return book;
        }
        return nullptr;
    }

    void registerUser(User* user) { users.push_back(user); }

    User* findUser(int id) {
        for (auto& user : users) {
            if (user->getUserId() == id) return user;
        }
        return nullptr;
    }
};

int main() {
    Library lib;
    User* user1 = new User(1, "Ahmed");
    lib.registerUser(user1);

    int choice;
    string title, author, isbn, search;
    int userId;

    auto getUserAndBook = [&](User*& user, Book*& book, bool needBook) {
        cout << "Enter your User ID: ";
        cin >> userId;
        user = lib.findUser(userId);
        if (!user) {
            cout << "User not found.\n";
            return false;
        }
        if (needBook) {
            cout << "Enter book title or ISBN: ";
            cin >> search;
            book = lib.findBook(search);
            if (!book) {
                cout << "Book not found.\n";
                return false;
            }
        }
        return true;
    };

    do {
        cout << "\n--- Library Menu ---\n";
        cout << "1. Add Book\n2. Show Books\n3. Borrow Book\n4. Return Book\n5. Show My Books\n0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Title, Author, ISBN:\n";
            cin >> title >> author >> isbn;
            lib.addBook(new Book(title, author, isbn));
            break;

        case 2:
            lib.showBooks();
            break;

        case 3: {
            User* user = nullptr; Book* book = nullptr;
            if (getUserAndBook(user, book, true))
                user->borrowBook(book);
            break;
        }

        case 4: {
            User* user = nullptr; Book* book = nullptr;
            if (getUserAndBook(user, book, true))
                user->returnBook(book);
            break;
        }

        case 5: {
            User* user = nullptr;
            Book* dummy = nullptr;
            if (getUserAndBook(user, dummy, false))
                user->showBorrowedBooks();
            break;
        }
        }
    } while (choice != 0);

    return 0;
}

