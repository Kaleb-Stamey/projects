package dynamicWordle;

public class User {
	private String name;
	private int score;
	
	public User(String name) {
		this.name = name;
		score = 0;
	}
	
	public String getName() {
		return name;
	}
	
	public int getScore() {
		return score;
	}
	
	public void updateScore(int score) {
		this.score += score;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	@Override
	public String toString() {
		return String.format("\nName: %s Points: %d", name, score);
	}
}
