#include <fstream>
#include <sstream>
#include "../includes_usr/fileIO.h"
using namespace std;


/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	books.clear();

	ifstream myInputFile;
	myInputFile.open(filename, ios::in);

	if (! myInputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	std::string line;
	std::string tempToken;
	book tmp_book;

	while (! myInputFile.eof()){
		getline(myInputFile, line);

		if (line == ""){
			break;
		}

		stringstream ss(line);
		std::string tmp;

		getline(ss, tmp, ',');
		tmp_book.book_id = stoi(tmp);
		getline(ss, tmp, ',');
		tmp_book.title = tmp;
		getline(ss, tmp, ',');
		tmp_book.author = tmp;
		getline(ss, tmp, ',');
		tmp_book.state = (book_checkout_state) stoi(tmp);
		getline(ss, tmp, '\n');
		tmp_book.loaned_to_patron_id = stoi(tmp);

		books.push_back(tmp_book);
	}

	myInputFile.close();

	if (books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	ofstream myOutputFile;
	myOutputFile.open(filename, ios::out);

	if (! myOutputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	if (books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}

	for (book b : books){
		myOutputFile << b.book_id << "," << b.title << "," << b.author << "," << b.state << "," << b.loaned_to_patron_id << "\n";
	}

	myOutputFile.close();

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	patrons.clear();

	ifstream myInputFile;
	myInputFile.open(filename, ios::in);

	if (! myInputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	std::string line;
	std::string tempToken;
	patron tmp_patron;

	while (! myInputFile.eof()){
		getline(myInputFile, line);

		if (line == ""){
			break;
		}

		stringstream ss(line);
		std::string tmp;

		getline(ss, tmp, ',');
		tmp_patron.patron_id = stoi(tmp);
		getline(ss, tmp, ',');
		tmp_patron.name = tmp;
		getline(ss, tmp, '\n');
		tmp_patron.number_books_checked_out = stoi(tmp);

		patrons.push_back(tmp_patron);
	}

	myInputFile.close();

	if (patrons.empty()){
		return NO_PATRONS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	ofstream myOutputFile;
	myOutputFile.open(filename, ios::out);

	if (! myOutputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	if (patrons.empty()){
		return NO_PATRONS_IN_LIBRARY;
	}

	for (patron p : patrons){
		myOutputFile << p.patron_id << "," << p.name << "," << p.number_books_checked_out << "\n";
	}

	myOutputFile.close();

	return SUCCESS;
}
