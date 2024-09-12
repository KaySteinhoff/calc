#ifndef CALC_MESSENGER_H_
#define CALC_MESSENGER_H_

#define FG_BLACK 	30
#define FG_RED 		31
#define FG_GREEN 	32
#define FG_YELLOW 	33
#define FG_BLUE 	34
#define FG_MAGENTA 	35
#define FG_CYAN 	36
#define FG_WHITE 	37
#define FG_DEFAULT 	39

#define BG_BLACK 	40
#define BG_RED 		41
#define BG_GREEN 	42
#define BG_YELLOW 	43
#define BG_BLUE 	44
#define BG_MAGENTA 	45
#define BG_CYAN 	46
#define BG_WHITE 	47
#define BG_DEFAULT 	49

#define TEXT_DEFAULT		0
#define TEXT_BOLD		1
#define TEXT_DIM		2
#define TEXT_ITALIC		3
#define TEXT_UNDERLINE		4
#define TEXT_BLINKING		5
#define TEXT_INVERSE		7
#define TEXT_STRIKETHROUGH	9

void LogError(char *errorFormat, ...);
void LogWarning(char *warningFormat, ...);
void LogInfo(char *infoFormat, ...);
void CustomLog(char textStyle, char fgColor, char bgColor, char *format, ...);

#endif
