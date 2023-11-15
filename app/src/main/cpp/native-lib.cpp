#include <jni.h>
#include <string>
#include "bitmap32bit.h"
#include "SimpleCNN.h"
extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_deepcnnapptest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_deepcnnapptest_MainActivity_resultIntDataFromJNI(JNIEnv *env, jobject instance, jobject assetManager, jstring jfilename){
    const char* filename = env->GetStringUTFChars(jfilename, 0);
    AAssetManager* assetManagerPtr = AAssetManager_fromJava(env, assetManager);

    std::vector<std::vector<std::vector<float>>> imageData = readTestBMP(assetManagerPtr,filename);
   // __android_log_print(ANDROID_LOG_INFO, "안녕하세요", "%s", "test");

    const char* deepFileName = "cnn_model3.txt";
    AAsset *asset = AAssetManager_open(assetManagerPtr, deepFileName, AASSET_MODE_UNKNOWN);
    if (!asset) {
        return -999;
    }

    const void* data = AAsset_getBuffer(asset);
    off_t fileSize = AAsset_getLength(asset);
    std::string content(static_cast<const char*>(data), fileSize);

    AAsset_close(asset);

    cnn::CNN* cnn = new cnn::CNN();

    cnn->load(content);

    cnn->compile(cnn::OPTIMIZER::Momentum, cnn::LOSS::CategoricalCrossentropy);

    cnn::V3D* v = cnn->getLayers()[0]->getFilter3D();
    std::vector<float> result = cnn->predict(imageData);
    int maxIndex = max_element(result.begin(), result.end()) - result.begin();

    return maxIndex;
}
