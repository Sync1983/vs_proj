#include "stdafx.h"
#include "LLV.h"
#include "ifptr.h"
#include "dto_errors.h"
#include "dto_const.h"

bool LLV::init() {
	iface_error = false;
	cmd(iface->put_DeviceSingleSetting(S_PORT, 18));
	cmd(iface->put_DeviceSingleSetting(S_PROTOCOL, TED::Fptr::ProtocolAtol30));
	cmd(iface->put_DeviceSingleSetting(S_MODEL, TED::Fptr::ModelATOL30F));
	cmd(iface->put_DeviceSingleSetting(S_BAUDRATE, 1200));
	cmd(iface->ApplySingleSettings());

	cmd(iface->put_DeviceEnabled(1));
	iface->put_Frequency(1000);
	iface->put_Duration(500);
	iface->Sound();

	iface->put_Frequency(1500);
	iface->put_Duration(400);
	iface->Sound();

	iface->put_Frequency(2000);
	iface->put_Duration(500);
	iface->Sound();

	wrap = TED::Fptr::TextWrapWord;
	alignment = TED::Fptr::AlignmentCenter;

	return !iface_error;
}

LLV::LLV() {
	HMODULE hLib = LoadLibrary(L"fptr.dll");
	if (!hLib) {
		DWORD error_no = GetLastError();		
		return;
	}

	create = (CreateFptrInterfacePtr)GetProcAddress(hLib, "CreateFptrInterface");
	release = (ReleaseFptrInterfacePtr)GetProcAddress(hLib, "ReleaseFptrInterface");
	if (!create || !release) {
		return;
	}

	iface = create(DTO_IFPTR_VER1);
	
	if (!init()) {
		return;
	}

	cmd(iface->GetStatus());	
	iface->get_con

	/*cmd(iface->CancelCheck());
	cmd(iface->put_Mode(TED::Fptr::ModeReportNoClear));
	cmd(iface->SetMode());
	cmd(iface->PrintHeader());

	print_text(L"Тест");

	cmd(iface->put_Mode(TED::Fptr::ModeReportNoClear));
	cmd(iface->SetMode());
	cmd(iface->PrintFooter());*/
	//report_z();
}

void LLV::checkError(LPCWSTR cmd_text) {
	if (!iface) {
		return;
	}
	wchar_t text[256];
	int rc = EC_OK;
	iface->get_ResultCode(&rc);
	if (rc < 0) {
		int size = iface->get_ResultDescription(text, 255);
		if (size > 0) {
			OutputDebugStringW(L"ERROR!!! \n");
			OutputDebugStringW(text);
			OutputDebugStringW(L"\n");
			OutputDebugStringW(cmd_text);
			OutputDebugStringW(L"\n");
		}
	}
}

void LLV::report_z() {
	cmd(iface->put_SessionEnd(1));
	cmd(iface->put_Mode(TED::Fptr::ModeReportClear));
	cmd(iface->SetMode());
	cmd(iface->put_ReportType(TED::Fptr::ReportZ));
	cmd(iface->Report());
}

bool LLV::print_text(LPCWSTR text) {
	cmd(iface->put_Caption(text));
	cmd(iface->put_TextWrap(wrap));
	cmd(iface->put_Alignment(alignment));
	cmd(iface->PrintString());
	return !iface_error;
}

LLV::~LLV(){
	iface->put_Frequency(2000);
	iface->put_Duration(500);
	iface->Sound();

	iface->put_Frequency(1500);
	iface->put_Duration(400);
	iface->Sound();

	iface->put_Frequency(1000);
	iface->put_Duration(500);
	iface->Sound();

	cmd(iface->put_DeviceEnabled(0));
	release(&iface);
}
