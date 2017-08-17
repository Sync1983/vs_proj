#pragma once

struct propList{
	wchar_t Name[2][50];
	bool readable;
	bool writeable;	
	tVariant *value;
};

#define numProp  12

static propList properties[numProp] = {
	{ { L"DriverStatus",	L"СтатусДрайвера" }, true, false, 0},
	{ { L"Fiscal",			L"Фискализирована" }, true, false, 0 },
	{ { L"Serial",			L"СерийныйНомер" }, true, false, 0 },	
	{ { L"SessionOpen",		L"СессияОткрыта" }, true, false, 0 },
	{ { L"PaperPresent",	L"БумагаПрисутствует" }, true, false, 0 },
	{ { L"Operator",		L"ОператорСмены" }, true, false, 0 },
	{ { L"MachineNumber",	L"НомерККМ" }, true, false, 0 },
	{ { L"Date",			L"Дата" }, true, false, 0 },
	{ { L"CoverOpen",		L"КрышкаОткрыта" }, true, false, 0 },
	{ { L"VerHi",			L"ВерсияЧ1" }, true, false, 0 },
	{ { L"VerLo",			L"ВерсияЧ2" }, true, false, 0 },
	{ { L"Build",			L"Сборка" }, true, false, 0 }
};
