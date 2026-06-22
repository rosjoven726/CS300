//  **************************************
//  7-1 Submit Project Two.cpp 
//  Joven Rosales SNHU Final Project 
//  **************************************

/*
Design Summary:

This program uses a Binary Search Tree (BST) to store course data.
The BST is chosen because it allows efficient searching and maintains
sorted order automatically based on course number.

Operations:
- Insert: Adds courses while maintaining BST structure
- Search: Finds a course by course number
- Print: Displays courses in sorted order using in-order traversal
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Represents a single course with its number, title,
// and a list of prerequisite courses.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Represents a node in the Binary Search Tree.
// Each node stores a Course object and pointers
// to left and right child nodes.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree (BST) class
// Stores Course objects sorted by course number.
// Provides insertion, search, and in-order traversal.
class BinarySearchTree {

private:
    Node* root;

    // Recursively inserts a course into the BST
    // based on course number comparison.
    void addNode(Node* node, Course course) {

        if (course.courseNumber < node->course.courseNumber) {

            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                addNode(node->left, course);
            }
        }
        else {

            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                addNode(node->right, course);
            }
        }
    }

    // Performs in-order traversal of the BST
    // to display courses in sorted order.
    // O(n) time complexity
    // Visits every node once in sorted order
    void inOrder(Node* node) {

        if (node != nullptr) {

            inOrder(node->left);

            cout << node->course.courseNumber
                << ", "
                << node->course.courseTitle
                << endl;

            inOrder(node->right);
        }
    }

public:
    // Initializes an empty BST with root set to nullptr.
    BinarySearchTree() {
        root = nullptr;
    }

    // Inserts a new course into the BST while maintaining sorted order
    // based on course number. This allows efficient search and traversal.
    // Average: O(log n), Worst: O(n)
    // Depends on tree balance
    void Insert(Course course) {

        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }
    }

    // Prints all courses in alphanumeric order
    // using in-order traversal.
    void PrintCourseList() {
        inOrder(root);
    }

    // Searches for a course by course number.
    // Returns the matching Course object if found,
    // otherwise returns an empty Course.
    // Average: O(log n), Worst: O(n)
    // Performs binary search through BST
    Course Search(string courseNumber) {

        Node* current = root;

        while (current != nullptr) {

            if (current->course.courseNumber == courseNumber) {
                return current->course;
            }

            if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        Course emptyCourse;
        return emptyCourse;
    }
};

// Reads course data from a CSV file and loads it
// into the Binary Search Tree.
// courseNumber,courseTitle,prerequisite1,prerequisite2,...
void loadCourses(string fileName, BinarySearchTree& bst) {

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Could not open file!" << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        string prereq;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }
        
        bst.Insert(course);
    }

    file.close();

    cout << "Data loaded successfully." << endl;
}

// Main program loop that displays a menu for the user.
// Allows loading data, printing all courses, and searching
// for a specific course until the user exits.
int main() {

    BinarySearchTree bst;

    string fileName;
    int choice = 0;
    bool dataLoaded = false;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << endl;

        cout << "What would you like to do? ";

        // Validates user input to ensure a number is entered.
        // Clears invalid input from the input buffer if needed.
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
         // Load course data from CSV file into BST
        case 1:
        {
            loadCourses("CS 300 ABCU_Advising_Program_Input.csv", bst);
            cout << "Course data loaded." << endl;
            break;
        }
        // Display all courses in sorted order
        case 2:
        {                      
            cout << endl;
            cout << "Here is a sample schedule:" << endl;
            

            bst.PrintCourseList();
            break;
        }
        // Search for a specific course and display details
        // including prerequisites
        case 3:
        {
            string courseNumber;

            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            transform(courseNumber.begin(),
                courseNumber.end(),
                courseNumber.begin(),
                ::toupper);

            Course course = bst.Search(courseNumber);
            

            if (course.courseNumber.empty()) {

                cout << "Course not found." << endl;
            }
            else {

                cout << course.courseNumber
                    << ", "
                    << course.courseTitle
                    << endl;

                cout << "Prerequisites: ";

                if (course.prerequisites.empty()) {

                    cout << "None";
                }
                else {

                    for (size_t i = 0; i < course.prerequisites.size(); i++) {

                        cout << course.prerequisites[i];

                        if (i < course.prerequisites.size() - 1) {
                            cout << ", ";
                        }
                    }
                }

                cout << endl;
            }

            break;
        }
        // Exit the program
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}

