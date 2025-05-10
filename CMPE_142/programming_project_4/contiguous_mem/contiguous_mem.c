#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PROCESSES 100
#define MAX_COMMAND_LENGTH 100

// A memory block object
typedef struct
{
    int start_address;
    int end_address;
    char process_id[10];
    bool is_allocated;
} MemoryBlock;

MemoryBlock memory_blocks[MAX_PROCESSES + 1];
int block_count = 0;
int max_memory = 0;

void initialize_memory(int size);
void request_memory(char *process_id, int size, char algorithm);
void release_memory(char *process_id);
void compact_memory();
void report_status();
void print_prompt();
int parse_command(char *command);
int find_best_fit(int size);
int find_worst_fit(int size);
int find_first_fit(int size);

int main(int argc, char *argv[])
{
    char command[MAX_COMMAND_LENGTH];

    // Input validation
    if (argc != 2)
    {
        printf("Usage: %s <memory_size>\n", argv[0]);
        return 1;
    }

    // Initialize memory with the specified size
    max_memory = atoi(argv[1]);
    if (max_memory <= 0)
    {
        printf("Error: Invalid memory size\n");
        return 1;
    }

    initialize_memory(max_memory);

    // Main command loop
    while (1)
    {
        print_prompt();

        // Get command from user
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            break;
        }

        command[strcspn(command, "\n")] = 0;

        // Parse and execute command
        if (parse_command(command) == -1)
        {
            break;
        }
    }

    return 0;
}

// Initialize memory
void initialize_memory(int size)
{
    memory_blocks[0].start_address = 0;
    memory_blocks[0].end_address = size - 1;
    strcpy(memory_blocks[0].process_id, "Unused");
    memory_blocks[0].is_allocated = false;
    block_count = 1;

    printf("Memory initialized with %d bytes\n", size);
}

// Find a suitable memory block using First-Fit algorithm
int find_first_fit(int size)
{
    for (int i = 0; i < block_count; i++)
    {
        if (!memory_blocks[i].is_allocated)
        {
            int block_size = memory_blocks[i].end_address - memory_blocks[i].start_address + 1;
            if (block_size >= size)
            {
                return i;
            }
        }
    }
    return -1; // No suitable block found
}

// Find a suitable memory block using Best-Fit algorithm
int find_best_fit(int size)
{
    int best_fit_index = -1;
    int smallest_sufficient_size = max_memory + 1;

    for (int i = 0; i < block_count; i++)
    {
        if (!memory_blocks[i].is_allocated)
        {
            int block_size = memory_blocks[i].end_address - memory_blocks[i].start_address + 1;
            if (block_size >= size && block_size < smallest_sufficient_size)
            {
                smallest_sufficient_size = block_size;
                best_fit_index = i;
            }
        }
    }

    return best_fit_index;
}

// Find a suitable memory block using Worst-Fit algorithm
int find_worst_fit(int size)
{
    int worst_fit_index = -1;
    int largest_size = -1;

    for (int i = 0; i < block_count; i++)
    {
        if (!memory_blocks[i].is_allocated)
        {
            int block_size = memory_blocks[i].end_address - memory_blocks[i].start_address + 1;
            if (block_size >= size && block_size > largest_size)
            {
                largest_size = block_size;
                worst_fit_index = i;
            }
        }
    }

    return worst_fit_index;
}

// Request memory for a process
void request_memory(char *process_id, int size, char algorithm)
{
    int block_index;

    // Find a suitable block based on the algorithm
    if (algorithm == 'F')
    {
        block_index = find_first_fit(size);
    }
    else if (algorithm == 'B')
    {
        block_index = find_best_fit(size);
    }
    else if (algorithm == 'W')
    {
        block_index = find_worst_fit(size);
    }
    else
    {
        printf("Error: Invalid algorithm. Use F (First-Fit), B (Best-Fit), or W (Worst-Fit)\n");
        return;
    }

    if (block_index == -1)
    {
        printf("Error: Not enough memory for process %s with size %d\n", process_id, size);
        return;
    }

    // Get the selected free block
    int start_address = memory_blocks[block_index].start_address;
    int end_address = memory_blocks[block_index].end_address;

    // If the block is exactly the size needed
    if (end_address - start_address + 1 == size)
    {
        memory_blocks[block_index].is_allocated = true;
        strcpy(memory_blocks[block_index].process_id, process_id);
    }
    else
    {
        // Need to split the block

        // Shift blocks to make room for the new one
        for (int i = block_count; i > block_index; i--)
        {
            memory_blocks[i] = memory_blocks[i - 1];
        }

        // Update the allocated block
        memory_blocks[block_index].end_address = start_address + size - 1;
        strcpy(memory_blocks[block_index].process_id, process_id);
        memory_blocks[block_index].is_allocated = true;

        // Create a new free block after the allocated one
        memory_blocks[block_index + 1].start_address = start_address + size;
        memory_blocks[block_index + 1].end_address = end_address;
        strcpy(memory_blocks[block_index + 1].process_id, "Unused");
        memory_blocks[block_index + 1].is_allocated = false;

        block_count++;
    }

    printf("Successfully allocated %d bytes to process %s\n", size, process_id);
}

// Release memory allocated to a process
void release_memory(char *process_id)
{
    bool found = false;

    // Find the block allocated to the process
    for (int i = 0; i < block_count; i++)
    {
        if (memory_blocks[i].is_allocated && strcmp(memory_blocks[i].process_id, process_id) == 0)
        {
            // Mark the block as free
            memory_blocks[i].is_allocated = false;
            strcpy(memory_blocks[i].process_id, "Unused");
            found = true;

            // Try to merge with adjacent free blocks

            // Check if we can merge with the previous block
            if (i > 0 && !memory_blocks[i - 1].is_allocated)
            {
                memory_blocks[i - 1].end_address = memory_blocks[i].end_address;

                // Shift all blocks to fill the gap
                for (int j = i; j < block_count - 1; j++)
                {
                    memory_blocks[j] = memory_blocks[j + 1];
                }

                block_count--;
                i--; // Adjust index after shifting
            }

            // Check if we can merge with the next block
            if (i < block_count - 1 && !memory_blocks[i + 1].is_allocated)
            {
                memory_blocks[i].end_address = memory_blocks[i + 1].end_address;

                // Shift all blocks to fill the gap
                for (int j = i + 1; j < block_count - 1; j++)
                {
                    memory_blocks[j] = memory_blocks[j + 1];
                }

                block_count--;
            }

            printf("Memory allocated to process %s has been released\n", process_id);
            break;
        }
    }

    if (!found)
    {
        printf("Error: No memory allocated to process %s\n", process_id);
    }
}

// Compact memory by moving all allocated blocks to the beginning
void compact_memory()
{
    if (block_count <= 1)
    {
        printf("No need for compaction\n");
        return;
    }

    int compact_pointer = 0;

    // Move allocated blocks to the beginning
    for (int i = 0; i < block_count; i++)
    {
        if (memory_blocks[i].is_allocated)
        {
            int block_size = memory_blocks[i].end_address - memory_blocks[i].start_address + 1;

            // If the block is not already at the compact pointer, move it
            if (memory_blocks[i].start_address != compact_pointer)
            {
                int old_start = memory_blocks[i].start_address;
                int old_end = memory_blocks[i].end_address;

                memory_blocks[i].start_address = compact_pointer;
                memory_blocks[i].end_address = compact_pointer + block_size - 1;

                printf("Moved process %s from addresses [%d:%d] to [%d:%d]\n",
                       memory_blocks[i].process_id, old_start, old_end,
                       memory_blocks[i].start_address, memory_blocks[i].end_address);
            }

            compact_pointer += block_size;
        }
    }

    // Create a single free block at the end if needed
    if (compact_pointer < max_memory)
    {
        // Remove all free blocks
        int allocated_count = 0;
        for (int i = 0; i < block_count; i++)
        {
            if (memory_blocks[i].is_allocated)
            {
                memory_blocks[allocated_count++] = memory_blocks[i];
            }
        }

        // Create a single free block at the end
        memory_blocks[allocated_count].start_address = compact_pointer;
        memory_blocks[allocated_count].end_address = max_memory - 1;
        strcpy(memory_blocks[allocated_count].process_id, "Unused");
        memory_blocks[allocated_count].is_allocated = false;

        block_count = allocated_count + 1;

        printf("Compaction completed. All free memory consolidated at addresses [%d:%d]\n",
               compact_pointer, max_memory - 1);
    }
    else
    {
        printf("Compaction completed. No free memory available.\n");
    }
}

// Report the status of memory allocation
void report_status()
{
    printf("\nCurrent memory allocation:\n");
    printf("-------------------------\n");

    for (int i = 0; i < block_count; i++)
    {
        printf("Addresses [%d:%d] ", memory_blocks[i].start_address, memory_blocks[i].end_address);

        if (memory_blocks[i].is_allocated)
        {
            printf("Process %s\n", memory_blocks[i].process_id);
        }
        else
        {
            printf("Unused\n");
        }
    }

    printf("-------------------------\n");
}

// Print the command prompt
void print_prompt()
{
    printf("allocator> ");
}

// Parse and execute a command
int parse_command(char *command)
{
    char cmd[10];
    char process_id[10];
    int size;
    char algorithm;

    // Extract the command
    if (sscanf(command, "%s", cmd) != 1)
    {
        printf("Error: Invalid command\n");
        return 0;
    }

    // Convert command to uppercase
    for (int i = 0; cmd[i]; i++)
    {
        cmd[i] = toupper(cmd[i]);
    }

    // Process the command
    if (strcmp(cmd, "RQ") == 0)
    {
        if (sscanf(command, "%*s %s %d %c", process_id, &size, &algorithm) != 3)
        {
            printf("Error: Invalid RQ command. Format: RQ <process_id> <size> <algorithm>\n");
            return 0;
        }
        algorithm = toupper(algorithm);
        request_memory(process_id, size, algorithm);
    }
    else if (strcmp(cmd, "RL") == 0)
    {
        if (sscanf(command, "%*s %s", process_id) != 1)
        {
            printf("Error: Invalid RL command. Format: RL <process_id>\n");
            return 0;
        }
        release_memory(process_id);
    }
    else if (strcmp(cmd, "C") == 0)
    {
        compact_memory();
    }
    else if (strcmp(cmd, "STAT") == 0)
    {
        report_status();
    }
    else if (strcmp(cmd, "X") == 0)
    {
        printf("Exiting the allocator program\n");
        return -1; // Signal to exit
    }
    else
    {
        printf("Error: Unknown command '%s'\n", cmd);
        printf("Available commands: RQ, RL, C, STAT, X\n");
    }

    return 0;
}