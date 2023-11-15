//
// Created by 이상민 on 2023-11-09.
//

#ifndef DEEPCNNAPPTEST_BITMAP32BIT_H
#define DEEPCNNAPPTEST_BITMAP32BIT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <android/asset_manager_jni.h>
#pragma pack(push, 1)

// BMP 파일 헤더
struct BMPHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
};

// BMP 정보 헤더
struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};

#pragma pack(pop)


std::vector<std::vector<std::vector<float>>> readTestBMP(AAssetManager* assetManager, const char* filename){
    AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
    if (asset != nullptr) {
        // BMP 파일을 읽는 코드
        // ...
        BMPHeader header;
        BMPInfoHeader infoHeader;

        AAsset_read(asset,reinterpret_cast<char*>(&header), sizeof(BMPHeader));
        AAsset_read(asset,reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

        if (header.signature != 0x4D42) {
            std::cerr << "올바르지 않은 BMP 파일 형식입니다." << std::endl;
            return {};
        }

        if (infoHeader.bitCount != 32) {
            std::cerr << "이 코드는 32비트 BMP 파일에만 대응합니다." << std::endl;
            return {};
        }
        std::vector<std::vector<std::vector<float>>> imageData(3, std::vector<std::vector<float>>(infoHeader.height, std::vector<float>(infoHeader.width)));

        for (int i = infoHeader.height - 1; i >= 0; i--) {
            for (int j = 0; j < infoHeader.width; j++) {
                uint8_t pixel[4];
                AAsset_read(asset,reinterpret_cast<char*>(&pixel), sizeof(pixel));
                imageData[0][i][j] = pixel[2] / 255.0f; // R
                imageData[1][i][j] = pixel[1] / 255.0f; // G
                imageData[2][i][j] = pixel[0] / 255.0f; // B
            }
        }
        AAsset_close(asset);
        return imageData;
    } else {
        return {};
    }

}
/*
    AAssetManager* assetManager = AAssetManager_fromJava(env, assetManagerObj);
    AAsset* asset = AAssetManager_open(assetManager, filename.c_str(), AASSET_MODE_BUFFER);
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return 159;
    }
    BMPHeader header;
    BMPInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (header.signature != 0x4D42) {
        return 789;
    }

    if (infoHeader.bitCount != 32) {
        return 456;
    }
    std::vector<std::vector<std::vector<float>>> imageData(3, std::vector<std::vector<float>>(infoHeader.height, std::vector<float>(infoHeader.width)));

    for (int i = infoHeader.height - 1; i >= 0; i--) {
        for (int j = 0; j < infoHeader.width; j++) {
            uint8_t pixel[4];
            file.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));

            imageData[0][i][j] = pixel[2] / 255.0f; // R
            imageData[1][i][j] = pixel[1] / 255.0f; // G
            imageData[2][i][j] = pixel[0] / 255.0f; // B
        }
    }
    return 111;*/

std::vector<std::vector<std::vector<float>>> readBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return {};
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (header.signature != 0x4D42) {
        std::cerr << "올바르지 않은 BMP 파일 형식입니다." << std::endl;
        return {};
    }

    if (infoHeader.bitCount != 32) {
        std::cerr << "이 코드는 32비트 BMP 파일에만 대응합니다." << std::endl;
        return {};
    }

    std::vector<std::vector<std::vector<float>>> imageData(3, std::vector<std::vector<float>>(infoHeader.height, std::vector<float>(infoHeader.width)));

    for (int i = infoHeader.height - 1; i >= 0; i--) {
        for (int j = 0; j < infoHeader.width; j++) {
            uint8_t pixel[4];
            file.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));

            imageData[0][i][j] = pixel[2] / 255.0f; // R
            imageData[1][i][j] = pixel[1] / 255.0f; // G
            imageData[2][i][j] = pixel[0] / 255.0f; // B
        }
    }

    return imageData;
}








#endif //DEEPCNNAPPTEST_BITMAP32BIT_H
