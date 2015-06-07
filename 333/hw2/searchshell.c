/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "memindex.h"
#include "filecrawler.h"

static void Usage(void);
char *gets(char *str);

void freePayload(LLPayload_t payload) { free(payload); }

int main(int argc, char **argv) {
  if (argc != 2) Usage();

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //

  //  - crawl from a directory provided by argv[1] to produce and index
  int res;
  DocTable dt;
  MemIndex idx;

  // check if "docroot" is an actual directory
  // print usage if not

  // print Indexing... then CrawlFileTree
  printf("Indexing '%s'\n", argv[1]);
  res = CrawlFileTree(argv[1], &dt, &idx);
  if (res != 1) {
    FreeDocTable(dt);
    FreeMemIndex(idx);
    Usage();
  }

  while (1) {
    //  - prompt the user for a query and read the query from stdin, in a loop
    char input[1024];  // huge buffer yaass
    // loop print "enter query:\n"
    printf("enter query:\n");
    gets(input);
    int eof = feof(stdin);
    if (eof == 1) {
      // received a ctrl+D
      printf("shutting down...\n");
      FreeDocTable(dt);
      FreeMemIndex(idx);
      return EXIT_SUCCESS;
    }
    //  - split a query into words (check out strtok_r)
    char *tokens[1024];
    tokens[0] = strtok(input, " ");
    int i = 0;
    while (tokens[i] != NULL) {
      i++;
      tokens[i] = strtok(NULL, " ");
    }
    LinkedList results = MIProcessQuery(idx, tokens, i);
    if (results == NULL) {
      continue;
    }
    LLIter resultsIter = LLMakeIterator(results, 0);
    //  - process a query against the index and print out the results
    do {
      LLPayload_t payload;
      LLIteratorGetPayload(resultsIter, &payload);
      SearchResult *result = (SearchResult *)payload;
      // need to grab docstring from doctable
      char *filename = DTLookupDocID(dt, result->docid);
      printf("\t%s (%d)\n", filename, result->rank);
    } while (LLIteratorNext(resultsIter));
    LLIteratorFree(resultsIter);
    FreeLinkedList(results, &freePayload);
  }

  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.

  return EXIT_SUCCESS;
}

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative "
          "path to a directory to build an index under.\n");
  exit(-1);
}
