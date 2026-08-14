#include "step_debugger.h"
#include "telemetry.h"
#include <stdio.h>
#include <string.h>

#ifndef _WIN32
#include <ncurses.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>
#endif

#define DEBUGGER_HISTORY_MAX 64

static char event_log[5][128];
static int event_count = 0;

static char history_snapshots[DEBUGGER_HISTORY_MAX][128];
static int total_history_count = 0;
static int history_cursor = 0;
static int inspector_active = 0;

static int get_keypress(int block)
{
#ifdef _WIN32
    if (block)
    {
        return _getch();
    }
    else
    {
        if (_kbhit())
        {
            return _getch();
        }
        return -1;
    }
#else
    if (stdscr != NULL && !isendwin())
    {
        nodelay(stdscr, block ? FALSE : TRUE);
        int ch = getch();
        return ch;
    }

    struct termios oldt, newt;
    memset(&oldt, 0, sizeof(oldt));
    memset(&newt, 0, sizeof(newt));
    int ch = -1;
    int is_tty = (tcgetattr(STDIN_FILENO, &oldt) == 0);
    if (is_tty)
    {
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }

    if (block)
    {
        ch = getchar();
    }
    else
    {
        struct timeval tv = {0, 0};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0)
        {
            ch = getchar();
        }
    }

    if (is_tty)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
    return ch;
#endif
}

int debugger_get_history_count(void)
{
    return total_history_count;
}

int debugger_get_current_step(void)
{
    return history_cursor;
}

void debugger_step_prev(void)
{
    if (history_cursor > 0)
    {
        history_cursor--;
    }
}

void debugger_step_next(void)
{
    if (history_cursor < total_history_count - 1)
    {
        history_cursor++;
    }
}

void debugger_step_reset(void)
{
    history_cursor = 0;
}

void debugger_toggle_inspector(void)
{
    inspector_active = !inspector_active;
}

int debugger_is_inspector_visible(void)
{
    return inspector_active;
}

void print_state_inspector_card(void)
{
    printf("\n┌──────────────────────────────────────────────────┐\n");
    printf("│              LIVE STATE INSPECTOR                │\n");
    printf("├──────────────────────────────────────────────────┤\n");
    printf("│ Active Step Index : %-28d │\n", history_cursor + 1);
    printf("│ Total Steps Saved : %-28d │\n", total_history_count);
    if (total_history_count > 0 && history_cursor < total_history_count)
    {
        printf("│ Current Snapshot  : %-28.28s │\n", history_snapshots[history_cursor]);
    }
    else
    {
        printf("│ Current Snapshot  : %-28s │\n", "None");
    }
    printf("└──────────────────────────────────────────────────┘\n");
}

void algorithm_step_hook(const char* event_msg)
{
    if (event_msg == NULL)
        return;

    if (is_telemetry_enabled())
    {
        telemetry_log_step(NULL, 0, event_msg);
    }

    // Shift events in circular log
    if (event_count < 5)
    {
        strncpy(event_log[event_count], event_msg, 127);
        event_log[event_count][127] = '\0';
        event_count++;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            strcpy(event_log[i], event_log[i + 1]);
        }
        strncpy(event_log[4], event_msg, 127);
        event_log[4][127] = '\0';
    }

    // Record snapshot in history ring buffer
    if (total_history_count < DEBUGGER_HISTORY_MAX)
    {
        strncpy(history_snapshots[total_history_count], event_msg, 127);
        history_snapshots[total_history_count][127] = '\0';
        history_cursor = total_history_count;
        total_history_count++;
    }
    else
    {
        for (int i = 0; i < DEBUGGER_HISTORY_MAX - 1; i++)
        {
            strcpy(history_snapshots[i], history_snapshots[i + 1]);
        }
        strncpy(history_snapshots[DEBUGGER_HISTORY_MAX - 1], event_msg, 127);
        history_snapshots[DEBUGGER_HISTORY_MAX - 1][127] = '\0';
        history_cursor = DEBUGGER_HISTORY_MAX - 1;
    }

    if (!get_step_mode())
        return;

    // Non-blocking keypress check to see if user wants to PAUSE during run
    if (!get_paused())
    {
        int ch = get_keypress(0);
        if (ch == ' ' || ch == 32)
        {
            set_paused(1);
            printf("\n[Paused by User]\n");
        }
        else if (ch == 'q' || ch == 'Q')
        {
            set_step_mode(0);
            set_paused(0);
            printf("\n[Step Debugger Disabled]\n");
        }
    }

    print_recent_events_card();
    if (inspector_active)
    {
        print_state_inspector_card();
    }

    while (get_step_mode() && get_paused())
    {
        printf("[Paused] Stepping: [n]ext, [p]rev, [r]eset, [i]nspect, [Space] resume, [q]uit\n");
        fflush(stdout);

        int ch = get_keypress(1);
        if (ch == ' ' || ch == 32)
        {
            set_paused(0);
            printf("Resuming execution...\n");
        }
        else if (ch == 'n' || ch == 'N' || ch == 's' || ch == 'S')
        {
            debugger_step_next();
            break; // Single step forward
        }
        else if (ch == 'p' || ch == 'P')
        {
            debugger_step_prev();
            printf("[Time-Travel: Step %d / %d] Event: %s\n", history_cursor + 1,
                   total_history_count, history_snapshots[history_cursor]);
        }
        else if (ch == 'r' || ch == 'R')
        {
            debugger_step_reset();
            printf("[Time-Travel: Reset to Step 1 / %d] Event: %s\n", total_history_count,
                   history_snapshots[0]);
        }
        else if (ch == 'i' || ch == 'I')
        {
            debugger_toggle_inspector();
            if (inspector_active)
            {
                print_state_inspector_card();
            }
            else
            {
                printf("State Inspector Hidden.\n");
            }
        }
        else if (ch == 'q' || ch == 'Q')
        {
            set_step_mode(0);
            set_paused(0);
            printf("Exiting step debugger mode. Running at full speed.\n");
        }
    }
}

void get_recent_events(char events[5][128], int* count)
{
    *count = event_count;
    for (int i = 0; i < event_count; i++)
    {
        strcpy(events[i], event_log[i]);
    }
}

void clear_recent_events(void)
{
    event_count = 0;
    total_history_count = 0;
    history_cursor = 0;
}

void print_recent_events_card(void)
{
    printf("\n┌──────────────────────────────────────────────────┐\n");
    printf("│             DEBUGGER EVENT HISTORY               │\n");
    printf("├──────────────────────────────────────────────────┤\n");
    for (int i = 0; i < 5; i++)
    {
        if (i < event_count)
        {
            printf("│ %02d. %-44s │\n", i + 1, event_log[i]);
        }
        else
        {
            printf("│ %02d. %-44s │\n", i + 1, "---");
        }
    }
    printf("└──────────────────────────────────────────────────┘\n");
}

static AlgorithmStateBridge current_bridge_state = {0};

void telemetry_bridge_update(const AlgorithmStateBridge* bridge)
{
    if (bridge != NULL)
    {
        current_bridge_state = *bridge;
    }
}

void telemetry_bridge_get(AlgorithmStateBridge* bridge_out)
{
    if (bridge_out != NULL)
    {
        *bridge_out = current_bridge_state;
    }
}

void telemetry_bridge_reset(const char* algorithm_name)
{
    memset(&current_bridge_state, 0, sizeof(current_bridge_state));
    if (algorithm_name != NULL)
    {
        strncpy(current_bridge_state.algorithm_name, algorithm_name,
                sizeof(current_bridge_state.algorithm_name) - 1);
    }
}
