/**
 * A very simple test problem
 * 
 * We first create a REBOUND simulation, then we add 
 * two particles and integrate the system for 100 time 
 * units.
 */
#include "rebound.h"
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

void heartbeat(struct reb_simulation* r){
    // This function gets called after every timestep.
    // Here, we simply print out the current simulation time.
    printf("%f\n",r->t);
}

int main(int argc, char* argv[]) {
    struct reb_simulation* r = reb_create_simulation();
    r->dt = 1e-3;
    //r->heartbeat = heartbeat;
    r->exact_finish_time = 1; // Finish exactly at tmax in reb_integrate(). Default is already 1.
    r->G = 0.01720209895 * 0.01720209895 * 365 * 365;
    printf("Gravity basic: %d\n", REB_GRAVITY_BASIC);
    printf("Cur gravity: %d\n", r->gravity);
    r->gravity      = REB_GRAVITY_COMPENSATED;
    printf("Cur gravity: %d\n", r->gravity);

    struct reb_particle p1 = {0}; // always initizialize a struct with this syntax to ensure all variables are set to 0.
    p1.m = 1.;
    reb_add(r, p1);  // reb_add makes a copy of the particle and adds it to the simulation.

int nplanets = atoi(argv[1]);
printf("n planets: %d\n", nplanets);

    
for (int i = 0; i < nplanets; ++i) {
    struct reb_particle p2 = {0};
    p2.x = i+1;
    p2.vy = sqrt(r->G / (i+1));
    p2.m = (1./333000)/((i+1)*(i+1));
    reb_add(r, p2);
}

reb_move_to_com(r);

	printf("N active: %d\n", r->N_active);

struct timeval tval_before, tval_after, tval_result;

gettimeofday(&tval_before, NULL);

    reb_integrate(r,1000.);

gettimeofday(&tval_after, NULL);

timersub(&tval_after, &tval_before, &tval_result);

printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);

}

