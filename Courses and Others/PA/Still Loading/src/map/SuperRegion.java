/**
 * Warlight AI Game Bot
 *
 * Last update: January 29, 2015
 *
 * @author Jim van Eeden
 * @version 1.1
 * @License MIT License (http://opensource.org/Licenses/MIT)
 */

package map;

import java.util.LinkedList;
import bot.BotState;
import java.util.ArrayList;

public class SuperRegion {

	private int id;
	private int armiesReward;
	private int nrwastelands = 0;
	int armyOnSuperRegion = 0;
	private LinkedList<Region> subRegions;

	public SuperRegion(int id, int armiesReward) {
		this.id = id;
		this.armiesReward = armiesReward;
		subRegions = new LinkedList<Region>();
	}

	public void addSubRegion(Region subRegion) {
		if (!subRegions.contains(subRegion))
			subRegions.add(subRegion);
	}

	/**
	 * @return A string with the name of the player that fully owns this
	 *         SuperRegion
	 */
	public String ownedByPlayer() {
		String playerName = subRegions.getFirst().getPlayerName();
		for (Region region : subRegions) {
			if (!playerName.equals(region.getPlayerName()))
				return null;
		}
		return playerName;
	}

	/**
	 * @return The id of this SuperRegion
	 */
	public int getId() {
		return id;
	}

	/**
	 * @return The number of armies a Player is rewarded when he fully owns this
	 *         SuperRegion
	 */
	public int getArmiesReward() {
		return armiesReward;
	}

	public void incNrWastelands() {
		this.nrwastelands++;
	}

	public int getArmyOnSuperRegion() {
		return armyOnSuperRegion;
	}

	public double getQuality() {
		
		double quality;
		for (int i = 0; i < subRegions.size(); i++) {
			armyOnSuperRegion += 2;
		}
		armyOnSuperRegion = armyOnSuperRegion + 4 * nrwastelands;
		quality = armiesReward / (float) (armyOnSuperRegion);

		return (quality);
	}

	/*
	 * public LinkedList getRegions() { return subRegions; }
	 */
	/**
	 * @return A list with the Regions that are part of this SuperRegion
	 */
	public LinkedList<Region> getSubRegions() {
		return subRegions;
	}
}
