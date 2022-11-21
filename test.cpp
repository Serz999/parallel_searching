#include <iostream>
#include "Searcher/InFileSearcher.h"
#include <gtest/gtest.h>

std::string init_data;

TEST(fileload, initial_test){
    InFileSearcher elem_finder("tmp_data.txt");
    ASSERT_EQ(init_data, elem_finder.GetFileData());
}

TEST(searching, async_mode){
    InFileSearcher elem_finder("tmp_data.txt");
    std::vector<size_t> positions = elem_finder.Find("РУССКИЙ ТЕКСТ");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {0, 20, 39, 64};
    ASSERT_EQ(positions, assert_positions);
}

TEST(searching, sync_mode){
    InFileSearcher elem_finder("tmp_data.txt");
    std::vector<size_t> positions = elem_finder.Find("sync", "РУССКИЙ ТЕКСТ");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {0, 20, 39, 64};
    ASSERT_EQ(positions, assert_positions);
}

TEST(warnings, unknown_mode){
    InFileSearcher elem_finder("tmp_data.txt");
    std::vector<size_t> positions = elem_finder.Find("mode", "РУССКИЙ ТЕКСТ");
    elem_finder.PrintFindedPositions(positions);
    std::vector<size_t> assert_positions = {0, 20, 39, 64};
    ASSERT_EQ(positions, assert_positions);
}

TEST(exceptions, filepath_error){
    ASSERT_ANY_THROW({
        InFileSearcher elem_finder("incorrect_filepath");
    });
}

int main(int argc, char **argv) {
    init_data = "РУССКИЙ ТЕКСТ слово РУССКИЙ ТЕКСТ\n"
                "буквы РУССКИЙ ТЕКСТ много слов РУССКИЙ ТЕКСТ";
    std::ofstream ofs("tmp_data.txt");
    ofs << init_data;
    ofs.close();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}