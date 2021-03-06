#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"

using namespace std;

//methods
Student* addStudent();
void addNode(Student* student, Node* &current, Node* &start);
void printNode(Node* start);
void deleteStudent(char studentName[], Node* &start, Node* current);

int main() {
  //beginnint node, most recently added node
  Node* start = NULL;
  Node* current = start;
  bool adding = true;
  //INFINATE LOOP, until exited when you quit
  while (adding == true) {
    //input demand
    char* input = new char[80];
    do {
      cout << "'add' 'quit' 'delete' or 'print'?" << endl;
      input = new char[80];
      cin.get(input, 80);
      cin.get();
    } while (strcmp(input, "add") != 0 && strcmp(input, "print") != 0 && strcmp(input, "quit") != 0 && strcmp(input, "delete") != 0);
    //check for demand
    if (strcmp(input, "add") == 0) {
      //create a new student
      Student* newStudent = addStudent();
      //create a new Node with that Student
      addNode(newStudent, current, start);
    }
    //break the while loop if quiting
    else if (strcmp(input, "quit") == 0) {
      break;
    }
    else if(strcmp(input, "delete") == 0) {
      //input student name
      cout << "Student Name: ";
      char studentName[80];
      cin.get(studentName, 80);
      cin.get();
      //delete that Node and student
      deleteStudent(studentName, start, start);
    }
    else {
      //print out linked list
      printNode(start);
    }
  }
  return 0;
}
//take input for name, ID, and GPA, then create a student with the following
Student* addStudent() {
  cout << "First Name: ";
  char* firstName = new char[40];
  cin.get(firstName, 40);
  cin.get();
  cout << "Last Name: ";
  char* lastName = new char[40];
  cin.get(lastName, 40);
  cin.get();
  cout << "ID: ";
  int ID;
  cin >> ID;
  cin.ignore();
  cout << "GPA: ";
  double GPA;
  cin >> GPA;
  cin.ignore();
  Student* newStudent = new Student(firstName, lastName, ID, GPA);
  return newStudent;
}


void addNode(Student* student, Node* &current, Node* &start) {
  //create a new node
  Node* newNode = new Node();
  newNode->setStudent(student);
  //if there is no first Node, create first Node
  if (start == NULL) {
    start = newNode;
    current = start;
    return;
  }
  //if this is the last node in the linked list, the new node is next
  //attach node to linked list
  if (current != NULL && current->getNext() == NULL) {
    current->setNext(newNode);
    //reset last Node
    current = newNode;
  
    return;
  }
  //if current is not the last node, run for the next node (shouldn't happen)
  if (current != NULL && current->getNext() != NULL) {
    current = current->getNext();
    addNode(student, current, start);
  }
}

void printNode(Node* start) {
  //start with first node and print
  Node* current = start;
  Student* currentStudent = current->getStudent();
  cout << "Name: " << currentStudent->getName() << endl;
  cout << "ID: " << currentStudent->getID() << endl;
  cout << "GPA: " << currentStudent->getGPA() << endl;
  cout << endl;
  //if this is the last Node- we're done!
  if (current->getNext() != NULL) {
    current = current->getNext();
    printNode(current);
  }
  return;
}

void deleteStudent(char studentName[], Node* &start, Node* current) {
  if (start == NULL) {
    cout << "no students" << endl;
    return;
  }
  //if the first node is this one, delete the first node and reset the new first node
  if (current == start && strcmp(current->getStudent()->getName(), studentName) == 0) {
    start = current->getNext();
    delete current;
    return;
  }
  //if we've already gone through all nodes, this student does not exist
  else if (current->getNext() == NULL) {
    cout << "Could not find student" << endl;
    return;
  }
  //if this is the node! reset this node next node, and delete its next node
  else if (strcmp(current->getNext()->getStudent()->getName(), studentName) == 0) {
    Node* deleteNode = current->getNext();
    current->setNext(current->getNext()->getNext());
    delete deleteNode;
    return;
  }
  //iterate to the next node if not found
  deleteStudent(studentName, start, current->getNext());
  
}
