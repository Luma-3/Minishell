# CMake generated Testfile for 
# Source directory: /home/jbrousse/Downloads/check-0.15.2
# Build directory: /home/jbrousse/Downloads/check-0.15.2/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(check_check "/home/jbrousse/Downloads/check-0.15.2/build/tests/check_check")
set_tests_properties(check_check PROPERTIES  _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;500;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(check_check_export "/home/jbrousse/Downloads/check-0.15.2/build/tests/check_check_export")
set_tests_properties(check_check_export PROPERTIES  _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;501;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(test_output.sh "sh" "/home/jbrousse/Downloads/check-0.15.2/tests/test_output.sh")
set_tests_properties(test_output.sh PROPERTIES  WORKING_DIRECTORY "/home/jbrousse/Downloads/check-0.15.2/build/tests" _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;505;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(test_log_output.sh "sh" "/home/jbrousse/Downloads/check-0.15.2/tests/test_log_output.sh")
set_tests_properties(test_log_output.sh PROPERTIES  WORKING_DIRECTORY "/home/jbrousse/Downloads/check-0.15.2/build/tests" _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;508;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(test_xml_output.sh "sh" "/home/jbrousse/Downloads/check-0.15.2/tests/test_xml_output.sh")
set_tests_properties(test_xml_output.sh PROPERTIES  WORKING_DIRECTORY "/home/jbrousse/Downloads/check-0.15.2/build/tests" _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;511;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(test_tap_output.sh "sh" "/home/jbrousse/Downloads/check-0.15.2/tests/test_tap_output.sh")
set_tests_properties(test_tap_output.sh PROPERTIES  WORKING_DIRECTORY "/home/jbrousse/Downloads/check-0.15.2/build/tests" _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;514;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(test_check_nofork.sh "sh" "/home/jbrousse/Downloads/check-0.15.2/tests/test_check_nofork.sh")
set_tests_properties(test_check_nofork.sh PROPERTIES  WORKING_DIRECTORY "/home/jbrousse/Downloads/check-0.15.2/build/tests" _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;517;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(test_check_nofork_teardown.sh "sh" "/home/jbrousse/Downloads/check-0.15.2/tests/test_check_nofork_teardown.sh")
set_tests_properties(test_check_nofork_teardown.sh PROPERTIES  WORKING_DIRECTORY "/home/jbrousse/Downloads/check-0.15.2/build/tests" _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;520;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
add_test(test_set_max_msg_size.sh "sh" "/home/jbrousse/Downloads/check-0.15.2/tests/test_set_max_msg_size.sh")
set_tests_properties(test_set_max_msg_size.sh PROPERTIES  WORKING_DIRECTORY "/home/jbrousse/Downloads/check-0.15.2/build/tests" _BACKTRACE_TRIPLES "/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;523;add_test;/home/jbrousse/Downloads/check-0.15.2/CMakeLists.txt;0;")
subdirs("lib")
subdirs("src")
subdirs("checkmk")
subdirs("tests")
