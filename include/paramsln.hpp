#ifndef _PARAMSLN_H
#define _PARAMSLN_H

/**
 * @defgroup KERNEL_CONST Константы, используемые при определении структур
 */
 /**@{*/


///Константы, используемые при определении структур

#define MAX_TRACK1     79  ///< Длинна Track1
#define MAX_TRACK2     40  ///< Длинна Track2
#define MAX_TRACK3    107  ///< Длинна Track3
#define CARD_TRACK3_LEN   (MAX_TRACK3-3) ///< Длина буфера третьей дорожки карты в структурах библиотеки pilot_nt.dll

#define MAX_AUTH_CODE      6  ///< Длина кода авторизации
#define MAX_AUTHCODE     ( MAX_AUTH_CODE+1) ///< Длина кода авторизации с учетом завершающего ноля
#define MAX_RRN           12  ///< Длина номера ссылки/идентификатора смены
#define MAX_REFNUM       (MAX_RRN+1) ///< Длина номера ссылки с учетом завершающего ноля
#define MAX_TERM           8 ///< Длина номера терминала
#define MAX_TERMID       ( MAX_TERM+1)  ///< Длина номера терминала с учетом завершающего ноля
#define MAX_PAN_N         19  ///< Длинна PAN
#define MAX_PAN          (MAX_PAN_N+1) ///< Длинна PAN с учетом завершающего ноля
#define MAX_VALTHRU      ( 5+1)
#define MAX_CURRCODE     ( 3+1)
#define MAX_REPLY        ( 2+1)

#define MAX_MERCHANT     (12+1)
#define MAX_MCCCODE      ( 4+1)
#define MAX_STORENUM     ( 4+1)
#define MAX_TERMNUM      ( 4+1)
#define MAX_SOFTVER      ( 3+1)
#define MAX_TSN          ( 4+1)
#define MAX_OPDATE       ( 6+1)
#define MAX_MESSAGE      (16+1)
#define MAX_EXT_MESSAGE  (24+1)
#define MAX_EXTRA       (249+1)
#define MAX_EXTRA_VISA  (120+1)
#define MAX_CHIPDATA        256
#define MAX_FIO          (40+1)
#define MAX_KEYLEN      (120+1)           /* for GISKE keys */
#define MAX_CVV           (3+1)
#define MAX_USER_NAME_FULL (20+1)
#define MAX_USER_PWD_FULL  (20+1)
#define MAX_ENT_CODE       (24+1)

//Константы, используемые при определении структур
#define MAX_CARD_NUM      30  ///< Длина номера карты
#define MAX_ACCOUNT_NUM   11  ///< Длина номера счета (Сберкарт)
#define MAX_BRANCH_NUM    11  ///< Длина кода банка (Сберкарт)
#define MAX_CERT          16  ///< Длина сертификата транзакции
#define MAX_NAME          38  ///< Длина названия карты (Visa, Maestro, ...)
#define MAX_DATE          10  ///< Длина строки даты (ДД.ММ.ГГГГ)
#define MAX_TIME           8  ///< Длина времени операции (ЧЧ:ММ:СС)


#define MAX_MERCHANT_LN   15  ///< Длина номера мерчанта
#define MAX_OPER_NAME     64  ///< Длина имени пользователя

#define MAX_HASH          20  ///< Длинна хеша номера карты
#define MAX_CARD_DATE     4   ///< Длинна даты выпуска карты MMYY
#define MAX_PASSPORT      512 ///< Длинна паспортных данных
#define MAX_PAYMENT_TAG   32  ///< Тэг дополнительных реквизитов платежей для передачи в банк
#define MAX_PAYMENT_VALUE 200 ///< Значение дополнительных реквизитов платежей для передачи в банк
#define MAX_CARD_LS_DATA  800 ///< Размер буфера данных для экранной подписи
#define MAX_TEXT_MESSAGE  700 ///< Размер максимального текстового сообщения
#define MAX_CLIENT_NAME    80 ///< Имя владельца карты
#define MAX_GOODS_NAME     25 ///< Максимальная длина имени товара
#define MAX_GOODS_CODE     24 ///< Максимальная длина кода товара
#define MAX_CASH_STATS     24 ///< Длинна полей для передачи информации о наличном обороте
#define MAX_FIO_N          58 ///< Длинна имени кассира
#define CARD_HOLDER_ANSWER_LEN 256 ///< Длина ответа введенная клиентом (v 26)
#define CARD_ID_LEN        25 ///< Длина буфера номера карты в структурах библиотеки pilot_nt.dll
#define CARD_HASH_LEN      41 ///< Длина буфера хеша карты в структурах библиотеки pilot_nt.dll
#define TRANSDATE_LEN      20 ///< Размер даты и времени операции в структурах библиотеки pilot_nt.dll


#define MAX_PAYMENT_ITEM  128      ///< Максимальный размер значения тега платежной системы.
#define MAX_ENCR_DATA  32          ///< Размер буфера шифрованого номера карты и срока действия
#define MAX_AID_ASCII_LEN   (32+1) ///< Максимальный размер длинны AID чиповой карты (в виде ASCIIZ-строки)
#define MAX_CARD_NAME_LEN   (32+1) ///< Максимальный размер названия платежной системы карты

#define MAX_FULL_ERROR_TEXT 128 ///<Максимальный размер текста ошибки, возвращаемый UPOS

/**@}*/

#endif
