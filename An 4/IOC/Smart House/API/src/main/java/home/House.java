package home;

import java.util.ArrayList;
import java.util.List;

public class House {

	private List<Room> rooms;
	private int peopleInHouse;
	
	public House() {
		rooms = new ArrayList<Room>();
		peopleInHouse = 1;
	}
	
	public House(int peopleInHouse) {
		rooms = new ArrayList<Room>();
		this.peopleInHouse = peopleInHouse;
	}
	
	public int getpeopleInHouse() {
		return peopleInHouse;
	}
	
	public void addRoom(Room room) {
		rooms.add(room);
	}
	
	public List<Room> getRooms() {
		return rooms;
	}
	
	public Room getRoom(String name) {
		for (Room room : rooms) 
			if(room.getName().equals(name))
				return room;
		return null;
	}
}
