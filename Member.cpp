// Author: Dale Berg, CPSC 2430 02
// Filename:
// Assignment:
// Date:

// Purpose:
// INPUT:
// PROCESS:
// OUTPUT:
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


void Member::login() {
   loggedIn = true;
}

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


   //if( this != inv2& ) {

      delete [] inventory;

      capacity = inv2.capacity;
      size = inv2.size;
      inventory = new Member[capacity];

      for( int i = 0; i < size; i++ ) {
          inventory[i] = inv2.inventory[i];
      }

      return *this;
}

// Purpose:
// Pre:
// Post:
 void MemberList::addMember( string name, int accountNumber ) {

    if( size >= capacity ) {
      ensureCapacity();
    }

    Member* m = new Member(name, accountNumber);
    inventory[size] = *m;
    size++;
 }

 // Purpose:
 // Pre:
 // Post:
 void MemberList::addMember( Member& m ) {

    if( size >= capacity ) {
      ensureCapacity();
    }

    inventory[size] = m;
    ++size;
}

// Purpose:
// Pre:
// Post:
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

// Purpose:
// Pre:
// Post:
Member& MemberList::getMember( int index ) {
    return inventory[index];
 }

 // Purpose:
 // Pre:
 // Post:
 Member& MemberList::getMemberByNumber( int acct ) {
    for(int i = 0; i < size; i++) {
      if(inventory[i].getAccountNumber() == acct) {
         return inventory[i];
      }
   }
    return getMemberByNumber(acct);
}


// Purpose:
// Pre:
// Post:
 Member& MemberList::getLastMember() {
    return inventory[size];
}


int MemberList::getCapacity() {
   return capacity;
}

int MemberList::getSize() {
   return size;
}

// Purpose:
// Pre:
// Post:
int MemberList::indexOf( string memberName ) {

     for( int i = 0; i < size; i++ ) {
      if( (inventory[i].getName() == memberName) ) {
           return i;
        }
     }
     return -1;
}


// Purpose:
// Pre:
// Post:
void MemberList::seeAllMembers() {
   for(int i = 0; i < size; i++ ) {
      cout << "Name : " << inventory[i].getName() << endl;
      cout << endl;
      cout << endl;
    }
}
