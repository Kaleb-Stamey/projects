package dynamicWordle;

import java.util.LinkedList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

/**
 * Main class of the program 
 * Methods: main, yesNo, getValidString, userLogin
 */
public class dynamicWordle {
	private static Scanner myScanner = new Scanner(System.in);
	
	/**
	 * Main Method
	 * @exception FileNotFoundException
	 * @exception IOException
	 */
	public static void main(String[] args) throws FileNotFoundException, IOException{
		//Initializing variables 
		LinkedList<String> myWordList = new LinkedList<>();
		File myWordFile = new File("words.txt");
		Scanner readFile = new Scanner(myWordFile);
		UserLinkedList myUsers = new UserLinkedList();
	
		while(readFile.hasNext()) {
			myWordList.add(readFile.next());
		}
		
		Game myGame = new Game(myWordList);
		boolean isSentinel = false;
		
		while(!isSentinel) {
			//signing in/up users and starting the game
			System.out.print("Are you an Admin? (Yes/No): ");
			boolean adminAnswer = yesNo();
			if(adminAnswer) {
				myUsers.displayAllData();
				System.out.printf("\nDo you want to shut down the game? (Yes/No): ");
				isSentinel = yesNo();
				if(isSentinel) {
					System.out.println("Shutting down...");
				}
			}
			else {
				String currentUser = userLogin(myUsers);
				
				System.out.printf("\nWelcome to DynamicWordle %s!\n", currentUser);
				System.out.print("Would you like to hear how to play? (Yes/No): ");
				boolean hereHowToPlay = yesNo();
				if(hereHowToPlay) {
					myGame.displayRules(); 
				}
				
				boolean keepPlaying = true;
				while(keepPlaying) {
					int size = getValidInt();
					System.out.printf("Your current score is %d\n",myUsers.getScore(currentUser));
					myUsers.addScore(currentUser,myGame.playGame(size));
					System.out.printf("\nDo you want to keep Playing?: ");
					keepPlaying = yesNo();
				}
				
			}
			
		}
		
		myScanner.close();
		readFile.close();
	}	
	
	/**
	 * This function gets a valid integer from the user
	 * @return Integer: valid integer obtained from user
	 */
	public static int getValidInt() {
		int maxWordLength = 10;
		int minWordLength = 0; 
		boolean gotValidInt = false;
		int validInt = 0;
		while(!gotValidInt) {
			System.out.print("Please enter an integer (1-10): ");
			validInt = myScanner.nextInt();
			if(validInt <= maxWordLength && validInt > minWordLength) {
				gotValidInt = true;
			}
			else {
				System.out.printf("\nError: you have not entered a valid int\n");
			}
		}
		myScanner.nextLine();
		return validInt;
	}
	
	/**
	 * Loops until valid input from user 
	 * @return boolean for yes or no
	 */
	public static boolean yesNo() {
		boolean myBool = false;
		boolean hasAnswer = false;
		
		while(!hasAnswer) {
			String myStr = myScanner.nextLine();
			if(myStr.toUpperCase().equals("YES")) {
				myBool = true;
				hasAnswer = true;
			}
			else if(myStr.toUpperCase().equals("NO")) {
				myBool = false;
				hasAnswer = true;
			}
			else {
				System.out.print("Error: Please Enter Yes OR No: ");
			}

		}
		
		return myBool;
	}
	
	/**
	 * Loops until valid user string is entered
	 * @return String: the users valid string
	 */
	public static String getValidString() {
		boolean gotValid = false;
		String validString = "";
		while(!gotValid) {
			validString = myScanner.nextLine();
			System.out.printf("Is %s correct? (Yes/No): ", validString);
			boolean correct = yesNo();
			if(correct) {
				gotValid = true;
			}
			else {
				System.out.print("Please enter again: ");
			}
		}
		
		return validString;
	}
	
	/**
	 * Allows one user to log in or sign up depending on if name is in 
	 * UserLinkedList
	 * @param myUsers: A linked list class made for holding users
	 * @return String: A string containing the name of the user
	 */
	public static String userLogin(UserLinkedList myUsers) {
		System.out.println("============================================");
		System.out.print("Please Enter your name First and Last: ");
		String name = getValidString();
		boolean found = myUsers.findUser(name);
		
		if(!found) {
			User tempUser = new User(name);
			myUsers.addUser(tempUser);
		}
		if(found) {
			System.out.println("you already have an account!");
		}
	
		return name;	
	}
}
