# HT16K33 14-Segment Display Driver for Apache Mynewt

This has been written against Apache Mynewt 1.4.1. Changes may be required
when using it with different releases.

# Folder Structure

- Reasonably complete **documentation** is available in the `docs` folder. The
documentation can be built via `doxygen Doxyfile`.

# Hardware

This package has been tested with the following hardware:

- [Adafruit Feather nRF52 Pro with myNewt Bootloader - nRF52832](https://www.adafruit.com/product/3574)

- [Adafruit 14-Segment Alphanumeric LED FeatherWing](https://www.adafruit.com/product/3089)

- [Dual Alphanumeric Display -Yellow 0.54" Digit Height - Pack of 2](https://www.adafruit.com/product/2154)

# Usage

The following code snippet shows how this package can be used. It assumes the
presence of 4 14-segment displays, numbered 0..3 below:

```
int rc;

/* Initialise the display at brightness 9/16. */
rc = ht16k33_init(HTK16K33_REG_DIM_9);
if (rc) {
    console_printf("HT16K33 init failed: %d\n", rc);
}

/* Display some test data on the display. */
ht16k33_write_num(0, 1, true);      /* 1. */
ht16k33_write_num(1, 2, false);     /* 2  */
ht16k33_write_num(2, 5, false);     /* 5  */
ht16k33_write_alpha(3, 'K', false); /* K  */
```
