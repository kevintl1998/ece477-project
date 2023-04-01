#include "releases/entry.h"
#include "stm32f0xx.h"
#include "stm32f091xc.h"

#include "settings.h"

#include "releases/release.h"
#include "releases/debug.h"
#include "releases/unit_test.h"


int other(void);

int entry(void) {
#if RELEASE_TYPE == RELEASE
    return release();
#elif RELEASE_TYPE == DEBUG
    return debug();
#elif RELEASE_TYPE == UNIT_TEST
    return unit_test();
#else
    return other();
#endif

    for(;;);
}


int other(void) {
    // extra function because you never know when you might need it
    return 0;
}
