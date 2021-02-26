# System76 Lemur Pro (lemp9)

See the [product page][lemp9] for a general overview. See the
[tech-docs] for internal photos and repair guide.

## Building coreboot

The following commands will build a working image:

```bash
make distclean
make defconfig KBUILD_DEFCONFIG=configs/config.system76_lemp9
make
```

## Flashing coreboot

```eval_rst
+---------------------+------------+
| Type                | Value      |
+=====================+============+
| Socketed flash      | no         |
+---------------------+------------+
| Vendor              | GigaDevice |
+---------------------+------------+
| Model               | GD25Q128C  |
+---------------------+------------+
| Size                | 16 MiB     |
+---------------------+------------+
| Package             | SOIC-8     |
+---------------------+------------+
| Internal flashing   | yes        |
+---------------------+------------+
| External flashing   | yes        |
+---------------------+------------+
```

The flash chip is located between the RAM slot and fan.

## Resources

- [GD25Q128C data sheet][GD25Q128C]

[lemp9]: https://system76.com/guides/lemp9
[tech-docs]: https://tech-docs.system76.com/models/lemp9/README.html
[GD25Q128C]: https://www.gigadevice.com/datasheet/gd25q128c/gd251128c_v2.5_20170726.pdf
