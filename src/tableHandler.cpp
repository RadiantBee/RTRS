/**
 * @file tableHandler.cpp
 * @brief Manages a collection of Table objects, including their creation, deletion, serialization, and rendering.
 */

#include "tableHandler.h"

/**
 * @brief Constructs a TableHandler with a specified filename for saving/loading.
 */
TableHandler::TableHandler(const std::string& filename)
{
    amount = 0;
    saveFileName = filename;
    activeID = -1;
}

/**
 * @brief Destructor that deallocates the table array if it's been initialized.
 */
TableHandler::~TableHandler()
{
    if (amount != 0)
    {
        delete[] tables;
    }
}

/**
 * @brief Loads table data from the save file.
 */
void TableHandler::loadData()
{
    int x, y;
    short int state, size, hour, minute;
    std::string name, phoneNumber;

    std::ifstream saveFile(saveFileName);
    while (saveFile >> x >> y >> state >> size >> name >> phoneNumber >> hour >> minute)
    {
        this->createNewTable();
        tables[amount - 1].setAll(x, y, state, size, name, phoneNumber, hour, minute);
    }
}

/**
 * @brief Saves current table data to the save file.
 */
void TableHandler::saveData()
{
    std::ofstream saveFile(saveFileName);
    if (saveFile)
    {
        for (int i = 0; i < amount; ++i)
        {
            saveFile << tables[i].getX() << " "
                     << tables[i].getY() << " "
                     << tables[i].getState() << " "
                     << tables[i].getSize() << " "
                     << tables[i].getName() << " "
                     << tables[i].getPhoneNumber() << " "
                     << tables[i].getHour() << " "
                     << tables[i].getMinute() << "\n";
        }
        saveFile.close();
    }
}

/**
 * @brief Adds a new Table to the dynamic table array.
 */
void TableHandler::createNewTable()
{
    Table* temp = new Table[amount + 1];

    if (amount != 0)
    {
        for (int i = 0; i < amount; ++i)
        {
            temp[i] = tables[i];
        }
        delete[] tables;
    }

    tables = temp;
    ++amount;
}

/**
 * @brief Deletes a table by index.
 *
 * @param id Index of the table to delete.
 */
void TableHandler::deleteTable(int id)
{
    if (amount == 0)
    {
        std::cerr << "!!!Can't delete table from empty array!!!\n";
        return;
    }

    if (id >= amount || id < 0)
    {
        std::cerr << "!!!Can't delete table 'cause index is out of range!!!\n";
        return;
    }

    if (amount == 1)
    {
        delete[] tables;
        amount = 0;
        return;
    }

    Table* temp = new Table[amount - 1];

    for (int i = 0; i < id; ++i)
    {
        temp[i] = tables[i];
    }

    for (int i = id + 1; i < amount; ++i)
    {
        temp[i - 1] = tables[i];
    }

    delete[] tables;
    tables = temp;
    --amount;
}

/**
 * @brief Loads table textures used for rendering.
 */
void TableHandler::loadTextures()
{
    tableFreeTexture = LoadTexture("tableFree.png");
    tableOccupiedTexture = LoadTexture("tableOccupied.png");
    tableReservedTexture = LoadTexture("tableReserved.png");
    tableReservedLateTexture = LoadTexture("tableReservedLate.png");
}

/**
 * @brief Unloads textures to free GPU memory.
 */
void TableHandler::unloadTextures()
{
    UnloadTexture(tableFreeTexture);
    UnloadTexture(tableOccupiedTexture);
    UnloadTexture(tableReservedTexture);
    UnloadTexture(tableReservedLateTexture);
}

/**
 * @brief Updates the state of all tables based on the current time.
 *
 * @param hour Current hour.
 * @param minute Current minute.
 */
void TableHandler::update(short int hour, short int minute)
{
    for (int i = 0; i < amount; ++i)
    {
        tables[i].timeCheck(hour, minute);
    }
}

/**
 * @brief Draws all tables using appropriate textures based on their state.
 */
void TableHandler::draw()
{
    for (int i = 0; i < amount; ++i)
    {
        Texture2D* texture = nullptr;
        switch (tables[i].getState())
        {
        case 1:
            texture = &tableReservedTexture;
            break;
        case 2:
            texture = &tableReservedLateTexture;
            break;
        case 3:
            texture = &tableOccupiedTexture;
            break;
        default:
            texture = &tableFreeTexture;
            break;
        }

        DrawTextureEx(*texture, Vector2{ tables[i].getX(), tables[i].getY() }, 0, 2, WHITE);
        DrawText(std::to_string(tables[i].getSize()).c_str(), tables[i].getX() + 25, tables[i].getY() + 20, 20, BLACK);
    }
}

/**
 * @brief Detects table selection based on mouse click coordinates.
 *
 * @param x Mouse X coordinate.
 * @param y Mouse Y coordinate.
 */
void TableHandler::onClick(int x, int y)
{
    for (int i = 0; i < amount; ++i)
    {
        if (x > tables[i].getX() && x < (tables[i].getX() + 64) &&
            y > tables[i].getY() && y < (tables[i].getY() + 64))
        {
            activeID = i;
            break;
        }
    }
}

/**
 * @brief Gets the index of the currently active table.
 */
int TableHandler::getActiveID()
{
    return activeID;
}

/**
 * @brief Sets the currently active table index.
 */
void TableHandler::setActiveID(int newID)
{
    activeID = newID;
}

/**
 * @brief Returns a reference to the currently active Table.
 * Returns the first table if no active ID is set.
 */
Table& TableHandler::getActiveIndexRef()
{
    return tables[activeID >= 0 ? activeID : 0];
}

/**
 * @brief Prints all table data to standard output for debugging.
 */
void TableHandler::test()
{
    for (int i = 0; i < amount; ++i)
    {
        std::cout << i << ": "
                  << tables[i].getX() << " "
                  << tables[i].getY() << " "
                  << tables[i].getState() << " "
                  << tables[i].getSize() << " "
                  << tables[i].getName() << " "
                  << tables[i].getPhoneNumber() << " "
                  << tables[i].getHour() << " "
                  << tables[i].getMinute() << "\n";
    }
}

