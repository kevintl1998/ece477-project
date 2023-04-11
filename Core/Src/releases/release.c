#include "releases/release.h"

#include "game.h"

/*
 * Consider this the entrypoint when RELEASE_TYPE in settings.h is set to RELEASE
 */
int release(void) {

	init_hardware();
	init_game();
	start_game();

	return 1;
}
