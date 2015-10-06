﻿#include "system_text.h"

namespace System { 

#ifdef _WIN32
	// Windows 에서는 "ko_KR.UTF-8" 이 없음 ㅠㅠ	
	// http://includes.egloos.com/v/1504676
	// http://sjc333.egloos.com/3137637
	Text::Encoding Text::UTF8Encoding(std::locale(std::locale("Korean")));
#else
	Text::Encoding Text::UTF8Encoding(std::locale(std::locale("ko_KR.UTF-8")));
#endif
} // end_of_namespace System

