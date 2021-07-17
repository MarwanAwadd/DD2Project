package com.company;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    static ArrayList<Integer> OBSx = new ArrayList<Integer>();
    static ArrayList<Integer> OBSy = new ArrayList<Integer>();
    static int boardH;
    static int boardW;
    static ArrayList<net> nets = new ArrayList<net>();
    static ArrayList<ArrayList<Integer>> board = new ArrayList<ArrayList<Integer>>();
    static int layers = 2;

    static void readInput(String file){
        try {
            File myObj = new File("Tests/"+file);
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                String temp = data;
                Scanner line = new Scanner(data);

                String firstWord = line.next();
                if(firstWord.contains("net")){
                    net currNet = new net();
                    currNet.netInit(temp);
                    nets.add(currNet);
                }
                else if(firstWord.contains("OBS")){
                    OBSx.add(Integer.parseInt(line.next()));
                    OBSy.add(Integer.parseInt(line.next()));
                }
                else if(firstWord == "1" || firstWord == "2"){
                    layers = Integer.parseInt(firstWord);
                }
                else{
                    String W = "", H = null;
                    int i = 0;
                    while(temp.charAt(i) != 'x'){
                        W = "" + W + temp.charAt(i);
                        i++;
                    }
                    temp = temp.substring(i + 1);
                    H = temp;
                    boardW = Integer.parseInt(W);
                    boardH = Integer.parseInt(H);
                }

            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    static void init(String file){
        readInput(file);
        for(int i = 0; i < boardH; i++){
            ArrayList<Integer> row = new ArrayList<Integer>();
            for(int j = 0; j < boardW; j++){
                row.add(0);
            }
            for(int o = 0; o < OBSx.size(); o++) {
                if (i == OBSy.get(o) - 1) {
                    row.set(OBSx.get(o) - 1, -1);
                }
            }
            board.add(row);
        }

        for(int i = 0; i < board.size(); i++){
            System.out.println(board.get(i));
        }

    }

    public static void main(String[] args) {
	init("test1.txt");


    }
}
