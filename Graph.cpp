/*Poppy La
File name: Graph.cpp
Instructor: Dr.Stiber
Date: 02/05/2021
Course: CSS343
Program 2: The Graph class
      This class takes a many vectors of actor names to create adjacency list and calculate
      the actor's bacon number, each vector contain names of actors that perform in the same 
      specific movie. The bacon number represent the minimize number of links between each actor 
      and Kevin Bacon. The class will print out the list of actors and their bacon number.
*/

#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <list>

using namespace std;

//default contructor
Graph::Graph()
{
   kevinIndex_ = -1;
   vertices_ = 0;
}


//destructor
Graph::~Graph()
{}


//takes a name vector from parameter and copy it into the object name_ vector
//set size value for vertices_, resize baconNumber_ vector and adjList_ with the
//name_ vector size
//pre-condition: the name vector from parameter valid
//post-condition: name_ vector stores all name of actors; vertices_, baconNumber_,
//             adjList_ and name_ have the same size
//return: true if all variable are resized and the data is copied into name_ vector
bool Graph::copyNames(vector<string>& actorNames)
{
   name_ = actorNames;
   vertices_ = actorNames.size();
   baconNumber_.resize(actorNames.size());
   adjList_.resize(actorNames.size());
   return true;
}


//take a vector of actors that are in the same movie then link them together in the
//adjacency list 
//pre-condition: the actor vector from parameter valid
//post-condition: all the actor in the same movie links together
//function called: Graph::linkPair(string,string)
//return: true if all the actor in the same movie link together
bool Graph::linkNames(vector<string>& actorNames)
{
   //take each pair of every 2 actors and link them in adjList
   for(int i = 0; i < actorNames.size()-1; i++) {
      for(int j = i+1; j < actorNames.size(); j++) {

         linkPair(actorNames[i], actorNames[j]);
      }
   }
   return true;
}


//take 2 actor names and link them together in adjacency list
//pre-condition: 2 actors names are valid in the name_ vector
//post-condition: 2 names are linked in adjacency list
//function called: Graph::addEdge(int, int)
//return: true if 2 names are linked
bool Graph::linkPair(string name1, string name2)
{
   int index1, index2;

   //find indexes of the 2 actors
   for(int i = 0; i < name_.size(); i++) {

      //find Kevin Bacon and store his index in kevinIndex_
      if (name_[i] == "Bacon, Kevin (I)") {
         kevinIndex_ = i;
      }

      if (name_[i] == name1) {
         index1 = i;

      } else if (name_[i] == name2) {
         index2 = i;
      }
   }

   //add links for 2 indexes
   addEdge(index1, index2);
   return true;
}


//take 2 actors indexes and link them together in adjacency list
//pre-condition: 2 actors are valid
//post-condition: 2 names are linked by their indexes in adjacency list
//return: true if 2 actors indexes are linked
bool Graph::addEdge(int index1, int index2)
{
   //check if 2 indexes are already linked before to avoid duplicate
   if (find(adjList_[index1].begin(), adjList_[index1].end(), index2) != adjList_[index1].end()) {
      return false;
   }

   //add link between 2 indexes in adjacency list
   adjList_[index1].push_back(index2);
   adjList_[index2].push_back(index1);
   return true;
}


//pre-condition: adjacency list is created
//post-condition: all bacon number are calculated and stored in baconNumber_ vector
//return: true if all the bacon number are calculated
bool Graph::findBaconNumber()
{
   //kevin number can not be calculated if Kevin Bacon data not valid in file
   if (kevinIndex_ == -1) {
      cout << "Can't find Kevin Bacon (I) in the database." << endl;
      return false;
   }

   vector<bool> visited(vertices_);       //vector marked visited vertex
   list<int> queue;     //queue that stores indexes with BFS order

   for(int i = 0; i < vertices_; i++) {

      visited[i] = false;     //set all vertices to false and
      baconNumber_[i] = -1;   //all bacon number to -1
   }
   
   //process Kevin Bacon index first, mark true as it's visited
   visited[kevinIndex_] = true;
   baconNumber_[kevinIndex_] = 0;          
   queue.push_back(kevinIndex_);    //first vertex in queue
   
   while(!queue.empty()) {

      int current = queue.front();  //save first index in queue to current to process
      queue.pop_front();        //pop out the in process at first of queue
      
      for(int i = 0; i < adjList_[current].size(); i++) {

         //process unvisited vertex only
         if(visited[adjList_[current][i]] == false) {

            visited[adjList_[current][i]] = true;     //set visited vertex to true
            //bacon number of current vertex's predecessor is 1 element increased from current vertex
            baconNumber_[adjList_[current][i]] = baconNumber_[current] + 1;
            queue.push_back(adjList_[current][i]);    //push to queue to continue processing 
         }
      }
   }
   return true;
}


//pre-condition: the adjacency list valid
//post-condition: printout the adjacency list with all actor names and indexes
void Graph::display() const
{
   cout << "___________________________" << endl << endl; 
   cout << "Actor Name   Bacon Number" << endl;
   cout << "___________________________" << endl << endl; 

   for(int i = 0; i < baconNumber_.size(); i++) {

      //printout "infinity" instead of -1
      if (baconNumber_[i] == -1) {
         cout << name_[i] << "\t" << "infinity" << endl;

      } else {
         cout << name_[i] << "\t" << baconNumber_[i] << endl;
      }
   }
}


//pre-condition: the adjacency list valid
//post-condition: printout the adjacency list with all actor names and indexes
void Graph::printAdj() const
{
   for(int i = 0; i < adjList_.size(); i++) {
      cout << "[" << i << "] " << name_[i] << ":";

      for(int j = 0; j < adjList_[i].size(); j++) {
         cout << " -> [" << adjList_[i][j] << "] " << name_[adjList_[i][j]];
      }

      cout<< endl;
   }
}


//pre-condition: graph object valid
//post-condition: printout all the actor names and bacon number.
//function called: Graph::display()
//return: out_stream
ostream& operator<<(ostream& out_stream, const Graph& graph)
{
   graph.display();
   return out_stream;
}