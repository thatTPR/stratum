#ifndef AUDIO_HPP
#define AUDIO_HPP
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


#include <acqres/wav.hpp>


void pitch(std::vector<uint8_t>* data, wavh* head, double multiplier);
void speed(std::vector<uint8_t>* data, wavh* head, double multiplier);


void reverb(std::vector<uint8_t>* data, wavh* head, double multiplier);
void delay(std::vector<uint8_t>* data, wavh* head, double multiplier);
void chorus(std::vector<uint8_t>* data, wavh* head, double multiplier);
void delay(std::vector<uint8_t>* data, wavh* head, double multiplier);
void phaser(std::vector<uint8_t>* data, wavh* head, double multiplier);


void Compression(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Limiter(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Expander(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Gate(std::vector<uint8_t>* data, wavh* head, double multiplier);

void Tremolo(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Vibrato(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Rotary(std::vector<uint8_t>* data, wavh* head, double multiplier);
void RingMod(std::vector<uint8_t>* data, wavh* head, double multiplier);

void hormonize(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Autotune(std::vector<uint8_t>* data, wavh* head, double multiplier);


void equalize(std::vector<uint8_t>* data, wavh* head, double multiplier);
void WahWah(std::vector<uint8_t>* data, wavh* head, double multiplier);
void bandpassFilter(std::vector<uint8_t>* data, wavh* head, double multiplier);


void lowpassFilter(std::vector<uint8_t>* data, wavh* head, double multiplier);
void highpassFilter(std::vector<uint8_t>* data, wavh* head, double multiplier);

void OverDrive(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Distortion(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Fuzz(std::vector<uint8_t>* data, wavh* head, double multiplier);
void BitCrush(std::vector<uint8_t>* data, wavh* head, double multiplier);

void Panning(std::vector<uint8_t>* data, wavh* head, double multiplier);
void StereoWiden(std::vector<uint8_t>* data, wavh* head, double multiplier);
void Binaural(std::vector<uint8_t>* data, wavh* head, double multiplier);

// Nodes :


template <class audioNode>
struct widgets {
    using sideBarWidget = widget;
     
};
#endif