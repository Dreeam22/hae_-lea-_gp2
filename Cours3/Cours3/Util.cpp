#pragma once

#include "pch.h"
#include "Util.hpp"

static bool timeZeroCalculated = false;
static std::chrono::system_clock::time_point time0;

double Util::getTimestamp() {
	if (!timeZeroCalculated) {
		time0 = std::chrono::system_clock::now();
		timeZeroCalculated = true;
	}

	auto tstamp = std::chrono::system_clock::now() - time0;

	//convert in seconds in double

	long long delta = std::chrono::duration_cast<std::chrono::nanoseconds>(tstamp).count();

	return delta * 0.000000001;
}