#ifndef SFMLSOUNDPROVIDER_HPP_INCLUDED
#define SFMLSOUNDPROVIDER_HPP_INCLUDED

#include "IAudioProvider.hpp"
#include "SoundFileCache.hpp"

class SFMLSoundProvider : public IAudioProvider {
public:
    SFMLSoundProvider();

    void PlaySound(std::string filename);
    void PlayMusic(std::string filename, bool looping = false);
    void StopSound();
    void StopMusic();
    void StopAll();
    void SetSoundEnable(bool enable = true);
    void SetMusicEnable(bool enable = true);
    void SetEnable(bool enable = true);
    bool IsSoundEnable();
    bool IsMusicEnable();

    bool IsSoundPlaying();
    bool IsMusicPlaying();

private:
    static const int MAX_SOUND_CHANNELS = 10;

    SoundFileCache _soundFileCache;
    sf::Sound _currentSounds[MAX_SOUND_CHANNELS];
    std::string _currentMusicName;
    bool _soundsEnable;
    bool _musicEnable;
};

#endif // SFMLSOUNDPROVIDER_HPP_INCLUDED
