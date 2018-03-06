#ifndef WAVFILE_H
#define WAVFILE_H
#include <QVector>

class WavFile {
private:
    struct {
        qint32 chunkId;   // Завжди містить значення 0x52494646 (літери "RIFF")
        qint32 chunkSize; // 36 + розмір другого підрозділу в байтах
                           // Іншими словами 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
                           // Це розмір всього файла мінус 8 байтів які займають поля chunkId та chunkSize
        qint32 format;    // Для wav-файла це завжди 0x57415645 (літери "WAVE")
    } riffheader;

    struct {
        qint32 subchunk1Id;   // Завжди 0x666d7420 – літери "fmt "
        qint32 subchunk1Size; // Завжди 16 для аудіо PCM. Це розмір частини підрозділу, що слідує після цього числа
        qint16 audioFormat;   // PCM = 1
        qint16 numChannels;   // Mono = 1, Stereo = 2
        qint32 sampleRate;    // Наприклад 44100
        qint32 byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
        qint16 blockAlign;    // == NumChannels * BitsPerSample/8
        qint16 bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
    } subchunk1;
    struct SUBCHUNK2{
        qint32 subchunk2Id;   // 0x64617461 – літери "data"
        qint32 subchunk2Size; // == NumSamples * NumChannels * BitsPerSample/8, кількість байтів аудіоданих
        QVector<QVector<qint16> > data;  // семпли
    } subchunk2;

};

#endif // WAVFILE_H
