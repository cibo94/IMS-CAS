
ADD_EXECUTABLE(unit_tests
	main.cpp
	)
TARGET_LINK_LIBRARIES(unit_tests)

ADD_TEST(TEST_UNIT ${VALGRIND} ./unit_tests)
