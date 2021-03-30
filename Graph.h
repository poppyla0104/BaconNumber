/*Poppy La
File name: Graph.h
Instructor: Dr.Stiber
Date: 02/05/2021
Course: CSS343
Program 2: The Graph class
      This class takes a many vectors of actor names to create adjacency list and calculate
      the actor's bacon numbers, each vector contains names of actors that perform in the same 
      specific movie. The bacon number represent the minimize number of links between each actor 
      and Kevin Bacon. The class will print out the list of actors and their bacon numbers.
*/

#pragma once
#include <string>
#include <vector>

using namespace std;

class Graph
{
   public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default contructor
   Graph();

   //destructor
   ~Graph();

//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	//takes a name vector from parameter and copy it into the object name_ vector
   //set size value for vertices_, resize baconNumber_ vector and adjList_ with the
   //name_ vector size
	//pre-condition: the name vector from parameter valid
	//post-condition: name_ vector stores all name of actors; vertices_, baconNumber_,
   //             adjList_ and name_ have the same size
	//return: true if all vector variable are resized and the data is copied into name_ vector
   bool copyNames(vector<string>& actorNames);

   //take a vector of actors that are in the same movie then link them together in the
   //adjacency list 
	//pre-condition: the actor vector from parameter valid
	//post-condition: all the actor in the same movie links together
   //function called: Graph::linkPair(string,string)
	//return: true if all the actor in the same movie link together
   bool linkNames(vector<string>&);
   
	//pre-condition: adjacency list is created
	//post-condition: all bacon number are calculated and stored in baconNumber_ vector
	//return: true if all the bacon number are calculated
   bool findBaconNumber();

   //pre-condition: the adjacency list valid and bacon numbers are calculated
	//post-condition: printout the actor names with their bacon numbers.
   void display() const;

   //pre-condition: the adjacency list valid
	//post-condition: printout the adjacency list with all actor names and indexes
   void printAdj() const;


//--------------------------------------------------------------
//                       OPERATORS OVERLOAD
//--------------------------------------------------------------
   //pre-condition: graph object valid
   //post-condition: printout all the actor names and bacon number.
   //function called: Graph::display()
   //return: out_stream
   friend ostream& operator<<(ostream& out_stream, const Graph&);

   protected:

   //take 2 actor names and link them together in adjacency list
	//pre-condition: 2 actors names are valid in the name_ vector
	//post-condition: 2 names are linked in adjacency list
   //function called: Graph::addEdge(int, int)
	//return: true if 2 names are linked
   bool linkPair(string, string);

   //take 2 actors indexes and link them together in adjacency list
	//pre-condition: 2 actors are valid
	//post-condition: 2 names are linked by their indexes in adjacency list
	//return: true if 2 actors indexes are linked
   bool addEdge(int, int);


   private:
//--------------------------------------------------------------
//                          VARIABLES
//--------------------------------------------------------------
   vector<string> name_;      //stores actor's name
   vector<int> baconNumber_;     //stores all actor's bacon number
   vector<vector<int>> adjList_;      //adjacency list
   int kevinIndex_;     //Kevin Bacon index         
   int vertices_;       //number of vertices   
   
};