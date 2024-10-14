//Erik Wood
// Object file

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org) noexcept:
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_)),
      classes_(move(org.classes_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string getName() const{
   return firstName_ + " " + lastName_;
   }

  void addClass(const string& className){
      if(std::find(classes_.begin(), classes_.end(), className) == classes_.end()) {
         classes_.push_back(className);
      }
   }

   const list<string>& getClasses() const {
      return classes_;
   }

   string print() const {
      string result = firstName_ + " " + lastName_ + ":";
      for(const auto& className : classes_){
         result+= " " + className;
      }
      result += "\n";
      return result;
   }

   // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
   list<string> classes_;
};




// reading a list from a fileName
void readRoster(vector<list<Student>>& roster, string fileName);  
// printing a list out
void printRoster(const vector<list<Student>>& roster);
void printRoster(const list<Student>& roster); 
void readDropouts(list<Student>& dropouts, string fileName);
void printDropouts(const list<Student>& dropouts);

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   vector <list<Student>> studentEntries; 

   for(int i = 1; i < argc - 1; i++){
      studentEntries.emplace_back();
      readRoster(studentEntries, argv[i]);  
      //cout << "\n\n" << argv[i] << "\n";  
      //printRoster(studentEntries); 
   }


   // reading in dropouts
   list<Student> dropouts; 
   readDropouts(dropouts, argv[argc-1]); 
   cout << "\n\n dropouts \n";
   printDropouts(dropouts);

   list<Student> allStudents;  // master list of students
 
   for (auto& lst : studentEntries) {
      allStudents.splice(allStudents.end(), lst); // merges the two lists
   }

   cout << "\n\n all students unsorted \n"; 
   printRoster(allStudents);

   allStudents.sort(); // sorting master list
   cout << "\n\n all students sorted \n";
   printRoster(allStudents);

   allStudents.unique([](Student& a, Student& b){
      if(a == b){
         for(const auto& className : b.getClasses()){
            a.addClass(className);
         }
         return true; // b should be removed because it is a duplicate
      }
      return false; // a and b are not the same
   }); // eliminating duplicates
   cout << "\n\n all students, duplicates removed \n";
   printRoster(allStudents);
   
   for (const auto& str : dropouts){ // removing individual dropouts
      allStudents.remove(str);
   }
   cout << "\n\n all students, dropouts removed \n";
   printRoster(allStudents);

}


void readRoster(vector<list<Student>>& roster, string fileName){
   ifstream infile(fileName);
   string first, last, className;
   className = fileName.substr(0, fileName.find('.')); // getting the names of the classes

   while(infile >> first >> last){
      Student newStudent(first,last);
      bool found = false;

      for(auto& student : roster.back()){
         string s1 = student.getName();
         string s2 = newStudent.getName();
         if(s1 == s2){
            student.addClass(className);
            found = true;
            break;
         }
      }

      if(!found){
         newStudent.addClass(className);
         roster.back().push_back(newStudent);
      }
   }
   infile.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster){
      cout << student.print();
   }
}

void printRoster(const vector<list<Student>>& roster) {
   for(const auto& courseList : roster){
      printRoster(courseList);
   }
}

void readDropouts(list<Student>& dropouts, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last){
      dropouts.emplace_back(first, last);
   }
   course.close();
}

void printDropouts(const list<Student>& dropouts){
   for(const auto& dropout : dropouts) {
      cout << dropout.print() << endl;
   }
}
