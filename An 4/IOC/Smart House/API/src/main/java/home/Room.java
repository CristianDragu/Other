package home;

public class Room {

	private String name;
	private State light;
	private State windows;
	private double temperature;
	
	public Room(){
		
	}
	
	public Room(String name, State light, double temperature, State windows){
		this.name = name;
		this.light = light;
		this.temperature = temperature;
		this.windows = windows;
	}
	
	public String getName() {
		return name;
	}
	
	public State getLight() {
		return light;
	}
	
	public double getTemperature() {
		return temperature;
	}
	
	public void setLight(State state) {
		this.light = state;
	}
	
	public void setTemperature(Double temperature) {
		this.temperature = temperature;
	}
	
	public State getWindows() {
		return this.windows;
	}
	
	public void setWindows(State state) {
		this.windows = state;
	}
}
