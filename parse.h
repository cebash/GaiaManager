#ifndef _PARSE_H
#define _PARSE_H

#ifdef __cplusplus
extern "C" {
#endif

extern int parse_ps3_disc(char *path, char *id);
extern int parse_param_sfo(char *file, const char *field, char *title_name);
extern void change_param_sfo_version(char *file);

#ifdef __cplusplus
}
#endif

#endif

/* vim: set ts=4 sw=4 sts=4 tw=120 */
