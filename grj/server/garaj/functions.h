#pragma once
#include <map>

struct funct_descr {
	wchar_t Name[2][50];
	int		params_num;
	bool	is_function;
};

enum Functs {
  start = 0,
  stop,  
  lastFunct
};

typedef std::map<Functs, funct_descr>::iterator functions_it;

static std::map<Functs, funct_descr> functions = {
  { start, { { L"Start",	L"Запустить"},  0, false } },
  { stop,  { { L"Stop",	L"Остановить"}, 0, false } }
};