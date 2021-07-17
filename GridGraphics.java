package com.company;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class GridGraphics {

    public static void Draw(ArrayList<ArrayList<Integer>> board, int boardW, int boardH){
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800,800);
        frame.setLayout(new GridLayout(boardH, boardW, 5, 5));

        for(int i = 0; i < boardH; i++){
            for(int j = 0; j < boardW; j++){
                JButton button;
                JLabel label;
                if(board.get(i).get(j) == -1){
                    label = new JLabel("OBS");
                    label.setBackground(Color.BLACK);
                    //label.setForeground(Color.RED);

                    label.setOpaque(true);
                }
                else if(board.get(i).get(j) == 0){
                    label = new JLabel();
                    label.setBackground(Color.WHITE);
                    label.setForeground(Color.WHITE);
                    label.setOpaque(true);
                }
                else {
                    label = new JLabel("net" + String.valueOf(board.get(i).get(j)));
                    label.setBackground(Color.YELLOW);
                    label.setForeground(Color.YELLOW);
                    label.setOpaque(true);
                }

                frame.add(label);
            }
        }


        frame.setVisible(true);

    }
}
