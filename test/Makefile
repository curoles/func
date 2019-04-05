TST := $(SRC)/test

CFLAGS := -I$(SRC) -Wall -Werror

.PHONY: test test_file test_lambda
test: test_file test_lambda
	@echo done testing

test_file:
	rm -rf $@
	gcc $(CFLAGS) $(TST)/file.c -o $@
	./$@

test_lambda:
	rm -rf $@
	gcc $(CFLAGS) $(TST)/lambda.c -o $@
	./$@
