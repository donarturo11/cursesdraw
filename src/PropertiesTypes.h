#ifndef PROPERTIESTYPES_H
#define PROPERTIESTYPES_H
typedef struct objectProps {
    int width=0;
    int height=0;
    int x=0;
    int y=0;
} objectProps;

typedef struct position {
    int x=0;
    int y=0;
} position;

typedef struct Range {
    int min=0;
    int max=0;
} Range;
#endif
