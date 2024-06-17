package dynamicWordle;

public class UserLinkedList {
	
	
	public class Node {
		User user;
		Node next;
		
		public Node(User user) {
			this.user = user;
			next = null;
		}
	}
}
