#ifndef CONSTANTS
#define CONSTANTS

namespace Constants
{
    const int SCENE_RECT_X = 0;
    const int SCENE_RECT_Y = 0;
    const int SCENE_RECT_WIDTH = 1000;
    const int SCENE_RECT_HIGH = 600;

    const int TIMER_STEP_MS = 50;

    const int ANTS_COUNT = 20;
    const int ANT_SPEED = 2;
    const int ANT_DIAMETER = 15;
    const int ANT_ANGLE = 15;
    const int ANT_CAPACITY = 1;

    const int FOOD_COUNT = 5;
    const int FOOD_DIAMETER = 50;
    const int FOOD_AMOUNT = 10;

    const int ANTHILL_DIAMETER = 100;
    const int ANTHILL_CAPACITY = 0;
    const int ANTHILL_X = SCENE_RECT_X + ANT_DIAMETER;
    const int ANTHILL_Y = SCENE_RECT_Y + ANT_DIAMETER;
}

#endif // CONSTANTS

