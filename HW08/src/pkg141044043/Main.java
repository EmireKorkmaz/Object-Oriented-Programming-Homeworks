/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg141044043;
/*
    HW08 - Emire Korkmaz

    In this homework, we wrote our game of Connect Four program in Java
   with a GUI. When the game starts, a dialog box shows up to ask 1 or 2 player
   game. Another dialog asks the size of the board. After these the game starts.

*/

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import static javafx.application.Platform.exit;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;


public class Main  {
    JFrame frame = new JFrame();
    JPanel panel = new JPanel();
    JPanel panel2 = new JPanel();
    static JButton[][] buttons = new JButton[20][20];
    static JButton[][] buttons2 = new JButton[20][20];
    JButton[] harfler = new JButton[20];
    public static int size, a, b;
    public static String choice, move;
    public static boolean turn, block;
    public Color currentColor;
    public String[] letters={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T", "U", "V", "W", "X", "Y", "Z"};
    public int[] isColFilled = new int[size];
    public static int isFilled;
    
    public Main(){
        turn = true;
        isFilled=0;
        block=true;
        if(turn) // player's color
            currentColor=Color.blue;
        else
            currentColor=Color.red;
        
        for(int i=0; i<size; i++)
            isColFilled[i]=size-1;
        
        panel.setLayout(new GridLayout(size+1, size, 10, 10)); // setting up a panel
                
        Dimension d = new Dimension(10*size,10*size);
        
        handler e = new handler();
        
        for(int i=0; i<size;i++){
            harfler[i] = new JButton(letters[i]);
            harfler[i].addActionListener(e); // creating buttons with letters
            panel.add(harfler[i]);
        }
        
        
        for(int i= 0; i<size; i++)
            for(int j=0; j<size;j++){
                buttons[i][j] = new JButton();
                buttons[i][j].setPreferredSize(d); // creating buttons with colors
                buttons[i][j].setBackground(Color.white);
                panel.add(buttons[i][j]);
            }
        frame.add(panel);
        
        frame.setSize(350+(10*size),350+(10*size)); // setting size of the frame
        frame.setResizable(false);
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
        
    }
    public static void main(String[] args) {
        String temp = JOptionPane.showInputDialog("Enter size");
        size = Integer.parseInt(temp);
        while(size<4){
            String t = JOptionPane.showInputDialog("Invalid size. Size must be greater than 3.");
            size = Integer.parseInt(t);
        }
        
        choice = JOptionPane.showInputDialog("Enter choice. \n\"C\" for 1 player \"P\" for 2 players");
        
        Main obj = new Main();
   
    }
    
    private class handler implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            for(int i=0; i<=size; i++){ // event handler for user's actions
                if(e.getSource() == harfler[i] ){
                    move=letters[i];
                    makeMove();
                }
                    
            }                 
        }
    }
    public void makeMove(){
        
        getAscii();
        if(isColFilled[a]<0){
            JOptionPane.showInputDialog("Try again coloumn is fiiled");
            return ;
        }
        if(turn)
            buttons[isColFilled[a]][a].setBackground(Color.blue);
        else
            buttons[isColFilled[a]][a].setBackground(Color.red);
        isColFilled[a]--;
        isFilled++;
        
        whoWon(); // checks evertime if there is a winner
        if(size*size==isFilled){
             JOptionPane.showMessageDialog(null, "Board is full.");
            int answer = JOptionPane.showConfirmDialog(null, "New game?", "", JOptionPane.YES_NO_OPTION);
            if (answer == JOptionPane.YES_OPTION) // after the game ends ask for another game
                newGame();
            else
                exit();
        }
        if(choice.equals("P"))
            turn = (turn ? false : true);
        
        if(choice.equals("C") && (isFilled==1 || isFilled%2==0))
            block = (block ? false : true);
        
        if((choice.equals("C")) && !block){
            turn = (turn ? false : true);
            play();
            block=false;
            turn = (turn ? false : true);
        }
    }
    
    // checks whole board to see if there is a winner or not
    public void whoWon(){
        String player = (turn ? "Blue" : "Red");
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                if(buttons[i][j]!=null)
                    if(j+3<size && buttons[i][j].getBackground()!=Color.white && buttons[i][j+3]!=null){
                        if (buttons[i][j].getBackground()==buttons[i][j+1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j+2].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j+3].getBackground()){  
                            JOptionPane.showMessageDialog(null,player +" won.");
                            int answer = JOptionPane.showConfirmDialog(null, "New game?", "", JOptionPane.YES_NO_OPTION);
                            if (answer == JOptionPane.YES_OPTION) // after the game ends ask for another game
                                newGame();
                            else
                                exit();
                        }
                    }
            }
        }
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                if(buttons[i][j]!=null)
                    if(i+3<size && buttons[i][j].getBackground()!=Color.white && buttons[i+3][j]!=null){
                        if (buttons[i][j].getBackground()==buttons[i+1][j].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i+2][j].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i+3][j].getBackground()){  
                            JOptionPane.showMessageDialog( null, player +" won.", "", JOptionPane.INFORMATION_MESSAGE, null); 
                            int answer = JOptionPane.showConfirmDialog(null, "New game?", "", JOptionPane.YES_NO_OPTION);
                            if (answer == JOptionPane.YES_OPTION)
                                newGame();
                            else
                                System.exit(0);
                        }
                    }
            }
        }
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                if(buttons[i][j]!=null)
                    if (j+3<size && i+3<size && buttons[i][j].getBackground()!=Color.white &&
                        buttons[i][j].getBackground()==buttons[i+1][j+1].getBackground() &&
                        buttons[i][j].getBackground()==buttons[i+2][j+2].getBackground() &&
                        buttons[i][j].getBackground()==buttons[i+3][j+3].getBackground()){ 
                        
                        JOptionPane.showMessageDialog( null, player +" won.", "", JOptionPane.INFORMATION_MESSAGE, null); 
                        int answer = JOptionPane.showConfirmDialog(null, "New game?", "", JOptionPane.YES_NO_OPTION);
                            if (answer == JOptionPane.YES_OPTION)
                                newGame();
                            else
                                System.exit(0);
                    }
                    if (i+3<size && buttons[i][j].getBackground()!=Color.white && j>2 &&
                                buttons[i][j].getBackground()==buttons[i+1][j-1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i+2][j-2].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i+3][j-3].getBackground()){
                        JOptionPane.showMessageDialog( null, player +" won.", "", JOptionPane.INFORMATION_MESSAGE, null); 
                        int answer = JOptionPane.showConfirmDialog(null, "New game?", "", JOptionPane.YES_NO_OPTION);
                            if (answer == JOptionPane.YES_OPTION)
                                newGame();
                            else
                                System.exit(0);
                    }
                    if (j+3<size && buttons[i][j].getBackground()!=Color.white && i>2 &&
                                buttons[i][j].getBackground()==buttons[i-1][j+1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i-2][j+2].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i-3][j+3].getBackground()){
                       JOptionPane.showMessageDialog( null, player +" won.", "", JOptionPane.INFORMATION_MESSAGE, null); 
                        int answer = JOptionPane.showConfirmDialog(null, "New game?", "", JOptionPane.YES_NO_OPTION);
                            if (answer == JOptionPane.YES_OPTION)
                                newGame();
                            else
                                System.exit(0);
                    }

            }
        }
    }
    private void getAscii(){ // gets numerical value of move
        switch(move){
            case "A": a =0;
                    break;
            case "B": a =1;
                    break;
            case "C": a =2;
                    break;
            case "D": a =3;
                    break;
            case "E": a =4;
                    break;
            case "F": a =5;
                    break;
            case "G": a =6;
                    break;
            case "H": a =7;
                    break;
            case "I": a =8;
                    break;
            case "J": a =9;
                    break; 
            case "K": a =10;
                    break; 
            case "L": a =11;
                    break; 
            case "M": a =12;
                    break; 
            case "N": a =13;
                    break;     
            case "O": a =14;
                    break; 
            case "P": a =15;
                    break; 
            case "Q": a =16;
                    break; 
            case "R": a =17;
                    break; 
            case "S": a =18;
                    break; 
            case "T": a =19;
                    break; 
            case "U": a =20;
                    break; 
            case "V": a =21;
                    break; 
            case "W": a =22;
                    break; 
            case "X": a =23;
                    break; 
            case "Y": a =24;
                    break; 
            case "Z": a =25;
                    break;                
        }
    }
    
    // after the game ends asks user if there will be another game
    public void newGame(){ // if it is gets new game's board's size and choice
                           //  and after these creates a brand new game
        frame.getContentPane().remove(panel);
        String temp = JOptionPane.showInputDialog("Enter size");
        choice = JOptionPane.showInputDialog("Enter choice");
        
        size = Integer.parseInt(temp);
        
        turn = true;
        isFilled=0;
        block=false;
        
        if(turn)
            currentColor=Color.blue;
        else
            currentColor=Color.red;
 
        panel2.setLayout(new GridLayout(size+1, size, 10, 10));
        
        Dimension d = new Dimension(10*size,10*size);
        
        handler ev = new handler();
        
        for(int i=0; i<size;i++){
            harfler[i] = new JButton(letters[i]);
            harfler[i].addActionListener(ev);
            panel2.add(harfler[i]);
        }
        buttons = new JButton[size][size];
        for(int i= 0; i<size; i++)
            for(int j=0; j<size;j++){
                buttons[i][j] = new JButton();
                buttons[i][j].setPreferredSize(d);
                buttons[i][j].setBackground(Color.white);
                panel2.add(buttons[i][j]);
            }
        
        panel2.setVisible(true);
        frame.getContentPane().remove(panel);
        frame.add(panel2);
        frame.getContentPane().invalidate();
        frame.getContentPane().validate();
        frame.setSize(350+(10*size),350+(10*size));
        frame.setResizable(false);
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
        
        isColFilled = new int[size];
        for(int m=0; m<size; m++)
           isColFilled[m]=size-1;
        isFilled=0;
        
    }
    
    // this function is for computer's move. Checks whole board and decides the
    // best move to make.
    public void play(){
        Random r = new Random();

        int  rand = r.nextInt(4) + 1;
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j) {
                if( buttons[i][j].getBackground()!=currentColor){
                    if(j<size-3 && buttons[i][j+2].getBackground()==Color.white &&
                            buttons[i][j].getBackground()==buttons[i][j+1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j+3].getBackground())
                        move = letters[j+2];
                    else if(j<size-3 && buttons[i][j+1].getBackground()==Color.white &&
                            buttons[i][j].getBackground()==buttons[i][j+2].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j+3].getBackground())
                        move = letters[j+1];
                    else if( j<size-3 &&buttons[i][j+3].getBackground()==Color.white &&
                            buttons[i][j].getBackground()==buttons[i][j+1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j+2].getBackground())
                        move = letters[j+3];
                    else if(j>2 && buttons[i][j-3].getBackground()==Color.white &&
                            buttons[i][j].getBackground()==buttons[i][j-1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j-2].getBackground())
                        move = letters[j-3];

                    if (j<size-3 &&
                            buttons[i][j].getBackground()==buttons[i][j+1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j+2].getBackground() &&
                            buttons[i][j+3].getBackground()==Color.white)
                        move=letters[j+3];
                    else if(i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i-3][j].getBackground() &&
                            buttons[i-3][j].getBackground()==Color.white)
                        move=letters[j];
                    else if (j<size-3 &&
                            buttons[i][j].getBackground()==buttons[i][j+1].getBackground() &&
                            buttons[i][j+2].getBackground()==Color.white)
                        move=letters[j+2];
                    else if(i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j].getBackground() &&
                            buttons[i-3][j].getBackground()==Color.white)
                        move=letters[j];

                    if (j<size-3 && i<size-3 &&
                            buttons[i][j].getBackground()==buttons[i+1][j+1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i+2][j+2].getBackground() &&
                            buttons[i+3][j+3].getBackground()==Color.white)
                        move = letters[j+3];
                    else if (j>2 && i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j-1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i-2][j-2].getBackground() &&
                            buttons[i-3][j-3].getBackground()==Color.white)
                        move = letters[j-3];
                    else if (j<size-3 && i<size-3 &&
                            buttons[i][j].getBackground()==buttons[i+1][j+1].getBackground() &&
                            buttons[i+2][j+2].getBackground() ==Color.white)
                        move = letters[j+2];
                    else if(j>2 && i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j-1].getBackground() &&
                            buttons[i-2][j-2].getBackground()==Color.white)
                        move = letters[j-2];
                }

                else if( buttons[i][j].getBackground()!=Color.white &&
                            buttons[i][j].getBackground()==currentColor ){
                    if (j<size-3 &&
                            buttons[i][j].getBackground()==buttons[i][j+1].getBackground() &&
                            buttons[i][j].getBackground()==buttons[i][j+2].getBackground() &&
                            buttons[i][j+3].getBackground()==Color.white)
                        move=letters[j+3];
                    else if(i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j].getBackground() && 
                            buttons[i][j].getBackground()==buttons[i-3][j].getBackground() &&
                            buttons[i-3][j].getBackground()==Color.white)
                        move=letters[j];
                    else if (j<size-3 &&
                            buttons[i][j].getBackground()==buttons[i][j+1].getBackground() && 
                            buttons[i][j+2].getBackground()==Color.white)
                        move=letters[j+2];
                    else if(i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j].getBackground() && 
                            buttons[i-3][j].getBackground()==Color.white)
                        move=letters[j];

                    if (j<size-3 && i<size-3 &&
                            buttons[i][j].getBackground()==buttons[i+1][j+1].getBackground() && 
                            buttons[i][j].getBackground()==buttons[i+2][j+2].getBackground() && 
                            buttons[i+3][j+3].getBackground()==Color.white)
                        move = letters[j+3];
                    else if (j>2 && i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j-1].getBackground() && 
                            buttons[i][j].getBackground()==buttons[i-2][j-2].getBackground() && 
                            buttons[i-3][j-3].getBackground()==Color.white)
                        move = letters[j-3];
                    else if (j<size-3 && i<size-3 &&
                            buttons[i][j].getBackground()==buttons[i+1][j+1].getBackground() && 
                            buttons[i+2][j+2].getBackground() ==Color.white)
                        move = letters[j+2];
                    else if(j>2 && i>2 &&
                            buttons[i][j].getBackground()==buttons[i-1][j-1].getBackground() &&
                            buttons[i-2][j-2].getBackground()==Color.white)
                        move = letters[j-2];
                }
                else{
                    move=letters[rand];
                }
            }
        }
        if(move==null) {
            for (int i = 0; i < size; ++i)
                if (buttons[i][rand].getBackground() == Color.white)
                    move = letters[rand];
        }
        makeMove();
    }
}
