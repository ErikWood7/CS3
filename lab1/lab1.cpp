// Erik Wood
// Lab1 due 8/30/24

#include <string> 
#include <iostream>
#include <fstream>

using std::cout; using std::endl;

void comparelines(const std::string& file1, const std::string& file2) {
    std::ifstream infile1(file1);
    std::ifstream infile2(file2);
    
    std::string line1, line2;

    int linenum = 0; // used for tracking line number.

    while(std::getline(infile1, line1) && std::getline(infile2, line2)){
        linenum++;

        if(line1 != line2){ //if statement used to check if the lines are not the same.

            cout << file1  << ": " << linenum << ": " << line1 << endl;
            cout << file2  << ": " << linenum << ": " << line2 << endl;
            std:: string linemessage = ": " + std::to_string(linenum) + ": "; 
            
            int minlength = std::min(line1.length(), line2.length()); // var created to to be the shortest of the two lines

            int i = 0;
            while(i <= minlength){
                if(line1[i] != line2[i]) {
                    std::string stringspace; 
                    stringspace.assign(i + linemessage.length() + file1.length(), ' ');
                    stringspace += '^';
                    cout << stringspace << endl;
                    break;
                }
                i++;
            }
        }
    }

    while (std::getline(infile1, line1)) {
        linenum++;
        std::cout << file1 << ": " << linenum << ": " << line1;
        if(!infile1.eof()){
            std::cout << std::endl;
        }
    }

    while (std::getline(infile2, line2)) {
        linenum++;
        std::cout << file2 << ": " << linenum << ": " << line2;
        if(!infile2.eof()){
            std::cout << std::endl;
        }
    }

    infile1.close();
    infile2.close();
}

// std::to_string


int main(int argc, char* argv[]){
    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << "<file1> <file2>" << std::endl;
        return 1;
    } 

    const std::string file1(argv[1]); 
    const std::string file2(argv[2]);

    comparelines(file1, file2);

}
