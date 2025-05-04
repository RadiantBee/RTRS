#pragma once

#include "tables.h"
#include "resource_dir.h"
#include <fstream>

/**
 * @class TableHandler
 * @brief Manages a collection of restaurant tables and their interactions.
 *
 * This class handles dynamic creation, deletion, updating, saving/loading,
 * and rendering of table objects in a restaurant setting.
 */
class TableHandler
{
private:
    Table* tables;                    ///< Dynamic array of tables
    int amount;                       ///< Number of tables currently managed
    Texture tableFreeTexture;        ///< Texture used to represent a free table
    Texture tableOccupiedTexture;    ///< Texture used to represent an occupied table
    Texture tableReservedTexture;    ///< Texture used to represent a reserved table
    Texture tableReservedLateTexture;///< Texture used to represent a reserved but late table
    std::string saveFileName;        ///< File path for saving/loading table data
    int activeID;                    ///< ID of the currently selected/active table

public:
    /**
     * @brief Constructor that initializes the handler with a file name for data persistence.
     * @param filename The file name used for loading and saving table data.
     */
    TableHandler(const std::string& filename);

    /**
     * @brief Destructor to clean up resources.
     */
    ~TableHandler();

    /**
     * @brief Loads table data from the save file.
     */
    void loadData();

    /**
     * @brief Loads textures required for table visualization.
     */
    void loadTextures();

    /**
     * @brief Unloads previously loaded textures.
     */
    void unloadTextures();

    /**
     * @brief Saves current table data to the save file.
     */
    void saveData();

    /**
     * @brief Adds a new table to the collection.
     */
    void createNewTable();

    /**
     * @brief Deletes a table by its ID.
     * @param id The ID/index of the table to delete.
     */
    void deleteTable(int id);

    /**
     * @brief Updates the state of all tables based on the current time.
     * @param hour The current hour.
     * @param minute The current minute.
     */
    void update(short int hour, short int minute);

    /**
     * @brief Handles mouse click interactions on the table layout.
     * @param x The X-coordinate of the click.
     * @param y The Y-coordinate of the click.
     */
    void onClick(int x, int y);

    /**
     * @brief Renders all tables and their states.
     */
    void draw();

    /**
     * @brief Gets the ID of the currently active table.
     * @return The active table's ID.
     */
    int getActiveID();

    /**
     * @brief Sets the currently active table ID.
     * @param newID The new active table ID.
     */
    void setActiveID(int newID);

    /**
     * @brief Gets a reference to the currently active table.
     * @return Reference to the active table.
     */
    Table& getActiveIndexRef();

    /**
     * @brief Test function (for debug or development use).
     */
    void test();
};

