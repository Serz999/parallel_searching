#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include <future>

class InFileSearcher {
public:
    InFileSearcher();

    InFileSearcher(const std::string &filepath);

    void SetFileData(const std::string &filepath);

    std::string GetFileData();

    std::vector<size_t> Find(const std::string &mode, const std::string &element);

    std::vector<size_t> Find(const std::string &element);

    void PrintFindedPositions(std::vector<size_t> &finded_positions);

private:
    std::string file_data;

    std::string LoadFileData(const std::string &filepath);
};