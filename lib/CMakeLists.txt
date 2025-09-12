add_library(wc_lib
    ./word_counter/word_counter.cpp
    ./word_counter/word_counter.hpp
)

set_target_properties(wc_lib PROPERTIES LINKER_LANGUAGE CXX)