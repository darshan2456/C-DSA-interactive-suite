#include "file_exporter.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h>
#define make_dir(path) _mkdir(path)
#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & _S_IFMT) == _S_IFDIR)
#endif
#ifndef S_ISREG
#define S_ISREG(mode) (((mode) & _S_IFMT) == _S_IFREG)
#endif
#else
#define make_dir(path) mkdir(path, 0755)
#endif

static void ensure_dir_exists(const char* dirpath)
{
    if (!dirpath || strlen(dirpath) == 0)
    {
        return;
    }
    char tmp[1024];
    snprintf(tmp, sizeof(tmp), "%s", dirpath);
    size_t len = strlen(tmp);
    if (len == 0)
    {
        return;
    }
    if (tmp[len - 1] == '/')
    {
        tmp[len - 1] = '\0';
    }
    for (char* p = tmp + 1; *p; p++)
    {
        if (*p == '/')
        {
            *p = '\0';
            make_dir(tmp);
            *p = '/';
        }
    }
    make_dir(tmp);
}

bool dfs_search_file(const char* base_dir, const char* target_filename, char* found_path_out)
{
    if (!base_dir || !target_filename || !found_path_out)
    {
        return false;
    }

    const char* search_dir = base_dir;
    struct stat st_src;
    if (strcmp(base_dir, ".") == 0)
    {
        if (stat("src", &st_src) == 0 && S_ISDIR(st_src.st_mode))
        {
            search_dir = "src";
        }
        else if (stat("../src", &st_src) == 0 && S_ISDIR(st_src.st_mode))
        {
            search_dir = "../src";
        }
    }

    DIR* dir = opendir(search_dir);
    if (!dir)
    {
        return false;
    }

    struct dirent* entry;
    bool found = false;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, ".git") == 0 || strcmp(entry->d_name, "build") == 0 ||
            strcmp(entry->d_name, "object_files") == 0 ||
            strcmp(entry->d_name, "test_binaries") == 0 ||
            strncmp(entry->d_name, "test_", 5) == 0 || strncmp(entry->d_name, "export", 6) == 0 ||
            entry->d_name[0] == '.')
        {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", search_dir, entry->d_name);

        struct stat st;
        if (stat(path, &st) == -1)
        {
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            if (dfs_search_file(path, target_filename, found_path_out))
            {
                found = true;
                break;
            }
        }
        else if (S_ISREG(st.st_mode))
        {
            if (strcmp(entry->d_name, target_filename) == 0)
            {
                strncpy(found_path_out, path, 512);
                found_path_out[511] = '\0';
                found = true;
                break;
            }
        }
    }

    closedir(dir);
    return found;
}

bool copy_file_contents(const char* src_path, const char* dest_path)
{
    if (!src_path || !dest_path)
    {
        return false;
    }

    FILE* src_fp = fopen(src_path, "rb");
    if (!src_fp)
    {
        return false;
    }

    char dest_dir[1024];
    strncpy(dest_dir, dest_path, sizeof(dest_dir) - 1);
    dest_dir[sizeof(dest_dir) - 1] = '\0';
    char* last_slash = strrchr(dest_dir, '/');
    if (last_slash != NULL)
    {
        *last_slash = '\0';
        ensure_dir_exists(dest_dir);
    }

    FILE* dest_fp = fopen(dest_path, "wb");
    if (!dest_fp)
    {
        fclose(src_fp);
        return false;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_fp)) > 0)
    {
        fwrite(buffer, 1, bytes_read, dest_fp);
    }

    fclose(src_fp);
    fclose(dest_fp);
    return true;
}

bool export_file_pair(const char* root_dir, const char* base_filename, const char* header_basename,
                      const char* dest_dir, char* exported_c_path, char* exported_h_path)
{
    if (!root_dir || !base_filename || !dest_dir)
    {
        return false;
    }

    const char* start_dir = (strlen(root_dir) > 0) ? root_dir : ".";

    char c_filename[256];
    char h_filename[256];
    snprintf(c_filename, sizeof(c_filename), "%s.c", base_filename);
    snprintf(h_filename, sizeof(h_filename), "%s.h",
             header_basename ? header_basename : base_filename);

    char found_c_src[1024] = {0};
    char found_h_src[1024] = {0};

    bool found_c = dfs_search_file(start_dir, c_filename, found_c_src);
    bool found_h = dfs_search_file(start_dir, h_filename, found_h_src);

    if (!found_c || !found_h)
    {
        return false;
    }

    ensure_dir_exists(dest_dir);

    char target_c_dest[1024];
    char target_h_dest[1024];

    size_t dest_len = strlen(dest_dir);
    if (dest_len > 0 && dest_dir[dest_len - 1] == '/')
    {
        snprintf(target_c_dest, sizeof(target_c_dest), "%s%s", dest_dir, c_filename);
        snprintf(target_h_dest, sizeof(target_h_dest), "%s%s", dest_dir, h_filename);
    }
    else
    {
        snprintf(target_c_dest, sizeof(target_c_dest), "%s/%s", dest_dir, c_filename);
        snprintf(target_h_dest, sizeof(target_h_dest), "%s/%s", dest_dir, h_filename);
    }

    bool success_c = copy_file_contents(found_c_src, target_c_dest);
    if (success_c && exported_c_path)
    {
        strncpy(exported_c_path, target_c_dest, 512);
        exported_c_path[511] = '\0';
    }

    bool success_h = copy_file_contents(found_h_src, target_h_dest);
    if (success_h && exported_h_path)
    {
        strncpy(exported_h_path, target_h_dest, 512);
        exported_h_path[511] = '\0';
    }

    return (success_c && success_h);
}

bool export_generic_state(const char* ds_name, const char* format, const char* details)
{
    if (!ds_name || !format || !details)
    {
        return false;
    }

    ensure_dir_exists("exports");

    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "exports/%s_state.%s", ds_name, format);

    FILE* fp = fopen(filepath, "w");
    if (!fp)
    {
        return false;
    }

    if (strcasecmp(format, "json") == 0)
    {
        // If not already structured as JSON, format it
        if (details[0] != '{' && details[0] != '[')
        {
            fprintf(fp, "{\n  \"data_structure\": \"%s\",\n  \"state\": \"%s\"\n}\n", ds_name,
                    details);
        }
        else
        {
            fprintf(fp, "%s\n", details);
        }
    }
    else if (strcasecmp(format, "csv") == 0)
    {
        // Simple CSV format check
        if (strchr(details, '\n') == NULL)
        {
            fprintf(fp, "DataStructure,State\n%s,%s\n", ds_name, details);
        }
        else
        {
            fprintf(fp, "%s\n", details);
        }
    }
    else
    {
        // Fallback or TXT format
        fprintf(fp, "=== %s STATE SNAPSHOT ===\n", ds_name);
        fprintf(fp, "%s\n", details);
    }

    fclose(fp);
    printf("\n[Export Successful] Saved to: %s\n", filepath);
    return true;
}

void draw_unicode_box_header(const char* title)
{
    if (!title)
        return;
    printf("\n┌────────────────────────────────────────────────────────┐\n");
    printf("│ %-54s │\n", title);
    printf("├────────────────────────────────────────────────────────┤\n");
}

void draw_unicode_box_footer(void)
{
    printf("└────────────────────────────────────────────────────────┘\n");
}
