## Autor
*This project has been created as part of the 42 curriculum by gustde-s.*

# Get Next Line (GNL)

## Description
The Get Next Line (GNL) project consists of coding a C function that reads and returns a single line from a file. 
The most important thigs that i use in this project is static variables, memory allocation, and file manipulation. 
The Gnl is make to read an entire file line by line, perfectly managing memory without leaks, regardless of the `BUFFER_SIZE` defined at compile time.

## Features
- Handles variable chunk sizes efficiently.
- Memory leak-free
- Successfully reads from files and standard input.

## Instructions

### Compilation
To compile the project and use it in your own code, include the header and compile your files alongside the GNL source files. You must specify a `BUFFER_SIZE` macro.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_executable
```

## Usage Example
To test the function, you can use the following `main.c` template:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    // Open a text file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file.\n");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Algorithm Explanation and Justification

The core of the logic is built around a single `static char *remainder` variable. Because it is static, its value persists between consecutive calls, allowing us to store extra characters read from the buffer that belong to the next line.

The algorithm is divided into:

1. **Reading Data (`keep_read`)**: 
   A temporary buffer is allocated to read data from the file descriptor in chunks of `BUFFER_SIZE`. Using `read()`, the function loops and appends each new chunk to the static `remainder` variable using `ft_strjoin`. The loop stops when a newline (`\n`) is found within the static variable or when `read()` returns 0 (End of File). If `read()` fails (returns -1).

2. **Extracting the Line (`extract_line`)**:
   Once reading halts, this function parses the `remainder` string. It iterates to find the length of the current line up to the `\n`. It then allocates the exact memory needed (`i + 2` to account for the `\n` and the null terminator `\0`), copies the characters, and returns the cleanly formatted line.

3. **Updating the Remainder (`update_remainder`)**:
   After the current line is extracted, the `remainder` still holds characters that belong to subsequent lines. This function calculates the size of the leftover data (`ft_strlen(remainder) - i + 1`), allocates a new string (`new_remainder`), and copies the remaining data into it. Finally, it explicitly calls `free(remainder)` on the old string to prevent memory leaks before returning the new static pointer.

This structure was chosen to guarantee that memory is constantly managed at every stage of the pipeline, preventing overlapping pointers and segmentation faults.

## Resources
* **System calls**: `man 2 read`, `man 3 malloc`, `man 3 free`.
* **Concept Reference**: [Understanding C Static Variables](https://en.wikipedia.org/wiki/Static_variable).
* **AI Usage Statement**: The AI was used to trace memory execution paths to identify a missing `free()` call, and to correct the mathematical logic for the `malloc` size calculation (`ft_strlen(remainder) - i + 1`) inside the `update_remainder` function.