#include "queue.h"
#include "tile_game.h"

int is_same_board(struct game_state state, struct linked_list *visited);
int is_goal(struct game_state state);






void enqueue(struct queue *q, struct game_state state) {
	size_t value = (size_t) serialize(state);
	insert_at_tail(&q->data, value);

}

struct game_state dequeue(struct queue *q) { 
	size_t value = remove_from_head(&q->data);
	return deserialize((uint64_t) value);
	
	
	
	//return (struct game_state){0};
	 }

int number_of_moves(struct game_state start) { 
	struct linked_list queue = {0};
	struct linked_list repeats = {0};  //have to check if anything has been there before even if leaves the queue.
	struct queue q;
	q.data = queue;	
	
	enqueue(&q, start);
	insert_at_tail(&repeats, (size_t)serialize(start));


	while(q.data.head != NULL)
	{
		//printf("it ran this\n");
		struct game_state current = dequeue(&q);


		if(is_goal(current))
		{
			free_list(queue);
			free_list(repeats);
			return (int)current.num_steps;	
	
		}

		struct game_state copy;
	
		copy = current;
		move_up(&copy);
		if(!is_same_board(copy, &repeats))
		{
			//copy.numsteps++;
			insert_at_tail(&repeats, serialize(copy));
			enqueue(&q, copy);
		}

		copy = current;
		move_right(&copy);
		if(!is_same_board(copy, &repeats))
		{
			insert_at_tail(&repeats, serialize(copy));
			enqueue(&q, copy);
		}

		copy = current;
		move_down(&copy);
		if(!is_same_board(copy, &repeats))
		{
			insert_at_tail(&repeats, serialize(copy));
			enqueue(&q, copy);
		}

		copy = current;
		move_left(&copy);
		if(!is_same_board(copy, &repeats))
		{
			insert_at_tail(&repeats, serialize(copy));
			enqueue(&q, copy);
		}

	}


	free_list(queue);
	free_list(repeats);




	return 0; }



int is_same_board(struct game_state state, struct linked_list *visited) {
    struct list_node *cur = visited->head;
    while (cur != NULL) {
        // Deserialize each state in visited list
        struct game_state visited_state = deserialize(cur->value);

        // Compare tiles of the current state and the visited state
        int is_equal = 1;
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                if (state.tiles[r][c] != visited_state.tiles[r][c]) {
                    is_equal = 0;
                    break;
                }
            }
            if (!is_equal) break;
        }

        if (is_equal) return 1; // Found a match, boards are the same

        cur = cur->next;
    }

    return 0; // No match, boards are different
}


int is_goal(struct game_state state) {
    uint8_t expected = 1;

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            // Last tile should be 0 (empty)
            if (r == 3 && c == 3) {
                if (state.tiles[r][c] != 0) return 0;
            } else {
                if (state.tiles[r][c] != expected) return 0;
                expected++;
            }
        }
    }

    return 1; // Board is in goal state
}

