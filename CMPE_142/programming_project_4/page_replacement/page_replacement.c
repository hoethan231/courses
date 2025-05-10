/**
 * Page Replacement Algorithm Simulator
 *
 * Implements FIFO, LRU, and Optimal (OPT) page replacement algorithms
 * and compares their performance on a random page-reference string.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#define MAX_PAGES 10
#define REF_STRING_LEN 100

void generateReferenceString(int *refString, int length);
int fifoPageReplacement(int *refString, int length, int numFrames);
int lruPageReplacement(int *refString, int length, int numFrames);
int optPageReplacement(int *refString, int length, int numFrames);
void printPageFrames(int *frames, int numFrames, int currentPage);
int findLRUPage(int *lastUsed, int numFrames);
int findOptimalPage(int *refString, int startPos, int length, int *frames, int numFrames);
bool isPageInFrames(int page, int *frames, int numFrames);
int findVictimFrame(int *frames, int numFrames, int *refString, int currentPos, int length, char algorithm);

int main(int argc, char *argv[])
{
    // Input validation
    if (argc != 2)
    {
        printf("Usage: %s <number_of_frames>\n", argv[0]);
        return 1;
    }

    int numFrames = atoi(argv[1]);
    if (numFrames <= 0)
    {
        printf("Error: Number of frames must be positive\n");
        return 1;
    }

    // Random number generator
    srand(time(NULL));

    // Generate the random page-reference string
    int refString[REF_STRING_LEN];
    generateReferenceString(refString, REF_STRING_LEN);

    // Print the reference string
    printf("Generated Page Reference String:\n");
    for (int i = 0; i < REF_STRING_LEN; i++)
    {
        printf("%d ", refString[i]);
        if ((i + 1) % 20 == 0)
            printf("\n");
    }
    printf("\n\n");

    // Apply each algorithm and record page faults
    int fifoFaults = fifoPageReplacement(refString, REF_STRING_LEN, numFrames);
    int lruFaults = lruPageReplacement(refString, REF_STRING_LEN, numFrames);
    int optFaults = optPageReplacement(refString, REF_STRING_LEN, numFrames);

    // Display results
    printf("\nPage Replacement Algorithm Comparison:\n");
    printf("===================================\n");
    printf("Number of frames: %d\n", numFrames);
    printf("Reference string length: %d\n\n", REF_STRING_LEN);
    printf("Algorithm\tPage Faults\tFault Rate\n");
    printf("---------------------------------------\n");
    printf("FIFO\t\t%d\t\t%.2f%%\n", fifoFaults, (float)fifoFaults / REF_STRING_LEN * 100);
    printf("LRU\t\t%d\t\t%.2f%%\n", lruFaults, (float)lruFaults / REF_STRING_LEN * 100);
    printf("OPT\t\t%d\t\t%.2f%%\n", optFaults, (float)optFaults / REF_STRING_LEN * 100);

    return 0;
}

// Generates a random page-reference string with page numbers 0 to 9
void generateReferenceString(int *refString, int length)
{
    for (int i = 0; i < length; i++)
    {
        refString[i] = rand() % MAX_PAGES;
    }
}

// Implements the FIFO page replacement algorithm
int fifoPageReplacement(int *refString, int length, int numFrames)
{
    printf("Running FIFO Page Replacement Algorithm:\n");

    int frames[numFrames];
    int pageFaults = 0;
    int nextVictim = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
    }

    // Process each page reference
    for (int i = 0; i < length; i++)
    {
        int currentPage = refString[i];
        bool pageFound = false;

        // Check if page is already in a frame
        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j] == currentPage)
            {
                pageFound = true;
                break;
            }
        }

        // If page fault occurs
        if (!pageFound)
        {
            // Replace the next victim frame with the current page
            frames[nextVictim] = currentPage;
            // Update the next victim pointer
            nextVictim = (nextVictim + 1) % numFrames;
            pageFaults++;

            // Print the status of frames
            if (i < 20)
            {
                printf("Reference %2d: Page %d loaded into frame. Frames: ", i, currentPage);
                printPageFrames(frames, numFrames, currentPage);
                printf("  [Page Fault]\n");
            }
            else if (i == 20)
            {
                printf("... remaining references omitted for brevity ...\n");
            }
        }
        else if (i < 20)
        {
            printf("Reference %2d: Page %d already in frame. Frames: ", i, currentPage);
            printPageFrames(frames, numFrames, currentPage);
            printf("\n");
        }
    }

    printf("\nFIFO Total Page Faults: %d\n\n", pageFaults);
    return pageFaults;
}

/**
 * Implements the LRU page replacement algorithm
 * Returns the number of page faults
 */
int lruPageReplacement(int *refString, int length, int numFrames)
{
    printf("Running LRU Page Replacement Algorithm:\n");

    int frames[numFrames];
    int lastUsed[numFrames];
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    // Process each page reference
    for (int i = 0; i < length; i++)
    {
        int currentPage = refString[i];
        bool pageFound = false;
        int frameIndex = -1;

        // Check if page is already in a frame
        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j] == currentPage)
            {
                pageFound = true;
                frameIndex = j;
                break;
            }
        }

        // If page fault occurs
        if (!pageFound)
        {
            // Find the least recently used frame
            int lruIndex = findLRUPage(lastUsed, numFrames);
            frames[lruIndex] = currentPage;
            lastUsed[lruIndex] = i;
            pageFaults++;
            frameIndex = lruIndex;

            // Print the status of frames
            if (i < 20)
            {
                printf("Reference %2d: Page %d loaded into frame. Frames: ", i, currentPage);
                printPageFrames(frames, numFrames, currentPage);
                printf("  [Page Fault]\n");
            }
            else if (i == 20)
            {
                printf("... remaining references omitted for brevity ...\n");
            }
        }
        else
        {
            // Update the last used time for this frame
            lastUsed[frameIndex] = i;

            if (i < 20)
            {
                printf("Reference %2d: Page %d already in frame. Frames: ", i, currentPage);
                printPageFrames(frames, numFrames, currentPage);
                printf("\n");
            }
        }
    }

    printf("\nLRU Total Page Faults: %d\n\n", pageFaults);
    return pageFaults;
}

// Implements the OPT page replacement algorithm
int optPageReplacement(int *refString, int length, int numFrames)
{
    printf("Running Optimal Page Replacement Algorithm:\n");

    int frames[numFrames];
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
    }

    // Process each page reference
    for (int i = 0; i < length; i++)
    {
        int currentPage = refString[i];
        bool pageFound = false;

        // Check if page is already in a frame
        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j] == currentPage)
            {
                pageFound = true;
                break;
            }
        }

        // If page fault occurs
        if (!pageFound)
        {
            // Check if there's an empty frame
            int emptyFrameIndex = -1;
            for (int j = 0; j < numFrames; j++)
            {
                if (frames[j] == -1)
                {
                    emptyFrameIndex = j;
                    break;
                }
            }

            if (emptyFrameIndex != -1)
            {
                // If there's an empty frame, use it
                frames[emptyFrameIndex] = currentPage;
            }
            else
            {
                // Find the optimal page to replace
                int victimIndex = findOptimalPage(refString, i + 1, length, frames, numFrames);
                frames[victimIndex] = currentPage;
            }

            pageFaults++;

            // Print the status of frames
            if (i < 20)
            {
                printf("Reference %2d: Page %d loaded into frame. Frames: ", i, currentPage);
                printPageFrames(frames, numFrames, currentPage);
                printf("  [Page Fault]\n");
            }
            else if (i == 20)
            {
                printf("... remaining references omitted for brevity ...\n");
            }
        }
        else if (i < 20)
        {
            printf("Reference %2d: Page %d already in frame. Frames: ", i, currentPage);
            printPageFrames(frames, numFrames, currentPage);
            printf("\n");
        }
    }

    printf("\nOptimal Total Page Faults: %d\n\n", pageFaults);
    return pageFaults;
}

// Prints the current state of page frames
void printPageFrames(int *frames, int numFrames, int currentPage)
{
    printf("[");
    for (int i = 0; i < numFrames; i++)
    {
        if (frames[i] == -1)
        {
            printf(" -");
        }
        else if (frames[i] == currentPage)
        {
            printf("%2d*", frames[i]);
        }
        else
        {
            printf("%2d", frames[i]);
        }

        if (i < numFrames - 1)
        {
            printf(", ");
        }
    }
    printf("]");
}

// Finds the index of the least recently used page in the frames
int findLRUPage(int *lastUsed, int numFrames)
{
    int lruIndex = 0;
    int minTime = INT_MAX;

    for (int i = 0; i < numFrames; i++)
    {
        if (lastUsed[i] < minTime)
        {
            minTime = lastUsed[i];
            lruIndex = i;
        }
    }

    return lruIndex;
}

// Finds the optimal page to replace based on future references
int findOptimalPage(int *refString, int startPos, int length, int *frames, int numFrames)
{
    // Create an array to store the next occurrence of each page in the frame
    int nextOccurrence[numFrames];

    // Initialize all next occurrences to infinity
    for (int i = 0; i < numFrames; i++)
    {
        nextOccurrence[i] = INT_MAX;
    }

    // Find next occurrence for each page in the frames
    for (int i = 0; i < numFrames; i++)
    {
        int page = frames[i];
        for (int j = startPos; j < length; j++)
        {
            if (refString[j] == page)
            {
                nextOccurrence[i] = j;
                break;
            }
        }
    }

    // Find the page with the furthest next occurrence
    int optimalIndex = 0;
    int furthestPos = -1;

    for (int i = 0; i < numFrames; i++)
    {
        if (nextOccurrence[i] > furthestPos)
        {
            furthestPos = nextOccurrence[i];
            optimalIndex = i;
        }
    }

    return optimalIndex;
}

// Checks if a page is already in the frames
bool isPageInFrames(int page, int *frames, int numFrames)
{
    for (int i = 0; i < numFrames; i++)
    {
        if (frames[i] == page)
        {
            return true;
        }
    }
    return false;
}