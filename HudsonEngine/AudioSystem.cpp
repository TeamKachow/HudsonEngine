#include "AudioSystem.h"
#include <irrKlang.h>

using namespace irrklang;

AudioSystem::AudioSystem() {
    // Initialize the sound engine
    engine = irrklang::createIrrKlangDevice();
}

AudioSystem::~AudioSystem() {
    // Stop all sounds and close the sound engine
    stopAllSounds();
    engine->drop();
}

void AudioSystem::playSound(const char* file, bool loop, float volume, float pitch, float pan) 
{
    // Play a sound file
    irrklang::ISound* sound = engine->play2D(file, loop, false, true);
    if (sound) {
        sounds.push_back(sound);
        sound->setVolume(volume);
        sound->setPlaybackSpeed(pitch);
        sound->setPan(pan);
    }
}

void AudioSystem::stopSound(const char* file) 
{
    // Stop a sound file
    for (auto it = sounds.begin(); it != sounds.end(); ++it) {
        irrklang::ISound* sound = *it;
        if (sound->getSoundSource()->getName() == file) {
            sound->stop();
            sounds.erase(it);
            break;
        }
    }
}

void AudioSystem::stopAllSounds() 
{
    // Stop all sound files
    for (auto& sound : sounds) {
        sound->stop();
    }
    sounds.clear();
}

void AudioSystem::setListenerPosition(float x, float y) 
{
    // Set the position of the listener
    engine->setListenerPosition(irrklang::vec3df(x, y, 0), irrklang::vec3df(0, 0, 1));
}

void AudioSystem::setSoundVolume(const char* file, float volume) 
{
    // Set the volume of a sound file
    for (auto& sound : sounds) 
    {
        if (sound-> getSoundSource()->getName() == file) 
        {
            sound->setVolume(volume);
            break;
        }
    }
}

void AudioSystem::setSoundPitch(const char* file, float pitch) 
{
    // Set the pitch of a sound file
    for (auto& sound : sounds) {
        if (sound->getSoundSource()->getName() == file) {
            sound->setPlaybackSpeed(pitch);
            break;
        }
    }
}

void AudioSystem::setSoundPan(const char* file, float pan) 
{
    // Set the pan of a sound file
    for (auto& sound : sounds) {
        if (sound->getSoundSource()->getName() == file) {
            sound->setPan(pan);
            break;
        }
    }
}

bool AudioSystem::isSoundPlaying(const char* file) 
{
    // Check if a sound file is currently playing
    for (auto& sound : sounds) 
    {
        if (sound->getSoundSource()->getName() == file) 
        {
            return !sound->isFinished();
        }
    }
    return false;
}

//bool AudioSystem::applySoundEffect(const char* file, int effectType, float value) 
//{
//    for (auto& sound : sounds) 
//    {
//        if (sound->getSoundSource()->getName() == file) 
//        {
//            irrklang::ISoundEffectControl* effectControl = sound->getSoundEffectControl();
//            if (!effectControl)
//                return false;
//            effectControl->enableEffect(effectType, true);
//            effectControl->setEffectParam(effectType, 0, value);
//            break;
//        }
//    }
//    return true;
//}

//void AudioSystem::fxDisplayUI()
//{
//    ImGui::Begin("Sound Effects");
//    ImGui::Text("Toggle sound effects:");
//    if (ImGui::Button("Echo")) toggleEcho();
//    ImGui::SameLine();
//    ImGui::Text(echoEnabled_ ? "Enabled" : "Disabled");
//    if (ImGui::Button("Chorus")) toggleChorus();
//    ImGui::SameLine();
//    ImGui::Text(chorusEnabled_ ? "Enabled" : "Disabled");
//    if (ImGui::Button("Distortion")) toggleDistortion();
//    ImGui::SameLine();
//    ImGui::Text(distortionEnabled_ ? "Enabled" : "Disabled");
//    if (ImGui::Button("Reverb")) toggleReverb();
//    ImGui::SameLine();
//    ImGui::Text(reverbEnabled_ ? "Enabled" : "Disabled");
//    // Add more buttons for other effects
//    ImGui::End();
//}