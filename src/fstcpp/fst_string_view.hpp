#pragma once
// Force to use nonstd::string_view
#define nssv_CONFIG_SELECT_STRING_VIEW nssv_STRING_VIEW_NONSTD
#include "fstcpp/string_view.hpp"

namespace fst {

using string_view_ = nonstd::sv_lite::string_view;

} // namespace fst
