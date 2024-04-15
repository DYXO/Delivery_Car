cmake_minimum_required(VERSION 3.8)
project(motor_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

###########################################################################################
# Find the path to the pigpio includes.
find_path(pigpio_INCLUDE_DIR 
	NAMES pigpio.h pigpiod_if.h pigpiod_if2.h
	HINTS /usr/local/include)
	
# Find the pigpio libraries.
find_library(pigpio_LIBRARY 
	NAMES libpigpio.so
	HINTS /usr/local/lib)
find_library(pigpiod_if_LIBRARY 
	NAMES libpigpiod_if.so
	HINTS /usr/local/lib)
find_library(pigpiod_if2_LIBRARY 
	NAMES libpigpiod_if2.so
	HINTS /usr/local/lib)
    
# Set the pigpio variables to plural form to make them accessible for 
# the paramount cmake modules.
set(pigpio_INCLUDE_DIRS ${pigpio_INCLUDE_DIR})
set(pigpio_INCLUDES     ${pigpio_INCLUDE_DIR})

# Handle REQUIRED, QUIET, and version arguments 
# and set the <packagename>_FOUND variable.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pigpio 
    DEFAULT_MSG 
    pigpio_INCLUDE_DIR pigpio_LIBRARY pigpiod_if_LIBRARY pigpiod_if2_LIBRARY)
  
add_executable(motor_control src/motor.cpp)
 
install(TARGETS
  motor_control
  DESTINATION lib/${PROJECT_NAME})
target_link_libraries(motor_control libpigpio.so)

##########################################################################################

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
