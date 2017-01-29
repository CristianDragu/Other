package hello;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import home.*;

@RestController
public class HouseController {
    
	House house;
	
	public HouseController() {
		house = new House();
		house.addRoom(new Room("bucatarie", State.ON, 40, State.OFF));
		house.addRoom(new Room("sufragerie", State.OFF, 33, State.ON));
		house.addRoom(new Room("dormitor", State.OFF, 32, State.ON));
	}
	
    @RequestMapping(path="/rooms", method=RequestMethod.GET)
    public List<Room> getRooms() {
    	return house.getRooms();
    }
    
    @RequestMapping(path="/room", method=RequestMethod.GET)
    public Room getRoom(@RequestParam(value="name", defaultValue="") String name) {
    	return house.getRoom(name);
    }
    
    @RequestMapping(path="/rooms-lights-on", method=RequestMethod.GET)
    public List<Room> getRoomsWithLightsOn() {
    	List <Room> lightsOnRooms = new ArrayList<Room>();
    	
    	for(Room room : house.getRooms())
    		if(room.getLight() == State.ON)
    			lightsOnRooms.add(room);
    	
    	return lightsOnRooms;
    }
    
    @RequestMapping(path="/turn-off-lights", method=RequestMethod.POST)
    public void turnOffLights() {
    	for(Room room : house.getRooms()) {
			if(room.getLight() == State.ON)
				room.setLight(State.OFF);
		}
    }
    
    @RequestMapping(path="/switch-lights-room", method=RequestMethod.POST)
    public void turnOffLightsByRoom(@RequestParam(value="name", defaultValue="") String name) {
    	for(Room room : house.getRooms())
    		if(room.getName().equals(name))
    			if(room.getLight() == State.ON)
    				room.setLight(State.OFF);
    			else
    				room.setLight(State.ON);
    }
    
    @RequestMapping(path="/rooms-windows-on", method=RequestMethod.GET)
    public List<Room> getRoomsWithOpenedWindows() {
    	List<Room> rooms = new ArrayList<Room>();
    	
    	for(Room room : house.getRooms())
    		if(room.getWindows() == State.ON)
    			rooms.add(room);
    	
    	return rooms;
    }
    
    @RequestMapping(path="/close-windows", method=RequestMethod.POST)
    public void closeWindows() {
    	for(Room room : house.getRooms()) {
			if(room.getWindows() == State.ON)
				room.setWindows(State.OFF);
		}
    }
    
    @RequestMapping(path="/close-windows-room", method=RequestMethod.POST)
    public void closeWindowsByRoom(@RequestParam(value="name", defaultValue="") String name) {
    	for(Room room : house.getRooms())
    		if(room.getName().equals(name) && room.getWindows() == State.ON)
    			room.setWindows(State.OFF);
    }
    
    @RequestMapping(path="/open-windows-room", method=RequestMethod.POST)
    public void openWindowsByRoom(@RequestParam(value="name", defaultValue="") String name) {
    	for(Room room : house.getRooms())
    		if(room.getName().equals(name) && room.getWindows() == State.OFF)
    			room.setWindows(State.ON);
    }
    
    @RequestMapping(path="/people-in-house", method=RequestMethod.GET)
    public int getPeopleInHouse() {
    	return house.getpeopleInHouse();
    }
}
