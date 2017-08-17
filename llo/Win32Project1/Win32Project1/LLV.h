#pragma once
#include "ifptr.h"
#include "dto_errors.h"
#include "dto_const.h"
#define cmd_text(a) L#a
#define cmd(a) if((a) < 0) {\
					this->checkError(cmd_text(a));\
					iface_error = true; \
				}\

class LLV
{
protected:
	TED::Fptr::IFptr *iface;
	TED::Fptr::Alignment alignment;
	TED::Fptr::TextWrap wrap;
	CreateFptrInterfacePtr create;
	ReleaseFptrInterfacePtr release;
	bool iface_error;
protected:
	bool init();
	void checkError(LPCWSTR cmd_text);
	void report_z();
	bool print_text(LPCWSTR text);
public:
	LLV();
	~LLV();
};

