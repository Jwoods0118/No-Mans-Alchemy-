//Title Ship.cpp
//Author: Josh Woods
//Date: 3/11/21
//Description: Ship.cpp file holds all of the methods for running the ship aspect of the game
#ifndef SHIP_CPP
#define SHIP_CPP
#include "Material.h"
#include "Ship.h"
#include "Game.h"

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

Ship::Ship() {
    SetName("");
    m_shipRank = 'D';
    m_numMaterials = 0;
}

Ship::Ship(string name){
    SetName(name);
    m_shipRank = 'D';
    m_numMaterials = 0;
}

string Ship::GetName(){
    return m_shipName;
}

void Ship::SetName(string name){
    cout << "What is the name of your ship?" << endl;
    getline(cin, name);
    cout << "\n" << endl;
    m_shipName = name;
}

int Ship::CheckMaterial(Material newMaterial){
    //iterate through ship array and return index of material
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (m_myMaterials[i].m_name == newMaterial.m_name){
            return i;
        }
    }
    return -1;
}

void Ship::AddMaterial(Material newMaterial){
    int index = CheckMaterial(newMaterial);

    //AddMaterial to ship array if not found (-1 index)
    if (index == -1){
        m_myMaterials[m_numMaterials] = newMaterial;
        m_numMaterials += 1;
    }
}

void Ship::IncrementQuantity(Material newMaterial){
    //Check index
    int index = CheckMaterial(newMaterial);

    //if found in array, increment the material
    if (index != -1) {
        m_myMaterials[index].m_quantity += 1;
    }

    //If not found, inform user
    else{
        cout << "You do not have any " << newMaterial.m_name << endl;
    }
}

bool Ship::DecrementQuantity(Material newMaterial){
    //Check index
    int index = CheckMaterial(newMaterial);

    //If found in the array
    if (index != -1) {
        //If quantity of material is not already 0, decrement by 1
        if (m_myMaterials[index].m_quantity != 0) {
            m_myMaterials[index].m_quantity -= 1;
            return true;
        }

	//if quanitity is 0, return false
        else{
            return false;
        }
    }
    //If material not in array, return false and inform user
    else{
        cout << "You do not have any " << newMaterial.m_name << endl;
        return false;
    }
}

bool Ship::CheckQuantity(Material material1, Material material2) {
    //Get index of both material1 and material2
    int indexOne = CheckMaterial(material1);
    int indexTwo = CheckMaterial(material2);

    //if array is empty, return false
    if (m_numMaterials == 0) {
        return false;

	//If either materials are empty, return false
    }   else if (indexOne == -1 || indexTwo == -1) {
        return false;
    }

    //If both materials are present in array
    else if (indexOne != -1 && indexTwo != -1) {
      
        //Check to see if material1 is material2
        if (m_myMaterials[indexOne].m_name == m_myMaterials[indexTwo].m_name) {

	    //If so, check to see if quantity is equal/greater than 2
            if (m_myMaterials[indexOne].m_quantity >= 2) {
                return true;}

	    
            else {
                return false;}

	    //if materials are different and quantity is greater than 1, return true
        }   else if (m_myMaterials[indexOne].m_quantity >= 1 && m_myMaterials[indexTwo].m_quantity >= 1) {
            return true;}
    }
    return false;
}




Material Ship::GetMaterial(int matNumber){
    return m_myMaterials[matNumber];
}

void Ship::IncRank(){
    //Increase rank system is called when a unique item is crafted
    if (m_shipRank == 'D'){
        m_shipName = 'C';
    }

    else if (m_shipRank == 'C'){
        m_shipName = 'B';
    }

    else if (m_shipRank == 'B'){
        m_shipName = 'A';
    }

    else if (m_shipRank == 'A'){
        m_shipName = 'S';
    }
}

char Ship::GetRank(){
    return m_shipRank;
}

#endif
