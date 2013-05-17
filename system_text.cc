#include "system_text.h"

namespace System { 

Text::Encoding Text::UTF8Encoding(std::locale(std::locale(), new boost::archive::detail::utf8_codecvt_facet));

} // end_of_namespace System

