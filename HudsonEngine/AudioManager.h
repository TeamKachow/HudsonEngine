#pragma once
#include "./Util/stdafx.h"

using namespace irrklang;

enum SoundEffectType {
  
    SOUND_EFFECT_TYPE_CHORUS,
    SOUND_EFFECT_TYPE_COMPRESSOR,
    SOUND_EFFECT_TYPE_DISTORTION,
    SOUND_EFFECT_TYPE_ECHO,
    SOUND_EFFECT_TYPE_FLANGER,
    SOUND_EFFECT_TYPE_GARGLE,
    SOUND_EFFECT_TYPE_REVERB,
    SOUND_EFFECT_TYPE_DISABLE
};


class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    void setFilePath(std::string& filePath);
    
    irrklang::ISound* playSound(const std::string& filePath, bool playLooped, float pitch, float pan);
    bool toggleSound(const std::string& filePath);
    bool pauseSound(const std::string& filePath);
    bool resumeSound(const std::string& filePath);
    void stopSound(const std::string& filePath);
    void stopAllSounds();
    void setListenerPosition(float x, float y);

    void loadSoundFile(const std::string& filePath);
    void unloadSoundFile(const std::string& filePath);

    void setSoundVolume(const std::string& filePath, float sVolume = 1.0f);
    void setSoundPitch(const std::string& filePath, float pitch = 1.0f);
    void setSoundPan(const std::string& filePath, float pan = 0.0f);
    bool isSoundPlaying(const std::string& filePath);
    
    bool addAudioStreamLoader(irrklang::IAudioStreamLoader* loader, int numLoaders = 0);  
    void setSoundEffect(const std::string& filePath, SoundEffectType effectType, bool enable);

    void soundButtonUI(const std::string& filePath);

private:
   
    std::string filePath;

    irrklang::ISoundEngine* engine;
    
    std::map<std::string, std::vector<irrklang::ISound*>> sounds;

    std::vector<irrklang::ISoundEffectControl*> fx;

    std::vector<irrklang::IAudioStreamLoader*> audioStreamLoaders;
    std::unordered_map<std::string, irrklang::IAudioStream*> decoders;
   
   
};


