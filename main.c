/**
 * @file main.c
 * @brief Implement command line tool.
 */
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#include <time.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <syslog.h>
#include "ebsinit.c"

/**
 * @brief The maximum number of IO requests that can be executed simultaneously
 * 
 * Currently, about 500 is sufficient, but if AWS performance improves in 
 * the future, you may want to specify a larger number.
 * If it is too large, it will be difficult to accept keyboard interrupts.
 */
#define IO_RANGE 500

/**
 * @brief Progress rate output interval when using syslog
 *
 * Specify in seconds.
 */
#define LOG_INTERVAL 300

/**
 * @brief Progress rate output interval when using display output
 *
 * Specify in seconds.
 */
#define DISPLAY_INTERVAL 5

/** @brief True if the progress rate is not displayed */
static int silent_mode = 0;

/** @brief True when using syslog */
static int syslog_mode = 0;

/** @brief Unix time when the last log was recorded */
static int last_log_time = 0;

/** @brief Unix time when progress was last displayed */
static int last_display_time = 0;

/**
 * @brief display help mesage
 */
void help()
{
    puts("Usage: [options] Target");
    puts("Initialize EBS volume.");
    puts("");
    puts("options:");
    puts("  -s, --silent    Do not show progress");
    puts("  -l, --syslog    Progress is output to syslog");
    puts("  -v, --version   Output version number and exit");
    puts("  -h, --help      Display this help and exit");
    puts("");
    puts("example:");
    puts("  ebsinit -s /dev/xvda");
    puts("  ebsinit -ls /dev/xvda1");
}

/**
 * @brief display version code
 */
void version()
{
    puts(EBSINIT_VERSION);
}

/**
 * @brief Error termination processing
 * @param err Error code
 */
void error_abort(int err)
{
    fputs(strerror(err), stderr);
    fputs("\n", stderr);
    if (syslog_mode) {
        syslog(LOG_ERR, "Error: %s", strerror(err));
    }
}

/**
 * @brief Progress display
 * @param h handle of ebsinit
 * @param cur_no Processing number
 * @param max_no Maximum processing number
 */
void display_progress(ebsinit_handle h, int cur_no, int max_no)
{
    float rate = (float)cur_no / (float)max_no * 100.0;
    time_t t = time(NULL);
    if (!silent_mode) {
        if (rate == 100.0 || t - last_display_time >= DISPLAY_INTERVAL) {
            fprintf(stderr, "\r\033[2K%3.1f%% done.", rate);
            fflush(stderr);
            last_display_time = t;
        }
    }
    if (syslog_mode) {
        if (rate == 100.0 || t - last_log_time >= LOG_INTERVAL) {
            syslog(LOG_ERR, "Info: %3.1f%% done.", rate);
            last_log_time = t;
        }
    }
}

/**
 * @vrief main
 */
int main(int argc, char* const argv[])
{
    if (argc == 1) {
        help();
        return 0;
    }
    struct option longopts[] = {
        { "silent",     no_argument,       NULL, 's' },
        { "syslog",     no_argument,       NULL, 'l' },
        { "help",       no_argument,       NULL, 'h' },
        { "version",    optional_argument, NULL, 'v' },
        { NULL,         0,                 0,     0  },
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "slhv", longopts, NULL)) != -1) {
      switch (opt) {
        case 's':
          silent_mode = 1;
          break;
        case 'l':
          syslog_mode = 1;
          break;
        case 'h':
          help();
          return 0;
        case 'v':
          version();
          return 1;
        default:
          return 1;
      }
    }
    if (optind != argc - 1) {
        puts("Please specify only one target device.");
        return 1;
    }

    const char* target = argv[argc - 1];
    if (syslog_mode) {
        openlog(NULL, LOG_PID, LOG_USER);
        syslog(LOG_INFO, "Info: Start initialize of '%s'.", target);
    }

    struct stat stat_buf;
    if (stat(argv[argc - 1], &stat_buf)) {
        error_abort(errno);
        return 1;
    }
    if (!S_ISBLK(stat_buf.st_mode) && !S_ISREG(stat_buf.st_mode)) {
        const char* message = "Target can only be block devices or regular file.";
        fputs(message, stderr);
        fputs("\n", stderr);
        if (syslog_mode) {
            syslog(LOG_ERR, "Error: %s", message);
        }
        return 1;
    }
    int fd = open(target, O_RDONLY | O_DIRECT);
    if (fd == -1) {
        error_abort(errno);
        return 1;
    }
    off64_t size = lseek64(fd, 0, SEEK_END);
    if (size == -1) {
        error_abort(errno);
        return 1;
    }
    if (syslog_mode) {
        syslog(LOG_INFO, "Info: Target size = %lld bytes.", (long long)size);
    }

    ebsinit_handle h = ebsinit_alloc(IO_RANGE);
    if (!h) {
        error_abort(errno);
        return 1;
    }
    h->print = display_progress;
    h->user_data = (void*)target;
    ebsinit_setup(h, fd);
    ebsinit_do(h, 0, size);
    if (!silent_mode) {
        fputs("\n", stderr);
    }
    ebsinit_release(h);
    close(fd);
    if (syslog_mode) {
        syslog(LOG_INFO, "Info: Complete.");
    }
    return 0;
}
