package dynamicWordle;

import java.util.LinkedList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class dynamicWordle {
	private static Scanner myScanner = new Scanner(System.in);
	
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
					System.out.printf("Your current score is %d\n",myUsers.getScore(currentUser));
					myUsers.addScore(currentUser,myGame.playGame());
					System.out.printf("\nDo you want to keep Playing?: ");
					keepPlaying = yesNo();
				}
				
			}
			
		}
		
		myScanner.close();
		readFile.close();
	}	
	
	//used to get (Yes || No) input from the user.
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
	
	//function for user Sign up
	//Returns the name of the current user
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
