#include "main.h"

/**
 * input_buf - Read user input into the input buffer.
 * @info: A pointer to the info_type structure containing input and
 *        history information.
 * @buf: A pointer to the input buffer.
 * @len: A pointer to the length of the input buffer.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_type *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t buffer_length_tmp = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_interrupt_signal);
#if USE_GETLINE
		bytes_read = getline(buf, &buffer_length_tmp, stdin);
#else
		bytes_read = _getline(info, buf, &buffer_length_tmp);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				/* Remove trailing newline */
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			/* Check for command chaining here. */
			*len = bytes_read;
			info->cmd_buf = buf;
		}
	}
	return (bytes_read);
}

/**
 * get_input - Retrieve user input, handling command chaining.
 * @info: A pointer to the info_type structure containing input
 *        and history information.
 *
 * Return: The length of the current command in the buffer or -1 on EOF.
 */
ssize_t get_input(info_type *info)
{
	static char *chain_buffer; /* Buffer for command chaining */
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH); /* Flush the output buffer. */
	bytes_read = input_buf(info, &chain_buffer, &len);
	if (bytes_read == -1) /* If EOF */
		return (-1);
	if (len)	/* If there are commands left in the chain buffer */
	{
		/*Initialize the new iterator to the current buffer position*/
		j = i;
		p = chain_buffer + i; /* get pointer for return */

		check_chain(info, chain_buffer, &j, i, len);
		while (j < len) /* Iterate to the semicolon or end */
		{
			if (is_chain(info, chain_buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	/* else not a chain, pass back buffer from _getline() */
	*buf_p = chain_buffer;
	return (bytes_read); /* return length of buffer from _getline() */
}

/**
 * read_buf - Read data from a file descriptor into a buffer and
 *            update the buffer position.
 * @info: A pointer to the info_type structure containing file
 *        descriptor and buffer information.
 * @buf: A pointer to the buffer where data will be read into.
 * @buffer_position: A pointer to the position within the buffer.
 *
 * Return: The number of bytes read or an error code (negative value).
 */
ssize_t read_buf(info_type *info, char *buf, size_t *buffer_position)
{
	ssize_t bytes_read = 0;

	if (*buffer_position)
		return (0);
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*buffer_position = bytes_read;
	return (bytes_read);
}

/**
 * _getline - Read a line from a file descriptor and
 *            append it to a buffer.
 * @info: A pointer to the info_type structure containing
 *        file descriptor information.
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: A pointer to the length of the buffer.
 *
 * Return: The length of the line read or -1 on failure or EOF.
 */
int _getline(info_type *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_interrupt_signal - Handle the SIGINT signal (Ctrl+C).
 * @signal_number: The signal number (unused).
 */
void handle_interrupt_signal(__attribute__((unused))int signal_number)
{
	_puts("\n");
	_puts(PROMPT);
	_putchar(BUF_FLUSH);
}
