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
	{ { L"AddItem",		L"���������������"}, 3, false },
	{ { L"OpenChek",	L"����������"}, 0, false},
	{ { L"AddPay",		L"��������������" }, 2, false },	
	{ { L"CloseChek",	L"����������" }, 0, false },
	{ { L"ZReport",		L"Z�����" }, 0, false },
	{ { L"GetChekNumber",L"�����������������" }, 0, true},
	{ { L"GetChekSumm",L"�����������������" }, 0, true },
};