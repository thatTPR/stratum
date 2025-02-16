#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;



struct wavh {
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
};


bool readwavFile(char* path, wavh* header,std::vector<uint8_t>& pcmdata){
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