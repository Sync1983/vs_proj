#pragma once
#include "ifptr.h"
#include "dto_errors.h"
#include "dto_const.h"
#include <time.h>

#define cmd_text(a) L#a
#define cmd(a) if((a) < 0) {\
					this->checkError(cmd_text(a));\
					iface_error = true; \
				}\

struct kkm_status {
	bool	connected;
	bool	fiscal;
	wchar_t	serial_number[8];
	int		model;
	bool	session_open;
	bool	paper_present;
	int		kkm_operator;
	wchar_t	inn[12];
	wchar_t	machine_number[10];
	struct tm date;
	int		char_line_length;
	int		dot_line_length;
	int		dot_position;
	bool	cover_open;
	wchar_t	ver_hi[10];
	wchar_t	ver_lo[10];
	wchar_t	build[10];
};
typedef kkm_status* pkkm_status;

class LLV {
protected:
	TED::Fptr::IFptr		*iface;
	TED::Fptr::Alignment	alignment;
	TED::Fptr::TextWrap		wrap;
	CreateFptrInterfacePtr	create;
	ReleaseFptrInterfacePtr release;
	pkkm_status				status;
	bool					iface_error;
	bool					chek_open;
	bool					session_open;	
protected:	
	void checkError(LPCWSTR cmd_text);	
	bool print_text(LPCWSTR text);
public:
	
	bool init();
	bool hasError();
	pkkm_status getStatus();	
	bool add_item(LPWSTR name, double count, double price);
	bool add_pay(int type, double sum);
	bool open_check();
	bool close_check();
	bool report_z();
	int	get_check_number();
	double get_check_summ();
	LLV();
	~LLV();
};
