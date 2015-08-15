gcc -o evil -O0 -g evil.c
valgrind ./evil 100
