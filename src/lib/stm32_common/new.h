#ifndef _NEW_H
#define _NEW_H

inline void* operator new  (size_t n) {return ::malloc(n);}

#endif