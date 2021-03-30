/*Poppy La
File name: BaconNumber.cpp
Instructor: Dr.Stiber
Date: 02/05/2021
Course: CSS343
Program 2: The BaconNumber class
      This class takes a database file name and extracts all the actor and their movies as the
      program's data then store them into a map with each movie as keys and vector of actors in 
      that same movie as value. A graph with an adjacency list will be create useing the map data.
      The class process the file, build the graph and prin out actors with their bacon number.
*/

#include "BaconNumber.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// default constructor
BaconNumber::BaconNumber()
{}


//destructor
BaconNumber::~BaconNumber()
{}


//takes database file in parameter and extract the names and movie information, create a
//map with each movie as keys and vector of actors in that same movie as value, use the 
//map to determine links between actors, pass the links into graph to create adjacency list
//and count bacon number.
//pre-condition: database file name is valid
//post-condition: create a Graph that has a adjacency list and a vector that stores all bacon number.
//function called: BaconNumber::cleanMovie(string), BaconNumber::createGraph()
//return: true if database file is found and Graph is created with all bacon numbers counted
bool BaconNumber::processFile(string filename)
{
   ifstream bacon;
   bacon.open(filename);

   //notice that corpus file is not exist and stop processing
   if(!bacon.is_open()) {
      cout << " File can not be opened or file does not exist." << endl;
      return false;
   }

   string line, data, name, movie;  
   
   //go through each line of the database file and process
   while (getline(bacon, line)) {
      stringstream copyLine(line);
      bool nameExtracted = false;      //if the line has "name" data, check if the name is
                                       //already extracted

      //separate information in the line with tabs and store them as unidentify data string
      while (getline(copyLine, data, '\t')) {
         
         //processing name information of the line if it exist
         if (line[0] != '\t' && !nameExtracted) {
            //set unidentify data as name
            name = data;
            name_.push_back(name);     //push new name into the name_ vector
            nameExtracted = true;      //marked that name is extracted

         //process movie information
         } else if (data != "\0") {        
            movie = cleanMovie(data);  //remove all other-info in data and set it to movie
            mmap_[movie].push_back(name);    //add the pair of movie and name to the map
         }
      }
   }

   //build the graph
   createGraph();
   return true;
}


//extract the extra other-info from the movie data, only movie names and years remained
//pre-condition: the movie passed in paramter valid
//post-condition: the movie only contain name and year
string BaconNumber::cleanMovie(string movie)
{
   istringstream ss(movie);
   string word, result;

   //read each word from string
   while(ss >> word) {

      //escape the loop if the word starts with {} [] <> and ()
      if (word[0] == '{' || word[0] == '[' || word[0] == '<' || word[0] == '(') {

         //add the word to result string if it start with (), then escape
         if (word[0] == '('){
            result += word + " ";
         } 
         break;

      //add the word to result string
      } else {
         result += word + " ";
      }
   }
   return result;
}


//create graph that stores all the actors name with their bacon numbers in a adjacency list
//pre-condition: the mmap_ is valid
//post-condition: the graph is created with adjacency list of actors and their bacon number calculated
//function called: Graph::setNames(vector<string>), Graph::linkNames(vector<string>), Graph::findBaconNumber()
//return: true if the graph is created
bool BaconNumber::createGraph()
{  
   //copy the name_ vector to graph
   baconGraph_.copyNames(name_);

   //take the value vector of each movie and pass to graph to create adjacency list
   for(map<string, vector<string> >::const_iterator itr = mmap_.begin(); itr != mmap_.end(); ++itr) {
      vector<string> names = itr->second;
      baconGraph_.linkNames(names);
   }

   //calculate bacon number
   baconGraph_.findBaconNumber();
   return true;
}


//display the actor names with their bacon number of the database file
//pre-condition: database file is valid, Graph with bacon number is counted
//post-condition: printout all the actor with their bacon numbers
//function called: Graph::display()
bool BaconNumber::display() const 
{
   //print out actors and bacon numbers
   baconGraph_.display();
   return true;
}

