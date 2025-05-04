#include "ui.h"

#include "raylib.h"
#include <cstring>
#define RAYGUI_NO_RICONS
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

/**
 * @brief Constructs the UI and initializes default values.
 * 
 * @param tables Pointer to the TableHandler managing all tables.
 */
UI::UI(TableHandler* tables)
{
    this->tables = tables;
    tableState = 0;
    deltaID = -1;
    tableConfigWindowActive = true;
    entryXActive = false;
    entryXValue = 0;
    entryYActive = false;
    entryYValue = 0;
    entrySizeActive = false;
    entrySizeValue = 0;
    entryNameActive = false;
    entryPhoneActive = false;
    entryHourActive = false;
    entryHourValue = 0;
    entryMinuteActive = false;
    entryMinuteValue = 0;
}

/**
 * @brief Loads background texture and table textures.
 */
void UI::loadTextures()
{
    bg = LoadTexture("cafePlaceholder.png");
    tables->loadTextures();
}

/**
 * @brief Unloads background and table textures to free memory.
 */
void UI::unloadTextures()
{
    tables->unloadTextures();
    UnloadTexture(bg);
}

/**
 * @brief Renders the entire UI frame, including buttons and table configuration window.
 * 
 * Displays the background, handles GUI input, and allows table creation, modification, 
 * deletion, and reservation.
 */
void UI::draw()
{
    ClearBackground(BLACK);
    DrawTexture(bg, 0,0,WHITE);

    tables->draw();

    // Buttons for creating a new table and saving data
    if (GuiButton((Rectangle){ 150, 550, 120, 30 }, "New Table"))
    {
        tables->createNewTable();
    }
    if (GuiButton((Rectangle){ 300, 550, 120, 30 }, "Save"))
    {
        tables->saveData();
    }

    // If a table is selected, show its configuration
    if (tables->getActiveID() != -1)
    {
        tableState = tables->getActiveIndexRef().getState();

        // Refresh input values if active table changed
        if(deltaID != tables->getActiveID())
        {
            deltaID = tables->getActiveID();

            entryXValue = tables->getActiveIndexRef().getX();
            entryYValue = tables->getActiveIndexRef().getY();
            entrySizeValue = tables->getActiveIndexRef().getSize();

            strncpy(entryNameValue, tables->getActiveIndexRef().getName().c_str(),128);
            strncpy(entryPhoneValue, tables->getActiveIndexRef().getPhoneNumber().c_str(),128);

            entryHourValue = tables->getActiveIndexRef().getHour();
            entryMinuteValue = tables->getActiveIndexRef().getMinute();
        }

        tableConfigWindowActive = !GuiWindowBox((Rectangle){ 550, 25, 200, 310 }, "Configure Table");

        // Display ID and position/size input
        GuiLabel((Rectangle){ 560, 50, 56, 24 }, "ID:");
        GuiLabel((Rectangle){ 580, 50, 24, 24 }, std::to_string(tables->getActiveID()).c_str());

        if (GuiValueBox((Rectangle){ 620, 75, 120, 24 }, "Position x: ", &entryXValue, 0, 750, entryXActive)) entryXActive = !entryXActive;
        if (GuiValueBox((Rectangle){ 620, 100, 120, 24 }, "Position y: ", &entryYValue, 0, 550, entryYActive)) entryYActive = !entryYActive;
        if (GuiValueBox((Rectangle){ 620, 125, 120, 24 }, "Size: ", &entrySizeValue, 0, 100, entrySizeActive)) entrySizeActive = !entrySizeActive;

        // Display current state and allow updates
        GuiLabel((Rectangle){ 560, 150, 56, 24 }, "Status:");
        GuiLabel((Rectangle){ 600, 150, 48, 24 }, tableState==0?"Free":tableState==1?"Reserved":tableState==2?"Reserved and late":"Occupied");

        if(GuiButton((Rectangle){ 560, 175, 72, 24 }, "Save"))
        {
            tables->getActiveIndexRef().changeMainData(entryXValue, entryYValue, entrySizeValue);
        }

        if(GuiButton((Rectangle){ 670, 175, 72, 24 }, tableState==3?"Free":"Occupy"))
        {
            tableState==3 ? tables->getActiveIndexRef().free() : tables->getActiveIndexRef().occupy();
        }

        GuiLine((Rectangle){ 550, 200, 208, 12 }, NULL);

        // Reservation details input
        GuiLabel((Rectangle){ 560, 225, 80, 24 }, "Name:");
        if (GuiTextBox((Rectangle){ 620, 225, 120, 24 }, entryNameValue, 128, entryNameActive)) entryNameActive = !entryNameActive;

        GuiLabel((Rectangle){ 560, 250, 80, 24 }, "Phone:");
        if (GuiTextBox((Rectangle){ 620, 250, 120, 24 }, entryPhoneValue, 128, entryPhoneActive)) entryPhoneActive = !entryPhoneActive;

        GuiLabel((Rectangle){ 560, 275, 120, 24 }, "Time: [H|M]");
        if (GuiValueBox((Rectangle){ 620, 275, 60, 24 }, "", &entryHourValue, 0, 23, entryHourActive)) entryHourActive = !entryHourActive;
        if (GuiValueBox((Rectangle){ 680, 275, 60, 24 }, "", &entryMinuteValue, 0, 59, entryMinuteActive)) entryMinuteActive = !entryMinuteActive;

        // Reservation and deletion buttons
        if(GuiButton((Rectangle){ 670, 300, 72, 24 }, "Reserve"))
        {
            tables->getActiveIndexRef().reserve(entryNameValue, entryPhoneValue, entryHourValue, entryMinuteValue);
        }

        if(GuiButton((Rectangle){ 560, 300, 72, 24 }, "Delete"))
        {
            tables->deleteTable(tables->getActiveID());
            tables->setActiveID(-1);
        }
    }
}

