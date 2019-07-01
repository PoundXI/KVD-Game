#ifndef SERVICELOCATOR_HPP_INCLUDED
#define SERVICELOCATOR_HPP_INCLUDED

#include "IAudioProvider.hpp"

class ServiceLocator {
public:
    static IAudioProvider* GetAudio() {
        return _audioProvider;
    } const

    static void RegisterServiceLocator(IAudioProvider* provider) {
        _audioProvider = provider;
    }

private:
    static IAudioProvider* _audioProvider;
};

#endif // SERVICELOCATOR_HPP_INCLUDED
