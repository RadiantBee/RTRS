/**
 * @file main.cpp
 * @brief Entry point for the Restaurant Table Reservation System (RTRS).
 *
 * Initializes the window and core systems, loads data, and enters the main update/render loop.
 * Delegates functionality to TableHandler and UI classes.
 */

#include <string>
#define RAYGUI_STATIC
#include "ui.h"
#include <ctime>

/**
 * @brief Application entry point.
 *
 * Initializes the graphical window, loads saved table data, updates the table states over time,
 * and handles rendering and input. Uses the TableHandler and UI classes to manage state and draw the interface.
 *
 * @return Exit code (0 if successful).
 */
int main ()
{
    // Enable vsync and support for high-DPI screens
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    // Initialize window and OpenGL context
    InitWindow(800, 600, "RTRS");

    // Set working directory to resources folder for texture loading
    SearchAndSetResourceDir("resources");

    // Create core components
    TableHandler tables("saveFile.txt");
    UI ui(&tables);
    ui.loadTextures();
    tables.loadData();

    // Time tracking for live updates
    std::time_t now;
    std::tm* localTime;
    short int hour, minute;
    std::string stringTime = "";

    // Main application loop
    while (!WindowShouldClose())
    {
        now = std::time(nullptr);
        localTime = std::localtime(&now);

        hour = localTime->tm_hour;
        minute = localTime->tm_min;

        // Format time string as HH:MM
        stringTime = hour > 9 ? std::to_string(hour) : "0" + std::to_string(hour);
        stringTime += ":";
        stringTime += minute > 9 ? std::to_string(minute) : "0" + std::to_string(minute);

        // Mouse input handling
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            tables.onClick(GetMouseX(), GetMouseY());
        }

        // Update table states (e.g., late reservations)
        tables.update(hour, minute);

        // Rendering
        BeginDrawing();
        ui.draw();
        DrawText(stringTime.c_str(), 10, 550, 50, WHITE); // Display current time
        EndDrawing();
    }

    // Save table data before exiting
    tables.saveData();

    // Cleanup
    ui.unloadTextures();
    CloseWindow();

    return 0;
}

