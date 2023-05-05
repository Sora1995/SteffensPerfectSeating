/***************************************************************
* Name : Final
* Author: Andrew Evans
* Created : 04/05/2023
* Course: CIS 152 - Data Structure
* Version: 1.0
* OS: Windows 11
* IDE: QT Creator 9.0.0
* Copyright : This is my own original work
* based on specifications issued by our instructor
* Description : An app that creates a deque and sorts passengers into their seats
*            Input: int rows, the number of rows in the plane
*            Ouput: strings informing user what to do, final seating arrangement
* Academic Honesty: I attest that this is my original work.
* I have not used unauthorized source code, either modified or
* unmodified. I have not given other fellow student(s) access
* to my program.
***************************************************************/

#include <iostream>
#include <queue>
#include <QCoreApplication>
#include <QTextStream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <time.h>
#include <stdlib.h>

/**************************************************************
* Name: generate_deque
* Description: Generates the deque
* Input: int rows, constant int cols
* Output: N/A
***************************************************************/

std::deque<int> generate_deque(int rows, const int cols) {

    std::deque<int> q;
    int total = rows * cols;
    for (int i = 1; i <= total; i++)
    {
        q.push_back(i);
    }
    return q;
}

/**************************************************************
* Name: insertionSort
* Description: Insertion sort of deque
* Input: Deque
* Output: N/A
***************************************************************/

void insertionSort(std::deque<int>& d)
{
    int n = d.size();

    for (int i = 1; i < n; i++) {
        int key = d[i];
        int j = i - 1;

        while (j >= 0 && d[j] > key) {
            d[j + 1] = d[j];
            j--;
        }
        d[j + 1] = key;
    }
}

/**************************************************************
* Name: main
* Description: Main portion of the program
* Input: N/A
* Output: Program
***************************************************************/

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream qin(stdin);
    QTextStream qout(stdout);

    // Defines critical values
    bool ok;
    int cols = 6;

    // Prompts user
    qout << "Enter how many rows are in the plane: " <<Qt::endl;

    int rows = qin.readLine().toInt(&ok);

    while(!ok || rows <= 0)
    {
        qout << "Enter a positive, whole number" << Qt::endl;
        rows = qin.readLine().toInt(&ok);
    }

    qout.flush();

    if(ok)
    {
        qout << "There are " << rows << " rows in the plane, for a total of " << (rows * cols) << " seats." << Qt::endl;
        qout << "Each column of seats is represented with a letter (A - F) and each row is represented by a number (1 - " << rows << ")." << Qt::endl;
        qout << "Passengers will now be randomly assigned boarding order." << Qt::endl;
    }

    // Generates new array of the defined size in runtime with "new"
    int** seats = new int* [rows];
    for (int i = 0; i < rows; i++) { seats[i] = new int[cols]; };

    // Fills deque with passengers
    std::deque<int> passengers = generate_deque(rows, cols);

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    std::shuffle(passengers.begin(), passengers.end(), rng);

    std::deque<int> sorted_passengers(passengers);

    // Populate seats
    for (int l_col = 0; l_col < cols / 2; l_col++) {
        int r_col = cols - l_col - 1;
        for (int r = 0; r < rows; r += 2)
        {
            seats[rows - 1 - r][l_col] = passengers.front();
            passengers.pop_front();
        }
        for (int r = 0; r < rows; r += 2)
        {
            seats[rows - 1 - r][r_col] = passengers.front();
            passengers.pop_front();
        }
        for (int r = 1; r < rows; r += 2)
        {
            seats[rows - 1 - r][l_col] = passengers.front();
            passengers.pop_front();
        }
        for (int r = 1; r < rows; r += 2)
        {
            seats[rows - 1 - r][r_col] = passengers.front();
            passengers.pop_front();
        }
    }

    // Display seating arrangement
    qout << "\t  A  \tB  \tC  \tD  \tE  \tF" << Qt::endl;
    for (int r = 0; r < rows; r++) {
        qout << "Row " << r + 1 << "\t: ";
        for (int c = 0; c < cols; c++) {
            qout << seats[r][c] << "\t";
        }
        qout << Qt::endl;
    }

    qout << "\nNow, the passengers will be sorted into their correct seats\n" << Qt::endl;

    insertionSort(sorted_passengers);

    // Populate seats
    for (int l_col = 0; l_col < cols / 2; l_col++) {
        int r_col = cols - l_col - 1;
        for (int r = 0; r < rows; r += 2)
        {
            seats[rows - 1 - r][l_col] = sorted_passengers.front();
            sorted_passengers.pop_front();
        }
        for (int r = 0; r < rows; r += 2)
        {
            seats[rows - 1 - r][r_col] = sorted_passengers.front();
            sorted_passengers.pop_front();
        }
        for (int r = 1; r < rows; r += 2)
        {
            seats[rows - 1 - r][l_col] = sorted_passengers.front();
            sorted_passengers.pop_front();
        }
        for (int r = 1; r < rows; r += 2)
        {
            seats[rows - 1 - r][r_col] = sorted_passengers.front();
            sorted_passengers.pop_front();
        }
    }

    // Display seating arrangement
    qout << "\t  A  \tB  \tC  \tD  \tE  \tF" << Qt::endl;
    for (int r = 0; r < rows; r++) {
        qout << "Row " << r + 1 << "\t: ";
        for (int c = 0; c < cols; c++) {
            qout << seats[r][c] << "\t";
        }
        qout << Qt::endl;
    }

    // Memory cleanup
    for (int i = 0; i < rows; i++) {
        delete[] seats[i];
    }
    delete[] seats;

    return 0;

}
