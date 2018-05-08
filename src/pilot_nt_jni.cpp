#include "../include/pilot_nt_jni.hpp"

namespace JNI {

    Pilot_NT_JNI::Pilot_NT_JNI() {
        dll = LoadLibrary(DDL_NAME);
    }

    int Pilot_NT_JNI::checkConnect() {
        if (!dll) return -1;
		try {
			test_function function = (test_function)GetProcAddress(dll, TEST_PINPAD);
			if (!function) return -2;
			return function();
		} catch (...) {
			FreeLibrary(dll);
			return -3;
		}
    }

    int Pilot_NT_JNI::setConfigs(const char *params) {
        if (!dll) return -1;
		try {
			set_config_data_function function = (set_config_data_function)GetProcAddress(dll, SET_CONFIG_DATA);
			if (!function) return -2;
			return function(params);
		} catch (...) {
			FreeLibrary(dll);
			return -3;
		}
    }

    int Pilot_NT_JNI::cardOperation(int *typeOperation, int *amount) {
        if (!dll) return -1;
		try {
			card_authorize_function function = (card_authorize_function)GetProcAddress(dll, CARD_AUTHORIZE);
			if (!function) return -2;
            struct auth_answer authAnswer;
		    memset(&authAnswer, 0, sizeof(authAnswer));
		    authAnswer.TType = *typeOperation;
		    authAnswer.Amount = *amount;
			return function(NULL, &authAnswer);;
		} catch (...) {
			FreeLibrary(dll);
			return -3;
        }
    }

    int Pilot_NT_JNI::closeDay() {
        if (!dll) return -1;
		try {
			close_day_function function = (close_day_function)GetProcAddress(dll, CLOSE_DAY);
			if (!function) return -2;
            struct auth_answer authAnswer;
			return function(&authAnswer);
		} catch (...) {
			FreeLibrary(dll);
			return -3;
		}
    }

	int Pilot_NT_JNI::getStatistics(bool *fullReport) {
		if (!dll) return -1;
		try {
			get_statistics function = (get_statistics)GetProcAddress(dll, GET_STATISCTICS);
			if (!function) return -2;
			struct auth_answer authAnswer;
			if (*fullReport) authAnswer.TType = 0;
			return function(&authAnswer);
		} catch(...) {
			FreeLibrary(dll);
			return -3;
		}
	}

    int Pilot_NT_JNI::showServiceMenu() {
        if (!dll) return -1;
		try {
			service_menu_function function = (service_menu_function)GetProcAddress(dll, SERVICE_MENU);
			if (!function) return -2;
			struct auth_answer authAnswer;
            return function(&authAnswer);
		} catch (...) {
			FreeLibrary(dll);
			return -3;
		}
    }

    Pilot_NT_JNI::~Pilot_NT_JNI() {
        FreeLibrary(dll);
    }
}
