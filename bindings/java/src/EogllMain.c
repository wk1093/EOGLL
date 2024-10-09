#include "EogllMain.h"

#include "eogll.h"

JNIEXPORT jint JNICALL Java_Eogll_init(JNIEnv* env, jclass clazz) {
    return eogllInit();
}

JNIEXPORT void JNICALL Java_Eogll_terminate(JNIEnv* env, jclass clazz) {
    eogllTerminate();
}

JNIEXPORT jstring JNICALL Java_Eogll_getVersionString(JNIEnv* env, jclass clazz) {
    const char* versionString = eogllGetVersionString();
    return (*env)->NewStringUTF(env, versionString);
}
