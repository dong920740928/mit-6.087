/*
 * lab1a.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

#define DIRECTION_NUM 8

int directions[8][2] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(void)
{
    int n;

    /* TODO: initialize the world */
    initialize_world();

    for (n = 0; n < NUM_GENERATIONS; n++)
        next_generation();

    /* TODO: output final world state */
    output_world();

    return 0;
}

void next_generation(void)
{
    /* TODO: for every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) */
    int width = get_world_width();
    int height = get_world_height();
    for (int x = 0; x < width; ++x){
        for (int y = 0; y < height; ++y){
            int new_state = get_next_state(x, y);
            set_cell_state(x, y, new_state);
        }
    }

    finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y)
{
    /* TODO: for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
    int current_state = get_cell_state(x, y);
    int neighbors = num_neighbors(x, y);
    if (current_state == ALIVE){
        if (neighbors >= 2 && neighbors <= 3){
            // alive -> alive
            return ALIVE;
        } else{
            // alive -> dead
            return DEAD;
        }
    } else{
        if (neighbors == 3){
            // dead -> alive
            return ALIVE;
        } else{
            // dead -> dead
            return DEAD;
        }
    }
}

int num_neighbors(int x, int y)
{
    /* TODO: for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */
    int num = 0;
    for (int d = 0; d < DIRECTION_NUM; ++d){
        int tmp_x = x + directions[d][0];
        int tmp_y = y + directions[d][1];

        if (get_cell_state(tmp_x, tmp_y) == ALIVE){
            ++num;
        }
    }

    return num;
}
