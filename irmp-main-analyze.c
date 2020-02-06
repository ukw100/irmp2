

#include "irmp.c"



#ifdef ANALYZE

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * main functions - for Unix/Linux + Windows only!
 *
 * AVR: see main.c!
 *
 * Compile it under linux with:
 * cc irmp.c -o irmp
 *
 * usage: ./irmp [-v|-s|-a|-l] < file
 *
 * options:
 *   -v verbose
 *   -s silent
 *   -a analyze
 *   -l list pulse/pauses
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

void
print_spectrum (const char * text, int * buf, int is_pulse)
{
    int     i;
    int     j;
    int     min;
    int     max;
    int     max_value = 0;
    int     value;
    int     sum = 0;
    int     counter = 0;
    double  average = 0;
    double  tolerance;

    puts ("-----------------------------------------------------------------------------");
    printf ("%s:\n", text);

    for (i = 0; i < 256; i++)
    {
        if (buf[i] > max_value)
        {
            max_value = buf[i];
        }
    }

    for (i = 1; i < 200; i++)
    {
        if (buf[i] > 0)
        {
            printf ("%3d ", i);
            value = (buf[i] * 60) / max_value;

            for (j = 0; j < value; j++)
            {
                putchar ('o');
            }
            printf (" %d\n", buf[i]);

            sum += i * buf[i];
            counter += buf[i];
        }
        else
        {
            max = i - 1;

            if (counter > 0)
            {
                average = (float) sum / (float) counter;

                if (is_pulse)
                {
                    printf ("pulse ");
                }
                else
                {
                    printf ("pause ");
                }

                printf ("avg: %4.1f=%6.1f us, ", average, (1000000. * average) / (float) F_INTERRUPTS);
                printf ("min: %2d=%6.1f us, ", min, (1000000. * min) / (float) F_INTERRUPTS);
                printf ("max: %2d=%6.1f us, ", max, (1000000. * max) / (float) F_INTERRUPTS);

                tolerance = (max - average);

                if (average - min > tolerance)
                {
                    tolerance = average - min;
                }

                tolerance = tolerance * 100 / average;
                printf ("tol: %4.1f%%\n", tolerance);
            }

            counter = 0;
            sum = 0;
            min = i + 1;
        }
    }
}

#define STATE_LEFT_SHIFT    0x01
#define STATE_RIGHT_SHIFT   0x02
#define STATE_LEFT_CTRL     0x04
#define STATE_LEFT_ALT      0x08
#define STATE_RIGHT_ALT     0x10

#define KEY_ESCAPE          0x1B            // keycode = 0x006e
#define KEY_MENUE           0x80            // keycode = 0x0070
#define KEY_BACK            0x81            // keycode = 0x0071
#define KEY_FORWARD         0x82            // keycode = 0x0072
#define KEY_ADDRESS         0x83            // keycode = 0x0073
#define KEY_WINDOW          0x84            // keycode = 0x0074
#define KEY_1ST_PAGE        0x85            // keycode = 0x0075
#define KEY_STOP            0x86            // keycode = 0x0076
#define KEY_MAIL            0x87            // keycode = 0x0077
#define KEY_FAVORITES       0x88            // keycode = 0x0078
#define KEY_NEW_PAGE        0x89            // keycode = 0x0079
#define KEY_SETUP           0x8A            // keycode = 0x007a
#define KEY_FONT            0x8B            // keycode = 0x007b
#define KEY_PRINT           0x8C            // keycode = 0x007c
#define KEY_ON_OFF          0x8E            // keycode = 0x007c

#define KEY_INSERT          0x90            // keycode = 0x004b
#define KEY_DELETE          0x91            // keycode = 0x004c
#define KEY_LEFT            0x92            // keycode = 0x004f
#define KEY_HOME            0x93            // keycode = 0x0050
#define KEY_END             0x94            // keycode = 0x0051
#define KEY_UP              0x95            // keycode = 0x0053
#define KEY_DOWN            0x96            // keycode = 0x0054
#define KEY_PAGE_UP         0x97            // keycode = 0x0055
#define KEY_PAGE_DOWN       0x98            // keycode = 0x0056
#define KEY_RIGHT           0x99            // keycode = 0x0059
#define KEY_MOUSE_1         0x9E            // keycode = 0x0400
#define KEY_MOUSE_2         0x9F            // keycode = 0x0800

static uint_fast8_t
get_fdc_key (uint_fast16_t cmd)
{
    static const uint8_t key_table[128] =
    {
     // 0     1      2    3    4     5    6    7    8     9     A     B     C     D     E     F
        0x00, '^',  '1', '2', '3',  '4', '5', '6', '7',  '8',  '9',  '0',  0xDF, 0xB4,  0x00, '\b',
        '\t', 'q',  'w', 'e', 'r',  't', 'z', 'u', 'i',  'o',  'p',  0xFC, '+',  0x00,  0x00, 'a',
        's',  'd',  'f', 'g', 'h',  'j', 'k', 'l', 0xF6, 0xE4, '#',  '\r', 0x00, '<',   'y',  'x',
        'c',  'v',  'b', 'n', 'm',  ',', '.', '-', 0x00, 0x00, 0x00, 0x00, 0x00,  ' ',  0x00, 0x00,

        0x00, 0xB0, '!', '"', 0xA7, '$', '%', '&', '/',  '(',  ')',  '=',  '?',  0x60,  0x00, '\b',
        '\t', 'Q',  'W', 'E', 'R',  'T', 'Z', 'U', 'I',  'O',  'P',  0xDC, '*',  0x00,  0x00, 'A',
        'S',  'D',  'F', 'G', 'H',  'J', 'K', 'L', 0xD6, 0xC4, '\'', '\r', 0x00, '>',   'Y',  'X',
        'C',  'V',  'B', 'N', 'M',  ';', ':', '_', 0x00, 0x00, 0x00, 0x00, 0x00, ' ',   0x00, 0x00
    };
    static uint_fast8_t state;

    uint_fast8_t key = 0;

    switch (cmd)
    {
        case 0x002C: state |=  STATE_LEFT_SHIFT;    break;              // pressed left shift
        case 0x00AC: state &= ~STATE_LEFT_SHIFT;    break;              // released left shift
        case 0x0039: state |=  STATE_RIGHT_SHIFT;   break;              // pressed right shift
        case 0x00B9: state &= ~STATE_RIGHT_SHIFT;   break;              // released right shift
        case 0x003A: state |=  STATE_LEFT_CTRL;     break;              // pressed left ctrl
        case 0x00BA: state &= ~STATE_LEFT_CTRL;     break;              // released left ctrl
        case 0x003C: state |=  STATE_LEFT_ALT;      break;              // pressed left alt
        case 0x00BC: state &= ~STATE_LEFT_ALT;      break;              // released left alt
        case 0x003E: state |=  STATE_RIGHT_ALT;     break;              // pressed left alt
        case 0x00BE: state &= ~STATE_RIGHT_ALT;     break;              // released left alt

        case 0x006e: key = KEY_ESCAPE;              break;
        case 0x004b: key = KEY_INSERT;              break;
        case 0x004c: key = KEY_DELETE;              break;
        case 0x004f: key = KEY_LEFT;                break;
        case 0x0050: key = KEY_HOME;                break;
        case 0x0051: key = KEY_END;                 break;
        case 0x0053: key = KEY_UP;                  break;
        case 0x0054: key = KEY_DOWN;                break;
        case 0x0055: key = KEY_PAGE_UP;             break;
        case 0x0056: key = KEY_PAGE_DOWN;           break;
        case 0x0059: key = KEY_RIGHT;               break;
        case 0x0400: key = KEY_MOUSE_1;             break;
        case 0x0800: key = KEY_MOUSE_2;             break;

        default:
        {
            if (!(cmd & 0x80))                      // pressed key
            {
                if (cmd >= 0x70 && cmd <= 0x7F)     // function keys
                {
                    key = cmd + 0x10;               // 7x -> 8x
                }
                else if (cmd < 64)                  // key listed in key_table
                {
                    if (state & (STATE_LEFT_ALT | STATE_RIGHT_ALT))
                    {
                        switch (cmd)
                        {
                            case 0x0003: key = 0xB2;    break; // upper 2
                            case 0x0008: key = '{';     break;
                            case 0x0009: key = '[';     break;
                            case 0x000A: key = ']';     break;
                            case 0x000B: key = '}';     break;
                            case 0x000C: key = '\\';    break;
                            case 0x001C: key = '~';     break;
                            case 0x002D: key = '|';     break;
                            case 0x0034: key = 0xB5;    break; // Mu
                        }
                    }
                    else if (state & (STATE_LEFT_CTRL))
                    {
                        if (key_table[cmd] >= 'a' && key_table[cmd] <= 'z')
                        {
                            key = key_table[cmd] - 'a' + 1;
                        }
                        else
                        {
                            key = key_table[cmd];
                        }
                    }
                    else
                    {
                        int idx = cmd + ((state & (STATE_LEFT_SHIFT | STATE_RIGHT_SHIFT)) ? 64 : 0);

                        if (key_table[idx])
                        {
                            key = key_table[idx];
                        }
                    }
                }
            }
            break;
        }
    }

    return (key);
}

static int         analyze = FALSE;
static int         list = FALSE;
static IRMP_DATA   irmp_data;
static int         expected_protocol;
static int         expected_address;
static int         expected_command;
static int         do_check_expected_values;

static void
next_tick (void)
{
    if (! analyze && ! list)
    {
        (void) irmp_ISR ();

        if (irmp_get_data (&irmp_data))
        {
            uint_fast8_t key;

            ANALYZE_ONLY_NORMAL_PUTCHAR (' ');

            if (verbose)
            {
                printf ("%8.3fms ", (float) (time_counter * 1000) / F_INTERRUPTS);
            }

            if (irmp_data.protocol == IRMP_ACP24_PROTOCOL)
            {
                uint16_t    temp = (irmp_data.command & 0x000F) + 15;

                printf ("p=%2d (%s), a=0x%04x, c=0x%04x, f=0x%02x, temp=%d",
                        irmp_data.protocol, irmp_protocol_names[irmp_data.protocol], irmp_data.address, irmp_data.command, irmp_data.flags, temp);
            }
            else if (irmp_data.protocol == IRMP_FDC_PROTOCOL && (key = get_fdc_key (irmp_data.command)) != 0)
            {
                if ((key >= 0x20 && key < 0x7F) || key >= 0xA0)
                {
                    printf ("p=%2d (%s), a=0x%04x, c=0x%04x, f=0x%02x, asc=0x%02x, key='%c'",
                            irmp_data.protocol,  irmp_protocol_names[irmp_data.protocol], irmp_data.address, irmp_data.command, irmp_data.flags, key, key);
                }
                else if (key == '\r' || key == '\t' || key == KEY_ESCAPE || (key >= 0x80 && key <= 0x9F))                 // function keys
                {
                    const char * p = (const char *) NULL;

                    switch (key)
                    {
                        case '\t'                : p = "TAB";           break;
                        case '\r'                : p = "CR";            break;
                        case KEY_ESCAPE          : p = "ESCAPE";        break;
                        case KEY_MENUE           : p = "MENUE";         break;
                        case KEY_BACK            : p = "BACK";          break;
                        case KEY_FORWARD         : p = "FORWARD";       break;
                        case KEY_ADDRESS         : p = "ADDRESS";       break;
                        case KEY_WINDOW          : p = "WINDOW";        break;
                        case KEY_1ST_PAGE        : p = "1ST_PAGE";      break;
                        case KEY_STOP            : p = "STOP";          break;
                        case KEY_MAIL            : p = "MAIL";          break;
                        case KEY_FAVORITES       : p = "FAVORITES";     break;
                        case KEY_NEW_PAGE        : p = "NEW_PAGE";      break;
                        case KEY_SETUP           : p = "SETUP";         break;
                        case KEY_FONT            : p = "FONT";          break;
                        case KEY_PRINT           : p = "PRINT";         break;
                        case KEY_ON_OFF          : p = "ON_OFF";        break;

                        case KEY_INSERT          : p = "INSERT";        break;
                        case KEY_DELETE          : p = "DELETE";        break;
                        case KEY_LEFT            : p = "LEFT";          break;
                        case KEY_HOME            : p = "HOME";          break;
                        case KEY_END             : p = "END";           break;
                        case KEY_UP              : p = "UP";            break;
                        case KEY_DOWN            : p = "DOWN";          break;
                        case KEY_PAGE_UP         : p = "PAGE_UP";       break;
                        case KEY_PAGE_DOWN       : p = "PAGE_DOWN";     break;
                        case KEY_RIGHT           : p = "RIGHT";         break;
                        case KEY_MOUSE_1         : p = "KEY_MOUSE_1";   break;
                        case KEY_MOUSE_2         : p = "KEY_MOUSE_2";   break;
                        default                  : p = "<UNKNWON>";     break;
                    }

                    printf ("p=%2d (%s), a=0x%04x, c=0x%04x, f=0x%02x, asc=0x%02x, key=%s",
                            irmp_data.protocol, irmp_protocol_names[irmp_data.protocol], irmp_data.address, irmp_data.command, irmp_data.flags, key, p);
                }
                else
                {
                    printf ("p=%2d (%s), a=0x%04x, c=0x%04x, f=0x%02x, asc=0x%02x",
                            irmp_data.protocol,  irmp_protocol_names[irmp_data.protocol], irmp_data.address, irmp_data.command, irmp_data.flags, key);
                }
            }
            else
            {
                printf ("p=%2d (%s), a=0x%04x, c=0x%04x, f=0x%02x",
                        irmp_data.protocol, irmp_protocol_names[irmp_data.protocol], irmp_data.address, irmp_data.command, irmp_data.flags);
            }

            if (do_check_expected_values)
            {
                if (irmp_data.protocol != expected_protocol ||
                    irmp_data.address  != expected_address  ||
                    irmp_data.command  != expected_command)
                {
                    printf ("\nerror 7: expected values differ: p=%2d (%s), a=0x%04x, c=0x%04x\n",
                            expected_protocol, irmp_protocol_names[expected_protocol], expected_address, expected_command);
                }
                else
                {
                    printf (" checked!\n");
                }
                do_check_expected_values = FALSE;                           // only check 1st frame in a line!
            }
            else
            {
                putchar ('\n');
            }
        }
    }
}

int
main (int argc, char ** argv)
{
    int         i;
    int         ch;
    int         last_ch = 0;
    int         pulse = 0;
    int         pause = 0;

    int         start_pulses[256];
    int         start_pauses[256];
    int         pulses[256];
    int         pauses[256];

    int         first_pulse = TRUE;
    int         first_pause = TRUE;
    printf("IRMP F_INTERRUPTS = %u\n", F_INTERRUPTS);
    if (argc == 2)
    {
        if (! strcmp (argv[1], "-v"))
        {
            verbose = TRUE;
        }
        else if (! strcmp (argv[1], "-l"))
        {
            list = TRUE;
        }
        else if (! strcmp (argv[1], "-a"))
        {
            analyze = TRUE;
        }
        else if (! strcmp (argv[1], "-s"))
        {
            silent = TRUE;
        }
        else if (! strcmp (argv[1], "-r"))
        {
            radio = TRUE;
        }
    }

    for (i = 0; i < 256; i++)
    {
        start_pulses[i] = 0;
        start_pauses[i] = 0;
        pulses[i] = 0;
        pauses[i] = 0;
    }

    IRMP_PIN = 0xFF;

    while ((ch = getchar ()) != EOF)
    {
        if (ch == '_' || ch == '0')
        {
            if (last_ch != ch)
            {
                if (pause > 0)
                {
                    if (list)
                    {
                        printf ("pause: %d\n", pause);
                    }

                    if (analyze)
                    {
                        if (first_pause)
                        {
                            if (pause < 256)
                            {
                                start_pauses[pause]++;
                            }
                            first_pause = FALSE;
                        }
                        else
                        {
                            if (pause < 256)
                            {
                                pauses[pause]++;
                            }
                        }
                    }
                }
                pause = 0;
            }
            pulse++;
            IRMP_PIN = 0x00;
        }
        else if (ch == 0xaf || ch == '-' || ch == '1')
        {
            if (last_ch != ch)
            {
                if (list)
                {
                    printf ("pulse: %d ", pulse);
                }

                if (analyze)
                {
                    if (first_pulse)
                    {
                        if (pulse < 256)
                        {
                            start_pulses[pulse]++;
                        }
                        first_pulse = FALSE;
                    }
                    else
                    {
                        if (pulse < 256)
                        {
                            pulses[pulse]++;
                        }
                    }
                }
                pulse = 0;
            }

            pause++;
            IRMP_PIN = 0xff;
        }
        else if (ch == '\n')
        {
            IRMP_PIN = 0xff;
            time_counter = 0;

            if (list && pause > 0)
            {
                printf ("pause: %d\n", pause);
            }
            pause = 0;

            if (! analyze)
            {
                for (i = 0; i < (int) ((10000.0 * F_INTERRUPTS) / 10000); i++)               // newline: long pause of 10000 msec
                {
                    next_tick ();
                }
            }
            first_pulse = TRUE;
            first_pause = TRUE;
        }
        else if (ch == '#')
        {
            time_counter = 0;

            if (analyze)
            {
                while ((ch = getchar()) != '\n' && ch != EOF)
                {
                    ;
                }
            }
            else
            {
                char            buf[1024];
                char *          p;
                int             idx = -1;

                puts ("----------------------------------------------------------------------");
                putchar (ch);


                while ((ch = getchar()) != '\n' && ch != EOF)
                {
                    if (ch != '\r')                                                         // ignore CR in DOS/Windows files
                    {
                        if (ch == '[' && idx == -1)
                        {
                            idx = 0;
                        }
                        else if (idx >= 0)
                        {
                            if (ch == ']')
                            {
                                do_check_expected_values = FALSE;
                                buf[idx] = '\0';
                                idx = -1;

                                expected_protocol = atoi (buf);

                                if (expected_protocol > 0)
                                {
                                    p = buf;
                                    while (*p)
                                    {
                                        if (*p == 'x')
                                        {
                                            p++;

                                            if (sscanf (p, "%x", &expected_address) == 1)
                                            {
                                                do_check_expected_values = TRUE;
                                            }
                                            break;
                                        }
                                        p++;
                                    }

                                    if (do_check_expected_values)
                                    {
                                        do_check_expected_values = FALSE;

                                        while (*p)
                                        {
                                            if (*p == 'x')
                                            {
                                                p++;

                                                if (sscanf (p, "%x", &expected_command) == 1)
                                                {
                                                    do_check_expected_values = TRUE;
                                                }
                                                break;
                                            }
                                            p++;
                                        }

                                        if (do_check_expected_values)
                                        {
                                            // printf ("!%2d %04x %04x!\n", expected_protocol, expected_address, expected_command);
                                        }
                                    }
                                }
                            }
                            else if (idx < 1024 - 2)
                            {
                                buf[idx++] = ch;
                            }
                        }
                        putchar (ch);
                    }
                }
                putchar ('\n');
            }

        }

        last_ch = ch;

        next_tick ();
    }

    if (analyze)
    {
        print_spectrum ("START PULSES", start_pulses, TRUE);
        print_spectrum ("START PAUSES", start_pauses, FALSE);
        print_spectrum ("PULSES", pulses, TRUE);
        print_spectrum ("PAUSES", pauses, FALSE);
        puts ("-----------------------------------------------------------------------------");
    }
    return 0;
}

#endif // ANALYZE


