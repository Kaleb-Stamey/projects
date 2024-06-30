package dynamicWordle;

import java.util.LinkedList;
import java.util.Scanner;

/**
 * Represents one game, can be called multiple times
 * Methods: getWord, playGame, displayRules, getGuess
 */
public class Game {
	private LinkedList<String> words;
	private Scanner myScanner = new Scanner(System.in);
	
	/**
	 * This is the constructor for Game Class
	 * @param words: A linked list containing your words
	 */
	public Game(LinkedList<String> words) {
		this.words = words;
	}
	
	/**
	 * Gets one word at random from the words linked list
	 * @return String: The random word
	 */
	public String getWord() {
		int randNum = (int)(Math.random() * (words.size()));
		
		if(randNum > words.size()) {
			randNum = words.size();
		}
		
		return words.get(randNum);
	}
	
	/**
	 * This represents one game and each game that is played will yield some points
	 * @return Integer: The number of points obtained from that round
	 */
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
	
	/**
	 * This function displays the rules for the game
	 * @return void
	 */
	public void displayRules() {
		System.out.println("How to Play:");
		System.out.printf("\nEach round you are given a random word.\n\n"
				+ "The length of this word determines the number of guesses you get.\n\n"
				+ "If the Number of guesses is reached and you have not guessed the word you lose.\n\n"
				+ "Each guess MUST be a valid word that is the correct length."
				+ "If you guess the word before your guesses run out points are added to your total.\n\n"
				+ "Invalid guesses do not count as a real guess\n\n");
	}
	
	/**
	 * Gets a valid guess from the user
	 * @param length: Length of the current word
	 * @return String: The users guess
	 */
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
