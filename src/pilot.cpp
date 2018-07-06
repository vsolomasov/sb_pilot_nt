#include "../include/pilot.hpp"
#include <string.h>

namespace JNI {

	Pilot_NT_JNI::Pilot_NT_JNI() {
		dll = LoadLibrary(DDL_NAME);
	}

	int Pilot_NT_JNI::checkConnect() {
		if (!dll) return LOAD_ERROR;
		try {
			test_function function = (test_function)GetProcAddress(dll, TEST_PINPAD);
			if (!function) return FUNC_ERROR;
			return function();
		}
		catch (...) {
			FreeLibrary(dll);
			return EXCEPTION;
		}
	}

	int Pilot_NT_JNI::rollbackLastTrx(DWORD amount) {
		if (!dll) return LOAD_ERROR;
		try {
			rollback_trx_function function = (rollback_trx_function)GetProcAddress(dll, ROLLBACK_TRX);
			if (!function) return FUNC_ERROR;
			return function(amount, NULL);
		}
		catch (...) {
			FreeLibrary(dll);
			return EXCEPTION;
		}
	}

	int Pilot_NT_JNI::setConfigs(const char *params) {
		if (!dll) return LOAD_ERROR;
		try {
			set_config_data_function function = (set_config_data_function)GetProcAddress(dll, SET_CONFIG_DATA);
			if (!function) return FUNC_ERROR;
			return function(params);
		}
		catch (...) {
			FreeLibrary(dll);
			return EXCEPTION;
		}
	}

	int Pilot_NT_JNI::cardOperation(int *typeOperation, int *amount) {
		if (!dll) return LOAD_ERROR;
		try {
			card_authorize_function function = (card_authorize_function)GetProcAddress(dll, CARD_AUTHORIZE);
			if (!function) return FUNC_ERROR;
			struct auth_answer authAnswer;
			memset(&authAnswer, 0, sizeof(authAnswer));
			authAnswer.TType = *typeOperation;
			authAnswer.Amount = *amount;
			return function(NULL, &authAnswer);
		}
		catch (...) {
			FreeLibrary(dll);
			return EXCEPTION;
		}
	}

	int Pilot_NT_JNI::closeDay() {
		if (!dll) return LOAD_ERROR;
		try {
			close_day_function function = (close_day_function)GetProcAddress(dll, CLOSE_DAY);
			if (!function) return FUNC_ERROR;
			struct auth_answer authAnswer;
			return function(&authAnswer);;
		}
		catch (...) {
			FreeLibrary(dll);
			return EXCEPTION;
		}
	}

	int Pilot_NT_JNI::getStatistics(bool *fullReport) {
		if (!dll) return LOAD_ERROR;
		try {
			get_statistics_function function = (get_statistics_function)GetProcAddress(dll, GET_STATISCTICS);
			if (!function) return FUNC_ERROR;
			struct auth_answer authAnswer;
			if (*fullReport) authAnswer.TType = 0;
			return function(&authAnswer);
		}
		catch (...) {
			FreeLibrary(dll);
			return EXCEPTION;
		}
	}

	int Pilot_NT_JNI::showServiceMenu() {
		if (!dll) return LOAD_ERROR;
		try {
			service_menu_function function = (service_menu_function)GetProcAddress(dll, SERVICE_MENU);
			if (!function) return FUNC_ERROR;
			struct auth_answer authAnswer;
			return function(&authAnswer);
		}
		catch (...) {
			FreeLibrary(dll);
			return EXCEPTION;
		}
	}

	Pilot_NT_JNI::~Pilot_NT_JNI() {
		FreeLibrary(dll);
	}
}
