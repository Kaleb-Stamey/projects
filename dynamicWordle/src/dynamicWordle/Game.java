package dynamicWordle;

import java.util.LinkedList;
import java.util.Scanner;

public class Game {
	private LinkedList<String> words;
	private Scanner myScanner = new Scanner(System.in);
	
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
	
	public int playGame() {
		String word = getWord().toLowerCase();
		int wordLength = word.length();
		char[] wordDisplay = new char[wordLength];
		LinkedList<Character> charsInWord = new LinkedList<>();
		boolean found = false;
		int points = wordLength + 1;
		int numGuesses = 0;
		for(int i = 0; i < wordLength; i++) {
			wordDisplay[i] = '-';
		}
		
		System.out.println("============================================");
		while(!found && numGuesses < wordLength) {
			System.out.printf("\nYou have %d guesses left\n",wordLength - numGuesses);
			System.out.print("Letters in Word: ");
			System.out.println(charsInWord);
			for(int i = 0; i < wordLength; i++) {
				System.out.printf(" %c ",wordDisplay[i]);
			}
			String guess = getGuess(wordLength).toLowerCase();
			numGuesses++;
			points --;
			if(word.equals(guess)) {
				found = true;
			}
			else {
				//i in guess
				for(int i = 0; i < wordLength; i++) {
					//j in word
					for(int j = 0; j < wordLength; j++) {
						//if letter in right position
						if(guess.charAt(i) == word.charAt(j) && i == j) {
							wordDisplay[i] = guess.charAt(i);
							if(!charsInWord.contains(guess.charAt(i))){
								charsInWord.add(guess.charAt(i));
							}
						}
						//if letter right and not in position
						else if(guess.charAt(i) == word.charAt(j)) {
							if(!charsInWord.contains(guess.charAt(i))){
								charsInWord.add(guess.charAt(i));
							}
						}
					}//for j
				}//for i
			}//else
		}//while
		
		if(found) {
			if(numGuesses == 1) {
				System.out.println("Congradulations! You guessed the word in 1 try.");
			}
			else {
				System.out.printf("\nCongradulations! You guessed the word in %d tries.",numGuesses);
			}
			
			
		}
		else {
			System.out.printf("Better luck next time! The word was %s",word);
			points = 0;
		}
		return points;
	}
	
	public void displayRules() {
		System.out.println("How to Play:");
	}
	
	private String getGuess(int length) {
		String guess = "";
		System.out.printf("\nEnter your guess: ");
		boolean validGuess = false;
		while(!validGuess) {
			guess = myScanner.nextLine();
			if(guess.length() == length && words.contains(guess)) {
				validGuess = true;
			}
			else {
				System.out.println("That was not a valid Guess.");
				System.out.print("Enter your guess: ");
			}
		}
		return guess;
	}
}
