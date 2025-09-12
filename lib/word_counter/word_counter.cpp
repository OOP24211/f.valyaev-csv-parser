#include <iomanip>

#include "word_counter.hpp"

void StringHelper::toLowercase(std::string& s) {
    for (char& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
}

void StringHelper::removeNonAlnum(std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(),
        [](unsigned char c) { return !std::isalnum(c); }),
        s.end());
}

std::string StringHelper::capitalize(const std::string& s) {
    if (s.empty()) return s;
    std::string result = s;
    result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
    return result;
}

std::string StringHelper::alignRight(const std::string& s, size_t width) {
    if (s.size() >= width) return s;
    return s + std::string(width - s.size(), ' ');
}

WordCounter::WordCounter(std::string inputFile, std::string outputFile) {

    in.open(inputFile);
    if (!in.is_open()) {
        throw WordCounterError{"ERROR: word_counter.cpp: Input file " + inputFile + " can't be open\n"};
    }

    out.open(outputFile);
    if (!out.is_open()) {
        throw WordCounterError{"ERROR: word_counter.cpp: Output file " + outputFile + " can't be open\n"};
    }
}

WordCounter::~WordCounter() {
    in.close();
    out.close();
}


void WordCounter::parseWord(std::string &word) {
    StringHelper::toLowercase(word);
    StringHelper::removeNonAlnum(word);
}

void WordCounter::read() {
    std::string str;

    while (in >> str) {
        parseWord(str);
        words.push_back(str);
    }
}

void WordCounter::calculate() {
    size_t largestWordSize = 0;

    for (const auto &word : words) {
        largestWordSize = std::max(word.size(), largestWordSize);
        countOfWords[word]++;
    }

    for (const auto& [word, count] : countOfWords) {
        WordInfo info;
        info.word = StringHelper::alignRight(StringHelper::capitalize(word), largestWordSize);
        info.count = count;
        info.percentage = (static_cast<double>(count) / words.size()) * ONE_HUNDRED_PERSENT;
        wordList.push_back(info);
    }

    std::sort(wordList.begin(), wordList.end(),
    [](const WordInfo &a, const WordInfo &b) {
        return a.count > b.count;
    });
}

void WordCounter::write() {
    for (const auto& info : wordList) {
        out << info.word << " " << info.count << " "
        << std::setprecision(PRESICTION_VALUE) << info.percentage << "%"
        << std::endl;
    }
}

