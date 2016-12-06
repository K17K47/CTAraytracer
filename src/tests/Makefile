.PHONY: all clean basicRaytracing telescopeOcclusion octreeTest

all : basicRaytracing telescopeOcclusion octreeTest

basicRaytracing:
	cd basicRaytracing && $(MAKE)

telescopeOcclusion:
	cd telescopeOcclusion && $(MAKE)

octreeTest:
	cd octreeTest && $(MAKE)

clean:
	@echo "Clean."
	cd basicRaytracing && $(MAKE) clean
	cd telescopeOcclusion && $(MAKE) clean
	cd octreeTest && $(MAKE) clean
