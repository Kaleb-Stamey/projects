package dynamicWordle;

import java.util.LinkedList;

public class Game {
	LinkedList<String> words;
	
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
}
