//
// Created by 42kangaroo on 07.05.20.
//

#ifndef FUNCTIONS_LILYSTDFUNCS_HPP
#define FUNCTIONS_LILYSTDFUNCS_HPP

#include <iostream>
#include <memory>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <alsa/asoundlib.h>
#include <alsa/mixer.h>
#include <string>
#include <ctime>
#include <stdexcept>

namespace Lily::functions {
    namespace weather {
        /**
        * get the current weather from OpenWeatherMap
        * @return the weather
        */
        std::string getWeather();
    }


    namespace timeSP {
        /**
         * get the current Time
         * @return the time
         */
        std::string getTime();
    }


    namespace dateSP {
        /**
         * get the current Date
         * @return the Date
         */
        std::string getDate();
    }


    namespace volume_control {
        using std::string;

        /**
         * set the volume up for speaker
         * @return the current volume
         */
        string setPlaybackVolumeUp();

        /**
         * set the volume down for speaker
         * @return the current volume
         */
        string setPlaybackVolumeDown();

        /**
         * set the volume up for microphone
         * @return the current volume
         */
        string setCaptureVolumeUp();

        /**
         * set the volume down for microphone
         * @return the current volume
         */
        string setCaptureVolumeDown();

        /**
         * set the volume up for speaker and mic
         * @return the current volumes
         */
        string setAllVolumeUp();

        /**
         * set the volume down for speaker and mic
         * @return the current volumes
         */
        string setAllVolumeDown();
    }
}
#endif //FUNCTIONS_LILYSTDFUNCS_HPP
