package dynamicWordle;


public class UserLinkedList {
	/**
	 * This linked list stores users in alphabetical order.
	 */
	
	private Node head;
	
	//Constructor for this class
	public UserLinkedList() {
		head = null;
	}// constructor
	
	//Adds a user to the Linked List in alphabetical order.
	//Parameter: User user: User to add the the LL
	public void addUser(User user) {
		Node previous = null;
		Node current = head;
		boolean found = false;
		
		if(current == null){
			head = new Node(user);
		}
		else if(current.next == null) {
			Node tempUser = new Node(user);
			if(current.user.getName().compareTo(user.getName()) > 0) {
				tempUser.next = current;
				head = tempUser;
			}
			else {
				current.next = tempUser;
			}
		}
		else {
			while(current != null && !found) {
				if(current.user.getName().compareTo(user.getName()) > 0) {
					found = true;
				}
				else {
					previous = current;
					current = current.next;
				}
			}
			
			if(found) {
				Node tempUser = new Node(user);
				tempUser.next = current;
				previous.next = tempUser;
			}
		}
	}// add user 
	
	//Updates the score for one user
	//Takes in the name of the current user and the score to add 
	public void addScore(String name, int score) {
		Node current = head;
		boolean found = false;
		
		if(head == null) {
			System.out.println("There are no users");
		}
		else {
			while(current != null && !found) {
				if(current.user.getName().equals(name)) {
					found = true;
				}
				else {
					current = current.next;
				}	
			}
			
			if(found) {
				current.user.updateScore(score);
			}
			else {
				System.out.println("User isn't in List");
			}
			
		}
	}//add score 
	
	//Removes a user from the LinkedList
	//Takes in the name of the user to be deleted
	public void removeUser(String name) {
		Node previous = null;
		Node current = head;
		boolean found = false;
		
		if(current == null) {
			System.out.println("There are no users in the list");
		}
		else {
			while(current != null && !found) {
				if(current.user.getName().equals(name)) {
					found = true;
				}
				else {
					previous = current;
					current = current.next;
				}
			}
			
			if(found) {
				previous.next = current.next;
			}
		}
	}//remove user

	public boolean findUser(String name) {
		boolean found = false;
		Node current = head;
		while(!found && current != null) {
			if(current.user.getName().toUpperCase().equals(name.toUpperCase())) {
				found = true;
			}
			else {
				current = current.next;
			}
		}
		return found;
	}
	
	public int getScore(String name) {
		int score = 0;
		boolean found = false;
		Node current = head;
		while(!found && current != null) {
			if(current.user.getName().toUpperCase().equals(name.toUpperCase())) {
				found = true;
			}
			else {
				current = current.next;
			}
		}
		if(found) {
			score = current.user.getScore();
		}
		return score;
	}
	
	public void displayAllData() {
		Node tempNode = head;
		if(tempNode == null) {
			System.out.println("There is no data yet.");
		}
		else {
			while(tempNode != null) {
				System.out.printf("\n%s",tempNode.user.toString());
				tempNode = tempNode.next;
			}
		}
	}
	//Inner node class for linked list
	public class Node {
		User user;
		Node next;
		
		public Node(User user) {
			this.user = user;
			next = null;
		}
	}//node
}
