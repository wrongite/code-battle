#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long timestamp_t;

    timestamp_t get_timestamp ()
    {
      struct timeval now;
      gettimeofday (&now, NULL);
      return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
    }

int main(int argc, char **argv) {
    
    timestamp_t t0 = get_timestamp();
    system(argv[1]);
    timestamp_t t1 = get_timestamp();

    double secs = (t1 - t0) / 1000000.0L;
    printf("%0.9fs\n", secs);

    return 0;
}

