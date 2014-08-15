.PHONEY: clean


test: main.c ../va_args_count.h
	$(CC) $(CFLAGS) -I.. -o$@ $<


clean:
	-$(RM) test
