#include "InFileSearcher.h"

InFileSearcher::InFileSearcher(const std::string &filepath) {
    SetFileData(filepath);
}

void InFileSearcher::SetFileData(const std::string &filepath) {
    file_data = LoadFileData(filepath);
}

std::string InFileSearcher::GetFileData() {
    return file_data;
}

std::string InFileSearcher::LoadFileData(const std::string &filepath) {
    std::string file_data;
    std::ifstream ifs(filepath);
    if(ifs.is_open()){
        size_t filesize;
        ifs.seekg(0, std::ios::end);
        filesize = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        file_data.resize(filesize);
        ifs.read(file_data.data(), filesize);
    } else throw std::runtime_error("error:file is not found!");
    return file_data;
}

std::vector<size_t> InFileSearcher::Find(const std::string &element) {
    return Find("async", element);
}

std::vector<size_t> InFileSearcher::Find(const std::string &mode, const std::string &element) {
    std::vector<size_t> finded_positions;
    if(mode == "sync"){
        for(size_t i = 0; i < file_data.size(); i++){
            for(size_t j = 0; j < element.size(); j++){
                if(file_data[i] != element[j]) break;
                i++;
                if(j == element.size() - 1) finded_positions.push_back(i - element.size());
            }
        }
        return finded_positions;
    } else if (mode == "async") {
        std::mutex mtx;
        auto search_process = [this, &mtx, element, &finded_positions](const size_t start_idx, const size_t step){
            for(size_t i = start_idx; i < file_data.size(); i+=step){
                for(size_t j = 0, k = i; j < element.size(); j++){
                    if(file_data[k] != element[j]) break;
                    k++;
                    std::lock_guard<std::mutex> lock(mtx);
                    if(j == element.size() - 1) finded_positions.push_back(i);
                }
            }
        };
        const size_t max_thread_count = std::thread::hardware_concurrency();
        std::vector<std::future<void>> threads(max_thread_count - 1);
        for(size_t i = 0; i < max_thread_count - 1; i++){
            threads[i] = std::async(search_process, i, max_thread_count - 1);
        }
        return finded_positions;
    } else {
        std::cout << "unknown mode, start default mode(async)";
        Find("async", element);
    }
}

void InFileSearcher::PrintFindedPositions(std::vector<size_t> finded_positions) {
    std::sort(finded_positions.begin(), finded_positions.end());
    for(int i = 0; i < finded_positions.size(); i++){
        std:: cout << finded_positions[i];
        if(i != finded_positions.size() - 1) std::cout << ", ";
    }
}