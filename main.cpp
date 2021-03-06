#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int viaCount;
int **board;
int boardW;
int boardH;
vector <int> OBSx;
vector <int> OBSy;
struct net{
    string netLine;
    string name;
    vector<int> metal;
    vector<int> pinX;
    vector<int> pinY;
};
vector<net> nets;


net setupNet(net currNet){
    stringstream netLineSS;
    netLineSS << currNet.netLine;
    int i = 0;
    string temp;
    
    while(netLineSS >> temp){
        if(i != 0){
            string pin;
            string pinMetal;
            string pinX;
            string pinY;

            pin = temp;

            pin = pin.substr(1, pin.find(')') - 1);
            pinMetal = pin.substr(0, pin.find(','));

            pin = pin.substr(pin.find(',') + 1);
            pinX = pin.substr(0, pin.find(','));

            pinY = pin.substr(pin.find(',') + 1);

            currNet.metal.push_back(stoi(pinMetal));
            currNet.pinX.push_back(stoi(pinX));
            currNet.pinY.push_back(stoi(pinY));
        }

        else
            currNet.name = temp;
        i++;
    }
    
    return currNet;
}

void readInput(string file){
    fstream testFile;
    testFile.open("Tests/"+file);
    if (testFile.is_open()){   //checking whether the file is open
        cout << "open" << endl;
        string tp;
        while(getline(testFile, tp)){
            stringstream line;
            line << tp;
            string firstWord;
            line >> firstWord;
            if(firstWord.find("net") != string::npos){
                net currNet;
                currNet.netLine = tp;
                currNet = setupNet(currNet);
                nets.push_back(currNet);
            }
            else if(firstWord.find("OBS") != string::npos){
                string OBSph, OBSxs, OBSys;
                stringstream obs;
                obs << tp;
                obs >> OBSph >> OBSxs >> OBSys;
                OBSy.push_back(stoi(OBSys));
                OBSx.push_back(stoi(OBSxs));
            }
            else if ((firstWord.find("1") != string::npos) || (firstWord.find("2") != string::npos)){
                
            }
            else{
                string w, h;
                int i = 0;
                while(tp[i] != 'x'){
                    w = w + tp[i];
                    i++;
                }
                tp = tp.substr(i + 1);
                h = tp;
                boardW = stoi(w);
                boardH = stoi(h);
            }
        }
        testFile.close();
   }


}

void initBoard(string fileName){
    readInput(fileName);
    
    //Iniitialize empty board as 2d array
    board = new int*[boardH];
    for(int i = 0; i < boardH; i++){
        board[i] = new int[boardW];
    }
    
    for(int i = 0; i < boardH; i++){
        for(int j = 0; j < boardW; j++){
            board[i][j] = 0;
        }
    }
    
    for(int i = 0; i < OBSx.size(); i++){
        board[OBSy[i] - 1][OBSx[i] - 1] = -1;
    }
    
    for(int i = 0; i < nets.size(); i++){
        for(int j = 0; j < nets[i].metal.size(); j++){
            board[nets[i].pinY[j] - 1][nets[i].pinX[j] - 1] = i + 1;
        }
    }
    
    for(int i = 0; i < boardH; i++){
        for(int j = 0; j < boardW; j++){
            cout << board[i][j] << "   ";
        }
        cout << endl;
    }
    
}

int main(){
    initBoard("test1.txt");
    return 0;
}
