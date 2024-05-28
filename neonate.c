#include "terminal.h"
void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

iv neonate_fn(char *arr, int start, iv vals)
{

    start += 11;
    int length = strlen(arr);
    char *timeing = malloc(10);
    int d = 0;
    for (int i = start; i < length; i++)
        timeing[d++] = arr[start++];
    timeing[d] = '\0';
    d = 0;
    int time = strtoint(timeing);
    char *inp = malloc(sizeof(char) * 100);
    char c;
    char *buffer = malloc(MaxLimit);

    char *path = "/proc/loadavg";
    int cpid = fork();
    if (cpid > 0)
    {

        setbuf(stdout, NULL);
        enableRawMode();
        memset(inp, '\0', 100);
        int pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (iscntrl(c))
            {
                if (c == 27)
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2)
                    { // length of escape code
                        printf("\rarrow key: %s", buf);
                    }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (inp[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        inp[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character
                    inp[pt++] = c;
                    for (int i = 0; i < 8; i++)
                    { // TABS should be 8 spaces
                        printf(" ");
                    }
                }
                else if (c == 4)
                {
                    // exit(0);
                }
                else
                {
                    // printf("%d\n", c);
                }
            }
            else
            {
                if (c == 120)
                {
                    kill(cpid,9);
                    disableRawMode();
                    return vals;
                    break;
                }
                inp[pt++] = c;
            }

        }
    }
    else
    {
        while (1)
        {
            FILE *fptr = fopen(path, "r");
            fgets(buffer, MaxLimit, fptr);
            // printf("%s\n", buffer);
            fclose(fptr);
            length = strlen(buffer);
            int sno = 0;
            d = 0;
            for (int i = 0; i < length; i++)
            {
                if (buffer[i] == ' ')
                    sno++;
                else if (sno == 4)
                {
                    if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\0')
                        break;
                    timeing[d++] = buffer[i];
                }
            }
            timeing[d] = '\0';
            int pid = strtoint(timeing);
            printf("%d\n", pid);
            sleep(time);
        }
    }

    return vals;
}