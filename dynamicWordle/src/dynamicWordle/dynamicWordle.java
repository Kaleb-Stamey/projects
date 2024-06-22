package dynamicWordle;

import java.util.LinkedList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;


public class dynamicWordle {
		public static void main(String[] args) throws FileNotFoundException, IOException{
			LinkedList<String> myWordList = new LinkedList<>();
			
			//Adds Words to linked list using a text file
			File myWordFile = new File("words.txt");
			Scanner readFile = new Scanner(myWordFile);
			
			while(readFile.hasNext()) {
				myWordList.add(readFile.next());
			}
			
			for(int i = 0; i < myWordList.size(); i++) {
				System.out.println(myWordList.get(i));
			}
			
			Game myGame = new Game(myWordList);
			myGame.playGame();
			
			readFile.close();
		}		
}
