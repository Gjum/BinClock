#include "Segment.h"

Segment::Segment(int x, int y,
                 unsigned int w, unsigned int h,
                 unsigned int bitNumberArg,
                 float tickTimeArg,
                 float blendSpeedArg)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;

    rect.setSize(sf::Vector2f(width, height));
    rect.setPosition(xPos, yPos);
    rect.setFillColor(sf::Color(0, 128, 255));

    bitNumber = bitNumberArg;
    blendSpeed = blendSpeedArg * tickTimeArg * 1000;

    tickPeriod = tickTimeArg * 1000;

    for (unsigned int i = bitNumberArg; i > 0; i--)
        tickPeriod *= 2;
}

Segment::~Segment()
{
}

float Segment::draw(sf::RenderWindow *window, uint32_t millisec)
{
    float intensity = 0.8;

    millisec %= tickPeriod;

    /*
           _        _
       ___| |   ___| |
     _|     |__|     |_
         0 1 2  3
    */

//    if (millisec < bitNumber * blendSpeed) intensity = 0.8;
//    else if (millisec < (bitNumber + 1) * blendSpeed) intensity = 1.0;
//    else if (millisec < tickPeriod / 2 + bitNumber * blendSpeed) intensity = 0.0;
//    else intensity = 0.8;


    /*
       ___/\    ___/\
     _/     \__/     \_
         01 2 34 501 2

    nr const from to   until
    0     c  0.8  0.8  bitNumber * blendSpeed
    1        0.8  1.0  (bitNumber + 1) * blendSpeed
    2        1.0  0.0  (bitNumber + 2) * blendSpeed
    3     c  0.0  0.0  tickPeriod / 2 + bitNumber * blendSpeed
    4        0.0  0.8  tickPeriod / 2 + (bitNumber + 1) * blendSpeed
    5     c  0.8  0.8  ~
    */

    if (millisec < bitNumber * blendSpeed)
        intensity = 0.8;
    else if (millisec < (bitNumber + 1) * blendSpeed)
        intensity = 0.8 + (1.0 - 0.8)
                    * (millisec - bitNumber * blendSpeed)
                    / ((bitNumber + 1) * blendSpeed - bitNumber * blendSpeed);
    else if (millisec < (bitNumber + 2) * blendSpeed)
        intensity = 1.0 + (0.0 - 1.0)
                    * (millisec - (bitNumber + 1) * blendSpeed)
                    / ((bitNumber + 2) * blendSpeed - (bitNumber + 1) * blendSpeed);
    else if (millisec < tickPeriod / 2 + bitNumber * blendSpeed)
        intensity = 0.0;
    else if (millisec < tickPeriod / 2 + (bitNumber + 1) * blendSpeed)
        intensity = 0.0 + (0.8 - 0.0)
                    * (millisec - (tickPeriod / 2 + bitNumber * blendSpeed))
                    / ((tickPeriod / 2 + (bitNumber + 1) * blendSpeed) - (tickPeriod / 2 + bitNumber * blendSpeed));
    else intensity = 0.8;

    rect.setFillColor(sf::Color(0, 200, 200, 255 * intensity));
    window->draw(rect);

    return intensity;
}
