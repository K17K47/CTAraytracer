.PHONY: all clean basicRaytracing telescopeOcclusion precisionTest

all : basicRaytracing telescopeOcclusion precisionTest

basicRaytracing:
	cd basicRaytracing && $(MAKE)

telescopeOcclusion:
	cd telescopeOcclusion && $(MAKE)

precisionTest:
	cd precisionTest && $(MAKE)

clean:
	@echo "Clean."
	cd basicRaytracing && $(MAKE) clean
	cd telescopeOcclusion && $(MAKE) clean
	cd precisionTest && $(MAKE) clean
