#include "command_excute.h"
#include "mixer.h"

void command_excute(char* buf)
{
	char* argv[10];
	uint8_t num_arg = 0;
	char* token = strtok(buf," ");
	while(token != NULL)
	{
		argv[num_arg++] = token;
		token = strtok(NULL, " ");
	}
	mixer_output(argv);
}
