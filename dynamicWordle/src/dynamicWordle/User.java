package dynamicWordle;

/**
 * This class represents one user.
 * Each user has a String: name and a Integer: score
 * Methods: getName, getScore, updateScore, setName, toString
 */
public class User {
	private String name;
	private int score;
	
	/**
	 * constructor for User class
	 * @param name: Name of the user
	 */
	public User(String name) {
		this.name = name;
		score = 0;
	}
	
	/**
	 * @return String: The users name
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * @return Integer: users score
	 */
	public int getScore() {
		return score;
	}
	
	/**
	 * adds score to the users total score
	 * @param score: Score to add
	 */
	public void updateScore(int score) {
		this.score += score;
	}
	
	/**
	 * sets the name for the user
	 * @param name: New user name
	 */
	public void setName(String name) {
		this.name = name;
	}
	
	/**
	 * Method that returns a formatted string
	 * @return String: Formatted string
	 */
	@Override
	public String toString() {
		return String.format("\nName: %s Points: %d", name, score);
	}
}
