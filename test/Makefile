TST := $(SRC)/test

CFLAGS := -g -O2 -I$(SRC) -Wall -Werror

TEST_LIST := test_file test_lambda test_factorial test_result
TEST_LIST += test_foreach test_vector

.PHONY: test $(TEST_LIST)
test: $(TEST_LIST)
	@echo done testing

define do_test
	rm -rf $@
	gcc $(CFLAGS) $(TST)/$1 -o $@
	./$@
endef

test_file:
	rm -rf $@
	gcc $(CFLAGS) $(TST)/file.c -o $@
	./$@

test_lambda:
	rm -rf $@
	gcc $(CFLAGS) $(TST)/lambda.c -o $@
	./$@

test_factorial:
	rm -rf $@
	gcc $(CFLAGS) $(TST)/factorial.c -o $@
	./$@

test_result:
	$(call do_test,result.c)

test_foreach:
	$(call do_test,foreach.c)

test_vector:
	$(call do_test,vector.c)
