
#include <stdexcept>
#include <chrono>
#include <cstdio>

#include "utils.h"
#include "Packet.h"

int stringToEpochDateTime(const std::string& dateTimeStr) {
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;

    int parsed = sscanf_s(
        dateTimeStr.c_str(),
        "%d_%d_%d %d:%d:%d",
        &month, &day, &year, &hour, &minute, &second
    );

    if (parsed != 6) {
        return -1;
    }

    // Validate ranges
    if (month < 1 || month > 12) {
        return -1;
    }
    if (day < 1 || day > 31) {
        return -1;
    }
    if (hour < 0 || hour > 23) {
        return -1;
    }
    if (minute < 0 || minute > 59) {
        return -1;
    }
    if (second < 0 || second > 59) {
        return -1;
    }

    namespace chr = std::chrono;

    chr::year_month_day ymd{
        chr::year{year},
        chr::month{static_cast<unsigned>(month)},
        chr::day{static_cast<unsigned>(day)}
    };

    if (!ymd.ok()) {
        return -1;  // e.g. Feb 30, Apr 31, etc.
    }

    auto tp = chr::sys_days{ ymd }
        + chr::hours{ hour }
        + chr::minutes{ minute }
        + chr::seconds{ second };

    return static_cast<int>(chr::system_clock::to_time_t(tp));
}

std::string epochDateTimeToString(int epoch) {
    if (epoch < 0) {
        return "";
    }

    namespace chr = std::chrono;

    // Convert to a UTC time point, then break into date + time-of-day
    auto timePoint = chr::system_clock::from_time_t(static_cast<time_t>(epoch));
    auto dayPoint = chr::floor<chr::days>(timePoint);
    chr::year_month_day yearMonthDay{ dayPoint };
    chr::hh_mm_ss hourMinuteSecond{ chr::duration_cast<chr::seconds>(timePoint - dayPoint) };

    return std::format("{}_{}_{} {:02}:{:02}:{:02}",
        static_cast<unsigned>(yearMonthDay.month()),
        static_cast<unsigned>(yearMonthDay.day()),
        static_cast<int>(yearMonthDay.year()),
        hourMinuteSecond.hours().count(),
        hourMinuteSecond.minutes().count(),
        hourMinuteSecond.seconds().count()
    );
}

void trim(std::string& s) {
    // Trim from the right
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char c) { return !std::isspace(c); }).base(), s.end());

    // Trim from the left
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char c) { return !std::isspace(c); }));
}

Packet parseTelemLineToPacket(UUID_T clientId, const std::string& telem) {
    std::string telmetryData = telem;
    // Example:
    // 1_3_2023 12:35:34,33.571247,

    // Remove any whitespace
    trim(telmetryData);

    // Split data/time and fuel
    size_t pos = telmetryData.find(',');
    if (pos == std::string::npos) {
        throw std::invalid_argument("No comma found in: " + telmetryData);
    }

    std::string dataTimeString = telmetryData.substr(0, pos);
    std::string fuelFloatString = telmetryData.substr(pos + 1);

    // Parse fuel to float
    float fuelData = std::stof(fuelFloatString);
    // Parse date time to epoch string
    int epochDateTime = stringToEpochDateTime(dataTimeString);

    return Packet(clientId, epochDateTime, fuelData);
}
