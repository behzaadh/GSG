### tests
project(TESTGSGfile CXX C)

# source
SET(TestGSGfile_SOURCES
    main.cpp
)

add_executable(TestGSGfile ${TestGSGfile_SOURCES})

# add created library
target_link_libraries(TestGSGfile GSGfile)

# test compile and run
add_test(TestCompileAndRun TestGSGfile)
