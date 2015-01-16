#ifndef UGID_FUCNITONS_H
#define UGID_FUCNITONS_H

#include <ctype.h>

char * userNameFromId(uid_t uid);
uid_t userIdFromName(const char* name);
char * groupNameFromId(gid_t gid);
gid_t groupIdFromName(const char* name);

#endif
