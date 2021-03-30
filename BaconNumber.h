/*Poppy La
File name: BaconNumber.h
Instructor: Dr.Stiber
Date: 02/05/2021
Course: CSS343
Program 2: The BaconNumber class
      This class takes a database file name and extracts all the actor and their movies as the
      program's data then store them into a map with each movie as keys and vector of actors in 
      that same movie as value. A graph with an adjacency list will be create useing the map data.
      The class process the file, build the graph and prin out actors with their bacon number.
*/

#pragma once
#include "Graph.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class BaconNumber
{
   public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default contructor
   BaconNumber();

   //destructor
   ~BaconNumber();

//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	//takes database file in parameter and extract the names and movie information, create a
   //map with each movie as keys and vector of actors in that same movie as value, use the 
   //map to determine links between actors, pass the links into graph to create adjacency list
   //and count bacon number.
	//pre-condition: database file name is valid
	//post-condition: create a Graph that has a adjacency list and a vector that stores all bacon number.
	//function called: BaconNumber::cleanMovie(string), BaconNumber::createGraph()
	//return: true if database file is found and Graph is created with all bacon numbers counted
   bool processFile(string);

   //display the actor names with their bacon number of the database file
	//pre-condition: database file is valid, Graph with bacon number is counted
	//post-condition: printout all the actor with their bacon numbers
	//function called: Graph::display()
   bool display() const;
   
   protected:
   //extract the extra other-info from the movie data, only movie names and years remained
   //pre-condition: the movie passed in paramter valid
   //post-condition: the movie only contain name and year
   string cleanMovie(string);

   //create graph that stores all the actors name with their bacon numbers in a adjacency list
   //pre-condition: the mmap_ is valid
   //post-condition: the graph is created with adjacency list of actors and their bacon number calculated
   //function called: Graph::setNames(vector<string>), Graph::linkNames(vector<string>), 
   //                Graph::findBaconNumber()
   //return: true if the graph is created
   bool createGraph();

   private:
//--------------------------------------------------------------
//                          VARIABLES
//--------------------------------------------------------------
   vector<string> name_;      //stores all actor's names
   map<string, vector<string>> mmap_;     //stores all the movies as keys with each key's value is a
                                          //vector of actors that in that same movie
   Graph baconGraph_;          //Graph of all actors and their bacon numbers
};