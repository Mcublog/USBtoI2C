#!/usr/bin/env python3

import time

import serial
from cobs import cobsr


def main():
    data = str.encode("-led on")
    with serial.Serial(port="/dev/ttyS11") as s:
        data = cobsr.encode(data)
        print(f"send: {data}")
        s.write(data + b'\x00')
        time.sleep(0.100)
        print(f"read: {s.read_all().decode('utf-8')}")


if __name__ == "__main__":
    main()

