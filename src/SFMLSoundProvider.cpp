#include "SFMLSoundProvider.hpp"
#include "SoundFileCache.hpp"

SFMLSoundProvider::SFMLSoundProvider()
    : _currentMusicName("")
    , _soundsEnable(true)
    , _musicEnable(true) {
}

void SFMLSoundProvider::PlaySound(std::string filename) {
    if(_soundsEnable == false)
        return;

    int availChannel = -1;
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++) {
        if(_currentSounds[i].GetStatus() != sf::Sound::Playing) {
            availChannel = i;
            break;
        }
    }

    // If all sound channels are in use, do nothing for now
    if(availChannel != -1) {
        try {
            _currentSounds[availChannel] = _soundFileCache.GetSound(filename);
            _currentSounds[availChannel].Play();
        } catch(SoundNotFoundExeception& snfe) {
            // ERROR, file wasnt found, should handle error here
            // snfe.what will contain the exception details
        }
    }
}

void SFMLSoundProvider::PlayMusic(std::string filename, bool looping) {
    if(_musicEnable == false)
        return;

    sf::Music* currentSong;
    try {
        currentSong = _soundFileCache.GetSong(filename);
    } catch(SoundNotFoundExeception&) {
        // This one is dire, means we couldn't find or load the selected song
        // So, lets exit!
        return;
    }
    // See if prior song is playing still, if so, stop it
    if(_currentMusicName != "") {
        try {
            sf::Music* priorSong = _soundFileCache.GetSong(_currentMusicName);
            if(priorSong->GetStatus() != sf::Sound::Stopped) {
                priorSong->Stop();
            }
        } catch(SoundNotFoundExeception&) {
            // Do nothing, this exception isn't dire.  It simply means the previous sound we were
            // trying to stop wasn't located.
        }

    }
    _currentMusicName = filename;
    currentSong->SetLoop(looping);
    currentSong->Play();
}

void SFMLSoundProvider::StopSound() {
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++) {
        _currentSounds[i].Stop();
    }
}

void SFMLSoundProvider::StopMusic() {
    if(_currentMusicName != "") {
        sf::Music* currentSong = _soundFileCache.GetSong(_currentMusicName);
        if(currentSong->GetStatus() == sf::Sound::Playing) {
            currentSong->Stop();
        }
    }
}

void SFMLSoundProvider::StopAll() {
    StopSound();
    StopMusic();
}

void SFMLSoundProvider::SetSoundEnable(bool enable) {
    _soundsEnable = enable;
}

void SFMLSoundProvider::SetMusicEnable(bool enable) {
    _musicEnable = enable;
}

void SFMLSoundProvider::SetEnable(bool enable) {
    SetSoundEnable(enable);
    SetMusicEnable(enable);
}

bool SFMLSoundProvider::IsSoundEnable() {
    return _soundsEnable;
}

bool SFMLSoundProvider::IsMusicEnable() {
    return _musicEnable;
}

bool SFMLSoundProvider::IsSoundPlaying() {
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++) {
        if(_currentSounds[i].GetStatus() == sf::Sound::Playing)
            return true;
    }
    return false;
}


bool SFMLSoundProvider::IsMusicPlaying() {
    if(_currentMusicName != "") {
        return _soundFileCache.GetSong(_currentMusicName)->GetStatus() == sf::Music::Playing;
    }
    return false;
}
