#include "data.h"
#include "alarm.h"
#include "dashboard.h"

Data data;

void init_data()
{
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
    data.alarm = 0;
}

Data get_data()
{
    return data;
}

void set_data(Data _data)
{

    if (_data.openings1 == 1 ||
        _data.openings2 == 1 ||
        _data.openings3 == 1 ||
        _data.openings4 == 1 ||
        _data.openings5 == 1 ||
        _data.openings6 == 1 ||
        _data.presences1 == 1 ||
        _data.presences2 == 1)
    {
        if (data.playing == 0)
        {
            _data.playing = 1;
            turn_on_alarm();
        }
    }
    else
    {
        _data.playing = 0;
        turn_off_alarm();
    }


    data = _data;

    render_info_win();
}
