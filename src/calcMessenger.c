#include "calcMessenger.h"
#include <stdio.h>
#include <stdarg.h>

void LogError(char *errorFormat, ...)
{
	CustomLog(TEXT_BOLD, FG_RED, BG_DEFAULT, "ERROR: ");

	va_list args;
	va_start(args, errorFormat);
	vprintf(errorFormat, args);
	va_end(args);
}

void LogWarning(char *warningFormat, ...)
{
	CustomLog(TEXT_BOLD, FG_YELLOW, BG_DEFAULT, "WARNING: ");

	va_list args;
	va_start(args, warningFormat);
	vprintf(warningFormat, args);
	va_end(args);
}

void LogInfo(char *infoFormat, ...)
{
	CustomLog(TEXT_ITALIC, FG_WHITE, BG_DEFAULT, "INFO: ");

	va_list args;
	va_start(args, infoFormat);
	vprintf(infoFormat, args);
	va_end(args);
}

void CustomLog(char textStyle, char fgColor, char bgColor, char *format, ...)
{
	printf("\x1b[%d;%d;%dm", textStyle, fgColor, bgColor);

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("\x1b[0m");
}
