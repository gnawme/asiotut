/// \file   AsioCommon.h
#pragma once

#include <ctime>
#include <string>

///
static std::string makeDaytimeResponse() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

