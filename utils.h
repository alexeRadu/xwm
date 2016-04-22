#ifndef UTILS_H
#define UTILS_H

#define error(m, ...) 	fprintf(stderr, "[ERR] " m "\n", ##__VA_ARGS__)
#define info(m, ...) 	fprintf(stderr, "[INFO] " m "\n", ##__VA_ARGS__)

#endif
