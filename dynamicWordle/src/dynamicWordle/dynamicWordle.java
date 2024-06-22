package dynamicWordle;

import java.util.LinkedList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;


public class dynamicWordle {
	static Scanner myScanner = new Scanner(System.in);
	
	public static void main(String[] args) throws FileNotFoundException, IOException{
		//Initializing variables 
		LinkedList<String> myWordList = new LinkedList<>();
		File myWordFile = new File("words.txt");
		Scanner readFile = new Scanner(myWordFile);
		
		while(readFile.hasNext()) {
			myWordList.add(readFile.next());
		}
		
		Game myGame = new Game(myWordList);
		UserLinkedList myUsers = new UserLinkedList();
		
		//signing in/up users and starting the game
		
		startGame(myGame, myUsers);
		
	
			
		myScanner.close();
		readFile.close();
	}	
	
	//function for user login / sign up...
	public static void signUpOrIn(UserLinkedList myUsers) {
		
	}
		
	//function for playing the game...
		
	public static void startGame(Game myGame, UserLinkedList myUsers) {
		System.out.println("Welcome to DynamicWordle!");
		System.out.print("Would you like to hear how to play? (Yes || no): ");
		String answer = myScanner.nextLine();
		if(answer.toUpperCase().equals("YES")) {
			myGame.displayRules(); 
		}
		myGame.playGame();
	}
		
		
}
