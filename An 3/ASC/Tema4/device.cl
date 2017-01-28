#define EARTH_RADIUS 6371
#define DEGREE_TO_RADIANS 0.0174533

/*
	For each zone/city calculate the distances to the other zones.
	If the distance obtained is lower than kmrange than add the 
	population to the accesible population.
*/
__kernel void kernel_id(__global float* latitudine, 
						__global float* longitudine, 
						__global int* population, 
						int kmrange, 
						int length, 
						__global int* outputs)
{
	uint gid = get_global_id(0);
	
	uint i;
	
	float phi1 = (90 - latitudine[gid]) * DEGREE_TO_RADIANS;
	float theta1 = longitudine[gid] * DEGREE_TO_RADIANS;

	for(i = 0; i < length; i++) {
		if(i != gid) {
			float phi2 = (90 - latitudine[i]) * DEGREE_TO_RADIANS;
			float theta2 = longitudine[i] * DEGREE_TO_RADIANS;
			
			float cs = sin(phi1) * sin(phi2) * cos(theta1 - theta2) + cos(phi1) * cos(phi2);
			float distance = EARTH_RADIUS * acos(cs);
			
			if(distance <= kmrange)
				outputs[gid] += population[i];
		}
	}

}
