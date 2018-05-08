#include "../include/pilot_nt_jni.hpp"
#include "../include/ru_kinoplan_sbrf_ISbrfNative.hpp"

using JNI::Pilot_NT_JNI;

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_testPinpad(JNIEnv *jenv, jobject jobj) {
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->checkConnect();
    delete pilot;
    pilot = 0;
    return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_setConfigData(JNIEnv *jenv, jobject jobj, jstring jConfigs) {
    const char *configs = jenv->GetStringUTFChars(jConfigs, 0);
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->setConfigs(configs);
    delete pilot;
    pilot = 0;
    return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_cardTransaction(JNIEnv *jenv, jobject jobj, jint jTypeOperation, jint jAmount) {
    int typeOperation = (int) jTypeOperation;
    int amount = (int) jAmount;
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->cardOperation(&typeOperation, &amount);
    delete pilot;
    pilot = 0;
    return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_closeDay(JNIEnv *jenv, jobject jobj) {
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->closeDay();
    delete pilot;
    pilot = 0;
    return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_getStatistics(JNIEnv *jenv, jobject jobj, jboolean jbool) {
	bool fullReport = (bool) jbool;
	Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
	int res = pilot->getStatistics(&fullReport);
	delete pilot;
	pilot = 0;
	return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_showServiceMenu(JNIEnv *jenv, jobject jobj) {
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->showServiceMenu();
    delete pilot;
    pilot = 0;
    return res;
}

