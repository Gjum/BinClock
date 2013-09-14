#include <Segment.h>

#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
    const unsigned int gridSize = 50;
    const unsigned int gridSpace = 4;

    const float tickTime = 1.0; // part of a second
    const float blendSpeed = 0.1; // part of tickTime

    const unsigned int numberOfSegments = 16;

    Segment *segments[numberOfSegments];

    for (unsigned int i = 0; i < numberOfSegments; i++)
        segments[i] = new Segment(gridSpace / 2,
                                  i * gridSize + gridSpace / 2,
                                  gridSize - gridSpace,
                                  gridSize - gridSpace,
                                  i, tickTime, blendSpeed);


    const unsigned int debugLines = 0; // set to 0 to disable debugging
    const int32_t debugEveryMs = 0; // 0 for instant feedback
    float debugMatrix[debugLines * numberOfSegments];
    unsigned int debugIndex = 0;
    int32_t timeLastDebug = 0;

    for (unsigned int i = 0; i < debugLines * numberOfSegments; i++)
        debugMatrix[i] = 0.0;


    sf::RenderWindow window(sf::VideoMode(gridSize + debugLines, numberOfSegments * gridSize), "Binary Clock Simulator");

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int32_t timeElapsed = clock.getElapsedTime().asMilliseconds();

        window.clear();

        for (unsigned int i = 0; i < numberOfSegments; i++)
        {
            if (debugLines <= 0) segments[i]->draw(&window, timeElapsed);
            else debugMatrix[debugIndex + i] = segments[i]->draw(&window, timeElapsed);
        }

        if (debugLines > 0)
        {
            for (unsigned int segment = 0; segment < numberOfSegments; segment++)
                for (unsigned int line = 0; line < debugLines - 1; line++)
                {
                    if (line == debugIndex / numberOfSegments) continue;

                    float va = debugMatrix[line * numberOfSegments + segment];
                    float vb = debugMatrix[(line + 1) * numberOfSegments + segment];
//                    float vb = va + 1.0 / gridSize; // no interpolation

                    sf::Vertex vertexArray[] =
                    {
                        sf::Vertex(sf::Vector2f(
                            line + gridSize,
                            (segment + 1) * gridSize - va * (gridSize - gridSpace) - gridSpace / 2)),

                        sf::Vertex(sf::Vector2f(
                            line + gridSize + 1,
                            (segment + 1) * gridSize - vb * (gridSize - gridSpace) - gridSpace / 2))
                    };
                    window.draw(vertexArray, 2, sf::Lines);
                }

            if (timeElapsed > timeLastDebug + debugEveryMs)
            {
                timeLastDebug += debugEveryMs;
                debugIndex += numberOfSegments;
                if (debugIndex >= debugLines * numberOfSegments) debugIndex = 0;
            }
        }

        window.display();
    }

    // TODO re-enable, disabled because compiler warns
    //delete [] segments;

    return EXIT_SUCCESS;
}
