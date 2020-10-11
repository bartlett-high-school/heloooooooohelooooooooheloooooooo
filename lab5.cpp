//c files lab
//COSC130
//MUD game
//Jay Ashworth
//used ideas from TA chris
//9/18/2020

#include <string>
#include <iostream>
#include <cstdio>
using namespace std;



class Room {   
private:    
string description;
int north,east,south,west;    
public: 
Room();
Room(string desc, int northr, int eastr, int southr, int westr);
string getDescription();
int getDirection(int direction);

};

class Game {
private:
    int numRooms;
    Room *arrayRoom;
public:
    int findRoomCount(const char * filename);
    void makeRoomArray(int numberOfRooms, const char * filename);
    void print(int roomNum);
    void deleteArray();
    int move(int initialPos, char direction);
};


int main(int argc, char *argv[]) {
    Game main;
    int numRooms;
    int pos = 0;
    int newPos = 0;
    char choice,eoftest,filter;

    //initial setup and error checking
    numRooms = main.findRoomCount(argv[1]);  
    if (numRooms == -1) {
        printf("Invalid File\n");
        return 1;
    } 
    else if (numRooms == 0) {
        printf("File Contains No Rooms\n");
        return 2;
    }
    main.makeRoomArray(numRooms, argv[1]);
    //main loop
    main.print(pos);
    while ((eoftest = scanf("%c", &choice)) == 1) {
        scanf("%c", &filter);
        if (choice == 'q') {
            break;
        }
        if (choice == 'n' || choice == 'e' || choice == 's' || choice == 'w') {
            newPos = main.move(pos,choice);
        }
        else {
            printf("That is not a valid direction.\n");
        }
        if (newPos != pos) {
            pos = newPos;
            main.print(pos);
        }

    }
    
    return 0;
    
}

//function takes a file name, opens it, scans through it, and returns the number of '~' that it found (divided by 3) to tell how many rooms there are in the file
int Game::findRoomCount (const char * filename) {
    int roomsAmt = 0;
    FILE * pFile;
    char readChar;
    pFile = fopen (filename,"r");
    if (pFile!=NULL)
    {
        do {
            readChar = fgetc(pFile);
            if (readChar == '~') {
                roomsAmt++;
            }
        }while (readChar != EOF);
    }
    else {
        return -1;
    }
    fclose(pFile);
    return (roomsAmt / 3);
}

//creates an array of Rooms for how many rooms were found in findRoomCount. Then it scans the file, extracting the description and direction options from each room
void Game::makeRoomArray(int numberOfRooms, const char * filename) {
    arrayRoom = new Room[numberOfRooms];
    string read,intString;
    FILE * pFile;
    char readChar,direction;
    int north = -1;
    int east = -1;
    int south = -1;
    int west = -1;
    int temp;
    pFile = fopen (filename,"r");

    for (int i=0;i<numberOfRooms;i++) {
        //gets rid of the "Room #x" because I don't need to store it.
        do {
            readChar = fgetc(pFile);
        }while(readChar!='~');
        //extracting the description
        while (true){
            readChar = fgetc(pFile);
            if (readChar != '~'){
            read += readChar;
            }
            else {
                break;
            }
        }
        //extracting the directional options
        while (true){
            readChar = fgetc(pFile);
            if (readChar == 'n' || readChar == 'e' || readChar == 's' || readChar == 'w') {
                direction = readChar;
                readChar = fgetc(pFile);
                while(true) {
                    if (readChar == '\n') {
                        break;
                    }
                    else {
                        readChar = fgetc(pFile);
                        intString += readChar;
                    }
                    
                }
                
                temp = atoi(intString.c_str());
                
                intString = "";
                if (direction == 'n') {
                    north = temp; 
                }
                if (direction == 'e') {
                    east = temp; 
                }
                if (direction == 's') {
                    south = temp; 
                }
                if (direction == 'w') {
                    west = temp;
                }
                direction = 0;
            }
            
            if (readChar == '~') {
                break;
            }
        }
        //setting the Room to have the extracted values.
        arrayRoom[i] = Room(read,north,east,south,west);
        read = "";
        north = -1;
        south = -1;
        east = -1;
        west = -1;
    }   

    fclose(pFile);
}

//prints the user interface on a per-room basis (i.e Room #1 \n\n desc \n\n options)
void Game::print(int roomNum) {
        printf( "Room #" );
        printf("%i",roomNum);
        printf("\n");
        printf("%s",arrayRoom[roomNum].getDescription().c_str());
        printf("\nExits:");
        if(arrayRoom[roomNum].getDirection(1) != -1)
        printf(" n") ;
        if(arrayRoom[roomNum].getDirection(2) != -1)
        printf(" e") ; 
        if(arrayRoom[roomNum].getDirection(3) != -1)
        printf(" s") ; 
        if(arrayRoom[roomNum].getDirection(4) != -1)
        printf(" w") ;
        printf("\n");
}

//handles the movement of the player and says which direction they moved in
int Game::move(int initialPos, char direction) {
    if(direction == 'n') {
        if(arrayRoom[initialPos].getDirection(1) == -1) {
            printf("You can't go NORTH\n");
            return initialPos;
        }
        else {
            printf("You moved NORTH\n");
            return arrayRoom[initialPos].getDirection(1);
        }
    }
    if(direction == 'e') {
        if(arrayRoom[initialPos].getDirection(2) == -1) {
            printf("You can't go EAST\n");
            return initialPos;
        }
        else {
            printf("You moved EAST\n");
            return arrayRoom[initialPos].getDirection(2);
        }
    }
    if(direction == 's') {
        if(arrayRoom[initialPos].getDirection(3) == -1) {
            printf("You can't go SOUTH\n");
            return initialPos;
        }
        else {
            printf("You moved SOUTH\n");
            return arrayRoom[initialPos].getDirection(3);
        }
    }
    if(direction == 'w') {
        if(arrayRoom[initialPos].getDirection(4) == -1) {
            printf("You can't go WEST\n");
            return initialPos;
        }
        else {
            printf("You moved WEST\n");
            return arrayRoom[initialPos].getDirection(4);
        }
    }
    else {
        return 0;
    }
}



//returns the description for a given room
string Room::getDescription() {
    return description;
}

//returns the 4 directional options for a given room
int Room::getDirection(int direction) {
    if (direction == 1) {
        return north;
    }
    if (direction == 2) {
        return east;
    }
    if (direction == 3) {
        return south;
    }
    else {
        return west;
    }
}

Room::Room(){}

//constructor that is used to set values of the Room array that was created in makeRoomArray
Room::Room(string desc, int northr, int eastr, int southr, int westr) {
    description = desc;
    north = northr;
    east = eastr;
    south = southr;
    west = westr;
}


