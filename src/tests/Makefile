.PHONY: all clean basicRaytracing telescopeOcclusion

all : basicRaytracing telescopeOcclusion

basicRaytracing:
	cd basicRaytracing && $(MAKE)

telescopeOcclusion:
	cd telescopeOcclusion && $(MAKE)

clean:
	@echo "Clean."
	cd basicRaytracing && $(MAKE) clean
	cd telescopeOcclusion && $(MAKE) clean
