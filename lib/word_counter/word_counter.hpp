#ifndef WORD_COUNTER_HPP
#define WORD_COUNTER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <tuple>


class WordCounterError : public std::exception {
     private:
        std::string errorMessage;
     public:
        explicit WordCounterError(const std::string &message): errorMessage(message) {}
        const char* what() const noexcept override {
            return errorMessage.c_str();
        }
};


class StringHelper {
public:
    static void toLowercase(std::string& s);
    static void removeNonAlnum(std::string& s);
    static std::string capitalize(const std::string& s);
    static std::string alignRight(const std::string& s, size_t width);
};

class WordCounter {

     private:
        void parseWord(std::string &word);

     public:
        explicit WordCounter(std::string inputFile = "in.txt",
                              std::string outputFile = "out.csv");
        virtual void read();

        void calculate();

        virtual void write();

        ~WordCounter();

     private:
        struct WordInfo {
            std::string word;
            size_t count;
            double percentage;
        };

        static const size_t PRESICTION_VALUE = 6;
        static const size_t ONE_HUNDRED_PERSENT = 100;

        std::ifstream in;
        std::ofstream out;
        std::vector <std::string> words;
        std::map <std::string, size_t> countOfWords;
        std::vector<WordInfo> wordList;
};

#endif