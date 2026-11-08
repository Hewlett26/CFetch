
#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <dirent.h>

int main(void) {
    char info[8][256] = {0};

    // Ram
    FILE *fptr = fopen("/proc/meminfo", "r");

    if (fptr == NULL) {
        perror("meminfo");
        return 1;
    }

    unsigned long memtotal = 0, memavailable = 0;
    char myString[100];

    while (fgets(myString, sizeof(myString), fptr)) {
        if (strstr(myString, "MemTotal:"))
            sscanf(myString, "MemTotal: %lu", &memtotal);

        if (strstr(myString, "MemAvailable:"))
            sscanf(myString, "MemAvailable: %lu", &memavailable);
    }

    fclose(fptr);

    if (memtotal == 0) {
        fprintf(stderr, "Unable to read memory information.\n");
        return 1;
    }

    double total_gb = (double)memtotal / (1024 * 1024);
    double available_gb = (double)memavailable / (1024 * 1024);

    snprintf(info[0], sizeof(info[0]),
             "Memory: %.2f / %.2f GiB",
             total_gb - available_gb, total_gb);

    
    // uptime
    FILE *fileptr = fopen("/proc/uptime", "r");

    if (fileptr == NULL) {
        perror("uptime");
        return 1;
    }

    double uptime = 0;
    fscanf(fileptr, "%lf", &uptime);
    fclose(fileptr);

    int hours = (int)uptime / 3600;
    int minutes = ((int)uptime % 3600) / 60;

    snprintf(info[1], sizeof(info[1]),
             "Uptime: %d hour%s %d minute%s",
             hours, hours == 1 ? "" : "s",
             minutes, minutes == 1 ? "" : "s");

    // hname
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        hostname[sizeof(hostname) - 1] = '\0';
        snprintf(info[2], sizeof(info[2]),
                 "Hostname: %s", hostname);
    }

    // uname
    char *username = getenv("USER");

    snprintf(info[3], sizeof(info[3]),
             "User: %s", username ? username : "Unknown");

    // shee-heell
    char *shell = getenv("SHELL");

    snprintf(info[4], sizeof(info[4]),
             "Shell: %s", shell ? shell : "Unknown");

    // distro
    FILE *cfprt = fopen("/etc/os-release", "r");

    if (cfprt == NULL) {
        perror("os-release");
        return 1;
    }

    char pname[100] = "Unknown";
    char tring[256];

    while (fgets(tring, sizeof(tring), cfprt)) {
        if (strncmp(tring, "PRETTY_NAME=", 12) == 0) {
            char *start = strchr(tring, '"');
            char *end = strrchr(tring, '"');

            if (start && end && start != end) {
                *end = '\0';
                snprintf(pname, sizeof(pname), "%s", start + 1);
            }
            break;
        }
    }

    fclose(cfprt);

    snprintf(info[5], sizeof(info[5]), "Distro: %s", pname);

    // kernel
    struct utsname sysinfo;

    if (uname(&sysinfo) == 0) {
        snprintf(info[6], sizeof(info[6]),
                 "Kernel: %s", sysinfo.release);
    }

    // pkgs
    DIR *dirp = opendir("/var/lib/pacman/local/");

    if (dirp == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    int packages = 0;

    while ((entry = readdir(dirp)) != NULL) {
        if (entry->d_type == DT_DIR &&
            entry->d_name[0] != '.') {
            packages++;
        }
    }

    closedir(dirp);

    snprintf(info[7], sizeof(info[7]),
             "Packages: %d", packages);

    // CFetch Special Logo
    char *logo[] = {
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⢀⢀⢀⢀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ",
    "⠀⠀⠀⠀⠀⠀⠀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⠀⠀⠀⠀⠀⠀ ",
    "⠀⠀⠀⢀⢀⢀⢀⢀⢀⢁⣠⣤⣤⣴⣶⣦⣤⣤⣠⡐⢀⢀⢀⢀⢀⢀⠀⠀ ",
    "⢀⢀⢀⢀⢀⢀⢁⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡐⢀⢀⢀⠁⠂",
    "⢀⢀⢀⢀⢀⣰⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⠆⠁⠁⠀⠀ ",
    "⢀⢀⢀⢀⣸⣿⣿⣿⣿⣿⠟⠉⢀⢀⢀⢀⢀⠉⠻⠿⠛⠉⠀⠀⠀⠀⠀⠀ ",
    "⢀⢀⢀⢀⣿⣿⣿⣿⣿⡇⢀⢀⢀⢀⠁⠁⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ",
    "⢀⢀⢀⠈⣿⣿⣿⣿⣿⡇⠁⠁⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ",
    "⢀⢀⢀⢀⢻⣿⣿⣿⣿⣿⣄⡀⠀⠀⠀⠀⠀⢀⣠⣶⣤⣀⠀⠀⠀⠀⠀⠀ ",
    "⢀⢀⠁⠁⠁⠻⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⠖⠀⠀⠀⠀ ",
    "⠁⠁⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀ ",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠛⠿⠿⠿⠿⠿⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀ "
    };

    // how to display ts
    int logo_lines = sizeof(logo) / sizeof(logo[0]);
    int info_lines = sizeof(info) / sizeof(info[0]);

    int max_lines = logo_lines > info_lines
                    ? logo_lines : info_lines;

    for (int i = 0; i < max_lines; i++) {
        if (i < logo_lines)
            printf("%s", logo[i]);

        if (i < info_lines)
            printf("    %s", info[i]);

        printf("\n");
    }

    return 0;
}

