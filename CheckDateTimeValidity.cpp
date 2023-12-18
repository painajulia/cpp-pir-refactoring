const int first_time = 0;
const int first_date = 1;
const int last_sec_minut = 59;
const int last_hour = 23;
const int last_year = 9999;
const int last_month = 12;

 const int GetMonthLength(int year, int month) {
    const bool is_leap_year = (year % 4 == 0) && !(year % 100 == 0 && year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return month_lengths[month];
}
 enum  class Errors {
     success = 0,
     year_to_small = 1 << 0,
     yaer_to_big = 1 << 1,
     month_to_small = 1 << 2,
     month_to_big = 1 << 3,
     day_to_small = 1 << 4,
     day_to_big = 1 << 5,
     hour_to_small = 1 << 6,
     hour_to_big = 1 << 7,
     minut_to_small = 1 << 8,
     minut_to_big = 1 << 9,
     sec_to_small = 1 << 10,
     sec_to_big = 1 << 11
 };
 
 
 Errors CheckDateTimeValidity(const DateTime&  dt) {
    if (dt.year < first_date) {
        return Errors::year_to_small;
    }
    if (dt.year > last_year) {
        return Errors::yaer_to_big;
    }

    if (dt.month < first_date) {
        return Errors::month_to_small;
    }
    if (dt.month > last_month) {
        return Errors::month_to_big;
    }

    if (dt.day < first_date) {
        return Errors::day_to_small;
    }
    if (dt.day > GetMonthLength(dt.year, dt.month - 1)) {
        return Errors::day_to_big;
    }

    if (dt.hour < first_time) {
        return Errors::hour_to_small;
    }
    if (dt.hour > last_hour) {
        return Errors::hour_to_big;
    }

    if (dt.minute < first_time) {
        return Errors::minut_to_small;
    }
    if (dt.minute > last_sec_minut) {
        return Errors::minut_to_big;
    }

    if (dt.second < first_time) {
        return Errors::sec_to_small;
    }
    if (dt.second > last_sec_minut) {
        return Errors::sec_to_big;
    }
}