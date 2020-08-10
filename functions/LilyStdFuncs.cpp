//
// Created by 42kangaroo on 07.05.20.
//

#include "LilyStdFuncs.hpp"

namespace {
    std::size_t callback(
            const char *in,
            std::size_t size,
            std::size_t num,
            std::string *out) {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}
namespace Lily::functions {
    namespace weather {
        std::string getWeather() {
            std::string openWeatherMapToken = "";
            const std::string url(
                    "http://api.openweathermap.org/data/2.5/weather?q=Riehen,ch&appid=" + oponWeatherMapToken +
                    "&units=metric");

            CURL *curl = curl_easy_init();
            if (curl == nullptr) {
                throw std::runtime_error("curl could not be initialized");
            }

            // Set remote URL.
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // Don't bother trying IPv6, which would increase DNS resolution time.
            curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

            // Don't wait forever, time out after 10 seconds.
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

            // Follow HTTP redirects if necessary.
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            // Response information.
            int httpCode(0);
            std::unique_ptr<std::string> httpData(new std::string());

            // Hook up data handling function.
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

            // Hook up data container (will be passed as the last parameter to the
            // callback handling function).  Can be any pointer type, since it will
            // internally be passed as a void pointer.
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

            // Run our HTTP GET command, capture the HTTP response code, and clean up.
            curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            curl_easy_cleanup(curl);
            std::string descriptionString;
            int temperature;
            if (httpCode == 200) {

                // Response looks good - done using Curl now.  Try to parse the results
                // and print them out.
                Json::Value jsonData;
                Json::Reader jsonReader;

                if (jsonReader.parse(*httpData, jsonData)) {

                    auto weatherArray = jsonData["weather"];

                    auto firstelemDesc = weatherArray[0];
                    descriptionString = firstelemDesc["description"].asString();
                    temperature = jsonData["main"]["temp"].asDouble();

                } else {
                    std::cout << "Could not parse HTTP data as JSON" << std::endl;
                    std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
                    return "Parsing failed";
                }
            } else {
                throw std::runtime_error("request to openWeatherMap failed");
            }
            std::string answer = "temperatur is ";
            answer += std::to_string(temperature);
            answer += " degrees Celcius and the description is " + descriptionString;
            return "The " + answer;

        }
    }
    namespace dateSP {
        std::string getDate() {
            using namespace std::literals::string_literals;
            time_t now;
            struct tm *ltm;
            char times[40];
            std::time(&now);
            ltm = localtime(&now);
            if (strftime(times, 40, "%A the %d of %B %Y", ltm) == 0) {
                throw std::runtime_error("time exceeded the char limit");
            }
            return "The date is "s + times;
        }
    }
    namespace timeSP {
        std::string getTime() {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            std::string times = std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min);
            return "The time is " + times;
        }
    }

    namespace volume_control {
        std::string setPlaybackVolumeUp() {

            snd_mixer_t *handle;
            snd_mixer_selem_id_t *sid;
            const char *card = "hw:1";
            const char *selem_name = "PCM";

            if (snd_mixer_open(&handle, 0) < 0) {
                throw std::runtime_error("could not open speaker");
            }
            snd_mixer_attach(handle, card);
            snd_mixer_selem_register(handle, NULL, NULL);
            snd_mixer_load(handle);

            snd_mixer_selem_id_malloc(&sid);
            snd_mixer_selem_id_set_index(sid, 0);
            snd_mixer_selem_id_set_name(sid, selem_name);
            snd_mixer_elem_t *elem = snd_mixer_find_selem(handle, sid);
            if (elem == NULL) {
                throw std::runtime_error("could not find elem");
            }
            long outvol;
            long minv, maxv;
            long oldmax, oldmin;
            snd_mixer_selem_get_playback_volume_range(elem, &minv, &maxv);

            if (snd_mixer_selem_get_playback_volume(elem, static_cast<snd_mixer_selem_channel_id_t>(0), &outvol) <
                0) {
                throw std::runtime_error("could not get volume");
            }
            oldmax = maxv;
            oldmin = minv;
            outvol -= minv;
            maxv -= minv;
            minv = 0;
            outvol = 100 * (outvol) / maxv;
            if (outvol < 96) {
                outvol += 4;
            } else {
                outvol = 100;
            }
            snd_mixer_selem_set_playback_volume_all(elem, outvol * oldmax / 100 - oldmin);
            snd_mixer_close(handle);
            std::string returnValue = "Playback Volume is now " + std::to_string(outvol);
            return returnValue;
        }

        std::string setPlaybackVolumeDown() {
            snd_mixer_t *handle;
            snd_mixer_selem_id_t *sid;
            const char *card = "hw:1";
            const char *selem_name = "PCM";

            if (snd_mixer_open(&handle, 0) < 0) {
                throw std::runtime_error("could not open speaker");
            }
            snd_mixer_attach(handle, card);
            snd_mixer_selem_register(handle, NULL, NULL);
            snd_mixer_load(handle);

            snd_mixer_selem_id_malloc(&sid);
            snd_mixer_selem_id_set_index(sid, 0);
            snd_mixer_selem_id_set_name(sid, selem_name);
            snd_mixer_elem_t *elem = snd_mixer_find_selem(handle, sid);
            if (elem == NULL) {
                throw std::runtime_error("could not find elem");
            }
            long outvol;
            long minv, maxv;
            long oldmax, oldmin;
            snd_mixer_selem_get_playback_volume_range(elem, &minv, &maxv);

            if (snd_mixer_selem_get_playback_volume(elem, static_cast<snd_mixer_selem_channel_id_t>(0), &outvol) <
                0) {
                throw std::runtime_error("could not get volume");
            }
            oldmax = maxv;
            oldmin = minv;
            outvol -= minv;
            maxv -= minv;
            minv = 0;
            outvol = 100 * (outvol) / maxv;
            if (outvol > 4) {
                outvol -= 3;
            } else {
                outvol = 0;
            }
            snd_mixer_selem_set_playback_volume_all(elem, outvol * oldmax / 100 - oldmin);
            snd_mixer_close(handle);
            std::string returnValue = "Playback Volume is now " + std::to_string(outvol);
            return returnValue;
        }

        string setCaptureVolumeUp() {
            snd_mixer_t *handle;
            snd_mixer_selem_id_t *sid;
            const char *card = "hw:1";
            const char *selem_name = "Boost";

            if (snd_mixer_open(&handle, 0) < 0) {
                throw std::runtime_error("could not open speaker");
            }
            snd_mixer_attach(handle, card);
            snd_mixer_selem_register(handle, NULL, NULL);
            snd_mixer_load(handle);

            snd_mixer_selem_id_malloc(&sid);
            snd_mixer_selem_id_set_index(sid, 0);
            snd_mixer_selem_id_set_name(sid, selem_name);
            snd_mixer_elem_t *elem = snd_mixer_find_selem(handle, sid);
            if (elem == NULL) {
                throw std::runtime_error("could not find elem");
            }
            long outvol;
            long minv, maxv;
            long oldmax, oldmin;
            snd_mixer_selem_get_capture_volume_range(elem, &minv, &maxv);

            if (snd_mixer_selem_get_capture_volume(elem, static_cast<snd_mixer_selem_channel_id_t>(0), &outvol) <
                0) {
                throw std::runtime_error("could not get volume");
            }
            oldmax = maxv;
            oldmin = minv;
            outvol -= minv;
            maxv -= minv;
            minv = 0;
            outvol = 100 * (outvol) / maxv;
            if (outvol < 96) {
                outvol += 5;
            } else {
                outvol = 100;
            }
            snd_mixer_selem_set_capture_volume_all(elem, outvol * oldmax / 100 - oldmin);
            snd_mixer_close(handle);
            std::string returnValue = "Capture Volume is now " + std::to_string(outvol);
            return returnValue;
        }

        string setCaptureVolumeDown() {
            snd_mixer_t *handle;
            snd_mixer_selem_id_t *sid;
            const char *card = "hw:1";
            const char *selem_name = "Boost";

            if (snd_mixer_open(&handle, 0) < 0) {
                throw std::runtime_error("could not open speaker");
            }
            snd_mixer_attach(handle, card);
            snd_mixer_selem_register(handle, NULL, NULL);
            snd_mixer_load(handle);

            snd_mixer_selem_id_malloc(&sid);
            snd_mixer_selem_id_set_index(sid, 0);
            snd_mixer_selem_id_set_name(sid, selem_name);
            snd_mixer_elem_t *elem = snd_mixer_find_selem(handle, sid);
            if (elem == NULL) {
                throw std::runtime_error("could not find elem");
            }
            long outvol;
            long minv, maxv;
            long oldmax, oldmin;
            snd_mixer_selem_get_capture_volume_range(elem, &minv, &maxv);

            if (snd_mixer_selem_get_capture_volume(elem, static_cast<snd_mixer_selem_channel_id_t>(1), &outvol) <
                0) {
                throw std::runtime_error("could not get volume");
            }
            oldmax = maxv;
            oldmin = minv;
            outvol -= minv;
            maxv -= minv;
            minv = 0;
            outvol = 100 * (outvol) / maxv;
            if (outvol > 4) {
                outvol -= 3;
            } else {
                outvol = 0;
            }
            snd_mixer_selem_set_capture_volume_all(elem, outvol * oldmax / 100 - oldmin);
            snd_mixer_close(handle);
            std::string returnValue = "Capture Volume is now " + std::to_string(outvol);
            return returnValue;
        }

        string setAllVolumeDown() {
            return setPlaybackVolumeDown() + " and " + setCaptureVolumeDown();
        }

        string setAllVolumeUp() {
            return setPlaybackVolumeUp() + " and " + setCaptureVolumeUp();
        }
    }
}