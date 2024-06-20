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
	}
	
	private void displayRules() {
		System.out.println("How to Play:");
		
		
	}
}
