#include "userCommand.h"
#include "fsNode.h"

extern FSNODE *root;

char *test_mkDir_emptyRoot();
char *test_mkDir_invalid();
char *test_mkDir_noPath();
char *test_mkDir_absolute();
char *test_mkDir_relative();
char *test_mkDir_noDupes();
