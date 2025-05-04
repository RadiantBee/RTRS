/**
 * @file tables.cpp
 * @brief Implementation of the Table class for managing individual restaurant tables and their reservations.
 */

#include "tables.h"

/**
 * @brief Default constructor for a Table.
 *
 * Initializes the table with default values indicating it's unused or unconfigured.
 */
Table::Table()
{
    x = 0;
    y = 0;
    state = 0;
    size = -1;
    name = "-";
    phoneNumber = "-1";
    hour = -1;
    minute = -1;
}

/**
 * @brief Parameterized constructor for a Table.
 *
 * @param x Table's X position.
 * @param y Table's Y position.
 * @param state Initial state (0: free, 1: reserved, etc.).
 * @param size Number of people the table can seat.
 * @param name Reservation holder's name.
 * @param phoneNumber Reservation holder's phone number.
 * @param hour Reservation hour.
 * @param minute Reservation minute.
 */
Table::Table(int x, int y, short int state, short int size, const std::string& name, const std::string& phoneNumber, short int hour, short int minute)
{
    this->x = x;
    this->y = y;
    this->state = state;
    this->size = size;
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->hour = hour;
    this->minute = minute;
}

/**
 * @brief Sets all properties of the table at once.
 */
void Table::setAll(int x, int y, short int state, short int size, const std::string& name, const std::string& phoneNumber, short int hour, short int minute)
{
    this->x = x;
    this->y = y;
    this->state = state;
    this->size = size;
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->hour = hour;
    this->minute = minute;
}

/**
 * @brief Copy assignment operator using copy-swap idiom.
 */
Table& Table::operator=(Table obj)
{
    std::swap(x, obj.x);
    std::swap(y, obj.y);
    std::swap(state, obj.state);
    std::swap(size, obj.size);
    std::swap(name, obj.name);
    std::swap(phoneNumber, obj.phoneNumber);
    std::swap(hour, obj.hour);
    std::swap(minute, obj.minute);
    return *this;
}

/**
 * @brief Changes only the main physical data of the table (position and size).
 */
void Table::changeMainData(int newX, int newY, short int newSize)
{
    this->x = newX;
    this->y = newY;
    this->size = newSize;
}

/**
 * @brief Marks the table as reserved and stores reservation details.
 */
void Table::reserve(const std::string& clientName, const std::string& clientPhoneNumber, short int reservationHour, short int reservationMinute)
{
    this->state = 1;
    this->name = clientName;
    this->phoneNumber = clientPhoneNumber;
    this->hour = reservationHour;
    this->minute = reservationMinute;
}

/**
 * @brief Marks the table as currently occupied.
 */
void Table::occupy()
{
    state = 3;
}

/**
 * @brief Frees the table and clears any reservation details.
 */
void Table::free()
{
    state = 0;
    name = "-";
    phoneNumber = "-1";
    hour = -1;
    minute = -1;
}

/**
 * @brief Checks if a reserved table is late compared to the current time.
 * Changes state to 2 if late.
 */
void Table::timeCheck(short int currentHour, short int currentMinute)
{
    if (state == 1)
    {
        if (this->hour < currentHour || (this->hour == currentHour && this->minute < currentMinute))
        {
            state = 2; // Table is late
        }
    }
}

/**
 * @brief Debug method to print test output.
 */
void Table::test()
{
    std::cout << "test\n";
}

// ------------------------ Getters ------------------------

/**
 * @brief Returns the current state of the table.
 */
short int Table::getState()
{
    return state;
}

/**
 * @brief Returns the X position of the table.
 */
int Table::getX()
{
    return x;
}

/**
 * @brief Returns the Y position of the table.
 */
int Table::getY()
{
    return y;
}

/**
 * @brief Returns the size (seating capacity) of the table.
 */
short int Table::getSize()
{
    return size;
}

/**
 * @brief Returns the name on the reservation.
 */
std::string Table::getName()
{
    return name;
}

/**
 * @brief Returns the reservation phone number.
 */
std::string Table::getPhoneNumber()
{
    return phoneNumber;
}

/**
 * @brief Returns the reservation hour.
 */
short int Table::getHour()
{
    return hour;
}

/**
 * @brief Returns the reservation minute.
 */
short int Table::getMinute()
{
    return minute;
}

