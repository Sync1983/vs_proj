#pragma once

struct propList{
	wchar_t Name[2][50];
	bool readable;
	bool writeable;	
	tVariant *value;
};

#define numProp  12

static propList properties[numProp] = {
	{ { L"DriverStatus",	L"��������������" }, true, false, 0},
	{ { L"Fiscal",			L"���������������" }, true, false, 0 },
	{ { L"Serial",			L"�������������" }, true, false, 0 },	
	{ { L"SessionOpen",		L"�������������" }, true, false, 0 },
	{ { L"PaperPresent",	L"������������������" }, true, false, 0 },
	{ { L"Operator",		L"�������������" }, true, false, 0 },
	{ { L"MachineNumber",	L"��������" }, true, false, 0 },
	{ { L"Date",			L"����" }, true, false, 0 },
	{ { L"CoverOpen",		L"�������������" }, true, false, 0 },
	{ { L"VerHi",			L"�������1" }, true, false, 0 },
	{ { L"VerLo",			L"�������2" }, true, false, 0 },
	{ { L"Build",			L"������" }, true, false, 0 }
};
