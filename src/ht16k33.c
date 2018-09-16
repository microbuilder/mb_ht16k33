/**
 * Depending on the type of package, there are different
 * compilation rules for this directory.  This comment applies
 * to packages of type "pkg."  For other types of packages,
 * please view the documentation at http://mynewt.apache.org/.
 *
 * Put source files in this directory.  All files that have a *.c
 * ending are recursively compiled in the src/ directory and its
 * descendants.  The exception here is the arch/ directory, which
 * is ignored in the default compilation.
 *
 * The arch/<your-arch>/ directories are manually added and
 * recursively compiled for all files that end with either *.c
 * or *.a.  Any directories in arch/ that don't match the
 * architecture being compiled are not compiled.
 *
 * Architecture is set by the BSP/MCU combination.
 */

#include "ht16k33/ht16k33.h"
#include "ht16k33_priv.h"

/* Define the stats section and records */
STATS_SECT_START(ht16k33_stat_section)
    STATS_SECT_ENTRY(errors)
STATS_SECT_END

/* Define stat names for querying */
STATS_NAME_START(ht16k33_stat_section)
    STATS_NAME(ht16k33_stat_section, errors)
STATS_NAME_END(ht16k33_stat_section)

/* Global variable used to hold stats data */
STATS_SECT_DECL(ht16k33_stat_section) g_ht16k33stats;

#define HT16K33_LOG(lvl_, ...) \
    MODLOG_ ## lvl_(MYNEWT_VAL(HT16K33_LOG_MODULE), __VA_ARGS__)

int
ht16k33_init(void)
{
    int rc;

    /* Initialise the stats entry. */
    rc = stats_init(
        STATS_HDR(g_ht16k33stats),
        STATS_SIZE_INIT_PARMS(g_ht16k33stats, STATS_SIZE_32),
        STATS_NAME_INIT_PARMS(ht16k33_stat_section));
    if (rc != 0) {
        goto err;
    }

    /* Register the entry with the stats registry. */
    rc = stats_register("ht16k33", STATS_HDR(g_ht16k33stats));
    if (rc != 0) {
        goto err;
    }

    return (0);
err:
    return (rc);
}
