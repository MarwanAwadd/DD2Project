package com.company;
import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;
import java.util.Scanner;

class pin{
    int x;
    int y;
    int metal;
    int dist;

    public pin(int metal, int x, int y, int dist){
        this.x = x;
        this.y = y;
        this.metal = metal;
        this.dist = dist;
    }
}

public class Main {

    static ArrayList<Integer> OBSx = new ArrayList<Integer>();
    static ArrayList<Integer> OBSy = new ArrayList<Integer>();
    static int boardH;
    static int boardW;
    static ArrayList<net> nets = new ArrayList<net>();
    static int board[][];
    static int layers = 2;

    static final int row[] = {-1, 0, 0, 1};
    static final int col[] = {0, -1, 1, 0};
    static boolean flag;

    static boolean isValid(boolean visited[][], int row, int col){
        return (row >= 0) && (row < boardH) && (col >= 0) && (col < boardW) && (board[row][col] == 0) && !visited[row][col];
    }


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
        board = new int[boardH][boardW];
        for(int i = 0; i < boardH; i++){
            for(int j = 0; j < boardW; j++){
                board[i][j] = 0;
            }
            for(int o = 0; o < OBSx.size(); o++) {
                if (i == OBSy.get(o) - 1) {
                    board[i][OBSx.get(o) - 1] = -1;
                }
            }
        }
    }

    public static void shortestPath(boolean[][] visited, ArrayList<pin> checked, int sX, int sY, int dX, int dY, int sM, int dM, int minDest, int counter){
        if(flag){
            return;
        }
        if (sX == dX && sY == dY && sM == dM){
            flag = true;
            return;
        }
        else if (counter > minDest){ // not the shortest path
            counter = counter - 1;
            return;
        }
        else{
            if ((sX - 1 >= 0) && (visited[sY][sX - 1]))
            {
//                visitedPath[sY][sX] = true;
                shortestPath(visited, checked, sX - 1, sY, dX, dY, sM, dM, minDest, counter+1 );
                if (flag) {
                    checked.add(new pin(sM, sX, sY, counter));
                }
            }

            if ((sY - 1 >= 0) && (visited[sY - 1][sX]))
            {
//                visitedPath[sY][sX] = true;
                shortestPath(visited, checked, sX, sY - 1, dX, dY, sM, dM, minDest, counter+1);
                if (flag)
                    checked.add(new pin(sM, sX, sY, counter));
            }

            if ((sX + 1 < boardW) && (visited[sY][sX + 1]))
            {
//                visitedPath[sY][sX] = true;
                shortestPath(visited, checked, sX + 1, sY, dX, dY, sM, dM, minDest, counter+1);
                if (flag)
                    checked.add(new pin(sM, sX, sY, counter));
            }

            if ((sY + 1 < boardH) && (visited[sY + 1][sX]))
            {
//                visitedPath[sY][sX] = true;
                shortestPath(visited, checked, sX, sY + 1, dX, dY, sM, dM, minDest, counter+1);
                if (flag)
                    checked.add(new pin(sM, sX, sY, counter));
            }
        }
    }

    static void BFS(int boardTemp[][],int sX, int sY, int dX, int dY){
        boolean[][] visited = new boolean[boardH][boardW];
        Queue<pin> q = new ArrayDeque<>();
        ArrayList<pin> checked = new ArrayList<>();

        int i = sX; int j = sY;
        q.add(new pin(1, i, j, 0));
        int minDist = Integer.MAX_VALUE;

        while(!q.isEmpty()){
            pin pin = q.poll();
            i = pin.x;
            j = pin.y;
            int dist = pin.dist;


            if(i == dX && j == dY){
                minDist = dist;
                break;
            }

            for(int k = 0; k < 4; k++){
                if(isValid(visited, i + row[k], j + col[k])){
                    visited[i + row[k]][j + col[k]] = true;
                    boardTemp[i + row[k]][(j + col[k])] = dist + 1;

                    q.add(new pin(1, i + row[k], j + col[k], dist + 1));
                }
            }
        }
        int xxxx = 0;
        for(int m = 0; m < boardH; m++){
            for(int n = 0; n < boardW; n++){
                if(visited[m][n]){
                    pin p = new pin(1, n, m, boardTemp[m][n]);
                    checked.add(p);
//                    System.out.println(p.x + "  " + p.y + "  " + p.metal + "  " + p.dist);
                    xxxx++;
                }
            }
        }
        System.out.println(minDist);

        ArrayList<pin> path = new ArrayList<>();
        flag = false;
        boolean[][] visitedPath = new boolean[boardH][boardW];
        shortestPath(visited, path, sX, sY, dX, dY, 1, 1, minDist, 0);
        System.out.println("please");
        for(int p = 0; p < path.size(); p++){
            board[path.get(p).y][path.get(p).x] = 1;
            System.out.println(path.get(p).x + "  " + path.get(p).y);
        }
        board[dY][dX] = 1;

        System.out.println(path.size());

    }

    public static void main(String[] args) {
	init("test1.txt");
	int[][] temp = new int[boardH][boardW];

	BFS(temp, 3, 4, 6, 6);

	GridGraphics gg = new GridGraphics();
	gg.Draw(board, boardW, boardH);


    }
}
