#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "lametus.h"
#include "encoder.h"
#include "audio.h"

static int line;
static FILE *fp;
static char *token;

static void parse_token(void)
{
	char tokenbuf[1024];
	int pos = 0;
	int quoted = 0;
	int c;

	while (1)
	{
		c = fgetc(fp);

		if (isspace(c) && !pos)
		{
			if (c == '\n')
				line++;

			continue;
		}
		else if (c == '"')
		{
			quoted = 1 - quoted;
			continue;
		}
		else if (c == EOF || (!quoted && !isalnum(c)))
		{
			if (!pos && c != EOF)
				tokenbuf[pos++] = (char)c;
			else if (c != EOF && !isspace(c))
				ungetc(c,fp);

			break;
		}

		tokenbuf[pos++] = (char)c;

		if (pos >= 1024)
			fatal("Too long token in configuration file on line %d",line);
	}

	if (c == '\n')
		line++;

	tokenbuf[pos] = '\0';
	token = strdup(tokenbuf);
}

static signed long parse_number(void)
{
	char *tmp;
	signed long tmpnum;

	free(token);
	parse_token();
	tmpnum = strtol(token,&tmp,0);

	if (*tmp)
		fatal("Number argument expected in configuration file on line %d",line);

	return tmpnum;
}

static char *parse_string(void)
{
	free(token);
	parse_token();

	return strdup(token);
}

static void encoder_block(void)
{
	char *saved_token = token;
	struct encoder *enc = encoder_create();

	parse_token();

	if (strcmp("{",token))
		fatal("Syntax error in configuration file on line %d, expected \"{\" but got \"%s\"",line,token);

	while (1)
	{
		fprintf(stderr, "%s\n", token);
		free(token);

		parse_token();

		if (!strlen(token))
			fatal("Unexpected EOF in configuration file");

		if (!strcmp(token,"samplerate"))
			enc->samplerate = parse_number();
		else if (!strcmp(token,"mono"))
			enc->mono = 1;
		else if (!strcmp(token,"bitrate"))
			enc->bitrate = parse_number();
		else if (!strcmp(token,"serverhost"))
		{
			free(token);
			parse_token();

			enc->server_addr.sin_addr.s_addr = inet_addr(token);

			if (enc->server_addr.sin_addr.s_addr == -1)
				fatal("Could not parse \"%s\" as IP address in configuration file on line %d", token,line);
		}
		else if (!strcmp(token,"filename"))
			enc->file_name = parse_string();
		else if (!strcmp(token,"serverport"))
			enc->server_addr.sin_port = htons(parse_number());
		else if (!strcmp(token,"password"))
			enc->passwd = parse_string();
		else if (!strcmp(token,"name"))
			enc->name = parse_string();
		else if (!strcmp(token,"genre"))
			enc->genre = parse_string();
		else if (!strcmp(token,"url"))
			enc->url = parse_string();
		else if (!strcmp(token,"public"))
			enc->pub = parse_number();
		else if (strcmp(token,"}"))
			fatal("Unrecognized option \"%s\" in configuration file on line %d",token,
					line);
		else
			break;
	}

	token = saved_token;

	if (num_encoders >= MAX_ENCODERS)
		fatal("Too many encoders specified");

	encoders[num_encoders++] = enc;
}

static void source_block(void)
{
	char *saved_token = token;
	struct audio_source *src = audio_source_create();

	parse_token();

	if (strcmp("{",token))
		fatal("Syntax error in configuration file on line %d, expected \"{\" but got \"%s\"",line,token);

	while (1)
	{
		free(token);

		parse_token();

		if (!strlen(token))
			fatal("Unexpected EOF in configuration file");

		if (!strcmp(token,"device"))
			src->devname = parse_string();
		else if (!strcmp(token,"samplerate"))
			src->samplerate = parse_number();
		else if (!strcmp(token,"channels"))
			src->channels = parse_number();
		else if (!strcmp(token,"stereo"))
			src->channels = 2;
		else if (!strcmp(token,"mono"))
			src->channels = 1;
		else if (strcmp(token,"}"))
			fatal("Unrecognized option \"%s\" in configuration file on line %d",token,
					line);
		else
			break;
	}

	token = saved_token;

	source = src;
}

void parse_file(FILE *file)
{
	line = 1;
	fp = file;

	token = NULL;

	do
	{
		parse_token();

		if (!strcmp(token,"encoder"))
			encoder_block();
		else if (!strcmp(token,"source"))
			source_block();
		else if (strlen(token))
			fatal("Parse error in configuration file on line %d",line);

		free(token);
	}
	while (!feof(file));
}
