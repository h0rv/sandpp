// Make sure widths and height is divisible by ratio
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480 
#define PIXEL_RATIO   4

struct Color {
    unsigned char R, G, B;
};

struct sand {
    bool isActive;
    Color *color;
    
    sand() { 
        this->isActive = false;
    }

    sand(Color *color) {
        this->isActive = true;
        this->color = color;
    }
    
    // deep copy constructor
    sand(const sand &other) : isActive(other.isActive), color(other.color) {};
};

// Dracula Colors 
/* const Color bg = {40, 42, 54}; */
/* // Global Colors */
/* Color colors[5] = { */
/*     {189, 147, 249}, */
/*     {139, 233, 253}, */
/*     {255, 121, 198}, */
/*     {80, 250, 123}, */
/*     {255, 184, 108}, */
/* }; */
/* const unsigned char numColors = 5; */

// Gruvbox Colors
const Color bg = {40, 40, 40};
// Global Colors
Color colors[6] = {
    {204, 36, 29},
    {152, 151, 26},
    {215, 133, 136},
    {177, 98, 134},
    {104, 157, 106},
    {214, 93, 14},
};
const unsigned char numColors = 6;

const int rows = SCREEN_HEIGHT/PIXEL_RATIO;
const int cols = SCREEN_WIDTH/PIXEL_RATIO;
