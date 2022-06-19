#!/usr/bin/env python3

import time

import serial
from cobs import cobs


def main():
    data = str.encode("-h")
    with serial.Serial(port="/dev/ttyS11") as s:
        data = cobs.encode(data)
        print(f"send: {data}")
        s.write(data + b'\x00')


if __name__ == "__main__":
    main()
