
#include <stdexcept>
#include <chrono>
#include <cstdio>

#include "utils.h"

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
