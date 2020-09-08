//
// Created by 42kangaroo on 15.08.20.
//

#ifndef SETTINGS_CSVFILEHANDLER_HPP
#define SETTINGS_CSVFILEHANDLER_HPP

#include <string>
#include <vector>
#include <fstream>

namespace Lily {
    class csvFileHandler {
        std::fstream file_;
        std::string filename_;
        int numCategories_;

        /**
         * gets the index of the category. throws invalid_argument if category not valid
         * @param category the category as string
         * @return the index of the category in a vector
         */
        int getCategoriesColumn(const std::string &category);

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
         * finds the first occurrence of the search in the column label
         * @param label the label of which to search
         * @param search the search text
         * @return the index of the found item
         */
        int find_index(const std::string &label, const std::string &search);

        /**
         * finds all the occurrences of the search in the column label
         * @param label
         * @param search the label of which to search
         * @return a vector of vectors with all the rows found
         */
        std::vector<std::vector<std::string>> find_all(const std::string &label, const std::string &search);

        /**
         * deletes the first row in which the search with the label finds it
         * @param label the label in wich to search for delete
         * @param deleteSearch the text to search for wich will be deleted
         */
        void delete_row(const std::string &label, const std::string &deleteSearch);

        /**
         * deletes the row at the index
         * @param index the index in the file, starting at 0 for the first data row
         */
        void delete_row(int index);

        /**
         * deletes all the rows in which the search with the label finds it
         * @param label the label in wich to search for delete
         * @param deleteSearch the text to search for wich will be deleted
         */
        void delete_rows(const std::string &label, const std::string &deleteSearch);

        /**
         * change the row with index at the column label set newVal
         * @param index the index of the row
         * @param label the labe of the column
         * @param newVal the new value
         */
        void change_row(int index, const std::string &label, std::string newVal);

        /**
         * change the row oldVector at the column label set newVal
         * @param oldVector the vector of the old row
         * @param label the labe of the column
         * @param newVal the new value
         */
        void change_row(const std::vector<std::string> &oldVector, const std::string &label, std::string newVal);
    };
}

#endif //SETTINGS_CSVFILEHANDLER_HPP
