#include <jni.h>

#ifndef _Included_ru_kinoplan_sbrf_ISbrfNative
#define _Included_ru_kinoplan_sbrf_ISbrfNative
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_testPinpad
  (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_setConfigData
  (JNIEnv *, jobject, jstring);

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_cardTransaction
  (JNIEnv *, jobject, jint, jint);

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_closeDay
  (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_showServiceMenu
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
