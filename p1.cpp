// Author: Dale Berg, CPSC 2430 02
// Filename: p1.cpp
// Assignment: P1, Recommendations
// Date: 4/20/2019

// Purpose: p1.cpp contains the main and UI methods for the Project 1,
// Recommendations assignment. The Extra credit portion of the program writes
// to files called "bookState.txt" and "fileState.txt". These files can then
// be read back into the program if the user chooses.

#include "Book.h"
#include "Member.h"
#include "Rating.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++
//  METHOD PROTOTYPES / CLASS VARIABLE DECLARATIONS
//+++++++++++++++++++++++++++++++++++++++++++++++++


// prototype statements for methods defined after main.
void addNewUser();
void addNewBook();
void getRecommendations(Member user);
void getReallyLike( int memberNumber );
void getLike( int memberNumber );
int getInput();
int getLoginInfo( int maxIdx );
void mainMenu();
Member& memberLogin( MemberList& memberList );
void logout(Member user);
void userMenu( Member user );
void rateBook();
bool selectionValidation( int n);
void writeStateToFile();
void viewAllRatings(Member user);

// Vairables which need to declare this outside main so
// that functions below have access.
bool userLoggedIn = false;
Member user;
int input;
int bookCounter;

// Long ensures we can have lots of accounts. Increments to generate unique
// account numbers as users are added.
long accountNumberGenerator = 0;

// Increments to generate unique isbn numbers
long isbnGenerator = 0; //


//+++++++++++++++++++++++++++++++
//  BOOK, MEMBER and RATING LISTS
//+++++++++++++++++++++++++++++++
// Design: These are declared outside of main so that they are accessible
// to methods implemnted later in the file (after main executes).
// I chose to implement this way in order to keep main cleaner, and to be
// able to reuse some behaviour.

//instantiate BookInventory
BookInventory bookInventory(100); // 100 is arbitrary for now

//initialize member list
MemberList memberList(100); // 100 is arbitrary for now

// initialize ratinglist
//extern RatingList ratingList;
RatingList ratingList(100,100); //100/100 is arbitrary, as ratings are added
                                // ensure cpacity will increase sizes as needed



int main() {


   // Get book file name from user
   string bookFile;
   cout << "Please input book file name:  " << endl;
   cin >> bookFile;

   // Get ratings file name from user
   string ratingFile;
   cout << "Please input ratings file name:  " << endl;
   cin >> ratingFile;

   // Initialize bookReader - responsible for initializing all book objects
   // must be converted to c string for cs1 to compile
   ifstream bookReader(bookFile.c_str());

   // Test if file opens
   if( bookReader.is_open() ) {
      cout << "Book File is open! " << endl;
   }
   else {
      cout << "Book File not open :(" << endl;
   }

   string line; // Need this for file traversal to work
   bookCounter = 0;
   string author, title, year;
   while( getline(bookReader, line) ) {
      stringstream   linestream(line);
      string         value;
      string str[3]; // 3 pieces of book information
      for(int i = 0; i < 3; i ++) {
          getline(linestream, value, ',');
          str[i] = value;
       }
       string author = str[0];
       string title = str[1];
       string year = str[2];
       isbnGenerator++;
       bookInventory.addBook(author, title, year, isbnGenerator);
       bookCounter++;
    }

   //confirm books were read in properly
   cout << "\n" << endl;
   cout << "Number Books: " << bookCounter << endl;
   cout << "\n" << endl;


   ifstream ratingReader(ratingFile);



   //test if file opens
   if( ratingReader.is_open() ) {
      cout << "Rating File is open!" << endl;
   }
   else {
      cout << "Rating File not open :(" << endl;
   }

   cout << "\n" << endl;


   string name;
   string line2;
   int ratingsIndex = -1;
   Member m;
   // need to set book size for ensure capacity to function
   ratingList.setBookSize(bookCounter);

   // File processing section
   while (ratingReader.peek() != EOF) {
      getline(ratingReader,line2);
      stringstream   lineStream(line2);
      string         ratingString;
      char c = line2[0];
      if(isalpha(c)) { // name case
         name = line2;
         accountNumberGenerator++;
         Member temp(name, accountNumberGenerator);
         m = temp;
         memberList.addMember(temp);
      }
      else { // numerical rating case
         while(lineStream >> ratingString) {
            int score = stoi(ratingString);
            ratingList.addRating(bookInventory.getBook(ratingsIndex), accountNumberGenerator, score);
            ratingsIndex++;
         }
         ratingsIndex =-1;
      }
   }

   ratingList.setMemberSize( memberList.getSize() );
   Member user;
   string newUserName;
   mainMenu();

   cout << "Thank you for using our Book Recommendation program!" << endl;
   ratingReader.close();
   bookReader.close();
   writeStateToFile();
   return 0;
}

/********************
 *   UI FUNCTIONS    *
 ********************/

 // Purpose: Adds a new member to the memberList
 void addNewUser() {
    string n;
    cout << "Please input name of member ";
    cout << "(first character must not be numeric) : ";
    cin >> n;
    while(!isalpha(n[0])) {//First character must be alphabetic for file reading
       string n;
       cout << "Please input name of member ";
       cout << "(first character must not be numeric) : ";
       cin >> n;
    }
    memberList.addMember(n, accountNumberGenerator);
    Member temp;
    temp = memberList.getMember(accountNumberGenerator);
    cout << "We added " << temp.getName() << " to our member list!" << endl;
    accountNumberGenerator++;
    ratingList.setMemberSize(accountNumberGenerator);//increments for all users

    if(userLoggedIn) {
       userMenu(user);
    }
    else {
       mainMenu();
    }

 }

 // executes when the user adds a new book from either menu.
 void addNewBook() {
    string title;
    cout << "Please input title of book : ";
    cin >> title;
    cout << endl;
    string author;
    cout << "Please input author of book : ";
    cin >> author;
    cout << endl;
    cout << "Please input year book was written: ";
    string year;
    cin >> year;

    // instantiate book
    bookInventory.addBook(author, title, year, isbnGenerator);
    Book temp;
    temp = bookInventory.getBook(isbnGenerator);

    // confirm the book was added by finding it in list
    cout << "We added " << temp.getTitle() << " by " << temp.getAuthor();
    cout << " to our book list! The isbn is: " << temp.getIsbn() << endl;
    cout << isbnGenerator << endl;
    isbnGenerator++;
    ratingList.setBookSize(isbnGenerator); // increments for all users

    if(userLoggedIn) {
       userMenu(user);
    }
    else {
       mainMenu();
    }
 }

 // Purpose: When no member is logged in, these are the options
 // to interact with the program.
void mainMenu() {
      cout << " -------------------------------------- " << endl;
      cout << " User: not logged in                   |" << endl;
      cout << "                                       | " << endl;
      cout << " 1. login                              | " << endl;
      cout << " 2. Add new member                     | " << endl;
      cout << " 3. Add new Book                       | " << endl;
      cout << " 4. Quit                               | " << endl;
      cout << " -------------------------------------  " << endl;
      cout << "\n" << endl;

      input = getInput();
      int userNumber;
      switch(input) {
         case 1 : userNumber = getLoginInfo(memberList.getSize());
                  user = memberList.getMember(userNumber);
                  cout <<  user.getName() << endl;
                  user.login();
                  userMenu(user);
                  break;
         case 2 : addNewUser();
                 break;
         case 3 : addNewBook();
                  break;
         case 4 :
                  break;

      }
   }

// Purpose: When a member is logged in, these are the options
// to interact with the program.
// Pre: user currently logged in
// Post: displays user menu
void userMenu(Member user) {

   userLoggedIn = true;
      cout << " +++++++++++++++++++++++++++++++++++++++ " << endl;
      cout << " User: " << user.getName() << "          " << endl;
      cout << "                                       + " << endl;
      cout << " 1. Add new member                     + " << endl;
      cout << " 2. Add new Book                       + " << endl;
      cout << " 3. Logout                             + " << endl;
      cout << " 4. View all own ratings               + " << endl;
      cout << " 5. Rate a book                        + " << endl;
      cout << " 6. See recommendations                + " << endl;
      cout << " 7. Quit                               + " << endl;
      cout << "                                       + " << endl;
      cout << "++++++++++++++++++++++++++++++++++++++++ " << endl;


      input = getInput();
      switch(input) {
         case 1 : addNewUser();
                  break;
         case 2 : addNewBook();
                  break;
         case 3 : logout(user);
                  break;
         case 4 : viewAllRatings(user);
                  break;
         case 5 : rateBook();
                  break;
         case 6 : getRecommendations(user);
                  break;
         case 7 :
                  break;

         }
}

// Purpose: takes numerical input from user and validates that it corresponds
// with a menu option
// Post: validates input is correct and returns integer selection
int getInput() {
   int selection;
   cout << "Please enter a selection: ";
   cin >> selection;
   while(!selectionValidation(selection)) {
      cout << "Selection invalid, please try again" << endl;
      cout << "Please enter a selection: ";
      cin >> selection;
   }
   return selection;
}

// Purpose: gets account number as input from the user adn returns indexOf
// of user in memberList.
// Purpose: gets login info from user. Validates that input is legal.
// Pre: maxIdx is account number of last memeber in list.
// Post: returns accoutn number of member to be logged in.
int getLoginInfo( int maxIdx ) {

   int acctNum = 0;
   cout << "Please enter your account number: ";
   cout << "hint: any # between 0 and " << ( maxIdx-1 ) << " inclusive ";
   cout << endl;
   cin >> acctNum;
   while( acctNum < 0 || acctNum > maxIdx) {
      cout << "Account # must be between 0 and " << maxIdx << endl;
      cout << "Please enter your account number: ";
      cin >> acctNum;
   }
   return acctNum; // leveraging index system.
}

// Purpose: Gets list of recommendations from user with ratings most mostSimilar
// to the ratings logged by active user.
// Pre: Memebr obejct representing the current user.
// Post: Prints list of book recommendations for currently logged in user.
void getRecommendations(Member user) {

   int mostSimilar = ratingList.getMostSimilar( user.getAccountNumber() );
   if(mostSimilar != -1) {
      Member mostSimilarMember =  memberList.getMemberByNumber(mostSimilar);
      string mostSimilarName = mostSimilarMember.getName();
      cout << "The user with the most similar ratings is: ";
      cout <<  mostSimilarName << endl;
      cout << "\n" << "Here are the books " << mostSimilarName;
      cout <<  " really liked: " << endl;
      getReallyLike(mostSimilar);
      getLike(mostSimilar);
   }
   else {
      cout << " Couldn't find most similar user " << endl;
   }
   userMenu(user);
}

// Purpose: prints list of books with numerical rating 5 logged by member
// represented by memberNumber passed as argument.
// Pre: integer memberNumber representing user in memberList.
void getReallyLike( int memberNumber ) {
   int count = 1;
   for(int i = 0; i < bookCounter; ++i) {
      Rating r = ratingList.getRating( memberNumber, i);
      if( r.getScore() == 5 ) {
        cout << count << "." << " " << bookInventory.getTitle(i) << endl;
        count++;
      }
   }
   cout << endl;
}

// Purpose: prints list of books with numerical rating 4 logged by member
// represented by memberNumber passed as argument.
// Pre: integer memberNumber representing user in memberList.
void getLike( int memberNumber ) {
   int count = 1;
   cout << "Here are the books they liked: " << endl;
   for(int i = 0; i < bookCounter; ++i) {
      Rating r = ratingList.getRating( memberNumber, i);
      if( r.getScore() == 3 ) {
        cout << count << "." << " " << bookInventory.getTitle(i);
        cout << " by " << bookInventory.getAuthor(i) << endl;
        count++;
      }
   }
   cout << endl;
}

// Purpose: logs current user out.
// Pre: user passed as parameter. USer must be stipulated so that their internal
// isLoggedIn field may be toggled.
// Post: user logged out of system.
void logout(Member user) {
      user.logout(); // updates user's field.
      userLoggedIn = false;
      mainMenu();
}

// Purpose: validates whether menu selection is valid
bool selectionValidation( int n) {
   if( (n < 1) || (n > 7) ) {
      return false;
   }
   return true;
}

// Purpose: allows currently loged in user to add a new rating to ratingList
// Pre: user must be logged in.
// Post: rating added to ratingList
void rateBook() {
   int i;
   int r;
   cout << "Please input ISBN of book you'd like to rate ";
   cout << " (0 - " << isbnGenerator-1 << ") inclusive: ";
   cin >> i;
   cout << endl;
   cout << "Rating must be: -5, -3, 0, 1, 3 or 5" << endl;
   cout << "Please enter your rating: ";
   cin >> r;
   while ( !(r == -5 || r == -3 || r == 0 || r == 1 || r == 3 || r == 5) ) {
      cout << "Invalid rating, please try again: ";
      cin >> r;
   }

   ratingList.updateRating( i , user.getAccountNumber(), r);
   userMenu(user);
}

// Purpose: displays all ratings logged by user currently logged in to the
// system.
// Pre: user logged in
// Post: prints all user's ratings to console.
void viewAllRatings(Member user) {
   cout << "Displaying ratings for " << user.getName() << " ";
   ratingList.allUserRatings( user.getAccountNumber() );
   userMenu(user);
}

// Purpose: writes current state of program to text files on exit. This is
// intended to fulfill the extra credit assignment.
// Post: writes data in assignmetn specified format to .txt files called
// bookState.txt and ratingState.txt
void writeStateToFile() {

   // saving here so that method is only called once.
   int numberMembers = memberList.getSize();

   ofstream bookStateWriter( "bookState.txt" );
   ofstream fileStateWriter( "ratingState.txt" );
   bookStateWriter << bookInventory.allBooksString();
   for(int i = 0; i < numberMembers; ++i) {
      Member mem = memberList.getMember(i);
      fileStateWriter << mem.getName();
      fileStateWriter << "\n";
      fileStateWriter << ratingList.getRowAsString(mem.getAccountNumber());
      fileStateWriter << "\n";
   }
}
