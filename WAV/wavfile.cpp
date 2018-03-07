#include "wavfile.h"
#include <fstream>


void WavFile::readFromFile(QString filename) {
    //TODO: fix cyrillic characters problem
    std::ifstream in(filename.toUtf8(), std::ios::binary);

    in.read((char*) &riffheader, sizeof riffheader);
    in.read((char*) &subchunk1, sizeof subchunk1);

    in.read((char*) &subchunk2.subchunk2Id, sizeof subchunk2.subchunk2Id);
    in.read((char*) &subchunk2.subchunk2Size, sizeof subchunk2.subchunk2Size);

    subchunk2.data.resize(subchunk1.numChannels);
    for (int i = 0; i < subchunk1.numChannels; ++i) {
        subchunk2.data[i].resize(subchunk2.subchunk2Size / subchunk1.blockAlign);
    }

    // maybe, i will use there something better (in future)
    if (subchunk1.bitsPerSample == 8) {
        size_t i = 0;
        while (!in.eof()) {
            in.read((char*) &subchunk2.data[i % 2][i / 2].data8, sizeof subchunk2.data[i % 2][i / 2].data8);
            ++i;
        }
    }
    else if (subchunk1.bitsPerSample == 16) {
        size_t i = 0;
        while (!in.eof()) {
            in.read((char*) &subchunk2.data[i % 2][i / 2].data16, sizeof subchunk2.data[i % 2][i / 2].data16);
            ++i;
        }
    }
    else {
        size_t i = 0;
        while (!in.eof()) {
            in.read((char*) &subchunk2.data[i % 2][i / 2].data32, sizeof subchunk2.data[i % 2][i / 2].data32);
            ++i;
        }
    }

}

void WavFile::saveToFile(QString filename) {
    //TODO: fix cyrillic characters problem
    std::ofstream out (filename.toUtf8(), std::ios::binary);
    out.write((char*) &riffheader, sizeof riffheader);
    out.write((char*) &subchunk1, sizeof subchunk1);
    out.write((char*) &subchunk2.subchunk2Id, sizeof subchunk2.subchunk2Id);
    out.write((char*) &subchunk2.subchunk2Size, sizeof subchunk2.subchunk2Size);

    if (subchunk1.bitsPerSample == 8) {
        for (int i = 0; i < this->subchunk2.data[0].size() * subchunk1.numChannels; ++i) {
            out.write((char*) &subchunk2.data[i % 2][i / 2].data8, sizeof subchunk2.data[i % 2][i / 2].data8);
        }
    }
    else if (subchunk1.bitsPerSample == 16) {
        for (int i = 0; i < this->subchunk2.data[0].size() * subchunk1.numChannels; ++i) {
            out.write((char*) &subchunk2.data[i % 2][i / 2].data16, sizeof subchunk2.data[i % 2][i / 2].data16);
        }
    }
    else {
        for (int i = 0; i < this->subchunk2.data[0].size() * subchunk1.numChannels; ++i) {
            out.write((char*) &subchunk2.data[i % 2][i / 2].data32, sizeof subchunk2.data[i % 2][i / 2].data32);
        }
    }
}

//src - input, dst - output, k - coefficient
void WavFile::resize(const WavFile &src, WavFile &dst, double k) {

}




