#include "stdafx.h"
#include "LLV.h"
#include "ifptr.h"
#include "dto_errors.h"
#include "dto_const.h"
#include <vcruntime_exception.h>
#include <stdlib.h>
#include <time.h>

bool LLV::init() {
	if ( !iface ) {
		iface_error = true;
		return false;
	}

	iface_error = false;
	try {
		cmd(iface->put_DeviceSingleSetting(S_PORT, 18));
		cmd(iface->put_DeviceSingleSetting(S_PROTOCOL, TED::Fptr::ProtocolAtol30));
		cmd(iface->put_DeviceSingleSetting(S_MODEL, TED::Fptr::ModelATOL30F));
		cmd(iface->put_DeviceSingleSetting(S_BAUDRATE, 9600));
		cmd(iface->ApplySingleSettings());

		cmd(iface->put_DeviceEnabled(1));
		cmd(iface->put_Frequency(1000));
		cmd(iface->put_Duration(70));
		cmd(iface->Sound());

		cmd(iface->put_Frequency(1500));
		cmd(iface->put_Duration(70));
		cmd(iface->Sound());

		cmd(iface->put_Frequency(2000));
		cmd(iface->put_Duration(70));
		cmd(iface->Sound());

		wrap = TED::Fptr::TextWrapWord;
		alignment = TED::Fptr::AlignmentCenter;

		cmd(iface->put_SessionEnd(1));
	} catch (...) {
		int rc = EC_OK;
		iface->get_ResultCode(&rc);
		if (rc != EC_INVALID_MODE && rc != EC_3801)
			return false;
	}
	return !iface_error;
}

LLV::LLV() {
	WCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);
	wcsncat_s(path, L"\\fptrwin32.dll", (size_t)15);
	HMODULE hLib = LoadLibrary(path);
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
	chek_open = false;
	session_open = false;
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

bool LLV::report_z() {
	cmd(iface->put_SessionEnd(1));
	cmd(iface->put_Mode(TED::Fptr::ModeReportClear));
	cmd(iface->SetMode());
	cmd(iface->put_ReportType(TED::Fptr::ReportZ));
	cmd(iface->Report());
	return !iface_error;
}

bool LLV::print_text(LPCWSTR text) {
	cmd(iface->put_Caption(text));
	cmd(iface->put_TextWrap(wrap));
	cmd(iface->put_Alignment(alignment));
	cmd(iface->PrintString());
	return !iface_error;
}

LLV::~LLV() {
	if (!iface) {
		return;
	}
	iface->put_Frequency(2000);
	iface->put_Duration(70);
	iface->Sound();

	iface->put_Frequency(1500);
	iface->put_Duration(70);
	iface->Sound();

	iface->put_Frequency(1000);
	iface->put_Duration(70);
	iface->Sound();

	cmd(iface->put_DeviceEnabled(0));
	release(&iface);
}

bool LLV::hasError() {
	return iface_error;
}

pkkm_status LLV::getStatus() {
	if (status == NULL) {
		void *t;
		t = malloc(sizeof(kkm_status));
		if (t != NULL) {
			status = (pkkm_status)t;
		}
	}

	if (!iface) {
		status->connected = false;
		return status;
	}

	status->connected = true;

	cmd(iface->GetStatus());

	if (iface_error) {
		status->connected = false;
		return status;
	}
	
	int tmp = 0;
	
	iface->get_Fiscal(&tmp);
	status->fiscal = tmp == 1;

	iface->get_SerialNumber(status->serial_number, 8);

	iface->get_Model(&tmp);
	status->model = tmp;

	iface->get_SessionOpened(&tmp);
	status->session_open = tmp == 1;
	session_open = status->session_open;

	iface->get_CheckPaperPresent(&tmp);
	status->paper_present = tmp == 1;

	iface->get_Operator(&status->kkm_operator);
	iface->get_INN(status->inn,12);
	iface->get_MachineNumber(status->machine_number, 10);	

	iface->get_CharLineLength(&status->char_line_length);
	iface->get_PixelLineLength(&status->dot_line_length);
	iface->get_SummPointPosition(&status->dot_position);

	iface->get_CoverOpened(&tmp);
	status->cover_open = tmp == 1;

	iface->get_VerHi(status->ver_hi,10);
	iface->get_VerLo(status->ver_lo,10);
	iface->get_Build(status->build,10);

	tm date;
	memset(&date, 0, sizeof(tm));	
	iface->get_Time(&date.tm_hour, &date.tm_min, &date.tm_sec);
	iface->get_Date(&date.tm_mday, &date.tm_mon, &date.tm_year);
	date.tm_mon -= 1;
	date.tm_year -= 1900;
	status->date = date;

	return status;
}

bool LLV::open_check() {
	iface_error = false;	
	cmd(iface->put_Mode(TED::Fptr::Mode::ModeSelect));
	cmd(iface->SetMode());	

	if ( !session_open ) {
		try {
			cmd(iface->put_Session(1));
		} catch (...) {
			int rc = EC_OK;
			iface->get_ResultCode(&rc);
			if (rc != EC_INVALID_MODE && rc != EC_3801)
				return false;
		}
	}

	session_open = true;

	if (chek_open) {
		return false;
	}	
	
	cmd(iface->put_Mode(TED::Fptr::Mode::ModeRegistration));
	cmd(iface->SetMode());
	if (iface_error) {
		int rc = EC_OK;
		iface->get_ResultCode(&rc);
		if (rc == EC_3822) {			
			iface_error = !report_z();
		}
	}

	try {		
		cmd(iface->put_CheckType(TED::Fptr::ChequeSell));
		cmd(iface->put_PrintCheck(1));
		cmd(iface->OpenCheck());		
	} catch (...) {

		int rc = EC_OK;
		iface->get_ResultCode(&rc);
		if (rc == EC_3822) {
			report_z();
			return open_check();
		}
		return false;
	}
	if (iface_error) {
		int rc = EC_OK;
		iface->get_ResultCode(&rc);		
	}

	chek_open = true;
	cmd( iface->put_LeftMargin(20) );
	cmd( iface->put_PictureNumber(1) );
	cmd( iface->PrintPictureByNumber() );
	cmd(iface->put_LeftMargin(0));
	
	return !iface_error;
}

bool LLV::close_check() {
	chek_open = false;
	getStatus();
	cmd(iface->CloseCheck());
	cmd(iface->put_Mode(TED::Fptr::Mode::ModeSelect));
	cmd(iface->SetMode());
	return !iface_error;
}

bool LLV::add_item(LPWSTR name, double count, double price) {
	
	if ( !chek_open ) {
		return false;
	}
	
	cmd(iface->put_PositionSum(count * price));
	cmd(iface->put_Quantity(count));
	cmd(iface->put_Price(price));
	cmd(iface->put_Table(TED::Fptr::TaxVATNo));
	cmd(iface->put_Name(name));
	cmd(iface->Registration());
	
	return !iface_error;
}

bool LLV::add_pay(int type, double sum) {
	if (!chek_open) {
		return false;
	}

	cmd(iface->put_Summ(sum));
	cmd(iface->put_TypeClose(type));
	cmd(iface->Payment())

	return !iface_error;
}

int	LLV::get_check_number() {
	int num;
	cmd(iface->get_CheckNumber(&num));
	if (iface_error) {
		return -1;
	}
	return num;
}

double LLV::get_check_summ() {
	double sum;
	cmd(iface->get_Summ(&sum));

	if (iface_error) {
		return -1.0f;
	}

	return sum;
}