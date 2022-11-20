#include <iostream>
#include "Searcher/InFileSearcher.h"
#include <gtest/gtest.h>

std::string arg;

TEST(fileload, basic_char){
    InFileSearcher elem_finder(arg);
    std::cout << elem_finder.GetFileData() << '\n';
}

TEST(fileload, utf_symbols){
    InFileSearcher elem_finder(arg);
    std::cout << elem_finder.GetFileData() << '\n';
}

TEST(searching, async_mode){
    InFileSearcher elem_finder(arg);
    std::vector<size_t> positions = elem_finder.Find("ゔぁ");
    elem_finder.PrintFindedPositions(positions);
    //std::vector<size_t> assert_positions;
}

TEST(searching, sync_mode){
    InFileSearcher elem_finder(arg);
    std::vector<size_t> positions = elem_finder.Find("sync", "BANDIT");
    elem_finder.PrintFindedPositions(positions);
    //std::vector<size_t> assert_positions;
}

TEST(warnings, unknown_mode){
    InFileSearcher elem_finder(arg);
    std::vector<size_t> positions = elem_finder.Find("1", "BANDIT");
    elem_finder.PrintFindedPositions(positions);
}

TEST(exceptions, filepath_error){
    InFileSearcher elem_finder("");
}

int main(int argc, char **argv) {
    arg = argv[1];
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}