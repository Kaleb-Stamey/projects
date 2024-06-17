package dynamicWordle;

import java.util.LinkedList;

public class dynamicWordle {
		public static void main(String[] args) {
			LinkedList<String> myList = new LinkedList<>();
			Game myGame = new Game(myList);
			myGame.playGame();
		}		
}
