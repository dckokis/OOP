#include "daysCount.hpp"
#include "numberOfDays.hpp"
#include "defineDay.hpp"

int rdn(int d, int m, int y) { /* Rata Die day one is 0001-01-01 */
    if (m < 3)
        y--, m += 12;
    return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
}

std::vector<int> daysCounter(date beg, date end) {
    std::vector<int> dayNamesAmount (7);
    int beginDay = defineDay(beg.getDay(), beg.getMonth(), beg.getYear());
    int endDay = defineDay(end.getDay(), end.getMonth(), end.getYear());
    int daysBetween = rdn(end.getDay(), end.getMonth(), end.getYear()) - rdn(beg.getDay(), beg.getMonth(), beg.getYear());
    int v = daysBetween / 7;
    for (int  i = 0; i < 7; i++) {
        dayNamesAmount[i] = v;
    }
    int delta = endDay - beginDay;
    if (delta != 0) {
        for (int i = 0; i <= delta; i++) {
            dayNamesAmount[beginDay + i] += 1;
        }
    }
    return dayNamesAmount;
}
