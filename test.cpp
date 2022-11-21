#include <iostream>
#include <gtest/gtest.h>
#include "Searcher/InFileSearcher.h"
#include "SimpleTimer/SimpleTimer.h"

std::string init_data;
std::string unicode_init_data;
SimpleTimer timer("../README.md");

TEST(fileload, initial_test){
    InFileSearcher elem_finder("data.tmp");
    ASSERT_EQ(init_data, elem_finder.GetFileData());
}

TEST(searching, async_mode){
    std::ofstream ofs("../README.md");
    ofs.close();
    InFileSearcher elem_finder("data.tmp");
    timer.Start();
    std::vector<size_t> positions = elem_finder.Find("word");
    timer.Stop("## [small data] async_mode");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {0, 16, 30, 35, 47};
    ASSERT_EQ(positions, assert_positions);
}

TEST(searching, sync_mode){
    InFileSearcher elem_finder("data.tmp");
    timer.Start();
    std::vector<size_t> positions = elem_finder.Find("sync", "word");
    timer.Stop("## [small data] sync_mode");
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

TEST(searching, async_generate_statistic){
    ASSERT_NO_FATAL_FAILURE({
        InFileSearcher elem_finder("../HarryPotter.txt");
        timer.Start();
        std::vector<size_t> positions = elem_finder.Find("Harry");
        timer.Stop("## [big data] async_mode");
        elem_finder.PrintFindedPositions(positions);
    });
}

TEST(searching, sync_generate_statistic){
    ASSERT_NO_FATAL_FAILURE({
        InFileSearcher elem_finder("../HarryPotter.txt");
        timer.Start();
        std::vector<size_t> positions = elem_finder.Find("sync", "Harry");
        timer.Stop("## [big data] sync_mode");
        elem_finder.PrintFindedPositions(positions);
    });
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