


#include "Speach_recognizer.hpp"

#define MODELDIR "/usr/local/share/pocketsphinx/model" // Dort sind die Modele

using std::cout;
using std::endl;
namespace {
    ps_decoder_t *ps;                  // create pocketsphinx decoder structure
    cmd_ln_t *config;                  // create configuration structure
    ad_rec_t *ad;
    int16 adbuf[4096];                 // buffer array to hold audio data
    uint8 utt_started, in_speech;      // flags for tracking active speech - has speech started? - is speech currently happening?
    int32 k;                           // holds the number of frames in the audio buffer
    char const *hyp;                   // pointer to "hypothesis" (best guess at the decoded result)
    char *device = "default";                       //soundcard
    float buffer[48000];


    /**
* recognition of the keyphrase
* @return the keyphrase or Null if not recognized
*/
    const char *keyphrase_is_spoken() {
        ps_set_search(ps, "activate");
        ad_start_rec(ad);// start recording
        ps_start_utt(ps);                                // mark the start of the utterance
        utt_started = FALSE;// clear the utt_started flag

        while (true) {
            k = ad_read(ad, adbuf,
                        4096);                // capture the number of frames in the audio buffer

            ps_process_raw(ps, adbuf, k, FALSE,
                           FALSE); // send the audio buffer to the pocketsphinx decoder

            in_speech = ps_get_in_speech(
                    ps);            // test to see if speech is being detected

            if (in_speech &&
                !utt_started) {             // if speech has started and utt_started flag is false
                utt_started = TRUE; // then set the flag
                std::cout << "starting keyphrase" << std::endl;
            }

            if (!in_speech &&
                utt_started) {             // if speech has ended and the utt_started flag is true
                ps_end_utt(ps);                          // then mark the end of the utterance
                ad_stop_rec(ad);                         // stop recording
                hyp = ps_get_hyp(ps,
                                 NULL);// query pocketsphinx for "hypothesis" of decoded statement
                return hyp;                            // the function returns the hypothesis
            }

        }
    }


    /**
* recognize a string from the microfone
* @return the recognized string.
*/
    const char *recognize_from_microphone() {
        ps_set_search(ps, "recognize");
        ad_start_rec(ad);// start recording
        ps_start_utt(ps);                                // mark the start of the utterance
        utt_started = FALSE;// clear the utt_started flag

        while (true) {
            k = ad_read(ad, adbuf,
                        4096);                // capture the number of frames in the audio buffer
            ps_process_raw(ps, adbuf, k, FALSE,
                           FALSE); // send the audio buffer to the pocketsphinx decoder

            in_speech = ps_get_in_speech(
                    ps);            // test to see if speech is being detected

            if (in_speech &&
                !utt_started) {             // if speech has started and utt_started flag is false
                utt_started = TRUE; // then set the flag
                std::cout << "starting recognition" << std::endl;
            }

            if (!in_speech &&
                utt_started) {             // if speech has ended and the utt_started flag is true
                ps_end_utt(ps);                          // then mark the end of the utterance
                ad_stop_rec(ad);                         // stop recording
                hyp = ps_get_hyp(ps,
                                 NULL);// query pocketsphinx for "hypothesis" of decoded statement
                return hyp;                              // the function returns the hypothesis
            }

        }

    }

    /**
     * beep as a feedback
     * @param frequency the frequency in which to beep
     * @param time the length of the beep. (to hear it it must be over 2000 long)
     */
    void beep(int frequency, int time = 15000) {
        time = (time < 48000) ? time : 48000;
        int err;
        int k;

        int fs = 48000;             //sampling frequency

        snd_pcm_t *handle;
        // ERROR HANDLING

        if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
            using namespace std::literals::string_literals;
            throw std::runtime_error("Playback open error: "s + snd_strerror(err) + "\n"s);
        }

        if ((err = snd_pcm_set_params(handle,
                                      SND_PCM_FORMAT_FLOAT,
                                      SND_PCM_ACCESS_RW_INTERLEAVED,
                                      1,
                                      48000,
                                      1,
                                      500000)) < 0) {
            using namespace std::literals::string_literals;
            throw std::runtime_error("Playback open error: "s + snd_strerror(err) + "\n"s);


        }

        for (k = 0; k < time; k++) {

            buffer[k] = sin(2 * M_PI * frequency / fs * k);                 //sine wave value generation
        }

        snd_pcm_writei(handle, buffer, time);    //sending values to sound driver



        if (snd_pcm_close(handle) != 0) {
            throw std::runtime_error("couldn't close speaker");
        }
    }


}
namespace Lily {
    namespace Speach_recognizer {
        /**
        * init of Pocketsphinx
        */
        void init() {
            config = cmd_ln_init(NULL, ps_args(),
                                 TRUE,                   // Load the configuration structure - ps_args() passes the default values
                                 "-hmm", MODELDIR "/en-us/en-us",
                                 "-lm", "/home/pi/C-Programmes/listen/lm_file.lm",
                                 "-dict", "/home/pi/C-Programmes/listen/dic_file.dic",
                                 "-logfn",
                                 "/dev/null",                                      // suppress log info from being sent to screen
                                 NULL);
            if (config == NULL) {
                throw std::runtime_error("pocketsphinx could not be initialized");
            }

            ps = ps_init(config); // initialize the pocketsphinx decoder
            if (ps == NULL) {
                throw std::runtime_error("Failed to create recognizer, see log for details");
            }
            ad = ad_open_dev("default", (int) cmd_ln_float32_r(config,
                                                               "-samprate")); // open default microphone at default samplerate
            if (ad == NULL) {
                throw std::runtime_error("Failed to open Speach_recognizer\n");
            }

            if (ps_set_kws(ps, "activate", "/home/pi/C-Programmes/listen/keyphrase.list")) {
               throw std::runtime_error("Failed to load Keyphrases\n");
            }
            if (ps_set_lm_file(ps, "recognize", "/home/pi/C-Programmes/listen/lm_file.lm")) {
                throw std::runtime_error("Failed to load lm\n");
            }
            fprintf(stdout, "init complete\n");
            Dictionary_txt::reloadIfNew();
        }

/**
 * close all
 */
        void free() {
            ps_free(ps);
            cmd_ln_free_r(config);
            if(ad_close(ad) !=0){
                throw std::runtime_error("couldn't close mic");
            } // close the microphone
        }

/**
 * recognize a phrase, but only after hearing the Keyphrase
 * @return the recognized phrase without the keyphrase
 */
        std::string recognize_with_keyphrase() {
            const char *hyp_key;
            do {
                hyp_key = (keyphrase_is_spoken());
            } while (hyp_key == nullptr);
            std::cout << "heard!" << std::endl;
            beep(490);
            usleep(1000);
            std::string hyp{};
            while (hyp.empty() || hyp == "WHAT") {
                hyp = recognize_from_microphone();
                if (hyp.c_str() == nullptr) {
                    throw std::runtime_error("Reconiction failed\n");
                }
            }
            beep(400);
            return hyp;
        }

    }
}