ADD_EXECUTABLE(unit_tests
	main.cpp
  test_cell.cpp
  test_state.cpp
  support.hh
  test_automata.cpp
  test_plot.cpp)
TARGET_LINK_LIBRARIES(unit_tests)
ADD_TEST(TEST_UNIT ${VALGRIND} ./unit_tests)

ADD_EXECUTABLE(bmp_tests
	test_bmp.cpp)
TARGET_LINK_LIBRARIES(bmp_tests)
ADD_TEST(TEST_BMP ${PROJECT_SOURCE_DIR}/tests/check_bmp.sh ./bmp_tests)
