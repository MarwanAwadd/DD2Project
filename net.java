package com.company;

import java.util.ArrayList;
import java.util.Scanner;

public class net {

    public String Name;
    public ArrayList<Integer> metal;
    public ArrayList<Integer> pinX;
    public ArrayList<Integer> pinY;

    public net() {
        metal = new ArrayList<Integer>();
        pinX = new ArrayList<Integer>();
        pinY = new ArrayList<Integer>();
    }

    public void netInit(String netLine){
        Scanner nL = new Scanner(netLine);

        this.Name = nL.next();
        String temp = nL.next();
        do{
            String pX, pY, m;

            temp = temp.substring(1, temp.indexOf(')'));
            m = temp.substring(0, temp.indexOf(','));

            temp = temp.substring(temp.indexOf(',') + 1);
            pX = temp.substring(0, temp.indexOf(','));

            pY = temp.substring(temp.indexOf(',') + 1);

            metal.add(Integer.parseInt(m));
            pinX.add(Integer.parseInt(pX));
            pinY.add(Integer.parseInt(pY));

            temp = null;
            temp = nL.next();
        }while(nL.hasNext());

        String pX, pY, m;

        temp = temp.substring(1, temp.indexOf(')'));
        m = temp.substring(0, temp.indexOf(','));

        temp = temp.substring(temp.indexOf(',') + 1);
        pX = temp.substring(0, temp.indexOf(','));

        pY = temp.substring(temp.indexOf(',') + 1);

        metal.add(Integer.parseInt(m));
        pinX.add(Integer.parseInt(pX));
        pinY.add(Integer.parseInt(pY));

    }
}
