cmake_minimum_required(VERSION 3.10)
project(test_png)
set(CMAKE_C_STANDARD 99)

# Find the libpng library
find_package(PNG REQUIRED)

# ajouter ce code pour vérifier si la librairie mathématique est automatiquement liée
# (ce n'est pas le cas pour gcc sous Linux, ce code est donc indispensable dans ce cas)
include(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(m sin "" HAVE_LIB_M)                                                                                                                                                                                                                                         
if (HAVE_LIB_M)                                                                                                                          
    set(EXTRA_LIBS ${EXTRA_LIBS} m)                                                                                                      
endif (HAVE_LIB_M)

# Add an executable target
add_executable(test_png testImage.c pngwrap.c correlation.c)

# Link the libpng library to the test_png target
target_link_libraries(test_png PRIVATE PNG::PNG) 

# ajouter cette instruction pour lier la librairie mathématique si nécessaire (le cas de gcc sous Linux)
target_link_libraries(test_png PUBLIC ${EXTRA_LIBS})