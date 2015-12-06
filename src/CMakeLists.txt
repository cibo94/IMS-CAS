set(CAS_SOURCE
	main.cpp
	cell.hh
	state.hh
	cellular_automata.hh
	bmp.hh
	)

add_executable(cas ${CAS_SOURCE} bmp.hh)

target_link_libraries(cas)
