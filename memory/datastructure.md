---
title: Datastructures 
layout: main 
category: memory 
---

# Datastructure 

### Exercise0 : Particle datastructure
Create a Class or struct for a Particle with the following members
- 1 `const std::string` to hold the particle’s name;
- 3 `double`s for the x, y, z velocities
- 3 `bool`s to mark if there has been a collision along the x, y z directions
- 1 `float` for the mass
- 1 `float` for the energy
- 3 `doubles` for the px, py, pz coordinates
- 1 `const int` for the particle’s id
- 1 `static int` to keep track of the total number of objects

What is the best order for your members?


### Exercise1: Access Pattern

Now let's use our GoodParticle (nicely organized struct/class) and let's do some computations

- Write a function to initialize a collectin of `N` `GoodParticle`s
	- The function should also initialize all the memebers of each object
- Write another function that takes as input the collection of `GoodParticle`s and `x_max` value
	- Iterate over all the elements and for each element:
		- Generate a random number representing a time interval t
		- Update the position `x-->x = x + px/m * t`
		- If the updated position x is less than 0 or greater than `x_max`
			- set `hit_x` to true
		- Else:
			- Set `hit_x` to false and change the sign of px

- How are you accessing the members in the datastructure?

### Exercise2: AoS vs SoA

- Write a new structure/class for your GoodParticle but in SoA fashion --> ParticleSoA
- Implement the functions described in Exercise1 for the SoA object
- Work with fixed size objects
- Measure the time for AoS implementation and SoA implementation and compare them
- What happens if you compile with some optimization? `-O1', '-O2', '-O3'?
- How does SoA interface change with respect to AoS?
