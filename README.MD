This program counts the words in the specified txt file and outputs the result to the specified csv file in the form of a table:
1) Word
2) Frequency
3) Frequency as a percentage

Compile: g++ -std=c++11 -o word_counter bin/main.cpp lib/word_counter/word_counter.cpp -I.
Create input and output files
Add text into input file
Run: word_counter.exe input.txt output.txt
