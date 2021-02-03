#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<fstream>
#include <cstdlib>
#include <string>
using namespace std;
 class organism {
 private:
     int xLocation, yLocation; bool alive;
 public:
     organism(int xLoc, int yLoc){
         xLocation=xLoc;
         yLocation=yLoc;
         alive=true;
     }
     organism(int xLoc, int yLoc, bool living){
         xLocation=xLoc;
         yLocation=yLoc;
         alive=living;
     }
     organism(){
         xLocation=0;yLocation=0;
         alive=true;
     }

     bool getAlive(){return alive;}
     void changeAlive(bool living){alive=living;}
     int getVectorLocation(){
         int vectorLocation=0;
         vectorLocation+=(yLocation-1)*20;
         vectorLocation+=xLocation;
         vectorLocation-=1;
         return vectorLocation;
     }
     ~organism(){}
     virtual int getLastBred(){cout<<"Calling last bred org version error"; return 0;};
     virtual int getLastEaten(){cout<<"Calling last Eaten Org version error"; return 0;};
     virtual bool getMovedThisTurn(){cout<<"why are you calling this";return true;};
     virtual void changeMovedThisTurn(bool moved){cout<<"why are you calling this"; };
     virtual void changeLastBred(int toChange){cout<<"Changing an org last bred";};
     virtual void changeLastEaten(int toChange){"Changing an org last eaten";};
     virtual void starve(vector<organism*>& grid){cout<<"starving an org";};

     virtual char getIdentifier(){return '-';};

     virtual void breed(vector<organism*>& grid){};

     virtual void move(vector<organism*>& grid){};

     int getXLocation() const {
         return xLocation;
     }

     int getYLocation() const{
         return yLocation;
     }

     void changeXLocation(int changeBy) {
             xLocation += changeBy;
         if (xLocation>20||xLocation<1)
             cout << "error";
     }

     void changeYLocation(int changeBy) {
             yLocation += changeBy;
         if (yLocation>20||yLocation<1)
             cout << "error";


     }
 };
class doodlebug : public organism{
private: int lastBredDoodlebug,lastEatenDoodlebug;char identifier; bool movedThisTurn;
public:
    doodlebug() {
        lastBredDoodlebug = 0;
        lastEatenDoodlebug =0;
        identifier='X';
        movedThisTurn=false;
    }
    doodlebug(int lastBred){
        lastBredDoodlebug=lastBred;
        identifier='X';
        movedThisTurn=false;
    }
    doodlebug(int xLoc, int yLoc, int lastBred, int lastEaten):organism( xLoc, yLoc){
        lastBredDoodlebug=lastBred;
        lastEatenDoodlebug=lastEaten;
        identifier='X';
        movedThisTurn=false;
    }
    virtual char getIdentifier(){return identifier;}
    virtual bool getMovedThisTurn(){return movedThisTurn;}
    virtual void changeMovedThisTurn(bool moved){movedThisTurn=moved;}
    ~doodlebug(){}
    int getLastBred(){return lastBredDoodlebug;}
    int getLastEaten(){return lastEatenDoodlebug;}
    void changeLastBred(int toChange){lastBredDoodlebug+=toChange;}
    void changeLastEaten(int toChange){lastEatenDoodlebug+=toChange;}
    void starve(vector<organism*>& grid);
    void breed(vector<organism*>& grid);
    void move(vector<organism*>& grid);
};
 class ant : public organism{
 private: int lastBredAnt;char identifier;bool movedThisTurn;
 public:
     ant(){
         lastBredAnt=0;
         identifier='o';
         movedThisTurn=false;

     }
     ant(int lastBred){
         lastBredAnt=lastBred;
         identifier='o';
         movedThisTurn=false;

     }
     ant(int xLoc, int yLoc, int lastBred):organism( xLoc, yLoc){
         lastBredAnt=lastBred;
         identifier='o';
         movedThisTurn=false;
     }
     ~ant(){};
     virtual bool getMovedThisTurn(){return movedThisTurn;}
     virtual void changeMovedThisTurn(bool moved){movedThisTurn=moved;};
    void breed(vector<organism*>& grid);
    virtual char getIdentifier(){return identifier;}
    void move(vector<organism*>& grid);
    int getLastBred(){return lastBredAnt;}
    void changeLastBred(int toChange){lastBredAnt+=toChange;}
 };

 void ant:: breed(vector<organism*>& grid){
     bool validMove=false;
     bool north=false , south=false , west=false , east =false;
     while ((validMove==false)&&(north==false||east==false||south==false||west==false)){
         int randMove = (rand() % 4)+1;
     if (randMove==1) {
         if (getYLocation() > 1) {//is this valid
             if (grid[getVectorLocation() - 20]->getAlive() == false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()-20];
                 grid[getVectorLocation()-20]= new ant(getXLocation(),getYLocation()-1,0);
                 validMove=true;
             }

         }
         north=true;
     }
     else if (randMove==2) {
         if (getXLocation() < 20) {//is this valid
             if (grid[getVectorLocation() + 1]->getAlive() == false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()+1];
                 grid[getVectorLocation()+1]= new ant(getXLocation()+1,getYLocation(),0);
                 validMove=true;
             }

         }
         east=true;
     }
     else if (randMove==3){
         if (getYLocation()<20){//is this valid
             if (grid[getVectorLocation()+20]->getAlive()==false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()+20];
                 grid[getVectorLocation()+20]= new ant(getXLocation(),getYLocation()+1,0);
                 validMove=true;
             }

         }
         south=true;

     }
     else if (randMove==4) {
         if (getXLocation() > 1) {//is this valid
             if (grid[getVectorLocation() - 1]->getAlive() == false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()-1];
                 grid[getVectorLocation()-1]= new ant(getXLocation()-1,getYLocation(),0);
                 validMove=true;
             }

         }
         west=true;
     }
     }
 }
 void doodlebug:: breed(vector<organism*>& grid){
     bool validMove=false;
     bool north=false , south=false , west=false , east =false;
     while ((validMove==false)&&(north==false||east==false||south==false||west==false)){
         int randMove = (rand() % 4)+1;
         if (randMove==1) {
             if (getYLocation() > 1) {//is this valid
                 if (grid[getVectorLocation() - 20]->getAlive() == false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()-20];
                     grid[getVectorLocation()-20]= new doodlebug(getXLocation(),getYLocation()-1,0,0);
                     validMove=true;
                 }

             }
             north=true;
         }
         else if (randMove==2) {
             if (getXLocation() < 20) {//is this valid
                 if (grid[getVectorLocation() + 1]->getAlive() == false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()+1];
                     grid[getVectorLocation()+1]= new doodlebug(getXLocation()+1,getYLocation(),0,0);
                     validMove=true;
                 }

             }east=true;
         }
         else if (randMove==3){
             if (getYLocation()<20){//is this valid
                 if (grid[getVectorLocation()+20]->getAlive()==false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()+20];
                     grid[getVectorLocation()+20]= new doodlebug(getXLocation(),getYLocation()+1,0,0);
                     validMove=true;
                 }

             }south=true;

         }
         else if (randMove==4) {
             if (getXLocation() > 1) {//is this valid
                 if (grid[getVectorLocation() - 1]->getAlive() == false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()-1];
                     grid[getVectorLocation()-1]= new doodlebug(getXLocation()-1,getYLocation(),0,0);
                     validMove=true;
                 }

             }west=true;
         }
     }
 }

 void doodlebug:: starve(vector<organism*>& grid){
     int temp;
     temp= getVectorLocation();
     delete grid[temp];
     grid[temp]= new organism(0,0,false);

 }
 void doodlebug:: move(vector<organism*>& grid) {
     int originalLocation=getVectorLocation();
     int randMove = (rand() % 4)+1;
     changeMovedThisTurn(true);
     if (randMove==1) {
         if (getYLocation() > 1) {//is this valid
             if (grid[getVectorLocation() - 20]->getAlive() == false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()-20];
                 changeYLocation(-1);//move up one row.
                 grid[getVectorLocation()] = this; //set that location to this instance
                 grid[originalLocation] = new organism(0, 0, false);

             }
             else if (grid[getVectorLocation() - 20]->getIdentifier() == 'o'){//its an ant, eat it
                 changeLastEaten(-getLastEaten()); //reset eat to 0
                 delete grid[getVectorLocation()-20];
                 changeYLocation(-1);//move up one row.
                 grid[getVectorLocation()] = this; //set that location to this instance
               //  delete grid[originalLocation];
                 grid[originalLocation] = new organism(0, 0, false); //clear original location
             }

         }
     }
     else if (randMove==2) {
         if (getXLocation() < 20) {//is this valid
             if (grid[getVectorLocation() + 1]->getAlive() == false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()+1];
                 changeXLocation(1);//move right one.
                 grid[getVectorLocation()] = this; //set that location to this instance
                 grid[originalLocation] = new organism(0, 0, false);

             }
             else if (grid[getVectorLocation() + 1]->getIdentifier() == 'o') {//its an ant, eat it
                 changeLastEaten(-getLastEaten()); //reset eat to 0
                 delete grid[getVectorLocation()+1];
                 changeXLocation(1);//move right one
                 grid[getVectorLocation()] = this; //set that location to this instance
                 //delete grid[originalLocation];
                 grid[originalLocation] = new organism(0, 0, false); //clear original location
             }
         }
     }
     else if (randMove==3){
         if (getYLocation()<20){//is this valid
             if (grid[getVectorLocation()+20]->getAlive()==false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()+20];
                 changeYLocation(1);//move down one row.
                 grid[getVectorLocation()]=this; //set that location to this instance
                 grid[originalLocation]=new organism(0,0,false);
             }
             else if (grid[getVectorLocation() + 20]->getIdentifier() == 'o') {//its an ant, eat it
                 changeLastEaten(-getLastEaten()); //reset eat to 0
                 delete grid[getVectorLocation()+20];
                 changeYLocation(1);//move down one
                 grid[getVectorLocation()] =this; //set that location to this instance
                 //delete grid[originalLocation];
                 grid[originalLocation] = new organism(0, 0, false); //clear original location
             }

         }

     }
     else if (randMove==4){
         if (getXLocation()>1){//is this valid
             if (grid[getVectorLocation()-1]->getAlive()==false) //delineating that the space is empty
             {
                 delete grid[getVectorLocation()-1];
                 changeXLocation(-1);//move left one.
                 grid[getVectorLocation()]=this; //set that location to this instance
                 grid[originalLocation]=new organism(0,0,false);
             }
             else if (grid[getVectorLocation() -1]->getIdentifier() == 'o') {//its an ant, eat it
                 changeLastEaten(-getLastEaten()); //reset eat to 0
                 delete grid[getVectorLocation()-1];
                 changeXLocation(-1);//move left one
                 grid[getVectorLocation()] = this; //set that location to this instance
                // delete grid[originalLocation]; //clear original location
                 grid[originalLocation]=new organism(0,0,false);
             }
         }

     }
 }
 void ant::move(vector<organism*>& grid){
        changeMovedThisTurn(true);
        int originalLocation=getVectorLocation();
         int randMove = (rand() % 4)+1;
         if (randMove==1) {
             if (getYLocation() > 1) {//is this valid
                 if (grid[getVectorLocation() - 20]->getAlive() == false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()-20];
                     changeYLocation(-1);//move up one row.
                     grid[getVectorLocation()] = this; //set that location to this instance
                     grid[originalLocation] = new organism(0, 0, false);

                 }

             }
         }
         else if (randMove==2) {
             if (getXLocation() < 20) {//is this valid
                 if (grid[getVectorLocation() + 1]->getAlive() == false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()+1];
                     changeXLocation(1);//move right one.
                     grid[getVectorLocation()] = this; //set that location to this instance
                     grid[originalLocation] =new organism(0, 0, false);

                 }

             }
         }
         else if (randMove==3){
             if (getYLocation()<20){//is this valid
                 if (grid[getVectorLocation()+20]->getAlive()==false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()+20];
                     changeYLocation(1);//move down one row.
                     grid[getVectorLocation()]=this; //set that location to this instance
                     grid[originalLocation]=new organism(0,0,false);
                 }

             }

         }
         else if (randMove==4){
             if (getXLocation()>1){//is this valid
                 if (grid[getVectorLocation()-1]->getAlive()==false) //delineating that the space is empty
                 {
                     delete grid[getVectorLocation()-1];
                     changeXLocation(-1);//move left one.
                     grid[getVectorLocation()]=this; //set that location to this instance
                     grid[originalLocation]=new organism(0,0,false);
                 }

             }

         }
     }
 void printGrid(vector<organism*>& grid, int breakAfter);
void printGrid(vector<organism*>& grid, int breakAfter){
    for (int i=0;i<grid.size();i++) {
            cout << grid[i]->getIdentifier();
        if ((i+1)%breakAfter==0)
            cout<<endl;
    }
}
void deleteGrid(vector<organism*>& grid);
void deleteGrid(vector<organism*>& grid){
    for (int i=0;i<grid.size();i++)
        delete grid[i];
}
void doodlebugMove(vector<organism*>&grid);
void doodlebugMove(vector<organism*>&grid){
    for(int i=0;i<grid.size();i++){
        if (grid[i]->getIdentifier()=='X')
            grid[i]->changeMovedThisTurn(false);
    }
    for(int i=0;i<grid.size();i++){
    if ((grid[i]->getIdentifier()=='X')&&(grid[i]->getMovedThisTurn()==false)) {//it is a doodlebug hasn't moved
            grid[i]->changeLastEaten(1);
            grid[i]->move(grid);
        }
    }
}
void doodlebugKill(vector<organism*>&grid);
void doodlebugKill(vector<organism*>&grid) {
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i]->getIdentifier() == 'X') {//it is a doodlebug
            if (grid[i]->getLastEaten() == 3)
                grid[i]->starve(grid);
        }
    }
}
void antMove(vector<organism*>&grid);
void antMove(vector<organism*>&grid) {
    for (int i = 0; i < grid.size(); i++) { //reset all to not moved
        if (grid[i]->getIdentifier() == 'o')
            grid[i]->changeMovedThisTurn(false);
        for (int i = 0; i < grid.size(); i++) {
            if (grid[i]->getIdentifier() == 'o' && grid[i]->getMovedThisTurn() == false) {//it is a ant and hasnt mvoed
                grid[i]->move(grid);
            }
        }
    }
}
void antBreed(vector<organism*>&grid);
void antBreed(vector<organism*>&grid){
    for(int x=0;x<grid.size();x++){ //now ant breed
        if (grid[x]->getIdentifier()=='o') { //is it ant
            grid[x]->changeLastBred(+1); //its survived a time step! yay!
            if (grid[x]->getLastBred() == 3) { //test if it should breed
                grid[x]->breed(grid);
                grid[x]->changeLastBred(-3); //it has bred reset
            }

        }
    }
}
void doodlebugBreed(vector<organism*>&grid);
void doodlebugBreed(vector<organism*>&grid) {
    for (int x = 0; x < grid.size(); x++) { //now doodle bug breed
        if (grid[x]->getIdentifier() == 'X') { //is it doodlebug
            grid[x]->changeLastBred(+1);
            if (grid[x]->getLastBred() == 8) { //test if it should breed
                grid[x]->breed(grid);
                grid[x]->changeLastBred(-8); //it has bred reset
            }
        }
    }
}
void insertAnimals(vector <organism*>& grid, int numAntWanted, int numDoodleWanted);
void insertAnimals(vector <organism*>& grid, int numAntWanted, int numDoodleWanted){
    int randomGrid1, randomGrid2;
    for (int i=0;i<numDoodleWanted;i++) {
        bool pickedEmpty=false;
        while (pickedEmpty == false) {
            randomGrid1=rand();
            randomGrid2= randomGrid1 % 400; //for some reason this wasn't working stored in one variable.
            if (grid[randomGrid2]->getAlive() == false){
                delete grid[randomGrid2];
                grid[randomGrid2]=new doodlebug ((randomGrid2 % 20) + 1, (randomGrid2 / 20) + 1, 0, 0);
                pickedEmpty=true;
            }
        }
    }
    for (int i=0;i<numAntWanted;i++) {
        bool pickedEmpty=false;
        while (pickedEmpty == false) {
            randomGrid1=rand();
            randomGrid2= randomGrid1 % 400; //for some reason this wasn't working stored in one variable.
            if (grid[randomGrid2]->getAlive()==false){
                delete grid[randomGrid2];
                grid[randomGrid2]=new ant (randomGrid2%20+1,(randomGrid2/20)+1,0);
                pickedEmpty=true;
            }
        }
    }
}
int main() {
    srand(time(NULL));
    ofstream myFile("predprey.csv");
    vector <organism*> grid;
    grid.resize(400);
    for (int i=0;i<grid.size();i++){ //fills grid with "empties"
        grid[i]=new organism(0,0,false);
    }
    insertAnimals(grid,100,5);
    cout<<"The original state:"<<endl;
    printGrid(grid, 20);
    cout<<endl;
int i=1;
myFile<<"Number of Predators Alive"<<","<<"Number of Prey Alive"<<endl;
int numberOfPred, numberOfPrey;
char test='x';
bool userInput=true;
   while (userInput==true){
        numberOfPred=0; //counters for output to file to track fluctuations.
        numberOfPrey=0;
        cout<<"After time "<<i<<endl;
        doodlebugMove(grid);
        doodlebugBreed(grid);
        doodlebugKill(grid);
        antMove(grid);
        antBreed(grid);
        printGrid(grid,20);
        i++;
        cout<<"Please press enter to see the next stage or 0 to break"<<endl;
        cin.get(test);
        if (test=='0')
            userInput=false;

       for (int i=0;i<grid.size();i++){ //counting pred and prey to output
           if (grid[i]->getIdentifier()=='X')
               numberOfPred++;
           if (grid[i]->getIdentifier()=='o')
               numberOfPrey++;
       }
       myFile<<numberOfPred<<","<<numberOfPrey<<","<<endl;
    }
   myFile.close();

    deleteGrid(grid);
    return 0;
}
//if time allows: reorient 20X20 board size to a const to allow changing
// run out further simulation and graph in excel to ensure behavior continues properly
