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


//Class pin holds the value of a cell in terms of its x and y coordinates, its metal layer that it sits on and the distance from the source pin of the current path
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

	
//Checks if a cell is a possible part of the path from source to destination by checking if its within the grid boundaries, if it is an empty cell or if it was visited before or not
    static boolean isValid(boolean visited[][], int row, int col){
        return (row >= 0) && (row < boardH) && (col >= 0) && (col < boardW) && (board[row][col] == 0) && !visited[row][col];
    }

//Systematically takes the data from the tect file line by line and puts it in the location in the program that it is required to be in
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

//Initializes board with 0s for empty cells and -1 for cells that contain an obstacle
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
	
//Recursive function that takes all the visited cells of the board with their distances from the source and runs recursively to check if the current path the program
//is on is the correct 1, if the counter exceeds the minimum distance from src to dest then the program goes back to its previous cell and tries a new direction.
//Once found, a flag is to be set true and return the function and upon every return from the path, the cells data of the path is stored in an ArrayList of pin objects.
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

//A BFS algorithm that iteratively checks every possible value from source to destination while marking it if its visited or not and marking the distance each cell
//from the source and goes in every possible direction by putting all cell values in a queue if the cell is within bounds or is not checked before or is not an obstacle
//which then stops when it reaches the destination cell to produce the minimum distance between source and dest which is used in the above function to produce a path
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
	
//function that takes a net from the list of nets and runs each of its pins where one pin is src and the next is the destination and in the next iteration, the previous
//destination is now the source and a new pin is the destination.
    public static void runNet(net n, int netI){
        ArrayList<pin> pathPin = new ArrayList<>();

        for(int i = 0; i < n.pinX.size() - 1; i++){
            flag.add(false);
            pathPin.addAll(BFS(n.pinX.get(i) - 1, n.pinY.get(i), n.pinX.get(i + 1), n.pinY.get(i + 1), netI + 1, flag.size() - 1));
        }
        writeBack(netI, pathPin);
    }
//function that takes values from the list containing pins of the path from all paths in a net and writes them to text file of our choosing
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

//runs runNet but for every net in the program
    public static void runAll(){
        for(int i = 0; i < nets.size(); i++){
            runNet(nets.get(i), i);
        }
    }

    public static void main(String[] args) {
	init("test1.txt");

    flag = new ArrayList<Boolean>();

    runAll();
	//creates graphics
	GridGraphics gg = new GridGraphics();
	gg.Draw(board, boardW, boardH);


    }
}
