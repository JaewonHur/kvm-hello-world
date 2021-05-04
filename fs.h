/* File system */

#define OPEN 0xA0
#define READ 0xB0
#define WRITE 0xC0

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2

typedef struct _hypercall_open {
    char *fname;
    int flags;
    int fd;
} hypercall_open;

typedef struct _hypercall_read {
    int fd;
    void *buf;
    size_t count;
    size_t ret;
} hypercall_read;

typedef struct _hypercall_write {
    int fd;
    void *buf;
    size_t count;
    size_t ret;
} hypercall_write;

static hypercall_open hopen = { 0, };
static hypercall_read hread = { 0, };
static hypercall_write hwrite = { 0, };

static inline int open(const char *fname, int flags) {
    hopen.fname = (char *) fname;
    hopen.flags = flags;

    outb(OPEN, (size_t) &hopen);
    return hopen.fd;
};

static inline size_t read(int fd, void *buf, size_t count) {
    hread.fd = fd;
    hread.buf = buf;
    hread.count = count;

    outb(READ, (size_t) &hread);
    return hread.ret;
};

static inline size_t write(int fd, const void *buf, size_t count) {
    hwrite.fd = fd;
    hwrite.buf = buf;
    hwrite.count = count;

    outb(WRITE, (size_t) &hwrite);
    return hwrite.ret;
}
