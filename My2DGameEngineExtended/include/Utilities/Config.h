#pragma once

struct GraphicsConfig {
    int screenWidth{0};
    int screenHeight{0};
    int resolutionWidth{0};
    int resolutionHeight{0};

    GraphicsConfig(const int screenWidth, const int screenHeight, const int resolutionWidth, const int resolutionHeight) 
        : screenWidth{screenWidth}, screenHeight{screenHeight}, resolutionWidth{resolutionWidth}, resolutionHeight{resolutionHeight} {}
};