#include "WindowHints.h"

#include "eogll.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_WindowHints_wh_1create(JNIEnv* env, jclass clazz, jboolean resizable, jboolean decorated, jboolean floating, jboolean maximized, jboolean visible, jboolean focused, jboolean transparent) {
    EogllWindowHints e = eogllCreateWindowHints(resizable, decorated, floating, maximized, visible, focused, transparent);
    EogllWindowHints* ePtr = (EogllWindowHints*) malloc(sizeof(EogllWindowHints));
    *ePtr = e;
    return (jlong) ePtr;
}

JNIEXPORT void JNICALL Java_WindowHints_wh_1destroy(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    free(ePtr);
}

JNIEXPORT jboolean JNICALL Java_WindowHints_wh_1resizable(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    return ePtr->resizable;
}

JNIEXPORT jboolean JNICALL Java_WindowHints_wh_1decorated(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    return ePtr->decorated;
}

JNIEXPORT jboolean JNICALL Java_WindowHints_wh_1floating(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    return ePtr->floating;
}

JNIEXPORT jboolean JNICALL Java_WindowHints_wh_1maximized(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    return ePtr->maximized;
}

JNIEXPORT jboolean JNICALL Java_WindowHints_wh_1visible(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    return ePtr->visible;
}

JNIEXPORT jboolean JNICALL Java_WindowHints_wh_1focused(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    return ePtr->focused;
}


JNIEXPORT jboolean JNICALL Java_WindowHints_wh_1transparent(JNIEnv* env, jclass clazz, jlong ptr) {
    EogllWindowHints* ePtr = (EogllWindowHints*) ptr;
    return ePtr->transparent;
}

JNIEXPORT jlong JNICALL Java_WindowHints_wh_1create_1default(JNIEnv* env, jclass clazz) {
    EogllWindowHints e = eogllDefaultWindowHints();
    EogllWindowHints* ePtr = (EogllWindowHints*) malloc(sizeof(EogllWindowHints));
    *ePtr = e;
    return (jlong) ePtr;
}

#ifdef __cplusplus
}
#endif

