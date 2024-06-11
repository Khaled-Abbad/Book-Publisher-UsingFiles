/*

                                                      Book Publisher Management System
                                                                  Members
                                                    Khaled Salem Abbad     -   222453448
                                                    Hamzah Eyad Mohammed   -   222453516
                                                    Basel Ahmed            -   222453505
                                                    Mohammad Asad AbuYahya -   222453463
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <fstream>
using namespace std;

struct Book
{
    string id;
    string title;
    string numberOfPages;
    string subject;
    string dateOfPub;
    string authorName;
};

struct Author
{
    string id;
    string name;
    string phone;
    string address;
    string job_title;
    int numberOfBooksOfAuthor = 0;
    Book listOfBooks[100];
};

Book BookArray[100];
Author AuthorArray[100];

/// convert string to Number if any , else ask for number
void isNumber(string *number)
{
    string tempNumber = *number;
    bool isTrue = false;
    if (tempNumber == " ")
    {
        tempNumber = "a";
    }
    do
    {
        for (int i = 0; i < tempNumber.length(); i++)
        {
            if (!('0' <= tempNumber.at(i) && tempNumber.at(i) <= '9'))
            {
                isTrue = false;
                cout << "Enter a Correct Number \n";
                cin >> tempNumber;
                isNumber(&tempNumber);
            }
            isTrue = true;
        }
    } while (!isTrue);
    *number = tempNumber;
}

int readBooksFromFile()
{
    string line;
    ifstream myFile;
    myFile.open("Book.txt");
    int counterOfBooks = 0;
    while (getline(myFile, line))
    {
        BookArray[counterOfBooks].id = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        BookArray[counterOfBooks].title = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        BookArray[counterOfBooks].authorName = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        BookArray[counterOfBooks].numberOfPages = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        BookArray[counterOfBooks].subject = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        BookArray[counterOfBooks].dateOfPub = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        counterOfBooks++;
    }
    myFile.close();
    return counterOfBooks;
}

int readAuthorFromFile()
{
    string line;
    ifstream myFile;
    myFile.open("Author.txt");
    int counterOfAuthor = 0;
    while (getline(myFile, line))
    {
        AuthorArray[counterOfAuthor].id = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        AuthorArray[counterOfAuthor].name = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        AuthorArray[counterOfAuthor].job_title = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        AuthorArray[counterOfAuthor].phone = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        AuthorArray[counterOfAuthor].address = line.substr(0, line.find('#'));
        line.erase(0, line.find('#') + 1);
        AuthorArray[counterOfAuthor].numberOfBooksOfAuthor = stoi(line.substr(0, line.find('#')));
        line.erase(0, line.find("#[") + 2);
        for (int j = 0; j < AuthorArray[counterOfAuthor].numberOfBooksOfAuthor; j++)
        {
            AuthorArray[counterOfAuthor].listOfBooks[j].id = line.substr(0, line.find('#'));
            line.erase(0, line.find('#') + 1);
            AuthorArray[counterOfAuthor].listOfBooks[j].title = line.substr(0, line.find('#'));
            line.erase(0, line.find('#') + 1);
            AuthorArray[counterOfAuthor].listOfBooks[j].authorName = AuthorArray[counterOfAuthor].name;
            line.erase(0, line.find('#') + 1);
            AuthorArray[counterOfAuthor].listOfBooks[j].numberOfPages = line.substr(0, line.find('#'));
            line.erase(0, line.find('#') + 1);
            AuthorArray[counterOfAuthor].listOfBooks[j].subject = line.substr(0, line.find('#'));
            line.erase(0, line.find('#') + 1);
            AuthorArray[counterOfAuthor].listOfBooks[j].dateOfPub = line.substr(0, line.find('#'));
            line.erase(0, line.find("#]") + 2);
        }
        line.erase(0, line.find(']') + 1);
        counterOfAuthor++;
    }
    myFile.close();
    return counterOfAuthor;
}

void writeBookToFile(int counterOfBooks)
{
    ofstream file;
    file.open("Book.txt");

    for (int i = 0; i < counterOfBooks; i++)
    {
        file << BookArray[i].id << "#" << BookArray[i].title << "#" << BookArray[i].authorName << "#" << BookArray[i].numberOfPages << "#" << BookArray[i].subject
             << "#" << BookArray[i].dateOfPub << "#" << endl;
    }
    file.close();
}

void writeAuthorToFile(int counterOfAuthor)
{
    ofstream file;
    file.open("Author.txt");

    for (int i = 0; i < counterOfAuthor; i++)
    {
        // file << BookArray[i].id <<"#"<< BookArray[i].title <<"#"<< BookArray[i].authorName <<"#"<< BookArray[i].numberOfPages <<"#"<< BookArray[i].subject <<"#"<< BookArray[i].dateOfPub <<"#"<<endl;
        file << AuthorArray[i].id << "#" << AuthorArray[i].name << "#" << AuthorArray[i].job_title << "#" << AuthorArray[i].phone << "#" << AuthorArray[i].address
             << "#" << AuthorArray[i].numberOfBooksOfAuthor << "#[";
        for (int j = 0; j < AuthorArray[i].numberOfBooksOfAuthor; j++)
        {
            file << AuthorArray[i].listOfBooks[j].id << "#" << AuthorArray[i].listOfBooks[j].title << "#" << AuthorArray[i].listOfBooks[j].numberOfPages << "#" << AuthorArray[i].listOfBooks[j].subject << "#" << AuthorArray[i].listOfBooks[j].dateOfPub << "#";
        }
        file << "]\n";
    }
    file.close();
}

class BookFunctions
{
public:
    /// Show All Books until [counterOfBooks]
    void showAllBooks(int counterOfBooks)
    {
        if (counterOfBooks == 0)
        {
            cout << "------------------- No Books yet -------------------\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            cin.get();
            system("cls");
        }
        else
        {
            for (int i = 0; i < counterOfBooks; i++)
            {

                if (i == 0)
                {
                    cout << "\n--------------------All Books-----------------------\n";
                }
                else
                {
                    cout << "\n\n";
                }
                cout << "                  Book Number " << i + 1 << "                  \n";
                cout << "Book id: " << BookArray[i].id << endl;
                cout << "Book Title: " << BookArray[i].title << endl;

                if (BookArray[i].authorName == "")
                {
                    cout << "Author Name: Not Assign Yet" << endl;
                }
                else
                {
                    cout << "Author Name: " << BookArray[i].authorName << endl;
                }
                cout << "Number of Book Pages: " << BookArray[i].numberOfPages << endl;
                cout << "Book subject: " << BookArray[i].subject << endl;
                cout << "Publication Date: " << BookArray[i].dateOfPub << endl;
                if (i == counterOfBooks - 1)
                {
                    cout << "\n-------------------End of List----------------------\n";
                    cout << "Press Enter to Go to Menu";
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "\nPress Enter to continue";
                    cin.ignore();
                    cin.get();
                }
                // system("cls");
            }
        }
        system("cls");
    }

    /// search if you have book id before
    bool isNew(string id, int counterOfBooks)
    {
        for (int i = 0; i < counterOfBooks; i++)
        {
            if (BookArray[i].id == id)
            {

                cout << "This Id is already exist\n";
                cout << "\nPress Enter to continue";
                cin.ignore();
                cin.get();
                system("cls");
                return false;
            }
        }
        return true;
    }

    /// add Book to the Array
    void addBook(int &counterOfBooks)
    {
        cout << "\n- Enter book Details -\n";

        string id;
        cout << "Book Id: ";
        cin.ignore();
        getline(cin, id);

        isNumber(&id);

        if (!isNew(id, counterOfBooks))
        {
            return;
        }

        BookArray[counterOfBooks].id = id;

        cout << "Book Title: ";
        // cin.ignore();
        getline(cin, BookArray[counterOfBooks].title);

        cout << "Enter Number of Book Pages: ";
        cin >> BookArray[counterOfBooks].numberOfPages;
        isNumber(&BookArray[counterOfBooks].numberOfPages);

        cout << "Enter Book subject: ";
        cin.ignore();
        getline(cin, BookArray[counterOfBooks].subject);

        cout << "Enter Publication Date: ";
        // cin.ignore(); if you run it will ignore first char of date
        getline(cin, BookArray[counterOfBooks].dateOfPub);
        system("cls");
        counterOfBooks++;
        cout << "\n\n\n\n\n\t\t\t\t Book added Successfuly\n\n\t\t\t\tPress Enter to continue.";
        cin.get();
        writeBookToFile(counterOfBooks);
    }

    /// Get Book Number and check the range
    int getBookNumber(int counterOfBooks)
    {
        if (counterOfBooks == 0)
        {
            cout << "------------------- No Books yet -------------------\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            cin.get();
            system("cls");
            return -1;
        }

        string bookNumber;
        cout << "\n--------------------All Books-----------------------\n";
        for (int i = 0; i < counterOfBooks; i++)
        {
            cout << i + 1 << ". Book title: " << BookArray[i].title << endl;
        }

        cout << "\n\nChoose a Book, or press 0 to exite: ";
        int bookNumberInt;
        do
        {
            cin >> bookNumber;
            isNumber(&bookNumber);
            bookNumberInt = stoi(bookNumber);
        } while (!(0 <= bookNumberInt && bookNumberInt <= counterOfBooks));
        return bookNumberInt - 1;
    }

    /// update a book
    void updateBook(int &counterOfBooks, int counterOfAuthors)
    {
        int bookNumberInt = getBookNumber(counterOfBooks);
        if (bookNumberInt == -1)
            return;
        char Choice;
        do
        {
            system("cls");
            cout << "What do you  want to update" << endl;
            cout << "1- Book id: " << endl;
            cout << "2- Book Title: " << endl;
            cout << "3- Number of Book Pages: " << endl;
            cout << "4- Book subject: " << endl;
            cout << "5- Publication Date: " << endl;
            cout << "6- Exit" << endl;
            cout << "Enter your choice: ";
            cin >> Choice;
            system("cls");

            string newId;
            switch (Choice)
            {
            case '1':
                cout << "Book Id: ";
                cin.ignore();
                getline(cin, newId);
                isNumber(&newId);

                if (!isNew(newId, counterOfBooks))
                {
                    return;
                }
                BookArray[bookNumberInt].id = newId;
                cin.get();

                break;
            case '3':
                cout << "Number of Book Pages: ";
                cin >> BookArray[bookNumberInt].numberOfPages;
                isNumber(&BookArray[bookNumberInt].numberOfPages);
                break;
            case '4':
                cout << "Book subject: ";
                cin >> BookArray[bookNumberInt].subject;
                break;
            case '5':
                cout << "Publication Date: ";
                cin >> BookArray[bookNumberInt].dateOfPub;
                break;
            case '6':
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
            case '2':
                cout << "Book Title: ";
                string newTitle;
                getline(cin , newTitle);
                for (int i = 0; i < counterOfAuthors; i++)
                {
                    if (AuthorArray[i].name == AuthorArray[bookNumberInt].name)
                    {
                        AuthorArray[i].listOfBooks[bookNumberInt].title = newTitle;
                    }
                }
                BookArray[bookNumberInt].title = newTitle;
                break;
            }
        } while (Choice != '6');
        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t Book Updated Successfuly\n\n\t\t\t\tPress Enter to continue.";
        cin.get();
        writeBookToFile(counterOfBooks);
    }

    /// remove a book
    void RemoveABook(int &counterOfBooks)
    {
        int bookNumberInt = getBookNumber(counterOfBooks);
        if (bookNumberInt == -1)
            return;
        BookArray[bookNumberInt] = Book();

        for (int i = bookNumberInt; i < counterOfBooks; i++)
        {
            BookArray[i] = BookArray[i + 1];
        }
        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t Book Deleted Successfuly\n\n\t\t\t\tPress Enter to continue.";
        cin.get();
        counterOfBooks--;
        writeBookToFile(counterOfBooks);
    }

    /// delete all books
    void DeleteAllBooks(int &counterOfBooks)
    {
        cout << "If you want to delete all Book press 1 , else Enter Anything else \n";
        char choice;
        cin >> choice;
        if (choice == '1')
        {
            for (int i = 0; i < counterOfBooks; i++)
            {
                BookArray[i] = Book();
            }
            cout << "\n\n\n\n\n\t\t\t\tAll Book Deleted Successfully\n";
            Sleep(1000);
            system("cls");
        }
        system("cls");
        cin.get();
        counterOfBooks = 0;
        writeBookToFile(counterOfBooks);
    }

};

class AuthorFunctions
{
public:
    /// show Author to the Array
    void showAllAuthors(int counterOfAuthors)
    {
        if (counterOfAuthors == 0)
        {
            cout << "------------------- No Authors yet -------------------\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            cin.get();
            system("cls");
        }
        else
        {
            for (int i = 0; i < counterOfAuthors; i++)
            {
                if (i == 0)
                {
                    cout << "\n--------------------All Authors-----------------------\n";
                }
                else
                {
                    cout << "\n\n";
                }
                cout << "                  Author Number " << i + 1 << "                  \n";
                cout << "Author id: " << AuthorArray[i].id << endl;
                cout << "Author name: " << AuthorArray[i].name << endl;
                cout << "Author phone: " << AuthorArray[i].phone << endl;
                cout << "Author Address: " << AuthorArray[i].address << endl;
                cout << "Author JobTitle: " << AuthorArray[i].job_title << endl;
                if (AuthorArray[i].numberOfBooksOfAuthor > 0)
                {
                    cout << "Author Books Title: " << endl;
                    for (int j = 0; j < AuthorArray[i].numberOfBooksOfAuthor; j++)
                    {
                        cout << j + 1 << ". title : ";
                        cout << AuthorArray[i].listOfBooks[j].title << endl;
                    }
                }
                else
                {
                    cout << "This Author don't have books yet" << endl;
                }
                if (i == counterOfAuthors - 1)
                {
                    cout << "-------------------End of List----------------------\n";
                    cout << "Press Enter to Go to Menu";
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "\nPress Enter to continue";
                    cin.ignore();
                    cin.get();
                }
                // system("cls");
            }
        }
        system("cls");
    }

    /// search if you have book id before
    bool isNew(string id, int counterOfAuthors)
    {
        for (int i = 0; i < counterOfAuthors; i++)
        {
            if (AuthorArray[i].id == id)
            {

                cout << "This Id is already exist\n";
                cout << "\nPress Enter to continue";
                cin.ignore();
                cin.get();
                system("cls");
                return false;
            }
        }
        return true;
    }

    /// add a new Author
    void addAuthor(int &counterOfAuthors)
    {
        cout << "\n- Enter Author Details -\n";
        string id;
        cout << "Author Id: ";
        cin.ignore();
        getline(cin, id);

        isNumber(&id);

        if (!isNew(id, counterOfAuthors))
        {
            return;
        }

        AuthorArray[counterOfAuthors].id = id;

        cout << "Author name: ";
        
        getline(cin, AuthorArray[counterOfAuthors].name);

        cout << "Author phone: ";
        cin >> AuthorArray[counterOfAuthors].phone;
        isNumber(&AuthorArray[counterOfAuthors].phone);

        cout << "Author Address: ";
        cin.ignore();
        getline(cin, AuthorArray[counterOfAuthors].address);

        cout << "Author JobTitle: ";
        getline(cin, AuthorArray[counterOfAuthors].job_title);

        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t Author Added Successfuly\n\n\t\t\t\tPress Enter to continue.";
        cin.ignore();
        cin.get();
        counterOfAuthors++;
        writeAuthorToFile(counterOfAuthors);
    }

    int getAuthorNumber(int counterOfAuthors)
    {
        if (counterOfAuthors == 0)
        {
            cout << "------------------- No Authors yet -------------------\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            cin.get();
            system("cls");
            return -1;
        }
        string authorNumber;
        cout << "\n--------------------All Authors-----------------------\n";
        for (int i = 0; i < counterOfAuthors; i++)
        {
            cout << i + 1 << ". Author Name: " << AuthorArray[i].name << endl;
        }
        cout << "\n\nChoose an Author ";
        int authorNumberInt;
        do
        {
            cin >> authorNumber;
            isNumber(&authorNumber);
            authorNumberInt = stoi(authorNumber);
            if (authorNumberInt == 0)
                return -1;
        } while (!(0 < authorNumberInt && authorNumberInt <= counterOfAuthors));
        return authorNumberInt - 1;
    }

    /// Assign Books To An Author
    void AssignBooksToAuthor(int counterOfAuthors, int counterOfBooks)
    {

        int authorNumberInt = getAuthorNumber(counterOfAuthors);
        if (authorNumberInt == -1)
            return;

        system("cls");
        cout << "\n--------------------All Books-----------------------\n";
        for (int i = 0; i < counterOfBooks; i++)
        {
            cout << i + 1 << ". Book Title: " << BookArray[i].title << endl;
        }
        string assigns;

        cout << "\n\nEnter Number of books you want to Assign ";
        int assignsInt;
        do
        {
            cin >> assigns;
            isNumber(&assigns);
            assignsInt = stoi(assigns);
        } while (!(0 <= assignsInt && assignsInt <= counterOfBooks));

        string Books[assignsInt];
        for (int i = 0; i < assignsInt; i++)
        {
            cout << "Choose Books Number ";
            cin >> Books[i];
            isNumber(&Books[i]);
            int BookNumber = stoi(Books[i]);
            BookNumber--;
            BookArray[BookNumber].authorName = AuthorArray[authorNumberInt].name;
            AuthorArray[authorNumberInt].listOfBooks[AuthorArray[authorNumberInt].numberOfBooksOfAuthor] = BookArray[BookNumber];
            AuthorArray[authorNumberInt].numberOfBooksOfAuthor++;
        }
        cout << "\t\t\t\t Press Enter to continue  \n";
        cin.ignore();
        cin.get();
        writeAuthorToFile(counterOfAuthors);
    }

    // Remove Books from an Author
    void RemoveAuthorBooks(int &counterOfAuthors)
    {
        int authorNumberInt = getAuthorNumber(counterOfAuthors);
        if (authorNumberInt == -1)
            return;

        for (int i = 0; i < AuthorArray[authorNumberInt].numberOfBooksOfAuthor - 1; i++)
        {
            cout << i + 1 << ". Book Title: " << AuthorArray[authorNumberInt].listOfBooks[i].title << endl;
        }

        string remove;

        cout << "Enter Number of books you want to Remove ";
        cin >> remove;
        isNumber(&remove);
        int removeInt = stoi(remove);
        string Books[removeInt];

        for (int i = 0; i < removeInt; i++)
        {
            cout << "Choose Books Number ";
            cin >> Books[i];
            isNumber(&Books[i]);
            int BookNumber = stoi(Books[i]);
            BookNumber--;
            BookArray[BookNumber].authorName = "";
            AuthorArray[authorNumberInt].listOfBooks[AuthorArray[authorNumberInt].numberOfBooksOfAuthor] = {};
            AuthorArray[authorNumberInt].numberOfBooksOfAuthor--;
        }
        cout << "\t\t\t\t Press Enter to continue  \n";
        cin.ignore();
        cin.get();

        system("cls");
        writeAuthorToFile(counterOfAuthors);
    }

    /// update an Author
    void updateAuthor(int &counterOfAuthors, int counterOfBooks)
    {
        int authorNumberInt = getAuthorNumber(counterOfAuthors);
        if (authorNumberInt == -1)
            return;

        char Choice;
        do
        {
            system("cls");
            cout << "What do you  want to update" << endl;
            cout << "1- Author id: " << endl;
            cout << "2- Author Name: " << endl;
            cout << "3- Author Phone: " << endl;
            cout << "4- Number of Address: " << endl;
            cout << "5- Author Job title: " << endl;
            cout << "6- Exit" << endl;
            cout << "Enter your choice: ";
            cin >> Choice;
            system("cls");

            string newId;

            switch (Choice)
            {
            case '1':
                cout << "Author Id: ";
                cin.ignore();
                getline(cin, newId);
                isNumber(&newId);

                if (!isNew(newId, counterOfAuthors))
                {
                    return;
                }
                AuthorArray[authorNumberInt].id = newId;
                cin.get();
                break;
            case '3':
                cout << "Author Phone: ";
                cin >> AuthorArray[authorNumberInt].phone;
                break;
            case '4':
                cout << "Author Address: ";
                cin >> AuthorArray[authorNumberInt].address;
                break;
            case '5':
                cout << "Author Job title: ";
                cin >> AuthorArray[authorNumberInt].job_title;
                break;
            case '6':
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
            case '2':
                cout << "Author Name: ";
                string newName;
                getline(cin,newName);
                for (int i = 0; i < counterOfBooks; i++)
                {
                    if (BookArray[i].authorName == AuthorArray[authorNumberInt].name)
                    {
                        BookArray[i].authorName = newName;
                    }
                }
                AuthorArray[authorNumberInt].name = newName;
                break;
            }
        } while (Choice != '6');
        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t Author Updated Successfuly\n\n\t\t\t\tPress Enter to continue.";
        cin.get();
        writeAuthorToFile(counterOfAuthors);
    }

    /// remove an Author
    void RemoveAnAuthor(int &counterOfAuthors)
    {
        if (counterOfAuthors == 0)
        {
            cout << "------------------- No Authors yet -------------------\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            cin.get();
            system("cls");
            return;
        }

        string authorNumber;
        cout << "\n--------------------All Authors-----------------------\n";
        for (int i = 0; i < counterOfAuthors; i++)
        {
            cout << i + 1 << ". Author Name: " << AuthorArray[i].name << endl;
        }

        cout << "\n\nChoose an Author ";
        cin >> authorNumber;
        isNumber(&authorNumber);
        int authorNumberInt = stoi(authorNumber);
        authorNumberInt--;

        AuthorArray[authorNumberInt] = Author();
        for (int i = authorNumberInt; i < counterOfAuthors; i++)
        {
            AuthorArray[i] = AuthorArray[i + 1];
        }
        counterOfAuthors--;
        writeAuthorToFile(counterOfAuthors);
    }

    /// delete all authors
    void DeleteAllAuthors(int &counterOfAuthors)
    {
        cout << "If you want to delete all Author press 1, else Enter Anything else\n";
        char choice;
        cin >> choice;
        if (choice == '1')
        {
            for (int i = 0; i < counterOfAuthors; i++)
            {
                AuthorArray[i] = Author();
            }
            cout << "\n\n\n\n\n\t\t\t\tAll Author Deleted Successfully\n";
            Sleep(2000);
            system("cls");
        }
        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t All Authors Deleted Successfuly\n\n\t\t\t\tPress Enter to continue.";
        cin.get();
        counterOfAuthors = 0;
        writeAuthorToFile(counterOfAuthors);
    }
};

void showBook(int i)
{
    cout << "Book id: " << BookArray[i].id << endl;
    cout << "Book Title: " << BookArray[i].title << endl;
    if (BookArray[i].authorName == "")
    {
        cout << "Author Name: Not Assign Yet" << endl;
    }
    else
    {
        cout << "Author Name: " << BookArray[i].authorName << endl;
    }
    cout << "Number of Book Pages: " << BookArray[i].numberOfPages << endl;
    cout << "Book subject: " << BookArray[i].subject << endl;
    cout << "Publication Date: " << BookArray[i].dateOfPub << endl;
}

void searchForBook(int counterOfBooks)
{
    int intChoice;
    do
    {
        system("cls");
        cout << "choses what you want to search about" << endl;
        cout << "1- Book id: " << endl;
        cout << "2- Book Title: " << endl;
        cout << "3- Book Author: " << endl;
        cout << "4- Number of Book Pages: " << endl;
        cout << "5- Book subject: " << endl;
        cout << "6- Publication Date: " << endl;
        cout << "7- Exit" << endl;
        cout << "Enter your choice: ";

        string information;
        bool isMore = false;
        bool isFound = false;

        string choice;
        cout << "Enter your choice: ";
        cin >> choice;
        isNumber(&choice);
        intChoice = stoi(choice);
        switch (intChoice)
        {
        case 1:
            system("cls");
            cout << "Enter Id You want to search for: ";
            cin.ignore();
            getline(cin, information);
            isNumber(&information);
            system("cls");
            for (int i = 0; i < counterOfBooks; i++)
            {
                if (BookArray[i].id == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;

                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 2:
            system("cls");
            cout << "Enter Book Title You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");
            for (int i = 0; i < counterOfBooks; i++)
            {
                if (BookArray[i].title == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 3:
            system("cls");
            cout << "Enter Author You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");
            for (int i = 0; i < counterOfBooks; i++)
            {
                if (BookArray[i].authorName == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 4:
            system("cls");
            cout << "Enter subject You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");
            for (int i = 0; i < counterOfBooks; i++)
            {
                if (BookArray[i].subject == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 5:
            system("cls");
            cout << "Enter numberOfPages You want to search for: ";
            cin.ignore();
            getline(cin, information);
            isNumber(&information);
            system("cls");
            for (int i = 0; i < counterOfBooks; i++)
            {
                if (BookArray[i].numberOfPages == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 6:
            system("cls");
            cout << "Enter date of publication You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");
            for (int i = 0; i < counterOfBooks; i++)
            {
                if (BookArray[i].dateOfPub == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 7:
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (intChoice != 7);
};

void showAuthor(int i)
{
    cout << "Author Name: " << AuthorArray[i].name << endl;
    cout << "Author Phone: " << AuthorArray[i].phone << endl;
    cout << "Author Address: " << AuthorArray[i].address << endl;
    cout << "Author Job title: " << AuthorArray[i].job_title << endl;
    cout << "Author Number of Books: " << AuthorArray[i].numberOfBooksOfAuthor << endl;
    cout << "Author Books: " << endl;
    if (AuthorArray[i].numberOfBooksOfAuthor > 0)
    {
        cout << "Author Books Title: " << endl;
        for (int j = 0; j < AuthorArray[i].numberOfBooksOfAuthor; j++)
        {
            cout << j + 1 << ". title : ";
            cout << AuthorArray[i].listOfBooks[j].title << endl;
        }
    }
    else
    {
        cout << "This Author don't have books yet" << endl;
    }
}

void searchForAuthor(int counterOfAuthors, int counterOfBooks)
{
    int intChoice;
    do
    {
        system("cls");
        cout << "choses what you want to search about" << endl;
        cout << "1- Author id: " << endl;
        cout << "2- Author Name: " << endl;
        cout << "3- Author Phone: " << endl;
        cout << "4- Number of Address: " << endl;
        cout << "5- Author Job title: " << endl;
        cout << "6- Author Books" << endl;
        cout << "7- Exit" << endl;
        string information;
        bool isMore = false;
        bool isFound = false;
        string choice;
        cout << "Enter your choice: ";
        cin >> choice;
        isNumber(&choice);
        intChoice = stoi(choice);
        switch (intChoice)
        {
        case 1:
            system("cls");
            cout << "Enter Id You want to search for: ";
            cin.ignore();
            getline(cin, information);
            isNumber(&information);
            system("cls");
            for (int i = 0; i < counterOfAuthors; i++)
            {
                if (AuthorArray[i].id == information)
                {
                    isFound = true;
                    showAuthor(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 2:
            system("cls");
            cout << "Enter Author Name You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");
            for (int i = 0; i < counterOfAuthors; i++)
            {
                if (AuthorArray[i].name == information)
                {
                    isFound = true;
                    showAuthor(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 3:
            system("cls");
            cout << "Enter Phone You want to search for: ";
            cin.ignore();
            getline(cin, information);
            isNumber(&information);
            system("cls");
            for (int i = 0; i < counterOfAuthors; i++)
            {
                if (AuthorArray[i].phone == information)
                {
                    isFound = true;
                    showAuthor(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 4:
            system("cls");
            cout << "Enter Address You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");
            for (int i = 0; i < counterOfAuthors; i++)
            {
                if (AuthorArray[i].address == information)
                {
                    isFound = true;
                    showAuthor(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Founded  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 5:
            system("cls");
            cout << "Enter Job title You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");
            for (int i = 0; i < counterOfAuthors; i++)
            {
                if (AuthorArray[i].job_title == information)
                {
                    isFound = true;
                    showAuthor(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    // cin.ignore();
                    cin.get();
                }
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Press Enter Not Founded";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                // cin.ignore();
                cin.get();
            }
            break;
        case 6:
            system("cls");
            searchForBook(counterOfBooks);
            break;
        case 7:
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (intChoice != 7);
};

int main()
{
    string choice;
    BookFunctions bookFunctions;
    AuthorFunctions authorFunctions;
    int counterOfBooks = 0;
    int counterOfAuthors = 0;

    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t Welcome To Book Publisher Management System\n\n\t\t\t\t\tPress Enter to continue.";
    cin.get();

    counterOfBooks = readBooksFromFile();
    counterOfAuthors = readAuthorFromFile();

    do
    {
        system("cls");
        cout << "1  . Show All Books.\n";
        cout << "2  . Show All Authors.\n";
        cout << "3  . Add new Book.\n";
        cout << "4  . Add new Author.\n";
        cout << "5  . Assign book to an author.\n";
        cout << "6  . Remove a Book from an author.\n";
        cout << "7  . Update A Book.\n";
        cout << "8  . Update An Author.\n";
        cout << "9  . Remove A Book.\n";
        cout << "10 . Remove An Author.\n";
        cout << "11 . Delete All Books.\n";
        cout << "12 . Delete All Authers.\n";
        cout << "13 . search for a book details.\n";
        cout << "14 . search for an Author details.\n";
        cout << "15 . Exit.\n";

        cout << "Enter your choice: ";
        cin >> choice;

        system("cls");
        if (choice == "1")
        {
            bookFunctions.showAllBooks(counterOfBooks);
        }
        else if (choice == "2")
        {
            authorFunctions.showAllAuthors(counterOfAuthors);
        }
        else if (choice == "3")
        {
            bookFunctions.addBook(counterOfBooks);
        }
        else if (choice == "4")
        {
            authorFunctions.addAuthor(counterOfAuthors);
        }
        else if (choice == "5")
        {
            authorFunctions.AssignBooksToAuthor(counterOfAuthors, counterOfBooks);
        }
        else if (choice == "6")
        {
            authorFunctions.RemoveAuthorBooks(counterOfAuthors);
        }
        else if (choice == "7")
        {
            bookFunctions.updateBook(counterOfBooks, counterOfAuthors);
        }
        else if (choice == "8")
        {
            authorFunctions.updateAuthor(counterOfAuthors, counterOfBooks);
        }
        else if (choice == "9")
        {
            bookFunctions.RemoveABook(counterOfBooks);
        }
        else if (choice == "10")
        {
            authorFunctions.RemoveAnAuthor(counterOfAuthors);
        }
        else if (choice == "11")
        {
            bookFunctions.DeleteAllBooks(counterOfBooks);
            counterOfBooks = 0;
        }
        else if (choice == "12")
        {
            authorFunctions.DeleteAllAuthors(counterOfAuthors);
            counterOfAuthors = 0;
        }
        else if (choice == "13")
        {
            searchForBook(counterOfBooks);
        }
        else if (choice == "14")
        {
            searchForAuthor(counterOfAuthors, counterOfBooks);
        }
        else if (choice == "15")
        {
            cout << "\n\n\n\n\n\t\t\t\tGoodbye!\n\n\n\n\n";
            Sleep(1000);
            system("cls");
        }
        else
        {
            cout << "\t\t\t\tinvalid input! \nPress Enter to continue  \n";
            cin.ignore();
            cin.get();
            system("cls");
        }
    } while (choice != "15");
    return 0;
}