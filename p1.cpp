// Author: Dale Berg, CPSC 2430 02
// Filename: Time.cpp
// Assignment: Lab 01, Time
// Date: 4/10/2019

// Purpose:
// INPUT:
// PROCESS:
// OUTPUT:


//***** change these to .h!!!!
//***** change these to .h!!!!
#include "Book.cpp"
#include "Member.cpp"
#include "Rating.cpp"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

//+++++++++++++++++++++++++++++++
//  METHOD PROTOTYPES
//+++++++++++++++++++++++++++++++

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
void viewAllRatings(Member user);


bool userLoggedIn = false; // need to declare this outside main so that functions have
                  // access.
Member user;

int input;

int bookCounter;

// This ensures we can have lots of accounts
long accountNumberGenerator = 0;

// This increments to generate unique isbn numbers
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


   // get book file name from user
   string bookFile;
   cout << "Please input book file name:  " << endl;
   cin >> bookFile;

   // get ratings file name from user
   string ratingFile;
   cout << "Please input ratings file name:  " << endl;
   cin >> ratingFile;

   // initialize bookReader - responsible for initializing all book objects
   ifstream bookReader(bookFile);

   //test if file opens
   if( bookReader.is_open() ) {
      cout << "Book File is open! " << endl;
   }
   else {
      cout << "Book File not open :(" << endl;
   }

   string line; // need this for file traversal to work
   bookCounter = 0;
   string author, title, year;
   while( getline(bookReader, line) ) {
      stringstream   linestream(line);
      string         value;
      string str[3];
      for(int i = 0; i < 3; i ++) {
          getline(linestream, value, ',');
          str[i] = value;
       }
       string author = str[0];
       string title = str[1];
       string year = str[2];
       //cout << "Author: " << author << " Title: " << title << " Year: " << year << endl;
       isbnGenerator++;
       bookInventory.addBook(author, title, year, isbnGenerator);
       bookCounter++;
    }

   //confim books were read in properly
   cout << "\n" << endl;
   cout << "Book list is populated! number Books: " << bookCounter << endl;
   cout << "\n" << endl;


   ifstream ratingReader(ratingFile);



   //test if file opens
   if( ratingReader.is_open() ) {
      cout << "Rating File is open!" << endl;
   }
   else {
      cout << "Rating File not open :(" << endl;
   }


   string name;
   string line2;
   int ratingsIndex = -1;
   Member m;
   ratingList.setBookSize(bookCounter);


   while (ratingReader.peek() != EOF) {
      getline(ratingReader,line2);
      stringstream   lineStream(line2);
      string         ratingString;
      char c = line2[0];
      if(isalpha(c)) { // name case
         name = line2;
         //cout << "name is: "  << name << endl;
         accountNumberGenerator++;
         Member temp(name, accountNumberGenerator);
         m = temp;
         memberList.addMember(temp);
      }
      else {
         while(lineStream >> ratingString) {
            //cout << ratingString << " ";
            int score = stoi(ratingString);
            //cout << score << ", ";
            ratingList.addRating(bookInventory.getBook(ratingsIndex), accountNumberGenerator, score);


            // cout << "Member name being added to: " << m.getName() << endl;
            // Book z;
            // z = bookInventory.getBook(ratingsIndex);
            // cout << "Book being added: " << z.getTitle() << endl;
            // cout << "rating applied: " << score << endl;
            // cout << endl;
            ratingsIndex++;
         }
         ratingsIndex =-1;
      }
   }

   ratingList.setMemberSize( memberList.getSize() );
   //cout << "this is bookSizesize of the list:::: " << ratingList.getBookSize() << endl;
   //cout << "This is the memberSize of the list:: " << ratingList.getMemberSize() <<  endl;
   Member user;
   string newUserName;
   mainMenu();



   cout << "Thank you for using our Book Recommendation software!" << endl;
   ratingReader.close();
   bookReader.close();
   return 0;
}

/********************
 *   UI FUNCTIONS    *
 ********************/

 // Purpose: This adds a new member to the memberList
 void addNewUser() {
    string n;
    cout << "Please input name of member ";
    cout << "(first character must not be numeric) : ";
    cin >> n;
    while(!isalpha(n[0])) {//First character must be alpahbetic for file reading
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

    if(userLoggedIn) {
       userMenu(user);
    }
    else {
       mainMenu();
    }

 }

 // This executes when the user adds a new book from either menu.
 void addNewBook() {
    // Gather book data
    string title;
    cout << "Please input title of book : ";
    cin >> title;
    cout << endl;
    string author;
    cout << "Please input author of book : ";
    cin >> author;
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
    ratingList.setBookSize(isbnGenerator);

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
      cout << " ------------------------------------- | " << endl;
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
         case 4 : cout << "Thank you for using our program!" << endl;
                  break;
      }
   }

// Purpose: When a member is logged in, these are the options
// to interact with the program.
void userMenu(Member user) {
      cout << " +++++++++++++++++++++++++++++++++++++++ " << endl;
      cout << " User: " << user.getName() << "        + " << endl;
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
int getLoginInfo( int maxIdx ) {

   int acctNum = 0;
   cout << "Please enter your account number: ";
   cout << "hint: any # between 1000 and " << ( maxIdx ) << endl;
   cin >> acctNum;
   while( acctNum < 0 || acctNum > maxIdx) {
      cout << "Account # must be between 1000 and " << (maxIdx) << endl;
      cout << "Please enter your account number: ";
      cin >> acctNum;
   }
   return (acctNum); // leveraging index system.
}

void getRecommendations(Member user) {

   cout << "user account number is:" << user.getAccountNumber() << endl;
   int mostSimilar = ratingList.getMostSimilar( user.getAccountNumber() );
   cout <<  "mostSimilar is "<< mostSimilar << endl;
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
      cout << " Something went wrong ";
   }
   userMenu(user);
}


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

void rateBook() {
   int i;
   int r;
   cout << "Please input ISBN of book you'd like to rate: ";
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


void viewAllRatings(Member user) {
   cout << "Displaying ratings for " << user.getName();
   ratingList.allUserRatings( user.getAccountNumber() );
   userMenu(user);
}
