products ?= tmp


.PHONEY : check
check : $(products)/test
	$(products)/test


.PHONEY : clean
clean :
	-rm $(products)/test


$(products)/test : main.c ../va_args_count.h | $(products)
	$(CC) $(CFLAGS) -I.. -o$@ $<


$(products) :
	mkdir -p $@
