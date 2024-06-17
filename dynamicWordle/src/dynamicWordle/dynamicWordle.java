package dynamicWordle;

import java.util.LinkedList;

public class dynamicWordle {
		public static void main(String[] args) {
			LinkedList<String> myList = new LinkedList<>();
			
			for(int i = 0; i < 10; i++) {
				myList.add(String.format("MyString + %d", i));
			}
			
			Game myGame = new Game(myList);
			
			for(int i = 0; i < 100; i++) {
				System.out.println(myGame.getWord());
			}
		}
}
