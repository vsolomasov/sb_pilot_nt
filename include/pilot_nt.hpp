/**
 * @file pilot_nt.h
 * @author A. Brik, S. Papazov
 * @date 12 June 2016
 * @brief File containing example of doxygen usage for quick reference.
 */
#ifndef _PILOT_NT_H_
#define _PILOT_NT_H_

#include <windows.h>

#ifdef UPOS
  #include "global.h"
  #define PILOT_NT_API __declspec(dllexport)
#else
  #define PILOT_NT_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif
#pragma pack(1)

/** Идентификатор контекста операции */
typedef long CONTEXT_PTR;

/** Идентификаторы параметров, которые можно получить или передать через контекст операции */
typedef enum {
PAR_LLT_ID          = 1,    ///< [out] Номер программы лояльности в который попала карта, целое. Параметр возвращается при вызове функций ::card_authorize15 и ::ReadCardContext
PAR_PAN             = 2,    ///< [out] Маскированный номер карты, строка. Параметр возвращается при вызове функций ::ReadCardContext
PAR_HASH            = 3,    ///< [out] Хэш. Строка. Параметр возвращается функцией ::ReadCardContext
PAR_CARD_TYPE       = 4,    ///< [out] Тип карты. Целое. Параметр возвращается функцией ::ReadCardContext
PAR_OWN_CARD        = 5     ///< [out] Признак "Карта выпущена Сбербанком". Целое. Параметр возвращается функцией ::ReadCardContext
} EParameterName;


/** Длина буфера кода авторизации */
#define AUTH_CODE_LEN     7
/** Длина буфера номера карты */
#define CARD_ID_LEN       25
/** Длина буфера хеша карты */
#define CARD_HASH_LEN     41
/** Размер даты и времени операции */
#define TRANSDATE_LEN     20
/** Длина буфера номера ссылки транзакции */
#define RRN_LEN           13
/** Длина буфера третьей дорожки карты */
#define CARD_TRACK3_LEN   104

/**
 * @defgroup FINANCIAL Финансовые операции
 */
/**@{*/

/** Типы обслуживаемых карт */
typedef enum {
CT_USER    = 0,  ///< Выбор типа карты из меню, либо автоматически
CT_VISA    = 1,  ///< Карта Visa
CT_EUROCARD= 2,  ///< Карта Eurocard/Mastercard
CT_CIRRUS  = 3,  ///< Карта Cirrus/Maestro
CT_AMEX    = 4,  ///< Карта Amex
CT_DINERS  = 5,  ///< Карта DinersCLub
CT_ELECTRON= 6,  ///< Карта VisaElectron
CT_PRO100  = 7,  ///< Карта PRO100
CT_CASHIER = 8,  ///< Карта кассира
CT_SBERCARD= 9,  ///< Карта Сберкарт
CT_MIR     = 10  ///< Карта МИР
} CardTypes;

/** Типы операций */
typedef enum {
OP_PURCHASE     = 1,   ///< Оплата покупки
OP_CASH         = 2,   ///< Выдача наличных
OP_RETURN       = 3,   ///< Возврат либо отмена покупки
OP_BALANCE      = 4,   ///< Баланс
OP_FUNDS        = 6,   ///< Безнал.перевод
OP_ADD_AUTH     = 42,  ///< Добавочная предавторизация
OP_CANC_AUTH    = 43,  ///< Отмена предавторизации
OP_PREAUTH      = 51,  ///< Предавторизация
OP_COMPLETION   = 52,  ///< Завершение расчета
OP_CASHIN       = 53,  ///< Взнос наличных
OP_CASHIN_COMP  = 54,  ///< Подтверждение взноса
OP_PILOT_START  = 55,  ///< Запуск мониторинга
OP_PILOT_STATUS = 56,  ///< Опрос статуса  мониторинга
OP_PILOT_STOP   = 57,  ///< Остановка мониторинга
OP_SETPIN       = 58,  ///< Установка ПИНа
OP_CHANGEPIN    = 59,  ///< Смена ПИНа
} OpetationTypes;

/**
 * Основные параметры операции
 * Структура, используемая для описания операции и получения результатов выполнения операции.
 */
struct auth_answer{
   int TType;             /**< [in] тип транзакции. см ::OpetationTypes */
   unsigned long Amount;  /**< [in] сумма в копейках                    */
   char RCode[3];         /**< [out] код результата авторизации         */
   char AMessage[16];     /**< [out] текст результата авторизации       */
   int  CType;            /**< [in,out] тип карты                       */
   char* Check;           /**< [out] образ чека, должен освобождаться GlobalFree в вызывающей программе */
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer Основные параметры операции. См. ::auth_answer
 *  @return int Код ошибки.
 */
PILOT_NT_API int card_authorize(char *track2, struct auth_answer *auth_answer);

/** @struct auth_answer2
 *  @brief Расширение для получения кода авторизации успешной операции.
 */
struct auth_answer2{
  struct auth_answer auth_answ;  /**< [in]  Основные параметры операции. См. ::auth_answer */
  char AuthCode[AUTH_CODE_LEN];  /**< [out] Код авторизации. 7 байт.              */
};

/** @brief Выполнение операций по картам
 *  @param[out] track2 - данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer - см. ::auth_answer2
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize2(char *track2, struct auth_answer2 *auth_answer);

/** @struct auth_answer3
 *  @brief Расширение для получения кода авторизации успешной операции и номера карты.
 */
struct auth_answer3{
  struct auth_answer auth_answ; /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char AuthCode[AUTH_CODE_LEN]; /**< [out] Код авторизации. 7 байт.                       */
  char CardID[CARD_ID_LEN];     /**< [out] Идентификатор карты. 25 байт. Для международных карт все символы, кроме первых 6 и последних 4, будут заменены символами ‘*’.*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer3
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize3(char *track2, struct auth_answer3 *auth_answer);

/** @struct auth_answer4
 *  @brief Расширение для получения кода авторизации успешной операции, номера карты, кода ответа, времени операции и номера операции на кассе.
 */
struct auth_answer4{
  struct auth_answer auth_answ; /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char AuthCode[AUTH_CODE_LEN]; /**< [out] Код авторизации. 7 байт.                            */
  char CardID[CARD_ID_LEN];     /**< [out] Идентификатор карты. 25 байт.                       */
  int  ErrorCode;               /**< [out] Код ошибки.                                         */
  char TransDate[TRANSDATE_LEN];/**< [out] Дата и время операции                               */
  int  TransNumber;             /**< [out] Номер операции за опер. день, см. номер на чеке     */
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer4
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize4(char *track2, struct auth_answer4 *auth_answer);

/** @struct auth_answer5
 *  @brief Расширение для получения кода авторизации успешной операции и номера ссылки (RRN).
 */
struct auth_answer5{
  struct auth_answer auth_answ;   /**< [in]  Основные параметры операции. См. ::auth_answer */
  char   RRN[RRN_LEN];            /**< [in,out] Номер ссылки операции, присвоеный хостом. Используется
                                                для операций возврат и множественной авторизации.
                                                Содержит уникальный 12-значный ссылочный номер.
                                                При предавторизации это поле является выходным
                                                (его заполняет библиотека pilot_nt.dll), а при
                                                завершении расчета – входным (значение должно 
                                                быть заполнено вызывающей программой; оно должно
                                                совпадать со значением, возвращенным при предавторизации).*/
  char   AuthCode[AUTH_CODE_LEN]; /**< [out] Код авторизации. 7 байт.                       */
};

/** @brief Выполнение операций по картам
 *  @param[out] track2 - данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer - см. ::auth_answer5
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize5(char *track2, struct auth_answer5 *auth_answer);

/** @struct auth_answer6
 *  @brief Расширение для получения данных как при выполнении auth_answer5 и auth_answer4.
 */
struct auth_answer6{
  struct auth_answer auth_answ;    /**< [in, out]  Основные параметры операции. См. ::auth_answer  */
  char   AuthCode[AUTH_CODE_LEN];  /**< [out] Код авторизации. 7 байт.                             */
  char   CardID[CARD_ID_LEN];      /**< [out] Идентификатор карты. 25 байт.                        */
  int    ErrorCode;                /**< [out] Код ошибки.                                          */
  char   TransDate[TRANSDATE_LEN]; /**< [out] Дата и время операции                                */
  int    TransNumber;              /**< [out] Номер операции за опер. день, см. номер на чеке      */
  char   RRN[RRN_LEN];            /**< [in,out] Номер ссылки операции, присвоеный хостом. Используется
                                                для операций возврат и множественной авторизации.
                                                Содержит уникальный 12-значный ссылочный номер.
                                                При предавторизации это поле является выходным
                                                (его заполняет библиотека pilot_nt.dll), а при
                                                завершении расчета – входным (значение должно 
                                                быть заполнено вызывающей программой; оно должно
                                                совпадать со значением, возвращенным при предавторизации).*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer6
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize6(char *track2, struct auth_answer6 *auth_answer);

/** Максимальный размер значения тега платежной системы.*/
#define MAX_PAYMENT_ITEM  128
/** @struct payment_info_item
 *  @brief This structure blah blah blah...
 */
struct payment_info_item{
  DWORD  dwTag;                    /**< Тег платежной системы */
  char   Value[MAX_PAYMENT_ITEM];  /**< Значение тэга платежной системы. 128 байт. ::MAX_PAYMENT_ITEM */
  BYTE   Flags;                    /**< must be 0x40 for immediate sending    */
  void*  pNextItem;                /**< ?? */
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer6
 *  @param[in,out] payinfo см. ::payment_info_item
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize6_ext(
  char *track2,
  struct auth_answer6 *auth_answer,
  struct payment_info_item *payinfo
);

/** @struct auth_answer7
 *  @brief Расширение для получения кода авторизации успешной операции, номера карты и признака принадлежности карты Сбербанку.
 */
struct auth_answer7{
  struct auth_answer auth_answ;    /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char   AuthCode[AUTH_CODE_LEN];  /**< [out] Код авторизации. 7 байт.                            */
  char   CardID [CARD_ID_LEN];     /**< [out] Идентификатор карты. 25 байт.                       */
  int    SberOwnCard;              /**< [out] Флаг принадлежности карты Сбербанку                 */
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer7
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize7(char *track2, struct auth_answer7 *auth_answer);

/** Размер буфера шифрованого номера карты и срока действия*/
#define MAX_ENCR_DATA  32

/** @struct auth_answer8
 *  @brief Расширение для получения данных как при выполнении auth_answer5 и auth_answer4, а также номера карты и срока действия в шифрованном виде.
 */
struct auth_answer8{
  struct auth_answer auth_answ;      /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char   AuthCode[AUTH_CODE_LEN];    /**< [out] Код авторизации. 7 байт.                            */
  char   CardID[CARD_ID_LEN];        /**< [out] Идентификатор карты. 25 байт.                       */
  int    ErrorCode;                  /**< [out] Код ошибки.                                         */
  char   TransDate[TRANSDATE_LEN];   /**< [out] Дата и время операции                               */
  int    TransNumber;                /**< [out] Номер операции за опер. день, см. номер на чеке     */
  char   RRN[RRN_LEN];               /**< [in,out] Номер ссылки операции, присвоеный хостом. Используется
                                                для операций возврат и множественной авторизации.
                                                Содержит уникальный 12-значный ссылочный номер.
                                                При предавторизации это поле является выходным
                                                (его заполняет библиотека pilot_nt.dll), а при
                                                завершении расчета – входным (значение должно 
                                                быть заполнено вызывающей программой; оно должно
                                                совпадать со значением, возвращенным при предавторизации).*/
  char   EncryptedData[MAX_ENCR_DATA*2+1]; /**< [in, out] шифрованый номер карты и срок действия.    */
};
/** @brief Выполнение операций по картам
 *  @note Функция удваивает количество воззвращаемых чеков. При работе по протоколу ТТК поле EncryptedData не заполняется.
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer8
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize8(char *track2, struct auth_answer8 *auth_answer);

/** @struct preauth_rec
 *  @brief  Структура для описания одной операции в списке, по которой нужно выполнить завершение расчета.
 */
struct preauth_rec{
  unsigned long  Amount;          /**< [in] сумма в копейках              */
  char   RRN[RRN_LEN];            /**< [in,out] Номер ссылки операции, присвоеный хостом. Используется
                                                для операций возврат и множественной авторизации.
                                                Содержит уникальный 12-значный ссылочный номер.
                                                При предавторизации это поле является выходным
                                                (его заполняет библиотека pilot_nt.dll), а при
                                                завершении расчета – входным (значение должно
                                                быть заполнено вызывающей программой; оно должно
                                                совпадать со значением, возвращенным при предавторизации).*/
  char           Last4Digits[5];  /**< [in] последние 4 цифры номера карты*/
  unsigned short ErrorCode;       /**< [out] Код ошибки.                  */
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_ans см. ::auth_answer8
 *  @param[in,out] pPreAuthList Массив структур с описанием, по которым требуется выполнить "Завершение расчета". См. ::preauth_rec
 *  @param[in] NumAuths Общее количество операций, по которым требуется выполнить "Завершение расчета".
 *  @return int Код ошибки.
 */
PILOT_NT_API int card_complete_multi_auth8(
  char* track2,
  struct auth_answer8* auth_ans,
  struct preauth_rec*  pPreAuthList,
  int NumAuths
);

/** @struct auth_answer9
*  @brief Расширение для получения кода авторизации успешной операции, номера карты, хеша номера карты и признака принадлежности карты Сбербанку.
 */
struct auth_answer9{
  auth_answer   ans;                     /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char          AuthCode[AUTH_CODE_LEN]; /**< [out] Код авторизации. 7 байт.                            */
  char          CardID [CARD_ID_LEN];    /**< [out] Идентификатор карты. 25 байт.                       */
  int           SberOwnCard;             /**< [out] Флаг принадлежности карты Сбербанку                 */
  char          Hash[CARD_HASH_LEN];     /**< [in, out] хеш SHA1 от номера карты, в формате ASCII с нулевым байтом в конце. 40 байт.*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer9
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize9(char *track2, struct auth_answer9 *auth_answer);

/** @struct auth_answer10
 *  @brief This structure blah blah blah...
 */
struct auth_answer10{
  auth_answer   ans;               /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char   AuthCode[AUTH_CODE_LEN];  /**< [out] Код авторизации. 7 байт.              */
  char   CardID[CARD_ID_LEN];      /**< [out] Идентификатор карты. 25 байт. Для международных карт все символы, кроме первых 6 и последних 4, будут заменены символами ‘*’.*/
  int    ErrorCode;                /**< [out] Код ошибки.                                         */
  char   TransDate[TRANSDATE_LEN]; /**< [out] Дата и время операции                               */
  int    TransNumber;              /**< [out] Номер операции за опер. день, см. номер на чеке     */
  int    SberOwnCard;              /**< [out] Флаг принадлежности карты Сбербанку                 */
  char   Hash[CARD_HASH_LEN];      /**< [in, out] хеш от номера карты, в формате ASCII с нулевым байтом в конце*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer10
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize10(char *track2, struct auth_answer10 *auth_answer);

/** @struct auth_answer11
 *  @brief Расширение для получения кода авторизации успешной операции, номера карты, кода ответа,
 *         даты, времени и номера операции, хеша номера карты, признака принадлежности карты Сбербанку, третьей дорожки карты.
 
 */
struct auth_answer11{
  auth_answer   ans;               /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char   AuthCode[AUTH_CODE_LEN];  /**< [out] Код авторизации. 7 байт.              */
  char   CardID[CARD_ID_LEN];      /**< [out] Идентификатор карты. 25 байт. Для международных карт все символы, кроме первых 6 и последних 4, будут заменены символами ‘*’.*/
  int    ErrorCode;                /**< [out] Код ошибки.                                         */
  char   TransDate[TRANSDATE_LEN]; /**< [out] Дата и время операции                               */
  int    TransNumber;              /**< [out] Номер операции за опер. день, см. номер на чеке     */
  int    SberOwnCard;              /**< [out] Флаг принадлежности карты Сбербанку                 */
  char   Hash[CARD_HASH_LEN];      /**< [in, out] хеш SHA1 от номера карты, в формате ASCII с нулевым байтом в конце. 40 байт.*/
  char   Track3[CARD_TRACK3_LEN];  /**< [out] Третья дорожка карты*/
  unsigned long RequestID;         /**< [in,out] Уникальный номер операции. Только PCI DSS решения.*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer11
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize11(char *track2, struct auth_answer11 *auth_answer);

/** @struct auth_answer12
 *  @brief Расширение card_authorize11 возможностью указать номер отдела и задать/получить номер ссылки.
 */
struct auth_answer12 {
  auth_answer   ans;              /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char   AuthCode[AUTH_CODE_LEN]; /**< [out] Код авторизации. 7 байт.              */
  char   CardID[CARD_ID_LEN];     /**< [out] Идентификатор карты. 25 байт. Для международных карт все символы, кроме первых 6 и последних 4, будут заменены символами ‘*’.*/
  int    ErrorCode;               /**< [out] Код ошибки.                                         */
  char   TransDate[TRANSDATE_LEN];/**< [out] Дата и время операции                               */
  int    TransNumber;             /**< [out] Номер операции за опер. день, см. номер на чеке     */
  int    SberOwnCard;             /**< [out] Флаг принадлежности карты Сбербанку                 */
  char   Hash[CARD_HASH_LEN];     /**< [in, out] хеш SHA1 от номера карты, в формате ASCII с нулевым байтом в конце. 40 байт.*/
  char   Track3[CARD_TRACK3_LEN]; /**< [out] третья дорожка карты*/
  unsigned long RequestID;        /**< [in,out] Уникальный номер операции. Только PCI DSS решения.*/
  DWORD  Department;              /**< [in] Порядковый номер отдела от 0 до 14-ти, включительно.
                                            При установке номера отдела в 0xFFFFFFFF, номер отдела
                                            будет запрошен через интерфейс терминала после вставки карты.
                                            Если номер отдела будет указан вне настроенного диапазона,
                                            то терминал вернет код ошибки 4191. */
  char   RRN[RRN_LEN];            /**< [in,out] Номер ссылки операции, присвоеный хостом. Используется
                                                для операций возврат и множественной авторизации.
                                                Содержит уникальный 12-значный ссылочный номер.
                                                При предавторизации это поле является выходным
                                                (его заполняет библиотека pilot_nt.dll), а при
                                                завершении расчета – входным (значение должно 
                                                быть заполнено вызывающей программой; оно должно
                                                совпадать со значением, возвращенным при предавторизации).*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer12
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize12(char *track2, struct auth_answer12 *auth_answer);

/** Максимальный размер длинны AID чиповой карты (в виде ASCIIZ-строки)*/
#define MAX_AID_ASCII_LEN   (32+1)
/** Максимальный размер длинны имени клиента на карте*/
#define MAX_CARD_NAME_LEN   (32+1)
/** Максимальный размер текста ошибки, возвращаемый UPOS*/
#define MAX_FULL_ERROR_TEXT 128

/** @struct auth_answer13
 *  @brief Расширение card_authorize11 возможностью указать номер отдела, код вылюты и получить способ чтения карты, имя клиента карты и AID.
 */
struct auth_answer13{

  auth_answer   ans;              /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char   AuthCode[AUTH_CODE_LEN]; /**< [out] Код авторизации. 7 байт.                       */
  char   CardID[CARD_ID_LEN];     /**< [out] Идентификатор карты. 25 байт. Для международных карт все символы, кроме первых 6 и последних 4, будут заменены символами ‘*’.*/
  int    ErrorCode;               /**< [out] Код ошибки.                                         */
  char   TransDate[TRANSDATE_LEN];/**< [out] Дата и время операции                               */
  int    TransNumber;             /**< [out] Номер операции за опер. день, см. номер на чеке     */
  int    SberOwnCard;             /**< [out] Флаг принадлежности карты Сбербанку                 */
  char   Hash[CARD_HASH_LEN];     /**< [in, out] хеш SHA1 от номера карты, в формате ASCII с нулевым байтом в конце. 40 байт.*/
  char   Track3[CARD_TRACK3_LEN]; /**< [out] третья дорожка карты*/
  DWORD  RequestID;               /**< [in,out] Уникальный номер операции. Только PCI DSS решения.*/
  DWORD  Department;              /**< [in] Порядковый номер отдела от 0 до 14-ти, включительно.
                                            При установке номера отдела в 0xFFFFFFFF, номер отдела
                                            будет запрошен через интерфейс терминала после вставки карты.
                                            Если номер отдела будет указан вне настроенного диапазона,
                                            то терминал вернет код ошибки 4191. */
  char   RRN[RRN_LEN];            /**< [in,out] Номер ссылки операции, присвоеный хостом. Используется
                                                для операций возврат и множественной авторизации.
                                                Содержит уникальный 12-значный ссылочный номер.
                                                При предавторизации это поле является выходным
                                                (его заполняет библиотека pilot_nt.dll), а при
                                                завершении расчета – входным (значение должно
                                                быть заполнено вызывающей программой; оно должно
                                                совпадать со значением, возвращенным при предавторизации).*/
  DWORD  CurrencyCode;            /**< [in] Международный код валюты (810, 643, 840, 978 и т.д.) */
  char   CardEntryMode;           /**< [out] Способ чтения карты ('D'-магн.полоса, 'M'-ручной ввод, 'C'-чип, 'E'-бесконтакт EMV, 'R'-бесконтакт magstripe, 'F'-fallback)*/
  char   CardName[MAX_CARD_NAME_LEN]; /**< [out] Название типа карты */
  char   AID[MAX_AID_ASCII_LEN];  /**< [out] Application ID чиповой карты (в виде ASCIIZ-строки)*/
  char   FullErrorText[MAX_FULL_ERROR_TEXT]; /**< [out] Полный текст сообщения об ошибке*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer13
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize13(char *track2, struct auth_answer13 *auth_answer);

/** Максимальный размер наименования или кода товара, включая завершающий ноль*/
#define MAX_GOODS_DATA  25
/** @struct auth_answer14
 *  @brief Расширение card_authorize13 возможностью указать информацию о товаре.
 */
struct auth_answer14 {
  auth_answer   ans;               /**< [in, out]  Основные параметры операции. См. ::auth_answer */
  char   AuthCode[AUTH_CODE_LEN];  /**< [out] Код авторизации. 7 байт.              */
  char   CardID[CARD_ID_LEN];      /**< [out] Идентификатор карты. 25 байт. Для международных карт все символы, кроме первых 6 и последних 4, будут заменены символами ‘*’.*/
  int    ErrorCode;                /**< [out] Код ошибки.                                         */
  char   TransDate[TRANSDATE_LEN]; /**< [out] Дата и время операции                               */
  int    TransNumber;              /**< [out] Номер операции за опер. день, см. номер на чеке     */
  int    SberOwnCard;              /**< [out] Флаг принадлежности карты Сбербанку                 */
  char   Hash[CARD_HASH_LEN];      /**< [in, out] хеш SHA1 от номера карты, в формате ASCII с нулевым байтом в конце. 40 байт.*/
  char   Track3[CARD_TRACK3_LEN];  /**< [out] третья дорожка карты*/
  DWORD  RequestID;                /**< [in,out] Уникальный номер операции. Только PCI DSS решения.*/
  DWORD  Department;              /**< [in] Порядковый номер отдела от 0 до 14-ти, включительно.
                                            При установке номера отдела в 0xFFFFFFFF, номер отдела
                                            будет запрошен через интерфейс терминала после вставки карты.
                                            Если номер отдела будет указан вне настроенного диапазона,
                                            то терминал вернет код ошибки 4191. */
  char   RRN[RRN_LEN];            /**< [in,out] Номер ссылки операции, присвоеный хостом. Используется
                                                для операций возврат, множественной авторизации и завершения расчета.
                                                Содержит уникальный 12-значный ссылочный номер.
                                                При предавторизации это поле является выходным
                                                (его заполняет библиотека pilot_nt.dll), а при
                                                завершении расчета – входным (значение должно 
                                                быть заполнено вызывающей программой; оно должно
                                                совпадать со значением, возвращенным при предавторизации).*/
  DWORD  CurrencyCode;             /**< [in] Международный код валюты (810, 643, 840, 978 и т.д.) */
  char   CardEntryMode;            /**< [out] Способ чтения карты ('D'-магн.полоса, 'M'-ручной ввод, 'C'-чип, 'E'-бесконтакт EMV, 'R'-бесконтакт magstripe, 'F'-fallback)*/
  char   CardName[MAX_CARD_NAME_LEN]; /**< [out] Название типа карты */
  char   AID[MAX_AID_ASCII_LEN];   /**< [out] Application ID чиповой карты (уже в виде ASCIIZ-строки)*/
  char   FullErrorText[MAX_FULL_ERROR_TEXT]; /**< [out] Полный текст сообщения об ошибке*/
  DWORD  GoodsPrice;                /**< [in] Цена за единицу товара, коп (34.99->3499)*/
  DWORD  GoodsVolume;               /**< [in] Количество товара, в тыс. долях (30.234->30234)*/
  char   GoodsCode[MAX_GOODS_DATA]; /**< [in] Код товара во внешней системе*/
  char   GoodsName[MAX_GOODS_DATA]; /**< [in] Наименование товара во внешней системе*/
};

/** @brief Выполнение операций по картам
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer14
 *  @param[in,out] payinfo Информация для платежной системы
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize14(
  char *track2,
  struct auth_answer14 *auth_answer,
  struct payment_info_item *payinfo
);


/** @brief Выполнение операций по картам
 *  @note Функция дополнительно принимает входной и выходной контексты операции. Во входном контексте в библиотеку передаются дополнительные параметры операции
 *  в выходном контексте возвращается расширенный результат операции. Параметры, которые могут переданы или полученны через контекст операции
 *  перечислены в EParameterName.
 *  @param[in] track2 данные дорожки карты с магнитной полосой. Если NULL, то будет предложено считать карту.
 *  @param[in,out] auth_answer см. ::auth_answer14
 *  @param[in,out] payinfo Информация для платежной системы
 *  @param[in] dataIn см. ::ctxAlloc
 *  @param[in] dataOut см. ::ctxAlloc
 *  @return int Код ошибки.
 */
PILOT_NT_API int  card_authorize15(
  char *track2,
  struct auth_answer14 *auth_answer,
  struct payment_info_item *payinfo,
  CONTEXT_PTR dataIn,
  CONTEXT_PTR dataOut
);

/**@}*/

/**
 * @defgroup SERVICE Служебные операции
 */
/**@{*/

 /** @brief Получить номер терминала как строку
 *  @note Функция не поддерживается по протоколу TTK для PCI-DSS решений.
 *  @param[out] pTerminalID Строковое представление номера терминала. 9 байт.
 *  @return int Код ошибки.
 */
PILOT_NT_API int GetTerminalID(char* pTerminalID);

/** @brief Открыть в техническое меню на пинпаде
 *  @note По завершении поле auth_answer.Check может содержать образ документа для печати.
 *  @param[out] auth_answer Буфер результата операции
 *  @return int Код ошибки.
 */
PILOT_NT_API int ServiceMenu(struct auth_answer *auth_answer);
 
/** @brief Закрытие дня.
 *  @note  Поля TType, Amount, CType заполнять не нужно.
 *  @param[in,out] auth_answer см. ::auth_answer
 *  @return int Код ошибки.
 */
PILOT_NT_API int close_day(struct auth_answer *auth_answer);

/** @brief Закрытие дня.
 *  @note  Поля auth_answer::TType, auth_answer::Amount, auth_answer::CType заполнять не нужно.
 *  char* Check
Содержит образ отчета по картам, который вызывающая программа должна отправить на печать, а затем освободить вызовом функции GlobalFree().
Может иметь значение NULL. В этом случае никаких действий с ним вызывающая программа выполнять не должна.
 *  @param[in,out] auth_answer см. ::auth_answer
 *  @param[in,out] iParams Дополнительная информация для передачи на хост Сбербанка (например, о наличном обороте кассы за смену).
 *  В текущей версии поддерживается следующий формат строки:
 *  1;число_оплат_за_наличные;сумма_оплат_за_наличные;номер кассовой смены
 *  Число 1 указывает, что следующие два параметра содержат количество наличных платежей и их сумму в копейках.
 *  Пример: «1;55;20010000;2334» - означает, что за смену было 55 оплат наличными на общую сумму 200100.00 руб, номер кассовой смены 2334.
 *  Параметр номер смены ккм используется для контроля уникальности, если в течении смены выполнялось несколько сверок итогов.
 *  @return int Код ошибки.
 */
PILOT_NT_API int close_day_info(struct auth_answer *auth_answer, const char* iParams);

/** @brief Получение текущего отчета за текущую смену
 *  @param[in, out] auth_answer См. auth_answer. При значении поля TType = 0 формируется краткий отчет, иначе - полный
 *  @return int Код ошибки.
 */
PILOT_NT_API int get_statistics(struct auth_answer *auth_answer);

/** @brief Получение номера версии библиотеки pilot_nt.dll
 *  @return Версия как целое число в формате 0x00VVRRBB. VV - версия, RR - релиз, BB - сборка
 */
PILOT_NT_API unsigned int GetVer();

 /** @brief Установить конфигурационные параметры в pinpad.ini
 *  @param[in] pConfData Строка формата param1=value1;...paramN=valueN;
 *  @return int Код ошибки.
 */
PILOT_NT_API int SetConfigData(const char* pConfData);

/** @brief Деинициализация библиотеки pilot_nt.dll
 *  @note Выполняется отключение от библиотеки gate.dll
 */
PILOT_NT_API void Done();

/** @brief Асинхронное включение чтения карты
 *  @param[in] hDestWindow Хендл окна, которое будет получать сообщения о чтении карты
 *  @param[in] message Идентификатор сообщение о чтении карты
 *  @return int Код ошибки.
 */
PILOT_NT_API int EnableReader (HWND hDestWindow, UINT message);

/** @brief Асинхронное выключение чтения карты
 *  @return int Код ошибки.
 */
PILOT_NT_API int DisableReader();

/** @brief Проверка готовности пинпада
 *  @note Функция проверяет наличие пинпада. При успешном выполнении возвращает 0 (пинпад подключен), при неудачном – код ошибки (пинпад не подключен или неисправен).
 *  @return int Код ошибки.
 */
PILOT_NT_API int TestPinpad();

/** @brief Функция переводит последнюю успешную транзакцию в «подвешенное» состояние. Если транзакция находится в этом состоянии, то при следующем сеансе связи с банком она будет отменена..
 *  @note Функция сверяет переданные извне параметры (сумму и код авторизации) со значениями в последней успешной операции, которая была проведена через библиотеку. Если хотя бы один параметр не совпадает, функция возвращает код ошибки 4140 и не выполняет никаких действий.
 *  @param dwAmount Сумма операции (в копейках)
 *  @param pAuthCode Код авторизации.
 *  @return int Код ошибки.
 */
PILOT_NT_API int SuspendTrx (DWORD dwAmount, char* pAuthCode);

/** @brief Функция возвращает последнюю успешную транзакцию в «нормальное» состояние.
 *  После этого транзакция будет включена в отчет и спроцессирована как успешная.
 *  Перевести ее снова в «подвешенное» состояние будет уже нельзя.
 *  @note Функция сверяет переданные извне параметры (сумму и код авторизации) со
 *  значениями в последней успешной операции, которая была проведена через библиотеку.
 *  Если хотя бы один параметр не совпадает, функция возвращает код ошибки 4140 и не выполняет никаких действий.
 *  @param dwAmount Сумма операции (в копейках)
 *  @param pAuthCode Код авторизации.
 *  @return int Код ошибки.
 */
PILOT_NT_API int CommitTrx  (DWORD dwAmount, char* pAuthCode);

/** @brief Функция вызывает немедленную отмену последней успешной операции
 *  @note Операция может быть предварительно возможно, ранее
 *  переведенную в «подвешенное» состояние, хотя это и не обязательно). Если транзакция уже
 *  была возвращена в «нормальное» состояние функцией CommitTrx(), то функция RollbackTrx()
 *  завершится с кодом ошибки 4141, не выполняя никаких действий.Функция сверяет переданные извне параметры (сумму и код авторизации) со значениями
 *  в последней успешной операции, которая была проведена через библиотеку. Если хотя бы один
 *  параметр не совпадает, функция возвращает код ошибки 4140 и не выполняет никаких действий.
 *  @param dwAmount Сумма операции (в копейках)
 *  @param pAuthCode Код авторизации.
 *  @return int Код ошибки.
 */
PILOT_NT_API int RollbackTrx(DWORD dwAmount, char* pAuthCode);

/** @brief Функция прерывает работу функций card_authorizeX()
 *  @note Внешнее ПО может вызвать эту функцию из отдельного треда, чтобы досрочно прекратить выполнение любой из функций card_authorize…(). При этом функция card_authorize…()  завершится с кодом ошибки 2000 (операция прервана).
 *  @return int Код ошибки.
 */
PILOT_NT_API int AbortTransaction();
/**@}*/

/**
 * @defgroup READCARD Чтение карты
 */
/**@{*/
/** @brief Чтение карты
 *  @param Last4Digits Буфер, куда функция записывает четыре последних цифры номера карты. Размер буфера должен быть не менее 5 байт.
 *  @param Hash Хеш от номера карты, в формате ASCII с нулевым байтом в конце. Размер буфера должен быть не менее 41 байта.
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadCard  (char *Last4Digits, char *Hash);

/** @brief Функция позволяет прочитать банковскую карту для использования в скидочной системе «Спасибо от Сбербанка».
 *  @note Карта должна быть выдана Сбербанком, в противном случае функция вернет ошибку.
 *  @param Last4Digits Буфер, куда функция записывает четыре последних цифры номера карты. Размер буфера должен быть не менее 5 байт.
 *  @param Hash Хеш от номера карты, в формате ASCII с нулевым байтом в конце. Размер буфера должен быть не менее 41 байта.
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadCardSB(char *Last4Digits, char *Hash);

/** @brief Чтение карты
 *  @param Last4Digits Буфер, куда функция записывает четыре последних цифры номера карты. Размер буфера должен быть не менее 5 байт.
 *  @param Hash Хеш от номера карты, в формате ASCII с нулевым байтом в конце. Размер буфера должен быть не менее 41 байта.
 *  @param pCardType Тип карты. См. ::CardTypes
 *  @param pIsOwnCard Признак "Карта выпущена Сбербанком"
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadCardWithType(
  char *Last4Digits,
  char *Hash,
  int*  pCardType,
  int*  pIsOwnCard
);

/** @brief Чтение карты
 *  @param PAN Буфер, куда функция записывает PAN карты
 *  @param Hash Хеш от номера карты, в формате ASCII с нулевым байтом в конце. Размер буфера должен быть не менее 41 байта.
 *  @param pCardType Тип карты. См. ::CardTypes
 *  @param pIsOwnCard Признак "Карта выпущена Сбербанком"
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadMaskedCardWithType(
  char *PAN,
  char *Hash,
  int*  pCardType,
  int*  pIsOwnCard
);

/** @brief Чтение полной второй дорожки карты
 *  @note  Данные второй дорожки могут иметь длину до 40 символов.
 *  Вторая дорожка имеет формат:
 *    nnnn...nn=yymmddd...d
 *  где     '=' - символ-разделитель
 *      nnn...n - номер карты
 *      yymm    - срок действия карты (ГГММ)
 *      ddd...d - служебные данные карты
 *  @param[out] Track2 Буфер на 41 байт.
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadTrack2(char *Track2);

/** @brief Чтение полной третьей дорожки карты
 *  @note Данные третьей дорожки могут иметь длину до 40 символов.
 *  @param[out] Last4Digits 4 последние цифры карты
 *  @param[out] Hash Хеш от номера карты, в формате ASCII с нулевым байтом в конце. Размер буфера должен быть не менее 41 байта.
 *  @param[out] pTrack3 третья дорожка карты
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadCardTrack3(char *Last4Digits, char *Hash, char* pTrack3);

/** @brief Чтение карты Сберкарт
 *  @param[out] CardNo полный номер карты
 *  @param[out] ClientName имя фамилия клиента эмброссированные на карте
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadSbercard(char *CardNo, char* ClientName);

/** @brief Чтение карты Сберкарт
 *  @param[out] pTrack2 Track2
 *  @param[out] ValidThru Срок действия карты в формате YYMM
 *  @param[out] pName имя фамилия клиента эмброссированные на карте
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadCardAndName(
  char *pTrack2,
  char* ValidThru,
  char* pName
);

/** @brief Чтение карты
 *  @note  Чтобы использовать результат для авторизации, их нужно будет сформатировать так "CardNo=ValidThru".  
 *  Функция не поддерживается по протоколу TTK для PCI-DSS решений.
 *  @param CardNo Номер карты. Может иметь длину от 13 до 19 цифр.
 *  @param ValidThru Срок действия карты в формате YYMM
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadCardFull(char *CardNo, char *ValidThru);

/** @brief Чтение карты
 *  @param dataOut Контекст операции, в которую копируются pan, хэш, тип карты, признак "Карта выпущена Сбербанком" и номер программы лояльности
 *  @return int Код ошибки.
 */
PILOT_NT_API int ReadCardContext(CONTEXT_PTR dataOut);


/**@}*/

/**
 * @defgroup VENDING Вендинговые операции
 */
/**@{*/
 /** @brief Установить элементы для вывода на экран
 *  @param[in] hText Элемент вывода текста.
 *  @param[in] hEdit Элемент ввода текста.
 *  @return int Код ошибки.
 */
PILOT_NT_API int SetGUIHandles(int hText, int hEdit);

/** @brief Извлечь карту. Команда 5020.
 *  @return int Код ошибки.
 */
PILOT_NT_API int EjectCard();

/** @brief Перемещение карты в лоток для задержанных карт. Команда 5021.
 *  @return int Код ошибки.
 */
PILOT_NT_API int CaptureCard();

/** @brief Проверка наличия карты в чиповом считывателе.
 *  @return int Код ошибки. 0 - карта внутри ридера, готова к работе; 254 - карты нет; 251 - карта в устье ридера, ожидает, что ее заберет клиент
 */
PILOT_NT_API int TestCard();

/** @brief Открыть клавиатуру в нешифрованом режиме
 *  @return int Код ошибки.
 */
PILOT_NT_API int OpenKeyboard();

/** @brief Закрыть клавиатуру
 *  @return int Код ошибки.
 */
PILOT_NT_API int CloseKeyboard();

/** @brief Получить код нажатого символа без ожидания
 *  @return int Возвращается 0, если нажатия клавиши не было.
 */
PILOT_NT_API int ReadKeyboard();

/** @brief Протестировать готовность оборудования
 *  @return unsigned char Возвращает битовую маску.
 - 0x00 ни пинпад, ни картридер не готов
 - 0x01 готов только пинпад
 - 0x02 готов только картридер
 - 0x03 готов и пинпад, и картридер
 */
PILOT_NT_API unsigned char TestHardware();
/**@}*/

/**
 * @defgroup CONTEXT Функции работы с контекстом
 */
/**@{*/
 /** @brief Создать контекст операции. Функция создает пустой контекст операции.
  *  @note Для входного контекста значения параметров устанавливаются вызывающей программой, для выходного контекста значения параметров устанавливаются библиотекой.
  *  При повторном использовании контекста, если переменная уже есть в контексте, она будет перезаписана. Рекомендуется либо создавать и удалять контексты при каждой
  *  операции, либо очищать контекст вызовом функции ctxClear перед повторным использованием.
  *  @return CONTEXT_PTR Идентификатор контекста операции или 0, если произошла ошибка
 */
PILOT_NT_API CONTEXT_PTR ctxAlloc(void);

 /** @brief Удалить контекст операции
  *  @param[in] ctx Идентификатор контекста.
  *  @return нет
 */
PILOT_NT_API void ctxFree(CONTEXT_PTR ctx);

 /** @brief Отчистить контекст. Функция удаляет все параметры из контекста.
  *  @param[in] ctx Идентификатор контекста.
  *  @return нет
 */
PILOT_NT_API void ctxClear(CONTEXT_PTR ctx);

 /** @brief Записать в контекст значение строкового параметра.
  *  @param[in] ctx  Идентификатор контекста.
  *  @param[in] name Идентификатор параметра.
  *  @param[in] str  Указатель на строку.
  *  @return int Код ошибки.
 */
PILOT_NT_API int ctxSetString(CONTEXT_PTR ctx, EParameterName name, const char* str);

 /** @brief Записать в контекст значение целочисленного параметра.
  *  @param[in] ctx  Идентификатор контекста.
  *  @param[in] name Идентификатор параметра.
  *  @param[in] val  Значение параметра.
  *  @return int Код ошибки.
 */
PILOT_NT_API int ctxSetInt(CONTEXT_PTR ctx, EParameterName name, int val);

 /** @brief Записать в контекст значение параметра в виде последовательности байт.
  *  @param[in] ctx  Идентификатор контекста.
  *  @param[in] name Идентификатор параметра.
  *  @param[in] val  Указатель на буфер.
  *  @param[in] sz   Длина буфера.
  *  @return int Код ошибки.
 */
PILOT_NT_API int ctxSetBinary(CONTEXT_PTR ctx, EParameterName name, unsigned char* val, int sz);

 /** @brief Считать из контекста значение переменной в виде строки.
  *  @note Для целочисленной переменной вы получите ее строковое представление, а для последовательности байт функция вернет hex строку.
  *  @param[in] ctx  Идентификатор контекста.
  *  @param[in] name Идентификатор параметра.
  *  @param[in] val  Указатель на строку.
  *  @param[in] sz   Максимально возможная длина строки.
  *  @return int Код ошибки.
 */
PILOT_NT_API int ctxGetString(CONTEXT_PTR ctx, EParameterName name, char* str, int sz);

 /** @brief Считать из контекста значение переменной в виде целого числа.
  *  @note Для строковой переменной будет выполнено преобразование строки в число, для последовательности байт
  *  функция преобразует первые четыре байта последовательности в целое число с прямым порядком байт.
  *  @param[in] ctx  Идентификатор контекста.
  *  @param[in] name Идентификатор параметра.
  *  @param[in] pVal Указатель на число.
  *  @return int Код ошибки.
 */
PILOT_NT_API int ctxGetInt   (CONTEXT_PTR ctx, EParameterName name, int* pVal);

 /** @brief Считать из контекста значение переменной в виде последовательности байт.
  *  @note Для строковой переменной будет значение будет возвращено без изменения, для целочисленной переменной функция
  *  вернет последовательность из четырех байт с прямым порядком байт.
  *  @param[in] ctx     Идентификатор контекста.
  *  @param[in] name    Идентификатор параметра.
  *  @param[in] pVal    Указатель на буфер результата.
  *  @param[in] pOutSz  Количество байт, скопированных в буфер.
  *  @param[in] MAXSIZE Максимально возможное количество байт.
  *  @return int Код ошибки.
 */
PILOT_NT_API int ctxGetBinary(CONTEXT_PTR ctx, EParameterName name, unsigned char* pVal, int* pOutSz, int MAXSIZE);

#pragma pack()

#ifdef __cplusplus
};
#endif

#endif
