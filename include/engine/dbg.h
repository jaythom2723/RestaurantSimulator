#ifndef DBG_H_INCLUDED
#define DBG_H_INCLUDED

namespace resimdbg
{
    typedef enum {
        ERRTYPE_FAIL_INIT_SDL,
        ERRTYPE_FAIL_CREATE_WND,
        ERRTYPE_FAIL_LOAD_IMAGE,
        ERRTYPE_FAIL_CREATE_RND
    } ErrorType;

    // returns true if their was an error, false if no error
    bool pushErrorCheck(ErrorType t, bool cond);
}

#endif // DBG_H_INCLUDED
