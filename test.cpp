#include <iostream>
#include "Searcher/InFileSearcher.h"
#include <gtest/gtest.h>

std::string init_data;
std::string unicode_init_data;

TEST(fileload, initial_test){
    InFileSearcher elem_finder("data.tmp");
    ASSERT_EQ(init_data, elem_finder.GetFileData());
}

TEST(searching, async_mode){
    InFileSearcher elem_finder("data.tmp");
    std::vector<size_t> positions = elem_finder.Find("word");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {0, 16, 30, 35, 47};
    ASSERT_EQ(positions, assert_positions);
}

TEST(searching, sync_mode){
    InFileSearcher elem_finder("data.tmp");
    std::vector<size_t> positions = elem_finder.Find("sync", "word");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {0, 16, 30, 35, 47};
    ASSERT_EQ(positions, assert_positions);
}

TEST(warnings, unknown_mode){
    InFileSearcher elem_finder("data.tmp");
    std::vector<size_t> positions = elem_finder.Find("special_mode", "word");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {0, 16, 30, 35, 47};
    ASSERT_EQ(positions, assert_positions);
}

TEST(searching, unicode_handling){
    InFileSearcher elem_finder("unicode_data.tmp");
    std::vector<size_t> positions = elem_finder.Find("мир!");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {13, 51};
    ASSERT_EQ(positions, assert_positions);
}

TEST(exceptions, filepath_error){
    ASSERT_ANY_THROW({
        InFileSearcher elem_finder("incorrect_filepath");
    });
}

int main(int argc, char **argv) {
    init_data = "word aasdasdasd word asdasdas word word awdawd word";
    unicode_init_data = "привет мир! прощай жестокий мир!";
    std::ofstream ofs("data.tmp");
    ofs << init_data;
    ofs.close();
    ofs.open("unicode_data.tmp");
    ofs << unicode_init_data;
    ofs.close();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}