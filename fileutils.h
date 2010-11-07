#ifndef _FILEUTILS_H
#define _FILEUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

extern int abort_copy, copy_mode, copy_is_split;
extern int num_directories, num_files_big, num_files_split;
extern int file_counter;
extern int64_t global_device_bytes;

extern int my_game_copy(char *path, char *path2);
extern int my_game_test(char *path);
extern int my_game_delete(char *path);

#ifdef __cplusplus
}
#endif

#endif

/* vim: set ts=4 sw=4 sts=4 tw=120 */
