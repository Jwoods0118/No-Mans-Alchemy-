//Title Game.cpp
//Author: Josh Woods
//Date: 3/11/21
//Description: Game.cpp holds all the methods for running the entirety of the game including
//loading materials, searching materials, and starting the game
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

Game::Game(){
    GameTitle();
    LoadMaterials();
    
}

void Game::LoadMaterials(){
    string name, type, material1, material2;
    const char DELIMITER = ',';
    int count = 0;
    ifstream infile(PROJ2_DATA);
    int quantity = 0;

    //Formatting
    cout << "\n" << endl;
    
    //load in game file to m_materials array
    if(infile.is_open()){
        while(count < PROJ2_SIZE){
            getline(infile, name, DELIMITER);
            getline(infile, type, DELIMITER);
            getline(infile, material1, DELIMITER);
            getline(infile, material2);
            m_materials[count] = Material(name, type, material1, material2, quantity);
            count++;
        }

	cout << "62 materials loaded." << endl;
	
    }else{
        cout << "ERROR OPENING FILE" << endl;
    }
    //Once m_materials is loaded, iterate through and copy the elements into the m_myShip Array
    for (int i = 0; i < PROJ2_SIZE; i++){
      m_myShip.AddMaterial(m_materials[i]);
    }
}


void Game::StartGame(){
    int choice = 0;

    //While choice != ("Quit") and Ship is not superior rank
    while (choice != 5 && m_myShip.GetRank() != 'S'){
        choice = MainMenu();
        m_myShip.GetRank();
    }

    cout << "Thank you for playing!" << endl;
}

int Game::MainMenu(){
    int choice = 0;

    //Main Menu that takes input 1-5
    cout << "What would you like to do? " << endl;
    cout << "1. Display your Ship's Materials" << endl;
    cout << "2. Search for Raw Mateirals" << endl;
    cout << "3. Attempt to merge Materials" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;
    cin >> choice;
    
    if (choice == 1){
        DisplayMaterials();
        return 1;
    }

    else if (choice == 2){
        SearchMaterials();
        return 2;
    }

    else if(choice == 3){
        CombineMaterials();
        return 3;
    }

    else if (choice == 4){
        CalcScore();
        return 4;
    }

    else if (choice == 5){
        return 5;
    }

    else{
        cout << "Invalid response" << endl;
        MainMenu();
        return 0;
    }
}

void Game::DisplayMaterials(){
    //Iterate through m_myShip's materials using GetMaterial to output the users materials
    //In a numbered list
    for (int i = 0; i < PROJ2_SIZE; i++){
        cout << i + 1 << ". " << m_myShip.GetMaterial(i).m_name << " "
             << m_myShip.GetMaterial(i).m_quantity << endl;
    }
}

void Game::SearchMaterials() {
    int MAX = 62;
    int randNum;
    int index;
    
    //Random number to find a random material in the array
    srand(time(NULL));
    randNum = rand() % MAX;

    //While the random material is type not "raw"
    //Keep searching until type raw
    while (m_materials[randNum].m_type != "raw") {
        while (m_materials[randNum].m_type != "raw") {
            randNum = rand() % MAX;
        }

	
	cout << m_materials[randNum].m_name << " Found!" << endl;


	//Add the material to the m_myShip Array
        index = m_myShip.CheckMaterial(m_materials[randNum]);
        if (index == -1) {
            m_myShip.AddMaterial(m_materials[randNum]);
        } else {
            m_myShip.IncrementQuantity(m_materials[randNum]);
        }
    }
}
void Game::CombineMaterials(){
    int choiceOne;
    int choiceTwo;
    int matOne;
    int matTwo;
    string matOneName;
    string matTwoName;
    int recipeIndex = 0;
    bool canCombine = false;

    //Get index of materials
    RequestMaterial(choiceOne);
    RequestMaterial(choiceTwo);

    //Set materials to index
    matOne = choiceOne;
    matTwo = choiceTwo;

    //Material Name
    matOneName = m_materials[choiceOne].m_name;
    matTwoName = m_materials[choiceTwo].m_name;

    //Check quantity of both items
    canCombine = m_myShip.CheckQuantity(m_materials[matOne], m_materials[matTwo]);

    //Find corresponding recipe
    recipeIndex = SearchRecipes(matOneName, matTwoName);

    if (recipeIndex == -1){
        recipeIndex = SearchRecipes(matTwoName, matOneName);
        
    }
    if (recipeIndex >= 0){
        //Check recipe in reverse
        canCombine = m_myShip.CheckQuantity(m_materials[matOne], m_materials[matTwo]);
      
        if (canCombine == true){
	  cout << "You have built " << m_materials[recipeIndex].m_name << endl;
            m_myShip.IncrementQuantity(m_materials[recipeIndex]);
            m_myShip.DecrementQuantity(m_materials[matOne]);
            m_myShip.DecrementQuantity(m_materials[matTwo]);
        }
    }

        else{
            cout << "Unable to combine items" << endl;
        }


    //check if unique, if so increase rank of ship
    if (m_materials[recipeIndex].m_type == "Unique"){
	m_myShip.IncRank();}
}

void Game::RequestMaterial(int &choice) {
    int escapeLoop = 0;
    int option = 0;

    //Keep asking the user a choice until two materials have been entered
    while (escapeLoop != 1){
        cout << "Which materials would you like to merge?" << endl;
        cout << "To list known materials enter -1" << endl;
        cin >> option;

	//iterate through the m_myShip array to display all materials
        if (option == -1){
            for (int i = 0; i < PROJ2_SIZE; i++){
                cout << i << ". " << m_myShip.GetMaterial(i).m_name << " "
                     << m_myShip.GetMaterial(i).m_quantity << endl;
            }
        }
	//Make choice of material equal to user input
        else if (option != -1 && 1 <= option <= 62){
            choice = option - 1;
            escapeLoop += 1;
        }
    }
}


int Game::SearchRecipes(string materialOne, string materialTwo){
  //Iterate through and try and find two matching materials
  //return index
  for (int i = 0; i < PROJ2_SIZE; i++){
        if (m_materials[i].m_material1 == materialOne && m_materials[i].m_material2 == materialTwo)
            return i;
    }
  //If not found, return -1
    return -1;
}

void Game::CalcScore(){
  string name = m_myShip.GetName();
  //Display Ship information
  cout << "***The Ship***" << endl;
  cout << "The Great Ship " << name << endl;
  cout << "Ship Rank: " << m_myShip.GetRank() << endl;
}

#endif
