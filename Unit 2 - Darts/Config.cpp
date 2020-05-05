#include "Config.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void Config::GetConfig()
{
    //Validation code here was helped by the code found here:
    //https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers


	cout << "What would you like the starting score to be? (Default is 501)\n";

    std::string line;
    int d;
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (ss >> d)
        {
            if (ss.eof())
            {
                StartingScore = d;;
                break;
            }
            break;
        }
        std::cout << "Please only input a number" << std::endl;
    }

	cout << "What would you like Joes Accuracy to be? (Default is 71%)(Do not include a %)\n";
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (ss >> d)
        {
            if (ss.eof())
            {
                JoeAcc = d;
                break;
            }
            break;
        }
        std::cout << "Please only input a number" << std::endl;
    }

	cout << "What would you lie Sids Accuracy to be? (Default is 73%)(Do not include a %)\n";
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (ss >> d)
        {
            if (ss.eof())
            {
                SidAcc = d;
                break;
            }
            break;
        }
        std::cout << "Please only input a number" << std::endl;
    }

	cout << "What would you like the max rounds per set to be? (Default is 30)\n";
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (ss >> d)
        {
            if (ss.eof())
            {   
                MaxRounds = d;
                break;
            }
            break;
        }
        std::cout << "Please only input a number" << std::endl;
    }

	cout << "How many matches would you like to simulate? (Default is 1)\n";
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (ss >> d)
        {
            if (ss.eof())
            {   
                NumberOfGames = d;
                break;
            }
            break;
        }
        std::cout << "Please only input a number" << std::endl;
    }

    cout << "Would you like to display text when running the simulation (Saying no will speed up execution)(0 for no, anything else for yes)\n";
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (ss >> d)
        {
            if (ss.eof())
            {
                displayText = d;
                break;
            }
            break;
        }
        std::cout << "Please only input a number" << std::endl;
    }
}
