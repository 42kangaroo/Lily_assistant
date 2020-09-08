//
// Created by 42kangaroo on 15.08.20.
//

#include <sstream>
#include <algorithm>
#include <utility>
#include "csvFileHandler.hpp"

namespace Lily {
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
        file_.clear();
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
        int column = getCategoriesColumn(label);
        auto fileData = getWholeFile();
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
        int column = getCategoriesColumn(label);
        auto fileData = getWholeFile();
        auto foundIndex = std::find_if(fileData.cbegin() + 1, fileData.cend(),
                                       [column, search](const std::vector<std::string> &row) {
                                           return row.at(column).find(search) != std::string::npos;
                                       });
        if (foundIndex == fileData.end()) {
            throw std::invalid_argument("the string was not found");
        }
        return *foundIndex;
    }

    std::vector<std::vector<std::string>>
    csvFileHandler::find_all(const std::string &label, const std::string &search) {
        int column = getCategoriesColumn(label);
        auto fileData = getWholeFile();
        auto foundIndex = fileData.cbegin();
        std::vector<std::vector<std::string>> foundVector{};
        while (foundIndex != fileData.cend()) {
            foundIndex = std::find_if(foundIndex + 1, fileData.cend(),
                                      [column, search](const std::vector<std::string> &row) {
                                          return row.at(column).find(search) != std::string::npos;
                                      });
            if (foundIndex != fileData.cend()) {
                foundVector.emplace_back(*foundIndex);
            }
        }
        if (foundVector.empty()) {
            throw std::invalid_argument("the string was not found");
        }
        return foundVector;
    }

    void csvFileHandler::delete_row(const std::string &label, const std::string &deleteSearch) {
        int column = getCategoriesColumn(label);
        auto fileData = getWholeFile();
        auto foundIndex = std::find_if(fileData.cbegin() + 1, fileData.cend(),
                                       [column, deleteSearch](const std::vector<std::string> &row) {
                                           return row.at(column).find(deleteSearch) != std::string::npos;
                                       });
        fileData.erase(foundIndex);
        rewriteFile(fileData);
    }

    int csvFileHandler::getCategoriesColumn(const std::string &category) {
        int column{0};
        auto categories = getCategories();
        for (const auto &label : categories) {
            if (label == category) {
                break;
            }
            column++;
        }
        if (column == categories.size()) {
            throw std::invalid_argument("category not found");
        }
        return column;
    }

    void csvFileHandler::delete_row(int index) {
        auto fileData = getWholeFile();
        fileData.erase(fileData.cbegin() + index + 1);
        rewriteFile(fileData);
    }

    void csvFileHandler::delete_rows(const std::string &label, const std::string &deleteSearch) {
        int column = getCategoriesColumn(label);
        auto fileData = getWholeFile();
        auto foundIndex = fileData.cbegin() + 1;
        while (foundIndex != fileData.cend()) {
            foundIndex = std::find_if(foundIndex, fileData.cend(),
                                      [column, deleteSearch](const std::vector<std::string> &row) {
                                          return row.at(column).find(deleteSearch) != std::string::npos;
                                      });
            if (foundIndex != fileData.cend()) {
                fileData.erase(foundIndex);
            }
        }
        rewriteFile(fileData);
    }

    void csvFileHandler::change_row(int index, const std::string &label, std::string newVal) {
        auto fileData = getWholeFile();
        int column = getCategoriesColumn(label);
        fileData.at(index + 1).at(column) = std::move(newVal);
        rewriteFile(fileData);
    }

    void csvFileHandler::change_row(const std::vector<std::string> &oldVector, const std::string &label,
                                    std::string newVal) {
        auto fileData = getWholeFile();
        int column = getCategoriesColumn(label);
        auto referenceVector = std::find(fileData.begin() + 1, fileData.end(), oldVector);
        referenceVector->at(column) = std::move(newVal);
        rewriteFile(fileData);
    }

    int csvFileHandler::find_index(const std::string &label, const std::string &search) {
        int column = getCategoriesColumn(label);
        auto fileData = getWholeFile();
        auto foundIndex = std::find_if(fileData.cbegin() + 1, fileData.cend(),
                                       [column, search](const std::vector<std::string> &row) {
                                           return row.at(column).find(search) != std::string::npos;
                                       });
        if (foundIndex == fileData.cend()) {
            throw std::invalid_argument("the string was not found");
        }
        return std::distance(fileData.cbegin(), foundIndex) - 1;
    }
}