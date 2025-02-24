#ifndef WAV_HPP
#define WAV_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstddef>
using namespace std;



typedef struct {
 char riff[4];                // "RIFF"
    uint32_t chunkSize;
    char wave[4];                // "WAVE"
    char fmt[4];                 // "fmt "
    uint32_t subchunk1Size;      // PCM = 16
    uint16_t audioFormat;        // PCM = 1
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char data[4];                // "data"
    uint32_t dataSize;
} wavh;


bool readwavFile(char* path,struct wavh* header,std::vector<uint8_t>& pcmdata){
     std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr<<"Failed to open WAV file"<< filePath;
        return false;
    };
    // Read WAV header
    file.read(reinterpret_cast<char*>(header), sizeof(wavh));
    // Read PCM data
    pcmData.resize(header.dataSize);
    
    file.read(reinterpret_cast<char*>(pcmData.data()), header.dataSize);
    file.close();

    return true;
};

double getTime(wavh* header){/
    return (header->datasize)/(header->byteRate);
};
bool readwavFile(char* path, wavh* header,std::vector<uint8_t>& pcmdata, double start, double end){
     std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr<<"Failed to open WAV file"<< filePath;
        return false;
    };

    // Read WAV header
    file.read(reinterpret_cast<char*>(header), sizeof(wavh));
    double duration = getTime(header); double sstart;
    if(start>duration){sstart=duration>1?(duration-1):(duration-duration/10) ;}
    else {sstart=start};
    if(end>duruation){send=duration;}
    else {send=end;}
    if(sstart<send){
    uint tstart = header->datasize / (duration-sstart); 
    uint tend = header->datasize / (duration-send);
    }
    else {
    uint tend = header->datasize / (duration-sstart); 
    uint tstart = header->datasize / (duration-send);
    };
    uint rangesize  =  tend-tstart;
    file.seekg(tstart);
    // Read PCM data
    pcmData.resize(reangesize);
    file.read(reinterpret_cast<char*>(pcmData.data()), rangesize);
    if(sstart>send){
    for(int i=0;i<pcmData.size()/2 ;i++){
        auto temp = pcmData.data()[0];
        pcmData.data()[0+i] = pcmData.data()[pcmData.size() -i];
        pcmData.data()[pcmData.size()-i] = temp; 
    };
    };
    file.close();
    return true;
};
/*
1. Time-Based Effects
Reverb – Simulates sound reflections in a space, adding depth and ambiance.
Delay – Repeats the sound after a short period, creating an echo effect.
Chorus – Duplicates and slightly delays/modulates a sound to create a fuller effect.
Flanger – Creates a swirling or jet-plane-like effect by modulating a delayed signal.
Phaser – Uses phase shifting to create a sweeping, spacey effect.
2. Dynamic Effects
Compression – Reduces the dynamic range, making loud sounds quieter and quiet sounds louder.
Limiter – Prevents audio from exceeding a set volume, avoiding distortion.
Expander – Increases the dynamic range by making quiet sounds quieter.
Gate (Noise Gate) – Mutes sound below a certain threshold to remove background noise.
3. Modulation Effects
Tremolo – Rapid volume changes create a wobbling effect.
Vibrato – Rapid pitch variations create a warbling effect.
Rotary Speaker (Leslie effect) – Simulates the rotating speaker sound for a swirling effect.
Ring Modulation – Alters pitch by mixing the input with a synthesized signal.
4. Pitch-Based Effects
Pitch Shifting – Raises or lowers the pitch without affecting the speed.
Harmonizer – Adds additional harmonized notes to the original sound.
Auto-Tune – Corrects pitch errors or creates robotic vocal effects.
5. Filter-Based Effects
EQ (Equalization) – Adjusts the balance of frequencies to shape the tone.
Wah-Wah – Sweeps a peak filter up and down the frequency spectrum.
Bandpass, Lowpass, Highpass Filters – Remove specific frequency ranges.
6. Distortion Effects
Overdrive – Soft distortion that emulates a pushed tube amp.
Distortion – More aggressive, used for rock and metal sounds.
Fuzz – Extremely clipped and gritty distortion.
Bitcrusher – Lowers sample rate and bit depth for a lo-fi, digital sound.
7. Spatial Effects
Panning – Moves sound left or right in the stereo field.
Stereo Widening – Expands the stereo image for a bigger sound.
3D Audio (Binaural Effects) – Creates an immersive spatial effect using phase and timing differences.
*/
void phase(std::vector<uint8_t>* data, wavh* head, double multiplier);
void frequency(std::vector<uint8_t>* data, wavh* head, double multiplier);
void speed(std::vector<uint8_t>* data, wavh* head, double multiplier);
void reverb(std::vector<uint8_t>* data, wavh* head, double multiplier);
void pitch(std::vector<uint8_t>* data, wavh* head, double multiplier);



#endif