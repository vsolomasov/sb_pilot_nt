#include "./include/pilot.hpp"
#include "./include/pilot_nt_jni.hpp"

using JNI::Pilot_NT_JNI;

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_testPinpad(JNIEnv *jenv, jobject jobj) {
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->checkConnect();
	pilot->~Pilot_NT_JNI();
    delete pilot;
    pilot = 0;
    return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_transaction(JNIEnv *jenv, jobject jobj, jint jTypeOperation, jint jAmount) {
	int typeOperation = (int)jTypeOperation;
	int amount = (int)jAmount;
	Pilot_NT_JNI *pilot = new Pilot_NT_JNI();

	int res = null;
	if (typeOperation == 13) {
		res = pilot->rollbackLastTrx(amount);
	} else {
		res = pilot->cardOperation(&typeOperation, &amount);
	}

	pilot->~Pilot_NT_JNI();
	delete pilot;
	pilot = 0;
	return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_closeDay(JNIEnv *jEnv, jobject jobj) {
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->closeDay();
	pilot->~Pilot_NT_JNI();
    delete pilot;
    pilot = 0;
    return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_getStatistics(JNIEnv *jEnv, jobject jobj, jboolean jbool) {
	bool fullReport = (bool) jbool;
	Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
	int res = pilot->getStatistics(&fullReport);
	pilot->~Pilot_NT_JNI();
	delete pilot;
	pilot = 0;
	return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_showServiceMenu(JNIEnv *jenv, jobject jobj) {
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->showServiceMenu();
	pilot->~Pilot_NT_JNI();
    delete pilot;
    pilot = 0;
    return res;
}

JNIEXPORT jint JNICALL Java_ru_kinoplan_sbrf_ISbrfNative_setConfigData(JNIEnv *jEnv, jobject jobj, jstring jConfigs) {
    const char *configs = jEnv->GetStringUTFChars(jConfigs, 0);
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->setConfigs(configs);
	pilot->~Pilot_NT_JNI();
    delete pilot;
    pilot = 0;
    return res;
}
