package dynamicWordle;

import java.util.LinkedList;
import java.util.Scanner;

public class Game {
	LinkedList<String> words;
	Scanner myScanner = new Scanner(System.in);
	
	public Game(LinkedList<String> words) {
		this.words = words;
	}
	
	public String getWord() {
		int randNum = (int)(Math.random() * (words.size()));
		
		if(randNum > words.size()) {
			randNum = words.size();
		}
		
		return words.get(randNum);
	}
	
	public void playGame() {
		System.out.println("Welcome to DynamicWordle!");
		System.out.print("Would you like to hear how to play? (Yes || no): ");
		String answer = myScanner.nextLine();
		if(answer.toUpperCase().equals("YES")) {
			displayRules(); 
		}
		
		//use get a random word and setup the game based on that word
		//after each round as the user if they want to play again 
		//game ends after they guess the word or run out of tries
		/*
		 * Can use a file containing all english words and if guess not in words than 
		 * make the user guess again ( this wouldn't get rid of a turn)
		 */
		
	}
	
	private void displayRules() {
		System.out.println("How to Play:");
		
		
	}
}
