/**
 * Warlight AI Game Bot
 *
 * Last update: January 29, 2015
 *
 * @author Jim van Eeden
 * @version 1.1
 * @License MIT License (http://opensource.org/Licenses/MIT)
 */

package bot;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.Vector;
import map.Map;

import map.Region;
import map.SuperRegion;
import move.AttackTransferMove;
import move.PlaceArmiesMove;

public class BotStarter implements Bot {

	private Set<Region> regionCheck;
	private Set<Region> attacked;
	private HashMap<SuperRegion, ArrayList<Region>> wastelandsMap = new HashMap<SuperRegion, ArrayList<Region>>();

	public int numberOfWastelands(Region region) {
		if (wastelandsMap.containsKey(region.getSuperRegion()))
			return wastelandsMap.get(region.getSuperRegion()).size();
		else
			return 0;
	}

	@Override
	public Region getStartingRegion(BotState state, Long timeOut) {

		ArrayList<Region> regions = state.getPickableStartingRegions();
		ArrayList<Region> wastelands = state.getWasteLands();
		ArrayList<Region> regionWithWastelands = new ArrayList<Region>();
		ArrayList<Region> regionWithoutWastelands = new ArrayList<Region>();
		ArrayList<Region> regionWithoutBonus = new ArrayList<Region>();

		for (Region wasteland : wastelands) {
			if (!wastelandsMap.containsKey(wasteland.getSuperRegion())) {
				ArrayList<Region> aux = new ArrayList();
				aux.add(wasteland);
				wastelandsMap.put(wasteland.getSuperRegion(), aux);
			} else
				wastelandsMap.get(wasteland.getSuperRegion()).add(wasteland);
		}

		/****************************************** CREARE VECTORI CU/FARA WASTES *******************************************/
		for (int i = 0; i < regions.size(); i++) {
			if (regions.get(i).getSuperRegion().getArmiesReward() == 0)
				regionWithoutBonus.add(regions.get(i));
			else if (wastelandsMap.containsKey(regions.get(i).getSuperRegion())) {
				regionWithWastelands.add(regions.get(i));
			} else
				regionWithoutWastelands.add(regions.get(i));
		}

		/****************************************** COMPARATORI *******************************************/
		if (regionWithoutWastelands != null)
			Collections.sort(regionWithoutWastelands, new Comparator<Region>() {

				@Override
				public int compare(Region o1, Region o2) {
					if (o1.getSuperRegion().getSubRegions().size() - 
							o2.getSuperRegion().getSubRegions().size() == 0)
						return o2.getSuperRegion().getArmiesReward() - 
								o1.getSuperRegion().getArmiesReward();
					else
						return o1.getSuperRegion().getSubRegions().size() - 
								o2.getSuperRegion().getSubRegions().size();
				}

			});

		if (regionWithWastelands != null)
			Collections.sort(regionWithWastelands, new Comparator<Region>() {

				@Override
				public int compare(Region o1, Region o2) {
					if (numberOfWastelands(o1) == numberOfWastelands(o2))
						return o2.getSuperRegion().getArmiesReward() - 
								o1.getSuperRegion().getArmiesReward();
					else
						return numberOfWastelands(o1) - numberOfWastelands(o2);
				}

			});

		if (regionWithoutBonus != null)
			Collections.sort(regionWithoutBonus, new Comparator<Region>() {

				@Override
				public int compare(Region o1, Region o2) {
					if (numberOfWastelands(o1) == numberOfWastelands(o2))
						return o1.getSuperRegion().getSubRegions().size() - 
								o2.getSuperRegion().getSubRegions().size();
					else
						return numberOfWastelands(o1) - numberOfWastelands(o2);
				}

			});

		if (regionWithoutWastelands.isEmpty() == false) {
			return regionWithoutWastelands.get(0);
		} else if (regionWithWastelands.isEmpty() == false) {
			return regionWithWastelands.get(0);
		} else
			return regionWithoutBonus.get(0);

	}


	//------------------------------------PLACE ARMY ---------------------------------////

	private boolean hasEnemyNear(Region r, String playerName) {
		LinkedList<Region> neighbors = r.getNeighbors();

		for(int i = 0; i < neighbors.size(); i++)
			if(!neighbors.get(i).ownedByPlayer(playerName))
				return true;

		return false;
	}
//Verifica daca o SuperRegiune are cel putin o regiune controlata de adversar
	private boolean isSuperRegionOwnedByEnemy(SuperRegion superRegion, String playerName) {
		LinkedList<Region> regions = superRegion.getSubRegions();
		for (int i = 0; i < regions.size(); i++)
			if (regions.get(i).ownedByPlayer(playerName))
				return true;
		return false;
	}
//Vede cate regiuni din SuperRegiune nu detin
	private int numberNotControledSuperRegion(SuperRegion superRegion, String playerName) {
		LinkedList<Region> regions = superRegion.getSubRegions();
		int nrControlled = 0;

		for (int i = 0; i < regions.size(); i++)
			if (regions.get(i).ownedByPlayer(playerName))
				nrControlled++;

		return regions.size() - nrControlled;
	}
        
        //Afla numarul de vecini din aceeasi superregiune a unei regiuni
        private int numberNeighbouringRegionsWithinSR(Region regiune, String playerName) {
            LinkedList<Region> myNeighbours = regiune.getNeighbors();
            int nr=0;
            for (int i = 0; i < myNeighbours.size(); i++)
                if ( myNeighbours.get(i).getSuperRegion().equals(regiune.getSuperRegion()) &&
						!myNeighbours.get(i).ownedByPlayer(playerName) ) 
                    nr++;
            return nr;
        }

	public ArrayList<PlaceArmiesMove> getPlaceArmiesMoves(BotState state, Long timeOut) {

		ArrayList<PlaceArmiesMove> placeArmiesMoves = new ArrayList<PlaceArmiesMove>();
		String myName = state.getMyPlayerName();
		String hisName = state.getOpponentPlayerName();
		int armiesLeft = state.getStartingArmies();
		LinkedList<SuperRegion> visibleSuperRegions = state.getVisibleMap().getSuperRegions();

		LinkedList<SuperRegion>myBorderingSuperRegions = new LinkedList<SuperRegion>();
//Introduc in LinkedList SuperRegiunile ce nu le detin total ce fie au bonus fie au inamic
		for (int i = 0; i < visibleSuperRegions.size(); i++) {
			if ( (numberNotControledSuperRegion(visibleSuperRegions.get(i), myName) != 0 && 
					visibleSuperRegions.get(i).getArmiesReward() > 0 ) || 
					( numberNotControledSuperRegion(visibleSuperRegions.get(i), myName) != 0 && 
					isSuperRegionOwnedByEnemy(visibleSuperRegions.get(i), hisName)) )
				myBorderingSuperRegions.add(visibleSuperRegions.get(i));
		}

		if (myBorderingSuperRegions != null)
			Collections.sort(myBorderingSuperRegions, new Comparator<SuperRegion>() {
//Sortez crescator dupa numarul de regiune ce nu controlez si descrescator dupa bonus
		  @Override
		  public int compare(SuperRegion o1, SuperRegion o2) {
		    if (numberNotControledSuperRegion(o1,myName) - 
		    		numberNotControledSuperRegion(o2,myName) == 0)
			  return o2.getArmiesReward() - o1.getArmiesReward();
			else
			  return numberNotControledSuperRegion(o1,myName) - 
					  numberNotControledSuperRegion(o2,myName);
				}

			});
//daca exista superegiune ce detinem 0% din ele
		if (numberNotControledSuperRegion(
				myBorderingSuperRegions.get(myBorderingSuperRegions.size()-1), myName)
				== myBorderingSuperRegions.get(
						myBorderingSuperRegions.size()-1).getSubRegions().size()) {
			//Iau SuperRegiunile pe rand
			for (int j = 0; j < myBorderingSuperRegions.size(); j++) {
				if (armiesLeft == 0)
					break;
				//Daca o superregiune e detinuta partial de mine
				if (numberNotControledSuperRegion(myBorderingSuperRegions.get(j), myName) !=
						myBorderingSuperRegions.get(j).getSubRegions().size()) {
                                    
					LinkedList<Region> tempRegions = myBorderingSuperRegions.get(j).getSubRegions();
                    LinkedList<Region> subRegions = new LinkedList<Region>();
                                        
                    for (int i = 0; i < tempRegions.size(); i++) {
                        if ( numberNeighbouringRegionsWithinSR(tempRegions.get(i), myName) > 0)
                            subRegions.add(tempRegions.get(i));
                    }
                    
					if (subRegions.size() > 0)
					Collections.sort(subRegions, new Comparator<Region>() {
					//Sortez crescator dupa numarul de vecini di aceeasi SuperRegiune
						@Override
						public int compare(Region o1, Region o2) {
							return numberNeighbouringRegionsWithinSR(o1,myName) - 
									numberNeighbouringRegionsWithinSR(o2,myName);
									}
					});
                                        
					//Gasesc una cu inamici prin jur
					for(int i = 0; i < subRegions.size(); i++) 
						if (hasEnemyNear(subRegions.get(i), myName) &&
								subRegions.get(i).ownedByPlayer(myName)) {
							LinkedList<Region> neighboringSubRegions = subRegions.get(i).getNeighbors();
							int enemyArmy = 0;
							//Aflu numarul de inamici din jur
							for (int k = 0; k < neighboringSubRegions.size(); k++) 
								if (!neighboringSubRegions.get(k).ownedByPlayer(myName)) 
									enemyArmy += neighboringSubRegions.get(k).getArmies();
							
							enemyArmy = (int) (enemyArmy * 1.5) - subRegions.get(i).getArmies() + 1;
							//Adaug in regiune
							if (armiesLeft > enemyArmy) {
								placeArmiesMoves.add(new PlaceArmiesMove(
										myName, 
										subRegions.get(i), 
										enemyArmy));
								subRegions.get(i).updateArmies(enemyArmy);
								armiesLeft -= enemyArmy;
							}
							else {
								placeArmiesMoves.add(new PlaceArmiesMove(
										myName,
										subRegions.get(i),
										armiesLeft));
								subRegions.get(i).updateArmies(armiesLeft);
								armiesLeft = 0;
							}
							//Trec la urmatoarea SuperRegiune
							break;
						}                              

				}
				//Daca nu controlez deloc aceea superRegiune
				else {
					LinkedList<Region> subRegions = myBorderingSuperRegions.get(j).getSubRegions();
					//Iau pe rand regiunile 
					for (int i = 0; i < subRegions.size(); i++) {
						if (armiesLeft == 0) 
							break;
						LinkedList<Region> neighboringSubRegions = subRegions.get(i).getNeighbors();
						//Caut prin vecini
						for (int k = 0; k < neighboringSubRegions.size(); k++) {
							if (armiesLeft == 0) 
								break;
							//Pana gasesc o regiune detinuta de mine si pun restul de armata acolo
							if (neighboringSubRegions.get(k).ownedByPlayer(myName)) {
								LinkedList<Region> myNeighbours = neighboringSubRegions.get(k).getNeighbors();
								int enemyArmy = 0;
                                                                
								for (int o = 0; o < myNeighbours.size(); o++)
									if (!myNeighbours.get(o).ownedByPlayer(myName)) {
                                        enemyArmy += myNeighbours.get(o).getArmies();
                                                                            
								}
								
								enemyArmy = (int) (enemyArmy * 1.5) - subRegions.get(i).getArmies() + 1;
                                 
								if (armiesLeft > enemyArmy) {
									placeArmiesMoves.add(new PlaceArmiesMove(
											myName, 
											neighboringSubRegions.get(k), 
											enemyArmy));
									neighboringSubRegions.get(k).updateArmies(enemyArmy);
									armiesLeft -= enemyArmy;
								}
								else {						
									placeArmiesMoves.add(new PlaceArmiesMove(
											myName, 
											neighboringSubRegions.get(k), 
											armiesLeft));
									neighboringSubRegions.get(k).updateArmies(armiesLeft);
									armiesLeft = 0; 
								}
								break;
							}
						}
					}
				}
			}

		}
		//Daca toate SuperRegiunele sunt detinute partial sau total
		else {
			while(armiesLeft>0) {
				//Iau SuperRegiunile pe rand
				for (int j = 0; j < myBorderingSuperRegions.size(); j++) {
					if (armiesLeft == 0)
						break;   	               
					LinkedList<Region> subRegions = myBorderingSuperRegions.get(j).getSubRegions();
					//Iau pe rand regiunile
					for(int i = 0; i < subRegions.size(); i++)
						//Gasesc una cu inamici
						if (hasEnemyNear(subRegions.get(i),myName) &&
								subRegions.get(i).ownedByPlayer(myName)) {
							LinkedList<Region> neighboringSubRegions = subRegions.get(i).getNeighbors();
							int enemyArmy = 0;
							//Aflu numarul de inamici din jur
							for (int k = 0; k < neighboringSubRegions.size(); k++) 
								if (!neighboringSubRegions.get(k).ownedByPlayer(myName)) 
									enemyArmy += neighboringSubRegions.get(k).getArmies();

							enemyArmy = (int) (enemyArmy * 1.5) + 1;
							//Pun in regiune
							if (armiesLeft > enemyArmy) {
								placeArmiesMoves.add(new PlaceArmiesMove(
										myName, 
										subRegions.get(i), 
										enemyArmy));
								subRegions.get(i).updateArmies(enemyArmy);
								armiesLeft -= enemyArmy;
							}
							else {
								placeArmiesMoves.add(new PlaceArmiesMove(myName, 
																		 subRegions.get(i), 
																		 armiesLeft));
								subRegions.get(i).updateArmies(armiesLeft);
								armiesLeft = 0;
							}
							//Trec la urmatoarea SuperRegiune
							break;
						}    	                    
				}		
			//Daca a mai ramas armata repet
			}
		}

		return placeArmiesMoves;
	}


	public Region makePath(LinkedList<Region> path, 
			LinkedList<Region> fathers, 
			Region start, 
			Region region) {
		if (fathers.get(path.indexOf(region)) == start)
			return region;
		else
			return makePath(path, fathers, start, fathers.get(path.indexOf(region)));
	}

	public ArrayList<AttackTransferMove> deployOnFrontier(LinkedList<Region> myRegions, 
														  String myName){

		ArrayList<AttackTransferMove> attackTransferMoves = new ArrayList<AttackTransferMove>();

		for(int i = 0; i < myRegions.size(); i++){
			if(myRegions.get(i).getArmies() > 1 && myRegions.get(i).ownedByPlayer(myName)){
				LinkedList<Region> neighbors = new LinkedList<Region>();	
				LinkedList<Region> fathers = new LinkedList<Region>();	
				LinkedList<Region> path = new LinkedList<Region>();
				regionCheck = new HashSet<Region>();

				boolean sem = true;
				neighbors = myRegions.get(i).getNeighbors();
				for(int j = 0; j < neighbors.size(); j++){
					if(!neighbors.get(j).getPlayerName().equals(myRegions.get(i).getPlayerName())){
						sem = false;
						break;
					}
				}

				if(sem == true){

					regionCheck.add(myRegions.get(i));
					path.add(myRegions.get(i));
					fathers.add(myRegions.get(i));

					for(int j = 0; j < path.size(); j++){
						neighbors = path.get(j).getNeighbors();
						for(int k = 0; k < neighbors.size(); k++){
							if(!regionCheck.contains(neighbors.get(k)))
								if(neighbors.get(k).getPlayerName().equals(path.get(j).getPlayerName())){
									path.add(neighbors.get(k));
									regionCheck.add(neighbors.get(k));
									fathers.add(path.get(j));
								}
								else{
									sem = false;
									break;
								}
						}
						if(sem == false){
							if(path.get(j) != myRegions.get(i)){
								Region toRegion = makePath(path, fathers, myRegions.get(i), path.get(j));
								attackTransferMoves.add(new AttackTransferMove(myName, 
																			   myRegions.get(i), 
																			   toRegion, 
																			   myRegions.get(i).getArmies()-1));
							}
							break;
						}
					}
				}
			}
		}

		return attackTransferMoves;

	}


	public LinkedList<Region> izolated(Region region, String name) {
		LinkedList<Region> neighbors = region.getNeighbors();

		for (int i = 0; i < neighbors.size(); i++) {
			if (!neighbors.get(i).ownedByPlayer(name)) {
				return null;
			}
		}
		return neighbors;
	}


	@Override
	public ArrayList<AttackTransferMove> getAttackTransferMoves(BotState state, Long timeOut) {

		ArrayList<AttackTransferMove> attackTransferMoves = new ArrayList<AttackTransferMove>();
		String myName = state.getMyPlayerName();

		LinkedList<Region> myRegions = state.getVisibleMap().getRegions();

		//-----------------MODIFICAT--------------------------------------------------------------------------------////
		attackTransferMoves = deployOnFrontier(myRegions, myName);
		if(attackTransferMoves.isEmpty())
			attackTransferMoves = new ArrayList<AttackTransferMove>();
		//-----------------pana aici--------------------------------------------------------------------------------////

		myRegions = state.getVisibleMap().getRegions();
		attacked = new HashSet<Region>();
		
		if(myRegions.size() / state.getFullMap().getRegions().size() >= 0.9){
			for (Region fromRegion : myRegions) {
				if (fromRegion.ownedByPlayer(myName)) // do an attack
				{
					ArrayList<Region> possibleToRegions = new ArrayList<Region>();
					possibleToRegions.addAll(fromRegion.getNeighbors());

					ArrayList<Region> neutralRegions = new ArrayList<Region>();
					
					// regiuni neutre din aceeasi super-regiune
					ArrayList<Region> SameSuperRegionNeutrals = new ArrayList<Region>(); 
					
					// regiuni neutre din alte super-regiuni
					ArrayList<Region> OtherNeutrals = new ArrayList<Region>(); 
					
					// regiuni inamice din aceeasi super-regiune
					ArrayList<Region> SameSuperRegionEnemy = new ArrayList<Region>(); 
					
					// regiuni inamice din alte super-regiuni
					ArrayList<Region> OtherEnemy = new ArrayList<Region>(); 

					for (Region reg : possibleToRegions) {
						if (reg.getPlayerName().equals(state.getOpponentPlayerName()) == 
								false && reg.getPlayerName().equals(state.getMyPlayerName()) == false) {
							neutralRegions.add(reg);
						}
					}

					for (Region reg : neutralRegions) {
						if (reg.getSuperRegion() == fromRegion.getSuperRegion()) {
							SameSuperRegionNeutrals.add(reg);
						} else {
							OtherNeutrals.add(reg);
						}
					}

					for (Region reg : possibleToRegions) {
						if (reg.getPlayerName().equals(state.getOpponentPlayerName()) && 
								reg.getSuperRegion() == fromRegion.getSuperRegion()) {
							SameSuperRegionEnemy.add(reg);
						} else {
							if (reg.getPlayerName().equals(state.getOpponentPlayerName())) {
								OtherEnemy.add(reg);
							}
						}
					}

					int units = fromRegion.getArmies();
					int originalUnits = fromRegion.getOriginalArmies();

					// atac teritoriile inamice din aceeasi super-regiune(daca am armate)
					if (SameSuperRegionEnemy.size() != 0 && units > 2) { 
						for (Region reg : SameSuperRegionEnemy) {
							if (reg.getArmies() < 0.8 * (originalUnits - 1)) { 
								// avand in vedereca se face downcast la int, procentul scade cu putin
								attackTransferMoves.add(new AttackTransferMove(myName, 
																			   fromRegion, 
																			   reg, 
																			   units - 1));
								units = 1;
							}
						}
					}

					if (OtherEnemy.size() != 0 && units > 2) { 
						// nu stau pe loc, il termin pe fraier, ii iau teritoriile,
						for (Region reg : OtherEnemy) { 
							// chiar daca nu sunt din aceeasi super-regiune.
							if (reg.getArmies() < 0.8 * (originalUnits - 1)) { 
								// procent: +80%
								attackTransferMoves.add(new AttackTransferMove(myName, 
																			   fromRegion, 
																			   reg, 
																			   units - 1));
								units = 1;
							}
						}
					}

					if (SameSuperRegionNeutrals.size() != 0 && units > 2) { 
						// atac toate teritoriile neutre dina ceeasi regiune (daca am armate)
						for (Region reg : SameSuperRegionNeutrals) {
							if (units - 1 >= 1.5 * reg.getArmies() && !attacked.contains(reg) && reg.getArmies() > 1) {
								attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, (int) (1.5 * reg.getArmies())));
								units -= (int) (1.5 * reg.getArmies());
								attacked.add(reg);
							}
							else
								if(units - 1 >= 2 * reg.getArmies() && !attacked.contains(reg)){
									attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, 2 * reg.getArmies()));
									units -= 2 * reg.getArmies();
									attacked.add(reg);
								}
						}
					}

					if (OtherNeutrals.size() != 0 && units > 2) { // atac celelalte teritorii neutre(daca am armate)
						for (Region reg : OtherNeutrals) {
							if (units - 1 >= 1.5 * reg.getArmies() && !attacked.contains(reg) && reg.getArmies() > 1) {
								attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, (int) (1.5 * reg.getArmies())));
								units -= (int) (1.5 * reg.getArmies());
								attacked.add(reg);
							}
							else
								if(units - 1 >= 2 * reg.getArmies() && !attacked.contains(reg)){
									attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, 2 * reg.getArmies()));
									units -= 2 * reg.getArmies();
									attacked.add(reg);
								}
						}
					}
				}
			}
		}
		else {
			for (Region fromRegion : myRegions) {
				if (fromRegion.ownedByPlayer(myName)) // do an attack
				{
					ArrayList<Region> possibleToRegions = new ArrayList<Region>();
					possibleToRegions.addAll(fromRegion.getNeighbors());
	
					ArrayList<Region> neutralRegions = new ArrayList<Region>();
					
					// regiuni neutre din aceeasi super-regiune
					ArrayList<Region> SameSuperRegionNeutrals = new ArrayList<Region>(); 
					
					// regiuni neutre din alte super-regiuni
					ArrayList<Region> OtherNeutrals = new ArrayList<Region>(); 
					
					// regiuni inamice din aceeasi super-regiune
					ArrayList<Region> SameSuperRegionEnemy = new ArrayList<Region>(); 
					
					// regiuni inamice din alte super-regiuni
					ArrayList<Region> OtherEnemy = new ArrayList<Region>(); 
	
					for (Region reg : possibleToRegions) {
						if (reg.getPlayerName().equals(state.getOpponentPlayerName()) == 
								false && reg.getPlayerName().equals(state.getMyPlayerName()) == false) {
							neutralRegions.add(reg);
						}
					}
	
					for (Region reg : neutralRegions) {
						if (reg.getSuperRegion() == fromRegion.getSuperRegion()) {
							SameSuperRegionNeutrals.add(reg);
						} else {
							OtherNeutrals.add(reg);
						}
					}
	
					for (Region reg : possibleToRegions) {
						if (reg.getPlayerName().equals(state.getOpponentPlayerName()) && 
								reg.getSuperRegion() == fromRegion.getSuperRegion()) {
							SameSuperRegionEnemy.add(reg);
						} else {
							if (reg.getPlayerName().equals(state.getOpponentPlayerName())) {
								OtherEnemy.add(reg);
							}
						}
					}
	
					int units = fromRegion.getArmies();
					int originalUnits = fromRegion.getOriginalArmies();
					int unitsAttack;
	
					// atac teritoriile inamice din aceeasi super-regiune(daca am armate)
					if (SameSuperRegionEnemy.size() != 0 && units > 2) { 
						for (Region reg : SameSuperRegionEnemy) {
							if (1.5 * reg.getArmies() <= originalUnits - 1 && reg.getArmies() * 2.25 <= units - 1 && !attacked.contains(reg)) {
								unitsAttack = (int) (reg.getArmies() * 2.25);
								attackTransferMoves.add(new AttackTransferMove(myName, 
																			   fromRegion, 
																			   reg, 
																			   unitsAttack));
								units -= unitsAttack;
								attacked.add(reg);
							}
						}
					}
					
					if (SameSuperRegionNeutrals.size() != 0 && units > 2) { 
						// atac toate teritoriile neutre dina ceeasi regiune (daca am armate)
						for (Region reg : SameSuperRegionNeutrals) {
							if (units - 1 >= 1.5 * reg.getArmies() && !attacked.contains(reg) && reg.getArmies() > 1) {
								attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, (int) (1.5 * reg.getArmies())));
								units -= (int) (1.5 * reg.getArmies());
								attacked.add(reg);
							}
							else
								if(units - 1 >= 2 * reg.getArmies() && !attacked.contains(reg)){
									attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, 2 * reg.getArmies()));
									units -= 2 * reg.getArmies();
									attacked.add(reg);
								}
						}
					}
	
					if (OtherEnemy.size() != 0 && units > 2) { 
						// nu stau pe loc, il termin pe fraier, ii iau teritoriile,
						for (Region reg : OtherEnemy) { 
							// chiar daca nu sunt din aceeasi super-regiune.
							if (1.5 * reg.getArmies() <= originalUnits - 1 && reg.getArmies() * 2.25 <= units - 1 && !attacked.contains(reg)) {
								unitsAttack = (int) (reg.getArmies() * 2.25);
								attackTransferMoves.add(new AttackTransferMove(myName, 
																			   fromRegion, 
																			   reg, 
																			   unitsAttack));
								units -= unitsAttack;
								attacked.add(reg);
							}
						}
					}
	
					if (OtherNeutrals.size() != 0 && units > 2) { // atac celelalte teritorii neutre(daca am armate)
						for (Region reg : OtherNeutrals) {
							if (units - 1 >= 1.5 * reg.getArmies() && !attacked.contains(reg) && reg.getArmies() > 1) {
								attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, (int) (1.5 * reg.getArmies())));
								units -= (int) (1.5 * reg.getArmies());
								attacked.add(reg);
							}
							else
								if(units - 1 >= 2 * reg.getArmies() && !attacked.contains(reg)){
									attackTransferMoves.add(new AttackTransferMove(myName, fromRegion, reg, 2 * reg.getArmies()));
									units -= 2 * reg.getArmies();
									attacked.add(reg);
								}
						}
					}
				}
			}
		}

		return attackTransferMoves;
	}

	public static void main(String[] args) {
		BotParser parser = new BotParser(new BotStarter());
		parser.run();
	}

}
