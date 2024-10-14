// Erik Wood

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::string; 
using std::getline;
using std::list; 
using std::vector;
using std::cout; 
using std::endl;
using std::move;
using std::map;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org) noexcept:
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {return firstName_ + ' ' + lastName_;}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return (left.firstName_ == right.firstName_ && left.lastName_ == right.lastName_);
    }

   // needed for sort()
    friend bool operator< (Student left, Student right){
      return left.firstName_ < right.firstName_ ||
	     (left.firstName_ == right.firstName_ && 
	      left.lastName_ < right.lastName_);
    }
private:
   string firstName_;
   string lastName_;
};





// reading a list from a fileName
void readdropouts(list<Student>& dropouts, const string& fileName);
void readRoster(map<Student, list<string>>& roster, const string& fileName);
// printing a list out
void printRoster(const map<Student, list<string>>& roster);

int main(int argc, char* argv[]){

    if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

    // vector of courses of students
    map<Student, list<string>> allStudents; 

    for(int i = 1; i < argc - 1; ++i) {
        readRoster(allStudents, argv[i]);
    }


    // reading in dropouts
    list<Student> dropouts; 
    readdropouts(dropouts, argv[argc-1]); // reads in the dropouts

    for(const auto& dropout : dropouts){
        allStudents.erase(dropout); // removing dropouts
    }

    printRoster(allStudents);
}


void readRoster(map<Student, list<string>>& roster, const string& fileName){
   ifstream file(fileName);
   
   string firstName, lastName;
   string className = fileName.substr(0, fileName.find('.')); // gets the class name from the fileName

   while(file >> firstName >> lastName){
        roster[Student(firstName, lastName)].push_back(className);
    }
   file.close();
}

void readdropouts(list<Student>& dropouts, const string& fileName) {
    ifstream course(fileName);
   string first, last;
   while(course >> first >> last){
      dropouts.emplace_back(first, last);
   }
   course.close();
}

// printing a list out
void printRoster(const map<Student, list<string>>& roster){
   cout << "all students, dropouts removed and sorted" << endl;
   cout << "first name last name: courses enrolled" << endl;

   for(const auto& entry : roster){
       cout << entry.first.print() << ": ";
       for(const auto& course : entry.second){
           cout << course << " ";
        }
       cout << endl;
    }
}