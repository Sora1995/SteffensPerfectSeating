#include <iostream>
#include <queue>
#include <time.h>
#include <cstdlib>
#include <QCoreApplication>
#include <QTextStream>

void showq(std::queue<int> gq)
{
    QTextStream qin(stdin);
    QTextStream qout(stdout);
    std::queue<int> g = gq;
    while (!g.empty()) {
        qout << '\t' << g.front();
        g.pop();
    }
    qout << '\n';
}

std::queue<int> generate_random_queue(int rows, const int cols) {
    srand((unsigned)time(NULL));
    std::queue<int> q;
    int total = rows * cols;
    for (int i = 1; i <= total; i++)
    {
        (rand() * (RAND_MAX + 1) + rand()) % rows;
    }
    return q;
}

char col_letter(int i)
{
    return static_cast<char>('A' + i);
}


int main(int argc, char* argv[])
{

    QCoreApplication a(argc, argv);

    QTextStream qin(stdin);
    QTextStream qout(stdout);


    // Define critical values
    bool ok;
    int cols = 6;

    // Prompt user
    qout << "Enter how many rows are in the plane: " <<Qt::endl;
    int rows = qin.readLine().toInt(&ok);

    while(!ok)
    {
        qout << "Enter a positive, whole number" << Qt::endl;
        rows = qin.readLine().toInt(&ok);
    }

    qout.flush();

    if(ok)
    {
        qout << "There are " << rows << " rows in the plane, for a total of " << (rows * cols) << " seats." << Qt::endl;
        qout << "Each column of seats is represented with a letter (A - F) and each row is represented by a number (1 - " << rows << ")." << Qt::endl;
        qout << "Passengers will now be assigned boarding order." << Qt::endl;
    }

    // Generate new array of the defined size in runtime with "new"
    int** seats = new int* [rows];
    for (int i = 0; i < rows; i++) { seats[i] = new int[cols]; };



    // Fill the queue with passengers
    std::queue<int> passengers = generate_random_queue(rows, cols);



    // Populate seats
    for (int l_col = 0; l_col < cols / 2; l_col++) {
        int r_col = cols - l_col - 1;
        for (int r = 0; r < rows; r += 2)
        {
            //qout << "Attempting to add passenger " << passengers.front() << "\tto the plane in seat " << col_letter(l_col) << rows - r << Qt::endl;
            seats[rows - 1 - r][l_col] = passengers.front();
            passengers.pop();
        }
        for (int r = 0; r < rows; r += 2)
        {
            //qout << "Attempting to add passenger " << passengers.front() << "\tto the plane in seat " << col_letter(r_col) << rows - r << Qt::endl;
            seats[rows - 1 - r][r_col] = passengers.front();
            passengers.pop();
        }
        for (int r = 1; r < rows; r += 2)
        {
            //qout << "Attempting to add passenger " << passengers.front() << "\tto the plane in seat " << col_letter(l_col) << rows - r << Qt::endl;
            seats[rows - 1 - r][l_col] = passengers.front();
            passengers.pop();
        }
        for (int r = 1; r < rows; r += 2)
        {
            //qout << "Attempting to add passenger " << passengers.front() << "\tto the plane in seat " << col_letter(r_col) << rows - r << Qt::endl;
            seats[rows - 1 - r][r_col] = passengers.front();
            passengers.pop();
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
