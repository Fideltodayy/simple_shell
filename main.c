#include "main.h"

/**
 * main - The main function of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, otherwise error codes.
 */
int main(int argc, char **argv)
{
	/* Initialize the info data structure */
	info_type info[] = { INFO_INIT };
	/* Initialize the file descriptor to 2 */
	int file_descriptor = 2;
	/* Inline assembly to modify the file descriptor */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));
	/* Check the number of command-line arguments */
	if (argc == 2)
	{
		/* Attempt to open the specified file */
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			/* Handle different error cases */
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file_descriptor;
	}
	/* Populate environment list */
	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
