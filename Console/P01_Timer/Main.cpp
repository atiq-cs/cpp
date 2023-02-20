//------------------------------------------------------------------------------
// Title   : ANSI C Timer Program
// Author  : Atiq Rahman
// Date    : 06-12-2011 (updated texts and safer string functions 02-2023)
//
// Notes   : A Console application for implementing timer
//      - As we know a direct sleep command is not available on windows.
//      - Hence, we implement this along with a running timer so we can track how
//       much time is remaining.
//      - ANSI C Program, highly optimized but tedius code
//        
// Applications:
//      - Unix/Linux Shell Scripts.
//      - Windows batch or powershell scripts
//
// Demos,
//   - strtok
//   - sprintf
//   - ifdef to cover multiple platforms
//      ref, SO - Boolean in ifdef: https://stackoverflow.com/q/1312132
//
// Usage and Refs on ReadMe.
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
// Windows, ref, Predefined macros
//   https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros
#if defined (_WIN32) || defined (_WIN64)
#include <windows.h>
// Unix
#else
#include <stdlib.h>
#include<unistd.h>
#endif

int main (int argc, char *argv[]) {
  char *token;
  char formatstr[100];
  char sep[] = ":";
  char *next_token = NULL;
  bool nonzerof = true;

  int delay, i, res;
  size_t formatlen = 0;
  size_t prelen = 0;

  if (argc<2)
  {
    puts("Argument: Time (HH:MM:SS) is missing!");
    return 0;
  }
  else if (argc>2) {
    printf("More than one argument provided: %d\n", (argc-1));
    return 0;
  }

  // Split first token
  token = strtok_s(argv[1], sep, &next_token);
  //printf("Current token: %s\n", token);
  res = atoi(token);
  if (res >= 0)
    delay = res;
  else {
    printf("Invalid token: %s in time argument!\n", token);
    return 0;
  }

  i = 0;

  // Split hours, minute and seconds
  while (token = strtok_s(NULL, sep, &next_token))
  {
    if (token) {
      res = atoi(token);

      if (res < 60)
        delay = delay * 60 + res;
      else {
        printf("Invalid token: %s!\n", token);
        return 0;
      }
      //printf("Current token: %s\n", token);
    }

    if (++i > 2)
    {
      puts("Too many seperator colons!");
      return 0;
    }
  }


  if (delay > 24 * 60 * 60)
    puts("****  Warning: delay more than 24 hours  ****");


  for (i=0; i<delay; i++)
  {
    res = (delay - i) / 3600;
    // On Unix we had following instead of next two lines, not sure if that matters
    // sprintf(formatstr, "\rTo Elapse:");
    putchar('\r');
    sprintf_s(formatstr, sizeof(formatstr), "To elapse:");
    formatlen = strlen(formatstr);

    // Display remaining hours
    if (res) {
      sprintf_s(&formatstr[formatlen], sizeof(formatstr) - formatlen,  " %dh", res);
      formatlen = strlen(formatstr);
      // printf(" %dh", res);
      nonzerof = false;
    }

    // Display remaining minutes
    res = (delay-i)%3600;
    res /= 60;
    if (res) {
      // printf(" %dm", res);
      sprintf_s(&formatstr[formatlen], sizeof(formatstr) - formatlen, " %dm", res);
      formatlen = strlen(formatstr);
      nonzerof = false;
    }

    // Display remaining seconds
    res = (delay-i)%3600;
    res %= 60;
    if (res || nonzerof) {
      sprintf_s(&formatstr[formatlen], sizeof(formatstr) - formatlen, " %ds", res);
      formatlen = strlen(formatstr);
      // printf(" %ds", res);
    }

    if (prelen && prelen > formatlen) {
      size_t j;

      for (j = formatlen; j<prelen; j++)
        formatstr[j] = ' ';

      formatstr[j] = '\0';
    }

    printf(formatstr);

    // if (prelen && prelen > formatlen) {
    //     int diff = prelen - formatlen;
    //     for (int j=0; j<diff; j++)
    //         printf(" ");
    // }

    prelen = formatlen;

    #if defined (_WIN32) || defined (_WIN64)
      Sleep(1000);
    #else
      fflush(stdout);
      sleep(1);
    #endif
  }

  putchar('\r');

  nonzerof = true;
  putchar(' ');

  res = delay / 3600;
  if (res)
    printf("%dh ", res);

  res = delay%3600;
  res /= 60;
  if (res) {
    printf("%dm ", res);
    nonzerof = false;
  }

  res = delay%3600;
  res %= 60;
  if (res || nonzerof)
    printf("%ds", res);

  puts(" elapsed.       ");

  return 0;
}
