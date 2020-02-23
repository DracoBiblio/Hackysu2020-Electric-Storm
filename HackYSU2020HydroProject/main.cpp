#include <iostream>
#include <ofstream>
#include <chrono>
#include <time.h>

using namespace std;


bool WaterTemp(float);

bool WaterPressure(float, float, float);

float calculateAveragePressure(float, double, float);

float calculateAverageEnergy(float, double, float);


int main()

{

    bool running = true;
    float average = 0.0;
    double count = 1;
    float pressureSum = 0.0;
    float AvgenergyGenerated;
    float totalEnergy;
    float lowerPressureLimit;
    float upperPressureLimit;

    cout << "Enter the lower limit for pressure: ";
    cin >> lowerPressureLimit;

    cout << "\nEnter the upper limit for pressure: ";
    cin >> upperPressureLimit;


    ofstream dataFile;
    ofstream errorFile;

    dataFile.open();
    errorFile.open();

    while (running == true){

        float pressure = 0;
        float currentTemp;
        float energy;

        cout << "input pressure: ";
        cin >> pressure;

        average = calculateAveragePressure(pressure, count, pressureSum);

        AvgenergyGenerated = calculateAverageEnergy(energy, count, totalEnergy);

        WaterTemp(currentTemp);

        if (WaterPressure(average, lowerPressureLimit, upperPressureLimit) == false){
            running = false;
        }

        if (WaterTemp(currentTemp) == false){
            running = false;
        }


        int hours = chrono::hours.count();

        //this probably isn't right
        if (hours <= 24){
            count += 1;

        }
        else if(hours == 1){
            dataFile << average << chrono::system_clock() << endl;
            average = 0.0;
        }
        else {
            count = 1;

        }

    }

    dataFile.close();
    errorFile.close();

    return 0;

}


bool WaterTemp(float temp){

    bool isSafe;


    if (temp < 45){
        //export error to document
        cout << "Temperature is too cold at " << temp << "degrees.";
        cout << "\nThis occured on " << chrono::system_clock();

        errorFile << temp << " degrees. Too cold." << chrono::system_clock() << endl;

        isSafe = false;

    }
    else if (temp > 80){
        cout << "Temperature is too warm at " << temp << "degrees.";
        cout << "\nThis occured on " << chrono::system_clock();

        errorFile << temp << " degrees. Too warm." << chrono::system_clock() << endl;


        isSafe = false;

    }
    else{
        isSafe = true;

    }

    return isSafe;

}



bool WaterPressure(float pressure, float lowerLimit, float upperLimit){

    bool isSafe;

    if (pressure < lowerLimit){

        cout << "Pressure is too low at " << pressure << " psi.";

        errorFile << pressure << " psi. Too low." << chrono::system_clock() << endl;


        isSafe = false;

    }

    else if(pressure > upperLimit){
        cout << "Pressure is high at " << pressure << " psi.";
        errorFile << pressure << " psi. Too low." << chrono::system_clock() << endl;


        isSafe = false;

    }
    else{
        isSafe = true;

    }

    return isSafe;

}


float calculateAveragePressure(float pressure, double count, float &sum){

    float tempAvg = 0.0;

    sum += pressure;

    tempAvg = sum/count;

    return tempAvg;

}


float calculateAverageEnergy(float energy, double count, float &totalEnergy){

    float tempAvg = 0.0;

    totalEnergy += energy;

    tempAvg = totalEnergy/count;

    return tempAvg;

}

