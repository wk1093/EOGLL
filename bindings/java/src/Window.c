#include "Window.h"

#include "eogll.h"

JNIEXPORT jlong JNICALL Java_Window_w_1create(JNIEnv* env, jclass clazz, jint width, jint height, jstring title, jlong hints) {
    if (eogllInit() != EOGLL_SUCCESS) {
        printf("Failed to initialize EOGLL\n");
        return 0;
    }
    EogllWindowHints* eHints = (EogllWindowHints*) hints;
    const char* titleString = (*env)->GetStringUTFChars(env, title, NULL);
    EogllWindow* e = eogllCreateWindow(width, height, titleString, *eHints);
    return (jlong) e;
}

JNIEXPORT void JNICALL Java_Window_w_1destroy(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindow* e = (EogllWindow*) ptr;
    eogllDestroyWindow(e);
}

JNIEXPORT jboolean JNICALL Java_Window_w_1shouldClose(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindow* e = (EogllWindow*) ptr;
    return eogllWindowShouldClose(e);
}

JNIEXPORT void JNICALL Java_Window_w_1setShouldClose(JNIEnv* env, jclass clazz, jlong ptr, jboolean shouldClose) {
    EogllWindow* e = (EogllWindow*) ptr;
    eogllSetWindowShouldClose(e, shouldClose);
}

JNIEXPORT void JNICALL Java_Window_w_1pollEvents(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindow* e = (EogllWindow*) ptr;
    eogllPollEvents(e);
}

JNIEXPORT void JNICALL Java_Window_w_1swapBuffers(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindow* e = (EogllWindow*) ptr;
    eogllSwapBuffers(e);
}


