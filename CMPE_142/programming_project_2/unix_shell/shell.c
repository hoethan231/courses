#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE 80
#define MAX_CMDS 10
#define MAX_HIST 10

struct command
{
    char *args[MAX_LINE / 2 + 1];
    int argc;
};

// History array and index
char *history[MAX_HIST];
int history_count = 0;

void add_to_history(const char *cmd_line)
{
    // Don't add empty commands or duplicates of the last command
    if (strlen(cmd_line) == 0 || (history_count > 0 && strcmp(history[history_count - 1], cmd_line) == 0))
    {
        return;
    }

    // If history is full, remove oldest command
    if (history_count == MAX_HIST)
    {
        free(history[0]);
        for (int i = 1; i < MAX_HIST; i++)
        {
            history[i - 1] = history[i];
        }
        history_count--;
    }

    history[history_count++] = strdup(cmd_line);
}

// Free history memory
void free_history()
{
    for (int i = 0; i < history_count; i++)
    {
        free(history[i]);
    }
}

void parse_cmd(char *input, struct command *cmd)
{
    int argc = 0;
    char *token = strtok(input, " \t");

    // Parse the command and save its args and count in the struct
    while (token != NULL && argc < MAX_LINE)
    {
        cmd->args[argc] = strdup(token);
        argc += 1;
        token = strtok(NULL, " \t");
    }

    cmd->args[argc] = NULL;
    cmd->argc = argc;
}

int parse_line(char *input, struct command commands[])
{
    char *cmds[MAX_CMDS];
    int cmd_count = 0;

    // Splits stdin by pipes and stores args
    char *token = strtok(input, "|");
    while (token != NULL && cmd_count < MAX_CMDS)
    {
        cmds[cmd_count] = token;
        cmd_count += 1;
        token = strtok(NULL, "|");
    }

    // Parse each command
    for (int i = 0; i < cmd_count; i++)
    {
        parse_cmd(cmds[i], &commands[i]);
    }

    return cmd_count;
}

void handle_input_redirection(struct command *cmd)
{

    // Parses for "<" character
    for (int i = 0; i < cmd->argc; i++)
    {
        if (strcmp(cmd->args[i], "<") == 0)
        {

            // Opens the file after "<"
            int fd = open(cmd->args[i + 1], O_RDONLY);
            if (fd < 0)
            {
                fprintf(stderr, "Unable to open file");
                exit(1);
            }

            // Make stdin point to the contents of the file instead
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                fprintf(stderr, "Unable to use file");
                exit(1);
            }
            close(fd);

            // Remove "<" and the file from command
            free(cmd->args[i]);
            free(cmd->args[i + 1]);

            for (int j = i; j < cmd->argc - 2; j++)
            {
                cmd->args[j] = cmd->args[j + 2];
            }

            cmd->argc -= 2;
            cmd->args[cmd->argc] = NULL;
            break;
        }
    }
}

void handle_output_redirection(struct command *cmd)
{
    for (int i = 0; i < cmd->argc; i++)
    {
        if (strcmp(cmd->args[i], ">") == 0 || strcmp(cmd->args[i], ">>") == 0)
        {
            int flags;

            if (strcmp(cmd->args[i], ">") == 0)
            {
                flags = O_WRONLY | O_CREAT | O_TRUNC;
            }
            else
            {
                flags = O_WRONLY | O_CREAT | O_APPEND;
            }

            // Opens the file
            int fd = open(cmd->args[i + 1], flags, 0644);
            if (fd < 0)
            {
                fprintf(stderr, "Unable to open file");
                exit(1);
            }

            // Sets the output to the file's descriptor
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                fprintf(stderr, "Unable to output file");
                exit(1);
            }

            close(fd);

            // Remove ">" and the file from command
            free(cmd->args[i]);
            free(cmd->args[i + 1]);

            for (int j = i; j < cmd->argc - 2; j++)
            {
                cmd->args[j] = cmd->args[j + 2];
            }
            cmd->argc -= 2;
            cmd->args[cmd->argc] = NULL;

            break;
        }
    }
}

// Checks for background key
int check_background(struct command *cmd)
{
    // Checks the last arg for "&" and remove it from the cmd
    if (cmd->argc > 0 && strcmp(cmd->args[cmd->argc - 1], "&") == 0)
    {
        free(cmd->args[cmd->argc - 1]);
        cmd->args[cmd->argc - 1] = NULL;
        cmd->argc -= 1;
        return 1;
    }
    return 0;
}

// Frees allocated memory
void free_cmds(struct command commands[], int cmd_count)
{
    for (int i = 0; i < cmd_count; i++)
    {
        for (int j = 0; j < commands[i].argc; j++)
        {
            free(commands[i].args[j]);
        }
    }
}

// Execute a single command
void execute_cmd(struct command *cmd)
{
    handle_input_redirection(cmd);
    handle_output_redirection(cmd);

    if (execvp(cmd->args[0], cmd->args) < 0)
    {
        fprintf(stderr, "Unable to execute command\n");
        return;
    }
}

void execute_cmds(struct command cmds[], int cmd_count, int background)
{
    if (cmd_count == 1)
    {
        pid_t pid = fork();

        // Parent Process
        if (pid > 0)
        {
            if (!background)
            {
                waitpid(pid, NULL, 0);
            }
        }

        // Child Process
        else if (pid == 0)
        {
            execute_cmd(&cmds[0]);
            exit(0);
        }

        // Error
        else
        {
            fprintf(stderr, "Unable to fork");
            exit(1);
        }
    }
    else
    {
        // Use pipes for ICP between processes
        int pipes[MAX_CMDS - 1][2];
        pid_t pids[MAX_CMDS];

        // Create pipes for each command
        for (int i = 0; i < cmd_count - 1; i++)
        {
            if (pipe(pipes[i]) < 0)
            {
                fprintf(stderr, "Unable to fork");
                return;
            }
        }

        // Fork and execute each command
        for (int i = 0; i < cmd_count; i++)
        {
            pids[i] = fork();

            if (pids[i] < 0)
            {
                fprintf(stderr, "Unable to fork");
                return;
            }

            // Child process
            else if (pids[i] == 0)
            {

                // Set up input from previous pipe
                if (i > 0)
                {
                    if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
                    {
                        fprintf(stderr, "Unable to assign input");
                        exit(1);
                    }
                }

                // Set up output to next pipe
                if (i < cmd_count - 1)
                {
                    if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
                    {
                        fprintf(stderr, "Unable to assign output");
                        exit(1);
                    }
                }

                // Close all pipe file descriptors
                for (int j = 0; j < cmd_count - 1; j++)
                {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }

                execute_cmd(&cmds[i]);
                exit(0);
            }
        }

        // Parent process
        // Close all pipe file descriptors
        for (int i = 0; i < cmd_count - 1; i++)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }

        // Wait for all children to finish (unless background)
        if (!background)
        {
            for (int i = 0; i < cmd_count; i++)
            {
                waitpid(pids[i], NULL, 0);
            }
        }
    }
}

int main(void)
{

    char input[MAX_LINE];
    struct command commands[MAX_CMDS];
    int should_run = 1;
    int cmd_count;

    while (should_run)
    {
        printf("osh> ");
        fflush(stdout);

        // Get user input
        if (!fgets(input, MAX_LINE, stdin))
        {
            fprintf(stderr, "Unable to get user input");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';
        add_to_history(input);

        // Continue if empty input
        if (strlen(input) == 0)
            continue;

        cmd_count = parse_line(input, commands);

        if (cmd_count == 0)
            continue;

        // Check for exit keyword
        if (strcmp(commands[0].args[0], "exit") == 0)
        {
            should_run = 0;
            free_cmds(commands, cmd_count);
            printf("Bye!\n");
            continue;
        }

        // Check for background process
        int background = check_background(&commands[cmd_count - 1]);

        execute_cmds(commands, cmd_count, background);
        free_cmds(commands, cmd_count);
    }

    free_history();
    return 0;
}
