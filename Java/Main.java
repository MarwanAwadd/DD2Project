package com.company;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
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
    static ArrayList<Boolean> flag;

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

    public static void shortestPath(boolean[][] visitedPath, boolean[][] visited, ArrayList<pin> checked, int sX, int sY, int dX, int dY, int sM, int dM, int minDest, int counter, int flagI){
        if(flag.get(flagI)){
            return;
        }
        if (sX == dX && sY == dY && sM == dM){
            flag.set(flagI, true);
            checked.add(new pin(sM, sX, sY, counter));
            return;
        }
        else if (counter > minDest){ // not the shortest path
            counter = counter - 1;
            return;
        }
        else{
            if ((sX - 1 >= 0) && (visited[sY][sX - 1]) && !(visitedPath[sY][sX - 1]) && !flag.get(flagI))
            {
                visitedPath[sY][sX] = true;
                shortestPath(visitedPath, visited, checked, sX - 1, sY, dX, dY, sM, dM, minDest, counter+1, flagI);
                if (flag.get(flagI)) {
                    checked.add(new pin(sM, sX, sY, counter));
                }
            }

            if ((sY - 1 >= 0) && (visited[sY - 1][sX]) && !(visitedPath[sY - 1][sX]) && !flag.get(flagI))
            {
                visitedPath[sY][sX] = true;
                shortestPath(visitedPath, visited, checked, sX, sY - 1, dX, dY, sM, dM, minDest, counter+1, flagI);
                if (flag.get(flagI))
                    checked.add(new pin(sM, sX, sY, counter));
            }

            if ((sX + 1 < boardW) && (visited[sY][sX + 1]) && !(visitedPath[sY][sX + 1]) && !flag.get(flagI))
            {
                visitedPath[sY][sX] = true;
                shortestPath(visitedPath, visited, checked, sX + 1, sY, dX, dY, sM, dM, minDest, counter+1, flagI);
                if (flag.get(flagI))
                    checked.add(new pin(sM, sX, sY, counter));
            }

            if ((sY + 1 < boardH) && (visited[sY + 1][sX]) && !(visitedPath[sY + 1][sX]) && !flag.get(flagI))
            {
                visitedPath[sY][sX] = true;
                shortestPath(visitedPath, visited, checked, sX, sY + 1, dX, dY, sM, dM, minDest, counter+1, flagI);
                if (flag.get(flagI))
                    checked.add(new pin(sM, sX, sY, counter));
            }

            visitedPath[sY][sX] = false;
        }
    }


    static ArrayList<pin> BFS(int sX, int sY, int dX, int dY, int netI, int flagI){
        int[][] boardTemp = new int[boardH][boardW];
        boolean[][] visited = new boolean[boardH][boardW];
        Queue<pin> q = new ArrayDeque<>();
        ArrayList<pin> checked = new ArrayList<>();

        int i = sY; int j = sX;
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
        for(int m = 0; m < boardH; m++){
            for(int n = 0; n < boardW; n++){
                if(visited[m][n]){
                    pin p = new pin(1, n, m, boardTemp[m][n]);
                    checked.add(p);
                }
            }
        }
        System.out.println(minDist);

        boolean[][] visitedPath = new boolean[boardH][boardW];

        flag.set(flagI, false);
        ArrayList<pin> path = new ArrayList<>();
        shortestPath(visitedPath, visited, path, sX, sY, dX, dY, 1, 1, minDist, 0, flagI);

        for(int p = 0; p < path.size(); p++){
            board[path.get(p).y][path.get(p).x] = netI;
        }
        board[dY][dX] = netI;

        return path;
    }

    public static void runNet(net n, int netI){
        ArrayList<pin> pathPin = new ArrayList<>();

        for(int i = 0; i < n.pinX.size() - 1; i++){
//            board[n.pinY.get(i)][n.pinX.get(i)] = 0;
            flag.add(false);
            pathPin.addAll(BFS(n.pinX.get(i) - 1, n.pinY.get(i), n.pinX.get(i + 1), n.pinY.get(i + 1), netI + 1, flag.size() - 1));
        }
        writeBack(netI, pathPin);
    }

    public static void writeBack(int n, ArrayList<pin> path){

        String out = new String("net" + String.valueOf(n + 1) + ": ");
        for(int i = 0; i < path.size(); i++){
            String temp = new String("(" + String.valueOf(path.get(i).metal) + "," + String.valueOf(path.get(i).x) + "," + String.valueOf(path.get(i).y) + ")");
            out = out + temp + " ";
        }

        try {
            FileWriter myWriter = new FileWriter("Results/result1.txt");
            myWriter.write(out);
            myWriter.close();
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static void runAll(){
        for(int i = 0; i < nets.size(); i++){
            runNet(nets.get(i), i);
        }
    }

    public static void main(String[] args) {
	init("test1.txt");

    flag = new ArrayList<Boolean>();

    runAll();

	GridGraphics gg = new GridGraphics();
	gg.Draw(board, boardW, boardH);


    }
}
