#ifndef SEGMENT_H
#define SEGMENT_H

#include <SFML/Graphics.hpp>

class Segment
{
    public:
        Segment(int x, int y,
                unsigned int w, unsigned int h,
                unsigned int bitNumberArg,
                float tickTimeArg,
                float blendSpeedArg);
        ~Segment();

        float draw(sf::RenderWindow *window, uint32_t millisec);

    private:
        int xPos, yPos;
        unsigned int width, height;
        unsigned int bitNumber;
        uint32_t blendSpeed;
        uint32_t tickPeriod;

        sf::RectangleShape rect;
};

#endif // SEGMENT_H
