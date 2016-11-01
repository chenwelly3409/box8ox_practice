package test;
import java.awt.*;        // Container, FlowLayout      
import java.awt.event.*;  // ActionEvent, ActionListener

import javax.swing.*;     // JApplet, JButton, JLabel, JTextField


public class test extends JApplet implements ActionListener {
	
	boolean firstRoll = true;  // true if first roll of dice
	
	int play1_sum = 0;
	int play2_sum = 0;
	
	int gameStatus = 0; // game not over yet
	
	// graphical user interface components                
	JLabel die1Label, die2Label, play1Label, play2Label;
	JTextField die1Field, die2Field, play1Field, play2Field;
	JButton rollButton;  
	
	JLabel stupid_player;
	JTextField player_input;
	JButton which;
	Dialog dialog;
	Frame f;
	String input;
	
	// set up GUI components
	public void init(){
		// obtain content pane and change its layout to FlowLayout
		Container container = getContentPane();                   
		container.setLayout( new FlowLayout() );                  
		
		// create label and text field for die 1
		die1Label = new JLabel( "Die 1" );      
		container.add( die1Label );             
		die1Field = new JTextField( 10 );       
		die1Field.setEditable( false );         
		container.add( die1Field );             
		// create label and text field for die 2
		die2Label = new JLabel( "Die 2" );
		container.add( die2Label );
		die2Field = new JTextField( 10 );
		die2Field.setEditable( false );
		container.add( die2Field );
		
		// create label and text field for sum
		play1Label = new JLabel( "Play1 sum: " );
		container.add( play1Label );
		play1Field = new JTextField( 10 );
		play1Field.setEditable( false );
		container.add( play1Field );
		
		// create label and text field for point
		play2Label = new JLabel( "Play2 sum: " );
		container.add( play2Label );
		play2Field = new JTextField( 10 );
		play2Field.setEditable( false );
		container.add( play2Field );
		
		// create button user clicks to roll dice
		rollButton = new JButton( "Roll Dice" ); 
		rollButton.addActionListener( this );    
		container.add( rollButton );             
		
		input=JOptionPane.showInputDialog("請輸入1 or 2");
		showStatus( "roll dice. You are playr" + input + "." );
		
	}// end method init

	
	// process one roll of dice
	public void actionPerformed( ActionEvent actionEvent ){
		rollDice();  // roll dice
		
		
		displayMessage();   // display message indicating game status

	}// end method actionPerformed
	
	
	public void rollDice(){
		// pick random die values
		int die1 = 1 + ( int ) ( Math.random() * 6 );  
		int die2 = 1 + ( int ) ( Math.random() * 6 );
		
		// display results in textfields
		die1Field.setText( Integer.toString( die1 ) );
		die2Field.setText( Integer.toString( die2 ) );
		
		play1_sum = play1_sum + die1;
		play2_sum = play2_sum + die2;
		
		play1Field.setText( Integer.toString( play1_sum ) );
		play2Field.setText( Integer.toString( play2_sum ) );
		
		
	}// end method rollDice
	
	
	// determine game status; display appropriate message in status bar
	public void displayMessage(){
		// game should continue
		
		
		if ( gameStatus == 2 ) {
			if ( play1_sum > play2_sum )
				showStatus( "Player1 wins!!" );
			else if( play2_sum > play1_sum )
				showStatus( "Player2 wins!!" );
			else 
				showStatus( "Duce!!" );

			play1_sum = 0;
			play2_sum = 0;
			gameStatus = 0;
			firstRoll = true;  // next roll is first roll of new game
			
			input=JOptionPane.showInputDialog("請輸入1 or 2");
			showStatus( "roll dice. You are playr" + input + "." );
			
		}
		else { // game won or lost
			gameStatus++;
			showStatus( "roll dice. You are playr" + input + "." );
			
		}// end else part of if...else


	}// end method displayMessage
	
	

}// end class Craps
