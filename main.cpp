/*Poppy La
File name: main.cpp
Instructor: Dr.Stiber
Date: 02/05/2021
Course: CSS343
Program 2: The Kevin Bacon Game
   The purpose of this programming assignment is counting the number of links between each actor and Kevin Bacon, 
   then print the names with their Bacon numbers as the result. A map will be used to determine the links between
   all the actors in the same movie. An adjacency list will be created and used to store actor's link and count 
   their bacon number. The program will take and read an input file from the command line argument. The output names 
   will be printed in the input file order, following by their bacon number. A BaconNumber class will be used to 
   process the input file and pass to a Graph class to calculate bacon number.
*/

#include "BaconNumber.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
   //notice the missing input file name
   if(argv[1] == nullptr){
      cout << "Please input a file name! " << endl;
   
   } else {
       //ignore all the other input after corpus file in command line argument, then process
      if (argc > 2) {
         cout << "Data after the file name will be ignored. " << endl << endl;
      }

   //Create BaconNumber object and process input file
   BaconNumber baconNumber;
   baconNumber.processFile(argv[1]);

   baconNumber.display();  //printout the output

   }

}