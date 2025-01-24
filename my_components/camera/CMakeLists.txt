idf_component_register(SRCS "camera.c"
        INCLUDE_DIRS "." "../../managed_components/espressif__esp32-camera/driver/include" "../../managed_components/espressif__esp32-camera/conversions/include"
		REQUIRES driver fatfs)