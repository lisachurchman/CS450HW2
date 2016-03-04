#include <stdio.h>
#include "constants.h"
#include "parsetools.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void syserror( const char * );

int main() {
    // Buffer for reading one line of input
    char line[MAX_LINE_CHARS];
    char* line_words[MAX_LINE_WORDS + 1];

    pid_t pid;
    // Loop until user hits Ctrl-D (end of input)
    // or some other input error occurs
    while( fgets(line, MAX_LINE_CHARS, stdin) ) {
      int num_words = split_cmd_line(line, line_words);
      
      // Just for demonstration purposes
      //for (int i=0; i < num_words; i++)
        //    printf("%s\n", line_words[i]);
      switch(pid = fork() ){
      case -1:
	syserror("Failed to fork");
      case 0:
	//for (int i=0; i< num_words; i++)
	execlp("\""line_words[0] "\",\"" line_words[0]
	       "\",\"" line_words[1]"\", NULL");
      }
    }
    
    return 0;
}

void syserror(const char *s)
{
  extern int errno;

  fprintf( stderr, "%s\n", s );
  fprintf( stderr, " (%s)\n", strerror(errno) );
  exit( 1 );
}
