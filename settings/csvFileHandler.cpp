//
// Created by 42kangaroo on 15.08.20.
//

#include <sstream>
#include <algorithm>
#include "csvFileHandler.hpp"

csvFileHandler::csvFileHandler(const std::string &filename, const std::vector<std::string> &labels) : filename_(
        filename) {
    file_.open(filename, std::ios::out | std::ios::trunc);
    if (file_.bad()) {
        throw std::runtime_error("filename is not valid, or file couldn't be opened");
    }
    numCategories_ = labels.size();
    writeRow(labels, std::ios::beg);
    file_.close();
    file_.open(filename, std::ios::out | std::ios::app | std::ios::in);
}

std::vector<std::vector<std::string>> csvFileHandler::getWholeFile() {

    std::vector<std::vector<std::string>> wholeFile{};
    file_.clear();
    file_.seekg(std::ios::beg);
    do {
        wholeFile.push_back(getNextRow());
    } while (!(wholeFile.back().empty()));
    wholeFile.pop_back();
    return wholeFile;
}

csvFileHandler::csvFileHandler(const std::string &filename) : filename_(filename) {
    file_.open(filename, std::ios::in | std::ios::out | std::ios::app);

    if (file_.bad()) {
        throw std::runtime_error("filename is not valid, or file couldn't be opened");
    }
    numCategories_ = getCategories().size();
}

std::vector<std::string> csvFileHandler::getNextRow() {
    std::vector<std::string> row{};
    std::string line;
    std::string cell;
    if (file_.bad()) {
        throw std::runtime_error("filestream is corrupted");
    }
    std::getline(file_, line);
    if (line.empty()) {
        return row;
    }
    std::stringstream lineStream{line};
    while (std::getline(lineStream, cell, ',')) {
        row.push_back(cell);
    }
    return row;
}

std::vector<std::string> csvFileHandler::getCategories() {
    file_.seekg(std::ios::beg);
    return getNextRow();
}

std::vector<std::vector<std::string>> csvFileHandler::getData() {
    auto wholeFile = getWholeFile();
    wholeFile.erase(wholeFile.begin());
    return wholeFile;
}

void csvFileHandler::writeRow(const std::vector<std::string> &data, std::ios::pos_type pos) {
    std::string dataRow{};
    if (data.size() != numCategories_) {
        throw std::invalid_argument("wrong size of row");
    }
    for (const auto &item: data) {
        dataRow += item + ",";
    }
    dataRow.erase(dataRow.find_last_of(','));
    file_.seekg(pos);
    file_ << dataRow << "\n";
}

void csvFileHandler::sort(const std::string &label) {
    int column{0};
    auto fileData = getWholeFile();
    auto categories = fileData.at(0);
    for (const auto &category : categories) {
        if (label == category) {
            break;
        }
        column++;
    }
    if (column == categories.size()) {
        throw std::invalid_argument("category not found");
    }
    std::sort(fileData.begin() + 1, fileData.end(), [column](const auto &left, const auto &right) {
        return left.at(column) < right.at(column);
    });
    rewriteFile(fileData);

}

void csvFileHandler::rewriteFile(const std::vector<std::vector<std::string>> &fileData) {
    file_.close();
    std::remove(filename_.c_str());
    file_.open(filename_, std::ios::out | std::ios::app | std::ios::in);

    if (!file_) {
        throw std::runtime_error("filename is not valid, or file couldn't be opened");
    }

    for (const auto &row : fileData) {
        writeRow(row);
    }
}

std::vector<std::string> csvFileHandler::find(const std::string &label, const std::string &search) {
    int column{0};
    auto fileData = getWholeFile();
    auto categories = fileData.at(0);
    for (const auto &category : categories) {
        if (label == category) {
            break;
        }
        column++;
    }
    if (column == categories.size()) {
        throw std::invalid_argument("category not found");
    }
    auto foundIndex = std::find_if(fileData.cbegin() + 1, fileData.cend(),
                                   [column, search](const std::vector<std::string> &row) {
                                       return row.at(column).find(search) != std::string::npos;
                                   });
    if (foundIndex == fileData.end()) {
        return std::vector<std::string>{};
    }
    return *foundIndex;
}

std::vector<std::vector<std::string>> csvFileHandler::find_all(const std::string &label, const std::string &search) {
    int column{0};
    auto fileData = getWholeFile();
    auto categories = fileData.at(0);
    for (const auto &category : categories) {
        if (label == category) {
            break;
        }
        column++;
    }
    if (column == categories.size()) {
        throw std::invalid_argument("category not found");
    }
    auto foundIndex = fileData.cbegin();
    std::vector<std::vector<std::string>> foundVector{};
    while (foundIndex != fileData.end()) {
        foundIndex = std::find_if(foundIndex + 1, fileData.cend(),
                                  [column, search](const std::vector<std::string> &row) {
                                      return row.at(column).find(search) != std::string::npos;
                                  });
        foundVector.emplace_back(*foundIndex);
    }
    return foundVector;
}
