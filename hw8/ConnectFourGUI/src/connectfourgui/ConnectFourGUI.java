package connectfourgui;

import java.awt.Color;
import java.awt.Font;
import static java.awt.Font.SERIF;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *
 * @author ferhat
 */
public class ConnectFourGUI extends JFrame {
    
    private JPanel Start;
    private JPanel AgainstComputer;
    private JPanel AgainstPlayer;
    private JPanel Setting;
    private JPanel Result;
    private JButton SingleGame;
    private JButton MultiGame;
    private JButton SettingButton;
    private JButton ReturnButton;
    private JButton HomeButton1;
    private JButton HomeButton2;
    private JButton AgainButton;
    private JLabel StartTitle;
    private JLabel PlayerAgainstComputer;
    private JLabel ComputerAgainstPlayer;
    private JLabel Player1Label;
    private JLabel Player2Label;
    private JLabel ResultLabel;
    private JLabel ResultText;
    private Icon Icons[];
    private Icon ResultIcon;
    private char GameCells[][];
    private JLabel CellsLabel[][];
    private JLabel CellsColumnLabel[];
    private JLabel Grid;
    private String CurrentPlayer;
    private char GameType;
    private final int RowNum =6;
    private final int ColNum =7;
    private final int ToWin =4;
    private boolean win;
    
    ConnectFourGUI(){
    
        super("CONNECT FOUR");
        super.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        super.setSize(900,700);
        super.setResizable(false);
        super.setVisible(true);
        setIcons();
        setLabels();
        setButtons();
        makeBoard();
     
        initStart();

    }
    
    /**
     * Initialize the first panel opening at the beginning of the program
     * Add single player and multi player buttons
     */
    public void initStart(){
    
        Start =new JPanel();
        Start.setSize(getHeight(),getWidth());
        Start.setLayout(null);
        Start.setBackground(new Color(160,82,45));
       
        Start.add(SingleGame);
        Start.add(MultiGame);
        Start.add(StartTitle);
        add(Start);
        revalidate();
        repaint();
    }
    
    /**
     * Initialize the panel that play against computer
     * Add grid and label to the panel
     */
    public void initAgainstComputer(){
    
        AgainstComputer =new JPanel();
        AgainstComputer.setSize(getHeight(),getWidth());
        AgainstComputer.setLayout(null);
        AgainstComputer.setBackground(new Color(160,82,45));
        

        AgainstComputer.add(PlayerAgainstComputer);
        
        AgainstComputer.add(ComputerAgainstPlayer);
        
        AgainstComputer.add(SettingButton);
        
        for(int i=0;i<getRow();++i){
        
            for(int j=0;j<getCol();++j){
                AgainstComputer.add(CellsLabel[i][j]);
            }
        }
        
        for(int i=0;i<getCol();++i){
 
            AgainstComputer.add(CellsColumnLabel[i]);
        }
      
        AgainstComputer.add(Grid);
        
        add(AgainstComputer);
        revalidate();
        repaint();
    }
    
    /**
     * Initialize the panel that play against player
     * Adds necessary component like label and grid
     */
    public void initAgainstPlayer(){
    
        AgainstPlayer =new JPanel();
        AgainstPlayer.setSize(getHeight(),getWidth());
        AgainstPlayer.setLayout(null);
        AgainstPlayer.setBackground(new Color(160,82,45));
   

        AgainstPlayer.add(Player1Label);

        AgainstPlayer.add(Player2Label);
        
        AgainstPlayer.add(SettingButton);
        
        for(int i=0;i<getRow();++i){
        
            for(int j=0;j<getCol();++j){

                AgainstPlayer.add(CellsLabel[i][j]);
            }
        }

        for(int i=0;i<getCol();++i){
            AgainstPlayer.add(CellsColumnLabel[i]);
        }
        
        AgainstPlayer.add(Grid);
        
        add(AgainstPlayer);
        revalidate();
        repaint();
    }
    
    /**
     *Initialize the Setting panel 
     * Add return button and home button
     */
    public void initSetting(){
    
        Setting =new JPanel();
        Setting.setSize(getHeight(),getWidth());
        Setting.setLayout(null);
        Setting.setBackground(new Color(160,82,45));
        
        Setting.add(StartTitle);
        
        Setting.add(ReturnButton);

        Setting.add(HomeButton1);

        add(Setting);
        revalidate();
        repaint();
    }
    
    /**
     *Initialize the last panel 
     * When game ends this panel opens 
     */
    public void initResult(){
    
        Result = new JPanel();
        Result.setSize(getHeight(),getWidth());
        Result.setLayout(null);
        Result.setBackground(new Color(160,82,45));

        if(win){
        
            if("User1".equals(CurrentPlayer)){
                ResultIcon =Icons[15];
                ResultText.setText("PLAYER1 WON!!!");
            }
            else{
                ResultIcon =Icons[16];
                if(GameType =='c')
                    ResultText.setText("COMPUTER WON!!!");
                else
                    ResultText.setText("PLAYER2 WON!!!");
            }
        }
        else{
        
            ResultIcon =Icons[19];
            ResultText.setText("GAME DRAWN!!!");
        }
        
        if(GameType =='c')
            remove(AgainstComputer);
        
        else
            remove(AgainstPlayer);
        
        deleteBoard();
        
        ResultLabel.setIcon(ResultIcon);
        ResultLabel.setBounds(330, 100,ResultIcon.getIconWidth(),ResultIcon.getIconHeight());
        
        Result.add(ResultText);
        Result.add(ResultLabel);
        Result.add(HomeButton2);
        Result.add(AgainButton);
        
        add(Result);
        revalidate();
        repaint();
    }
    
    /**
     *Initialize all labels here like Title and grid
     */
    public void setLabels(){
    
        StartTitle =new JLabel();
          
        StartTitle.setIcon(Icons[2]);
        StartTitle.setBounds(270, 130,Icons[2].getIconWidth(),Icons[2].getIconHeight());
        
        PlayerAgainstComputer =new JLabel();
        ComputerAgainstPlayer =new JLabel();
        
        PlayerAgainstComputer.setIcon(Icons[3]);
        PlayerAgainstComputer.setBounds(25,50,Icons[3].getIconWidth(),Icons[3].getIconHeight());
        
        ComputerAgainstPlayer.setIcon(Icons[4]);
        ComputerAgainstPlayer.setBounds(775,50,Icons[4].getIconWidth(),Icons[4].getIconHeight());
        
        Player1Label =new JLabel();
        Player2Label =new JLabel();
        
        Player1Label.setIcon(Icons[17]);
        Player1Label.setBounds(25,50,Icons[17].getIconWidth(),Icons[17].getIconHeight());
        
        Player2Label =new JLabel();
        Player2Label.setIcon(Icons[18]);
        Player2Label.setBounds(775,50,Icons[18].getIconWidth(),Icons[18].getIconHeight());
        
        
        CellsLabel  = new JLabel[RowNum][ColNum];
        
        for(int i=0;i<getRow();++i){
        
            for(int j=0;j<getCol();++j){
            
                CellsLabel[i][j]  = new JLabel();
                CellsLabel[i][j].setBounds(190+j*(Icons[7].getIconWidth())+j,65+i*(Icons[7].getIconHeight())+i*12,Icons[7].getIconWidth(),Icons[7].getIconHeight());
            }
        }
        
        CellsColumnLabel =new JLabel[ColNum];
        for(int i=0;i<getCol();++i){
            CellsColumnLabel[i] =new JLabel();
            CellsColumnLabel[i].setBounds(175+i*(Icons[6].getIconWidth()/7), 60,Icons[6].getIconWidth()/7,Icons[6].getIconHeight());
            CellsColumnLabel[i].addMouseListener(new LabelHandler(i));
        }
        
        Grid =new JLabel();
        Grid.setIcon(Icons[6]);
        Grid.setBounds(170,50,Icons[6].getIconWidth(),Icons[6].getIconHeight());
        
        ResultText =new JLabel();
        ResultText.setForeground(Color.LIGHT_GRAY);
        ResultText.setBackground(Color.BLACK);
        ResultText.setFont(new Font(SERIF,Font.BOLD,20));
        ResultText.setBounds(330, 300, 300, 50);
        
        ResultLabel =new JLabel();      
    }
    
    /**
     *Initialize all button here like single multi
     */
    public void setButtons(){
     
        SingleGame =new JButton();
        MultiGame =new JButton();
        SettingButton =new JButton();
        ReturnButton =new JButton();
        HomeButton1 =new JButton();
        HomeButton2 =new JButton();
        AgainButton =new JButton();
        
        SingleGame.setIcon(Icons[0]);
        SingleGame.setToolTipText("Play Against Computer");
        SingleGame.setBounds(270, 250,Icons[0].getIconWidth(),Icons[0].getIconHeight());
        SingleGame.addActionListener(new ButtonHandler("SingleGame"));
        
        MultiGame.setIcon(Icons[1]);
        MultiGame.setToolTipText("Play Against Player");
        MultiGame.setBounds(450,250,Icons[1].getIconWidth(),Icons[1].getIconHeight());
        MultiGame.addActionListener(new ButtonHandler("MultiGame"));
        
        SettingButton.setIcon(Icons[5]);
        SettingButton.setBounds(775,500,Icons[5].getIconWidth(),Icons[5].getIconHeight());
        SettingButton.setToolTipText("Setting");
        SettingButton.addActionListener(new ButtonHandler("Setting"));       
        
        ReturnButton.setIcon(Icons[12]);
        ReturnButton.setBounds(270, 250,Icons[12].getIconWidth(),Icons[12].getIconHeight()); 
        ReturnButton.setToolTipText("Return");
        ReturnButton.addActionListener(new ButtonHandler("Return"));
        
        HomeButton1.setIcon(Icons[13]);
        HomeButton1.setBounds(450,250,Icons[13].getIconWidth(),Icons[13].getIconHeight());
        HomeButton1.setToolTipText("Home");
        HomeButton1.addActionListener(new ButtonHandler("Home1"));
        
        HomeButton2.setIcon(Icons[13]);
        HomeButton2.setBounds(270,350,Icons[13].getIconWidth(),Icons[13].getIconHeight()); 
        HomeButton2.setToolTipText("Home");
        HomeButton2.addActionListener(new ButtonHandler("Home2"));
        
        
        AgainButton =new JButton();
        AgainButton.setIcon(Icons[14]);
        AgainButton.setBounds(470,350,Icons[14].getIconWidth(),Icons[14].getIconHeight());
        AgainButton.setToolTipText("Play Again");
        AgainButton.addActionListener(new ButtonHandler("Again"));    
        
    }
    
    /**
     * Initialize all icons here
     */
    public void setIcons(){
    
        Icons = new ImageIcon[20];
        Icons[0] =new ImageIcon(getClass().getResource("/images/single"));
        Icons[1] =new ImageIcon(getClass().getResource("/images/multi"));
        Icons[2] =new ImageIcon(getClass().getResource("/images/connect"));
        Icons[3] =new ImageIcon(getClass().getResource("/images/player"));
        Icons[4] =new ImageIcon(getClass().getResource("/images/computer"));
        Icons[5] =new ImageIcon(getClass().getResource("/images/setting"));
        Icons[6] =new ImageIcon(getClass().getResource("/images/frame"));
        Icons[7] =new ImageIcon(getClass().getResource("/images/arrows"));
        Icons[8] =new ImageIcon(getClass().getResource("/images/red"));
        Icons[9] =new ImageIcon(getClass().getResource("/images/blue"));
        Icons[10] =new ImageIcon(getClass().getResource("/images/redWin"));
        Icons[11] =new ImageIcon(getClass().getResource("/images/blueWin"));
        Icons[12] =new ImageIcon(getClass().getResource("/images/return"));
        Icons[13] =new ImageIcon(getClass().getResource("/images/homeB"));
        Icons[14] =new ImageIcon(getClass().getResource("/images/again"));
        Icons[15] =new ImageIcon(getClass().getResource("/images/red1"));
        Icons[16] =new ImageIcon(getClass().getResource("/images/blue1"));
        Icons[17] =new ImageIcon(getClass().getResource("/images/player1"));
        Icons[18] =new ImageIcon(getClass().getResource("/images/player2"));     
        Icons[19] =new ImageIcon(getClass().getResource("/images/drawn"));    
    }
    
    /**
     * Update the board for the move and check is game is over or somebody wins
     * @param colNum
     */
    public void updateBoard(int colNum){
    
        char letter;
        Icon cellIcon, winIcon;
        if("User1".equals(getCurrentPlayer())){
            letter ='X';
            cellIcon =Icons[8];
            winIcon =Icons[10];
        }
        else{
            letter ='O';           
            cellIcon =Icons[9];
            winIcon =Icons[11];
        }
        for(int i=getRow()-1;0<=i;--i){
             
           if(GameCells[i][colNum] =='.'){
                    
               GameCells[i][colNum] =letter;
               CellsLabel[i][colNum].setIcon(cellIcon);
               break;
            }
        }
        
        if(isWin(colNum)){
            win =true;  
            for(int i=0;i<getRow();++i){
               for(int j=0;j<getCol();++j){
                   if(GameCells[i][j] == Character.toLowerCase(letter)){
                       CellsLabel[i][j].setIcon(winIcon);
                   }               
               }
           }
           revalidate();
           repaint();
           
           Timer paintLabel =new Timer(1500,new HandlePaint()); 
           
           paintLabel.setRepeats(false);
           paintLabel.start();
            
        }
        else if(isGameOver()){
        
           Timer paintLabel =new Timer(1500,new HandlePaint()); 
           
           paintLabel.setRepeats(false);
           paintLabel.start();
             
        }
        else{
            switchUser();
        }
    }
    
    private class HandlePaint implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
                initResult();  
        }

    }
    
    /**
     * Checks if the move is available
     * @param colNum
     * @return
     */
    public boolean isAvailable(int colNum){
 
        if(GameCells[0][colNum] == '.'){ 
            return true;
        }
   
        return false;
    }
    
    /**
     *Checks if board is full
     * @return
     */
    public boolean isGameOver(){
    
        for(int i=0;i<getCol();++i){            // looking at the top side of the board
            if(GameCells[0][i] =='.')
                return false;
        }
    
        return true;
    }
    
    /**
     * Change the current user
     */
    public void switchUser(){
                
        if("User1".equals(CurrentPlayer)){        
        
            if(GameType =='p'){
                CurrentPlayer ="User2";
            }
            else{
                CurrentPlayer ="Computer";
                play();
            }
        }
        else{
            CurrentPlayer ="User1";
        }
    }
  
    /**
     * Computer makes a move and call updateBoard method
     */
    public void play(){    /* this is for computer to play */
   
        int max; int move = 0;
        boolean used =false;
    
        for(int i=0; i <getRow() && !used ;++i){           // blocking the opponent
            for(int j=0;j<getCol() && !used;++j){
            
                if(GameCells[i][j] == 'X'){         /* looking if there is 3 element of opponent  if there is then block it */ 
                    if(ToWin -1 == vertical(i,j)){
                        if(0 <=(i-1) && GameCells[i-1][j] == '.'){
                            move = j;
                            used =true;
                        }
                    }
                    if(!used && ToWin -1 == horizontal(i,j)){
                        if((j+1) < getCol() && GameCells[i][j+1] =='.'){
                            move = j+1;
                            used =true;
                        }
                        if(0 <= (j-1) && GameCells[i][j-1] == '.'){
                            move = j-1;
                            used =true;
                        }
                    }
                }
            }
        }
            
        max =0;
        if(!used){                                                   //to win
            for(int i=0;i<getRow();++i){                          // if there is 3 element of its own then try to win 
                for(int j=0;j<getCol();++j){
              
                    if(GameCells[i][j] =='O'){        
                        if(1 <= vertical(i,j) && max < vertical(i,j)){           /* for vertical */
                            if( 0<=(i-1) && GameCells[i-1][j] =='.'){
                                move =j;
                                used =true;
                                max =vertical(i,j);
                            }              
                        }
                    }
                }
            }
       
            for(int i=0;i<getRow();++i){
                for(int j=0;j<getCol();++j){
                    if(GameCells[i][j] == 'O'){
                        if(1 <=horizontal(i,j) && max < horizontal(i,j)){
                            if((j+1)<getCol() && GameCells[i][j+1] == '.'){       /* if used in vertical then to be used in horizontal it must be bigger than max */
                                move =j+1;
                                used =true;
                                max =horizontal(i,j);
                            }
                            if(0 <=(j-1) && GameCells[i][j-1] =='.'){
                                move =j-1;
                                used =true;
                                max =horizontal(i,j);
                            }
                        }
                    }
                }
            }
        }
 
        if(!used){    // if couldn't find a logical move then make a random move        
         
            Random rand =new Random();
            do{
                move =rand.nextInt(getCol());
     
            }while(!isAvailable(move));
        }
        updateBoard(move);
    }
    
    /**
     * Checks the game if play wins or not
     * @param LastMove
     * @return true if player wins
     */
    public boolean isWin(int LastMove) {
    
        int row = 0,col;                          //for last move coordinates
        col = LastMove;
        for(int i=0;i<getRow();++i){
        
            if(GameCells[i][col] !='.'){
                row =i;
                break;
            }
        }
    
        if(ToWin <= vertical(row,col))
            return true;
        
        if(ToWin <= horizontal(row,col))
            return true;
    
        if(ToWin <= diagonal(row,col))    
            return true;
            
        return false;

    }
 
    /**
     * Check the board for vertical position
     * @param row
     * @param col
     * @return the number of cell that is vertical position
     */
    public int vertical(int row,int col){  /* checks for vertical */
    
        int sum,up,down,count;
        sum =1; up =0; down =0;
    
   
        for(int i=row+1;i<getRow() && GameCells[row][col] == GameCells[i][col] ;++i){
            ++down;     
        }
    
        for(int i=row-1; 0<= i && GameCells[row][col] ==GameCells[i][col] ;--i){
            ++up;     
        }
    
        sum +=up+down;
        count =0;
     
        if(ToWin <= sum){        
            GameCells[row][col] = Character.toLowerCase(GameCells[row][col]);  //to lowercase 
            ++count; 
        
            for(int i=1;i<=up && count <ToWin;++i,++count){
            
                GameCells[row-i][col] =Character.toLowerCase(GameCells[row][col]);
            }
            for(int i=1; i<=down && count < ToWin ;++i,++count){
            
                GameCells[i+row][col] =Character.toLowerCase(GameCells[row][col]);    
            }   
        }
    
    return sum;
    }

    /**
     * checks the board for horizontal position
     * @param row
     * @param col
     * @return the number of cell that is at horizontal position
     */
    public int horizontal(int row,int col){   // check for horizontal
    
        int sum,right,left,count;
        sum =1; right =0; left =0;
    
  
        for(int i=col+1; i<getCol() && GameCells[row][col] == GameCells[row][i]; ++i){  // for right side
            ++right;      
        }
    
    
        for(int i=col-1; 0<= i && GameCells[row][col] == GameCells[row][i] ;--i){  // for left side
            ++left;     
        } 
    
        sum +=right+left;    
        count =0;
    
        if(ToWin <= sum){       
            GameCells[row][col] =Character.toLowerCase(GameCells[row][col]);       // if win then make them lower case        
            ++count;
            for(int i=1; i<=right && count< ToWin ;++i,++count){            
                GameCells[row][col+i] =Character.toLowerCase(GameCells[row][col]);     
            }
    
       
            for(int i=1; i<=left && count < ToWin ;++i,++count){
                GameCells[row][col-i] =Character.toLowerCase(GameCells[row][col]);     
            }
        }
    
    return sum;

    }

    /**
     * Checks board for diagonal position
     * @param row
     * @param col
     * @return the number of cell that is at diagonal position 
     */
    public int diagonal(int row,int col){        // check for diagonal
    
        int rightToLeft,leftToRight,rightUp,rightDown,leftUp,leftDown;
        int i,j;
        int ret,count;
    
        rightToLeft =1; leftToRight =1; rightUp=0; rightDown=0; leftUp =0; leftDown =0;
    
        for(i=row-1,j=col+1; 0<=i&& 0<=j && i<getRow() && j<getCol() && GameCells[row][col] == GameCells[i][j] ;--i,++j){        
            ++rightUp;     
        }
    
        for(i=row+1,j=col+1; 0<=i&& 0<=j && i<getRow() && j<getCol() && GameCells[row][col] == GameCells[i][j] ;++i,++j){
            ++rightDown;     
        }  
    
        for(i=row-1,j=col-1; 0<=i&& 0<=j && i<getRow() && j<getCol() && GameCells[row][col] == GameCells[i][j] ;--i,--j){
            ++leftUp;         
        }
       
        for(i=row+1,j=col-1; 0<=i&& 0<=j && i<getRow() && j<getCol() && GameCells[row][col] == GameCells[i][j] ;++i,--j){
            ++leftDown;        
        }
    
        rightToLeft +=rightUp+leftDown;
        leftToRight +=leftUp+rightDown;
        count =0;
        
        if(ToWin <= rightToLeft){                                                  // if win then make them lower case
            GameCells[row][col] =Character.toLowerCase(GameCells[row][col]);
            ++count;
            for(i=1;i<=rightUp && count <ToWin; ++i,++count){
            
                GameCells[row-i][col+i] =Character.toLowerCase(GameCells[row][col]);
            }
            for(i=1;i<=leftDown && count <ToWin;++i,++count){
                GameCells[row+i][col-i] =Character.toLowerCase(GameCells[row][col]);
            }
            ret =rightToLeft;
        }
    
        else if(ToWin <= leftToRight){       
            GameCells[row][col] =Character.toLowerCase(GameCells[row][col]);       
            ++count;
        
            for(i=1;i<=leftUp && count<ToWin;++i,++count){            
                GameCells[row-i][col-i] =Character.toLowerCase(GameCells[row][col]);      
            }       
            for(i=1;i<=rightDown &&count <ToWin;++i,++count){
            
                GameCells[row+i][col+i] =Character.toLowerCase(GameCells[row][col]);
            }
            ret =leftToRight;
        }
        else    
            ret =0;
    
        return ret;
    }
 
    
    private void makeBoard(){
    
        GameCells =new char[RowNum][ColNum];
        CurrentPlayer ="User1";
        win =false;
        for(int i=0;i<getRow();++i){
        
            for(int j=0;j<getCol();++j){
            
                GameCells[i][j] ='.';
            }
        }
    }
     
    /**
     * Clean the board 
     */
    public void deleteBoard(){   
        CurrentPlayer ="User1";
        win =false;
        for(int i=0;i<getRow();++i){       
            for(int j=0;j<getCol();++j){           
                GameCells[i][j] ='.';
                CellsLabel[i][j].setIcon(null);
            }
        }  
    }

    /**
     *
     * @return the Current player
     */
    public String getCurrentPlayer(){
    
        return CurrentPlayer;
    }

    /**
     *
     * @return the number of row of the board
     */
    public int getRow(){
    
        return RowNum;
    }

    /**
     *
     * @return the number of column of the board
     */
    public int getCol(){
    
        return ColNum;
    }
    
    private class LabelHandler extends MouseAdapter{
       
        private final int which;
        
        LabelHandler(int n){
           which =n;
        }

        @Override
        public void mouseEntered(MouseEvent e){

            for(int i=0;i<6;++i){
            
                if(GameCells[i][which] == '.'){
                
                    CellsLabel[i][which].setIcon(Icons[7]);
                }
            }          
        }
        @Override
        public void mouseExited(MouseEvent e){
        
            for(int i=0;i<6;++i){
            
                if(GameCells[i][which] =='.'){
                  
                    CellsLabel[i][which].setIcon(null);
                }
            }    
        }
        
        @Override
        public void mouseClicked(MouseEvent e){
            
            if(isAvailable(which)){
                
                updateBoard(which);
            }             
        }    
    }
    
    
    private class ButtonHandler implements ActionListener{
        
        private final String name;
        
        ButtonHandler(String n){
        
            name =n;     
        }

        @Override
        public void actionPerformed(ActionEvent e) {
        
            if("SingleGame".equals(name)){
            
                ConnectFourGUI.this.remove(Start);
                GameType ='c'; // against 
                initAgainstComputer();
            }
        
            else if("MultiGame".equals(name)){
            
                ConnectFourGUI.this.remove(Start);
                GameType ='p'; // against Player
                initAgainstPlayer();

            }
        
            else if("Setting".equals(name)){
            
                if(GameType == 'c')
                    ConnectFourGUI.this.remove(AgainstComputer);
                else      
                    ConnectFourGUI.this.remove(AgainstPlayer);
          
                initSetting();
            }
        
            else if("Return".equals(name)){
                ConnectFourGUI.this.remove(Setting);
                if(GameType =='c')
                    ConnectFourGUI.this.add(AgainstComputer);
                else 
                    ConnectFourGUI.this.add(AgainstPlayer);
                ConnectFourGUI.this.revalidate();
                ConnectFourGUI.this.repaint();
            }

        
            else if("Home1".equals(name)){
                ConnectFourGUI.this.remove(Setting);            
                deleteBoard();
                initStart();
            }
        
       
            else if("Home2".equals(name)){
            
                ConnectFourGUI.this.remove(Result);
                deleteBoard();
                initStart();
            }
        
            else if("Again".equals(name)){
                ConnectFourGUI.this.remove(Result);           
                deleteBoard();
                if(GameType == 'c')
                    ConnectFourGUI.this.add(AgainstComputer);
                else
                    ConnectFourGUI.this.add(AgainstPlayer);
                ConnectFourGUI.this.revalidate();
                ConnectFourGUI.this.repaint();
            }
        }
    }
}
