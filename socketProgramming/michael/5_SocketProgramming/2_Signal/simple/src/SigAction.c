#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	DieWithError(char *errorMessage);
void	InterruptSignalHandler(int signalType);

int main(int argc, char* argv[])
{
	// 1.Set up signal handler
	struct sigaction	handler;

	handler.sa_handler = InterruptSignalHandler;
	if (sigfillset(&handler.sa_mask) < 0)
		DieWithError("sigfillset() failed");

	handler.sa_flags = 0;

	if (sigaction(SIGINT, &handler, 0) < 0)
		DieWithError("sigaction() failed");

	// 2.Repeat until catch SIGINT
		for(;;)
			pause();

	exit(EXIT_SUCCESS);;
}

// 3.Handler function
void	InterruptSignalHandler(int signalType)
{
	printf("Interrupt Received. Exiting program.\n");
	exit(EXIT_FAILURE);
}
