//Erik Wood
// Main file


#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iterator>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(vector<list<string>>& studentEntries, string fileName);  

void readDropouts(list<string>& dropouts, string fileName);

// printing a list out
void printRoster(const vector<list<string>>& roster); 

void mergeStudentEntries(vector<list<string>>& allStudents, vector<list<string>>& courseStudents);

void removeDropouts(vector<list<string>>& allStudents, const list<string>& dropouts);

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl;
      exit(1);
   }

   // vector of courses of students
   vector <list<string>> courseStudents; 
   for(int i = 1; i < argc-1; i++){
      readRoster(courseStudents, argv[i]);
   }
  
   list<string> dropouts;
   readDropouts(dropouts, argv[argc-1]); // reading in dropouts

   // master list of students
   vector<list<string>> allStudents = move(courseStudents);


   mergeStudentEntries(allStudents, courseStudents); // sorts and removes duplicates in each student's course
   removeDropouts(allStudents, dropouts); // removes dropouts

   cout << "\n\n all students, dropouts removed \n"; 
   printRoster(allStudents);
   
}

// reading in a file of names into a list of strings
void readRoster(vector<list<string>>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   string courseName = fileName.substr(0, fileName.find("."));

   while(course >> first >> last){
      bool studentFound = false;
      string fullname = first + " " + last;

      for (auto& student: roster) { // goes through all elements in roster
         if(student.front() == (fullname)){
            student.push_back(courseName);
            studentFound = true;
            break;
         }
      }

      if(!studentFound){ // if no student is found then create a new element and push it into student entries
         list<string> newStudent = {fullname, courseName};
         roster.push_back(newStudent);
      }
   }
}


// printing a list out
void printRoster(const vector<list<string>>& roster){
   for(const auto& student: roster){
      for(const auto& entry : student){
         cout << entry << ' ';
      }
      cout << endl;
   }
}

void mergeStudentEntries(vector<list<string>>& allStudents, vector<list<string>>& courseStudents){

   std::sort(allStudents.begin(), allStudents.end(), [](const list<string>& a, const list<string>& b){
      return a.front() < b.front();// sort by alphabetical
   });

   for(size_t i = 0; i < allStudents.size()-1; ){
      if(allStudents[i].front() == allStudents[i+1].front()){ // checking if they are the same student
         allStudents[i].insert(allStudents[i].end(), ++allStudents[i+1].begin(), allStudents[i+1].end());
         allStudents.erase(allStudents.begin() + i + 1); // remove duplicate entries
      } else {
         i++;
      }
   }
}

void removeDropouts(vector<list<string>>& allStudents, const list<string>& dropouts){
   for (auto it = allStudents.begin(); it != allStudents.end();) {
      if (std::find(dropouts.begin(), dropouts.end(), it->front()) != dropouts.end()) { // if the iterator is not pointing at the end of the dropouts list then there is a dropout
         it = allStudents.erase(it);
      } else {
         it++;
      }
   }
}

void readDropouts(list<string>& dropouts, string fileName){
   ifstream course(fileName);
   string first, last;

   while(course >> first >> last){
      dropouts.push_back(first + " " + last);
   }
}