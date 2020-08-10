//
// Created by 42kangaroo on 23.04.20.
//


#include "Dictionary_txt.hpp"
namespace {
    bool beginning = true;
    std::stringstream getDic() {
        std::ifstream dic_file("/home/pi/C-Programmes/listen/dictcionary.txt");
        if (!dic_file) {
            throw std::runtime_error("could not open dictionary.txt");
        }
        std::stringstream sstr;
        sstr << dic_file.rdbuf();
        dic_file.close();
        return sstr;
    }
    std::stringstream oldStrStr = getDic();
    /**
     * helping function to reload the dic
     */
    std::size_t callback(
            const char *in,
            std::size_t size,
            std::size_t num,
            std::string *out) {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
    /**
     * helping function to reload the dic
     */
    std::size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
        size_t written = fwrite(ptr, size, nmemb, (FILE *) stream);
        return written;
    }

}
namespace Lily{
    namespace Dictionary_txt {
        void addToDic(std::string text) {
            std::replace(text.begin(), text.end(), ',', ' ');
            if (beginning) {
                remove("/home/pi/C-Programmes/listen/dictcionary.txt");
                beginning = false;
            }
            std::ofstream dicfile;
            dicfile.open("/home/pi/C-Programmes/listen/dictcionary.txt", std::ios::out | std::ios::app);
            if (!dicfile) {
                throw std::runtime_error("couldn't open dictioary file");
            }
            dicfile << text << std::endl;
            dicfile.close();
        }

        void reload_dic() {
            CURL *curl;
            CURLcode res;

            curl_mime *form = NULL;
            curl_mimepart *field = NULL;
            struct curl_slist *headerlist = NULL;
            static const char buf[] = "Expect:";
            res = curl_global_init(CURL_GLOBAL_ALL);
            if (res != CURLE_OK){
                throw std::runtime_error("couldn't init curl");
            }
            static const char *lmfilename = "/home/pi/C-Programmes/listen/lm_file.lm";
            FILE *lmfile;
            static const char *dicfilename = "/home/pi/C-Programmes/listen/dic_file.dic";
            FILE *dicfile;

            curl = curl_easy_init();
            if (curl) {
                /* Create the form */

                form = curl_mime_init(curl);

                /* Fill in the file upload field */
                field = curl_mime_addpart(form);
                curl_mime_name(field, "corpus");
                curl_mime_filedata(field, "/home/pi/C-Programmes/listen/dictcionary.txt");

                /* Fill in the submit field too, even if this is rarely needed */
                field = curl_mime_addpart(form);
                curl_mime_name(field, "formtype");
                curl_mime_data(field, "simple", CURL_ZERO_TERMINATED);

                /* initialize custom header list (stating that Expect: 100-continue is not
                   wanted */
                headerlist = curl_slist_append(headerlist, buf);
                std::unique_ptr<std::string> httpData(new std::string());

                /* what URL that receives this POST */
                curl_easy_setopt(curl, CURLOPT_URL, "http://www.speech.cs.cmu.edu/cgi-bin/tools/lmtool/run/");
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

                curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

                /* Perform the request, res will get the return code */
                res = curl_easy_perform(curl);
                if (res != CURLE_OK){
                    throw std::runtime_error("couldn't perform run request");
                }
                const char *urlString;
                curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &urlString);
                auto pos = httpData->find("TAR");
                pos += 3;
                std::string numbers = httpData->substr(pos, 4);
                std::string lm_location = urlString + numbers + ".lm";
                std::string dict_location = urlString + numbers + ".dic";
                std::cout << lm_location << std::endl << dict_location << std::endl;
                /* Check for errors */
                curl_easy_reset(curl);
                curl_easy_setopt(curl, CURLOPT_URL, lm_location.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                lmfile = fopen(lmfilename, "wb");
                if (lmfile) {
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, lmfile);
                    res = curl_easy_perform(curl);
                    if (res != CURLE_OK) {
                        throw std::runtime_error("couldn't perform run request");
                    }
                    fclose(lmfile);
                } else {
                    throw std::runtime_error("couldn't open file .lm");
                }


                curl_easy_reset(curl);
                curl_easy_setopt(curl, CURLOPT_URL, dict_location.c_str());
                dicfile = fopen(dicfilename, "wb");
                if (dicfile) {
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, dicfile);
                    res = curl_easy_perform(curl);
                    if (res != CURLE_OK){
                        throw std::runtime_error("couldn't perform run request");
                    }
                    fclose(dicfile);
                } else {
                    throw std::runtime_error("couldn't open file .dic");
                }

                /* always cleanup */
                curl_easy_cleanup(curl);
                /* then cleanup the form */
                curl_mime_free(form);
                /* free slist */
                curl_slist_free_all(headerlist);
            }
        }

        void reloadIfNew() {
            try {
                std::stringstream newDic = getDic();
                if (oldStrStr.str() != newDic.str()) {
                    reload_dic();
                    oldStrStr = std::move(newDic);
                }
            } catch (std::runtime_error &e) {
                std::cout << e.what() << "\n";
                throw std::runtime_error("Could not reload dictionary");
            }
        }

        void addMinimumPhrases() {
            addToDic("hey lily");
            addToDic("hello lily");
            addToDic("okey lily");
            addToDic("raspberry pi");
            addToDic("stop");
            addToDic("What is the");
            addToDic("who did");
            addToDic("you");
            addToDic("Say");
        }
    }
}