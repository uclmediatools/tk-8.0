/*
	Netvideo version 3.2
	Written by Ron Frederick <frederick@parc.xerox.com>

	Simple hack to translate a Tcl/Tk init file into a C string constant
*/

/*
 * Copyright (c) Xerox Corporation 1992. All rights reserved.
 *  
 * License is granted to copy, to use, and to make and to use derivative
 * works for research and evaluation purposes, provided that Xerox is
 * acknowledged in all documentation pertaining to any such copy or derivative
 * work. Xerox grants no other licenses expressed or implied. The Xerox trade
 * name should not be used in any advertising without its written permission.
 *  
 * XEROX CORPORATION MAKES NO REPRESENTATIONS CONCERNING EITHER THE
 * MERCHANTABILITY OF THIS SOFTWARE OR THE SUITABILITY OF THIS SOFTWARE
 * FOR ANY PARTICULAR PURPOSE.  The software is provided "as is" without
 * express or implied warranty of any kind.
 *  
 * These notices must be retained in any copies of any part of this software.
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef TRUE 
#define TRUE  1
#define FALSE 0
#endif

#ifndef WIN32

int
main(int argc, char **argv)
{
    int c, newline = TRUE;;

    if (argc < 2) {
	fprintf(stderr, "Usage: %s stringname\n", argv[0]);
	exit(1);
    }

    printf("/* This file is automatically generated by tcl2c, do NOT edit by hand! */\n");
    printf("char %s[] = \"\\\n", argv[1]);
    while ((c = getchar()) != EOF) {
            if (newline == TRUE && (isspace(c) || c == '#')) {
                    if (c == '#') {
                            do {
                                    c = getchar();
                            } while(c != EOF && c != '\n');
                    }
            } else {
                    newline = FALSE;
                    switch (c) {
                    case '\n':
                            printf("\\n\\\n");
                            newline = TRUE;
                            break;
                    case '\"':
                            printf("\\\"");
                            break;
                    case '\\':
                            printf("\\\\");
                            break;
                    default:
                            putchar(c);
                    }
            }
    }
    printf("\";\n");
    exit(0);
    /*NOTREACHED*/
    return 0;
}

#else /* WIN32 */

int
main(int argc, char **argv)
{
    int c, n;

    if (argc < 2) {
	fprintf(stderr, "Usage: %s stringname\n", argv[0]);
	exit(1);
    }

    printf("/* This file is automatically generated by tcl2c, do NOT edit by hand! */\n");
    printf("char %s[] = {\n", argv[1]);
    for (n = 0; (c = getchar()) != EOF;)
	printf("%u,%c", c, ((++n & 0xf) == 0) ? '\n' : ' ');

    printf("};\n");
    return 0;  
}

#endif /* WIN32 */
