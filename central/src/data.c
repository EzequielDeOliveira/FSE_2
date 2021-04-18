#include "data.h"

Data data;

void init_data() {
    data.lamp1 = 0;
    data.lamp2 = 0;
    data.lamp3 = 0;
    data.lamp4 = 0;
    data.air1 = 0;
    data.air2 = 0;
    data.openings1 = 0;
    data.openings2 = 0;
    data.openings3 = 0;
    data.openings4 = 0;
    data.openings5 = 0;
    data.openings6 = 0;
    data.presences1 = 0;
    data.presences2 = 0;
    data.humidity = 0;
    data.temperature = 0;
}

Data get_data() {
    return data;
}

void set_data(Data _data) {
    data = _data;
}
