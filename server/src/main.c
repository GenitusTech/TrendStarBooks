
#include <signal.h>
#include "include/utils.h"
#include "model/model.h"

static volatile sig_atomic_t running = 1;

void handle_signal(int sig) {
    running = 0;
}

int main(void) {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    model_init();

    ft_putstr("Starting web service on port 8080...\n");
    // start_web_service(8080);

    return 0;
}
