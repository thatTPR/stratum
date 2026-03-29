#ifndef AUDIO_HPP
#define AUDIO_HPP



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