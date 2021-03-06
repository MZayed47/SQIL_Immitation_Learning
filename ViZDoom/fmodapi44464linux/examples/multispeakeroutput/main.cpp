/*===============================================================================================
 Multi Speaker Output Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2016.

 This example shows how to play sounds in multiple speakers, and also how to even assign 
 sound subchannels, such as those in a stereo sound to different individual speakers.
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


int main(int argc, char *argv[])
{
    FMOD::System     *system;
    FMOD::Sound      *sound1, *sound2;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        getch();
        return 0;
    }

    /*
        Multichannel only supported in ALSA mode in 5.1 and 7.1.
        If the user doesn't have 5.1 speakers then only the speakers
        they have will be audible.
    */

    result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
    ERRCHECK(result);

    result = system->setSpeakerMode(FMOD_SPEAKERMODE_5POINT1);   
    ERRCHECK(result);
    
    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = system->createSound("../media/drumloop.wav", FMOD_SOFTWARE | FMOD_2D, 0, &sound1);
    ERRCHECK(result);
    result = sound1->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);


    result = system->createSound("../media/stereo.ogg", FMOD_SOFTWARE | FMOD_2D, 0, &sound2);
    ERRCHECK(result);

    printf("==============================================================================\n");
    printf("Multi Speaker Output Example.  Copyright (c) Firelight Technologies 2004-2016.\n");
    printf("==============================================================================\n");
    printf("\n");
    printf("Note!  You must have your speaker configuration set up correctly\n");
    printf("       in the windows control panel for this to work properly.\n");
    printf("\n");
    printf("Press '1' to play a mono sound on the FRONT LEFT speaker.\n");
    printf("Press '2' to play a mono sound on the FRONT RIGHT speaker.\n");
    printf("Press '3' to play a mono sound on the CENTER speaker.\n");
    printf("Press '4' to play a mono sound on the REAR LEFT speaker.\n");
    printf("Press '5' to play a mono sound on the REAR RIGHT speaker.\n");
    printf("Press '6' to play a mono sound on the SIDE LEFT speaker.\n");
    printf("Press '7' to play a mono sound on the SIDE RIGHT speaker.\n");
    printf("Press '8' to play a stereo sound on the front speakers.\n");
    printf("Press '9' to play a stereo sound on the front speakers but channel swapped.\n");
    printf("Press '0' to play the right part of a stereo sound on the CENTER speaker.\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    /*
        Main loop.
    */
    do
    {
        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case '1' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel);
                    ERRCHECK(result);

                    result = channel->setSpeakerMix(1.0f, 0, 0, 0, 0, 0, 0, 0);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);
                    break;
                }
                case '2' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel);
                    ERRCHECK(result);

                    result = channel->setSpeakerMix(0, 1.0f, 0, 0, 0, 0, 0, 0);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);
                    break;
                }
                case '3' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel);
                    ERRCHECK(result);

                    result = channel->setSpeakerMix(0, 0, 1.0f, 0, 0, 0, 0, 0);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);
                    break;
                }
                case '4' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel);
                    ERRCHECK(result);

                    result = channel->setSpeakerMix(0, 0, 0, 0, 1.0f, 0, 0, 0);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);
                    break;
                }
                case '5' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel);
                    ERRCHECK(result);

                    result = channel->setSpeakerMix(0, 0, 0, 0, 0, 1.0f, 0, 0);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);
                    break;
                }
                case '6' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel);
                    ERRCHECK(result);

                    result = channel->setSpeakerMix(0, 0, 0, 0, 0, 0, 1.0f, 0);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);
                    break;
                }
                case '7' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel);
                    ERRCHECK(result);

                    result = channel->setSpeakerMix(0, 0, 0, 0, 0, 0, 0, 1.0f);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);

                    break;
                }
                case '8' :
                {
                    float levels[2] = { 0, 1.0f };

                    result = system->playSound(FMOD_CHANNEL_FREE, sound2, true, &channel);
                    ERRCHECK(result);

                    /*
                        By default a stereo sound would play in all right and all left speakers, so this forces it to just the front.
                    */
                    result = channel->setSpeakerMix(1.0f, 1.0f, 0, 0, 0, 0, 0, 0);
                    ERRCHECK(result);

                    result = channel->setPaused(false);
                    ERRCHECK(result);

                    break;
                }
                case '9' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound2, true, &channel);
                    ERRCHECK(result);

                    /*
                        Clear out all speakers first.
                    */
                    result = channel->setSpeakerMix(0, 0, 0, 0, 0, 0, 0, 0);
                    ERRCHECK(result);

                    /*
                        Put the left channel of the sound in the right speaker.
                    */
                    {
                        float levels[2] = { 0, 1.0f };    /* This array represents the source stereo sound.  l/r */

                        result = channel->setSpeakerLevels(FMOD_SPEAKER_FRONT_LEFT, levels, 2);
                        ERRCHECK(result);
                    }
                    /*
                        Put the right channel of the sound in the left speaker.
                    */
                    {
                        float levels[2] = { 1.0f, 0 };    /* This array represents the source stereo sound.  l/r */

                        result = channel->setSpeakerLevels(FMOD_SPEAKER_FRONT_RIGHT, levels, 2);
                        ERRCHECK(result);
                    }

                    result = channel->setPaused(false);
                    ERRCHECK(result);

                    break;
                }
                case '0' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound2, true, &channel);
                    ERRCHECK(result);

                    /*
                        Clear out all speakers first.
                    */
                    result = channel->setSpeakerMix(0, 0, 0, 0, 0, 0, 0, 0);
                    ERRCHECK(result);

                    /*
                        Put the left channel of the sound in the right speaker.
                    */
                    {
                        float levels[2] = { 0, 1.0f };    /* This array represents the source stereo sound.  l/r */

                        result = channel->setSpeakerLevels(FMOD_SPEAKER_FRONT_CENTER, levels, 2);
                        ERRCHECK(result);
                    }

                    result = channel->setPaused(false);
                    ERRCHECK(result);

                    break;
                }
            }
        }

        system->update();

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            bool         playing = false;
            bool         paused = false;
            int          channelsplaying = 0;

            if (channel)
            {
                FMOD::Sound *currentsound = 0;

                result = channel->isPlaying(&playing);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = channel->getPaused(&paused);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }
               
                channel->getCurrentSound(&currentsound);
                if (currentsound)
                {
                    result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                    if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                    {
                        ERRCHECK(result);
                    }
                }
            }

            system->getChannelsPlaying(&channelsplaying);

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s : Channels Playing %2d\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped", channelsplaying);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}


