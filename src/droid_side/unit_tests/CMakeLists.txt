
add_subdirectory(server_message_handler)
add_subdirectory(scanner)
add_subdirectory(mover)
add_subdirectory(sensor_adapter)
add_subdirectory(servo_adapter)
add_subdirectory(engine_adapter)

if(AXELEROMETER_INCLUDED)
	add_subdirectory(axelerometer_adapter)
endif()