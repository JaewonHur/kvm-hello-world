#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "fs.h"


static inline uint32_t getNumExits() {
	return inb(0xF8);
}

static inline void printVal(uint32_t val) {
	outb(0xF9, val);
}

static inline void display(const char *str) {
	outb(0xFA, str);
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	const char *p;

	for (p = "Hello, world!\n"; *p; ++p)
		outb(0xE9, *p);

	static int fd = 0;
	static char *buf = "abcdefgh\n";

	display(buf);

	fd = open("test.txt", O_WRONLY);
	printVal(fd);

	read((int) fd, (char *) buf, 4);

	display(buf);

	write((int) fd, "GoodBye", 7);

	*(long *) 0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
