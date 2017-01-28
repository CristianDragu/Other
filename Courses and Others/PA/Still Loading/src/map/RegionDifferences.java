package map;

public class RegionDifferences implements Comparable<RegionDifferences> {

	private Region region;
	private int armiesDifferences;

	public RegionDifferences(Region region, int armiesDifferences) {
		this.region = region;
		this.armiesDifferences = armiesDifferences;
	}

	public Region getRegion() {
		return this.region;
	}

	public int getArmiesDifferences() {
		return this.armiesDifferences;
	}

	@Override
	public int compareTo(RegionDifferences r) {
		if (this.armiesDifferences < r.getArmiesDifferences())
			return -1;
		else if (this.armiesDifferences > r.getArmiesDifferences())
			return 1;
		return 0;
	}
	
}