#pragma once

#include <iostream>
#include <string>

/**
 * @class Table
 * @brief Represents a table in a restaurant with reservation and state information.
 *
 * The Table class encapsulates properties related to a restaurant table, including
 * its position, state (e.g., free, reserved, occupied), and reservation details.
 */
class Table
{
private:
    // GUI data
    int x;  ///< X-coordinate of the table on the layout
    int y;  ///< Y-coordinate of the table on the layout

    // Table properties
    short int state; ///< Current state of the table: free, occupied, reserved, or late reservation
    short int size;  ///< Maximum number of people the table can accommodate

    // Reservation data
    std::string name;        ///< Name of the person who reserved the table
    std::string phoneNumber; ///< Phone number of the person who reserved the table
    short int hour;          ///< Reservation hour (0–23)
    short int minute;        ///< Reservation minute (0–59)

public:
    /**
     * @brief Default constructor.
     */
    Table();

    /**
     * @brief Parameterized constructor to initialize a table with full data.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param state Table state.
     * @param size Number of people the table supports.
     * @param name Reservation name.
     * @param phoneNumber Reservation phone number.
     * @param hour Reservation hour.
     * @param minute Reservation minute.
     */
    Table(int x, int y, short int state, short int size,
          const std::string& name, const std::string& phoneNumber,
          short int hour, short int minute);

    /**
     * @brief Assignment operator.
     * @param obj Table to copy from.
     * @return Reference to this table.
     */
    Table& operator=(Table obj);

    /**
     * @brief Set all table data at once.
     */
    void setAll(int x, int y, short int state, short int size,
                const std::string& name, const std::string& phoneNumber,
                short int hour, short int minute);

    /**
     * @brief Change the table’s position and size.
     */
    void changeMainData(int newX, int newY, short int newSize);

    /**
     * @brief Make a reservation for the table.
     */
    void reserve(const std::string& clientName, const std::string& clientPhoneNumber,
                 short int reservationHour, short int reservationMinute);

    /**
     * @brief Mark the table as occupied.
     */
    void occupy();

    /**
     * @brief Free the table, removing reservation and occupancy state.
     */
    void free();

    /**
     * @brief Check if a reservation is late based on the current time.
     */
    void timeCheck(short int currentHour, short int currentMinute);

    /**
     * @brief Test function (used for debug or placeholder).
     */
    void test();

    // Getters

    /**
     * @brief Get the current state of the table.
     */
    short int getState();

    /**
     * @brief Get the X-coordinate of the table.
     */
    int getX();

    /**
     * @brief Get the Y-coordinate of the table.
     */
    int getY();

    /**
     * @brief Get the maximum number of people allowed at the table.
     */
    short int getSize();

    /**
     * @brief Get the name of the reservation holder.
     */
    std::string getName();

    /**
     * @brief Get the phone number of the reservation holder.
     */
    std::string getPhoneNumber();

    /**
     * @brief Get the hour of the reservation.
     */
    short int getHour();

    /**
     * @brief Get the minute of the reservation.
     */
    short int getMinute();
};

