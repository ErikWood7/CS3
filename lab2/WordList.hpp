// Erik Wood
// Due  9/6/2024


#ifndef _LAB2_HPP_
#define _LAB2_HPP_

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using std::string;

class WordOccurrence {
public:
    WordOccurrence(const string& word="", int num=0) : word_(word), num_(num) {}

    bool matchWord(const string &str){ return word_ == str; } 
    // returns true if word matches stored

    void increment(){ num_++; } // increments number of occurrences

    string getWord() const{ return word_; }

    int getNum() const{ return num_; }

private:
    string word_;
    int num_;
};

class WordList{
public:

    WordList() : wordArray_(nullptr), size_(0) {} // defualt constructor

    ~WordList(); // destructor 

    WordList(const WordList &rhs); // Copy constructor

    
    WordList& operator=(WordList rhs); // assignment operator
    

    friend bool equal(const WordList&, const WordList&);


    void addWord(const string &word);
    
    void print();

    // Only use for testing purposes
    WordOccurrence * getWords() const {return wordArray_;};
    int getSize() const {return size_;};
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};


#endif