#ifndef MonkeyConfig_H
#define MonkeyConfig_H

// version macros
#define Monkey_MAJOR_VERSION 0
#define Monkey_MINOR_VERSION 0
#define Monkey_PATCH_LEVEL 0

#define Monkey_VERSION_STR "0.0.0"

#define Monkey_VERSION_GE( MAJV , MINV , PLEV )  \
     ( (Monkey_MAJOR_VERSION > MAJV) || ( (Monkey_MAJOR_VERSION == MAJV) && (Monkey_MINOR_VERSION > MINV) ) \
  || ( (Monkey_MAJOR_VERSION == MAJV) && (Monkey_MINOR_VERSION == MINV) && (Monkey_PATCH_LEVEL >= PLEV) ) )

// project source dir
#define Monkey_DIR "/home/rete/soft/monkey"

#endif // MonkeyConfig_H
