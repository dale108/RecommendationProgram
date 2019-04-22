// Author: Dale Berg, CPSC 2430 02
// Filename: Book.h
// Assignment: P1, Recommendations
// Date: 4/20/2019

// Purpose: This file contains the implementation of the Memeber struct and
// MemberList classes.
 #include "Member.h"
 #include<iostream>

 using namespace std;


 // *******************
 // * MEMBER         *
 // *******************

Member::Member() {
   name = "xxx";
   accountNumber = 0;
}

// Purpose: default constructor sets member's fields to information passed as
// parameters
Member::Member( string name, int accountNumber) {

   this->name = name;
   this->accountNumber = accountNumber;
   loggedIn = false;

}

int Member::getAccountNumber() {
   return accountNumber;
}

string Member::getName() {
   return name;
}

bool Member::isLoggedIn() {
   return loggedIn;
}

// Purpose: toggles member's isLoggedIn field
void Member::login() {
   loggedIn = true;
}

// Purpose: toggles member's isLoggedIn field
void Member::logout() {
   loggedIn = false;
}



// *******************
// * MEMBERLIST     *
// *******************

MemberList::MemberList( int setCapacity ) {

   size = 0;
   capacity = setCapacity;
   inventory = new Member[capacity];
   for( int i = 0; i < capacity; i++ ) {
      Member b;
      inventory[i] = b;
   }
}

 MemberList::MemberList( const MemberList &inv2 ) {
    capacity = inv2.capacity;
    size = inv2.size;
    inventory = new Member[capacity];

    for( int i = 0; i < size; i++ ) {
      inventory[i] = inv2.inventory[i];
   }
 }


MemberList::~MemberList() {
   delete [] inventory;
}


 // Overloaded = operator
 MemberList& MemberList::operator =( const MemberList &inv2 ) {

      delete [] inventory;

      capacity = inv2.capacity;
      size = inv2.size;
      inventory = new Member[capacity];

      for( int i = 0; i < size; i++ ) {
          inventory[i] = inv2.inventory[i];
      }

      return *this;
}

// Purpose: adds member to list, setting their fields to information passed
// as parameters
 void MemberList::addMember( string name, int accountNumber ) {

    if( size >= capacity ) {
      ensureCapacity();
    }

    Member* m = new Member(name, accountNumber);
    inventory[size] = *m;
    size++;
 }

 // Purpose: Adds member to list by reference to existing member object
 void MemberList::addMember( Member& m ) {

    if( size >= capacity ) {
      ensureCapacity();
    }

    inventory[size] = m;
    ++size;
}

// Purpose: Ensures that the memberListy has enough space allocated for more
// members to be added. Ensures that we will not overrun our allocated memory.
// Post: Capacity of MemberList is increased twofold.
void MemberList::ensureCapacity() {

   capacity = capacity * 2;

   Member *tempArr;
    tempArr = new Member[capacity];

   int i = 0;
   for(; i < size; i++ ) {
      tempArr[i] = inventory[i];
   }
   for(; i < capacity; i++ ) {
      //Member* b;
      tempArr = nullptr;
   }

   delete [] inventory;

   inventory = tempArr;
}

// Purpose: returns the member at index passed as a parameter
Member& MemberList::getMember( int index ) {
    return inventory[index];
 }

 // Purpose: returns the member with the account number passed as parameter.
 // Pre: integer account number of member to be found.
 // Post: member with associated accountNumber. Null cannot be returned here,
 // so client must cverify that member returned has valid state.
 Member MemberList::getMemberByNumber( int acct ) {
    for(int i = 0; i < size; i++) {
      if(inventory[i].getAccountNumber() == acct) {
         return inventory[i];
      }
   }
   // compiler will not allow nullptr return here, so client must check if
   // member has non-default state.
   Member m;
   return m;
}


// Returns last memeber added to the list.
 Member& MemberList::getLastMember() {
    return inventory[size];
}

// Returns the number of members which can be added to the list.
int MemberList::getCapacity() {
   return capacity;
}

// Returns number of members added to this list by a client.
int MemberList::getSize() {
   return size;
}

// Purpose: prints names of all memebers in the list to console.
void MemberList::seeAllMembers() {
   for(int i = 0; i < size; i++ ) {
      cout << "Name : " << inventory[i].getName() << endl;
      cout << endl;
      cout << endl;
    }
}
