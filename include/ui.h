#pragma once

#include "tableHandler.h"

/**
 * @class UI
 * @brief Handles the graphical user interface for the restaurant table management system.
 *
 * The UI class is responsible for rendering the background, interacting with the user,
 * and providing input fields for configuring table data and reservations.
 */
class UI
{
private:
    Texture bg;                     ///< Background texture
    TableHandler* tables;          ///< Pointer to the table handler
    int tableState;                ///< Current state of the selected table
    int deltaID;                   ///< Used for table selection changes
    bool tableConfigWindowActive; ///< Indicates if the table configuration window is active

    // Entry field state and values
    bool entryXActive;             ///< Is the X position input active
    int entryXValue;               ///< Value of the X position input

    bool entryYActive;             ///< Is the Y position input active
    int entryYValue;               ///< Value of the Y position input

    bool entrySizeActive;          ///< Is the size input active
    int entrySizeValue;            ///< Value of the size input

    bool entryNameActive;          ///< Is the name input active
    char entryNameValue[128] = "";///< Value of the name input

    bool entryPhoneActive;         ///< Is the phone input active
    char entryPhoneValue[128] = "";///< Value of the phone number input

    bool entryHourActive;          ///< Is the hour input active
    int entryHourValue;            ///< Value of the hour input

    bool entryMinuteActive;        ///< Is the minute input active
    int entryMinuteValue;         ///< Value of the minute input

public:
    /**
     * @brief Constructs the UI object with a reference to the TableHandler.
     * @param tables Pointer to the TableHandler managing all tables.
     */
    UI(TableHandler* tables);

    /**
     * @brief Loads textures required for the UI.
     */
    void loadTextures();

    /**
     * @brief Unloads UI textures.
     */
    void unloadTextures();

    /**
     * @brief Renders the entire UI including background, table states, and input fields.
     */
    void draw();
};

