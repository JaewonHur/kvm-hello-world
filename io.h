/* IO instructions */

static inline void outb(uint16_t port, uint32_t value) {
	asm("out %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
};

static inline uint32_t inb(uint16_t port) {
	uint32_t ret;
	asm("in %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
};

static inline size_t oin(uint16_t port, uint32_t value) {
	size_t ret;
	asm("out %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
	asm("in %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
};
