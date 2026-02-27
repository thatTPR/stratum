#ifndef WAV_HPP
#define WAV_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstddef>
#include <filesystem>
using namespace std;



 struct wavh{
 char riff[4]= {'R','I','F','F'};                // "RIFF"
    uint32_t chunkSize;
    char wave[4]={'W','A','V','E'};                // "WAVE"
    char fmt[4]={'f','m','t',' '};                 // "fmt "
    uint32_t subchunk1Size=16;      // PCM = 16
    uint16_t audioFormat=1;        // PCM = 1
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char data[4]={'d','a','t','a'};                // "data"
    uint32_t dataSize;
    wavh(uint32_t numCh,uint16_t audioF,uint32_t srate) : numChannels(numCh),audioFormat(audioF), sampleRate(srate){};
};


bool read_wav(std::filesystem::path& filePath,struct wavh* header,std::vector<uint8_t>& pcmdata){
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
template <typename intT>
void write_wav(std::filesystem::path& p ,std::vector<intT>& vec,size_t numc, size_t audioF , uint32_t sampleRate , ){
  std::ofstream of(p);
  wavh h((uint16_t)numc,(uint16_t)audioF,(uint32_t)sampleRate);
  of.write(reinterpret_cast<char*>(h),sizeof(wavh));
  of.write(reinterpret_cast<char*>(vec.data),vec.size()*sizeof(intT));
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


#endif
