#ifndef WAVFILE_H
#define WAVFILE_H
#include <vector>
#include <cstdio>
#include <stdint-gcc.h>
#include <vector>

class WavFile {
private:
    struct {
        int32_t chunkId;   // Завжди містить значення 0x52494646 (літери "RIFF")
        int32_t chunkSize; // 36 + розмір другого підрозділу в байтах
                           // Іншими словами 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
                           // Це розмір всього файла мінус 8 байтів які займають поля chunkId та chunkSize
        int32_t format;    // Для wav-файла це завжди 0x57415645 (літери "WAVE")
    } riffheader;

    struct {
        int32_t subchunk1Id;   // Завжди 0x666d7420 – літери "fmt "
        int32_t subchunk1Size; // Завжди 16 для аудіо PCM. Це розмір частини підрозділу, що слідує після цього числа
        int16_t audioFormat;   // PCM = 1
        int16_t numChannels;   // Mono = 1, Stereo = 2
        int32_t sampleRate;    // Наприклад 44100
        int32_t byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
        int16_t blockAlign;    // == NumChannels * BitsPerSample/8
        int16_t bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
    } subchunk1;

    struct SUBCHUNK2{
        int32_t subchunk2Id;   // 0x64617461 – літери "data"
        int32_t subchunk2Size; // == NumSamples * NumChannels * BitsPerSample/8, кількість байтів аудіоданих
        std::vector <std::vector <int16_t> > data;  // семпли
    } subchunk2;

};

#endif // WAVFILE_H
