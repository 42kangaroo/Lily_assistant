//
// Created by 42kangaroo on 15.08.20.
//

#ifndef SETTINGS_CSVFILEHANDLER_HPP
#define SETTINGS_CSVFILEHANDLER_HPP

#include <string>
#include <vector>
#include <fstream>

class csvFileHandler {
    std::fstream file_;
    std::string filename_;
    int numCategories_;
public:

    /**
     * create file with name filename and a list of labels. If file exists, it will be overwritten
     * @param filename the filename
     * @param labels a vector of labels for the data
     */
    csvFileHandler(const std::string &filename, const std::vector<std::string> &labels);

    /**
     * opens the csv file
     * @param filename
     */
    explicit csvFileHandler(const std::string &filename);

    /**
     * get the whole file content in form of a double vector of strings
     * @return the whole file
     */
    std::vector<std::vector<std::string>> getWholeFile();

    /**
     * returns the next row of the file as vector;
     * @return a vector of std::string
     */
    std::vector<std::string> getNextRow();

    /**
     * returns the categories in the first row
     * @return a vector of std::string
     */
    std::vector<std::string> getCategories();

    /**
     * get whole file without the categories
     * @return the data
     */
    std::vector<std::vector<std::string>> getData();

    /**
     * write a row at the end of file
     * @param data a vector of the data
     */
    void writeRow(const std::vector<std::string> &data, std::ios::pos_type = std::ios::end);

    /**
     * sort the rows by one of the labels
     * @param label
     */
    void sort(const std::string &label);

    /**
     * delete the file and rewrite its whole content
     * @param fileData the new content
     */
    void rewriteFile(const std::vector<std::vector<std::string>> &fileData);

    /**
     * finds the first occurrence of the search in the column label
     * @param label the label of which to search
     * @param search the search text
     * @return a vector with the the row of the found index
     */
    std::vector<std::string> find(const std::string &label, const std::string &search);

    /**
     * finds all the occurrences of the search in the column label
     * @param label
     * @param search the label of which to search
     * @return a vector of vectors with all the rows found
     */
    std::vector<std::vector<std::string>> find_all(const std::string &label, const std::string &search);
};


#endif //SETTINGS_CSVFILEHANDLER_HPP
