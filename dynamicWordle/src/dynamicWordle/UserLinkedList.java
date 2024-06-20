package dynamicWordle;


// This class is to store the user data for each user
// Stores the users in alphabetical order
// Used when logging a user in.
public class UserLinkedList {
	Node head;
	
	public UserLinkedList() {
		head = null;
	}
	
	public void addUser(User user) {
		Node previous = null;
		Node current = head;
		
		if(current == null){
			head = new Node(user);
		}
		
		else {
			//add the node in alphabetical order
		}
	}
	
	public void addScore(String name) {
		// add score
	}
	
	public void removeUser(String name) {
		//remove user 
	}
	
	
	
	public class Node {
		User user;
		Node next;
		
		public Node(User user) {
			this.user = user;
			next = null;
		}
	}
}
