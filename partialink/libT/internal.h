

// GNU Attribute pour forcer un symbole visible
#if HAS_ATTRIB
# define ATTRIB_VISIBILITY       __attribute__ ((visibility("default")))
#else
# define ATTRIB_VISIBILITY
#endif

