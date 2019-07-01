#ifndef IAUDIOPROVIDER_HPP_INCLUDED
#define IAUDIOPROVIDER_HPP_INCLUDED

#include <string>

class IAudioProvider {
public:
    virtual void PlaySound(std::string filename) = 0;
    virtual void PlayMusic(std::string filename, bool looping) = 0;
    virtual void StopSound() = 0;
    virtual void StopMusic() = 0;
    virtual void StopAll() = 0;
    virtual void SetSoundEnable(bool enable) = 0;
    virtual void SetMusicEnable(bool enable) = 0;
    virtual void SetEnable(bool enable) = 0;
    virtual bool IsSoundEnable() = 0;
    virtual bool IsMusicEnable() = 0;

    virtual bool IsSoundPlaying() = 0;
    virtual bool IsMusicPlaying() = 0;
};

#endif // IAUDIOPROVIDER_HPP_INCLUDED
