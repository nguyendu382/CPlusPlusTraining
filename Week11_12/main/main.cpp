#include <iostream>
#include <vector>

void showUserMenu() {
	std::cout << "User Menu:\n";
	std::cout << "1. View Profile\n";
	std::cout << "2. Search Book\n";
	std::cout << "3. Borrow Book\n";
	std::cout << "4. View Borrowed Books\n";
	std::cout << "5. Return Book\n";
	std::cout << "0. Exit\n";
}

void showManagerMenu() {
	std::cout << "Manager Menu:\n";
	std::cout << "1. Add Book\n";
	//std::cout << "Modify Book";
	std::cout << "2. Remove Book\n";
	std::cout << "3. View All Books\n";
	std::cout << "4. View All Users\n";
	std::cout << "5. View Borrowed Books\n";
	std::cout << "6. Search Book\n";
	std::cout << "0. Exit\n";
}

void showMainMenu() {
	std::cout << "Main Menu:\n";
	std::cout << "1. I am a User\n";
	std::cout << "2. I am a Library Manager\n";
	//std::cout <<"
	std::cout << "0. Exit\n";
}

class Book {
	std::string id;
	std::string title;
	std::string author;
	std::string genre;
	std::string publicationDate;
	bool isAvailable;
public:
	Book(const std::string& id, const std::string& title, const std::string& author, 
		 const std::string& genre, const std::string& publicationDate, bool isAvailable)
		: id(id), title(title), author(author), genre(genre), publicationDate(publicationDate), isAvailable(isAvailable) {}
	void display() const {
		std::cout << "ID: " << id << "\n"
			<< "Title: " << title << "\n"
			<< "Author: " << author << "\n"
			<< "Genre: " << genre << "\n"
			<< "Publication Date: " << publicationDate << "\n"
			<< "Available: " << (isAvailable ? "Yes" : "No") << "\n";
	}
	std::string getId() const { return id; }
	std::string getTitle() const { return title; }
	std::string getAuthor() const { return author; }
	std::string getGenre() const { return genre; }
	std::string getPublicationDate() const { return publicationDate; }
	bool getAvailability() const { return isAvailable; }
	void setId(const std::string& newId) { id = newId; }
	void setTitle(const std::string& newTitle) { title = newTitle; }
	void setAuthor(const std::string& newAuthor) { author = newAuthor; }
	void setGenre(const std::string& newGenre) { genre = newGenre; }
	void setPublicationDate(const std::string& newPublicationDate) { publicationDate = newPublicationDate; }
	void setAvailability(bool availability) { isAvailable = availability; }
};

class User {
	std::string id;
	std::string name;
	std::vector<Book> borrowedBooks;
public:
	User(const std::string& id, const std::string& name) : id(id), name(name) {}
	void display() const {
		std::cout << "User ID: " << id << "\n"
			<< "Name: " << name << "\n"
			<< "Borrowed Books: " << borrowedBooks.size() << "\n";
		for (const auto& book : borrowedBooks) {
			book.display();
			std::cout << "-------------------\n";
		}
	}
	std::string getId() const { return id; }
	std::string getName() const { return name; }
	void setId(const std::string& newId) { id = newId; }
	void setName(const std::string& newName) { name = newName; }
	void borrowBook(const Book& book) { borrowedBooks.push_back(book); }
	void returnBook(const std::string& bookId) {
		auto it = std::remove_if(borrowedBooks.begin(), borrowedBooks.end(),
			[&bookId](const Book& book) { return book.getId() == bookId; });
		if (it != borrowedBooks.end()) {
			borrowedBooks.erase(it, borrowedBooks.end());
		} else {
			std::cout << "Book with ID " << bookId << " not found in borrowed books.\n";
		}
	}
};

enum class location {};

class LBook : public Book {
	int num;
	std::string location; 
};

class Library {
	std::vector<Book> books;
	//std::pair<Book,int> books;
	std::vector<User> users;
public:
	void addBook(const Book& book) {
		books.push_back(book);
	}
	void addUser(const User& user) {
		users.push_back(user);
	}
	void displayBooks() const {
		for (const auto& book : books) {
			book.display();
			std::cout << "-------------------\n";
		}
	}
	void displayUsers() const {
		for (const auto& user : users) {
			user.display();
			std::cout << "-------------------\n";
		}
	}
	void borrowBook(const std::string& userId, const std::string& bookId) {
		auto userIt = std::find_if(users.begin(), users.end(),
			[&userId](const User& user) { return user.getId() == userId; });
		if (userIt != users.end()) {
			auto bookIt = std::find_if(books.begin(), books.end(),
				[&bookId](const Book& book) { return book.getId() == bookId && book.getAvailability(); });
			if (bookIt != books.end()) {
				userIt->borrowBook(*bookIt);
				bookIt->setAvailability(false); 
				std::cout << "Book borrowed successfully.\n";
			} else {
				std::cout << "Book not available or not found.\n";
			}
		} else {
			std::cout << "User not found.\n";
		}
	}
	void returnBook(const std::string& userId, const std::string& bookId) {
		auto userIt = std::find_if(users.begin(), users.end(),
			[&userId](const User& user) { return user.getId() == userId; });
		if (userIt != users.end()) {
			userIt->returnBook(bookId);
			auto bookIt = std::find_if(books.begin(), books.end(),
				[&bookId](const Book& book) { return book.getId() == bookId; });
			if (bookIt != books.end()) {
				bookIt->setAvailability(true);
				std::cout << "Book returned successfully.\n";
			} else {
				std::cout << "Book not found in library.\n";
			}
		} else {
			std::cout << "User not found.\n";
		}
	}
};

int main() {
	Library library;
	library.addBook(Book("1", "1984", "George Orwell", "Dystopian", "1949", true));
	library.addBook(Book("2", "To Kill a Mockingbird", "Harper Lee", "Fiction", "1960", true));
	library.addBook(Book("3", "The Great Gatsby", "F. Scott Fitzgerald", "Classic", "1925", true));
	library.addUser(User("u1", "Alice"));
	library.addUser(User("u2", "Bob"));
	library.displayBooks();
	library.displayUsers();

	return 0;
}