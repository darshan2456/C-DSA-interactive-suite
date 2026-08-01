#include <stdbool.h>
#ifndef PROCESS_SYNCHRONIZATION_H
#define PROCESS_SYNCHRONIZATION_H
#define BUFFER_SIZE 5

typedef enum
{
    THINKING,
    HUNGRY,
    EATING
} PhilosopherState;

typedef struct
{
    int chopsticks[5];
    PhilosopherState phil_states[5];
    int strategy;
} DiningTable;

typedef struct
{
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int mutex;
    int empty;
    int full;
    int item_counter;
    int prod_blocked;
    int cons_blocked;
} ProducerConsumerState;

typedef struct
{
    int flag[2];
    int turn;
    int pc[2];
} PetersonState;

void consumer_step(ProducerConsumerState* pc_state);
void pc_auto_stimulate(ProducerConsumerState* pc_state, int steps, int step_mode);
void producer_step(ProducerConsumerState* pc_state);
void display_buffer_state(const int* buffer, int in, int out, int mutex, int empty, int full,
                          int prod_blocked, int cons_blocked);
void pc_init(ProducerConsumerState* pc_state);
void petersons_init(int* flag, int* turn, int* pc);
void petersons_reset(int* flag, int* turn, int* pc);
void step_process(int i, int* flag, int* turn, int* pc);
void dp_reset(DiningTable* table);
void dp_change_strategy(DiningTable* table, int strategy);
bool dp_is_deadlocked(const DiningTable* table);
void dp_auto_simulate(DiningTable* table, int steps, int step_mode);
void trigger_philosopher(int i, int strategy, int* chopsticks, PhilosopherState* states);
void display_table_state(const int* chopsticks, const PhilosopherState* states, int strategy);
void producer_consumer_demo(void);
void dining_philosophers_demo(void);
void petersons_algorithm_demo(void);
void process_synchronization_demo(void);

#endif
