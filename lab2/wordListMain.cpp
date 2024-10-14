// Erik Wood
// Due 9/6/2024

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include "WordList.hpp"


using std::cout; using std::endl;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }

    WordList wordList;

    string word;
    while (inputFile >> word) {
        wordList.addWord(word);
    }

    wordList.print();

    inputFile.close();
    return 0;
}

WordList::~WordList(){
    delete[] wordArray_;
    wordArray_ = nullptr;
    size_ = 0;
}

WordList::WordList(const WordList &rhs) : WordList() {
    if(rhs.size_ > 0){
            wordArray_ = new WordOccurrence[rhs.size_];
            size_ = rhs.size_;
            for(int i = 0; i < size_; i++){ wordArray_[i] = rhs.wordArray_[i];}
        }
}

WordList& WordList::operator=(WordList rhs) {
    if(this != &rhs){
            delete[] wordArray_;
            wordArray_ = nullptr;
            size_ = 0;
            if(rhs.size_ > 0){
            wordArray_ = new WordOccurrence[rhs.size_];
            size_ = rhs.size_;
            for(int i = 0; i < size_; i++){ wordArray_[i] = rhs.wordArray_[i];}
            }
        }
        return *this;
}

void WordList::addWord(const string &word){
    string changedWord = word; // creating a var to change the word to account for punctuation's in the word.
        changedWord.erase(remove_if(changedWord.begin(), changedWord.end(), ::ispunct), changedWord.end()); // removes the punction from the word.

        for(int i = 0; i < size_; i++) { // checks if the word is in the current array.
            if(wordArray_[i].matchWord(changedWord)){
                wordArray_[i].increment();
                return;
            }
        }

        // if it is not create another array with an extra space.
        WordOccurrence *newArray = new WordOccurrence[size_ + 1];

        for(int i = 0; i < size_; i++){ // assign the old array to the new one.
            newArray[i] = wordArray_[i];
        }
        // puts the new word into the array, with a WordOccurrence counter on it.
        newArray[size_] = WordOccurrence(changedWord, 1);

        delete[] wordArray_;
        wordArray_ = newArray;
        size_++;
}

void WordList::print(){
    std::sort(wordArray_, wordArray_ + size_, [](const WordOccurrence& a, const WordOccurrence& b) {
            if(a.getNum() != b.getNum()){
                return a.getNum() < b.getNum();
            }else{
                return a.getWord() < b.getWord();
            }
            
        });
        
        for(int i = 0; i < size_; i++){
            if(wordArray_[i].getWord() == ""){
                continue;
            }
            else{
                std::cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum() << std::endl;
            }
        }
}


bool equal(const WordList& a, const WordList& b) {
    if (a.size_ != b.size_) { // if they are no the same size then it must be false
        return false;
    }
    for (int i = 0; i < a.size_; i++) {
        if (!a.wordArray_[i].matchWord(b.wordArray_[i].getWord()) || a.wordArray_[i].getNum() != b.wordArray_[i].getNum()) {
            return false;
        }
    }
    return true;
}


