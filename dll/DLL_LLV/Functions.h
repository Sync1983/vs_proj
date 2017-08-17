#pragma once

struct functList {
	wchar_t Name[2][50];
	int		params_num;
	bool	is_function;
};

#define numFunctions  7

enum functionName {
	add_item = 0,
	open_check,
	add_pay,
	close_check,
	z_report
};

static functionName functName;

static functList fList[numFunctions] = {
	{ { L"AddItem",		L"ДобавитьПозицию"}, 3, false },
	{ { L"OpenChek",	L"ОткрытьЧек"}, 0, false},
	{ { L"AddPay",		L"ДобавитьОплату" }, 2, false },	
	{ { L"CloseChek",	L"ЗакрытьЧек" }, 0, false },
	{ { L"ZReport",		L"ZОтчет" }, 0, false },
	{ { L"GetChekNumber",L"ПолучитьНомерЧека" }, 0, true},
	{ { L"GetChekSumm",L"ПолучитьСуммуЧека" }, 0, true },
};